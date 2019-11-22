#ifndef SOLVERFV_H
#define SOLVERFV_H

#include "mesh.h"

class SolverFV
{
public:
	SolverFV();

	void doStep();

	virtual double g(double uL, double uR) const;

private:
	Mesh m_Mesh;
};

#endif // SOLVERFV_H
