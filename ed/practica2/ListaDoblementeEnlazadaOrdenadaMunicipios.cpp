/*!
	\file   ListaDoblementeEnlazadaOrdenadaMunicipios.cpp
	\brief  Clase de una lista doblemente enlazada y ordenada de Municipios
	\author  
	\date  
	\version 1.0
*/

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"
#include "NodoMunicipioInterfaz.hpp"
#include "Municipio.hpp"

// DEBES CODIFICAR LAS FUNCIONES DE LA CLASE ListaDoblementeEnlazadaOrdenadaMunicipios

int ed::ListaDoblementeEnlazadaOrdenadaMunicipios::nItems()const
{
	int items=0;

	ed::NodoDoblementeEnlazadoMunicipio *it=getHead();

	while(it!=NULL)
	{
		items++;
		it=it->getNext();
	}

return items;
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isFirstItem()const
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	if(getCurrent()==getHead())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isLastItem()const
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	if(getCurrent()->getNext()==NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getCurrentItem() const
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	return getCurrent()->getItem();
}

ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getPreviousItem() const
{

		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isFirstItem()==false);
		#endif

	ed::NodoDoblementeEnlazadoMunicipio *it;
	it=getCurrent()->getPrevious();

	return it->getItem();
}

ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getNextItem() const
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isLastItem()==false);
		#endif

	ed::NodoDoblementeEnlazadoMunicipio *it;
	it=getCurrent()->getNext();

	return it->getItem();
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoHead()
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	setCurrent(getHead());

		#ifndef NDEBUG
			assert(isFirstItem()==true);
		#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoLast()
{

		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif

	ed::NodoDoblementeEnlazadoMunicipio *it=getHead();

	while(it!=NULL)
	{
		it=it->getNext();
	}

	setCurrent(it);

		#ifndef NDEBUG
			assert(isLastItem()==true);
		#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoPrevious()
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isFirstItem()==false);
		#endif

	setCurrent(getCurrent()->getPrevious());
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoNext()
{
		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isLastItem()==false);
		#endif

	setCurrent(getCurrent()->getNext());
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::find(ed::Municipio const &item)
{
	if(isEmpty())
	{

   		return false;

  	}
 	 gotoHead();

  while(!isLastItem())
  {
	   if(item==getCurrentItem())
	   {

		    #ifndef NDEBUG
		     assert(getCurrentItem()==item);
		    #endif

	    return true;

	   }
	   else
	   {
	    gotoNext();
	   }
  }
  if(item==getCurrentItem())
  {
	   #ifndef NDEBUG
	    assert(getCurrentItem()==item);
	   #endif

   return true;

  }
  else
  {

	   #ifndef NDEBUG
	    assert(item<getCurrentItem() or isLastItem()==true);
	   #endif

   return false;

  }
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::insert(ed::Municipio const & item)
{

		int elementos=nItems();
		#ifndef NDEBUG
			assert(find(item)==false);
		#endif 

	ed::NodoDoblementeEnlazadoMunicipio *nuevo;
	nuevo=new NodoDoblementeEnlazadoMunicipio(item, NULL, NULL);

		if(isEmpty()==true)
		{
			setHead(nuevo);
			setCurrent(getHead());
			gotoHead();

				return;
		}
		else
		{
			gotoHead();
				while(isLastItem()==false)
				{
					if(item<getCurrentItem())
					{
						break;
					}

						gotoNext();
				}
		}

		if(nItems()==1)
		{
			if(item<getCurrentItem())
			{
				nuevo->setPrevious(NULL);
				nuevo->setNext(getCurrent());
				getCurrent()->setPrevious(nuevo);
				getCurrent()->setNext(NULL);
				setHead(nuevo);
				gotoHead();
			}
			else
			{
				nuevo->setPrevious(getCurrent());
				nuevo->setNext(NULL);
				getCurrent()->setNext(nuevo);
				gotoNext();
			}
		}
		else if(isLastItem())//Se controla el ultimo elemento 
		{
			if(item<getCurrentItem())
			{
				nuevo->setPrevious(getCurrent()->getPrevious());
				nuevo->setNext(getCurrent());
				getCurrent()->setPrevious(nuevo);
				gotoPrevious();
				getCurrent()->getPrevious()->setNext(getCurrent());
			}
			else
			{
				nuevo->setPrevious(getCurrent());
				nuevo->setNext(NULL);
				getCurrent()->setNext(nuevo);
				gotoNext();
			}
		}
		else if(isFirstItem())
		{//En este caso se colocara si es menor que la cabeza

		   if(item<getCurrentItem())
		   {//Si es menor que el ultimo se colocora el penultimo
			    nuevo->setNext(getCurrent());
			    nuevo->setPrevious(NULL);
			    getCurrent()->setPrevious(nuevo);
			    setHead(nuevo);
			    gotoHead();
		   }

		   else
		   {//En caso contrario se colocara el ultimo
			    nuevo->setPrevious(getCurrent()->getPrevious());
			    nuevo->setNext(getCurrent());
			    getCurrent()->setPrevious(nuevo);
			    gotoPrevious();
			    getCurrent()->getPrevious()->setNext(getCurrent());
		   }
		  }
		  else
		  {//Este es el ultimo caso, que el nuevo elemento va introducido entre dos elementos
			   nuevo->setPrevious(getCurrent()->getPrevious());
			   nuevo->setNext(getCurrent());
			   getCurrent()->setPrevious(nuevo);
			   gotoPrevious();
			   getCurrent()->getPrevious()->setNext(getCurrent());
		  }

		#ifndef NDEBUG
			assert(getCurrentItem()==item);
			assert(nItems()==elementos+1);
		#endif

}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::remove()
{

	  #ifndef NDEBUG
	  assert(!this->isEmpty());
	  #endif 
 
 int aux=nItems();
 
		 if(nItems()==1)
		 {
		   setCurrent(NULL);
		   delete getCurrent();
		   setHead(NULL);
		 }
		 else if (isFirstItem() && nItems()>=2)
		 {
		 	Municipio next=getNextItem();

			   setHead(getCurrent()->getNext());
			   delete getCurrent();
			   setCurrent(getHead());
			   getCurrent()->setPrevious(NULL);

			#ifndef NDEBUG
			   		if(isEmpty()==true)
			  		{
			  			assert(isEmpty()==true);
			  		}
			  		if(isEmpty()==false)
			  		{
			  			assert(next==getCurrentItem() and isFirstItem()==true);
			  		}
			#endif
		  
		 }
		 else if ( isLastItem() && nItems()>=2 )
		 {//Si queremos borra el ultimo elemento el penultimo pasa a ser el ultimo y apunta el siguiente a NULL.

		 	Municipio old=getPreviousItem();

			  gotoPrevious();
			  delete getCurrent()->getNext();
			  getCurrent()->setNext(NULL);

			  	#ifndef NDEBUG
			  		if(isEmpty()==true)
			  		{
			  			assert(isEmpty()==true);
			  		}
			  		if(isEmpty()==false)
			  		{
			  			assert(old==getCurrentItem() and isLastItem()==true);
			  		}
			  	#endif
		 }
		 else
		 {//Si queremos borrar un elemento de en medio se enlazan el anterior y el posterior a este entre si y luego se borra el elemento a borrar.  
		  
		  	Municipio old=getPreviousItem();
		  	Municipio next=getNextItem();
		  	ed::NodoDoblementeEnlazadoMunicipio *aux=getCurrent()->getNext();

			  getCurrent()->getPrevious()->setNext( getCurrent()->getNext() );//anterior->siguiente

			  getCurrent()->getNext()->setPrevious( getCurrent()->getPrevious() );//anterior<-siguiente
			  
			  delete getCurrent();
			  setCurrent(aux);
		  	
		  	#ifndef NDEBUG
			  	assert(old==getPreviousItem() and next==getCurrentItem());
			#endif
		 }
 
		#ifndef NDEBUG
		   assert(nItems()==aux-1);
		 #endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::removeAll()
{
  #ifndef NDEBUG
   assert(isEmpty()==false);
  #endif 

  gotoHead();
  std::cout<<"Numero de municipios a borrar:"<<nItems()<<"\n";
  while(isLastItem()==false)
  {
   remove();
   
  }
   remove();//ULTIMO ELEMENTO
  std::cout<<"\n";

  #ifndef NDEBUG
   assert(isEmpty()==true);
  #endif 
}