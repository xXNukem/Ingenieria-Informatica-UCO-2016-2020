/*! 
   \file Municipio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Municipio
*/


// Ficheros de cabecera
#include <iostream>
#include <string>

// atoi
#include <stdlib.h>

#include "Municipio.hpp"


/*
 Definiciones de las funciones lectura y escritura de la clase Municipio
*/

void ed::Municipio::leerMunicipio()
{
  int  n;
  std::string cadena;

  std::cout << "\n Lectura de los datos de un municipio" << std::endl;

  std::cout << " Nombre --> ";
  // Uso de getline para leer nombres compuestos separados por espacios
  std::getline(std::cin,cadena);
  this->setNombre(cadena);
 
  std::cout << " Código postal --> ";
  std::cin >> n;
  // Se elimna el salto de línea
  std::cin.ignore();
  // 
  this->setCodigoPostal(n);

  std::cout << " Número total de hombres --> ";
  std::cin >> n;
  // Se elimna el salto de línea
  std::cin.ignore();
  // 
  this->setHombres(n);

  std::cout << " Número total de mujeres --> ";
  std::cin >> n;
  // Se elimna el salto de línea
  std::cin.ignore();
  // 
  this->setMujeres(n);

}


void ed::Municipio::escribirMunicipio() const
{
/*
  std::cout  << "Código postal: "  << this->getCodigoPostal() << std::endl; 
  std::cout  << "Nombre: "   << this->getNombre() << std::endl; 
  std::cout  << "Habitantes: "  << this->getHabitantes() << std::endl; 
  std::cout  << "Hombres: " 	<< this->getHombres() << std::endl;  
  std::cout  << "Mujeres: " 	<< this->getMujeres() << std::endl << std::endl; 
*/

  std::cout  << this->getCodigoPostal();
  std::cout  << "\t"; 
  std::cout  << this->getNombre(); 
  std::cout  << "\t\t"; 
  std::cout  << this->getHombres();
  std::cout  << "\t"; 
  std::cout  << this->getMujeres();
  std::cout  << "\t"; 
  std::cout  << this->getHabitantes() << std::endl; 


}

////////////////////////////////////////////////////////////////////////////////

bool ed::comparar (Municipio const &objeto1, Municipio const &objeto2) 
{
   	return (   objeto1.getHombres() + objeto1.getMujeres() 
             < objeto2.getHombres() + objeto2.getMujeres() );
}


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, ed::Municipio const & objeto)
{
  // Se escriben los datos teniendo en cuenta el formato: CP Nombre; hombres; mujeres;
  stream << objeto.getCodigoPostal();
  stream << " ";
  stream << objeto.getNombre();
  stream << ";";
  stream << objeto.getHombres();
  stream << ";";
  stream << objeto.getMujeres();
  stream << ";";

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Municipio & objeto)
{
 // Se leen los datos teniendo en cuenta el formato: CP Nombre; hombres; mujeres;
  std::string cadena;

  std::getline(stream,cadena,' ');
  objeto.setCodigoPostal(atoi(cadena.c_str()));

  std::getline(stream,cadena,';');
  objeto.setNombre(cadena.c_str());

  std::getline(stream,cadena,';');
  objeto.setHombres(atoi(cadena.c_str()));

  std::getline(stream,cadena,';');
  objeto.setMujeres(atoi(cadena.c_str()));

  return stream;
} 

} // Fin del espacio de nombres ed
