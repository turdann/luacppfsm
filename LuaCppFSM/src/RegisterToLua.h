/*
 * RegisterToLua.h
 *
 *  Created on: 04-ago-2008
 *      Author: 79481180
 */

#ifndef REGISTERTOLUA_H_
#define REGISTERTOLUA_H_

#include <luabind/luabind.hpp>
using namespace luabind;

enum {
	ent_Miner_Bob = 1, ent_Elsa = 2
};
void RegisterToLuaTelegram(lua_State* Lua);
void RegisterToLuaMessageDispacher(lua_State* Lua);
void RegisterToLuaCrudeTimer(lua_State* Lua);
void RegisterToLuaBaseGameEntity(lua_State* Lua);
void RegisterToLuaActor(lua_State* Lua);
void RegisterToLuaScriptedStateMachine(lua_State* Lua);
void RegisterToLuaGlobals(lua_State* Lua);

#endif /* REGISTERTOLUA_H_ */
