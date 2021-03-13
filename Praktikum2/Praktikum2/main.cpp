#include "PolynomManager.h"

int main()
{
	PolynomManager man;
	//man.CreateTable(8);
	// Erstes Beispiel:
	//Polynom result = man.CalculateInverse(Polynom({ PolynomPart(1,5), PolynomPart(1,4), PolynomPart(1,3), PolynomPart(1,2), PolynomPart(1,1), PolynomPart(1,0) }));

	// Zweites Beispiel:
	//Polynom result = man.CalculateInverse(Polynom({ PolynomPart(1,2), PolynomPart(1,0) }));
	
	// Drittes Beispiel:
	//Polynom result = man.CalculateInverse(Polynom({ PolynomPart(1,1), PolynomPart(1,0) }));

	// Viertes Beispiel:
	//Polynom result = man.CalculateInverse(Polynom({ PolynomPart(1,2), PolynomPart(1,1) }));

	// Fünftes Beispiel:
	Polynom result = man.CalculateInverse(Polynom({ PolynomPart(1,2)}));

	int test = 0;

	return 0;
}