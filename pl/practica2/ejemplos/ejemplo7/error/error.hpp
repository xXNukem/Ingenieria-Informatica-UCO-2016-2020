/*! 
  \file error.hpp
  \brief Prototypes of error recovery functions 
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

/*! 
	\brief  Parser error recovery function
	\return void
	\param  errorMessage: Parser error message
	\sa     warning
*/
void yyerror(std::string errorMessage);

/*! 
	\brief  Show the error messages
	\return void
	\param  errorMessage1: first error message
	\param  errorMessage2: second error message
	\sa     yyerror, execerror
*/
void warning(std::string errorMessage1,std::string errorMessage2);


/***************************************************************/
/* NEW in example 6 */

/*! 
	\brief  Run time error recovery function
	\return void
	\param  errorMessage1: first error message
	\param  errorMessage2: second error message
	\sa     warning, longjmp
*/
void execerror(std::string errorMessage1,std::string errorMessage2);


/*! 
	\brief  Run time error recovery function
	\return void
	\param  signum  error type 
	\sa     warning
*/
void fpecatch(int signum);

/***************************************************************/

#endif 
