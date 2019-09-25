#include "medicionMetodo.hpp"
#include "p1auxiliares.hpp"

void MedicionMetodo::setMinElementos(int x)
{
	_minElementos=x;
}

void MedicionMetodo::setMaxElementos(int x)
{
	_maxElementos=x;
}

void MedicionMetodo::setIncremento(int x)
{
	_incremento=x;
}

void MedicionMetodo::setRepeticion(int x)
{
	_repeticion=x;
}

int MedicionMetodo::getMinElementos()
{
	return _minElementos;
}

int MedicionMetodo::getMaxElementos()
{
	return _maxElementos;
}

int MedicionMetodo::getIncremento()
{
	return _incremento;
}

int MedicionMetodo::getRepeticion()
{
	return _repeticion;
}

bool MedicionMetodo::estaOrdenado(std::vector<int> &v)
{

	for(int i=0;i<v.size()-1;i++)
	{
		if(v[i]>v[i+1])
		{
			return false;
		}
	}

	return true;
}


void MedicionMetodo::leerDatosMedicion()
{
	int valorMinimo,valorMaximo,incremento,repeticion;

	std::cout<<BIYELLOW<<"Introduce los valores para el experimento: "<<std::endl;
	std::cout<<BIBLUE<<"Minimo de elementos del vector--> "<<BIGREEN;
	std::cin>>valorMinimo;
	/* while(!(std::cin>>valorMinimo) || (valorMinimo<1))
	  { 
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"Debe ser mayor que 1"<<RESET<<std::endl;  
		 std::cout <<BIBLUE<< "Minimo de elementos del vector--> "<<BIGREEN;
	  }*/
	setMinElementos(valorMinimo);
	std::cout<<BIBLUE<<"Maximo de elementos del vector--> "<<BIGREEN;
	std::cin>>valorMaximo;
	/*while(!(std::cin>>valorMaximo) || (valorMaximo<valorMinimo))
	  { 
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"Debe ser mayor que el valor minimo"<<RESET<<std::endl;  
		 std::cout <<BIBLUE<< "Maximo de elementos del vector--> "<<BIGREEN;
	  }*/
	setMaxElementos(valorMaximo);
	std::cout<<BIBLUE<<"Incremento--> "<<BIGREEN;
	std::cin>>incremento;
	 /*while(!(std::cin>>incremento) || (incremento<0))
	  { 
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"Debe ser mayor que 0"<<RESET<<std::endl;  
		 std::cout <<BIBLUE<< "Incremento--> "<<BIGREEN;
	  }*/
	setIncremento(incremento);
	std::cout<<BIBLUE<<"Repeticion por incremento--> "<<BIGREEN;
	std::cin>>repeticion;
	/* while(!(std::cin>>repeticion) || (repeticion<0))
	  { 
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"Debe ser mayor que 0"<<RESET<<std::endl;  
		 std::cout <<BIBLUE<< "Repeticion por incremento--> "<<BIGREEN;
	  }*/
	setRepeticion(repeticion);

}

void MedicionMetodo::metodoInsercionBinaria()
{
	bool sofisticado=false;
	MedicionMetodo m;
	m.leerDatosMedicion();
	int numElmentosTiempo=((m.getMaxElementos()-m.getMinElementos())/m.getIncremento())+1;
	_vectorDatos.resize(numElmentosTiempo);
	datos d;
	_vectorDatos.clear();

	Clock time;
	for(int i=m.getMinElementos();i<=m.getMaxElementos();i=i+m.getIncremento())
	{			
		d._time=0;

			for(int j=0;j<m.getRepeticion();j++)
			{
					v.clear();
					m.setVector(v, i);
					time.start();
					m.ordenarInsercionBinaria(v,i);
						if (time.isStarted())
						{
							time.stop();
								/*Aserto para comprobar que está ordenado
								#ifndef NDEBUG
									assert(m.estaOrdenado(v)==true);
								#endif
								*/
							d._time+=time.elapsed();
							d._tam=i;
						}
			}
			d._time=d._time/m.getRepeticion();
			_vectorDatos.push_back(d);
	}

				generarMatriz(3,3);
				tiempoEstimado(_vectorDatos,sofisticado, _matrizSoluciones);
				grabarFichero(_vectorDatos);
				std::cout<<BIGREEN<<"Coeficiente de determinacion: "<<BIBLUE<<std::endl;
				std::cout<<getCoeficienteDeterminacion(_vectorDatos)<<RESET<<std::endl;
					std::cout<<BIGREEN<<"ECUACION:"<<std::endl<<RESET;
					std::cout<<BIYELLOW<<_matrizSoluciones[0][0]<<"+"<<_matrizSoluciones[1][0]<<"*N+"<<_matrizSoluciones[2][0]<<"*N^2"<<std::endl<<RESET;
				calcularDias( _matrizSoluciones, sofisticado);
				
				
				getchar();
}

void MedicionMetodo::ordenarInsercionBinaria(std::vector<int> &v, int tam)
{ 
	int i,j,aux,izq,der,m;
	//MedicionMetodo n;
    for(i=1;i<tam;i++)
    {
        aux = v[i];
        izq=0;
        der=i-1;
            while(izq<=der)
            {
            m=((izq+der)/2);
           		if (aux<v[m])
                der=m-1;
            	else
                izq=m+1;              
            }
        j=i-1;
            while(j>=izq)
            {
            	v[j+1]=v[j];
                j=j-1;
            }
        v[izq]=aux;
   	}
    //n.getVector(v);

}


void MedicionMetodo::metodoMonticulo()
{
	bool sofisticado=true;
	MedicionMetodo m;
	m.leerDatosMedicion();
	int numElmentosTiempo=((m.getMaxElementos()-m.getMinElementos())/m.getIncremento())+1;
	_vectorDatos.resize(numElmentosTiempo);
	datos d;
	_vectorDatos.clear();

	Clock time;
	for(int i=m.getMinElementos();i<=m.getMaxElementos();i=i+m.getIncremento())
	{			
		d._time=0;

			for(int j=0;j<m.getRepeticion();j++)
			{
					v.clear();
					m.setVector(v, i);
					time.start();
					m.ordenarMonticulo(v,i);
						if (time.isStarted())
						{
							time.stop();
								//Aserto para comprobar que está ordenado
								/*
								#ifndef NDEBUG
									assert(m.estaOrdenado(v)==true);
								#endif
								*/
							d._time+=time.elapsed();
							d._tam=i*log(i);
							//std::cout << "Han pasado " << time.elapsed() << " microsegundos \n";
						}
			}
			d._time=d._time/m.getRepeticion();
			_vectorDatos.push_back(d);
	}


				generarMatriz(2,2);
				tiempoEstimado(_vectorDatos,sofisticado, _matrizSoluciones);
				grabarFichero(_vectorDatos);
				std::cout<<BIGREEN<<"Coeficiente de determinacion: "<<BIBLUE<<std::endl;
				std::cout<<getCoeficienteDeterminacion(_vectorDatos)<<RESET<<std::endl;
					std::cout<<BIGREEN<<"ECUACION:"<<std::endl<<RESET;
					std::cout<<BIYELLOW<<_matrizSoluciones[0][0]<<"+"<<_matrizSoluciones[1][0]<<"*N*log(N)"<<std::endl<<RESET;
				calcularDias( _matrizSoluciones, sofisticado);

				
				
				getchar();

}

void MedicionMetodo::ordenarMonticulo(std::vector<int> &v,int size)
{
		//Me veo obligado a usar este metodo para la ordenacion por monticulo porque los algoritmos que hay en internet van muy lentos, el algoritmo que encontre más eficiente lo he dejado comentado
		std::make_heap(v.begin(), v.end());
		std::sort_heap (v.begin(),v.end());

	/*

	heapify(v, 0, size-1);
    int high = size - 1;
    while (high > 0)
    {

        int tmp = v[high];
        v[high] = v[0];
        v[0] = tmp;
        --high;
  
       shiftRight(v, 0, high);
    }
	*/
}

/*
 void MedicionMetodo::shiftRight(std::vector<int> &v, int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;

        if (v[swapIdx] < v[leftChild])
        {
            swapIdx = leftChild;
        }

        if ((rightChild <= high) && (v[swapIdx] < v[rightChild]))
        {
            swapIdx = rightChild;
        }

        if (swapIdx != root)
        {
            int tmp = v[root];
            v[root] = v[swapIdx];
            v[swapIdx] = tmp;

            root = swapIdx;
        }
        else
        {
            break;
        }
    }
    return;
}
void MedicionMetodo::heapify(std::vector<int> &v, int low, int high)
{
    int midIdx = (high - low -1)/2;
    while (midIdx >= 0)
    {
        shiftRight(v, midIdx, high);
        --midIdx;
    }
    return;
}

*/
void MedicionMetodo::setVector(std::vector<int> &v, int i)
{
		for(int j=0;j<i;j++)
		{
			int aleatorio=rand()%10000;
			v.push_back(aleatorio);
		}

}

void MedicionMetodo::getVector(std::vector<int> &v)
{
	for(int i=0;i<v.size();i++)
	{

		std::cout<<BIRED<<" "<<v.at(i)<<" ";
	}
	std::cout<<std::endl;
}

double MedicionMetodo::sumatorio(std::vector<datos> &v, int a, int b)
{
	double resultado=0;

		for(int i=0;i<v.size();i++)
		{
			resultado+=(pow(v[i]._tam,a))*(pow(v[i]._time,b));
		}

	return resultado;
}

void MedicionMetodo::generarMatriz(int nFil, int nCol)
{
	//Reserva de memoria para las matrizes
		_matrizCoeficientes = vector< vector< double > >(nFil, vector< double >(nCol));
		_matrizIndependientes = vector< vector< double > >(nFil, vector< double >(1));
		_matrizSoluciones=vector< vector< double > >(nFil, vector< double >(1));


			for(int i=0;i<nFil;i++)
			{
				for(int j=0;j<nCol;j++)
				{
					_matrizCoeficientes[i][j]=sumatorio(_vectorDatos,i+j,0);
				}
			}

			for(int i=0;i<nFil;i++)
			{
				_matrizIndependientes[i][0]=sumatorio(_vectorDatos,i,1);
			}

			mostrarSoluciones();
}

void MedicionMetodo::mostrarSoluciones()
{
	resolverSistemaEcuaciones(_matrizCoeficientes, _matrizIndependientes, _matrizCoeficientes.size(), _matrizSoluciones);

	std::cout<<BIGREEN<<"SOLUCIONES"<<std::endl<<RESET;

	for(int i=0;i<_matrizSoluciones.size();i++)
		{
			std::cout<<" "<<_matrizSoluciones[i][0]<<" ";
		}
		std::cout<<std::endl;
}

void MedicionMetodo::tiempoEstimado(std::vector<datos> &_vectorDatos, bool sofisticado, std::vector<std::vector<double> > _soluciones)
{
	//Tiempo resultado de aplicar la ecuacion a las soluciones, se queda en la tercera columna del fichero

		for(int i=0;i<_vectorDatos.size();i++)
		{
			if(sofisticado==false)
			{		
				_vectorDatos[i]._time_est=_soluciones[0][0]+_soluciones[1][0]*_vectorDatos[i]._tam+_soluciones[2][0]*pow(_vectorDatos[i]._tam,2);
			}
			else if (sofisticado==true)
			{
				_vectorDatos[i]._time_est=_soluciones[0][0]+_soluciones[1][0]*_vectorDatos[i]._tam;
			}
		}
}

double MedicionMetodo::getCoeficienteDeterminacion(std::vector <datos>const &_vectorDatos)
{
	double mt, me, st, se, ste, denom, r;

 // Calcula la media de las dos series x[], y[] /

	 mt = 0;
	 me = 0;

		 for (int i = 0; i < (int)_vectorDatos.size(); i++) 
		 {

		  mt += _vectorDatos[i]._time;
		  me += _vectorDatos[i]._time_est;

		 }

	 mt /= (int)_vectorDatos.size();
	 me /= (int)_vectorDatos.size();

 //Calculo de las varianzas de ambos tiempos

		 st = 0;
		 se = 0;

		 for (int i = 0; i < (int)_vectorDatos.size(); i++) 
		 {

		  st += (_vectorDatos[i]._time - mt) * (_vectorDatos[i]._time - mt);
		  se += (_vectorDatos[i]._time_est - me) * (_vectorDatos[i]._time_est - me);

		 }
		 //sacamos el denominador con las varianzas
 			denom = sqrt (st * se);

 // Calcula la correlación de las series 
 

 			ste = 0;

		 for (int i = 0; i < (int)_vectorDatos.size(); i++) 
		 {

		  ste += (_vectorDatos[i]._time - mt) * (_vectorDatos[i]._time_est - me);

		 }

		 r = ste / denom;

 return r;
}

void MedicionMetodo::calcularDias(std::vector<std::vector<double> > _matrizSoluciones, bool sofisticado)
{
	std::string opcion;
	cout<<BIBLUE<<"Quieres hacer una estimacion en dias? Pulsar 'n' para no."<<std::endl<<RESET;
	cin>>opcion;
	long long int tam=1; //pa poder poner numeros de 64 bites
	double totalMicrosegundos=0.0;

	//Para poder calcular los dias no es mas que sustituir en la N de la ecuacion un valor
		if(opcion!="n")
		{
			while(tam!=0)
			{
				cout<<BIBLUE<<"Introduce el tamaño del ejemplar, 0 para salir"<<std::endl<<RESET;
				cin>>tam;
						if(sofisticado==false)
						{		
							totalMicrosegundos=_matrizSoluciones[0][0]+_matrizSoluciones[1][0]*tam+_matrizSoluciones[2][0]*pow(tam,2);

							totalMicrosegundos=(pow(10,-6)*totalMicrosegundos)/86400;

							cout<<BIGREEN<<"Pasaran "<<(int)totalMicrosegundos<<" dias"<<std::endl<<RESET;
						}
						else if (sofisticado==true)
						{
							totalMicrosegundos=_matrizSoluciones[0][0]+_matrizSoluciones[1][0]*(tam*log(tam));

							totalMicrosegundos=(pow(10,-6)*totalMicrosegundos)/86400;

							cout<<BIGREEN<<"Pasaran "<<(int)totalMicrosegundos<<" dias"<<std::endl<<RESET;
						}
			}

		}

}