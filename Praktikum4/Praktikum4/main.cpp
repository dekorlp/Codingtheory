#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix mat;
	mat.CreateKontrollMatrix(3);
	mat.CreateGeneratorMatrix();
	mat.ErrorCorrection("1011110");
	return 0;
}