/*!
   \file  estadistica.cpp
   \brief Fichero que contiene las funciones de estadistica
*/

#include "estadistica.hpp"


double getMedia(std::vector<double> m)
{
	double suma = 0;

	for (int i = 0; i < m.size(); i++)
	{
		suma += m[i];
	}

	return suma / m.size();
}

double getVarianza(std::vector<double> v, double x)
{
	double varianza = 0;
	for (int i = 0; i < v.size(); i++)
	{
		varianza += (v[i] - x) * (v[i] - x);
	}
	return varianza;
}

double getCoeficienteDeterminacion(std::vector <double>const &t_practico,
                                   std::vector <double>const &t_teorico)
{
	double mp, mt, sp, st, ste, denom, r;

// Calcula la media de las dos series x[], y[] /

	mp = getMedia(t_practico);
	mt = getMedia(t_teorico);


//Calculo de las varianzas de ambos tiempos

	sp = getVarianza(t_practico, mp);
	st = getVarianza(t_teorico, mt);

	//sacamos el denominador con las varianzas
	denom = sqrt(sp * st);

// Calcula la correlación de las series


	ste = 0;

	for (int i = 0; i < t_practico.size(); i++)
	{

		ste += (t_practico[i] - mp) * (t_teorico[i] - mt);

	}

	r = ste / denom;

	return r;
}