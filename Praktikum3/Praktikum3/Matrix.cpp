#include "Matrix.h"

Matrix::Matrix()
{

}

void Matrix::CreateGeneratorMatrix(std::vector < std::vector<int>> values, int p)
{
	this->m_Values = values;
	this->p = p;
}

void Matrix::CreateCanonicalMatrix()
{


	// https://rosettacode.org/wiki/Reduced_row_echelon_form#C.23

	int lead = 0, rowCount = m_Values.size(), columnCount = m_Values[0].size();

	// print Matrix Form
	std::cout << "Input Matrix: " << std::endl;
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			std::cout << m_Values[i][j] << " ";
		}

		std::cout << std::endl;
	}

	// create matrix in stairs form
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
				// first 1 is in the correct position
				break;
			}
			else
			{
				// first 1 is not in the correct position
				// so make triangle change
				if (m_Values[i][j] == 1)
				{
					for (int k = 0; k < rowCount; k++)
					{
						int temp = m_Values[k][i];
						m_Values[k][i] = m_Values[k][j];
						m_Values[k][j] = temp;
					}
					break;
				}
			}
		}
		
	}

	// print Matrix in canonical Form
	std::cout << std::endl,
	std::cout << "Canonical Matrix: " << std::endl;
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			std::cout << m_Values[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void Matrix::CreateControlMatrix()
{
	//std::cout << std::endl;
	//std::cout << std::endl;

	int rowCount = m_Values.size(), columnCount = m_Values[0].size();

	// grab back part, which is not the identity matrix
	std::vector<std::vector<int>> backPart;
	for (int i = 0; i < rowCount; i++)
	{
		std::vector<int> row;

		for (int j = rowCount; j < columnCount; j++)
		{
			//std::cout << m_Values[i][j] << " ";
			row.push_back(m_Values[i][j]);
		}
		backPart.push_back(row);

		//std::cout << std::endl;
	}

	/*std::vector < std::vector<int>> backPart(
		{
			{ 1, 1, 0},
			{1, 1, 2}
		});*/

	std::vector<std::vector<int>> transposed;
	transposed.resize(backPart[0].size());
	for (int i = 0; i < transposed.size(); i++)
	{
		transposed[i].resize(backPart.size());
	}

	for (int i = 0; i < backPart.size(); i++)
	{
		for (int j = 0; j < backPart[i].size(); j++)
		{
			transposed[j][i] = ((-backPart[i][j]) + p)%p;
			int test = 0;
		}
	}

	int rowCountTransposed = transposed.size(), columnCountTransposed = transposed[0].size();

	int identityCounter = 0;
	// append identity matrix
	for (int i = 0; i < transposed.size(); i++)
	{
		for (int j = 0; j < rowCountTransposed; j++)
		{
			if (j == identityCounter)
			{
				transposed[i].push_back(1);
			}
			else
			{
				transposed[i].push_back(0);
			}
		}
		identityCounter++;
	}

	Controlmatrix = transposed;

	// print Matrix in canonical Form
	std::cout << std::endl,
		std::cout << "Control Matrix: " << std::endl;
	for (int i = 0; i < Controlmatrix.size(); i++)
	{
		for (int j = 0; j < Controlmatrix[i].size(); j++)
		{
			std::cout << Controlmatrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void Matrix::CreateSyndromeTable(int q)
{


}