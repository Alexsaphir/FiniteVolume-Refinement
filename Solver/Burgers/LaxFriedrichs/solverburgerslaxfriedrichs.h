//
// Created by micro on 02/12/2019.
//

#ifndef RAFFINEMENT_SOLVERBURGERSLAXFRIEDRICHS_H
#define RAFFINEMENT_SOLVERBURGERSLAXFRIEDRICHS_H

#include "Solver/Burgers/solverburgers.h"

class SolverBurgersLaxFriedrichs: public SolverBurgers
{
public:
	SolverBurgersLaxFriedrichs(ProblemIC pIC, ProblemMesh pM, ProblemFile file);

	[[nodiscard]] virtual double g(double uL, double uR, double dxL = 1.,
								   double dxR = 1., double dt = 1.) const;
};

#endif // RAFFINEMENT_SOLVERBURGERSLAXFRIEDRICHS_H
