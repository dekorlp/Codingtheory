#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix mat;
	mat.CreateKontrollMatrix(2);
	mat.CreateGeneratorMatrix();
	return 0;
}