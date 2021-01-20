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
	// https://rosettacode.org/wiki/Reduced_row_echelon_form#C.23

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

	// change columns
	for (int i = 0; i < m_Values.size(); i++)
	{
		for (int j = 0; j < m_Values[i].size(); j++)
		{
			if (m_Values[i][j] == 1 && i == j)
			{
				break;
			}
			else
			{
				int test = 0;
				if (m_Values[i][j] == 1)
				{
					for (int k = 0; k < rowCount; k++)
					{
						int temp = m_Values[k][i];
						m_Values[k][i] = m_Values[k][j];
						m_Values[k][j] = temp;
						int test = 0;
					}
					break;
				}
			}
		}
		
	}
}