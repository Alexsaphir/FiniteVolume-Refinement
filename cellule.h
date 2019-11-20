#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>

class Cellule
{
	friend class Maillage;

public:
	Cellule() = default;
	Cellule(double a, double b, double uin = 0., Cellule* next = nullptr);
	Cellule(const Cellule& cell);

	bool isTail() const;

	double length() const;
	double mid() const;

public:
	double a {0};
	double b {1};

	double uin {0};

	Cellule* next {nullptr};

	friend std::ostream& operator<<(std::ostream& out, const Cellule& cell);
};

std::ostream& operator<<(std::ostream& out, const Cellule& cell);

#endif // CELLULE_H
