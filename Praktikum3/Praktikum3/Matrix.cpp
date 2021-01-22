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
	PrintMatrix(rowCount, columnCount, m_Values);

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
				for (int k = 0; k < columnCount; k++)
				{
					m_Values[j][k] -= (sub * m_Values[r][k]);
					int test = 0;
				}
			}
		}
		lead++;
	}


	MoveUnitMatrix(m_Values);
	ApplyMod(m_Values);

	// print Matrix in canonical Form
	std::cout << std::endl,
	std::cout << "Canonical Matrix: " << std::endl;
	PrintMatrix(rowCount, columnCount, m_Values);
}

void Matrix::CreateControlMatrix()
{
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

	// print control Matrix in canonical Form
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

	// transpose 
	std::vector<std::vector<int>> transposedControlMatrix;
	transposedControlMatrix.resize(Controlmatrix[0].size());

	for (int i = 0; i < Controlmatrix.size(); i++)
	{
		for (int j = 0; j < Controlmatrix[0].size(); j++)
		{
			transposedControlMatrix.at(j).push_back(Controlmatrix[i][j]);
		}
	}

	Controlmatrix = transposedControlMatrix;

	// print transposed control Matrix in canonical Form
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

void Matrix::CreateControlMatrix(std::vector < std::vector<int>> values, int p)
{
	this->p = p;
	this->Controlmatrix = values;

	// transpose 
	std::vector<std::vector<int>> transposedControlMatrix;
	transposedControlMatrix.resize(Controlmatrix[0].size());

	for (int i = 0; i < Controlmatrix.size(); i++)
	{
		for (int j = 0; j < Controlmatrix[0].size(); j++)
		{
			transposedControlMatrix.at(j).push_back(Controlmatrix[i][j]);
		}
	}

	Controlmatrix = transposedControlMatrix;

	// print transposed control Matrix in canonical Form
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

void Matrix::CreateSyndromeTable()
{
	int codelength = Controlmatrix.size();
	int messageLength = Controlmatrix[0].size();
	int dimension = -1 * messageLength + codelength;

	//int countKeys = pow(p, codelength - dimension);

	std::vector<int> arr;
	arr.resize(codelength);
	std::vector<std::vector<int>> tuples;
	GenerateAllBinaries(codelength, arr, 0, &tuples);

	for (int i = 0; i < tuples.size(); i++)
	{
		//FillMap(tuples[24], Controlmatrix);
		FillMap(tuples[i], Controlmatrix);
	}

	int test = 0;
}

void Matrix::GenerateAllBinaries(int n, std::vector<int> &arr, int i, std::vector<std::vector<int>> *tuple)
{
	if (i == n)
	{
		tuple->push_back(arr);
		return;
	}

	for (int j = 0; j < p; j++)
	{
		arr[i] = j;
		GenerateAllBinaries(n, arr, i + 1, tuple);
	}
}

void Matrix::FillMap(std::vector<int> tuple, std::vector<std::vector<int>> Controlmatrix)
{
	std::vector<int> value;
	
	for (int i = 0; i < Controlmatrix[0].size(); i++)
	{
		int result = 0;
		for (int j = 0; j < tuple.size(); j++) // length of tuple = size of Controlmatrix (count columns)
		{
			result += Controlmatrix[j][i] * tuple[j];
			result %=p;
		}
		value.push_back(result);
	}

	// insert into map
	if (syndromeTable.find(value) == syndromeTable.end())
	{
		std::vector<std::vector<int>> entries;
		entries.push_back(tuple);

		// not found in dictionary
		syndromeTable.insert(std::pair< std::vector<int>, std::vector<std::vector<int>>>(value, entries));
		int test = 0;
	}
	else
	{
		syndromeTable.find(value)->second.push_back(tuple);
		// found in dictionary
		int test = 0;
	}
}

void Matrix::PrintMatrix(int rowCount, int columnCount, std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void Matrix::MoveUnitMatrix(std::vector<std::vector<int>> matrix)
{
	int rowCount = m_Values.size();

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
}

void Matrix::ApplyMod(std::vector<std::vector<int>> matrix)
{
	int rowCount = m_Values.size(), columnCount = m_Values[0].size();

	// use modulo on matrix
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			m_Values[i][j] = m_Values[i][j] % p;
			if (m_Values[i][j] < 0)
			{
				m_Values[i][j] = m_Values[i][j] + p;
			}
		}

	}
}

void Matrix::ErrorCorrection(std::string message)
{
	std::vector<int> messageVec;
	
	// convert to int vector
	for (int i = 0; i < message.size(); i++)
	{
		messageVec.push_back((int)message[i] - 48);
		int test = 0;
	}

	// generate class of syndrome table
	std::vector<int> classNumber;
	for (int i = 0; i < Controlmatrix[0].size(); i++)
	{
		int result = 0;
		for (int j = 0; j < messageVec.size(); j++) // length of tuple = size of Controlmatrix (count columns)
		{
			result += Controlmatrix[j][i] * messageVec[j];
			result %= p;
		}
		classNumber.push_back(result);
	}


	std::vector<int> correction = syndromeTable.find(classNumber)->second[0]; // if there are more than one, chose one element of the collection
	std::vector<int> resultVec;

	// subtract and calculate mod p
	for (int i = 0; i < correction.size(); i++)
	{
		int result = messageVec[i] - correction[i];
		result = result % p;
		if (result < 0)
		{
			result += p;
		}
		resultVec.push_back(result);
	}

	// print corrected message
	std::cout << std::endl;
	std::cout << "Corrected Message: " << std::endl;
	for (auto i : resultVec)
		std::cout << i;
	
	// calculate Hamington Distance
	int hamingtonCounter = 0;
	for (int i = 0; i < resultVec.size(); i++)
	{
		if (messageVec[i] != resultVec[i])
		{
			hamingtonCounter++;
		}
	}

	// print hamington distance
	std::cout << std::endl;
	std::cout << "Hamington Distance: " << hamingtonCounter << std::endl;
}