#ifndef CELL_H
#define CELL_H

#include <iostream>

class Cell
{
public:
	Cell() = default;
	Cell(double a, double b, double u, Cell* next = nullptr);

	bool isTail() const;

	double length() const;
	double mid() const;

private:
	double m_a {0.};
	double m_b {1.};
	double m_u {0.};

	Cell* m_next {nullptr};

public:
	friend class Mesh;
	friend class SolverFV;
	friend std::ostream& operator<<(std::ostream& out, const Cell& cell);
};

#endif // CELL_H
