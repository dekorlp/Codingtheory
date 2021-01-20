
#include <vector>
#include "Matrix.h"

int main()
{
	std::vector < std::vector<int>> Generatormatrix(
		{
			{ 0, 0, 0, 1, 1, 1},
			{0, 1, 1, 0, 1, 2},
			{1, 0, 1, 1, 2, 1 } 
		});

	Matrix mat;
	mat.CreateGeneratorMatrix(Generatormatrix);
	mat.CreateCanonicalMatrix();
	mat.CreateControlMatrix(3);

	return 0;
}