#include "cellule.h"

Cellule::Cellule()
= default;

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
