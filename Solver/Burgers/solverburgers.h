//
// Created by micro on 02/12/2019.
//

#ifndef RAFFINEMENT_SOLVERBURGERS_H
#define RAFFINEMENT_SOLVERBURGERS_H

#include "Solver/solverfv.h"

class SolverBurgers : public SolverFV
{
public:
	SolverBurgers(ProblemIC pIC, ProblemMesh pM, ProblemFile file);

public:
	[[nodiscard]] double f(double u) const;
	[[nodiscard]] double fDer(double u) const;
};

#endif // RAFFINEMENT_SOLVERBURGERS_H
