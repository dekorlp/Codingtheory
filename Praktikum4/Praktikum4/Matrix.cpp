#include "Matrix.h"

void Matrix::CreateGeneratorMatrix(int m)
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