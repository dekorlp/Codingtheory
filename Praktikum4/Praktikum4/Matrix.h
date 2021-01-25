#pragma once
#include <vector>

class Matrix
{
public:
	void CreateGeneratorMatrix(int m); // 1

private:
	void GenerateAllBinaries(int n, std::vector<int> &arr, int i, std::vector<std::vector<int>> *tuple);
	int q = 3;

};