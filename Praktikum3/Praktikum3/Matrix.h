#pragma once

#include <vector>
#include <iostream>

class Matrix
{
private:
	std::vector<std::vector<int>> m_Values;

public:
	Matrix();
	void CreateGeneratorMatrix(std::vector < std::vector<int>> values); // definition
	void CreateCanonicalMatrix(); // 1


};