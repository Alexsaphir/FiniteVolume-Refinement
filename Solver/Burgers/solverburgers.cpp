//
// Created by micro on 02/12/2019.
//

#include "solverburgers.h"

double SolverBurgers::f(double u) const
{
	return .5 * u * u;
}

double SolverBurgers::fDer(double u) const
{
	return u;
}
SolverBurgers::SolverBurgers(ProblemIC pIC, ProblemMesh pM, ProblemFile file)
	: SolverFV(pIC, pM, file)
{
}
