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
		std::vector<int> value;
		int counter = i-1;
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
		value.insert(std::end(value), std::begin(arr), std::end(arr));
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

	for (int j = 0; j < q; j++)
	{
		arr[i] = j;
		GenerateAllBinaries(n, arr, i + 1, tuple);
	}
}