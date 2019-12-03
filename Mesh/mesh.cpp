#include "mesh.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include "cell.h"

Mesh::Mesh() : Mesh(ProblemMesh())
{
}

Mesh::Mesh(ProblemMesh pMesh) : m_pMesh(pMesh)
{
	m_nbCells	= 0;
	double step = (pMesh.xmax - pMesh.xmin)
				  / pMesh.nbCellInitial;
	for (uint i = pMesh.nbCellInitial; i > 0; --i)
	{
		pushCell_front({pMesh.xmin + step * (i - 1.),
						pMesh.xmin + step * (i), 0});
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

bool Mesh::splitCell(Cell* cell, double ratio)
{
	double l = cell->length();
	double b = cell->m_b;

	// Création d'une nouvelle cellule et insertion dans la liste
	auto newcell = new (std::nothrow)
		Cell(b - ratio * l, b, cell->m_u, cell->m_next);
	if (!newcell)
		return false;

	cell->m_next = newcell;
	cell->m_b	 = newcell->m_a;
	++m_nbCells;
	return true;
}

void Mesh::fuseCell(Cell* cellDest)
{
	// On fuse la cellule suivante à celle passée en argument
	auto tmp = cellDest->m_next;
	if (tmp == nullptr)
		return;

	double u = cellDest->m_u * cellDest->length()
			   + tmp->m_u * tmp->length();
	u = u / (cellDest->length() + tmp->length());

	cellDest->m_b	 = tmp->m_b;
	cellDest->m_next = tmp->m_next;
	cellDest->m_u	 = u;
	--m_nbCells;
	delete tmp;
}

void Mesh::updateMesh(double dxMin, double dxMax,
					  double duMin, double duMax)
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

	// On raffine le maillage
	while (next != nullptr)
	{
		next	  = current->m_next;
		double du = std::abs(current->m_u - next->m_u)
					/ (next->mid() - current->mid());

		if (du > duMax)
		{
			bool block1Done {false};
			bool block2Done {false};

			double coeff = .5;

			if (current->length() >= 2. * dxMin)
			{
				block1Done = true;
				splitCell(current, coeff);
			}
			if (next->length() >= 2. * dxMin)
			{
				block2Done = true;
				splitCell(next, 1 - coeff);
			}

			if (block1Done && block2Done)
			{
				// continue;
			}

			//			current = current->m_next;
			//			next	= current->m_next;

			// On interpolle maintenant
			// on calcule l'équation de la droite (alpha*x +
			// beta) passant par les deux cellules extremes
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
		file << cell->m_a + .5 * cell->length() << ','
			 << cell->m_u << '\n';
		cell = cell->m_next;
	}

	file.close();
}

void Mesh::plotToFile(const std::string& filename) const
{
	std::ofstream file(filename, std::ios::trunc);

	auto cell = m_head;
	while (cell != nullptr)
	{
		double dx = cell->length() / 10.;
		for (int i = 0; i <= 10; ++i)
		{
			file << cell->m_a + i * dx << ',' << cell->m_u
				 << '\n';
		}
		cell = cell->m_next;
	}

	file.close();
}

void Mesh::applyFunctionOnMesh(double (*f)(double))
{
	auto cell = m_head;
	while (cell != nullptr)
	{
		cell->m_u = integrate(f, *cell, 1000)
					/ cell->length();
		cell = cell->m_next;
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

double Mesh::integrate(double (*f)(double),
					   const Cell& cell, uint N)
{
	double l  = cell.m_b - cell.m_a;
	double dx = l / (N - 1);

	double y = 0.;
	double x = cell.m_a;

	for (int i = 0; i < N; ++i)
	{
		y += dx * f(x);
		x += dx;
	}
	return y;
}

double Mesh::integrate(double (*f)(double, double), double t,
					   const Cell& cell, uint N)
{
	double l  = cell.m_b - cell.m_a;
	double dx = l / (N - 1);

	double y = 0.;
	double x = cell.m_a;

	for (int i = 0; i < N; ++i)
	{
		y += dx * f(x,t);
		x += dx;
	}
	return y;
}

double Mesh::computeMass() const
{
	double mass {0.};
	auto   cell = startList();//->m_next;
	while (cell != nullptr)
	{
		mass += cell->m_u * cell->length();
		cell = cell->m_next;
	}
	return mass;
}

double Mesh::computeError(double (*u_exa)(double x, double t), double t)
{
	double error {0.};

	auto cell = m_head;
	while (cell != nullptr)
	{
		error += std::abs(cell->m_u*cell->length()
						  - integrate(u_exa,t, *cell, 1000)
								);
		cell = cell->m_next;
	}
	return error/m_nbCells;
}

double Mesh::operator[](uint pos) const
{
	if (pos >= m_nbCells)
		return 0;
	auto cell = startList();
	for (uint i = 0; i < pos; ++i)
	{
		cell = cell->m_next;
	}
	return cell->m_u;
}