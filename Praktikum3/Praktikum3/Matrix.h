#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

class Matrix
{
private:
	std::vector<std::vector<int>> m_Values; // Generatormatrix
	std::vector<std::vector<int>> Controlmatrix; // Controlmatrix
	std::map<std::vector<int>, std::vector<int>> syndromeTable;

	int p = 0;
public:
	Matrix();
	void CreateGeneratorMatrix(std::vector < std::vector<int>> values, int p); // definition
	void CreateCanonicalMatrix(); // 1
	void CreateControlMatrix(); // 2
	void CreateSyndromeTable(int q); // 3


};