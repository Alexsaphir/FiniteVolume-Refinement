#ifndef MESH_H
#define MESH_H

#include <iostream>

class Cell;

class Mesh
{
public:
	Mesh();

	Mesh(double binf, double bsup, uint nbCell);

private:
	void pushCell_front(const Cell& cell);

	void fuseCell(Cell* cellDest);

	void splitCell(Cell* cell);

	void splitAndInterpolate(Cell* cellL, Cell* cellR);
	void splitAndInterpolate(Cell* cellL, Cell* cellR, double dx);

	Cell* startList() const;
	Cell* endList() const;

public:
	void applyFunctionOnMesh(double (*f)(double));

	void updateMesh(double dxMin, double dxMax, double duMin, double duMax);

private:
	uint m_nbCells {0};

	Cell* m_head {nullptr};

public:
	friend class SolverFV;

	friend std::ostream& operator<<(std::ostream& out, const Mesh& M);

	void saveToFile(const std::string& filename) const;
};

#endif // MESH_H
