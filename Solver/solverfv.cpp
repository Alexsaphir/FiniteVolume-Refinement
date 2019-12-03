#include "solverfv.h"

#include <fstream>
#include <utility>

#include "Mesh/cell.h"

SolverFV::SolverFV(ProblemIC pIC, ProblemMesh pM,
				   ProblemFile file)
	: m_pIC(pIC), m_file(std::move(file))
{
	m_Mesh = Mesh(pM);

	m_Mesh.applyFunctionOnMesh(pIC.u0);

	// m_Mesh.updateMesh(.001, 1., 0., 1.);
	std::cout << m_Mesh;
	// m_Mesh.applyFunctionOnMesh(u0);
}

void SolverFV::doStep()
{

	// FIXME On peut faire mieux
	if (m_Mesh.m_nbCells < 3)
		return; // Du fait de la condition au bord périodiqe

	// m_Mesh.updateMesh(.001, 1., 0., .01);
	Cell* currentCell = m_Mesh.startList();
	Cell* nextCell	  = currentCell->m_next;

	// Boucle sur l'ensemble des valeurs du maillage
	// intérieur On a donc que il ya au moins une cellule
	// dans l'interieur B I ... I B au moins B I B

	// On rappelle que les conditions au bord sont périodique
	double fluxLeft {0.};
	double fluxRightEnd {0.};
	double fluxRight {0.};

	double dt = std::min(m_pIC.dt_max, getCFL());
	double dx = currentCell->length();

	// On calcule le flux doit entre la cellule de bord
	// gauche et la cellule interieur gauche
	fluxRight = g(currentCell->m_u, nextCell->m_u, dx, dx,
				  dt);
	fluxRightEnd = fluxRight;

	for (uint i = 1; i < m_Mesh.m_nbCells - 1; ++i)
	{
		// On permutte alors les cellules
		currentCell = nextCell;
		nextCell	= nextCell->m_next;
		dx			= currentCell->length();

		// De meme pour les flux

		fluxLeft  = fluxRight;
		fluxRight = g(currentCell->m_u, nextCell->m_u, dx,
					  dx, dt);
		// On peut alors remplacer la valeur sur le maillage

		currentCell->m_u = currentCell->m_u
						   - dt / dx
								 * (fluxRight - fluxLeft);
	}

	m_Mesh.startList()->m_u = m_Mesh.startList()->m_u
							  - dt / dx
									* (fluxRightEnd
									   - fluxRight);
	currentCell->m_next->m_u = m_Mesh.startList()->m_u;

	// On peut alors traiter les conditions au bord.
	// On utilise la consistence du flux numérique g(u,u) =
	// f(u) On a donc

	t += dt;
}

double SolverFV::getCFL() const
{
	// On doit trouver le dt minimal suffisant
	// cad trouver le min de dx/fp(u)
	double cfl = 0.;

	auto cell = m_Mesh.m_head;
	cfl = .5 * cell->length() / std::abs(fDer(cell->m_u));
	for (int i = 0; i < m_Mesh.m_nbCells;
		 ++i, cell = cell->m_next)
	{
		cfl = std::min(cfl, .5 * cell->length()
								/ std::abs(f(cell->m_u)));
	}
	return cfl;
}

void SolverFV::solve()
{
	m_Mesh.plotToFile(m_file.u0);
	std::ofstream fileE(m_file.energy, std::ios::trunc);
	std::ofstream fileErr(m_file.errorOverTime,
						  std::ios::trunc);

	while (t < m_pIC.Tmax)
	{
		fileE << t << ',' << m_Mesh.computeMass() << '\n';
		fileErr << t << ','
				<< m_Mesh.computeError(*m_pIC.u_exa, t)
				<< '\n';
		std::cout << t << "s\n";
		doStep();
	}
	fileE << t << ',' << m_Mesh.computeMass() << '\n';
	fileErr << t << ','
			<< m_Mesh.computeError(*m_pIC.u_exa, t) << '\n';

	m_Mesh.plotToFile(m_file.uTmax);
	fileE.close();
	fileErr.close();

	std::cout << m_Mesh.computeError(*m_pIC.u_exa, t);
}
