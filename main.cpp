#include <cmath>
#include <iostream>

#include <mesh.h>

int main()
{
	Mesh mesh(-1., 1., 10);

	// auto mean = [](double uL, double uR) { return .5 * (uL + uR); };
	auto u0 = [](double x) { return (std::abs(x) < .5 ? 1. : 0.); };
	// auto u0 = [](double x) { return 1.; };
	// auto u0 = [](double x) { return x; };

	//	mesh.evaluateOn(u0);
	mesh.applyFunctionOnMesh(u0);
	mesh.saveToFile("mesh0.dat");

	std::cout << mesh << "\n";

	mesh.updateMesh(1., 1., 0., .5);
	mesh.saveToFile("mesh1.dat");
	std::cout << mesh << "\n";

	return 0;
}
