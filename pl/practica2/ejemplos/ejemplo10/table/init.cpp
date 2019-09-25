/*!	
	\file    init.cpp
	\brief   Code of the function for the initialization of table of symbols
	\author  
	\date    2017-12-5
	\version 1.0
*/

#include "init.hpp"

#include "table.hpp"

#include "numericVariable.hpp"

//  y.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"


//////////////////////////////////////////////////////////////////////////////////


void init(lp::Table &t)
{
 int i;

 lp::NumericVariable *n;

 // The predefined numeric constants are installed in the table of symbols
 for (i=0; numericConstant[i].name.compare("")!=0; i++)
	{
		// The  Predefined numeric constant is inserted into the symbol table

		 n = new lp::NumericVariable(numericConstant[i].name,
									 VARIABLE,
									 NUMBER,
									 numericConstant[i].value);

		// A pointer to the new NumericVariable is inserted into the table of symbols
		t.installSymbol(n);
	}
}


