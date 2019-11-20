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

// Maillage::Maillage(double a, double b, double (*u0)(double)) {}

Maillage::~Maillage()
{
	auto cell = m_tete;
	while (m_tete != nullptr)
	{
		cell   = m_tete;
		m_tete = cell->next;
		delete cell;
	}
}

bool Maillage::isValidCell(uint position) const
{
	return position < m_nbCellules;
}

Cellule* Maillage::findCell(uint position)
{
	if (!isValidCell(position))
		throw std::logic_error(
			"Cellule* Maillage::findCell(uint position)\n La cellule n'est pas dans le maillage");

	auto current = m_tete;

	for (uint i = 0; i < position; ++i)
	{
		current = current->next;
	}

	return current;
}

void Maillage::insertCellBetween(Cellule* A, Cellule* B)
{
	// Calcul le
}

void Maillage::splitCell(uint position)
{
	auto target = findCell(position);

	splitCell(target);
}

void Maillage::splitCell(Cellule* cell)
{
	double mid = .5 * (cell->a + cell->b);

	auto inserted = new Cellule(mid, cell->b, cell->uin, cell->next);

	cell->next = inserted;
	cell->b	= mid;

	m_nbCellules++;
}

void Maillage::fuseCell(uint position, double (*deduce)(double uL, double uR))
{
	auto target = findCell(position);

	fuseCell(target, deduce);
}

void Maillage::fuseCell(Cellule* cell, double (*deduce)(double, double))
{
	auto next = cell->next;

	if (next == nullptr)
		return; // On est sur la cellule de fin

	// Remplace les valeurs dans la cellule
	cell->b	= next->b;
	cell->uin  = deduce(cell->uin, next->uin);
	cell->next = next->next;

	// Supprime la cellule qui n'est plus nécessaire
	delete next;

	m_nbCellules--;
}

int Maillage::consultPosition(uint position, double& valeur) const
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

void Maillage::evaluateOn(double (*f)(double))
{
	auto mid = [](double a, double b) -> double { return .5 * (a + b); };

	auto midDown = [mid](Cellule* cell) -> double { return mid(cell->a, cell->mid()); };
	auto midUp   = [mid](Cellule* cell) -> double { return mid(cell->mid(), cell->b); };

	auto fillMaillage = [](Cellule* tete, double (*f)(double)) {
		auto cell = tete;
		while (cell != nullptr)
		{
			cell->uin = f(cell->mid());

			cell = cell->next;
		}
	};

	// Initialisation du maillage initiale
	fillMaillage(m_tete, f);

	// Commence a diviser les cellules

	auto cell = m_tete;

	// Si il y'a une seule cellule on test si on doit splitter en 2
	if (m_nbCellules == 1)
	{
		// On regarde si la taille de la cellule est suffisament grande pour etre divisé en deux;
		if (cell->length() < 2. * m_sizeCellMin)
		{
			cell = cell->next;
			return;
		}

		// On regarde maintenant si on divise la cellule en deux si cela vaut le coup

		double fUp   = f(midUp(cell));
		double fDown = f(midDown(cell));

		if (std::abs(fUp - fDown) < m_diffMinToSplit)
		{
			cell = cell->next;
			return; // Pas besoin de raffiner plus le maillage
		}

		// On split alors la cellule
		splitCell(cell);

		// Et l'on corrige les valeurs de u
		cell->uin		= fDown;
		cell->next->uin = fUp;
	}

	// On peut maintenant raffiner Cellule par cellule
	while (cell->next != nullptr) {}
};

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

std::ostream& operator<<(std::ostream& out, const Maillage& M)
{
	out << "Infos sur le maillage\n";
	out << "Nombre de cellule : " << M.m_nbCellules << '\n';

	auto cell = M.m_tete;

	for (uint i = 0; i < M.m_nbCellules; ++i)
	{
		out << *cell << '\n';
		cell = cell->next;
	}

	return out;
}
