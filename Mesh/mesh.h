#ifndef MESH_H
#define MESH_H

#include <iostream>

// Définition pour Mingw
typedef unsigned int uint;

class Cell;

struct ProblemMesh
{
	uint nbCellInitial {1};

	double xmin {-1.};
	double xmax {1.};

	double dx_inf{.001};
	double dx_sup{.1};

	double du_inf{0.};
	double du_sup{.5};
};

class Mesh
{
public:
	Mesh();

	Mesh(ProblemMesh pMesh);

	void applyFunctionOnMesh(double (*f)(double));

	void saveToFile(const std::string& filename) const;
	void plotToFile(const std::string& filename) const;

	void updateMesh(double dxMin, double dxMax,
					double duMin, double duMax);

	static double integrate(double (*f)(double),
							const Cell& cell, uint N = 100);
	static double integrate(double (*f)(double, double),double t,
							const Cell& cell, uint N = 100);
	double computeMass() const;
	double computeError(double (*u_exa)(double, double), double t);

	double operator[](uint pos) const;
private:
	[[nodiscard]] Cell* startList() const;
	[[nodiscard]] Cell* endList() const;

	void pushCell_front(const Cell& cell);

	void fuseCell(Cell* cellDest);
	bool splitCell(Cell* cell, double ratio = .5);

private:
	ProblemMesh m_pMesh;
	uint m_nbCells {0};
	Cell* m_head {nullptr};


public:
	friend class SolverFV;
	friend std::ostream& operator<<(std::ostream& out,
									const Mesh&	  M);

};

#endif // MESH_H
