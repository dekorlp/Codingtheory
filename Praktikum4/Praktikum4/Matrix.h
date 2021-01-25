#pragma once
#include <iostream>
#include <vector>

class Matrix
{
public:
	void CreateGeneratorMatrix(int m); // 1


	

private:
	void GenerateAllBinaries(int n, std::vector<int> &arr, int i, std::vector<std::vector<int>> *tuple);
	void PrintMatrix(int rowCount, int columnCount, std::vector<std::vector<int>> matrix);
	void TransposeMatrix(std::vector<std::vector<int>> &matrix);

	int q = 3;

};