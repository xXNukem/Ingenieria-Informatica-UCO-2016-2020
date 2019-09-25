/*! 
  \file interpreter.cpp
  \brief Main program
*/
 
/*!
 \mainpage Flex and Bison: example 1
 \author   
 \date     2018 - 12 - 11
 \version  2.0
 \note 
    + Arithmetic expressions composed of numbers are analyzed
		- Addition, subtraction, multiplication and division
		- Expressions whith parentheses are allowed
		- Expressions must finish with an end of line: "\n"
    	- The unary "+" or "-" are not allowed
    + Use of the interpreter
      - interactive: ./interpreter.exe 
         \n The program ends by pressing Control + D 
         \n or typing # at the beginning of line
      - Redirecting an input file: ./interpreter.exe < test.txt	
         \n The program ends when the end-of-file character is read 
         \n or when the # character is read at the beginning of line
 \attention
     + A message is shown when a parsing error is detected
*/


#include "./parser/interpreter.tab.h"

int lineNumber = 1; //!< Line counter

/*! 
	\brief  Main function
	\return int
	\note   C++ requires that main returns an int value
	\sa     yyparse(), yylex()
*/

int main()
{
	/* Option -t needed to debug */
	/* yydebug = 1; */
 
  	/* Parser function */
	yyparse();

	/* End of program */
	return 0;
}

