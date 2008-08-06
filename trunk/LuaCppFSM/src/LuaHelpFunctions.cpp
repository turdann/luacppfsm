/*
 * LuaHelpFunctions.cpp
 *
 *  Created on: 04-ago-2008
 *      Author: 79481180
 */
#include <sstream>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include "LuaHelpFunctions.h"
void RunLuaDoFile(lua_State* L, const char* script_name) {

	if (luaL_dofile(L, script_name) != 0) {

		throw(luabind::error(L));

	}

}
int add_file_and_line(lua_State* L) {

	lua_Debug d;
	lua_getstack(L, 1, &d);
	lua_getinfo(L, "Sln", &d);
	std::string err = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::stringstream msg;
	msg << "\n" << d.short_src << ":" << d.currentline;

	if (d.name != 0) {
		msg << "(" << d.namewhat << " " << d.name << ")";
	}
	msg << " " << err;
	lua_pushstring(L, msg.str().c_str());
	fprintf(stderr,msg.str().c_str());
	return 1;

}
