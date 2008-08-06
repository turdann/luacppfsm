/*
 * Actor.cpp
 *
 * Created on: 19-jul-2008
 * @Author: Rafael Ugalde
 */
#include <iostream>
#include <luabind/luabind.hpp>
using namespace luabind;

#include "Actor.h"

Actor::Actor(int id) :
	BaseGameEntity(id) {

	std::cout << "[C++Actor] constructor" << std::endl;
	m_pStateMachine = new ScriptedStateMachine<Actor> (this);
}
void Actor::Update() {
	std::cout << "[C++Actor] Update---------------------------------------"
			<< std::endl;
	m_pStateMachine->Update();
}
bool Actor::HandleMessage(const Telegram& msg) {

	return m_pStateMachine->HandleMessage(msg);
}

Actor::~Actor() {

	std::cout << "[C++Actor] destructor" << std::endl;
	delete m_pStateMachine;

}
