/*!	
	\file   init.hpp
	\brief   Prototype of the function for the initialization of table of symbols
	\author  
	\date    2017-12-20
	\version 1.0
*/

#ifndef _INIT_HPP_
#define _INIT_HPP_

#include "table.hpp"

//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"

/*!
  \ brief Predefined numeric constants
*/
static struct {
          std::string name ;
	      double value;
	      } numericConstant[] = {
	                    "PI",    3.14159265358979323846,
	                    "E",     2.71828182845904523536,
	                    "GAMMA", 0.57721566490153286060,
	                    "DEG",  57.29577951308232087680,
	                    "PHI",   1.61803398874989484820,
	                    "",      0
	                   };


// NEW in example 12 
/*!
  \ brief Predefined keywords
*/
static struct {
          std::string name ;
	      int token;
	      } keyword[] = {
	                    "print", PRINT,
	                    "read",  READ,
	                    "",      0
	                   };



/*!		
	\brief   Initialize the table of symbols
	\return  void 
*/

void init(lp::Table &t);

// End of _INIT_HPP_
#endif
