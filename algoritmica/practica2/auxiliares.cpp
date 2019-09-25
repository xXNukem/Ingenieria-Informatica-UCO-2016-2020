/*!
   \file  auxiliares.cpp
   \brief Dichero que contiene las funciones auxiliares para lanzar los algoritmos, grabar en el fichero o calcular los tiempos
*/


#include "auxiliares.hpp"

int menu()
{
	int opcion, posicion;

	// Se muestran las opciones del menú
	posicion = 2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(posicion++, 10);
	std::cout << BIBLUE;
	std::cout << "Programa principal | Opciones del menú   ";
	std::cout << RESET;

	posicion++;
	PLACE(posicion++, 10);
	std::cout << "[1] Combinatoria con recursividad " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[2] Combinatoria con recursividad y tablas " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[3] Combinatoria sin recursividad " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[4] Torres de Hanoi " << std::endl;



	posicion++;
	PLACE(posicion++, 20);
	std::cout << BIYELLOW;
	std::cout << "Opción: ";
	std::cout << RESET;
	std::cin >> opcion;

	std::cin.ignore();

	return opcion;
}

void ejecutarAlgoritmo(int opcion)
{
	Combinatoria c;
	Clock time;
	std::vector<double> _tablaValores;
	double resultado;
	std::vector<double> n;
	std::vector<double> naux;
	std::vector<float> t_practico;
	std::vector<float> t_teorico;
	n.clear();
	t_practico.clear();
	t_teorico.clear();
	SistemaMatrices m;
	std::vector<std::vector<double> > matrizSoluciones;
	float cD;
	double media = 0;
	int repeticiones = 0;

	if (opcion == 1)
	{
		c.leerDatos();
		std::cout << BIRED << "Computando... ESPERA POR FAVOR" << RESET << std::endl;
		for (int i = c.getNMin(); i <= c.getNMax(); i++)
		{
			n.push_back(i);
			naux.push_back(pow(2, i));
			time.start();
			for (int j = 0; j < c.getRepeticiones(); j++)
			{
				for (int k = 0; k <= i; k++)
				{
					resultado = c.combinatoriaRecursiva(i, k);
					//std::cout<<BIRED<<resultado<<std::endl;
				}
				if (time.isStarted())
				{
					time.stop();
					media += time.elapsed();
					//t_practico.push_back(time.elapsed());
					//std::cout<<BIGREEN<<"Han pasado "<<time.elapsed()<<" microsegundos"<<RESET<<std::endl;
				}

			}
			media = media / c.getRepeticiones();
			t_practico.push_back(media);
			resultado = 0;
		}
		std::cout << BIGREEN << "COMPUTADO!" << RESET << std::endl;
		m.setSistema(naux, t_practico, 2, 2);
		matrizSoluciones = std::vector<std::vector<double> >(2, std::vector< double >(1));
		resolverSistemaEcuaciones(m.getMatrizCoeficientes(), m.getMatrizIndependientes(),
		                          m.getMatrizCoeficientes().size(), matrizSoluciones);
		t_teorico = calcularTiempoTeorico(matrizSoluciones, n, opcion);
		std::cout << BIGREEN << "SOLUCIONES" << std::endl << RESET;

		for (int i = 0; i < matrizSoluciones.size(); i++)
		{
			std::cout << BIRED << " " << matrizSoluciones[i][0] << " ";
		}
		std::cout << RESET << std::endl;
		cD = getCoeficienteDeterminacion(t_practico, t_teorico);
		std::cout << BIBLUE << "Coeficiente de determinacion: " << BIYELLOW << cD << RESET << std::endl;
		std::cout << BIGREEN << "Ecuacion: " << BIBLUE << matrizSoluciones[0][0] << BIYELLOW << "+" <<
		          BIBLUE << matrizSoluciones[1][0] << BIYELLOW << "*2^n" << RESET << std::endl;
		grabarFichero(n, t_practico, t_teorico);
		calcularDias(matrizSoluciones, opcion);
	}
	if (opcion == 2)
	{
		c.leerDatos();
		std::cout << BIRED << "Computando... ESPERA POR FAVOR" << RESET << std::endl;
		for (int i = c.getNMin(); i <= c.getNMax(); i++)
		{
			n.push_back(i);
			time.start();
			for (int j = 0; j < c.getRepeticiones(); j++)
			{
				for (int k = 0; k <= i; k++)
				{
					resultado = c.combinatoriaTablaValores(i, k, _tablaValores);
					//std::cout<<BIRED<<resultado<<std::endl;
				}
				if (time.isStarted())
				{
					time.stop();
					media += time.elapsed();
					//t_practico.push_back(time.elapsed());
					//std::cout<<BIGREEN<<"Han pasado "<<time.elapsed()<<" microsegundos"<<RESET<<std::endl;
				}
			}
			media = media / c.getRepeticiones();
			t_practico.push_back(media);
			resultado = 0;
			_tablaValores.clear();
		}
		std::cout << BIGREEN << "COMPUTADO!" << RESET << std::endl;
		m.setSistema(n, t_practico, 3, 3);
		matrizSoluciones = std::vector<std::vector<double> >(3, std::vector< double >(1));
		resolverSistemaEcuaciones(m.getMatrizCoeficientes(), m.getMatrizIndependientes(),
		                          m.getMatrizCoeficientes().size(), matrizSoluciones);
		std::cout << BIGREEN << "SOLUCIONES" << std::endl << RESET;

		for (int i = 0; i < matrizSoluciones.size(); i++)
		{
			std::cout << BIRED << " " << matrizSoluciones[i][0] << " ";
		}
		std::cout << RESET << std::endl;
		t_teorico = calcularTiempoTeorico(matrizSoluciones, n, opcion);
		cD = getCoeficienteDeterminacion(t_practico, t_teorico);
		std::cout << BIBLUE << "Coeficiente de determinacion: " << BIYELLOW << cD << RESET << std::endl;
		std::cout << BIGREEN << "Ecuacion: " << BIBLUE << matrizSoluciones[0][0] << "+" <<
		          matrizSoluciones[1][0] << BIYELLOW << "*n+" << BIBLUE << matrizSoluciones[2][0] << BIYELLOW <<
		          "*n²" << RESET << std::endl;
		t_teorico = calcularTiempoTeorico(matrizSoluciones, n, opcion);
		grabarFichero(n, t_practico, t_teorico);
		calcularDias(matrizSoluciones, opcion);
	}
	if (opcion == 3)
	{
		c.leerDatos();
		std::cout << BIRED << "Computando... ESPERA POR FAVOR" << RESET << std::endl;
		for (int i = c.getNMin(); i <= c.getNMax(); i++)
		{
			n.push_back(i);
			time.start();
			for (int j = 0; j < c.getRepeticiones(); j++)
			{
				for (int k = 0; k <= i; k++)
				{
					resultado = c.combinatoriaNoRecursiva(i, k);
					//std::cout<<BIRED<<resultado<<std::endl;
				}
				if (time.isStarted())
				{
					time.stop();
					media += time.elapsed();
					//t_practico.push_back(time.elapsed());
					//std::cout<<BIGREEN<<"Han pasado "<<time.elapsed()<<" microsegundos"<<RESET<<std::endl;
				}
			}
			media = media / c.getRepeticiones();
			t_practico.push_back(media);
			resultado = 0;
		}
		std::cout << BIGREEN << "COMPUTADO!" << RESET << std::endl;
		m.setSistema(n, t_practico, 3, 3);
		matrizSoluciones = std::vector<std::vector<double> >(3, std::vector< double >(1));
		resolverSistemaEcuaciones(m.getMatrizCoeficientes(), m.getMatrizIndependientes(),
		                          m.getMatrizCoeficientes().size(), matrizSoluciones);
		std::cout << BIGREEN << "SOLUCIONES" << std::endl << RESET;

		for (int i = 0; i < matrizSoluciones.size(); i++)
		{
			std::cout << BIRED << " " << matrizSoluciones[i][0] << " ";
		}
		std::cout << RESET << std::endl;

		t_teorico = calcularTiempoTeorico(matrizSoluciones, n, opcion);
		cD = getCoeficienteDeterminacion(t_practico, t_teorico);
		std::cout << BIBLUE << "Coeficiente de determinacion: " << BIYELLOW << cD << RESET << std::endl;
		std::cout << BIGREEN << "Ecuacion: " << BIBLUE << matrizSoluciones[0][0] << "+" <<
		          matrizSoluciones[1][0] << BIYELLOW << "*n+" << BIBLUE << matrizSoluciones[2][0] << BIYELLOW <<
		          "*n²" << RESET << std::endl;
		grabarFichero(n, t_practico, t_teorico);
		calcularDias(matrizSoluciones, opcion);
	}
	if (opcion == 4)
	{
		int discos = 0, minDiscos = 1;
		double movimientos = 0;
		std::string o;
		std::cout << BIBLUE << "Modo texto=t - Modo medir tiempo=m --> " << BIYELLOW;
		std::cin >> o;
		if (o == "m")
		{
			std::cout << BIBLUE << "Introduce el minimo de discos --> " << BIYELLOW;
			std::cin >> minDiscos;
			std::cout << BIBLUE << "Introduce el maximo de discos --> " << BIYELLOW;
			std::cin >> discos;
			std::cout << BIBLUE << "Introduce el número de repeticiones --> " << BIYELLOW;
			std::cin >> repeticiones;
			std::cout << BIGREEN << "Ejecutando las torres de hanoi de " << BIBLUE << minDiscos << BIGREEN <<
			          " hasta " << BIBLUE << discos << BIGREEN" discos " << RESET << std::endl;
			std::cout << BIRED << "Computando... ESPERA POR FAVOR" << RESET << std::endl;
			for (int i = minDiscos; i <= discos; i++)
			{
				naux.push_back(pow(2, i));
				n.push_back(i);
				time.start();
				for (int j = 0; j < repeticiones; j++)
				{
					movimientos += torresHanoi(i);

					if (time.isStarted())
					{
						time.stop();
						media += time.elapsed();
						//t_practico.push_back(time.elapsed());
						//std::cout<<BIGREEN<<"Han pasado "<<time.elapsed()<<" microsegundos"<<RESET<<std::endl;
					}
				}
				//std::cout<<BIGREEN<<"Para "<<BIYELLOW<<i<<BIGREEN<<" discos han pasado "<<BIYELLOW<<time.elapsed()<<BIGREEN<<" microsegundos con "<<BIYELLOW<<repeticiones<<BIGREEN<<" repeticiones"<<RESET<<std::endl;
				media = media / repeticiones;
				t_practico.push_back(media);
			}
			std::cout << BIGREEN << "COMPUTADO!" << RESET << std::endl;
			std::cout << BIGREEN << "Se han llevado a cabo " << BIBLUE << movimientos << BIGREEN" movimientos "
			          << RESET << std::endl;
			m.setSistema(naux, t_practico, 2, 2);
			matrizSoluciones = std::vector<std::vector<double> >(2, std::vector< double >(1));
			resolverSistemaEcuaciones(m.getMatrizCoeficientes(), m.getMatrizIndependientes(),
			                          m.getMatrizCoeficientes().size(), matrizSoluciones);
			std::cout << BIGREEN << "SOLUCIONES" << std::endl << RESET;

			for (int i = 0; i < matrizSoluciones.size(); i++)
			{
				std::cout << BIRED << " " << matrizSoluciones[i][0] << " ";
			}
			std::cout << RESET << std::endl;
			t_teorico = calcularTiempoTeorico(matrizSoluciones, n, opcion);
			cD = getCoeficienteDeterminacion(t_practico, t_teorico);
			std::cout << BIBLUE << "Coeficiente de determinacion: " << BIYELLOW << cD << RESET << std::endl;
			std::cout << BIGREEN << "Ecuacion: " << BIBLUE << matrizSoluciones[0][0] << BIYELLOW << "+" <<
			          BIBLUE << matrizSoluciones[1][0] << BIYELLOW << "*2^n" << RESET << std::endl;
			grabarFichero(n, t_practico, t_teorico);
			calcularDias(matrizSoluciones, opcion);
		}
		if (o == "t")
		{
			std::cout << BIBLUE << "Introduce el número de discos --> " << BIYELLOW;
			std::cin >> discos;
			ejecutarHanoiTexto(discos);
			//std::cout<<BIGREEN<<"Ejecutando las torres de hanoi para "<<BIBLUE<<discos<<BIGREEN" discos "<<RESET<<std::endl;
			//torresHanoiTexto(discos,1,3,2);


		}

	}

	getchar();
}

void grabarFichero(std::vector<double> const &n, std::vector<float> const &t_practico,
                   std::vector<float> const &t_teorico)
{
	std::string o;
	o = "Datos.txt";

	std::ofstream f(o.c_str());

	for (int i = 0; i < (int)n.size(); i++)
	{
		f << n[i] << "\t" << t_practico[i] << "\t " << t_teorico[i] << std::endl;
	}

	f.close();

}

std::vector<float> calcularTiempoTeorico(std::vector<std::vector<double> > & _matrizSoluciones,
        std::vector<double> & n, int & opcion)
{
	std::vector<float> t_teorico;
	float tiempo;

	for (int i = 0; i < n.size(); i++)
	{
		if (opcion == 1 || opcion == 4)
		{
			tiempo = _matrizSoluciones[0][0] + _matrizSoluciones[1][0] * pow(2, n[i]);
			t_teorico.push_back(tiempo);
		}
		else if (opcion == 2 || 3)
		{
			tiempo = _matrizSoluciones[0][0] + _matrizSoluciones[1][0] * n[i] + _matrizSoluciones[2][0] * pow(
			             n[i], 2);
			t_teorico.push_back(tiempo);

		}

	}

	return t_teorico;
}

void calcularDias(std::vector<std::vector<double> > _matrizSoluciones, int o)
{
	std::string opcion;
	cout << BIBLUE << "Quieres hacer una estimacion en dias? Pulsar 'n' para no." << std::endl << RESET;
	cin >> opcion;
	double tam = 1; //pa poder poner numeros de 64 bites
	double totalMicrosegundos = 0.0;
	double dias;
	double horas;
	double minutos;
	double segundos;
	double anos;

	//Para poder calcular los dias no es mas que sustituir en la N de la ecuacion un valor
	if (opcion != "n")
	{
		while (tam != 0)
		{
			cout << BIBLUE << "Introduce el tamaño del ejemplar, 0 para salir" << std::endl << RESET;
			cin >> tam;
			if (o == 1 || o == 4)
			{
				totalMicrosegundos = _matrizSoluciones[0][0] + _matrizSoluciones[1][0] * pow(2, tam);

				//totalMicrosegundos=(pow(10,-6)*totalMicrosegundos)/86400;//Conversion a dias
				totalMicrosegundos = totalMicrosegundos / pow(10, 6);
				segundos = fmod(totalMicrosegundos, 60);

				totalMicrosegundos = (totalMicrosegundos - segundos) / 60;
				minutos = fmod(totalMicrosegundos, 60);

				totalMicrosegundos = (totalMicrosegundos - minutos) / 60;
				horas = fmod(totalMicrosegundos, 24);

				totalMicrosegundos = (totalMicrosegundos - horas) / 24;
				dias = fmod(totalMicrosegundos, 365);

				anos = totalMicrosegundos = (totalMicrosegundos - dias) / 365;

				std::cout << BIBLUE << "AÑOS: " << BIYELLOW << anos << std::endl << RESET;
				std::cout << BIBLUE << "DIAS: " << BIYELLOW << dias << std::endl << RESET;
				std::cout << BIBLUE << "HORAS: " << BIYELLOW << horas << std::endl << RESET;
				std::cout << BIBLUE << "MINUTOS: " << BIYELLOW << minutos << std::endl << RESET;
				std::cout << BIBLUE << "SEGUNDOS: " << BIYELLOW << segundos << std::endl << RESET;
				std::cout << BIBLUE << "MICROSEGUNDOS: " << BIYELLOW << totalMicrosegundos << std::endl << RESET;

			}
			else if (o == 2 || o == 3)
			{
				totalMicrosegundos = _matrizSoluciones[0][0] + _matrizSoluciones[1][0] * tam +
				                     _matrizSoluciones[2][0] * pow(tam, 2);

				//totalMicrosegundos=(pow(10,-6)*totalMicrosegundos)/86400;//Conversion a dias
				totalMicrosegundos = totalMicrosegundos / pow(10, 6);
				segundos = fmod(totalMicrosegundos, 60);

				totalMicrosegundos = (totalMicrosegundos - segundos) / 60;
				minutos = fmod(totalMicrosegundos, 60);

				totalMicrosegundos = (totalMicrosegundos - minutos) / 60;
				horas = fmod(totalMicrosegundos, 24);

				totalMicrosegundos = (totalMicrosegundos - horas) / 24;
				dias = fmod(totalMicrosegundos, 365);

				anos = totalMicrosegundos = (totalMicrosegundos - dias) / 365;

				std::cout << BIBLUE << "AÑOS: " << BIYELLOW << anos << std::endl << RESET;
				std::cout << BIBLUE << "DIAS: " << BIYELLOW << dias << std::endl << RESET;
				std::cout << BIBLUE << "HORAS: " << BIYELLOW << horas << std::endl << RESET;
				std::cout << BIBLUE << "MINUTOS: " << BIYELLOW << minutos << std::endl << RESET;
				std::cout << BIBLUE << "SEGUNDOS: " << BIYELLOW << segundos << std::endl << RESET;
				std::cout << BIBLUE << "MICROSEGUNDOS: " << BIYELLOW << totalMicrosegundos << std::endl << RESET;
			}
		}

	}

}