#include "solverfv.h"

#include "cell.h"

SolverFV::SolverFV() {}

void SolverFV::doStep()
{

	// FIXME On peut faire mieux
	if (m_Mesh.m_nbCells < 3)
		return; // Du fait de la condition au bord périodiqe

	Cell* previousCell {nullptr};
	Cell* currentCell = m_Mesh.m_head;
	Cell* nextCell	  = m_Mesh.m_head->m_next;

	// Boucle sur l'ensemble des valeurs du maillage intérieur
	// On a donc que il ya au moins une cellule dans l'interieur
	// B I ... I B
	// au moins
	// B I B

	// On rappelle que les conditions au bord sont périodique
	double fluxLeft {0.};
	double fluxRight {0.};

	double dt = 0;

	// On calcule le flux doit entre la cellule de bord gauche et la cellule
	// interieur gauche
	fluxRight = g(currentCell->m_u, nextCell->m_u);

	for (uint i = 1; i < m_Mesh.m_nbCells - 1; ++i)
	{
		// On permutte alors les cellules
		previousCell = currentCell;
		currentCell	 = nextCell;
		nextCell	 = nextCell->m_next;

		// De meme pour les flux
		fluxLeft  = fluxRight;
		fluxRight = g(currentCell->m_u, nextCell->m_u);

		// On peut alors remplacer la valeur sur le maillage

		// BUG Formule non correcte
		currentCell->m_u = currentCell->m_u + dt / currentCell->length() * (fluxRight - fluxLeft);
	}

	// On peut alors traiter les conditions au bord.
	// On utilise la consistence du flux numérique g(u,u) = f(u)
	// On a donc
}

double SolverFV::g(double uL, double uR) const
{
	return 0;
}

double SolverFV::getCFL() const
{
	// On doit trouver le dt minimal suffisant
	// cad trouver le min de dx/fp(u)
	double cfl = 1;

	auto cell = m_Mesh.m_head;
	for (int i = 0; i < m_Mesh.m_nbCells; ++i, cell = cell->m_next)

		return cfl;
}

double SolverFV::f(double u) const
{
	return 0;
}

double SolverFV::fDer(double u) const
{
	return 0;
}
