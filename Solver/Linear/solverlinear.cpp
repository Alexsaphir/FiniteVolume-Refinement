//
// Created by micro on 02/12/2019.
//

#include "solverlinear.h"
double SolverLinear::f(double u) const
{
	return a*u;
}
double SolverLinear::fDer(double u) const
{
	return a;
}
SolverLinear::SolverLinear(ProblemIC pIC, ProblemMesh pM, ProblemFile file,
						   double speed)
	: SolverFV(pIC, pM, file), a(speed)
{
}
