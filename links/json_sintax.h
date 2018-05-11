/*
 * json_sintax.h
 *
 *  Created on: 30 марта 2017 г.
 *      Author: walery
 */

#ifndef JSON_SINTAX_H_
#define JSON_SINTAX_H_

#ifdef __cplusplus
extern "C"
{
#endif

extern const char* startobj;			// = "{";
extern const char* endobj;				// = "}";
extern const char* colon;				// = ":";
extern const char* comma;				// = ",";
extern const char* dot;				//	= ".";
extern const char* escape1;			// =  "\"";
extern const char* templ_root_array;	// = "[]";
extern const char* templ_true;			// = "true";
extern const char* templ_false;		// = "false";

#ifdef __cplusplus
}
#endif

#endif /* JSON_SINTAX_H_ */
