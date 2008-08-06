/*
 * Actor.h
 *
 *  Created on: 19-jul-2008
 *      Author: Administrador
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include "ScriptedStateMachine.h"

#include "BaseGameEntity.h"
/*!
 * @class Actor
 * @brief Definicion de un Actor
 *
 * Definicion de una entidad de tipo Actor
 * para ser usada en el juego.
 *
 */
class Actor: public BaseGameEntity {

public:
	/*!
	 * @brief Creacion Actor.
	 *
	 * Constructor de Actor, el parametro indica el numero unico
	 * de esta entidad.
	 *
	 * @param id Numero de identificacion unico del Actor.
	 *
	 * @return
	 */
	Actor(int id);
	/*!
	 *
	 * @return
	 */
	virtual ~Actor();
	/*!
	 * @brief Actualizacion del Actor
	 *
	 * Actualizacion del estado del Actor, llamada una vez
	 * cada ciclo del juego.
	 *
	 */
	void Update();
	/*!
	 *
	 * @param msg
	 * @return
	 */
	bool  HandleMessage(const Telegram& msg);
	/*!
	 * @brief Obtener el puntero a la maquina de estados.
	 * @return
	 */
	ScriptedStateMachine<Actor>* GetFSM()const{return m_pStateMachine;}

private:
	/*!
	 * @brief puntero a Maquina de estados.
	 */
	ScriptedStateMachine<Actor>* m_pStateMachine;

	Actor( const Actor& actor );
	Actor& operator=( const Actor& actor );
};

#endif /* ACTOR_H_ */
