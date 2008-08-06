/*
 * LuaHelpFunctions.h
 *
 *  Created on: 04-ago-2008
 *      Author: 79481180
 */

#ifndef LUAHELPFUNCTIONS_H_
#define LUAHELPFUNCTIONS_H_
/*!
 * @brief Ejecutar un fichero de lua.
 *
 * Ejecuta un fichero script de lua, en el caso de detectar un error
 * throw un luabind::error.
 *
 * @param L
 * @param script_name
 */
void RunLuaDoFile(lua_State* L, const char* script_name);
/*!
 * @brief Añadir datos de linea y fichero error Lua
 *
 * Genera un mensaje de error ampliado con los datos del fichero y
 * la linea donde se ha producido. Lo introduce en el stack de Lua para
 * su utilización en el mensaje de error. Si esta anidado no funciona bien
 * por ello el escribir el error en la salida de error estandard.
 *
 * @param L Estado lua
 * @return Numero de parametros dejados en el stack.
 */
int add_file_and_line(lua_State* L );

#endif /* LUAHELPFUNCTIONS_H_ */
