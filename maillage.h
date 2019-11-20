#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <iostream>

class Cellule;

class Maillage
{
public:
	Maillage();
	Maillage(double a, double b);
	// Maillage(double a, double b, double (*u0)(double));

	Maillage(const Maillage& M);
	~Maillage();

	// Vérifie si il existe une cellule avec un tel index
	[[nodiscard]] bool isValidCell(uint position) const;
	// Permet d'avoir l'adresse d'une cellule
	Cellule* findCell(uint position);

	int  addPosition(double valeur, uint position);
	void removePosition(uint position);

	void insertCellBetween(Cellule* A, Cellule* B);

	void splitCell(uint position); // Split la cellule en 2 en ajoutant une nouvelle cellule apres
	void splitCell(Cellule* cell);

	void fuseCell(uint position,
				  double (*deduce)(double, double)); // Fuse la cellule avec la suivante
	void fuseCell(Cellule* cell, double (*deduce)(double, double));

	int consultPosition(uint position, double& valeur) const;

	void evaluateOn(double (*f)(double));

	//double projL2(double a, double b, double (*f)(double)) const;

private:
	Cellule* m_tete {nullptr};
	uint	 m_nbCellules {0};

	double m_sizeCellMin {.1};
	double m_diffMinToSplit {.2};

	double  operator[](uint position) const;
	double& operator[](uint position);

	friend std::ostream& operator<<(std::ostream&, const Maillage&);
};

std::ostream& operator<<(std::ostream& out, const Maillage& M);

#endif // MAILLAGE_H
