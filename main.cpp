#include <cmath>
#include <iostream>

#include "Solver/Burgers/LaxFriedrichs/solverburgerslaxfriedrichs.h"
#include "Solver/Burgers/Godunov/solverburgersgodunov.h"

#include "Solver/Linear/Upwind/solverlinearupwind.h"
#include "Solver/Linear/LaxFriedrichs/solverlinearlaxfriedrichs.h"

int main()
{
//	auto u0 = [](double x){ return std::abs(x)<.5?1.:0.;};
//	auto u = [](double x, double t){ return std::abs(x)<.5?1.:0.;};

	double		speed {1.};
//
	auto u0 = [](double x){ return std::sin(2.*M_PI*x)+1;};
	auto u = [](double x, double t){ return std::sin(2.*M_PI*(x-1.*t))+1;};
	ProblemIC	pIC{100.,.1,*u0,*u};
	ProblemMesh pM{1000,0,1.};

	ProblemFile file {"Mesh0.dat", "Mesh1.dat", "Mesh2.dat",
					  "Erreur.dat"};


	SolverLinearLaxFriedrichs Problem(pIC,pM,file,speed);
	Problem.solve ();

	return 0;
}
