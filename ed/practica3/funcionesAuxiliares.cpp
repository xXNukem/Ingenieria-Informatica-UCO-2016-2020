/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 1
  \author Carlos de la Barera Perez
  \date   2018-3-7
*/


#include <iostream>

#include <fstream>

#include <string>

#include "funcionesAuxiliares.hpp"
          
#include "MonticuloMediciones.hpp"

#include "Medicion.hpp"

#include "macros.hpp"

#include "Fecha.hpp"



//MENU DE OPCIONES PRINCIPAL

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
	std::cout << "[1] Cargar fichero de monticulo" << std::endl;

	PLACE(posicion++,10);
	std::cout << "[2] Guardar fichero de monticulo " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[3] Ver datos de monticulo " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[4] Mostrar monticulo ordenado " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[5] Insertar nueva precipitacion " << std::endl;

	PLACE(posicion++,10);
  	std::cout << "[6] Generar grafico circular" << std::endl;

  	PLACE(posicion++,10);
  	std::cout << "[7] Generar grafico de barras" << std::endl;

	PLACE(posicion++,10);
  	std::cout << "[8] Borrar todas las mediciones del monticulo " << std::endl; 

	PLACE(posicion++,10);
  	std::cout << "[9] Borrar mediciones del monticulo " << std::endl; 

  	PLACE(posicion++,10);
  	std::cout << "[10] Buscar precipitacion por fecha " << std::endl; 

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

bool ed::cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo) 
{
  	std::ifstream ifs(nombreFichero.c_str());
	ed::Medicion m;


	if(ifs)
	{
		while(ifs>>m)
		{
			monticulo.insert(m);
		}
		ifs.close();

		return true;

	}
	else
	{
		return false;
	}


}


void ed::grabarMonticuloEnFichero(std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo)
{
 
	ed::Medicion m;
	ed::MonticuloMediciones aux;
	aux=monticulo;

	if(monticulo.size()!=0)
	{
		std::ofstream f(nombreFichero.c_str());

		for (int i=0;i<monticulo.size();i++)
		{
			m=aux.top();

			f<<m.getFecha()<<" "<<m.getPrecipitacion()<<"\n";

			aux.remove();
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

void ed::datosMonticulo(ed::MonticuloMediciones const &monticulo)
{

	ed::MonticuloMediciones aux;
	aux=monticulo;
	int fechasRegistradas;
	ed::Fecha ff;
	float p=0.0;
	ed::Medicion m;
	int dias=0;
	float mediaPrecipitacion,precipitacionDia=0;
	float enero=0,febrero=0,marzo=0.0,abril=0,mayo=0,junio=0,julio=0,agosto=0,septiembre=0,octubre=0,noviembre=0,diciembre=0;
	float mEnero,mFebrero,mMarzo,mAbril,mMayo,mJunio,mJulio,mAgosto,mSeptiembre,mOctubre,mNoviembre,mDiciembre;
		if(monticulo.isEmpty()==true)
		{
			std::cout<<BIRED<<"No existen datos en el monticulo"<<"\n";
		}
		else
		{
			fechasRegistradas=monticulo.size();
			m=monticulo.top();
			ff=m.getFecha();
			p=m.getPrecipitacion();

				for (int i=0;i<monticulo.size();i++)
				{
					m=aux.top();

						if(m.getPrecipitacion()>0)
						{
							dias++;
						}

					precipitacionDia=precipitacionDia+m.getPrecipitacion();

						if(m.getFecha().getMes()==1)
						{
							enero=enero+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==2)
						{
							febrero=febrero+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==3)
						{
							marzo=marzo+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==4)
						{
							abril=abril+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==5)
						{
							mayo=mayo+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==6)
						{
							junio=junio+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==7)
						{
							julio=julio+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==8)
						{
							agosto=agosto+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==9)
						{
							septiembre=septiembre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==10)
						{
							octubre=octubre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==11)
						{
							noviembre=noviembre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==12)
						{
							diciembre=diciembre+m.getPrecipitacion();
						}

						aux.remove();
				}

				mEnero=enero/31;

					if (( ff.getAgno() % 4 == 0) and ( (not (ff.getAgno() % 100 == 0)) or  (ff.getAgno() % 400 == 0))) 
					{
						mFebrero=febrero/29;
					}
					else
					{
						mFebrero=febrero/28;
					}
				mMarzo=marzo/31;
				mAbril=abril/30;
				mMayo=mayo/31;
				mJunio=junio/30;
				mJulio=julio/31;
				mAgosto=agosto/31;
				mSeptiembre=septiembre/30;
				mOctubre=octubre/31;
				mNoviembre=noviembre/30;
				mDiciembre=diciembre/31;


			mediaPrecipitacion=precipitacionDia/monticulo.size();

			std::cout<<BIGREEN<<"Numero de registros: "<<BIBLUE<<fechasRegistradas<<"\n";
			std::cout<<BIGREEN<<"Fecha de máxima precipitacion: "<<BIBLUE<< ff<<"\n";
			std::cout<<BIGREEN<<"Maxima precipitacion registrada: "<<BIBLUE<<p<<"\n";
			std::cout<<BIGREEN<<"Numero de dias lluviosos: "<<BIBLUE<<dias<<"\n";
			std::cout<<BIGREEN<<"Media global de precipitaciones: "<<BIBLUE<<mediaPrecipitacion<<"\n";
			std::cout<<BIGREEN<<"Media por mes de precipitaciones: "<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Enero: "<<BIBLUE<<mEnero<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Febrero: "<<BIBLUE<<mFebrero<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Marzo: "<<BIBLUE<<mMarzo<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Abril: "<<BIBLUE<<mAbril<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Mayo: "<<BIBLUE<<mMayo<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Junio: "<<BIBLUE<<mJunio<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Julio: "<<BIBLUE<<mJulio<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Agosto: "<<BIBLUE<<mAgosto<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Septiembre: "<<BIBLUE<<mSeptiembre<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Octubre: "<<BIBLUE<<mOctubre<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Noviembre: "<<BIBLUE<<mNoviembre<<RESET<<"\n";
				std::cout<<"\t"<<BIYELLOW<<"Diciembre: "<<BIBLUE<<mDiciembre<<RESET<<"\n";
		}

	
}
 
void ed::insertarPrecipitacion(ed::MonticuloMediciones &monticulo)
{
	ed::Medicion m;
	ed::Fecha f;
	float p;
		f.leerFecha();
	
			std::cout<<BIGREEN<<"Escribe la precipitacion: "<<BIYELLOW<<"\n";
			std::cin>>p;
			m.setPrecipitacion(p);
			m.setFecha(f);

			monticulo.insert(m);

}

void ed::generarArbolGrafico(ed::MonticuloMediciones const &monticulo)
{
	
	ed::MonticuloMediciones aux;
	aux=monticulo;
	std::string cadena;
	if(monticulo.size()==0)
	{
		  std::cout<<RED<<"No hay datos para poder generar el grafico."<<RESET<<std::endl;
		  return;
 	}	
 	else
 	{ 
 			float enero=0,febrero=0,marzo=0.0,abril=0,mayo=0,junio=0,julio=0,agosto=0,septiembre=0,octubre=0,noviembre=0,diciembre=0;
 			ed::Medicion m;
 			for (int i=0;i<monticulo.size();i++)
				{
					m=aux.top();

						if(m.getFecha().getMes()==1)
						{
							enero=enero+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==2)
						{
							febrero=febrero+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==3)
						{
							marzo=marzo+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==4)
						{
							abril=abril+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==5)
						{
							mayo=mayo+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==6)
						{
							junio=junio+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==7)
						{
							julio=julio+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==8)
						{
							agosto=agosto+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==9)
						{
							septiembre=septiembre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==10)
						{
							octubre=octubre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==11)
						{
							noviembre=noviembre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==12)
						{
							diciembre=diciembre+m.getPrecipitacion();
						}
					aux.remove();
				}

  	//creo un fichero arbol.csv y le meto la cabecera
  	std::ofstream h("grafico1.csv");

  std::ofstream html("grafico1.html");
  html<<"<!DOCTYPE HTML><html><head><script>window.onload = function() {var chart = new CanvasJS.Chart('chartContainer', {animationEnabled: true,title: {text: 'GRAFICO MADE BY CARLOS DE LA BARRERA PEREZ'},data: [{type: 'pie',startAngle: 240,yValueFormatString: '##0.00\'%\'',indexLabel: '{label} {y}',";
  html<<"dataPoints: [";
  html<<"{y: "<<enero<<", label: 'Enero'},{y: "<<febrero<<", label: 'Febrero'},{y: "<<marzo<<", label: 'Marzo'},{y: "<<abril<<", label: 'Abril'},{y: "<<mayo<<", label: 'Mayo'},{y: "<<junio<<", label: 'Junio'},{y: "<<julio<<", label: 'Julio'},{y: "<<agosto<<", label: 'Agosto'},{y: "<<septiembre<<", label: 'Septiembre'},{y: "<<octubre<<", label: 'Octubre'},{y: "<<noviembre<<", label: 'Noviembre'},{y: "<<diciembre<<", label: 'Diciembre'}]";
  html<<"}]});chart.render();}</script></head><body><div id='chartContainer' style='height: 370px; width: 100%;'></div><script src='https://canvasjs.com/assets/script/canvasjs.min.js'></script></body></html>";
  html.close();
	  std::cout<<BIGREEN<<"Archivo 'grafico1.html' generado con exito"<<RESET<<std::endl;

 }
 

}

void ed::generarArbolGrafico2(ed::MonticuloMediciones const &monticulo)//No funciona
{
	if(monticulo.isEmpty()==true)
	{
		std::cout<<BIRED<<"No hay datos para realizar el gráfico"<<RESET<<"\n";
	}
	else
	{
		ed::Medicion m;
		ed::MonticuloMediciones aux;
		aux=monticulo;
			float enero=0,febrero=0,marzo=0.0,abril=0,mayo=0,junio=0,julio=0,agosto=0,septiembre=0,octubre=0,noviembre=0,diciembre=0;

 			for (int i=0;i<monticulo.size();i++)
				{
					m=aux.top();

						if(m.getFecha().getMes()==1)
						{
							enero=enero+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==2)
						{
							febrero=febrero+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==3)
						{
							marzo=marzo+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==4)
						{
							abril=abril+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==5)
						{
							mayo=mayo+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==6)
						{
							junio=junio+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==7)
						{
							julio=julio+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==8)
						{
							agosto=agosto+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==9)
						{
							septiembre=septiembre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==10)
						{
							octubre=octubre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==11)
						{
							noviembre=noviembre+m.getPrecipitacion();
						}
						if(m.getFecha().getMes()==12)
						{
							diciembre=diciembre+m.getPrecipitacion();
						}
					aux.remove();
				}

			std::ofstream html("grafico2.html");

			html<<"<!DOCTYPE HTML><html><head> <script>window.onload = function () {var chart = new CanvasJS.Chart('chartContainer', {animationEnabled: true,title:{text:'GRAFICO MADE BY CARLOS DE LA BARRERA PEREZ'},axisX:{interval: 1},axisY2:{interlacedColor: 'rgba(1,77,101,.2)',gridColor: 'rgba(1,77,101,.1)',title: 'Cantidad de lluvia por mes'},data: [{type: 'bar',name: 'companies',axisYType: 'secondary',color: '#014D65',dataPoints: [";

			html<<"{ y: "<<enero<<", label: 'Enero' },{ y: "<<febrero<<", label: 'Febrero' },{ y: "<<marzo<<", label: 'Marzo' },{ y: "<<abril<<", label: 'Abril' },{ y: "<<mayo<<", label: 'Mayo' },{ y: "<<junio<<", label: 'Junio' },{ y: "<<julio<<", label: 'Julio' },{ y: "<<agosto<<", label: 'Agosto' },{ y: "<<septiembre<<", label: 'Septiembre' },{ y: "<<octubre<<", label: 'Octubre' },{ y: "<<noviembre<<", label: 'Noviembre' },{ y: "<<diciembre<<", label: 'Diciembre' }";

			html<<"]}]});chart.render();}</script></head><body><div id='chartContainer' style='height: 370px; width: 100%;'></div><script src='https://canvasjs.com/assets/script/canvasjs.min.js'></script></body></html>";
			html.close();
			


			  std::cout<<BIGREEN<<"Archivo 'grafico2.html' generado con exito"<<RESET<<std::endl;

	}
}


void ed::vaciarMonticulo(ed::MonticuloMediciones &monticulo)
{
	if(monticulo.isEmpty()==true)
	{
		std::cout<<BIRED<<"El monticulo ya se encuentra vacio"<<RESET<<"\n";
	}
	else
	{
		std::cout<<BIGREEN<<"Monticulo vaciado correctamente"<<RESET<<"\n";

		monticulo.removeAll();
	}
}

void ed::borrarMediciones(ed::MonticuloMediciones &monticulo)
{
	int nMediciones;
	ed::Medicion m;
	if(monticulo.isEmpty()==false)
	{
		std::cout<<BIYELLOW<<"Introduce el numero de mediciones que quieres borrar (0 para no borrar ninguna)"<<BIBLUE<<"\n";
		while(!(std::cin>>nMediciones) || (nMediciones>monticulo.size()-1) || (nMediciones<1))
	  	{ 
	  		if(nMediciones==0)
	  		{
	  			break;
	  		}
		 std::cin.clear();
		 std::cin.ignore(80, '\n');
		 std::cout<<RED<<"Icorrecto!!!"<<RESET<<std::endl;  
		 std::cout <<BIGREEN<< " No se pueden introducir caracteres ni un numero mayor o igual al tamaño ->"<<BIBLUE;
	  	}

		if(nMediciones<=monticulo.size())
		{
			for(int i=0;i<nMediciones;i++)
			{
				m=monticulo.top();
				std::cout<<BIGREEN<<"La medicion con fecha "<<BIBLUE<<m.getFecha()<<" y precipitacion "<<m.getPrecipitacion()<<BIGREEN<<" ha sido borrada"<<"\n";
				monticulo.remove();
			}
			std::getchar();
		}
		else
		{
			std::cout<<BIRED<<"Numero de mediciones a borrar incorrecto"<<RESET<<"\n";
			std::getchar();
		}
	}
	else
	{
		std::cout<<BIRED<<"El monticulo está vacio "<<RESET<<"\n";
	}
		
}

void ed::buscarFecha(ed::MonticuloMediciones const &monticulo)
{
	ed::MonticuloMediciones aux;
	ed::Fecha f;
	ed::Medicion m;
	ed::Medicion m2;
	aux=monticulo;
		if(monticulo.isEmpty()==true)
		{
			std::cout<<BIRED<<"El monticulo está vacio"<<RESET<<"\n";
		}
		else
		{
			f.leerFecha();
				for(int i=0;i<monticulo.size();i++)
				{
					m=aux.top();
						if(m.getFecha()==f)
						{
							m2=m;
						}
					aux.remove();
				}

					if(m2.getPrecipitacion()>0)
					{
						std::cout<<BIGREEN<<"El dia "<<BIBLUE<<m2.getFecha()<<BIGREEN<<" llovio la friolera de: "<<BIBLUE<< m2.getPrecipitacion() <<" litros"<<RESET<<"\n";
					}
					else
					{
						std::cout<<BIRED<<"Sin precipitacion registrada"<<RESET<<"\n";
					}
		}


	getchar();
}