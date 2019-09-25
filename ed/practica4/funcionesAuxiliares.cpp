/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 1
  \author
  \date
*/


#include <iostream>

#include <fstream>

#include <string>

#include "funcionesAuxiliares.hpp"

#include "Grafo.hpp"

#include "Vertice.hpp"

#include "macros.hpp"

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
	std::cout << "[1] Cargar fichero de vertices" << std::endl;

	PLACE(posicion++,10);
	std::cout << "[2] Guardar fichero de vertices " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[3] Mostrar datos del grafo" << std::endl;

	PLACE(posicion++,10);
	std::cout << "[4] Añadir vertice " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[5] Borrar vertice " << std::endl;

	PLACE(posicion++,10);
  	std::cout << "[6] Aplicar algoritmo de Kruskal" << std::endl;

  	PLACE(posicion++,10);
  	std::cout << "[7] Aplicar algoritmo de Prim" << std::endl;

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

bool ed::cargarFichero(std::string const & nombreFichero, ed::Grafo & g) 
{
  	std::ifstream ifs(nombreFichero.c_str());
	ed::Vertice v;


	if(ifs)
	{
		while(ifs>>v)
		{

			v.setLabel(g.getNumVertices()); //Le asginamos a cada vertice el label correspondiente al numero de vertices que haya en ese momento

			g.insertVertice(v);
		}
		ifs.close();

		return true;

	}
	else
	{
		return false;
	}


}


void ed::grabarFichero(std::string const & nombreFichero, ed::Grafo const & g)
{
 
	ed::Vertice v;

	if(g.getNumVertices()!=0)
	{
		std::ofstream f(nombreFichero.c_str());

		for (int i=0;i<g.getNumVertices();i++)
		{

			f << std::fixed << std::setprecision ( 2 ) <<g.getVertice(i).getX()<<" "<<g.getVertice(i).getY()<<std::endl;

		}
		std::cout<<BIGREEN<<"Fichero guardado correctamente "<<RESET<<"\n";
		f.close();
	}
	else
	{
		std::cout<<BIRED<<"Error al guardar"<<RESET<<"\n";
	}
	
	return;
}

void ed::datosGrafo(ed::Grafo const & g)
{
	if(g.getNumVertices()<2)
	{
		std::cout<<BIRED<<"El grafo no se puede mostrar o no hay vertices suficientes"<<RESET<<std::endl;
	}
	else
	{
		std::cout<<BIGREEN<<"Matriz de adyacencia: "<<BIBLUE<<std::endl;

			g.printM();

		std::cout<<BIGREEN<<"Vector de vertices: "<<BIBLUE<<std::endl;

			g.printV();
			std::cout<<RESET<<std::endl;
	}
}


void ed::algoritmoKruskal(ed::Grafo  const & g,ed::Grafo & grafo)
{
	//ed::Grafo grafo;

	ed::Lado lado;

	std::vector<ed::Lado> vectorLados;

	std::vector<bool> visitados;

		/*for (int i = 0; i < g.getNumVertices(); ++i) //Copio en el grafo solucion el vector de vertices
		{
			grafo.insertarVertice(g.getVertice(i));
		}*/

		grafo.setVectorVertices(g.getVectorVertices());

		for (int i = 0; i < g.getNumVertices(); ++i) //Le meto al vector de lados las distancias euclideas de todos lados del grafo
		{
			lado.setVertice1(g.getVertice(i));

			for (int j = i+1; i < g.getNumVertices(); ++i)
				{
					lado.setVertice2(g.getVertice(j));

					lado.setPeso(lado.calcularDistanciaEuclidea(g.getVertice(i),g.getVertice(j)));

					vectorLados.push_back(lado);
				}	
		}	

			ed::Lado aux;

		for (int i = 0; i < ( int)vectorLados.size()-1; ++i) //ordeno el vector de lados de menor a mayor peso
		{
			for (int j = 0; j < ( int)vectorLados.size()-1; ++j)
			{
				if(vectorLados[j].getPeso()>vectorLados[j+1].getPeso())
				{
					aux=vectorLados[j];
					vectorLados[j]=vectorLados[j+1];
					vectorLados[j+1]=aux;
				}
			}
		}

		fill(visitados.begin(),visitados.end(),false); //inicializando el vector visitados todo a false

		for (int i = 0; i < ( int)vectorLados.size(); ++i)
		{
			//Comprobar si los vertices de ese lado estan visitados
			//Kruskal selecsiona ese lado siempre que los dos vertices no esten visitados
			if (visitados[vectorLados[i].getVertice1().getLabel()]!=true || visitados[vectorLados[i].getVertice2().getLabel()]!=true)
			{
				grafo.insertarMatriz(vectorLados[i].getVertice1().getLabel(),vectorLados[i].getVertice2().getLabel(), vectorLados[i].getPeso());
				//Como la matriz es simetrica la vuelvo a copiar invirtiendo el peso
				grafo.insertarMatriz(vectorLados[i].getVertice2().getLabel(),vectorLados[i].getVertice1().getLabel(), vectorLados[i].getPeso());
				visitados[i]=true;
			}
		}

}

void ed::algoritmoPrim(ed::Grafo  const & g,ed::Grafo & grafo)
{


}