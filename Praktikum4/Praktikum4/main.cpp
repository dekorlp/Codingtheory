#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix mat;
	mat.CreateKontrollMatrix(3);
	mat.CreateGeneratorMatrix();
	return 0;
}