#include "cellule.h"

Cellule::Cellule(double a, double b, double uin, Cellule *next)
{
	this->a = a;
	this->b = b;

	this->uin  = uin;
	this->next = next;
}

Cellule::Cellule(const Cellule &cell)
{
	a = cell.a;
	b = cell.b;

	uin = cell.uin;

	next = cell.next;
}

bool Cellule::isTail() const
{
	return next == nullptr;
}

double Cellule::length() const
{
	return b - a;
}

double Cellule::mid() const
{
	return .5 * (a + b);
}

std::ostream& operator<<(std::ostream& out, const Cellule& cell)
{
	out << '[' << cell.a << ", " << cell.uin << ", " << cell.b << ']';
	return out;
}
