//
// Created by micro on 02/12/2019.
//

#include "solverlinearlaxfriedrichs.h"
double SolverLinearLaxFriedrichs::g(double uL, double uR,
									double dxL, double dxR,
									double dt) const
{
	return .5 * (f(uL) + f(uR)) - .5 * dxR * (uR - uL) / dt;
}
SolverLinearLaxFriedrichs::SolverLinearLaxFriedrichs(
	ProblemIC pIC, ProblemMesh pM, ProblemFile file, double speed)
	: SolverLinear(pIC, pM,file, speed)
{
}
