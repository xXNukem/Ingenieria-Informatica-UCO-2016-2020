/*!	
	\file    init.cpp
	\brief   Code of the function for the initialization of table of symbols
	\author  
	\date    2017-12-20
	\version 1.0
*/

#include "init.hpp"

#include "table.hpp"

//  NEW in example 11 
#include "numericConstant.hpp"

//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"


//////////////////////////////////////////////////////////////////////////////////


void init(lp::Table &t)
{
 int i;

 //  MODIFIED in example 11 
 lp::NumericConstant *n;

 // The predefined numeric constants are installed in the table of symbols
 for (i=0; numericConstant[i].name.compare("")!=0; i++)
	{
		// The predefined numeric constant is inserted into the symbol table

		 n = new lp::NumericConstant(numericConstant[i].name,
									 CONSTANT,	// MODIFIED in example 11 
									 NUMBER, 	// MODIFIED in example 11 
									 numericConstant[i].value);

		// A pointer to the new NumericConstant is inserted into the table of symbols
		t.installSymbol(n);
	}
}


