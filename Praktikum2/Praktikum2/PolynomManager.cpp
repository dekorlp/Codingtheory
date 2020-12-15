#include "PolynomManager.h"

void PolynomManager::CreateTable(int gfPower)
{
	if (gfPower <= 2 && gfPower >= 15)
	{
		std::cout << "gfPower ist kleiner als 1 oder größer als 15" << std::endl;
		return;
	}

	if (!CheckInputGF2(gfPower))
	{
		std::cout << "Basis nicht nicht 2!" << std::endl;
		return;
	}

	// Ausgabe GF(X) = x^y
	std::cout << "GF(" << gfPower << ") = 2^" << log(gfPower)/log(2) << std::endl;
	std::cout << std::endl;


	CreateUnzerlegbarePolynome();
	//CreatePolynome(gfPower-1);

	Polynom pol1({ PolynomPart(0,0), PolynomPart(2,1) ,PolynomPart(1,2), PolynomPart(1,5) });
	Polynom pol2({ PolynomPart(1,1), PolynomPart(1,0), PolynomPart(1,4) });

	Polynom TEstPolynom =  pol2 + pol1;

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

		for (unsigned int i = 0; i < firstStep.GetSize(); i++)
		{
			pol.AddPolynomPart(firstStep[i]);
		}


		// Addiere doppelte Polynome
		Polynom secondStep = pol.EraseDuplicatedAndSort();

		Polynom thirdStep;

		// Modulo teilen und nutzen der PolynomTeile die nicht 0 sind
		for (unsigned int i = 0; i < secondStep.GetSize(); i++)
		{
			int mod = secondStep[i].GetBase() % modparam;

			if (mod != 0)
			{
				thirdStep.AddPolynomPart(PolynomPart(mod, secondStep[i].GetXPower()));
			}
		}

		// swap pol
		Polynom swap;
		for (unsigned int i = thirdStep.GetSize() - 1; i >= 0; i--)
		{
			swap.AddPolynomPart(thirdStep[i]);
		}

		pol = swap;
	}	

	Polynom endStep;

	// Remove last Modulo Parts!
	// Modulo teilen und nutzen der PolynomTeile die nicht 0 sind
	for (unsigned int i = 0; i < pol.GetSize(); i++)
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