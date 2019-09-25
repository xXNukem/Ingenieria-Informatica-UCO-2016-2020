/*!
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

//
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/stringVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST * root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType()
{
	// Get the identifier in the table of symbols as Variable
	lp::Variable * var = ( lp::Variable * ) table.getSymbol ( this->_id );

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::print()
{
	std::cout << "VariableNode: " << this->_id << std::endl;
	std::cout << "Type: " << this->getType() << std::endl;
}


double lp::VariableNode::evaluateNumber()
{
	double result = 0.0;

	if ( this->getType() == NUMBER )
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable * var = ( lp::NumericVariable * ) table.getSymbol ( this->_id );

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning ( "Error de ejecución en evaluateNumber(): la variable no es numérica",
		          this->_id );
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable * var = ( lp::LogicalVariable * ) table.getSymbol ( this->_id );

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning ( "Error de ejecución in evaluateBool(): la variable no es booleana",
		          this->_id );
	}

	// Return the value of the LogicalVariable
	return result;
}

std::string lp::VariableNode::evaluateString()
{
	std::string result = "";

	if ( this->getType() == STRING )
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::StringVariable * var = ( lp::StringVariable * ) table.getSymbol ( this->_id );

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning ( "Error de ejecución in evaluateBool(): la variable no es booleana",
		          this->_id );
	}

	// Return the value of the LogicalVariable
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::print()
{
	std::cout << "ConstantNode: " << this->_id << std::endl;
	std::cout << "Type: " << this->getType() << std::endl;
}

int lp::ConstantNode::getType()
{
	// Get the identifier in the table of symbols as Constant
	lp::Constant * var = ( lp::Constant * ) table.getSymbol ( this->_id );

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber()
{
	double result = 0.0;

	if ( this->getType() == NUMBER )
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant * constant = ( lp::NumericConstant * ) table.getSymbol ( this->_id );

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning ( "Error de ejecución in evaluateNumber(): la constante no es numérica",
		          this->_id );
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant * constant = ( lp::LogicalConstant * ) table.getSymbol ( this->_id );

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning ( "Error de ejecución in evaluateBool(): la constante no es booleana",
		          this->_id );
	}

	// Return the value of the LogicalVariable
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::print()
{
	std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber()
{
	return this->_number;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::StringNode::getType()
{
	return STRING;
}


void lp::StringNode::print()
{
	std::cout << "StringNode: " << * ( this->_string ) << std::endl;
}

std::string lp::StringNode::evaluateString()
{
	return * ( this->_string );
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if ( this->_exp->getType() == NUMBER )
	{
		result = NUMBER;
	}
	else
	{
		warning ( "Error de ejecución: tipo incompatible para", "Numeric Unary Operator" );
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if ( this->_exp->getType() == BOOL )
	{
		result = BOOL;
	}
	else
	{
		warning ( "Error de ejecución: tipo incompatible para", "Logical Unary Operator" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;

	if ( ( this->_left->getType() == NUMBER ) and ( this->_right->getType() == NUMBER ) )
		result = NUMBER;
	else
		warning ( "Error de ejecución: tipo incompatible para", "Numeric Operator" );

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::StringOperatorNode::getType()
{
	int result = 0;

	if ( ( this->_left->getType() == STRING ) and ( this->_right->getType() == STRING ) )
		result = STRING;
	else
		warning ( "Error de ejecución: tipo incompatible para", "String Operator" );

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;

	if ( ( this->_left->getType() == NUMBER ) and ( this->_right->getType() == NUMBER ) )
		result = BOOL;
	else if ( ( this->_left->getType() == STRING ) and ( this->_right->getType() == STRING ) )
		result = BOOL;
	else
		warning ( "Error de ejecución: tipo incompatible para", "Relational Operator" );

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;

	if ( ( this->_left->getType() == BOOL ) and ( this->_right->getType() == BOOL ) )
	{
		//
		result = BOOL;
	}
	else
		warning ( "Error de ejecución: tipo incompatible para", "Logical Operator" );

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryAddNode::print()
{
	std::cout << "UnaryAddNode: "  << std::endl;
	std::cout << identifier << std::endl;
}

double lp::UnaryAddNode::evaluateNumber()
{
	double result = 0;
	// Ckeck the type of the expression
	if ( this->getType() == NUMBER )
	{
		lp::NumericVariable * v = ( lp::NumericVariable * ) table.getSymbol ( identifier );
		result = v->getValue() + 1;
		v->setValue ( result );
	}
	else
	{
		warning ( "Error de ejecución: la expresion no es numérica para ", "UnaryAddNode" );
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnarySubstractNode::print()
{
	std::cout << "UnarySubstractNode: "  << std::endl;
	std::cout << identifier << std::endl;
}

double lp::UnarySubstractNode::evaluateNumber()
{
	double result = 0;
	// Ckeck the type of the expression
	if ( this->getType() == NUMBER )
	{
		lp::NumericVariable * v = ( lp::NumericVariable * ) table.getSymbol ( identifier );
		result = v->getValue() - 1;
		v->setValue ( result );
	}
	else
	{
		warning ( "Error de ejecución: la expresion no es numérica para ", "UnaryAddNode" );
	}

	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print()
{
	std::cout << "UnaryMinusNode: "  << std::endl;
	std::cout << "-";
	this->_exp->print();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if ( this->getType() == NUMBER )
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "UnaryMinus" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print()
{
	std::cout << "UnaryPlusNode: "  << std::endl;
	this->_exp->print();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if ( this->getType() == NUMBER )
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "UnaryPlus" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print()
{
	std::cout << "PlusNode: "  << std::endl;
	this->_left->print();
	std::cout << " + ";
	this->_right->print();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Plus" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenateNode::print()
{
	std::cout << "ConcatenateNode: "  << std::endl;
	this->_left->print();
	std::cout << " || ";
	this->_right->print();
}

std::string lp::ConcatenateNode::evaluateString()
{
	std::string result = "";

	// Ckeck the types of the expressions
	if ( this->getType() == STRING )
	{
		result = this->_left->evaluateString() + this->_right->evaluateString();
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Concatenate" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print()
{
	std::cout << "MinusNode: "  << std::endl;
	this->_left->print();
	std::cout << " - ";
	this->_right->print();
}

double lp::MinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Minus" );
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print()
{
	std::cout << "MultiplicationNode: "  << std::endl;
	this->_left->print();
	std::cout << " * ";
	this->_right->print();
}

double lp::MultiplicationNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Multiplication" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
	std::cout << "DivisionNode: " << std::endl;
	this->_left->print();
	std::cout << " / ";
	this->_right->print();
}

double lp::DivisionNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
		if ( std::abs ( rightNumber ) > ERROR_BOUND )
		{
			result = leftNumber / rightNumber;
		}
		else
		{
			warning ( "Error de ejecución", "Division por cero" );
		}
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Division" );
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionIntNode::print()
{
	std::cout << "DivisionNode: " << std::endl;
	this->_left->print();
	std::cout << " / ";
	this->_right->print();
}

double lp::DivisionIntNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
		if ( std::abs ( rightNumber ) > ERROR_BOUND )
		{
			result = ( int ) leftNumber / ( int ) rightNumber;
		}
		else
		{
			warning ( "Error de ejecución", "Division por cero" );
		}
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Division" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
	std::cout << "ModuloNode: " << std::endl;
	this->_left->print();
	std::cout << " / ";
	this->_right->print();
}

double lp::ModuloNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		if ( std::abs ( rightNumber ) > ERROR_BOUND )
			result = ( int ) leftNumber % ( int ) rightNumber;
		else
			warning ( "Error de ejecución", "Division por cero" );
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Modulo" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print()
{
	std::cout << "PowerNode: "  << std::endl;
	this->_left->print();
	std::cout << " ^ ";
	this->_right->print();
}

double lp::PowerNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		result = pow ( this->_left->evaluateNumber(), this->_right->evaluateNumber() );
	}
	else
	{
		warning ( "Error de ejecución: las expresiones no son numéricas para ", "Power" );
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::print()
{
	std::cout << "BuiltinFunctionNode_0: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( ) " ;
}

double lp::BuiltinFunctionNode_0::evaluateNumber()
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 * f = ( lp::BuiltinParameter0 * ) table.getSymbol ( this->_id );

	// Apply the function and copy the result
	return f->getFunction() ();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;

	if ( this->_exp->getType() == NUMBER )
		result = NUMBER;
	else
		warning ( "Error de ejecución: tipo incompatible para", "BuiltinFunctionNode_1" );

	return	result;
}

void lp::BuiltinFunctionNode_1::print()
{
	std::cout << "BuiltinFunctionNode_1: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;
	this->_exp->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_1::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if ( this->getType() == NUMBER )
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 * f = ( lp::BuiltinParameter1 * ) table.getSymbol ( this->_id );

		// Apply the function to the parameter and copy the result
		result = f->getFunction() ( this->_exp->evaluateNumber() );
	}
	else
	{
		warning ( "Error de ejecución: tipo incompatible de parámetro para", this->_id );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;

	if ( this->_exp1->getType() == this->_exp2->getType() )
		result = this->_exp1->getType();
	else
		warning ( "Error de ejecución: tipo incompatible para", "BuiltinFunctionNode_2" );

	return	result;
}


void lp::BuiltinFunctionNode_2::print()
{
	std::cout << "BuiltinFunctionNode_2: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;
	this->_exp1->print();
	std::cout << " , " ;
	this->_exp2->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_2::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if ( this->getType() == NUMBER )
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 * f = ( lp::BuiltinParameter2 * ) table.getSymbol ( this->_id );

		// Apply the function to the parameters and copy the result
		result = f->getFunction() ( this->_exp1->evaluateNumber(), this->_exp2->evaluateNumber() );
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", this->_id );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
	std::cout << "GreaterThanNode: " << std::endl;
	this->_left->print();
	std::cout << " > ";
	this->_right->print();
}

bool lp::GreaterThanNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = ( leftNumber > rightNumber );
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Greater than" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
	std::cout << "GreaterOrEqualNode: " << std::endl;
	this->_left->print();
	std::cout << " >= ";
	this->_right->print();
}

bool lp::GreaterOrEqualNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = ( leftNumber >= rightNumber );
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Greater or equal than" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
	std::cout << "LessThanNode: " << std::endl;
	this->_left->print();
	std::cout << " < ";
	this->_right->print();
}

bool lp::LessThanNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = ( leftNumber < rightNumber );
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Less than" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
	std::cout << "LessOrEqualNode: " << std::endl;
	this->_left->print();
	std::cout << " <= ";
	this->_right->print();
}

bool lp::LessOrEqualNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = ( leftNumber <= rightNumber );
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Less or equal than" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
	std::cout << "EqualNode: " << std::endl;
	this->_left->print();
	std::cout << " == ";
	this->_right->print();
}

bool lp::EqualNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		if ( ( this->_left->getType() == NUMBER ) and ( this->_right->getType() == NUMBER ) )
		{
			double leftNumber, rightNumber;
			leftNumber = this->_left->evaluateNumber();
			rightNumber = this->_right->evaluateNumber();

			// ERROR_BOUND to control the precision of real numbers
			result = std::abs ( ( leftNumber - rightNumber ) ) < ERROR_BOUND ;
		}
		else if ( ( this->_left->getType() == STRING ) and ( this->_right->getType() == STRING ) )
		{
			std::string leftString, rightString;
			leftString = this->_left->evaluateString();
			rightString = this->_right->evaluateString();
			result = ( leftString.compare(rightString) == 0 );
		}
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Equal" );
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
	std::cout << "NotEqualNode: " << std::endl;
	this->_left->print();
	std::cout << " <> ";
	this->_right->print();
}

bool lp::NotEqualNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		if ( ( this->_left->getType() == NUMBER ) and ( this->_right->getType() == NUMBER ) )
		{
			double leftNumber, rightNumber;
			leftNumber = this->_left->evaluateNumber();
			rightNumber = this->_right->evaluateNumber();

			// ERROR_BOUND to control the precision of real numbers
			result = ( std::abs ( leftNumber - rightNumber ) >= ERROR_BOUND );
		}
		else if ( ( this->_left->getType() == STRING ) and ( this->_right->getType() == STRING ) )
		{
			std::string leftString, rightString;
			leftString = this->_left->evaluateString();
			rightString = this->_right->evaluateString();
			result = ! ( leftString == rightString );
		}

	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Not equal" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
	std::cout << "AndNode: " << std::endl;
	this->_left->print();
	std::cout << " && ";
	this->_right->print();
}

bool lp::AndNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator And" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
	std::cout << "OrNode: " << std::endl;
	this->_left->print();
	std::cout << " || ";
	this->_right->print();
}

bool lp::OrNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Or" );
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
	std::cout << "NotNode: " << std::endl;
	std::cout << " ! ";
	this->_exp->print();
}

bool lp::NotNode::evaluateBool()
{
	bool result = false;

	if ( this->getType() == BOOL )
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning ( "Error de ejecución: tipos incompatibles de parámetros para ", "operator Not" );
	}

	return result;
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print()
{
	std::cout << "assignment_node: "  << std::endl;
	std::cout << this->_id << " = ";
	this->_exp->print();
	std::cout << std::endl;
}

void lp::AssignmentStmt::evaluate()
{
	/* Get the identifier in the table of symbols as Variable */
	/*
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable * firstVar = ( lp::Variable * ) table.getSymbol ( this->_id );

	// Check the expression
	if ( this->_exp != NULL )
	{
		// Check the type of the expression of the asgn
		switch ( this->_exp->getType() )
		{
		case NUMBER:
		{
			double value;
			// evaluate the expression as NUMBER
			value = this->_exp->evaluateNumber();

			// Check the type of the first varible
			if ( firstVar->getType() == NUMBER )
			{
				// Get the identifier in the table of symbols as NumericVariable
				lp::NumericVariable * v = ( lp::NumericVariable * ) table.getSymbol ( this->_id );

				// Assignment the value to the identifier in the table of symbols
				v->setValue ( value );
			}
			// The type of variable is not NUMBER
			else
			{
				// Delete the variable from the table of symbols
				table.eraseSymbol ( this->_id );

				// Insert the variable in the table of symbols as NumericVariable
				// with the type NUMBER and the value
				lp::NumericVariable * v = new lp::NumericVariable ( this->_id,
				        VARIABLE, NUMBER, value );
				table.installSymbol ( v );
			}
		}
		break;

		case BOOL:
		{
			bool value;
			// evaluate the expression as BOOL
			value = this->_exp->evaluateBool();

			if ( firstVar->getType() == BOOL )
			{
				// Get the identifier in the table of symbols as LogicalVariable
				lp::LogicalVariable * v = ( lp::LogicalVariable * ) table.getSymbol ( this->_id );

				// Assignment the value to the identifier in the table of symbols
				v->setValue ( value );
			}
			// The type of variable is not BOOL
			else
			{
				// Delete the variable from the table of symbols
				table.eraseSymbol ( this->_id );

				// Insert the variable in the table of symbols as NumericVariable
				// with the type BOOL and the value
				lp::LogicalVariable * v = new lp::LogicalVariable ( this->_id,
				        VARIABLE, BOOL, value );
				table.installSymbol ( v );
			}
		}
		break;

		case STRING:
		{
			std::string value;
			// evaluate the expression as STRING
			value = this->_exp->evaluateString();

			if ( firstVar->getType() == STRING )
			{
				// Get the identifier in the table of symbols as StringVariable
				lp::StringVariable * v = ( lp::StringVariable * ) table.getSymbol ( this->_id );

				// Assignment the value to the identifier in the table of symbols
				v->setValue ( value );
			}
			// The type of variable is not BOOL
			else
			{
				// Delete the variable from the table of symbols
				table.eraseSymbol ( this->_id );
				// Insert the variable in the table of symbols as NumericVariable
				// with the type BOOL and the value
				lp::StringVariable * v = new lp::StringVariable ( this->_id,
				        VARIABLE, STRING, value );

				table.installSymbol ( v );
			}
		}
		break;

		default:
			warning ( "Error de ejecución: incompatible type of expression for ", "Assigment" );
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else   // this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable * secondVar = ( lp::Variable * ) table.getSymbol ( this->_asgn->_id );

		// Get the type of the variable of the previous asgn
		switch ( secondVar->getType() )
		{
		case NUMBER:
		{
			/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
			lp::NumericVariable * secondVar = ( lp::NumericVariable * ) table.getSymbol ( this->_asgn->_id );
			// Check the type of the first variable
			if ( firstVar->getType() == NUMBER )
			{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable * firstVar = ( lp::NumericVariable * ) table.getSymbol ( this->_id );
				// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

				// Assignment the value of the second variable to the first variable
				firstVar->setValue ( secondVar->getValue() );

			}
			// The type of variable is not NUMBER
			else
			{
				// Delete the first variable from the table of symbols
				table.eraseSymbol ( this->_id );

				// Insert the first variable in the table of symbols as NumericVariable
				// with the type NUMBER and the value of the previous variable
				lp::NumericVariable * firstVar = new lp::NumericVariable ( this->_id,
				        VARIABLE, NUMBER, secondVar->getValue() );
				table.installSymbol ( firstVar );
			}
		}
		break;

		case BOOL:
		{
			/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
			lp::LogicalVariable * secondVar = ( lp::LogicalVariable * ) table.getSymbol ( this->_asgn->_id );
			// Check the type of the first variable
			if ( firstVar->getType() == NUMBER )
			{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable * firstVar = ( lp::LogicalVariable * ) table.getSymbol ( this->_id );
				// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

				// Assignment the value of the second variable to the first variable
				firstVar->setValue ( secondVar->getValue() );

			}
			// The type of variable is not NUMBER
			else
			{
				// Delete the first variable from the table of symbols
				table.eraseSymbol ( this->_id );

				// Insert the first variable in the table of symbols as NumericVariable
				// with the type BOOL and the value of the previous variable
				lp::LogicalVariable * firstVar = new lp::LogicalVariable ( this->_id,
				        VARIABLE, BOOL, secondVar->getValue() );
				table.installSymbol ( firstVar );
			}
		}
		break;

		case STRING:
		{
			/* Get the identifier of the previous asgn in the table of symbols as StringVariable */
			lp::StringVariable * secondVar = ( lp::StringVariable * ) table.getSymbol ( this->_asgn->_id );
			// Check the type of the first variable
			if ( firstVar->getType() == NUMBER )
			{
				/* Get the identifier of the first variable in the table of symbols as StringVariable */
				lp::StringVariable * firstVar = ( lp::StringVariable * ) table.getSymbol ( this->_id );
				// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

				// Assignment the value of the second variable to the first variable
				firstVar->setValue ( secondVar->getValue() );

			}
			// The type of variable is not NUMBER
			else
			{
				// Delete the first variable from the table of symbols
				table.eraseSymbol ( this->_id );

				// Insert the first variable in the table of symbols as NumericVariable
				// with the type BOOL and the value of the previous variable
				lp::StringVariable * firstVar = new lp::StringVariable ( this->_id,
				        VARIABLE, BOOL, secondVar->getValue() );
				table.installSymbol ( firstVar );
			}
		}
		break;
		default:
			warning ( "Error de ejecución: incompatible type of expression for ", "Assigment" );
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::print()
{
	std::cout << "PrintStmt: "  << std::endl;
	std::cout << " print ";
	this->_exp->print();
	std::cout << std::endl;
}


void lp::PrintStmt::evaluate()
{
	switch ( this->_exp->getType() )
	{
	case NUMBER:
		std::cout << this->_exp->evaluateNumber();
		break;
	case BOOL:
		if ( this->_exp->evaluateBool() )
			std::cout << "true";
		else
			std::cout << "false";

		break;
	default:
		warning ( "Error de ejecución: tipo incompatible para ", "escribir" );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStringStmt::print()
{
	std::cout << "PrintStringStmt: "  << std::endl;
	std::cout << " PrintString ";
	this->_exp->print();
	std::cout << std::endl;
}


void lp::PrintStringStmt::evaluate()
{
	if ( this->_exp->getType() == STRING )
	{
		std::string * auxiliar = new std::string ( this->_exp->evaluateString() );

		for ( int i = 0; i < ( int ) auxiliar->length(); ++i )
		{
			if ( auxiliar->at ( i ) == '\\' && auxiliar->at ( i + 1 ) == 'n' )
			{
				std::cout << std::endl;
				i++;
			}
			else if ( auxiliar->at ( i ) == '\\' && auxiliar->at ( i + 1 ) == '\'' )
			{
				std::cout << "'";
				i++;
			}
			else if ( auxiliar->at ( i ) == '\\' && auxiliar->at ( i + 1 ) == 't' )
			{
				std::cout << "\t";
				i++;
			}
			else
			{
				std::cout << auxiliar->at ( i );
			}

		}

	}
	else
	{
		warning ( "Error de ejecución: tipo incompatible para ", "escribir_cadena" );
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print()
{
	std::cout << "ReadStmt: "  << std::endl;
	std::cout << " read (" << this->_id << ")";
	std::cout << std::endl;
}


void lp::ReadStmt::evaluate()
{
	double value;
	std::cin >> value;

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable * var = ( lp::Variable * ) table.getSymbol ( this->_id );

	// Check if the type of the variable is NUMBER
	if ( var->getType() == NUMBER )
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable * n = ( lp::NumericVariable * ) table.getSymbol ( this->_id );

		/* Assignment the read value to the identifier */
		n->setValue ( value );
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol ( this->_id );

		// Insert $1 in the table of symbols as NumericVariable
		// with the type NUMBER and the read value
		lp::NumericVariable * n = new lp::NumericVariable ( this->_id,
		        VARIABLE, NUMBER, value );

		table.installSymbol ( n );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStringStmt::print()
{
	std::cout << "ReadStringStmt: "  << std::endl;
	std::cout << " leer_cadena (" << this->_id << ")";
	std::cout << std::endl;
}


void lp::ReadStringStmt::evaluate()
{
	std::string value;
	std::cin >> value;

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable * var = ( lp::Variable * ) table.getSymbol ( this->_id );

	// Check if the type of the variable is STRING
	if ( var->getType() == STRING )
	{
		/* Get the identifier in the table of symbols as StringVariable */
		lp::StringVariable * n = ( lp::StringVariable * ) table.getSymbol ( this->_id );

		/* Assignment the read value to the identifier */
		n->setValue ( value );
	}
	// The type of variable is not STRING
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol ( this->_id );

		// Insert $1 in the table of symbols as StringVariable
		// with the type STRING and the read value
		lp::StringVariable * n = new lp::StringVariable ( this->_id,
		        VARIABLE, STRING, value );

		table.installSymbol ( n );
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::print()
{
	std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate()
{
	// Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::print()
{

	std::cout << "IfStmt: "  << std::endl;
	this->_cond->print();

	std::list<Statement *>::iterator stmtIter;
	for ( stmtIter = this->_stmt1->begin(); stmtIter != this->_stmt1->end(); stmtIter++ )
	{
		( *stmtIter )->print();
	}
	if ( this->_stmt2 != NULL )
	{
		for ( stmtIter = this->_stmt2->begin(); stmtIter != this->_stmt2->end(); stmtIter++ )
		{
			( *stmtIter )->print();
		}
	}
	std::cout << std::endl;

}


void lp::IfStmt::evaluate()
{
	std::list<Statement *>::iterator stmtIter;
	// If the condition is true,
	if ( this->_cond->evaluateBool() == true )
	{
		// the consequent is run
		for ( stmtIter = this->_stmt1->begin(); stmtIter != this->_stmt1->end(); stmtIter++ )
		{
			( *stmtIter )->evaluate();
		}
	}
	// Otherwise, the alternative is run if exists
	else if ( this->_stmt2 != NULL )
	{
		for ( stmtIter = this->_stmt2->begin(); stmtIter != this->_stmt2->end(); stmtIter++ )
		{
			( *stmtIter )->evaluate();
		}

	}
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::print()
{
	std::cout << "WhileStmt: "  << std::endl;
	// Condition
	this->_cond->print();

	// Body of the while loop
	std::list<Statement *>::iterator stmtIter;
	for ( stmtIter = this->_stmtlist->begin(); stmtIter != this->_stmtlist->end(); stmtIter++ )
	{
		( *stmtIter )->print();
	}

	std::cout << std::endl;
}


void lp::WhileStmt::evaluate()
{
	// While the condition is true. the body is run
	while ( this->_cond->evaluateBool() == true )
	{
		//Run the stmtlist
		std::list<Statement *>::iterator stmtIter;
		for ( stmtIter = this->_stmtlist->begin(); stmtIter != this->_stmtlist->end(); stmtIter++ )
		{
			( *stmtIter )->evaluate();
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ForStmt::print()
{
	std::cout << "ForStmt: "  << std::endl;
	// Variable
	std::cout << "para " << this->_variable << " desde ";
	this->_from->print();
	std::cout << " hasta ";
	this->_until->print();
	std::cout << " paso ";
	this->_step->print();

	std::cout << std::endl;
	// Body of the for loop
	std::list<Statement *>::iterator stmtIter;
	for ( stmtIter = this->_stmtlist->begin(); stmtIter != this->_stmtlist->end(); stmtIter++ )
	{
		( *stmtIter )->print();
	}

	std::cout << std::endl;
}


void lp::ForStmt::evaluate()
{
	// Get the identifier in the table of symbols as NumericVariable
	lp::Variable * var = ( lp::Variable * ) table.getSymbol ( this->_variable );
	int indexValue = 0, stopValue = 0, stepValue = 0;
	lp::NumericVariable * v;
	// Check the type of the first varible
	if ( var->getType() == NUMBER )
	{
		// Get the identifier in the table of symbols as NumericVariable
		v = ( lp::NumericVariable * ) table.getSymbol ( this->_variable );
	}
	// The type of variable is not NUMBER or is declared
	else
	{
		// Delete the variable from the table of symbols
		table.eraseSymbol ( this->_variable );

		// Insert the variable in the table of symbols as NumericVariable
		// with the type NUMBER and the value
		v = new lp::NumericVariable ( this->_variable,
		                              VARIABLE, NUMBER, indexValue );
		table.installSymbol ( v );
	}
	if ( ( this->_from->getType() == NUMBER )
	        and ( this->_from->getType() == NUMBER )
	        and ( this->_from->getType() == NUMBER ) )
	{
		//Recogemos los valores para la iteración del for
		indexValue = this->_from->evaluateNumber();
		stopValue = this->_until->evaluateNumber();
		stepValue = this->_step->evaluateNumber();
		if ( stepValue != 0 )
		{
			if ( ( ( indexValue > stopValue ) and ( stepValue > 0 ) )
			        or ( ( indexValue < stopValue ) and ( stepValue < 0 ) ) )
			{
				warning ( "Error de ejecución: valores incompatibles para iterar", "para" );
			}
			else
			{
				for ( indexValue = this->_from->evaluateNumber() ; indexValue <= stopValue; indexValue = indexValue + stepValue )
				{
					v->setValue ( indexValue );
					//Run the stmtlist
					std::list<Statement *>::iterator stmtIter;
					for ( stmtIter = this->_stmtlist->begin(); stmtIter != this->_stmtlist->end(); stmtIter++ )
					{
						( *stmtIter )->evaluate();
					}
				}
			}
		}
		else
		{
			warning ( "Error de ejecución: paso incompatible para", "para" );
		}
	}
	else
	{
		warning ( "Error de ejecución: tipo incompatible para", "para" );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::RepeatStmt::print()
{
	std::cout << "RepeatStmt: "  << std::endl;
	// Condition
	this->_cond->print();

	// Body of the while loop
	std::list<Statement *>::iterator stmtIter;
	for ( stmtIter = this->_stmtlist->begin(); stmtIter != this->_stmtlist->end(); stmtIter++ )
	{
		( *stmtIter )->print();
	}

	std::cout << std::endl;
}


void lp::RepeatStmt::evaluate()
{
	// While the condition is true. the body is run
	do
	{
		//Run the stmtlist
		std::list<Statement *>::iterator stmtIter;
		for ( stmtIter = this->_stmtlist->begin(); stmtIter != this->_stmtlist->end(); stmtIter++ )
		{
			( *stmtIter )->evaluate();
		}
	}
	while ( this->_cond->evaluateBool() != true );

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print()
{
	std::list<Statement *>::iterator stmtIter;

	for ( stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++ )
	{
		( *stmtIter )->print();
	}
}


void lp::AST::evaluate()
{
	std::list<Statement *>::iterator stmtIter;

	for ( stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++ )
	{
		( *stmtIter )->evaluate();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EraseStmt::print()
{
	std::cout << "EraseStmt"  << std::endl;
}

void lp::EraseStmt::evaluate()
{
	std::cout << CLEAR_SCREEN << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlaceStmt::print()
{
	std::cout << "EraseStmt"  << std::endl;
}

void lp::PlaceStmt::evaluate()
{
	if ( ( this->_exp1->getType() == NUMBER ) and ( this->_exp2->getType() == NUMBER ) )
	{
		PLACE ( ( int ) this->_exp1->evaluateNumber(), ( int ) this->_exp2->evaluateNumber() );
	}
	else
	{
		warning ( "Error de ejecución: incompatible values for", "_lugar" );
	}
}

