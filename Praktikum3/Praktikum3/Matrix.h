#pragma once

#include <vector>
#include <iostream>

class Matrix
{
private:
	std::vector<std::vector<double>> m_Values;

public:
	Matrix();
	void CreateGeneratorMatrix(std::vector < std::vector<double>> values); // definition
	void CreateCanonicalMatrix(); // 1


};