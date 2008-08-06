/*
 * Actor_wrapper.h
 *
 *  Created on: 20-jul-2008
 *      Author: Administrador
 */

#ifndef ACTOR_WRAPPER_H_
#define ACTOR_WRAPPER_H_
/*!
 * @brief  Wrapper de la class Actor
 *
 * Utilizada para definir la clase en Lua y acceder a sus metodos
 * desde C++ y desde Lua a los metodos de C++
 *
 */
struct Actor_wrapper:  Actor, wrap_base{
	/*!
	 *
	 * @param id
	 * @return
	 */
	Actor_wrapper(int id):Actor(id){
		std::cout << "[C++Actor_wrapper] constructor" << std::endl;
	}
	/*!
	 *
	 * @return
	 */
	virtual ~Actor_wrapper(){
		std::cout << "[C++Actor_wrapper] destructor" << std::endl;
	}
};

#endif /* ACTOR_WRAPPER_H_ */
