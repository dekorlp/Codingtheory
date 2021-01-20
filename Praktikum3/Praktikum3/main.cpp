
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
	mat.CreateGeneratorMatrix(Generatormatrix, 3);
	mat.CreateCanonicalMatrix();
	mat.CreateControlMatrix();
	mat.CreateSyndromeTable(2);

	return 0;
}