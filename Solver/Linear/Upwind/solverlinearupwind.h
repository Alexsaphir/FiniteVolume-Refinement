//
// Created by micro on 02/12/2019.
//

#ifndef RAFFINEMENT_SOLVERLINEARUPWIND_H
#define RAFFINEMENT_SOLVERLINEARUPWIND_H

#include "Solver/Linear/solverlinear.h"

class SolverLinearUpwind:public  SolverLinear
{
public:
	SolverLinearUpwind(ProblemIC pIC, ProblemMesh pM, ProblemFile file, double speed);

	[[nodiscard]] double g(double uL, double uR,
								   double dxL = 1.,
								   double dxR = 1.,
								   double dt  = 1.) const override;
};

#endif // RAFFINEMENT_SOLVERLINEARUPWIND_H
