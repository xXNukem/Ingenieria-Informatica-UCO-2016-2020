/*!
   \file  algoritmos.cpp
   \brief Archivo cpp para los algoritmos voraces
*/
#include "algoritmos.hpp"

//FUNCIONES PARA LA MOCHILA
void algoritmoMochila(int n, int v, std::vector<Materiales> &m)
{

	int resto = v; //volumen total de la mochila
	//Los materiales han sido inicializados a que no se han usado nada
	bool materialDisponible = false;
	do {
		int precioMaximo = 0;
		int materialMaximo = 0;
		materialDisponible = false;

		//seleccionamos el material de maximo coste
		for (int i = 0; i < m.size(); i++)
		{
			if (m[i].getUSADO() == "nada")
			{
				materialDisponible = true;
				if (m[i].getPRE() > precioMaximo)
				{
					precioMaximo = m[i].getPRE();
					materialMaximo = i;
				}
			}
		}

		//comprobamos si el material de maximo coste cabe en la mochila
		if (materialDisponible == true)
		{
			if (resto >= m[materialMaximo].getVOL())
			{
				m[materialMaximo].setUSADO("total");
				resto = resto - m[materialMaximo].getVOL();
			}
			else
			{
				m[materialMaximo].setUSADO("parcial");
				m[materialMaximo].setVOL(resto);
				resto = 0;
			}
		}

	} while (!(resto == 0 || materialDisponible == false));

	recuentoMateriales(m, v);

}

void recuentoMateriales(std::vector<Materiales> &m, int v)
{
	int resto = v;
	int cantidadTotal = 0;

	cout << BIGREEN << "MATERIALES USADOS: " << RESET << endl;
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i].getUSADO() != "nada")
		{
			resto = resto - m[i].getVOL();
			cantidadTotal = cantidadTotal + (m[i].getVOL() * m[i].getPRE());

			cout << BIBLUE << "ID Material --> " << BIYELLOW << m[i].getID() << endl;
			cout << BIBLUE << "Volumen --> " << BIYELLOW << m[i].getVOL() << endl;
			cout << BIBLUE << "Precio --> " << BIYELLOW << m[i].getPRE() << endl;
			cout << BIBLUE << "Uitlizado --> " << BIYELLOW << m[i].getUSADO() << endl;
			cout << RESET << endl;
		}
	}

	cout << BIGREEN << "El precio total  es " << BIBLUE << cantidadTotal << RESET << endl;

}

//FUNCIONES PARA EL CAMBIO
void algoritmoCambio(std::vector<Dinero> d, int cambio)
{
	int sumaParcial = 0;

	while (sumaParcial != cambio)
	{
		for (int i = d.size() - 1; i >= 0; i--)
		{
			if (d[i].getValor() + sumaParcial <= cambio)
			{
				sumaParcial = sumaParcial + d[i].getValor();
				d[i].setCantidadUsada(d[i].getCantidadUsada() + 1);
				i = d.size();
			}
		}
	}

	recuentoDinero(d);

}


void recuentoDinero(std::vector<Dinero> d)
{
	cout << BIGREEN << "CAMBIO UTILIZADO" << RESET << endl;

	for (int i = d.size() - 1; i >= 0; i--)
	{
		if (d[i].getCantidadUsada() > 0)
		{
			cout << BIYELLOW << "Cantidad: " << BIBLUE << d[i].getCantidadUsada() << RESET << endl;
			cout << BIYELLOW << "VALOR: " << BIBLUE << (float)d[i].getValor() / 100 << "\t" << BIYELLOW <<
			     " TIPO: "
			     <<
			     BIBLUE << d[i].getTipo() << RESET << endl;

			cout << endl;
		}
	}
}