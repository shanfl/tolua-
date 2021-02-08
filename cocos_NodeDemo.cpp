TOLUA_API int register_all_cocos2dx(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_Ref(tolua_S);
	lua_register_cocos2dx_Material(tolua_S);
	lua_register_cocos2dx_Console(tolua_S);
	lua_register_cocos2dx_Node(tolua_S);
	lua_register_cocos2dx_Scene(tolua_S);
	
	....

	tolua_endmodule(tolua_S);
	return 1;
}

int lua_register_cocos2dx_Ref(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Ref");
    tolua_cclass(tolua_S,"Ref","cc.Ref","",nullptr);

    tolua_beginmodule(tolua_S,"Ref");
        tolua_function(tolua_S,"release",lua_cocos2dx_Ref_release);
        tolua_function(tolua_S,"retain",lua_cocos2dx_Ref_retain);
        tolua_function(tolua_S,"getReferenceCount",lua_cocos2dx_Ref_getReferenceCount);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Ref).name();
    g_luaType[typeName] = "cc.Ref";
    g_typeCast["Ref"] = "cc.Ref";
    return 1;
}



int lua_register_cocos2dx_Node(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Node");
    tolua_cclass(tolua_S,"Node","cc.Node","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Node");
        tolua_function(tolua_S,"new",lua_cocos2dx_Node_constructor);
        tolua_function(tolua_S,"addChild",lua_cocos2dx_Node_addChild);
        tolua_function(tolua_S,"removeComponent",lua_cocos2dx_Node_removeComponent);
        tolua_function(tolua_S,"setPhysicsBody",lua_cocos2dx_Node_setPhysicsBody);
        tolua_function(tolua_S,"getOnExitTransitionDidStartCallback",lua_cocos2dx_Node_getOnExitTransitionDidStartCallback);
        tolua_function(tolua_S,"getDescription",lua_cocos2dx_Node_getDescription);
        tolua_function(tolua_S,"setRotationSkewY",lua_cocos2dx_Node_setRotationSkewY);
        tolua_function(tolua_S,"setOpacityModifyRGB",lua_cocos2dx_Node_setOpacityModifyRGB);
        tolua_function(tolua_S,"setCascadeOpacityEnabled",lua_cocos2dx_Node_setCascadeOpacityEnabled);
        tolua_function(tolua_S,"getChildren",lua_cocos2dx_Node_getChildren);
        tolua_function(tolua_S,"setOnExitCallback",lua_cocos2dx_Node_setOnExitCallback);
        tolua_function(tolua_S,"setActionManager",lua_cocos2dx_Node_setActionManager);
        tolua_function(tolua_S,"convertToWorldSpaceAR",lua_cocos2dx_Node_convertToWorldSpaceAR);
        tolua_function(tolua_S,"isIgnoreAnchorPointForPosition",lua_cocos2dx_Node_isIgnoreAnchorPointForPosition);
		...
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Node).name();
    g_luaType[typeName] = "cc.Node";
    g_typeCast["Node"] = "cc.Node";
    return 1;
}