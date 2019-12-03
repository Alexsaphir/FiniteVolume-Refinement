//
// Created by micro on 02/12/2019.
//

#ifndef RAFFINEMENT_SOLVERLINEAR_H
#define RAFFINEMENT_SOLVERLINEAR_H

#include "Solver/solverfv.h"

class SolverLinear: public SolverFV
{
public:
	SolverLinear(ProblemIC pIC, ProblemMesh pM, ProblemFile file, double speed);

public:
	[[nodiscard]] double f(double u) const;
	[[nodiscard]] double fDer(double u) const;

protected:
	double a{1.};
};

#endif // RAFFINEMENT_SOLVERLINEAR_H
