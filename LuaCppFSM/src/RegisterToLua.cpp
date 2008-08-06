/*
 * RegisterToLua.cpp
 *
 *  Created on: 04-ago-2008
 *      Author: 79481180
 */
#include "RegisterToLua.h"

#include "Telegram.h"
#include "MessageDispatcher.h"
#include "CrudeTimer.h"
#include "BaseGameEntity.h"
#include "Actor.h"
#include "Actor_wrapper.h"
#include "ScriptedStateMachine.h"

void RegisterToLuaTelegram(lua_State* Lua){
	module( Lua)
	[
		 class_<Telegram> ("Telegram")
	     .def_readwrite("Msg",&Telegram::Msg)
	     .def_readwrite("ExtraInfo", &Telegram::ExtraInfo)
	];
}
void RegisterToLuaMessageDispacher(lua_State* Lua){
	module(Lua)
	[
		 class_<MessageDispatcher> ("Dispatch")
	 	.def("DispatchMsg",&MessageDispatcher::DispatchMsg)
	];
	globals( Lua)["Dispatch"] = Dispatch; // Es una class singleton
}
void RegisterToLuaCrudeTimer(lua_State* Lua){
	module(Lua)
	[
		 class_<CrudeTimer> ("Clock")
		 .def("GetCurrentTime",&CrudeTimer::GetCurrentTime)
	];
	globals( Lua)["Clock"] = Clock; // Es una class singleton
}
void RegisterToLuaBaseGameEntity(lua_State* Lua){
	module(Lua)
	[
		 class_<BaseGameEntity> ("BaseGameEntity")
		 .def("ID",&BaseGameEntity::ID)];
}
void RegisterToLuaActor(lua_State* Lua){
	module(Lua)
	[
		 class_<Actor, bases<BaseGameEntity> , Actor_wrapper> ("Actor")
		 .def(constructor<int> ())
		 .def("GetFSM",&Actor::GetFSM)
	];
}
void RegisterToLuaScriptedStateMachine(lua_State* Lua){
	module( Lua)
	[class_<ScriptedStateMachine<Actor> > ("ScriptedStateMachine")
		 .def("ChangeState", &ScriptedStateMachine<Actor>::ChangeState)
		 .def("CurrentState", &ScriptedStateMachine<Actor>::CurrentState)
		 .def("PreviousState", &ScriptedStateMachine<Actor>::PreviousState)
		 .def("GlobasState", &ScriptedStateMachine<Actor>::GlobalState)
		 .def("SetCurrentState",&ScriptedStateMachine<Actor>::SetCurrentState)
		 .def("SetGlobalState",&ScriptedStateMachine<Actor>::SetGlobalState)
		 .def("RevertToPreviousState",&ScriptedStateMachine<Actor>::RevertToPreviousState)
		 .def("isInState",&ScriptedStateMachine<Actor>::isInState)
	];
}
void RegisterToLuaGlobals(lua_State* Lua){
	globals(Lua)["ent_Miner_Bob"] = (int)ent_Miner_Bob;
	globals(Lua)["ent_Elsa"] = (int)ent_Elsa;
}
