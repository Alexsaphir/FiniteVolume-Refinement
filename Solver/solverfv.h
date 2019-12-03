#ifndef SOLVERFV_H
#define SOLVERFV_H

#include "Mesh/mesh.h"

struct ProblemIC
{
	double Tmax {1.};
	double dt_max {.01};

	double (*u0)(double) {[](double x) { return 0.; }};
	double (*u_exa)(double, double) {
		[](double x, double t) { return 0.; }};
};

struct ProblemFile
{
	std::string u0;
	std::string uTmax;
	std::string energy;
	std::string errorOverTime;

};

class SolverFV
{
public:
	SolverFV(ProblemIC pIC, ProblemMesh pM, ProblemFile file);
	void solve();

private:
	void				 doStep();
	[[nodiscard]] double getCFL() const;

protected:
	virtual double g(double uL, double uR, double dxL = 1.,
					 double dxR = 1.,
					 double dt	= 1.) const = 0;
	// f est une fonction analytique admettant suffisament
	// de continuité. De ce fait l'utilisateur  est requis
	// de donner ça dérivée
	virtual double f(double u) const	= 0;
	virtual double fDer(double u) const = 0;

private:
	ProblemIC m_pIC;
	ProblemFile m_file;
	Mesh	  m_Mesh;

	double t {0.};
};


#endif // SOLVERFV_H
