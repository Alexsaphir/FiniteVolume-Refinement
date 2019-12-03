#include "cell.h"

Cell::Cell(double a, double b, double u, Cell* next)
	: m_a(a), m_b(b), m_u(u), m_next(next)
{
}

bool Cell::isTail() const
{
	return m_next == nullptr;
}

double Cell::length() const
{
	return m_b - m_a;
}

double Cell::mid() const
{
	return .5 * (m_a + m_b);
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	out << '[' << cell.m_a << ", " << cell.m_u << ", "
		<< cell.m_b << ']';
	return out;
}
