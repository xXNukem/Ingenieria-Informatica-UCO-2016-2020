/*! 
  \file error.hpp
  \brief Prototypes of error recovery functions 
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

/*! 
	\brief  Show the error messages
	\return void
	\param  errorMessage1: first error message
	\param  errorMessage2: second error message
	\sa     yyerror
*/
void warning(std::string errorMessage1,std::string errorMessage2);

/*! 
	\brief  Parser error recovery function
	\return void
	\param  errorMessage: Parser error message
	\sa     warning
*/
void yyerror(std::string errorMessage);

#endif  // _ERROR_HPP_
