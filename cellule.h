#ifndef CELLULE_H
#define CELLULE_H


class Cellule
{
	friend class Maillage;

public:
	Cellule();
	Cellule(double a, double b, double uin, Cellule *next = nullptr);
	Cellule(const Cellule &cell);

public:
	double a {0};
	double b {1};

	double uin {0};

	Cellule *next {nullptr};
};

#endif // CELLULE_H
