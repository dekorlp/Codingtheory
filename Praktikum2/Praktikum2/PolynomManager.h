#pragma once
#include <iostream>
#include "Polynom.h"

using namespace std;

class PolynomManager
{
public:
	void CreateTable(int gfPower);
	Polynom CalculateInverse(Polynom pol);
private:
	std::vector<Polynom> m_UnzerlegbarePolynomeGF2;
	std::vector<Polynom> m_Polynome;

	void CreateUnzerlegbarePolynome();
	bool CheckInputGF2(int gfPower);
	void CreatePolynome(int gfPower);
	Polynom SimplifyPolynom(Polynom pol, Polynom unzerlegbaresPolynom, int mod);
};