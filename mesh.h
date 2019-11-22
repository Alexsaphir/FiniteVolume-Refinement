#ifndef MESH_H
#define MESH_H

#include <ostream>

class Cell;

class Mesh
{
public:
	Mesh();
	Mesh(double binf, double bsup, uint nbCell);

private:
	void pushCell_front(const Cell& cell);

private:
	uint m_nbCells {0};

	Cell* m_head {nullptr};

public:
	friend class SolverFV;
	friend std::ostream& operator<<(std::ostream& out, const Mesh& M);
};

std::ostream& operator<<(std::ostream& out, const Mesh& M);
#endif // MESH_H
