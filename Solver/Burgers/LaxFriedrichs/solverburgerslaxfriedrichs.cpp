//
// Created by micro on 02/12/2019.
//

#include "solverburgerslaxfriedrichs.h"


double SolverBurgersLaxFriedrichs::g(double uL, double uR,
									 double dxL, double dxR,
									 double dt) const
{
	return .5 * (f(uL) + f(uR)) - .5 * dxR * (uR - uL) / dt;
}
SolverBurgersLaxFriedrichs::SolverBurgersLaxFriedrichs(
	ProblemIC pIC, ProblemMesh pM, ProblemFile file)
	: SolverBurgers(pIC, pM,file)
{
}
