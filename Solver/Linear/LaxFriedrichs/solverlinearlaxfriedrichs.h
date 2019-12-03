//
// Created by micro on 02/12/2019.
//

#ifndef RAFFINEMENT_SOLVERLINEARLAXFRIEDRICHS_H
#define RAFFINEMENT_SOLVERLINEARLAXFRIEDRICHS_H

#include "Solver/Linear/solverlinear.h"

class SolverLinearLaxFriedrichs:public  SolverLinear
{
public:
	SolverLinearLaxFriedrichs(ProblemIC pIC, ProblemMesh pM, ProblemFile file, double speed);

public:
	[[nodiscard]] virtual double g(double uL, double uR, double dxL = 1.,
								   double dxR = 1., double dt = 1.) const;
};

#endif // RAFFINEMENT_SOLVERLINEARLAXFRIEDRICHS_H
