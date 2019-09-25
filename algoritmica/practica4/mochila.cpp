/*!
   \file  mochila.cpp
   \brief Archivo cpp para la clase mochila
*/
#include "mochila.hpp"


void Mochila::setMateriales()
{
	ifstream f("mochila.txt", ios::in);

	if (!f.good())
	{
		cout << "El fichero no existe\n" << endl;
	}
	else
	{
		int i = 0;
		int etiqueta, volumen, precio;

		while (f >> etiqueta >> volumen >> precio)
		{
			Materiales aux;
			aux.setID(etiqueta);
			aux.setVOL(volumen);
			aux.setPRE(precio);

			_m.push_back(aux);
		}

	}

	f.close();

}

void Mochila::mostrarMateriales(std::vector<Materiales> v)
{
	cout << BIGREEN << "MATERIALES LEIDOS" << RESET << endl;

	for (int i = 0; i < v.size(); i++)
	{
		cout << BIBLUE << "ETIQUETA: " << BIYELLOW << v[i].getID() << "\t" << BIBLUE
		     <<
		     " VOLUMEN: " << BIYELLOW
		     <<
		     v[i].getVOL() << "\t" << BIBLUE << " PRECIO UNIDAD: " << BIYELLOW << v[i].getPRE() << RESET << endl;
	}
}