#pragma once

#include <vector>
#include <iostream>

class Matrix
{
private:
	std::vector<std::vector<int>> m_Values; // Generatormatrix
	std::vector<std::vector<int>> Controlmatrix; // Controlmatrix

public:
	Matrix();
	void CreateGeneratorMatrix(std::vector < std::vector<int>> values); // definition
	void CreateCanonicalMatrix(); // 1
	void CreateControlMatrix(int q); // 2


};