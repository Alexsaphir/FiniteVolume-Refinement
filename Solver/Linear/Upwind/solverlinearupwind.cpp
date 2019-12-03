//
// Created by micro on 02/12/2019.
//

#include "solverlinearupwind.h"
double SolverLinearUpwind::g(double uL, double uR,
							 double dxL, double dxR,
							 double dt) const
{
	return .5 * (a + std::abs(a)) * uL + .5 * (a - std::abs(a)) * uR;
}
SolverLinearUpwind::SolverLinearUpwind(ProblemIC   pIC,
									   ProblemMesh pM, ProblemFile file,
									   double	   speed)
	: SolverLinear(pIC, pM,file, speed)
{
}
