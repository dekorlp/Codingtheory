
#include <vector>
#include "Matrix.h"
#include <string>

int main()
{
	std::vector < std::vector<int>> Generatormatrix(
		{
			{ 0, 0, 0, 1, 1, 1},
			{0, 1, 1, 0, 1, 2},
			{1, 0, 1, 1, 2, 1 } 
		});

	/*std::vector < std::vector<int>> Generatormatrix(
	{
		{  1, 0, 1, 1, 0},
		{  0, 1, 1, 0, 1 },
	});*/

	Matrix mat;
	mat.CreateGeneratorMatrix(Generatormatrix, 3);
	mat.CreateCanonicalMatrix();
	mat.CreateControlMatrix();
	//mat.CreateControlMatrix(DebuggingControlMatrix, 2);
	mat.CreateSyndromeTable();
	//mat.ErrorCorrection("01001");
	mat.ErrorCorrection("010010");

	return 0;
}