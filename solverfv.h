#ifndef SOLVERFV_H
#define SOLVERFV_H

#include "mesh.h"

class SolverFV
{
public:
	SolverFV();

	void doStep();

	double g(double uL, double uR) const;

private:
	double getCFL() const;

	// f est une fonction analytique admettant suffisament de continuité. De ce
	// fait l'utilisateur  est requis de donner ça dérivée
	[[nodiscard]] double f(double u) const;
	[[nodiscard]] double fDer(double u) const;

private:
	Mesh m_Mesh;

	double Tmax;
	double aggro; // Pourcentae d'utilisation de la CFL
};

#endif // SOLVERFV_H
