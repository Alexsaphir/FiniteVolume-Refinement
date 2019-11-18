#include "maillage.h"

#include <iostream>
#include <stdexcept>

#include "cellule.h"

Maillage::Maillage() : Maillage(0., 1.) {}

Maillage::Maillage(double a, double b)
{
	m_tete		 = new Cellule(a, b, 0.);
	m_nbCellules = 1;
}

Maillage::Maillage(double a, double b, double (*u0)(double)) {}

Maillage::~Maillage()
{
	auto cell = m_tete;
	while (cell != nullptr)
	{
		cell   = m_tete;
		m_tete = m_tete->next;
		delete cell;
	}
}

int Maillage::consultPosition(uint position, double &valeur) const
{
	valeur = (*this)[position];

	try
	{
		valeur = (*this)[position];
	} catch (std::exception &e)
	{
		std::cout << e.what() << '\n';
		return -1;
	}

	return 0;
}

double Maillage::operator[](uint position) const
{
	auto cell = m_tete;

	if (cell == nullptr)
		throw std::out_of_range("Maillage::operator[](uint position)");

	for (uint i = 0; i < position; ++i)
	{
		cell = cell->next;
		if (cell == nullptr)
			throw std::out_of_range("double Maillage::operator[](uint position)");
	}

	return cell->uin;
}

double &Maillage::operator[](uint position)
{
	auto cell = m_tete;

	if (cell == nullptr)
		throw std::out_of_range("double &Maillage::operator[](uint position)");

	for (uint i = 0; i < position; ++i)
	{
		cell = cell->next;
		if (cell == nullptr)
			throw std::out_of_range("double &Maillage::operator[](uint position)");
	}

	return cell->uin;
}
