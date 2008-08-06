#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------------------------------------------
//
//  Name:   BaseGameEntity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>

#include "Telegram.h"
/*!
 * @brief Definicion de la clase base para las entidades del juego.
 *
 * Todo tipo de entidades diferentes dentro del juego se derivan
 * desde esta clase. Actor, .....
 *
 */
class BaseGameEntity {

public:
	/*!
	 * @brief Creacion entidad base del juego.
	 * @param id Identificador unico de entidad.
	 * @return
	 */
	BaseGameEntity(int id) {
		SetID(id);
	}
	/*!
	 *
	 * @return
	 */
	virtual ~BaseGameEntity() {
	}
	/*!
	 *  Todas las entidades han de implementar una funcion Update.
	 */
	virtual void Update()=0;
	/*!
	 * @brief Manejo de los mensajes.
	 *
	 * Todas las entidades se pueden comunicar usando mensajaes. Se envian mediante la
	 * clase MenssageDispatch singleton.
	 *
	 * @param msg Mensaje a tratar.
	 * @return
	 */
	virtual bool HandleMessage(const Telegram& msg)=0;
	/*!
	 * @brief Obtencion del identificador de la entidad.
	 *
	 * @return
	 */
	int ID() const {
		return m_ID;
	}

private:
	/*!
	 * @brief Numero de identificacion de la unidad.
	 *
	 * Cada entidad ha de tener una identificacion unica.
	 */
	int m_ID;
	/*!
	 *
	 * this is the next valid ID. Each time a BaseGameEntity is instantiated
	 * this value is updated
	 */
	static int m_iNextValidID;
	/*!
	 * Se llamara a este metodo dentro del constructor para asegurarse que el ID
	 * es correcto. Verifica que el valor pasado al metodo es mayor o igual
	 * al siguiente ID valido, antes de poner el ID e incrementar el siguiente
	 * ID valido.
	 *
	 * @param val
	 */
	void SetID(int val);

};

#endif

