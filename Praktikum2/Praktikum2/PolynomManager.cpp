#include "PolynomManager.h"

void PolynomManager::CreateTable(int gfPower)
{
	if (gfPower <= 2 && gfPower >= 15)
	{
		std::cout << "gfPower has to be between 1 and 15" << std::endl;
		return;
	}

	if (!CheckInputGF2(gfPower))
	{
		std::cout << "Base is not equal 2!" << std::endl;
		return;
	}

	// Ausgabe GF(X) = x^y
	std::cout << "GF(" << gfPower << ") = 2^" << log(gfPower) / log(2) << std::endl;
	std::cout << std::endl;


	CreateUnzerlegbarePolynome();
	CreatePolynome(gfPower - 1);

	Polynom pol1({ PolynomPart(0,0) });
	Polynom pol2({ PolynomPart(1,1), PolynomPart(1,0) });

	Polynom TEstPolynom = pol2 * pol1;

	// Erstellen der unkorrigierten Tabelle
	std::vector<Polynom> uncorrectedTable;
	for (int i = 0; i < gfPower; i++)
	{
		for (int j = 0; j < gfPower; j++)
		{
			Polynom Ergebnis = m_Polynome[i] * m_Polynome[j];
			uncorrectedTable.push_back(Ergebnis);
		}
	}

	/*std::cout << "Unkorrigierte Tabelle: " << std::endl;
	std::cout << "-------------------------------------------------";

	//Print unkorrigierte Tabelle
	for (int i = 0; i < uncorrectedTable.size(); i++)
	{
		if ((i) % gfPower == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "   |   ";
		}

		for (int j = 0; j< uncorrectedTable.at(i).GetSize(); j++)
		{
			std::cout << left << uncorrectedTable.at(i)[j].GetBase() << "X^" << uncorrectedTable.at(i)[j].GetXPower();


			if (j != uncorrectedTable.at(i).GetSize()-1)
				std::cout << " + ";
			else
				std::cout << "";
		}
	}*/



	// Korrigiertes Polynom
	//SimplifyPolynom(Polynom({ PolynomPart(1, 4), PolynomPart(1, 3), PolynomPart(1, 2), PolynomPart(1, 1) }), Polynom({PolynomPart(1,3), PolynomPart(2,1), PolynomPart(1,0) }), 3);   //m_UnzerlegbarePolynomeGF2[(log(gfPower) / log(2))-1]);
	//SimplifyPolynom(Polynom({ PolynomPart(1, 3), PolynomPart(2, 1) }), Polynom({ PolynomPart(1,3), PolynomPart(2,1), PolynomPart(1,0) }), 3);

	// Erstellen der korrigierten Tabelle
	std::vector<Polynom> correctedTable;
	for (int i = 0; i < uncorrectedTable.size(); i++)
	{
		Polynom Ergebnis = SimplifyPolynom(uncorrectedTable[i], m_UnzerlegbarePolynomeGF2[(log(gfPower) / log(2)) - 1], 2);
		correctedTable.push_back(Ergebnis);
	}


	/*std::cout << endl << endl << endl;
	std::cout << "Korrigierte Tabelle: " << std::endl;
	std::cout << "-------------------------------------------------";

	//Print korrigierte Tabelle
	for (int i = 0; i < correctedTable.size(); i++)
	{
		if ((i) % gfPower == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "   |   ";
		}

		for (int j = 0; j < correctedTable.at(i).GetSize(); j++)
		{
			std::cout << left << correctedTable.at(i)[j].GetBase() << "X^" << correctedTable.at(i)[j].GetXPower();


			if (j != correctedTable.at(i).GetSize() - 1)
				std::cout << " + ";
			else
				std::cout << "";
		}
	}*/

	//std::cout << endl << endl << endl;
	std::cout << "decimal Tabelle: " << std::endl;
	std::cout << "-------------------------------------------------";

	std::vector<int> dezTable;
	for (int i = 0; i < correctedTable.size(); i++)
	{
		for (int j = 0; j < m_Polynome.size(); j++)
		{
			if (correctedTable[i] == m_Polynome[j])
			{
				dezTable.push_back(j);
			}
		}
	}

	for (int i = 0; i < dezTable.size(); i++)
	{
		if ((i) % gfPower == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "   |   ";
		}

		std::cout << left << dezTable[i];

	}

}

void PolynomManager::CalculateInverse(Polynom pol)
{
	CreateUnzerlegbarePolynome();

	// get polynom from vector
	Polynom unzerlegbaresPolynom = m_UnzerlegbarePolynomeGF2[pol.CalculateHighestFactor()];

	// iterative algorithm

	Polynom p = pol;
	Polynom q = unzerlegbaresPolynom;
	

	Polynom endEquation({ PolynomPart(1, 0) });
	Polynom endEquation2({ PolynomPart(-1, 0) });

	while (!(p == endEquation) && !(p == endEquation2) )
	{

		int highestFactorDifference = p.CalculateHighestFactor() - q.CalculateHighestFactor();
		if(highestFactorDifference < 0) highestFactorDifference = highestFactorDifference * -1;

		

		// calculate new p
		Polynom calc({ PolynomPart(-1, highestFactorDifference) });
		Polynom temp;
		temp = (p * calc) + q;


		q = p;
		p = temp;

		p = p.Mod(2);
		p = p.EraseZeroBases();
		
		
		int test = 0;
	}

	int test = 0;

}

bool PolynomManager::CheckInputGF2(int gfPower)
{
	int base = static_cast<int>(log(gfPower) / log(2));
	int gf = static_cast<int>(pow(2, base));

	if (gf != gfPower)
	{
		return false;
	}

	return true;
}

void PolynomManager::CreateUnzerlegbarePolynome()
{

	// GF(2)
	Polynom pol;
	pol.CreatePolynom({PolynomPart(0,1) }); // not used!
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,2), PolynomPart(1,1),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,3), PolynomPart(1,2),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,4), PolynomPart(1,3),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,5), PolynomPart(1,2),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,6), PolynomPart(1,5),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,7), PolynomPart(1,6),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);

	pol.CreatePolynom({ PolynomPart(1,8), PolynomPart(1,4),  PolynomPart(1,3),  PolynomPart(1,2),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,9), PolynomPart(1,4),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,10), PolynomPart(1,3),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1, 11), PolynomPart(1,2),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,12), PolynomPart(1,6),  PolynomPart(1,4),  PolynomPart(1,1),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,13), PolynomPart(1,4),  PolynomPart(1,3),  PolynomPart(1,1),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
	pol.CreatePolynom({ PolynomPart(1,14), PolynomPart(1,5),  PolynomPart(1,3),  PolynomPart(1,1),  PolynomPart(1,0) });
	m_UnzerlegbarePolynomeGF2.push_back(pol);
}

void PolynomManager::CreatePolynome(int gfPower)
{
	if(gfPower >= 0) m_Polynome.push_back({ Polynom({PolynomPart(0,0)}) });
	if (gfPower >= 1) m_Polynome.push_back({ Polynom({PolynomPart(1,0)}) });
	if (gfPower >= 2) m_Polynome.push_back({ Polynom({PolynomPart(1,1)}) });
	if (gfPower >= 3) m_Polynome.push_back({ Polynom({PolynomPart(1,1), PolynomPart(1,0)}) });
	if (gfPower >= 4) m_Polynome.push_back({ Polynom({PolynomPart(1,2)}) });
	if (gfPower >= 5) m_Polynome.push_back({ Polynom({PolynomPart(1,2), PolynomPart(1,0)}) });
	if (gfPower >= 6) m_Polynome.push_back({ Polynom({PolynomPart(1,2), PolynomPart(1,1)}) });
	if (gfPower >= 7) m_Polynome.push_back({ Polynom({PolynomPart(1,2), PolynomPart(1,1), PolynomPart(1,0) }) });
	// TODO 8-15 Einfügen
}

Polynom PolynomManager::SimplifyPolynom(Polynom pol, Polynom unzerlegbaresPolynom, int modparam)
{
	while (pol[0].GetXPower() >= unzerlegbaresPolynom[0].GetXPower())
	{

		PolynomPart helper((-1 * pol[0].GetBase() + modparam), pol[0].GetXPower() - unzerlegbaresPolynom[0].GetXPower()); // 2 da Basis 2!

		Polynom firstStep = Polynom({ helper }) * unzerlegbaresPolynom;

		for (int i = 0; i < firstStep.GetSize(); i++)
		{
			pol.AddPolynomPart(firstStep[i]);
		}


		// Addiere doppelte Polynome
		Polynom secondStep = pol.EraseDuplicatedAndSort();

		Polynom thirdStep;

		// Modulo teilen und nutzen der PolynomTeile die nicht 0 sind
		for (int i = 0; i < secondStep.GetSize(); i++)
		{
			int mod = secondStep[i].GetBase() % modparam;

			if (mod != 0)
			{
				thirdStep.AddPolynomPart(PolynomPart(mod, secondStep[i].GetXPower()));
			}
		}

		// swap pol
		Polynom swap;
		for (int i = thirdStep.GetSize() - 1; i >= 0; i--)
		{
			swap.AddPolynomPart(thirdStep[i]);
		}

		pol = swap;
	}

	Polynom endStep;

	// Remove last Modulo Parts!
	// Modulo teilen und nutzen der PolynomTeile die nicht 0 sind
	for (int i = 0; i < pol.GetSize(); i++)
	{
		int mod = pol[i].GetBase() % modparam;

		if (mod != 0)
		{
			endStep.AddPolynomPart(PolynomPart(mod, pol[i].GetXPower()));
		}
		if (pol[i].GetBase() == 0 && pol[i].GetXPower() == 0)
		{
			endStep.AddPolynomPart(PolynomPart(0, 0));
		}
	}

	pol = endStep.EraseDuplicatedAndSort();

	return pol;
}