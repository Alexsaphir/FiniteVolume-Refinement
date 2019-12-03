//
// Created by micro on 02/12/2019.
//

#include "solverburgersgodunov.h"
double SolverBurgersGodunov::g(double uL, double uR,
							   double dxL, double dxR,
							   double dt) const
{
	return 0;
}
SolverBurgersGodunov::SolverBurgersGodunov(ProblemIC   pIC,
										   ProblemMesh pM, ProblemFile file)
	: SolverBurgers(pIC, pM,file)
{
}
