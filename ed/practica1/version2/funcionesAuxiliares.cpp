/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 1
  \author 
  \date   
*/

#include <iostream>
#include <string>

#include "funcionesAuxiliares.hpp"

#include "macros.hpp"

#include "Vector3D.hpp"

int ed::menu()
{
 int opcion, posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(posicion++,10);
	std::cout << BIBLUE;
	std::cout << "Programa principal | Opciones del menú   ";
	std::cout << RESET;

	posicion++;
	PLACE(posicion++,10);
	std::cout << "[1] Leer vectores" << std::endl;

	PLACE(posicion++,10);
	std::cout << "[2] Leer número escalar " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[3] Escribir número y vectores " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[4] Observadores de los vectores: módulos y ángulos " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[5] Modificación del vector \"u\" usando v y k " << std::endl;

	PLACE(posicion++,10);
  	std::cout << "[6] Producto escalar de u y v " << std::endl;

	PLACE(posicion++,10);
  	std::cout << "[7] Producto vectorial de u y v " << std::endl; 

	PLACE(posicion++,10);
  	std::cout << "[8] Producto mixto de tres vectores  u * (v ^ w) " << std::endl; 

	PLACE(posicion++,10);
  	std::cout << "[9] Mostrar el uso de los operadores con u y v" << std::endl; 

	posicion++;
	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Fin del programa" << RESET << std::endl;

	posicion++;
	PLACE(posicion++,20);
	std::cout << BIYELLOW;
	std::cout << "Opción: ";
	std::cout << RESET;
	std::cin >> opcion;

   	// Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}


///////////////////////////////////////////////////////////////////////////

void ed::leerVectores(ed::Vector3D &u, ed::Vector3D &v, ed::Vector3D &w)
{

   

 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D


	// Usando la función de la clase
	std::cout << BIGREEN << "Lectura de u usando la función leerVector" << RESET << std::endl;
	std::cout << BIYELLOW << "u.leerVector() " << RESET << std::endl; 
	u.leerVector3D();

	std::cout << std::endl;

	// Usando la sobrecarga del operador >>
	std::cout << BIGREEN << "Lectura usando el operador de flujo >> " << RESET << std::endl;
	std::cout << "Introduzca las componentes separadas por espacios " << std::endl;
	std::cout << "v = "; 
	std::cin >> v;

	std::cout << std::endl;

	std::cout << "Introduzca las componentes separadas por espacios " << std::endl;
	std::cout << "w = "; 
	std::cin >> w;



 	return;
}

///////////////////////////////////////////////////////////////////////////

void ed::escribirVectores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w)
{
 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D

	// Usando la función de la clase
	std::cout  << BIYELLOW << "u = "  << RESET ; 
	u.escribirVector3D();
	std::cout << std::endl;

	// Usando la sobrecarga del operador >>
	std::cout  << BIYELLOW << "v = " << RESET  << v << std::endl;
	std::cout  << BIYELLOW << "w = " << RESET << w << std::endl;

 	return;
}


///////////////////////////////////////////////////////////////////////////

void ed::observadoresDeVectores(ed::Vector3D const &u, ed::Vector3D const &v)
{
 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D

	// Usando la función de la clase
	std::cout  << BIYELLOW << "u = "  << RESET ; 
	u.escribirVector3D();
	std::cout << std::endl;

	// Usando la función de la clase
	std::cout  << BIYELLOW << "v = "  << RESET ; 
	v.escribirVector3D();
	std::cout << std::endl;

	std::cout << BIYELLOW << "Módulo de u -->  ||u|| = " 
			  << RESET << u.modulo() << std::endl;

	std::cout << BIYELLOW << "Módulo de v -->  ||v|| = " 
			  << RESET << v.modulo() << std::endl;


  if ( (u.modulo() != 0.0) and  (v.modulo() != 0.0) ) 
	{
		std::cout << BIYELLOW << "Ángulo entre u y v = " 
			  << RESET << u.angulo(v) << std::endl;
	}
	else
	{
		std::cout << BIRED << "No se pueden calcular los ángulos: hay, al menos, un vector nulo" << RESET << std::endl;
		std::cout << BIYELLOW << "u = " << RESET << u << std::endl;
		std::cout << BIYELLOW << "v = " << RESET << v << std::endl;
	}


	// 

	std::cout << BIBLUE << "Datos de u = " << RESET << u << std::endl;
 	std::cout << BIYELLOW << "u.get1() = " << RESET << u.get1() << std::endl;
 	std::cout << BIYELLOW << "u.get2() = " << RESET << u.get2() << std::endl;
 	std::cout << BIYELLOW << "u.get3() = " << RESET << u.get3() << std::endl;

	std::cout << BIYELLOW << "u.modulo() = " << RESET << u.modulo() << std::endl;

	if ( (u.modulo() != 0.0) ) 
	{
		std::cout << BIYELLOW << "u.alfa() = " << RESET << u.alfa() << std::endl;
		std::cout << BIYELLOW << "u.beta() = " << RESET << u.beta() << std::endl;
		std::cout << BIYELLOW << "u.gamma() = " << RESET << u.gamma() << std::endl;
	}
	else
	{	
		std::cout << BIRED << "No se pueden calcular los ángulos de u: es un vector nulo" 
				  << RESET << std::endl;
		std::cout << BIYELLOW << "u = " << RESET << u << std::endl;
	}

	// //////////////////////

	std::cout << BIBLUE << "Datos de v = " << RESET << v << std::endl;
 	std::cout << BIYELLOW << "v.get1() = " << RESET << v.get1() << std::endl;
 	std::cout << BIYELLOW << "v.get2() = " << RESET << v.get2() << std::endl;
 	std::cout << BIYELLOW << "v.get3() = " << RESET << v.get3() << std::endl;

	std::cout << BIYELLOW << "v.modulo() = " << RESET << v.modulo() << std::endl;

	if ( (v.modulo() != 0.0) ) 
	{
		std::cout << BIYELLOW << "v.alfa() = " << RESET << v.alfa() << std::endl;
		std::cout << BIYELLOW << "v.beta() = " << RESET << v.beta() << std::endl;
		std::cout << BIYELLOW << "v.gamma() = " << RESET << v.gamma() << std::endl;
	}
	else
	{	
		std::cout << BIRED << "No se pueden calcular los ángulos de v: es un vector nulo" 
				  << RESET << std::endl;
		std::cout << BIYELLOW << "u = " << RESET << u << std::endl;
	}



 	return;
}

///////////////////////////////////////////////////////////////////////////

void ed::modificarVector(ed::Vector3D &u, ed::Vector3D const &v, double k)
{
 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D

   	std::cout << BIBLUE;
  	std::cout << "Modificaciones del vector " << std::endl; 
	std::cout << RESET;

	//
	std::cout << BIGREEN << "Valor inicial de u = " << RESET  << u 
			  << std::endl << std::endl;

	//
	u.sumConst(k);

  	std::cout << BIYELLOW << "u.sumConst(" << RESET 
			  << k 
			  << BIYELLOW << ") = " << RESET  << u << std::endl;

  	std::cout << BIGREEN << "Nuevo valor de u = " << RESET  << u 
			  << std::endl << std::endl;

	//
	u.multConst(k);

  	std::cout << BIYELLOW << "u.multConst(" << RESET 
			  << k 
			  << BIYELLOW << ") = " << RESET  << u << std::endl;

  	std::cout << BIGREEN << "Nuevo valor de u = " << RESET  << u 
			  << std::endl << std::endl;

	//
	std::cout << BIYELLOW << "Valor de v = " << RESET  << v 
			  << std::endl << std::endl;


	//
	u.sumVect(v);

  	std::cout << BIYELLOW << "u.sumConst(" << RESET 
			  << "v"
			  << BIYELLOW << ") = " << RESET  << u << std::endl;

  	std::cout << BIGREEN << "Nuevo valor de u = " << RESET  << u 
			  << std::endl << std::endl;

	//
	std::cout << BIYELLOW << "Valor de v = " << RESET  << v 
			  << std::endl << std::endl;

	u.multVect(v);

 	std::cout << BIYELLOW << "u.multConst(" << RESET 
			  << "v"
			  << BIYELLOW << ") = " << RESET  << u << std::endl;

  	std::cout << BIGREEN << "Nuevo valor de u = " << RESET  << u 
			  << std::endl << std::endl;


}

///////////////////////////////////////////////////////////////////////////

void ed::mostrarProductoEscalar(ed::Vector3D const &u, ed::Vector3D const &v)
{
 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D


	std::cout << BIBLUE;
	std::cout << "Producto escalar de dos vectores u y v " << std::endl << std::endl;
	std::cout << RESET;

	std::cout << BIGREEN << "Usando la función de la clase: u.dotProduct(v) " << RESET << std::endl; 
	std::cout << u << BIYELLOW << ".dotProduct(" << RESET << v << BIYELLOW << ") = " << RESET 
			  << u.dotProduct(v) << std::endl << std::endl;



	std::cout << BIGREEN << "Usando el operador: u * v " << RESET << std::endl; 
	std::cout << u << BIYELLOW << " * "  << RESET << v << " = " <<  u * v << std::endl  << std::endl;

	return;
}



///////////////////////////////////////////////////////////////////////////


void ed::mostrarProductoVectorial(ed::Vector3D const &u, ed::Vector3D const &v)
{
 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D


	// Se comprueba si no son nulos
	if ( (u.modulo() != 0.0) and  (v.modulo() != 0.0)) 
	{
		std::cout << BIBLUE;
	  	std::cout << "Producto vectorial de dos vectores: u ^ v " << std::endl << std::endl;
		std::cout << RESET;

	  	std::cout  << BIGREEN  << "Usando la función de la clase: " 
				   << BIYELLOW << " u.crossProduct(v) " 
				   << RESET << std::endl; 
		std::cout << u << BIYELLOW << ".crossProduct(" << RESET << v << BIYELLOW << ") = " << RESET 
			  << u.crossProduct(v) << std::endl << std::endl;

		std::cout  << BIGREEN  << "Usando el operador "
				   << BIYELLOW << " u ^ v "  << RESET << std::endl; 
		// Se deben usar los paréntesis en (u ^ v) para controlar la prioridad de los operadores
		std::cout << u <<  BIYELLOW << " ^ " << RESET 
	              << v << BIYELLOW << " = " << RESET 
	              << (u ^ v) << std::endl << std::endl;


		std::cout << BIGREEN << "Propiedad anticonmutativa: " << RESET << std::endl;
		std::cout << BIYELLOW << u << " ^ " << v << " = " << RESET << (u ^ v) << std::endl;

		std::cout << BIYELLOW << v << " ^ " << u << " = " << RESET << (v ^ u) << std::endl;
	}
	else 
	{	
		std::cout << BIRED << "No se puede calcular porque hay un vector nulo" << RESET << std::endl;
		std::cout << BIYELLOW << "u = " << RESET << u << std::endl;
		std::cout << BIYELLOW << "v = " << RESET << v << std::endl;
	}


	return;
}


///////////////////////////////////////////////////////////////////////////

void ed::mostrarProductoMixto(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w)
{
 // QUITAR LOS "COMENTARIOS DE BLOQUE" CUANDO SE HAYA CODIFICADO LA CLASE Vector3D


	// Se comprueba si no son nulos v y w
	if ( (v.modulo() != 0.0) and  (w.modulo() != 0.0)) 
	{
	  	std::cout << BIYELLOW << u << BIGREEN " * (" <<  v << " ^ " <<  w << ") = " << RESET
				  << u.productoMixto(v,w) << std::endl;

	  	std::cout << "Donde " << std::endl;
	  	std::cout << BIGREEN << v << " ^ " << w << " = " << RESET << (v ^ w) << std::endl;
	}
	else 
	{	
		std::cout << BIRED << "No se puede calcular porque hay un vector nulo " << RESET << std::endl;
		std::cout << BIYELLOW << "v = " << RESET << v << std::endl;
		std::cout << BIYELLOW << "w = " << RESET << w << std::endl;
	}


	return;
}


///////////////////////////////////////////////////////////////////////////

void ed::mostrarOperadores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D &w,  double k)
{

	std::cout << BIGREEN;
	std::cout << "Operador de igualdad == " << std::endl;
	std::cout << RESET;

	std::cout << BIYELLOW << "\t Los vectores u = " << RESET << u 
			  << BIYELLOW << " y v = " << RESET << v;

	if (u == v)
		std::cout << " son iguales " << std::endl;
	else
		std::cout << " son diferentes " << std::endl;


	//////////////////////
	std::cout << BIGREEN;
  	std::cout << "Operador de asignación: w = u" << std::endl;
	std::cout << RESET;

  	std::cout << BIYELLOW  << "\t Antes" << RESET  << std::endl; 
	std::cout << "\t w = " << w << "; u = " << u << std::endl; 

	// Operador de asignación
	w = u;

  	std::cout << BIYELLOW << "\t Después" << RESET << std::endl; 
	std::cout << "\t w = " << w << "; u = " << u << std::endl; 

	//////////////////////

   	std::cout << BIGREEN;
  	std::cout << "Operador prefijo unario +: +u" << std::endl; 
	std::cout << RESET;

	std::cout << BIYELLOW  << "\t + " << u << " = " << RESET <<  +u << std::endl;

	//////////////////////

   	std::cout << BIGREEN;
  	std::cout << "Operador prefijo unario -: -u " << std::endl; 
	std::cout << RESET;

	std::cout << BIYELLOW  << "\t - " << u << " = " << RESET <<  - u << std::endl;

	//////////////////////

   	std::cout << BIGREEN;
  	std::cout << "Operador binario +: u + v " << std::endl; 
	std::cout << RESET;
	std::cout << "\t" << BIYELLOW << u << " + " << v << " = " << RESET << u + v << std::endl;


	//////////////////////
   	std::cout << BIGREEN;
  	std::cout << "Operador binario -: u - v " << std::endl; 
	std::cout << RESET;

	std::cout << "\t" << BIYELLOW << u << " - " << v << " = " << RESET << u - v << std::endl;

	//////////////////////
   	std::cout << BIGREEN;
  	std::cout << "Producto por un número escalar (prefijo): k * u" << std::endl; 
	std::cout << RESET;

	std::cout << "\t" << BIYELLOW << k << " * " << u << " = " << RESET << (k * u) << std::endl;


	//////////////////////
   	std::cout << BIGREEN;
  	std::cout << "Producto por un número escalar (postfijo): u * k " << std::endl; 
	std::cout << RESET;

	std::cout << "\t" << BIYELLOW << u << " * " << k << " = " << RESET << (u * k) << std::endl;
	std::cout << std::endl;


	return;
}







		
