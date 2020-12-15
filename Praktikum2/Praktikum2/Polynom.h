#pragma once

#include <vector>
#include <algorithm>

class PolynomPart
{
private:
	int m_base;
	int m_xPower;

public:
	PolynomPart();
	PolynomPart(int base, int xPower);
	void SetPart(int base, int xPower);
	void SetBase(int base);
	void SetPower(int xPower);
	int GetBase();
	int GetXPower();

	PolynomPart operator*(PolynomPart &rhs);
	bool operator==(PolynomPart rhs);
};

class Polynom
{
public:
	Polynom();
	Polynom(std::vector<PolynomPart> polynom);
	void AddPolynomPart(PolynomPart part);
	void SetPolynomPart(unsigned int index, PolynomPart part);
	void CreatePolynom(std::vector<PolynomPart> polynom);
	Polynom operator*(Polynom &rhs);
	Polynom operator+(Polynom &rhs);
	PolynomPart operator[](int index);
	bool operator==(Polynom &rhs);
	int GetSize();
	Polynom EraseDuplicatedAndSort();
	Polynom Sort();
	void Erase(unsigned int index);


private:
	std::vector<PolynomPart> m_Polynom;
};