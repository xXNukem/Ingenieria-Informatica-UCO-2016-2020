/*! 
  \file error.cpp
  \brief Code of error recovery functions 
*/

// cerr, endl
#include <iostream>

#include <string>

#include "error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

extern int lineNumber; //!< // External line counter

/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  External program name
/***********************************************************/

void warning(std::string errorMessage1,std::string errorMessage2)
{
  /**************************************************/
  /* NEW in example 2 */
  std::cerr << IGREEN; 
  std::cerr << " Program: " << progname << std::endl; 
  /**************************************************/

  std::cerr << BIRED; 
  std::cerr << " Error line " << lineNumber 
            << " --> " << errorMessage1 << std::endl;
  std::cerr << RESET; 

  if (errorMessage2.compare("")!=0)
		 std::cerr << "\t" << errorMessage2 << std::endl;
}

void yyerror(std::string errorMessage)
{
	warning("Parsing error",errorMessage);
}
