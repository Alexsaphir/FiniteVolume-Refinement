//
// Created by micro on 02/12/2019.
//

#ifndef RAFFINEMENT_SOLVERBURGERSGODUNOV_H
#define RAFFINEMENT_SOLVERBURGERSGODUNOV_H

#include "Solver/Burgers/solverburgers.h"

class SolverBurgersGodunov:public SolverBurgers
{
public:
	SolverBurgersGodunov(ProblemIC pIC, ProblemMesh pM, ProblemFile file);

public:
	[[nodiscard]] virtual double g(double uL, double uR, double dxL = 1.,
								   double dxR = 1., double dt = 1.) const;
};

#endif // RAFFINEMENT_SOLVERBURGERSGODUNOV_H
