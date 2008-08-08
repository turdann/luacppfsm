/*!
 * main.cpp
 *
 *  Created on: 19-jul-2008
 *      Author: Administrador
 */

#ifdef WIN32
	#include <windows.h>
	#define SLEEP(n) Sleep(n)
#else
	#include <unistd.h>
	#define SLEEP(n) usleep(n * 1000)
#endif

#include <vector>
using namespace std;

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>
using namespace luabind;

#include "LuaHelpFunctions.h"
#include "EntityManager.h"
#include "Actor.h"
#include "Actor_wrapper.h"
#include "MessageDispatcher.h"
#include "CrudeTimer.h"
#include "RegisterToLua.h"

/*!
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

	vector<Actor*> Actores;

	srand(time(NULL));
	lua_State *Lua = lua_open();
	luaL_openlibs(Lua);

	open(Lua);// Connect LuaBind to this lua state

	RegisterToLuaTelegram(Lua);
	RegisterToLuaMessageDispacher(Lua);
	RegisterToLuaCrudeTimer(Lua);
	RegisterToLuaBaseGameEntity(Lua);
	RegisterToLuaActor(Lua);
	RegisterToLuaScriptedStateMachine(Lua);
	globals(Lua)["ent_Miner_Bob"] = (int)ent_Miner_Bob;
	globals(Lua)["ent_Elsa"] = (int)ent_Elsa;

	set_pcall_callback(&add_file_and_line);
	try {

		RunLuaDoFile(Lua,"./scripts/Init.lua");
		RunLuaDoFile(Lua,"./scripts/Miner.lua");
		RunLuaDoFile(Lua,"./scripts/Wife.lua");

		Actor* elMiner;
		elMiner = call_function<Actor*>(Lua, "Miner", (int)ent_Miner_Bob)[adopt(result)];
		EntityMgr->RegisterEntity(elMiner);
		Actores.push_back(elMiner);

		Actor* laWife;
		laWife = call_function<Actor*>(Lua, "Wife", (int)ent_Elsa)[adopt(result)];
		EntityMgr->RegisterEntity(laWife);
		Actores.push_back(laWife);

		for (int i = 0; i < 30; i++) {
			for (vector<Actor*>::iterator j = Actores.begin(); j < Actores.end(); j++) {
				(*j)->Update();
				Dispatch->DispatchDelayedMessages();
				SLEEP(800);
			}
		}
		for (vector<Actor*>::iterator j = Actores.begin(); j < Actores.end(); j++) {
			delete (*j);
		}
		Actores.erase(Actores.begin(), Actores.end());
		cout << "Dimensiones vector =" << Actores.size() << endl;
		lua_close(Lua);
	}
	catch (error e) {
		object error_msg(from_stack(e.state(),-1));
		cout << error_msg << " " << e.what() << endl;
		return 1;
	}
	catch (cast_failed e){
		object error_msg(from_stack(e.state(),-1));
		cout << error_msg << " " << e.what() << endl;
		return 1;
	}
	catch (exception e){
		cout << "Throw error: " << e.what() << endl;
		return 1;
	}
	return 0;
}
