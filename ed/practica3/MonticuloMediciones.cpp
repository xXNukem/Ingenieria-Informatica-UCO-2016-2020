/*!
	\file MonticuloMediciones.cpp
	\brief Fichero que contiene el código de las funciones de la clase MonticuloMediciones.
	\author Carlos de la Barrera Perez
	\date 2018-3-7
*/

//#include <vector>

#include <cassert>
#include <string.h>
#include "Medicion.hpp"

#include "MonticuloMediciones.hpp"

#include "macros.hpp"
/**
* @brief Variable global auxiliar utilizada en la funcion print()
*/
   int nDatos;
////////////////////////////////////////////////////////////////////

// Métodos privados de la clase MonticuloMediciones

ed::Medicion ed::MonticuloMediciones::getElement(int x)const
{
		#ifndef NDEBUG
			assert((x>=0)and((unsigned int)x<=_mediciones.size()));
		#endif

	Medicion m=_mediciones[x];

	return m;
}

void ed::MonticuloMediciones::setElement(int x, Medicion const & m)
{
	#ifndef NDEBUG
			assert((x>=0)and((unsigned int)x<=_mediciones.size()));
	#endif

	_mediciones[x]=m;

	#ifndef NDEBUG
		assert(getElement(x)==m);
	#endif

}

int ed::MonticuloMediciones::getLeftChild(int x)const
{
	int hijo;

		#ifndef NDEBUG
			assert(x>=0);
		#endif

		hijo=2*x+1;

		#ifndef NDEBUG
			assert(hijo==2*x+1);
		#endif

	return hijo;
}

int ed::MonticuloMediciones::getRightChild(int x)const
{
	int hijo;

		#ifndef NDEBUG
			assert(x>=0);
		#endif

		hijo=2*x+2;

		#ifndef NDEBUG
			assert(hijo==2*x+2);
		#endif

	return hijo;
}

int ed::MonticuloMediciones::getParent(int x)const
{
	int padre;

		#ifndef NDEBUG
			assert(x>=1);
		#endif

		padre=((x-1)/2);

		#ifndef NDEBUG
			assert(padre==((x-1)/2));
		#endif

	return padre;
}


void ed::MonticuloMediciones::shiftUp(int x)
{


	Medicion aux;

	if(x>0 && _mediciones[x]>_mediciones[getParent(x)])
	{

		#ifndef NDEBUG
			assert((x>0) and ((unsigned int)x<_mediciones.size()));
		#endif

		aux=_mediciones[x];
		_mediciones[x]=_mediciones[getParent(x)];
		_mediciones[getParent(x)]=aux;

			#ifndef NDEBUG
				if(x!=0)
				{
					assert(aux<=getElement(getParent(x)));
				}
				if(getLeftChild(x)<size() and getRightChild(x)<size())
				{
					assert(aux>=getElement(getLeftChild(x)));
					assert(aux>=getElement(getRightChild(x)));
				}
			#endif

		shiftUp(getParent(x));
		
	}


}
void ed::MonticuloMediciones::shiftDown(int x)
{
	Medicion aux;

	int aux1=x;
	int hijoI=getLeftChild(x);
	int hijoD=getRightChild(x);

		if((unsigned int)hijoI<_mediciones.size() && _mediciones[hijoI]>_mediciones[x])
		{
			aux1=hijoI;
		}
		if((unsigned int)hijoD<_mediciones.size() && _mediciones[hijoD]>_mediciones[aux1])
		{
			aux1=hijoD;
		}
		if(x!=aux1)
		{
			aux=_mediciones[x];
			_mediciones[x]=_mediciones[aux1];
			_mediciones[aux1]=aux;

				#ifndef NDEBUG
				if(x!=0)
				{
					assert(aux<=getElement(getParent(x)));
				}
				if(getLeftChild(x)<=size())
				{
					assert(getElement(x)>=getElement(getLeftChild(x)));
				}
				if(getRightChild(x)<=size())
				{
					assert(getElement(x)>=getElement(getRightChild(x)));
				}
			#endif



			shiftDown(aux1);
		}

}

bool ed::MonticuloMediciones::has(Medicion const & m)
{
	std::vector<Medicion>::iterator it;

		for(it=_mediciones.begin();it<_mediciones.end();it++)
		{
			if(*it==m)
			{
				return true;
			}
		}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////7

// Métodos públicos de la clase MonticuloMediciones

bool ed::MonticuloMediciones::isEmpty()const
{
	if(_mediciones.size()==0)
	{
			#ifndef NDEBUG
				assert(true==(_mediciones.size()==0));
			#endif

		return true;

	}
	else
	{
			#ifndef NDEBUG
				assert(false==(_mediciones.size()==0));
			#endif

		return false;

	}
}

int ed::MonticuloMediciones::size()const
{
	return _mediciones.size();
}

ed::Medicion const ed::MonticuloMediciones::top()const
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	Medicion pE=getElement(0);

		#ifndef NDEBUG
			assert(pE==getElement(0));
		#endif

	return pE;
}

void ed::MonticuloMediciones::insert(Medicion const &m)
{
	Medicion aux;
	bool encontrado=false;

	if(has(m)==true)
	{
		aux=m;
		encontrado=true;
	}
		
		if(encontrado==false)
		{
			_mediciones.push_back(m);
			shiftUp(_mediciones.size()-1);
		}
		else
		{
			std::cout<<BIRED<<"Error al insertar: "<<aux.getFecha()<<" Se omitirá su insercion"<<RESET<<"\n";
		}

			#ifndef NDEBUG
				assert(isEmpty()==false);
				assert(has(m)==true);
			#endif
		
}

void ed::MonticuloMediciones::remove()
{
	Medicion aux;

			#ifndef NDEBUG
				assert(isEmpty()==false);
			#endif

			aux=_mediciones[0];
			_mediciones[0]=_mediciones[_mediciones.size()-1];
			_mediciones[_mediciones.size()-1]=aux;

			_mediciones.erase(_mediciones.end());

			shiftDown(0);


}

void ed::MonticuloMediciones::removeAll()
{
	_mediciones.clear();

		#ifndef NDEBUG
			assert(isEmpty()==true);
		#endif
}


void ed::MonticuloMediciones::modify(Medicion const &m)
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	_mediciones[0]=m;

	shiftDown(0);

		#ifndef NDEBUG
			assert(has(m)==true);
		#endif
}
//OPERADORES 


ed::MonticuloMediciones ed::MonticuloMediciones::operator=(MonticuloMediciones const &mm)
{
		#ifndef NDEBUG
			//assert(_mediciones!=mm._mediciones);
		#endif

	_mediciones=mm._mediciones;

	return *this;
}


//Funcion de escritura
void ed::MonticuloMediciones::print()
{
	ed::MonticuloMediciones aux;
	ed::Medicion m;
	aux=*this;

   if(size()==0)
   {
    std::cout<<BIRED<<"El monticulo se encuentra vacio"<<RESET<<"\n";    
    return;
   }

		   char c[1];
		   	std::cout<<BIGREEN<<"Escribe la cantidad de datos que se mostraran simultaneamente"<<"\n";
		   	std::cout<<BIYELLOW<<"Hay "<<size()<<" registros disponibles, mostrar-> "<<BIBLUE;
		   	while(!(std::cin>>nDatos) || (nDatos<=0) || (nDatos>size()))
			  { 
				 std::cin.clear();
				 std::cin.ignore(80, '\n');
				 std::cout<<RED<<"Error!"<<RESET<<std::endl;  
				 std::cout <<BIGREEN<< " Escribe la cantidad de datos que se mostraran simultaneamente "<<BIBLUE<<"\n";
				 std::cout<<BIYELLOW<<"Hay "<<size()<<" registros disponibles, mostrar-> "<<BIBLUE;
			  }
			   int cont=0;
			   shiftUp(_mediciones.size()-1);
   for (int i = 0; i < size(); i++)
   { 

	    if(cont==nDatos)
	    {
	    	std::cout<<"Pulsa cualquier tecla para seguir mostrando, 's' para salir ->"<<BIBLUE;
	    	std::cin>>c;
	    	std::cout<<"\n";
		     if(strcmp(c,"s"))
		     {
		     	cont=0;
		     }
		     else
		     {
		     	break;
		 	}
	    }
	    		m=aux.top();

			    if(m.getFecha().getMes()<10 && m.getFecha().getDia()<10)
			    {
			     std::cout<<BIGREEN<<"\tFecha:"<<BIBLUE<<" 0"<<m.getFecha().getDia()<<"-0"<<m.getFecha().getMes()<<"-"<<m.getFecha().getAgno()<<BIGREEN<<"\t Precipitacion: "<<BIBLUE<<m.getPrecipitacion()<<std::endl;    
			    }    
			    else if(m.getFecha().getDia()<10)
			    {
			     std::cout<<BIGREEN<<"\tFecha:"<<BIBLUE<<" 0"<<m.getFecha()<<BIGREEN<<"\t Precipitacion: "<<BIBLUE<<m.getPrecipitacion()<<std::endl;    
			    }
			    else if(m.getFecha().getMes()<10)
			    {
			     std::cout<<BIGREEN<<"\tFecha: "<<BIBLUE<<m.getFecha().getDia()<<"-0"<<m.getFecha().getMes()<<"-"<<m.getFecha().getAgno()<<BIGREEN<<"\t Precipitacion: "<<BIBLUE<<m.getPrecipitacion()<<std::endl;    
			    }
			    else
			    {
			     std::cout<<BIGREEN<<"\tFecha: "<<BIBLUE<<m.getFecha()<<BIGREEN<<"\t Precipitacion: "<<BIBLUE<<m.getPrecipitacion()<<std::endl;
			    }
	    cont++;

	    aux.remove();
   }

   std::cout<<BIGREEN<<"Todos los resulados mostrados, pulsa tecla para salir"<<RESET<<"\n";
   getchar();
}

