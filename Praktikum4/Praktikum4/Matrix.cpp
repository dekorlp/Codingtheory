#include "Matrix.h"

void Matrix::CreateKontrollMatrix(int m)
{
	std::vector<std::vector<int>> matrix;
	
	for (int i = m; i > 0; i--)
	{
		// generate Binary Combinations
		std::vector<std::vector<int>> tuples;
		std::vector<int> arr;
		arr.resize(i-1);
		GenerateAllBinaries(i-1, arr, 0, &tuples);


		// fill Matrix
		for (int j = 0; j < tuples.size(); j++)
		{
			std::vector<int> value;
			int counter = i - 1;
			while (counter != m)
			{
				if (m - counter == 1)
				{
					value.push_back(1);
				}
				else
				{
					value.push_back(0);
				}
				counter++;
			}
			value.insert(std::end(value), std::begin(tuples[j]), std::end(tuples[j]));
			matrix.push_back(value);
		}
	}

	TransposeMatrix(matrix);

	std::cout << "Control Matrix: " << std::endl;
	PrintMatrix(matrix.size(), matrix[0].size(), matrix);

	mControlMatrixMatrix = matrix;

}

void Matrix::CreateGeneratorMatrix()
{
	std::vector<std::vector<int>> matrix = mControlMatrixMatrix;
	MoveUnitMatrix(matrix);
	std::cout << std::endl;
	//PrintMatrix(matrix.size(), matrix[0].size(), matrix);

	int rowCount = matrix.size(), columnCount = matrix[0].size();

	// grab back part, which is not the identity matrix
	std::vector<std::vector<int>> backPart;
	for (int i = 0; i < rowCount; i++)
	{
		std::vector<int> row;

		for (int j = rowCount; j < columnCount; j++)
		{
			//std::cout << m_Values[i][j] << " ";
			row.push_back(matrix[i][j]);
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
			transposed[j][i] = ((-backPart[i][j]) + q) % q;
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

	mGeneratorMatrixMatrix = transposed;

	// print control Matrix in canonical Form
	std::cout << std::endl,
		std::cout << "Generator Matrix: " << std::endl;
	for (int i = 0; i < mGeneratorMatrixMatrix.size(); i++)
	{
		for (int j = 0; j < mGeneratorMatrixMatrix[i].size(); j++)
		{
			std::cout << mGeneratorMatrixMatrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void Matrix::GenerateAllBinaries(int n, std::vector<int> &arr, int i, std::vector<std::vector<int>> *tuple)
{
	if (i == n)
	{
		tuple->push_back(arr);
		return;
	}

	for (int j = 0; j < q; j++)
	{
		arr[i] = j;
		GenerateAllBinaries(n, arr, i + 1, tuple);
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

void Matrix::TransposeMatrix(std::vector<std::vector<int>> &matrix)
{
	// transpose 
	std::vector<std::vector<int>> transposedControlMatrix;
	transposedControlMatrix.resize(matrix[0].size());

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			transposedControlMatrix.at(j).push_back(matrix[i][j]);
		}
	}

	matrix = transposedControlMatrix;
}

void Matrix::MoveUnitMatrix(std::vector<std::vector<int>> &matrix)
{
	std::vector<std::vector<int>> identityParts;
	std::vector<int> identityPositions;
	int m = matrix.size();

	for (int i = 0; i < m; i++)
	{
		std::vector<int> value;
		for(int j = 0; j < m; j++)
		{
			if (i == j)
			{
				value.push_back(1);
			}
			else
			{
				value.push_back(0);
			}
		}
		identityParts.push_back(value);
	}

	TransposeMatrix(matrix);

	for (int i = 0; i < identityParts.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[j] == identityParts[i])
			{
				identityPositions.push_back(j);
				break;
			}
		}
	}

	//TransposeMatrix(matrix);

	// create new Matrix
	std::vector<std::vector<int>> editedMatrix;
	editedMatrix.resize(matrix.size());
	for (int i = 0; i < identityPositions.size(); i++)
	{
		editedMatrix[i] = identityParts[i];
	}
	for (int i = editedMatrix[0].size(); i < matrix.size(); i++)
	{		
		if (std::find(identityPositions.begin(), identityPositions.end(), i) == identityPositions.end()) // not found
		{
			editedMatrix[i] = matrix[i];
		}
		else // found
		{
			int index = -1;
			for (int j = 0; j < identityPositions.size(); j++)
			{
				if (identityPositions[j] == i)
				{
					index = j;
					break;
				}
			}

			editedMatrix[i] = matrix[index];
		}
	}

	TransposeMatrix(editedMatrix);

	matrix = editedMatrix;
}
