#include "reinas.hpp"
//FILA K
//COLUMNA Xk
//Xj es la columna de la fila j
bool Reinas::verificarLugar(int k, std::vector<int> &x)
{
	for (int i = 1 ; i < k; i++)
	{
		if (x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k))
		{
			return false;
		}
	}
	return true;
}

void Reinas::nReinasBackTracking(int n)
{

	std::vector<int> x = std::vector<int> (n + 1);
	int cont = 0;
	int k = 1;
	x[k] = 0;

	while (k > 0)
	{
		x[k] = x[k] + 1;
		while (x[k] <= n && verificarLugar(k, x) == false)
		{
			x[k] = x[k] + 1;
		}
		if (x[k] <= n)
		{
			if (k == n) //habemus solucion
			{	//Escribir solucion
				_soluciones.push_back(x);
			}
			else
			{
				k = k + 1;
				x[k] = 0;
			}
		}
		else
		{
			k = k - 1;
		}
	}

}

void Reinas::nReinasLasVegas(int n, bool & exito)
{

	std::vector<int> x = std::vector<int> (n + 1);
	std::vector<int> posDisp = std::vector<int> (n + 1);
	int cont;

	for (int i = 0; i < x.size(); i++)
	{
		x[i] = 0;
	}

	for (int k = 1; k <= n; k++)
	{
		cont = 0;

		for (int j = 1; j <= n; j++)
		{
			x[k] = j;
			if (verificarLugar(k, x) == true)
			{
				cont = cont + 1;
				posDisp[cont] = j;
			}
		}
		if (cont == 0)
		{
			break;
		}
		int posAleat = rand() % cont + 1;
		int col = posDisp[posAleat];
		x[k] = col;

	}
	if (cont == 0)
	{
		exito = false;
	}
	else
	{
		_soluciones.push_back(x);
		exito = true;
	}
}

void Reinas::mostrarSolucion()
{

	int cont = 1;
	for (int i = 0; i < _soluciones.size(); i++)
	{
		std::vector<std::vector<string> > tablero = std::vector<std::vector<string> >(_n + 1,
		        std::vector< string >(_n + 1));

		for (int a = 1; a < _n + 1; a++)
		{
			for (int b = 1; b < _n + 1; b++)
			{
				tablero[a][b] = "0";
			}
		}


		cout << BIGREEN << "SOLUCION " << cont << RESET << endl;
		for (int j = 1; j < _n + 1; j++)
		{
			cout << BIBLUE << "[" << BIRED << _soluciones[i][j] << BIBLUE << "]";
			tablero[j][_soluciones[i][j]] = "*";
		}

		cont++;
		cout << endl;

		for (int a = 1; a < _n + 1; a++)
		{
			for (int b = 1; b < _n + 1; b++)
			{
				if (tablero[a][b] == "0")
				{
					cout << BIBLUE << "[" << BIYELLOW << tablero[a][b] << BIBLUE << "]";
				}
				else
				{
					cout << BIBLUE << "[" << BIRED << tablero[a][b] << BIBLUE << "]";
				}
			}
			cout << RESET << endl;
		}


	}


}

void Reinas::nReinasBackTrackingMOD(int n)
{

	std::vector<int> x = std::vector<int> (n + 1);
	int cont = 0;
	int k = 1;
	x[k] = 0;

	while (k > 0)
	{
		x[k] = x[k] + 1;
		while (x[k] <= n && verificarLugar(k, x) == false)
		{
			x[k] = x[k] + 1;
		}
		if (x[k] <= n)
		{
			if (k == n) //habemus solucion
			{

				break;
			}
			else
			{
				k = k + 1;
				x[k] = 0;
			}
		}
		else
		{
			k = k - 1;
		}
	}

}