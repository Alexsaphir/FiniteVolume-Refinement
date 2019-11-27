#include "mesh.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include "cell.h"

Mesh::Mesh() : Mesh(0, 1, 1) {}

Mesh::Mesh(double binf, double bsup, uint nbCell)
{
	m_nbCells = 0;

	double step = (bsup - binf) / nbCell;
	for (int i = nbCell; i > 0; --i)
	{
		pushCell_front({binf + step * (i - 1.), binf + step * (i), 0});
	}
}

void Mesh::pushCell_front(const Cell& cell)
{
	auto tmp	= new Cell(cell);
	tmp->m_next = m_head;
	m_head		= tmp;
	++m_nbCells;
}

std::ostream& operator<<(std::ostream& out, const Mesh& M)
{
	out << "\nMAILLAGE : \n";
	out << " Nombre de cellule(s) : " << M.m_nbCells << '\n';
	auto cell = M.m_head;
	while (cell != nullptr)
	{
		out << "  " << *cell << '\n';
		cell = cell->m_next;
	}

	return out;
}

void Mesh::splitCell(Cell* cell)
{
	double l = cell->length();
	double b = cell->m_b;

	// Création d'une nouvelle cellule et insertion dans la liste
	auto newcell = new Cell(b - .5 * l, b, cell->m_u, cell->m_next);
	cell->m_next = newcell;
	cell->m_b	 = newcell->m_a;
	++m_nbCells;
}

void Mesh::fuseCell(Cell* cellDest)
{
	// On fuse la cellule suivante à celle passée en argument
	auto tmp = cellDest->m_next;
	if (tmp == nullptr)
		return;

	double u = cellDest->m_u * cellDest->length() + tmp->m_u * tmp->length();
	u		 = u / (cellDest->length() + tmp->length());

	cellDest->m_b	 = tmp->m_b;
	cellDest->m_next = tmp->m_next;
	cellDest->m_u	 = u;
	--m_nbCells;
	delete tmp;
}

void Mesh::updateMesh(double dxMin, double dxMax, double duMin, double duMax)
{
	// dxMin : Taille minimum d'une cellule
	// dxMax : Taille maximum d'une cellule

	// duMax : Taux d'accroissement max autorisé
	// duMin : Taux d'accroissement min autorisé

	if (m_nbCells < 1)
		return;
	if (m_nbCells == 1)
		splitCell(m_head);

	// auto previous = endList();
	auto  current = startList();
	Cell* next	  = current->m_next;

	// On cherche la fin de la liste
	while (next != nullptr)
	{
		double du = std::abs(current->m_u - next->m_u);

		if (du > duMax)
		{
			if (cellL->length() > 2. * dx)
				splitCell(cellL);
			if (cellR->length() > 2. * dx)
				splitCell(cellR);
			continue;
		}

		current = current->m_next;
		next	= current->m_next;
	}
}

void Mesh::saveToFile(const std::string& filename) const
{
	std::ofstream file(filename, std::ios::trunc);

	auto cell = m_head;
	while (cell != nullptr)
	{
		file << cell->m_a + .5 * cell->length() << ',' << cell->m_u << '\n';
		cell = cell->m_next;
	}

	file.close();
}

void Mesh::applyFunctionOnMesh(double (*f)(double))
{
	auto cell = m_head;
	while (cell != nullptr)
	{
		cell->m_u = (*f)(cell->m_a + .5 * cell->length());
		cell	  = cell->m_next;
	}
}

Cell* Mesh::startList() const
{
	return m_head;
}

Cell* Mesh::endList() const
{
	auto tmp = m_head;

	for (int i = 1; i < m_nbCells; ++i)
		tmp = tmp->m_next;

	return tmp;
}

void Mesh::splitAndInterpolate(Cell* cellL, Cell* cellR)
{
	splitCell(cellL);
	splitCell(cellR);
}

void Mesh::splitAndInterpolate(Cell* cellL, Cell* cellR, double dx)
{
	if (cellL->length() > 2. * dx)
		splitCell(cellL);
	if (cellR->length() > 2. * dx)
		splitCell(cellR);
}
