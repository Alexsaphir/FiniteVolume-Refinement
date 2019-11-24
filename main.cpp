#include <iostream>

#include <mesh.h>

int main()
{
	Mesh mesh(-2.,2.,4.);

	auto mean = [](double uL, double uR) { return .5 * (uL + uR); };
	//auto u0   = [](double x) { return (x < .5 ? 0. : 1.); };
	//auto u0 = [](double x) { return 1.; };
	auto u0 = [](double x) { return x; };

	//mesh.evaluateOn(u0);

	std::cout << mesh << "\n";


	return 0;
}
