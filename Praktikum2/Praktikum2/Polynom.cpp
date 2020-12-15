#include "Polynom.h"


PolynomPart::PolynomPart()
{
	int test = 0;
}

PolynomPart::PolynomPart(int base, int xPower)
{
	this->m_base = base;
	this->m_xPower = xPower;
}

void PolynomPart::SetPart(int base, int xPower)
{
	this->m_base = base;
	this->m_xPower = xPower;
}

void PolynomPart::SetBase(int base)
{
	this->m_base = base;
}

void PolynomPart::SetPower(int xPower)
{
	this->m_xPower = xPower;
}

int PolynomPart::GetBase()
{
	return m_base;
}

int PolynomPart::GetXPower()
{
	return m_xPower;
}

Polynom::Polynom()
{

}

Polynom::Polynom(std::vector<PolynomPart> polynom)
{
	this->m_Polynom = polynom;
}

void Polynom::CreatePolynom(std::vector<PolynomPart> polynom)
{
	this->m_Polynom = polynom;
}

int Polynom::GetSize()
{
	return m_Polynom.size();
}

void Polynom::AddPolynomPart(PolynomPart part)
{
	m_Polynom.push_back(part);
}

void Polynom::SetPolynomPart(unsigned int index, PolynomPart part)
{
	m_Polynom[index] = part;
}

PolynomPart Polynom::operator[](int index)
{
	return m_Polynom[index];
}

bool PolynomPart::operator==(PolynomPart rhs)
{
	return this->GetBase() == rhs.GetBase() && this->GetXPower() == rhs.GetXPower();
}

PolynomPart PolynomPart::operator*(PolynomPart &rhs)
{
	return PolynomPart(this->GetBase() * rhs.GetBase(), this->GetXPower() + rhs.GetXPower());
}

Polynom Polynom::EraseDuplicatedAndSort()
{
	// Alle Elemente durchgehen (letztes ausgenommen)
	for (unsigned int i = 0; i < m_Polynom.size() - 1; i++)
	{
		// Position des zurzeit kleinstes Elementes
		unsigned int min_pos = i;

		// unsortierten Teil des Feldes durchlaufen
		// und nach kleinstem Element suchen
		for (unsigned int j = i + 1; j < m_Polynom.size(); j++)
			if (m_Polynom[j].GetXPower() < m_Polynom[min_pos].GetXPower())
				min_pos = j;

		// Elemente vertauschen
		// Das kleinste Element kommt an das Ende
		// bereits sortierten Teils des Feldes
		PolynomPart temp = m_Polynom[i];
		m_Polynom[i] = m_Polynom[min_pos];
		m_Polynom[min_pos] = temp;
	}

	Polynom temp;

	// doppelte aufsummieren

	m_Polynom.push_back(PolynomPart(0, 0));
	for (unsigned int i = 0; i < m_Polynom.size() - 1; i++)
	{
		if (m_Polynom[i].GetXPower() == m_Polynom[i + 1].GetXPower())
		{
			temp.AddPolynomPart(PolynomPart(m_Polynom[i].GetBase() + m_Polynom[i + 1].GetBase(), m_Polynom[i + 1].GetXPower()));
			i = i + 1;
		}
		else
		{
			temp.AddPolynomPart(m_Polynom[i]);
		}
	}


	//m_Polynom = temp;

	return temp;
}

Polynom Polynom::Sort()
{
	// Alle Elemente durchgehen (letztes ausgenommen)
	for (unsigned int i = 0; i < m_Polynom.size() - 1; i++)
	{
		// Position des zurzeit kleinstes Elementes
		unsigned int min_pos = i;

		// unsortierten Teil des Feldes durchlaufen
		// und nach kleinstem Element suchen
		for (unsigned int j = i + 1; j < m_Polynom.size(); j++)
			if (m_Polynom[j].GetXPower() < m_Polynom[min_pos].GetXPower())
				min_pos = j;

		// Elemente vertauschen
		// Das kleinste Element kommt an das Ende
		// bereits sortierten Teils des Feldes
		PolynomPart temp = m_Polynom[i];
		m_Polynom[i] = m_Polynom[min_pos];
		m_Polynom[min_pos] = temp;
	}

	return m_Polynom;
}

Polynom Polynom::operator*(Polynom &rhs)
{
	Polynom resultWithDoubleElements; 
	Polynom cleanedResult;

	Polynom lhs = *this;
	for (unsigned int i = 0; i < lhs.m_Polynom.size(); i++)
	{
		for (unsigned int j = 0; j < rhs.m_Polynom.size(); j++)
		{
			PolynomPart partlhs = lhs.m_Polynom[i];
			PolynomPart partrhs = rhs.m_Polynom[j];
			if ((partlhs.GetBase() != 0 && partlhs.GetBase()) != 0 && (partrhs.GetBase() != 0 && partrhs.GetBase()))
			{
				resultWithDoubleElements.AddPolynomPart(PolynomPart(partlhs.GetBase() * partrhs.GetBase(), partlhs.GetXPower() + partrhs.GetXPower()));
			}
			else
			{
				resultWithDoubleElements.AddPolynomPart({ 0, 0 });
			}
		}
	}

	cleanedResult = resultWithDoubleElements.EraseDuplicatedAndSort();


	Polynom result;
	// drehe Ergebnis um
	for (int i = cleanedResult.GetSize()-1; i >= 0; i--)
	{
		result.AddPolynomPart(cleanedResult[i]);
	}

	return result;
}

void Polynom::Erase(unsigned int index)
{
	m_Polynom.erase(m_Polynom.begin() + index);
}

Polynom Polynom::operator+(Polynom &rhs)
{
	EraseDuplicatedAndSort(); // erase duplicates from m_polynom
	Polynom right = m_Polynom;
	Polynom result = rhs.EraseDuplicatedAndSort();

	// add all equal terms
	for (unsigned int i = 0; i < result.GetSize(); i++)
	{
		int foundIndex = -1;

		for (unsigned int j = 0; j < right.GetSize(); j++)
		{
			if (result[i].GetXPower() == right[j].GetXPower())
			{
				result.SetPolynomPart(i, PolynomPart(result[i].GetBase() + right[j].GetBase(), right[j].GetXPower()));
				foundIndex = -1;
			}
		}
	}
	
	// add all terms which are not equal
	for (unsigned int i = 0; i < m_Polynom.size(); i++)
	{
		bool exists = false;

		for (unsigned int j = 0; j < result.GetSize(); j++)
		{
			if (m_Polynom[i].GetXPower() == result[j].GetXPower())
			{
				exists = true;
			}
		}

		if (!exists)
		{
			result.AddPolynomPart(m_Polynom[i]);
		}
	}
	
	// erase duplicates and sort terms
	result = result.Sort();

	return result;
}

bool Polynom::operator==(Polynom &rhs)
{
	bool same = false;

	Polynom lhs = *this;

	if (this->GetSize() != rhs.GetSize())
	{
		same = false;
	}
	else
	{
		for (unsigned int i = 0; i < this->GetSize(); i++)
		{
			for (unsigned int j = 0; j < rhs.GetSize(); j++)
			{
				PolynomPart partlhs = lhs.m_Polynom[i];
				PolynomPart partrhs = rhs.m_Polynom[j];

				if (partlhs.GetBase() == partrhs.GetBase() && partlhs.GetXPower() == partrhs.GetXPower())
				{
					same = true;
					break;
				}
				else
				{
					same = false;
				}
			}

			if (same == false)
			{
				break;
			}
		}
	}

	return same;
}