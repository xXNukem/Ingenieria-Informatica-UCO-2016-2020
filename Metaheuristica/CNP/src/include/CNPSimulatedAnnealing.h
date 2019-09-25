
#ifndef INCLUDE_CNPSIMULATEDANNEALING_H_
#define INCLUDE_CNPSIMULATEDANNEALING_H_

#include <CNPSolution.h>
#include <CNPInstance.h>
#include <CNPMetaheuristic.h>
#include <CNPStopCondition.h>
#include <cstdlib>

/**
 * Clase que implementa el Enfriamiento Simulado para el CNP.
 */
class CNPSimulatedAnnealing : public CNPMetaheuristic
{

protected:
    /**
	 * Variables miembro
	 * _T almacena la temperatura actual del sistema
	 * _initialProb almacena la probabilidad inicial con la que se aceptan en media los cambios a peores soluciones
	 * _annealingFactor almacena el factor con el que se enfría la temperatura
	 * _solution Solución al CNP sobre la que trabaja el Enfriamiento Simulado
	 * _instance Instancia del problema que se está abordando
	 */
    double _T;
    double _initialProb;
    double _annealingFactor;
    unsigned _itsPerAnnealing;
    CNPSolution *_solution;
    CNPInstance *_instance;

    /**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
    vector<double> _results;
    vector<CNPSolution> _resultsSols;

    /**
	 * Función que indica si se acepta la nueva solución según su diferencia en fitness con respecto a la actual
	 * @param[in] deltaFitness diferencia en fitnees de la nueva solución con respecto a la actual
	 * @return true si se acepta la nueva solución, false en otro caso
	 */
    bool accept(double deltaFitness);

public:
    /**
	 * Constructor
	 */
    CNPSimulatedAnnealing()
    {
        _T = 0;
        _initialProb = 0;
        _annealingFactor = 0;
        _itsPerAnnealing = 0;
        _solution = NULL;
        _instance = NULL;
    }

    /**
	 * Destructor
	 */
    virtual ~CNPSimulatedAnnealing()
    {

        if (_bestSolution != NULL)
        {
            delete _bestSolution;
            _bestSolution = NULL;
        }
    };

    /**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
    virtual void run(CNPStopCondition &stopCondition);

    /**
	 * Función que asigna la solución inicial para la metaheurística
	 * @param[in] solution Solución inicial a partir de la cual aplicar el enfriamiento simulado
	 */
    void setSolution(CNPSolution *solution);

    /**
	 * Función que inicializa ciertos parámetros de la metaheurística, en particular, se calcula la temperatura inicial del sistema según la probabilidad con la que se desean aceptar los primeros cambios a peores soluciones
	 * @param[in] initialProb Probabilidad con la que se desean aceptar en media los primeros cambios a peor
	 * @param[in] numInitialEstimates Número de soluciones iniciales sobre las que se estima la temperatura necesaria para aceptar cambios a peores soluciones con la probabilidad indicada
	 * @param[in] annealingFactor Factor con el cual se enfría la temperatura
	 * @param[in] itersPerAnnealing Número de iteraciones entre dos enfriamientos de la temperatura
	 * @param[in] instance Instancia del problema que se va a abordar
	 */
    void initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, CNPInstance &instance);

    /**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
    vector<double> &getResults()
    {
        return _results;
    }
    vector<CNPSolution>&getSolResults(){
        return _resultsSols;
    }
};

#endif /* INCLUDE_CNPSIMULATEDANNEALING_H_ */