#include "Matrix.h"

Matrix::Matrix()
{

}
#define N 3

void Matrix::CreateGeneratorMatrix(std::vector < std::vector<double>> values)
{
	this->m_Values = values;
}

void Matrix::CreateCanonicalMatrix()
{
	// https://www.geeksforgeeks.org/program-for-gauss-jordan-elimination-method/

	int i, j, k = 0, c;

	int n = m_Values.size();

	// Performing elementary operations 
	for (i = 0; i < n; i++)
	{
		if (m_Values[i][i] == 0)
		{
			c = 1;
			while ((i + c) < n && m_Values[i + c][i] == 0)
				c++;
			if ((i + c) == n) {
				//flag = 1;
				break;
			}
			for (j = i, k = 0; k <= n; k++)
				std::swap(m_Values[j][k], m_Values[j + c][k]);
			
		}

		for (j = 0; j < n; j++) {

			// Excluding all i == j 
			if (i != j) {

				// Converting Matrix to reduced row 
				// echelon form(diagonal matrix) 
				float pro = m_Values[j][i] / m_Values[i][i];

				for (k = 0; k <= n; k++)
					m_Values[j][k] = m_Values[j][k] - (m_Values[i][k]) * pro;
			}
		}

	}

	int test = 0;
}