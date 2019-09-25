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
	std::cout << "[1] Algoritmo de las N reinas Backtracking " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[2] Algoritmo de las N reinas Las Vegas " << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[3] Estudio de pruebas para el algoritmo de Las Vegas " << std::endl;


	PLACE(posicion++, 10);
	std::cout << "[4] Ajustar curva de tiempo para N reinas Backtracking" << std::endl;

	PLACE(posicion++, 10);
	std::cout << "[5] Comparacion entre Backtracking y Las Vegas" << std::endl;

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

	if (opcion == 1) //Algoritmo del cambio
	{
		string opc;
		Clock time;
		double tiempo;
		Reinas r;
		int n;
		cout << BIBLUE << "Introduce el valor N --> " << BIYELLOW;
		cin >> n;
		r.setN(n);
		cout << RESET << endl;
		cout << BIRED << "COMPUTANDO SOLUCIONES... ESPERATE!!!" << RESET << endl;
		time.start();
		r.nReinasBackTracking(r.getN());
		if (time.isStarted())
		{
			time.stop();
			tiempo = time.elapsed();
		}
		cout << BIGREEN <<
		     "TODAS LAS SOLUCIONES COMPUTADAS!!! Escirbe 's' para mostrarlas, cualquier tecla para continuar" <<
		     RESET <<
		     endl;
		cin >> opc;
		if (opc == "s")
		{
			r.mostrarSolucion();
		}
		cout << BIYELLOW << "TIEMPO DE COMPUTO:" << RESET << endl;

		tiempo = tiempo / pow(10, 6);
		double segundos = fmod(tiempo, 60);

		tiempo = (tiempo - segundos) / 60;
		double minutos = fmod(tiempo, 60);

		tiempo = (tiempo - minutos) / 60;
		double horas = fmod(tiempo, 24);

		std::cout << BIBLUE << "HORAS: " << BIYELLOW << abs(horas) << std::endl << RESET;
		std::cout << BIBLUE << "MINUTOS: " << BIYELLOW << abs(minutos) << std::endl << RESET;
		std::cout << BIBLUE << "SEGUNDOS: " << BIYELLOW << abs(segundos) << std::endl << RESET;
		getchar();
	}
	if (opcion == 2) //Algoritmo de la mochila
	{
		Reinas r;
		int n;
		cout << BIBLUE << "Introduce el valor N --> " << BIYELLOW;
		cin >> n;
		r.setN(n);
		cout << RESET << endl;
		bool exito = false;
		int cont = 0;
		while (exito != true)
		{
			r.nReinasLasVegas(r.getN(), exito);
			cont++;
		}
		r.mostrarSolucion();
		cout << BIGREEN << "Pruebas necesarias hasta el exito: " << BIYELLOW << cont << RESET << endl;
		getchar();
	}
	if (opcion == 3)
	{
		Reinas r;
		int n, rep;
		int intentos = 0;
		cout << BIBLUE << "Introduce el valor N --> " << BIYELLOW;
		cin >> n;
		r.setN(n);
		cout << RESET << endl;
		cout << BIBLUE << "Introduce numero de repeticiones --> " << BIYELLOW;
		cin >> rep;
		cout << RESET << endl;
		for (int i = 0; i < rep; i++)
		{
			bool exito = false;
			int c = 0;
			while (exito != true)
			{
				r.nReinasLasVegas(r.getN(), exito);
				c++;
			}
			intentos = intentos + c;
		}
		float media = (float)intentos / (float)rep;
		cout << BIBLUE << "Para " << BIYELLOW << n << BIBLUE << " reinas con " << BIYELLOW << rep << BIBLUE
		     << " repeticiones la media de intentos es " << BIYELLOW << media << RESET << endl;

		getchar();
	}
	if (opcion == 4)
	{
		Reinas r;
		Clock time;
		std::vector<double> nR;
		std::vector<double> t_practico;
		std::vector<double> t_teorico;
		std::vector<double> nRaux;
		std::vector<std::vector<double> > matrizSoluciones;
		int media, n, rep;
		cout << BIBLUE << "Introduce el valor N --> " << BIYELLOW;
		cin >> n;
		r.setN(n);
		cout << RESET << endl;
		cout << BIBLUE << "Introduce numero de repeticiones --> " << BIYELLOW;
		cin >> rep;
		cout << RESET << endl;
		cout << BIRED << "COMPUTANDO... ESPERATE!!!" << RESET << endl;
		for (int i = 4; i <= r.getN(); i++)
		{	//Decido partir desde 4 porque las soluciones de 1 a 3 son triviales o no existen
			media = 0;

			for (int j = 0; j < rep; j++)
			{
				time.start();
				r.nReinasBackTracking(i);
				if (time.isStarted())
				{
					time.stop();
					media = media + time.elapsed();
				}
				nR.push_back(i);
				nRaux.push_back(calcularFactorial(i));
				media = media / rep;
				t_practico.push_back(media);
			}
		}

		cout << BIGREEN << "COMPUTADO!!! Grafico y fichero generados" << RESET << endl;
		SistemaMatrices m;
		matrizSoluciones = std::vector<std::vector<double> >(2, std::vector< double >(1));
		m.setSistema(nRaux, t_practico, 2, 2);
		resolverSistemaEcuaciones(m.getMatrizCoeficientes(), m.getMatrizIndependientes(),
		                          m.getMatrizCoeficientes().size(), matrizSoluciones);
		t_teorico = calcularTiempoTeorico(matrizSoluciones, nRaux);
		grabarFichero(nR, t_practico, t_teorico);
		system("./ejemplo_gnuplot.sh");
		cout << BIGREEN << "SOLUCIONES DEL SISTEMA" << RESET << endl;

		cout << BIBLUE << "x1=" << BIYELLOW << matrizSoluciones[0][0] << " " << BIBLUE << "x2=" << BIYELLOW
		     <<
		     matrizSoluciones[1][0] << RESET << endl;

		cout << BIGREEN << "ECUACION OBTENIDA" << RESET << endl;
		cout << BIBLUE << matrizSoluciones[0][0] << BIYELLOW << "+" << BIBLUE << matrizSoluciones[1][0] <<
		     "*" << BIRED << "N!" << RESET << endl;
		double cd = getCoeficienteDeterminacion(t_practico, t_teorico);
		cout << BIGREEN << "COEFICIENTE DE DETERMINACION OBTENIDO: " << BIYELLOW << cd << RESET << endl;
		getchar();
	}
	if (opcion == 5)
	{
		Reinas r;
		Clock time;
		int n;
		double tiempoBacktracking = 0, tiempoLasVegas = 0;
		cout << BIBLUE << "Introduce el valor N maximo --> " << BIYELLOW;
		cin >> n;
		r.setN(n);
		cout << BIRED << "COMPUTANDO... ESPERATE" << RESET << endl;

		for (int i = 8; i <= r.getN(); i++)
		{
			time.start();
			r.nReinasBackTrackingMOD(i);
			if (time.isStarted())
			{
				time.stop();
				tiempoBacktracking = time.elapsed();
			}

			bool exito = false;
			time.start();
			while (exito != true)
			{
				r.nReinasLasVegas(i, exito);

			}
			if (time.isStarted())
			{
				time.stop();
				tiempoLasVegas = time.elapsed();
			}

			cout << BIRED << "PARA N = " << BIBLUE << i << RESET << endl;
			//---------------------------------------------
			cout << BIGREEN << "Tiempos obtenidos Backtracking: " << RESET << endl;
			tiempoBacktracking = tiempoBacktracking / pow(10, 6);
			double segundos = fmod(tiempoBacktracking, 60);

			tiempoBacktracking = (tiempoBacktracking - segundos) / 60;
			double minutos = fmod(tiempoBacktracking, 60);

			tiempoBacktracking = (tiempoBacktracking - minutos) / 60;
			double horas = fmod(tiempoBacktracking, 24);

			std::cout << BIBLUE << "HORAS: " << BIYELLOW << abs(horas) << std::endl << RESET;
			std::cout << BIBLUE << "MINUTOS: " << BIYELLOW << abs(minutos) << std::endl << RESET;
			std::cout << BIBLUE << "SEGUNDOS: " << BIYELLOW << abs(segundos) << std::endl << RESET;
			//---------------------------------------------
			cout << BIGREEN << "Tiempos obtenidos Las Vegas: " << RESET << endl;
			tiempoLasVegas = tiempoLasVegas / pow(10, 6);
			segundos = fmod(tiempoLasVegas, 60);

			tiempoLasVegas = (tiempoLasVegas - segundos) / 60;
			minutos = fmod(tiempoLasVegas, 60);

			tiempoLasVegas = (tiempoLasVegas - minutos) / 60;
			horas = fmod(tiempoLasVegas, 24);

			std::cout << BIBLUE << "HORAS: " << BIYELLOW << abs(horas) << std::endl << RESET;
			std::cout << BIBLUE << "MINUTOS: " << BIYELLOW << abs(minutos) << std::endl << RESET;
			std::cout << BIBLUE << "SEGUNDOS: " << BIYELLOW << abs(segundos) << std::endl << RESET;

		}

		getchar();
	}
}

std::vector<double> calcularTiempoTeorico(std::vector<std::vector<double> > & _matrizSoluciones,
        std::vector<double> & n)
{
	std::vector<double> t_teorico;
	float tiempo;

	for (int i = 0; i < n.size(); i++)
	{
		tiempo = _matrizSoluciones[0][0] + _matrizSoluciones[1][0] * n[i];
		t_teorico.push_back(tiempo);
	}

	return t_teorico;
}

void grabarFichero(std::vector<double> const &n, std::vector<double> const &t_practico,
                   std::vector<double> const &t_teorico)
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


int calcularFactorial(int n)
{
	int fact = 1;

	for (int b = n; b > 1; b--)
	{
		fact = fact * b;
	}

	return fact;
}