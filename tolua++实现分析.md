### tolua++实现分析


项目正在使用cocos2dx的lua绑定，绑定的方式是tolua++。对大规模使用lua代码信心不是很足，花了一些时间阅读tolua++的代码，希望对绑定实现的了解，有助于项目对lua代码的把控。从阅读结果上来看，起码在内存管理上，帮助还是很大的。

##### 1.tolua++如何将c++对象导入到lua里

tolua++为每一个传入lua的对象建立一个userdata，userdata的值，是c++对象的地址。userdata的metatable，是一个tolua++建立的，记录了userdata对应c++类型信息的表格，包括导出的成员变量、成员函数等信息。

对于成员变量的读取赋值，tolua++是在metatable里新建了.get和.set两个表。两个表里分别存储了以变量名为键，以读取设置c函数为值的表项。在metatable的__index和__newindex里，以变量名为键，从.get和.set表里取得读取设置函数并调用。


对于成员函数的调用，只需要以函数名为键，函数为值，存储在metatable里就好了。


传入c++对象的tolua++函数是tolua_pushusertype。一般情况下，第一次使用这个函数将一个c++对象push到lua堆栈上时，才会新建userdata。tolua++会以c++对象地址为键，userdata为值，将键值对存储在tolua_ubox表里。下次推入同样的c++对象时，从这个表里取出userdata推入堆栈即可。

—————————————————

#####  2.tolua++如何处理类型的继承

父类的metatable,是子类metatable的metatable。这样调用父类方法时，就会去父类的metatable里查找了。

tolua++还维护了一个tolua_super表，这个表以c++类型的metatable为键，以一个表格为值。这个值表格以类型名称为键，以true为值，记录了metatable对应c++类型的父类有哪些。这个表格可以用来帮助判断对象是否是某一个类型（子类实例也可以认为是父类类型）


—————————————————

#####  3.tolua++如何管理对象的生命周期

一般情况下，当lua里对c++对象的引用变量可以被垃圾回收时，tolua++只是简单的释放userdata占用的4字节指针地址内存。但是也可以通过绑定或者代码指定的方式，让tolua++真正释放对象所占内存。

绑定的方式，是指在将c++类型构造函数使用tolua++导出到lua里时，tolua++会自动生成new_local方法。如果在lua代码里，用这个方法新建对象时，tolua++会调用tolua_register_gc方法，指明回收对象时回收对象内存。

在c++代码里，使用`tolua_pushusertype_and_takeownership`；在lua代码里，使用`tolua.takeownership`，都可以达到同样的目的。

对于这些指定由tolua++回收内存的对象，如果其类型的析构函数也通过tolua++导出了，则在回收内存时，会通过delete运算符，调用对象的析构函数。否则只会使用free方法回收。

tolua_register_gc方法，做的事情，是以对象指针为键，以对象metatable为值，将键值对存储在tolua_gc表里。在对象类型的metatable表的__gc方法里，tolua++会检查tolua_gc表是否包含以这个地址为键的表项。包含的话才会进行上述的内存回收工作。

#####  4.其它

有的时候，在lua里取得一个c++对象后，我们想赋给它一些只在lua环境下有意义的属性。或者，我们想在lua里扩展一个c++类。tolua++也提供了实现这种需求的机制。

tolua++在LUA_REGISTRY里维护了一张tolua_peers表。这张表以表示c++对象的userdata为键，以一张表格t为值。t里面就记录了这个对象在lua里扩展的属性。