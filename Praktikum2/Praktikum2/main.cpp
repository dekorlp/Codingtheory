#include "PolynomManager.h"

int main()
{
	PolynomManager man;
	man.CreateTable(8);

	Polynom pol1({ PolynomPart(0,0) , PolynomPart(2,1), PolynomPart(4,1) });
	Polynom pol2({ PolynomPart(1,1), PolynomPart(1,0) });

	Polynom TEstPolynom = pol2 + pol1;

	int test = 0;

	return 0;
}