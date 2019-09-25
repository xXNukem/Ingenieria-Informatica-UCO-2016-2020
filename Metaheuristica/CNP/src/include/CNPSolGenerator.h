#ifndef _CNPSOLGENERATOR_
#define _CNPSOLGENERATOR_

#include "CNPInstance.h"
#include "CNPSolution.h"

using namespace std;

class CNPSolGenerator
{

public:
    static void genRandomSol(CNPInstance &instance, CNPSolution &solution);
};

#endif