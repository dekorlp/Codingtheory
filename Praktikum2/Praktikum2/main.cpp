#include "PolynomManager.h"

int main()
{
	PolynomManager man;
	//man.CreateTable(8);
	man.CalculateInverse(Polynom({ PolynomPart(1,2), PolynomPart(1,0) }));

	int test = 0;

	return 0;
}