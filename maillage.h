#ifndef MAILLAGE_H
#define MAILLAGE_H

#include <iostream>

class Cellule;

class Maillage
{
public:
	Maillage();
	Maillage(double a, double b);
	Maillage(double a, double b, double (*u0)(double));

	Maillage(const Maillage &M);
	~Maillage();

	int  addPosition(double valeur, uint position);
	void removePosition(uint position);

	int consultPosition(uint position, double &valeur) const;

	double projL2(double a, double b, double (*f)(double)) const;

private:
	Cellule *m_tete;
	uint	 m_nbCellules;

	double  operator[](uint position) const;
	double &operator[](uint position);

	friend std::ostream &operator<<(std::ostream &, const Maillage &);
};

#endif // MAILLAGE_H
