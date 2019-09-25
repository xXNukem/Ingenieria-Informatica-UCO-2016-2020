/*! 
  \file interpreter.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: example 2
 \author   
 \date     2018 - 4 - 26
 \version  1.0
 \note Novelties
    + The program name is displayed in the error messages
    + Use of the interpreter
     - interactive: ./interpreter.exe  
      \n The program ends by pressing Control + D
      \n or typing # at the beginning of line
     - Loading an input file: ./interpreter.exe test.txt 
       \n The program ends when reading the end-of-file character
*/

// New in example 2
#include <stdio.h>
#include <string>
//

#include "./parser/interpreter.tab.h"

int lineNumber = 1; //!< Line counter

// New in example 2
extern FILE * yyin; //!< Standard input device for yylex() 
std::string progname; //!<  Program name
//

//! \name Main program

/*! 
	\brief  Main function
	\param  argc: number of command line parameters
	\param  argv: values of command line parameters
	\return int
	\note   C++ requires that main returns an int value
	\sa     yyparse, yylex
*/
int main(int argc, char *argv[]) /* MODIFIED in example 2 */
{
	/* Option -t needed to debug */
	/* yydebug = 1; */
 
	/*****************************************/
	/* NEW in example 2 */
	/* 
		If the input file exists 
	      then 
    	       it is set as input device for yylex();
		otherwise
            the input device is the keyboard (stdin)
	*/
	if (argc == 2) 
    	 yyin = fopen(argv[1],"r");

	/* Copy the name of the interpreter */
	progname = argv[0];
	/*****************************************/

	/* Parser function */
	yyparse();

	/* End of program */
	return 0;
}

