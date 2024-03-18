// komiwojazer.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>

#include "komiwojazer.h"

// komiwojazer.exe -i "C:\Sandbox_personal\genetic-TSP\input.txt" -o "C:\Sandbox_personal\genetic-TSP\output.txt" -g 100 -n 20

using namespace std;

// -i plik we z macierza
// -o plik wysciowy z najlepszymi wynikami w kolejnych generacjacj
// -g liczba generacji
// -n liczba osobnikow


/**
 * \brief   The function bar.
 *
 * \details Funkcja main 
 *
 *
 * \param[in]		argc		arg count.
 * \param[in]		argv		arg vector.
 *
 * \return			The error return code of the function.
 *
 */

int main(int argc, char* argv[])
{
	std::srand(std::time(0));
	map<string, int> indeksyPrzelacznikow;
	int liczbaGeneracji{ 0 };
	int liczbaOsobnikow{ 0 };
	int miastoStartowe{ 4 };
	string sciezkaPlikuWejsciowego, sciezkaPlikuWyjsciowego;



	if (sprawdzParametryWejsciowe(argc, argv, indeksyPrzelacznikow))
	{
		bool wczytanoPoprawnie = wczytajPrzelaczniki(argc, argv, liczbaGeneracji, liczbaOsobnikow, sciezkaPlikuWejsciowego, sciezkaPlikuWyjsciowego, indeksyPrzelacznikow);

		if (!wczytanoPoprawnie)
			return 0;
	}
	else
	{
		return 0;
	}

	ofstream plikWyjsciowy(sciezkaPlikuWyjsciowego);

	vector<vector<int>> macierzOdleglosci;
	try
	{
		macierzOdleglosci = wczytajPlik(sciezkaPlikuWejsciowego);
	}
	catch(exception ex)
	{
		cout << ex.what();
		return 0;
	}



	auto populacjaStartowa = generujPopulacjeStartowa(macierzOdleglosci[0].size(), liczbaOsobnikow, miastoStartowe);


	/*for (int i = 0; i < populacjaStartowa.size(); i++)
	{
		vector <int> chromosom{ populacjaStartowa[i] };
		for (int j = 0; j < chromosom.size(); j++)
		{
			cout << chromosom[j] << " ";
		}
		cout << "dlugosc trasy: " << oblicz_trase(macierzOdleglosci, chromosom);
		cout << endl;
	}*/


	auto posortowanaPopulacja = sortujPopulacje(populacjaStartowa, macierzOdleglosci);




	cout << endl;
	for (int i = 0; i < posortowanaPopulacja.size(); i++)
	{
		vector <int> chromosom{ posortowanaPopulacja[i] };
		for (int j = 0; j < chromosom.size(); j++)
		{
			cout << chromosom[j] << " ";
		}
		cout << "dlugosc trasy: " << oblicz_trase(macierzOdleglosci, chromosom);
		cout << endl;
	}


	for (int i = 0; i < liczbaGeneracji; i++)
	{
		auto swiezaGeneracja = nowaGeneracja(posortowanaPopulacja);
		//wyswietlGeneracje(swiezaGeneracja,macierzOdleglosci);


		posortowanaPopulacja = sortujPopulacje(swiezaGeneracja, macierzOdleglosci);
		//wyswietlGeneracje(posortowanaPopulacja,macierzOdleglosci);
		cout << endl;
		auto wynik = oblicz_trase(macierzOdleglosci, posortowanaPopulacja[0]);
		cout << "iter: " << i << " dlugosc trasy: " << wynik << endl;

		zapiszDoPliku(i, posortowanaPopulacja[0], wynik, plikWyjsciowy);


		wyswietlGeneracje(posortowanaPopulacja, macierzOdleglosci);
		cout << "enmd";

	}
}