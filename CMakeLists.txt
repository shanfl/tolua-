# Copyright (C) 2007-2012 LuaDist.
# Created by Peter Kapec
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.

project ( toluapp C )
cmake_minimum_required ( VERSION 2.8 )
include ( cmake/dist.cmake )

SET(LUA_SRC 

  ./lua-5.1.5/src/lapi.c     
  ./lua-5.1.5/src/lapi.h     
  ./lua-5.1.5/src/lauxlib.c  
  ./lua-5.1.5/src/lauxlib.h  
  ./lua-5.1.5/src/lbaselib.c 
  ./lua-5.1.5/src/lcode.c    
  ./lua-5.1.5/src/lcode.h    
  ./lua-5.1.5/src/ldblib.c   
  ./lua-5.1.5/src/ldebug.c   
  ./lua-5.1.5/src/ldebug.h   
  ./lua-5.1.5/src/ldo.c      
  ./lua-5.1.5/src/ldo.h      
  ./lua-5.1.5/src/ldump.c    
  ./lua-5.1.5/src/lfunc.c    
  ./lua-5.1.5/src/lfunc.h    
  ./lua-5.1.5/src/lgc.c      
  ./lua-5.1.5/src/lgc.h      
  ./lua-5.1.5/src/linit.c    
  ./lua-5.1.5/src/liolib.c   
  ./lua-5.1.5/src/llex.c     
  ./lua-5.1.5/src/llex.h     
  ./lua-5.1.5/src/llimits.h  
  ./lua-5.1.5/src/lmathlib.c 
  ./lua-5.1.5/src/lmem.c     
  ./lua-5.1.5/src/lmem.h     
  ./lua-5.1.5/src/loadlib.c  
  ./lua-5.1.5/src/lobject.c  
  ./lua-5.1.5/src/lobject.h  
  ./lua-5.1.5/src/lopcodes.c 
  ./lua-5.1.5/src/lopcodes.h 
  ./lua-5.1.5/src/loslib.c   
  ./lua-5.1.5/src/lparser.c  
  ./lua-5.1.5/src/lparser.h  
  ./lua-5.1.5/src/lstate.c   
  ./lua-5.1.5/src/lstate.h   
  ./lua-5.1.5/src/lstring.c  
  ./lua-5.1.5/src/lstring.h  
  ./lua-5.1.5/src/lstrlib.c  
  ./lua-5.1.5/src/ltable.c   
  ./lua-5.1.5/src/ltable.h   
  ./lua-5.1.5/src/ltablib.c  
  ./lua-5.1.5/src/ltm.c      
  ./lua-5.1.5/src/ltm.h
  ./lua-5.1.5/src/lua.h
  ./lua-5.1.5/src/luaconf.h  
  ./lua-5.1.5/src/lualib.h   
  ./lua-5.1.5/src/lundump.c  
  ./lua-5.1.5/src/lundump.h  
  ./lua-5.1.5/src/lvm.c      
  ./lua-5.1.5/src/lvm.h      
  ./lua-5.1.5/src/lzio.c     
  ./lua-5.1.5/src/lzio.h     
  ./lua-5.1.5/src/Makefile   
  ./lua-5.1.5/src/print.c    

)
include_directories ( include src/lib ${LUA_INCLUDE_DIR} lua-5.1.5/src/)

# Build lib
file ( GLOB SRC_LIBTOLUAPP src/lib/*.c )
if ( MSVC )
  set ( DEF_FILE libtoluapp.def )
endif ( )

add_library ( toluapp_lib STATIC ${SRC_LIBTOLUAPP} ${DEF_FILE} ${LUA_SRC})
target_link_libraries ( toluapp_lib ${LUA_LIBRARIES} )
set_target_properties ( toluapp_lib PROPERTIES OUTPUT_NAME toluapp CLEAN_DIRECT_OUTPUT 
  1 )

# Build app
include_directories ( src/bin )
set ( SRC_TOLUA src/bin/tolua.c src/bin/toluabind.c )
add_executable ( toluapp ${SRC_TOLUA} )
target_link_libraries ( toluapp toluapp_lib ${LUA_LIBRARIES} )


ADD_EXECUTABLE(array   
src/tests/tarray.h  
src/tests/tarray.c 
src/tests/tarraybind.c
)
target_link_libraries ( array toluapp_lib)

# Install
install_library ( toluapp_lib )
install_executable ( toluapp )
install_header ( include/ )
install_data ( README INSTALL )
install_doc ( doc/ )
