#include "solverfv.h"

#include "cell.h"

SolverFV::SolverFV() {}

void SolverFV::doStep()
{
	double fluxLeft {0};
	double fluxRight {0};

	auto  previousCell = m_Mesh.m_head;
	Cell* currentCell {nullptr};
	Cell* nextCell {nullptr};

	// Boucle sur l'ensemble des valeurs du maillage intérieur
	// On a donc que il ya au moins une cellule dans l'interieur
	// B I ... I B
	// au moins
	// B I B

	for (uint i = 1; i < m_Mesh.m_nbCells - 1; ++i)
	{
		currentCell = previousCell->m_next;
		nextCell	= currentCell->m_next;

		fluxRight =
	}
}
