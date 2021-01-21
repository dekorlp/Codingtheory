#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

class Matrix
{
private:
	std::vector<std::vector<int>> m_Values; // Generatormatrix
	std::vector<std::vector<int>> Controlmatrix; // Controlmatrix
	std::map<std::vector<int>, std::vector<int>> syndromeTable;
	int p = 0;

	void GenerateAllBinaries(int n, std::vector<int> &arr, int i, std::vector<std::vector<int>> *tuple);

public:
	Matrix();
	void CreateGeneratorMatrix(std::vector < std::vector<int>> values, int p); // definition
	void CreateCanonicalMatrix(); // 1
	void CreateControlMatrix(std::vector < std::vector<int>> values, int p); // 2 (For Debugging and testing)
	void CreateControlMatrix(); // 2
	void CreateSyndromeTable(int q); // 3


};