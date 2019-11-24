#include "mesh.h"

#include "cell.h"


Mesh::Mesh() :Mesh(0,1,1)
{}

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
         while(cell != nullptr)
         {
           out << "  " << *cell << '\n';
           cell = cell->m_next;
         }

	return out;
}
