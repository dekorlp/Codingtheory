#include "Matrix.h"

Matrix::Matrix()
{

}
#define N 3

void Matrix::CreateGeneratorMatrix(std::vector < std::vector<int>> values)
{
	this->m_Values = values;
}

void Matrix::CreateCanonicalMatrix()
{
	// https://www.geeksforgeeks.org/program-for-gauss-jordan-elimination-method/

	/*int i, j, k = 0, c;

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

	int test = 0;*/


	//int zeilen = 3;
	//int spalten = 6;

	//TEST+++++++++++++++++++++
	/*int[,] matrix = new int[2, 4]{
	{ 1, 2, 0, 1},
	{ 1, 0, 2, 2 },
	};*/
	//+++++++++++++++++++++++++

	int lead = 0, rowCount = m_Values.size(), columnCount = m_Values[0].size();
	for (int r = 0; r < rowCount; r++)
	{
		if (columnCount <= lead) break;
		int i = r;
		while (m_Values[i][lead] == 0)
		{
			i++;
			if (i == rowCount)
			{
				i = r;
				lead++;
				if (columnCount == lead)
				{
					lead--;
					break;
				}
			}
		}
		for (int j = 0; j < columnCount; j++)
		{
			int temp = m_Values[r][j];
			m_Values[r][j] = m_Values[i][j];
			m_Values[i][j] = temp;
		}
		int div = m_Values[r][lead];
		if (div != 0)
			for (int j = 0; j < columnCount; j++) m_Values[r][j] /= div;
		for (int j = 0; j < rowCount; j++)
		{
			if (j != r)
			{
				int sub = m_Values[j][lead];
				for (int k = 0; k < columnCount; k++) m_Values[j][k] -= (sub * m_Values[r][k]);
			}
		}
		lead++;
	}

	int test = 0;
}