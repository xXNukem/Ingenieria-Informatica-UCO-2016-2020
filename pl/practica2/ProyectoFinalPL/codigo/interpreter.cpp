/*!
  \file interpreter.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: Práctica final
 \author
 \date     2019 - 5 - 29
 \version  1.0
*/




#include <stdio.h>
#include <string>
#include <string.h>
//

/////////////////////////////
#include "ast/ast.hpp"
////////////////////////////////////////

#include "./parser/interpreter.tab.h"

int lineNumber = 1; //!< Line counter


bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

int control = 0;


extern FILE * yyin; //!< Standard input device for yylex()
std::string progname; //!<  Program name
//


//////////////////////////////////////////////


// Use for recovery of runtime errors
#include <setjmp.h>
#include <signal.h>

// Error recovery functions
#include "error/error.hpp"


lp::AST * root; //!< Root of the abstract syntax tree AST
/////////////////////////////////////////////

//////////////////////////////////////////////
// NEW in example 10

#include "table/init.hpp"


/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors

//////////////////////////////////////////////
// NEW in example 7

#include "table/table.hpp"

lp::Table table; //!< Table of Symbols



// cout.precision
#include <iostream>
//////////////////////////////////////////////////

//! \name Main program

/* !
 @brief      Main function

 @param      argc  number of command line parameters
 @param      argv  values of command line parameters

 @return     int
 @note       C++ requires that main returns an int value
 @see        yyparse, yylex
*/
int main ( int argc, char * argv[] )
{
// Option -t needed
// yydebug = 1;

  /*
    If the input file exists
       then
            it is set as input device for yylex();
       otherwise
             the input device is the keyboard (stdin)
  */
  if ( argc == 2 )
  {
    yyin = fopen ( argv[1], "r" );
    if ( FILE * file = fopen ( argv[1], "r" ) )
    {
      fclose ( file );
      std::string * filename = new std::string ( argv[1] );
      std::size_t found = filename->find_last_of ( "." );
      std::string extension = filename->substr ( found + 1, filename->length() );
      if ( extension != "e" )
      {
        warning ( "Error en el fichero: ", "Extension no valida" );
        return 0;
      }


    }
    else
    {
      warning ( "Error en el fichero: ", "El fichero no existe" );
      return 0;
    }
    interactiveMode = false;
  }
  else
  {
    interactiveMode = true;
  }

// Copy the name of the interpreter
  progname = argv[0];

  /* Number of decimal places */
  std::cout.precision ( 7 );

  /*
    Table of symbols initialization
    Must be written before the recovery sentence: setjmp
  */
  init ( table );

  /* Sets a viable state to continue after a runtime error */
  setjmp ( begin );

  /* The name of the function to handle floating-point errors is set */
  signal ( SIGFPE, fpecatch );

// Parser function
  yyparse();

  if ( interactiveMode == false )
  {
    
    /*root->print();*/
    root->evaluate();
  }

  /* End of program */
  return 0;
}



