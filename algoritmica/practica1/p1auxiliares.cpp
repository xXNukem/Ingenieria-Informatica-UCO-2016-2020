#include "p1auxiliares.hpp"

int menu()
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
	std::cout << "[1] Metodo de Insercion Binaria " << std::endl;

	PLACE(posicion++,10);
	std::cout << "[2] Metodo de Monticulo " << std::endl;

	

	posicion++;
	PLACE(posicion++,20);
	std::cout << BIYELLOW;
	std::cout << "Opción: ";
	std::cout << RESET;
	std::cin >> opcion;

    std::cin.ignore();

	return opcion;
}

void grabarFichero(std::vector<datos> const &t)
{

	 std::string n="Datos.txt";
	 int tiempoEstimado;
		 std::ofstream f(n.c_str());

		 for (int i = 0; i < (int)t.size(); i++)
		 {
		  		f << t[i]._tam << "\t" << t[i]._time << "\t " << t[i]._time_est << std::endl;
		 }

		 f.close();
	
}