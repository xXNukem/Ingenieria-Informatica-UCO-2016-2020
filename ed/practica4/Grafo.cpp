/*!
	\file Grafo.cpp
	\brief Fichero que contiene el código de las funciones de la clase Grafo.
	\author
	\date
*/

//#include <vector>

#include <cassert>

#include "Vertice.hpp"

#include "Grafo.hpp"

////////////////////////////////////////////////////////////////////

bool ed::Grafo::existeVertice(ed::Vertice const & v)const
{
	for(int i=0;i<getNumVertices();i++)
	{
		if(_v[i]==v)
		{
			return true;
		}
	}

	return false;
}

ed::Vertice ed::Grafo::getVertice(int i)const 
{
		#ifndef NDEBUG
			assert(existeVertice(_v.at(i))==true);
		#endif 

	return _v.at(i);
}

int ed::Grafo::getNumVertices()const 
{
	int tam=_v.size();

	return tam;
}

void ed::Grafo::printM()const 
{
	for (int i = 0; i < getNumVertices(); ++i)
	{
		for (int j = 0; j < getNumVertices(); ++j)
		{
			std::cout<<std::fixed << std::setprecision ( 2 )<<"["<<_matriz[i][j]<<"]";
		}
		std::cout<<"\n";
	}
}

void ed::Grafo::printV()const
{
	for (int i=0; i<(int)_v.size();i++)
	{
		std::cout<<_v[i]<<BIYELLOW<<"Label: "<<_v[i].getLabel()<<BIBLUE<<std::endl;
	}
}


float ed::Grafo::calcularDistanciaEuclidea ( ed::Vertice v1, ed::Vertice v2 )
{

    float valorDevuelto = 0, x1, x2, y1, y2;
    //Obtenemos los valores de X e Y
    x1 = v1.getX();
    x2 = v2.getX();
    y1 = v1.getY();
    y2 = v2.getY();
    //Calculamos la distancia euclidea
    valorDevuelto = std::sqrt ( ( ( x2 - x1 ) * ( x2 - x1 ) ) + ( ( y2 - y1 ) * ( y2 - y1 ) ) );

    	#ifndef NDEBUG
    		assert(valorDevuelto==std::sqrt ( ( ( x2 - x1 ) * ( x2 - x1 ) ) + ( ( y2 - y1 ) * ( y2 - y1 ) ) ));
    	#endif

    return valorDevuelto;
}

void ed::Grafo::insertarVertice(ed::Vertice & v)
{
	_v.push_back(v);
}

void ed::Grafo::insertarMatriz(int x, int y,float peso)
{
	_matriz[x][y]=peso;
}

void ed::Grafo::leerVerticeInsertar()
{
	ed::Vertice v;
	float x,y;

		
std::cout<<BIGREEN<<" Escirbe la componente X -> "<<BIBLUE<<" ";
	while(!(std::cin>>x))
	 { 
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"ERROR"<<RESET<<std::endl;  
		 std::cout <<BIGREEN<< " Escirbe la componente X -> "<<BIBLUE;
	 }

	  std::cout<<BIGREEN<<" Escirbe la componente Y -> "<<BIBLUE<<" ";
	while(!(std::cin>>y))
	 { 
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"ERROR"<<RESET<<std::endl;  
		 std::cout <<BIGREEN<< " Escirbe la componente Y -> "<<BIBLUE;
	 }

	  v.setX(x);
	  v.setY(y);
	  v.setLabel(getNumVertices());

	  insertVertice(v);

	  #ifndef NDEBUG
	  	assert(existeVertice(v)==true);
	  #endif
}

void ed::Grafo::leerVerticeBorrar()
{

	if(getNumVertices()==0)
	{
		std::cout<<BIRED<<"El vector de vertices está vacio"<<RESET<<std::endl;
	}
	else
	{
		int label;
		ed::Vertice v;
		do{
			std::cout<<BIGREEN<<"Vertices cargados: (Las etiquetas se reorganizaran tras el borrado)"<<BIBLUE<<std::endl;
			printV();

			std::cout<<BIYELLOW<<"Label (-1 para salir)-> "<<BIBLUE;
			while(!(std::cin>>label) || (label<0) || (label>getNumVertices()-1))
		 	{ 
		 		if(label==-1)
		 		{
		 			return;
		 		}
			 std::cin.clear();
			 std::cin.ignore(80, '\n');
			 std::cout<<RED<<"ERROR"<<RESET<<std::endl;  
			 std::cout <<BIYELLOW<< "Label (-1 para salir)-> "<<BIBLUE;
		  	}
		  	v.setLabel(label);
		  	borrarVertice(v);

		  	#ifndef NDEBUG
		  		assert(existeVertice(v)==false);
		  	#endif
		  }while(getNumVertices()>0);
	}
}

void ed::Grafo::insertVertice(ed::Vertice & v)
{
	int nV=getNumVertices();

	float distanciaE;
	if(existeVertice(v)==false)
	{
			if(nV!=0)//Cuando el numero de vertices es mayor que 1, hay que reasignar el tamaño de la matriz
			{
				std::vector<float> aux (nV + 1); //Creo un vector auxiliar con el tamaño que tenia anteriormente la matriz mas 1

				fill(aux.begin(),aux.end(),0); //LLeno todo de ceros para evitar los valores basura

				_matriz.resize(nV+1,aux); //Añado una nueva fila y le jinco el valor al final

				//Hay que añadir una columna a las filas anteriores

					for(int i=0;i<nV;i++)
					{
						_matriz[i].resize(nV+1,0);
					}
				//La matriz ya se ha quedado con el tamaño bien

				for (int i = 0; i < nV; ++i) //Calculamos la distancia euclidea y la añadimos a la matiz
				{
					distanciaE=calcularDistanciaEuclidea(v,getVertice(i)); //Obtenemos la distancia del vertice v con respecto al resto de vertices
						//El label que cogen corresponden siempre al tamaño
					_matriz[v.getLabel()][getVertice(i).getLabel()]=distanciaE; //Lo insertamos en la fila correspondiente a la id(label) del vertice y como cada columna representa un vertice en la columna correspondiente
					_matriz[getVertice(i).getLabel()][v.getLabel()]=distanciaE; //Accede a la fila de cada vertice y añade en la ultima columna el peso correspondiente

				}
			}

			_v.push_back(v);
	}
		#ifndef NDEBUG
			assert(existeVertice(v)==true);
		#endif
}

void ed::Grafo::borrarVertice(ed::Vertice & v)
{
	int vL=v.getLabel();

	int nV=getNumVertices();

		for (int i = vL; i < nV-1; ++i)//Sobreescribo la fila a borrar por la siguiente
		{
			for (int j = 0; j < nV; j++)
			{
				_matriz[i][j]=_matriz[i+1][j];
			}
		}

		for (int i = 0; i < nV; ++i)//Sobreescribo la columna a borrar por la siguiente
		{
			for (int j = vL; j < nV-1; j++)
			{
				_matriz[i][j]=_matriz[i][j+1];
			}
		}

		//Hay que borrar el vertice del vector de vertices

		_v.erase(_v.begin()+vL);

		//Hay que reasignar el tamaño de la matriz

		nV=getNumVertices(); //El numero de vertices ahora ha cambiado

		_matriz.resize(nV); //Eliminamos de memoria la ultima fila

		for (int i = 0; i < nV; ++i) //Cada iteracin del for elimina el ultimo elemento de cada vector de la matriz
		{
			_matriz[i].resize(nV);
		}

		//Hay que modificar todas las label del los vertices en el vector de vertises

		for (int i = 0; i < nV; ++i)
		{
			_v[i].setLabel(i);
		}

			#ifndef NDEBUG
			assert(existeVertice(v)==false);
		#endif

}

vector <ed::Vertice> ed::Grafo::getVectorVertices()const
{
	return _v;
}

void ed::Grafo::setVectorVertices(vector <ed::Vertice> v)
{
	for (int i = 0; i < (int)v.size(); ++i)
	{
		_v.push_back(v[i]);
	}

		#ifndef NDEBUG
			for(int i=0;i<(int)v.size;i++)
			{
				assert(_v[i]==v[i])
			}
		#endif
}


ed::Grafo ed::Grafo::operator=(ed::Grafo & g)
{
	_matriz=g._matriz;
	_v=g._v;

	return *this;
}

// COMPLETAR