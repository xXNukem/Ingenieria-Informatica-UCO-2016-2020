/*!
   \file  auxiliares.cpp
   \brief Fichero que contiene las funciones auxiliares para lanzar los algoritmos
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
	std::cout << "[1] Algoritmo del cambio " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[2] Algoritmo de la mochila " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[3] Algoritmo del cambio con complejidad computacional " << std::endl;

	posicion++;
	PLACE(posicion++, 20);
	std::cout << BIYELLOW;
	std::cout << "Opción: ";
	std::cout << RESET;
	std::cin >> opcion;

	std::cin.ignore();

	return opcion;
}

void ejecutarOperacion(int opcion)
{

	Mochila m;
	if (opcion == 1) //Algoritmo del cambio
	{
		SistemaMonetario s;
		float cambio;
		s.setDinero();
		s.mostrarSistemaMonetario();
		cout << BIBLUE << "INTRODUCE LOS EUROS --> " << BIYELLOW;
		cin >> cambio;
		cambio = cambio * 100;
		s.setCambio(cambio);
		s.setTablaDinero(s.getCambio());
		s.obtenerSolucion();
		getchar();
	}
	if (opcion == 2) //Algoritmo de la mochila
	{

		Mochila m;
		int volumenMochila;
		m.setMateriales();
		m.mostrarMateriales();
		cout << BIBLUE << "Introduce el volumen de la mochila -->" << BIYELLOW;
		cin >> volumenMochila;
		m.setVolumen(volumenMochila + 1);
		cout << RESET << endl;
		m.setTablaMochila(m.getVolumen());
		m.obtenerSolucion();
		getchar();
	}
	if (opcion == 3)
	{
		Clock time;
		SistemaMatrices sm;
		int min = 500, max = 1000;
		int incr = 0, rep = 0;
		double cd;
		std::vector<double> n;
		std::vector<double> t_practico;
		std::vector<double> t_teorico;
		std::vector<std::vector<double> > matrizSoluciones;
		cout << BIBLUE << "Escribe el incremento--> " << BIYELLOW;
		cin >> incr;
		cout << BIBLUE << "Escribe el numero de repeticiones--> " << BIYELLOW;
		cin >> rep;
		min = min * 100;
		max = max * 100;
		n.clear();
		t_practico.clear();
		t_teorico.clear();
		cout << BIRED << "COMPUTANDO... ESPERATE " << RESET << endl;
		for (int i = min; i <= max; i = i + incr)
		{
			int media = 0;
			SistemaMonetario s;
			s.setDinero();
			s.setCambio(i);

			for (int j = 0; j <= rep; j++)
			{
				time.start();
				s.setTablaDinero(s.getCambio());
				if (time.isStarted())
				{
					time.stop();
					media = media + time.elapsed();
				}
			}

			n.push_back(i);
			media = media / rep;
			t_practico.push_back(media);
		}
		cout << BIGREEN << "COMPUTADO!!!" << RESET << endl;

		sm.setSistema(n, t_practico, 3, 3);
		matrizSoluciones = std::vector<std::vector<double> >(3, std::vector< double >(1));
		resolverSistemaEcuaciones(sm.getMatrizCoeficientes(), sm.getMatrizIndependientes(), 3,
		                          matrizSoluciones);
		cout << BIGREEN << "SOLUCIONES DEL SISTEMA" << RESET << endl;

		cout << BIBLUE << "x1=" << BIYELLOW << matrizSoluciones[0][0] << " " << BIBLUE << "x2=" << BIYELLOW
		     <<
		     matrizSoluciones[1][0] << " " << BIBLUE << "x3=" << BIYELLOW << matrizSoluciones[2][0] << RESET <<
		     endl;

		cout << BIGREEN << "ECUACION OBTENIDA" << RESET << endl;
		cout << BIBLUE << matrizSoluciones[0][0] << BIYELLOW << "+" << BIBLUE << matrizSoluciones[1][0] <<
		     "*" << BIRED << "n" << BIYELLOW << "+" << BIBLUE << matrizSoluciones[2][0] << "*" << BIRED << "n²"
		     << RESET << endl;

		t_teorico = calcularTiempoTeorico(matrizSoluciones, n);
		cd = getCoeficienteDeterminacion(t_practico, t_teorico);
		cout << BIGREEN << "COEFICIENTE DE DETERMINACION OBTENIDO: " << BIYELLOW << cd << RESET << endl;
		grabarFichero(n, t_practico, t_teorico);

		calcularDias(matrizSoluciones);

		getchar();

	}
}

std::vector<double> calcularTiempoTeorico(std::vector<std::vector<double> > & _matrizSoluciones,
        std::vector<double> & n)
{
	std::vector<double> t_teorico;
	double tiempo;

	for (int i = 0; i < n.size(); i++)
	{
		tiempo = _matrizSoluciones[0][0] + _matrizSoluciones[1][0] * n[i] + _matrizSoluciones[2][0] * pow(
		             n[i], 2);
		t_teorico.push_back(tiempo);
	}

	return t_teorico;
}

void grabarFichero(std::vector<double> n, std::vector<double> t_practico,
                   std::vector<double> t_teorico)
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

void calcularDias(std::vector<std::vector<double> > _matrizSoluciones)
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
			cout << BIBLUE << "Introduce el cambio para hacer la prediccion, 0 para salir" << std::endl <<
			     RESET;
			cin >> tam;

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

			std::cout << BIBLUE << "AÑOS: " << BIYELLOW << abs(anos) << std::endl << RESET;
			std::cout << BIBLUE << "DIAS: " << BIYELLOW << abs(dias) << std::endl << RESET;
			std::cout << BIBLUE << "HORAS: " << BIYELLOW << abs(horas) << std::endl << RESET;
			std::cout << BIBLUE << "MINUTOS: " << BIYELLOW << abs(minutos) << std::endl << RESET;
			std::cout << BIBLUE << "SEGUNDOS: " << BIYELLOW << abs(segundos) << std::endl << RESET;
			std::cout << BIBLUE << "MICROSEGUNDOS: " << BIYELLOW << abs(totalMicrosegundos) << std::endl <<
			          RESET;

		}

	}

}