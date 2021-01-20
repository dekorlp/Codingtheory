#pragma once

#include <vector>
#include <iostream>

class Matrix
{
private:
	std::vector<std::vector<int>> m_Values; // Generatormatrix
	std::vector<std::vector<int>> Controlmatrix; // Controlmatrix

	int q = 0;
public:
	Matrix();
	void CreateGeneratorMatrix(std::vector < std::vector<int>> values, int q); // definition
	void CreateCanonicalMatrix(); // 1
	void CreateControlMatrix(); // 2


};