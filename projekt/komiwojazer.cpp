#include "komiwojazer.h"
#include <algorithm>
#include <set>
#include <limits.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>


bool sprawdzParametryWejsciowe(int argc, char* argv[], map<string, int>& indeksyPrzelacznikow)
{
	bool plikWejsciowy{ false }, plikWyjsciowy{ false }, liczbaGeneracji{ false }, liczbaOsobnikow{ false };
	if (argc != 9)
	{
		cout << "niewłaściwa ilość parametrów wejściowych";
		return false;
	}

	for (int i = 0; i < argc; ++i)
	{
		string currentArgv(argv[i]);
		if (currentArgv == "-i")
		{
			indeksyPrzelacznikow["-i"] = i;
			plikWejsciowy = true;
		}
		if (currentArgv == "-o")
		{
			indeksyPrzelacznikow["-o"] = i;
			plikWyjsciowy = true;
		}
		if (currentArgv == "-g")
		{
			indeksyPrzelacznikow["-g"] = i;
			liczbaGeneracji = true;
		}
		if (currentArgv == "-n")
		{
			indeksyPrzelacznikow["-n"] = i;
			liczbaOsobnikow = true;
		}
	}

	if (plikWejsciowy == false || plikWyjsciowy == false || liczbaGeneracji == false || liczbaOsobnikow == false)
	{
		cout << "złe parametry wejściowe";
		return false;
	}

	return true;
}

bool wczytajPrzelaczniki(int argc, char* argv[], int& liczbaGeneracji, int& liczbaOsobnikow, string& plikWe, string& plikWy, map<string, int> indeksyPrzelacznikow)
{
	int indeksLiczbaGeneracji = indeksyPrzelacznikow["-g"];
	int indeksLiczbaOsobnikow = indeksyPrzelacznikow["-n"];
	int indeksPlikWe = indeksyPrzelacznikow["-i"];
	int indeksPlikWy = indeksyPrzelacznikow["-o"];

	if (indeksLiczbaGeneracji + 1 >= argc || indeksLiczbaOsobnikow + 1 >= argc || indeksPlikWe + 1 >= argc || indeksPlikWy + 1 >= argc)
	{
		cout << "brak wartości po przełączniku";
		return false;
	}

	try
	{
		string liczbaGeneracjiStr = argv[indeksLiczbaGeneracji + 1];
		liczbaGeneracji = stoi(liczbaGeneracjiStr);
		if (liczbaGeneracji < 1)
			throw exception();
	}
	catch (exception ex)
	{
		cout << "błędna liczba generacji";
		return false;
	}

	try
	{
		string liczbaOsobnikowStr = argv[indeksLiczbaOsobnikow + 1];
		liczbaOsobnikow = stoi(liczbaOsobnikowStr);
		if (liczbaOsobnikow < 1)
			throw exception();
	}
	catch (exception ex)
	{
		cout << "błędna liczba osobników";
		return false;
	}

	string plikWejsciowyStr = argv[indeksPlikWe + 1];
	ifstream plikWejsciowy;
	plikWejsciowy.open(plikWejsciowyStr, ios::in);
	if (!plikWejsciowy.is_open()) {
		cout << " nie znaleziono pliku wejsciowego";
		return false;
	}
	plikWejsciowy.close();
	plikWe = plikWejsciowyStr;

	string plikWyjsciowyStr = argv[indeksPlikWy + 1];
	ofstream plikWyjsciowy;
	plikWyjsciowy.open(plikWyjsciowyStr, ios::out);
	if (!plikWyjsciowy.is_open())
	{
		cout << "nie można zapisać do pliku wyjściowego";
		return false;
	}
	plikWyjsciowy.close();
	plikWy = plikWyjsciowyStr;

	return true;
}

vector<vector<int>> wczytajPlik (std::string sciezka)
{	
  ifstream plik_wejsciowy;
	ofstream outfile;
	string line;
	vector<vector<int>> macierz_odleglosci;
	plik_wejsciowy.open(sciezka);

	if (plik_wejsciowy.is_open())
	{
		int licznik_lini{ 0 };

		while (getline(plik_wejsciowy, line))
		{
			licznik_lini++;
			if (licznik_lini == 1)
			{
				continue;
			}

			cout << line;

			istringstream ss(line);    // opakowanie na string
			string odleglosc;

			vector<int> wiersz;
			while (ss >> odleglosc) // wywołanie operatora >> przekazuje kolejne słowa oddzielone spacjami
			{
				wiersz.push_back(stoi(odleglosc)); // string to int
			}
			cout << endl;

			macierz_odleglosci.push_back(wiersz);


		}

		for (int i = 0; i < macierz_odleglosci.size(); i++)
		{
			vector <int> odleglosc{ macierz_odleglosci[i] };

			if (odleglosc.size() != macierz_odleglosci.size())
			{
				throw exception("zle parametry macierzy wejsciowej");
			}
		}
  
	}
	else
	{
		cout << "nie mozna otworzyc pliku" << endl;
	}
  return macierz_odleglosci;
}

vector<vector<int>> generujPopulacjeStartowa(int iloscMiast, int rozmiarPopulacji, int miastoStartowe)
{
	vector<vector<int>> populacja;
	set<int> wylosowane;	// wylosowane zmienne

	std::srand(std::time(0)); //use current time as seed for random generator
	//int random_variable = std::rand() % iloscMiast;
	//std::cout << "Random value " << random_variable << '\n';

	int random_variable{ -1 };
	for (int j = 0; j < rozmiarPopulacji; j++)
	{

		vector<int> chromosom(iloscMiast);
		chromosom[0] = miastoStartowe;
		wylosowane.insert(miastoStartowe);
		for (int i = 1; i < iloscMiast; i++)
		{
			bool wylosowalemUnikat{ false };
			while (/*krec petla tak dlugo �eby dostac warunek ok*/ wylosowalemUnikat == false) {
				random_variable = std::rand() % iloscMiast;
				if (wylosowane.find(random_variable) == wylosowane.end())
				{
					chromosom[i] = random_variable;
					wylosowane.insert(random_variable);

					wylosowalemUnikat = true;
				}
				else
				{
					wylosowalemUnikat = false;
				}
			}

		}
		chromosom.push_back(chromosom[0]);
		wylosowane.clear();
		populacja.push_back(chromosom);
	}


	return populacja;
}

int oblicz_trase(vector<vector<int>> macierz_odleglosci, vector<int>kolejnosc) {
	int suma{ 0 };

	for (int i = 0; i < kolejnosc.size() - 1; i++) {
		int indeksMiastaAktualnego = kolejnosc[i];
		int indeksMiastaDocelowego = kolejnosc[i + 1];

		if (macierz_odleglosci[indeksMiastaAktualnego][indeksMiastaDocelowego] < 0) 
		{
			return INT_MAX;
		}

		suma += macierz_odleglosci[indeksMiastaAktualnego][indeksMiastaDocelowego];
	}
	return suma;
}

vector<vector<int>> sortujPopulacje(vector<vector<int>> populacja, vector<vector<int>> macierzOdleglosci) 
{
	for (int h = 0; h < populacja.size(); h++)
	{
		for (int i = 0; i < populacja.size() - h - 1; i++)
		{
			vector<int> chromosomAkualny = populacja[i];
			int wynikAktualny = oblicz_trase(macierzOdleglosci, chromosomAkualny);
			auto chromosomNastepny = populacja[i + 1];
			int wynikNastępny = oblicz_trase(macierzOdleglosci, chromosomNastepny);
			if (wynikAktualny > wynikNastępny)
			{
				swap(populacja[i], populacja[i + 1]);
			}
		}
	}

  return populacja;
}

vector<vector<int>> krzyzowanie(vector <int> rodzic1, vector <int> rodzic2)
{
	int liczbaWylosowana = std::rand() % (rodzic1.size() / 2 + 1);
	vector<int> potomek1;
	vector<int> potomek2;
	vector<vector<int>> rezultat;
	set <int> czescRodzica;

	// cout << "liczbaWylosowana: " << liczbaWylosowana << endl;

	potomek1.push_back(rodzic1[0]);
	potomek2.push_back(rodzic1[0]);
	czescRodzica.insert(rodzic1[0]);

	for (int i = 1; i <= liczbaWylosowana; i++)
	{
		potomek1.push_back(rodzic1[i]);
		czescRodzica.insert(rodzic1[i]);
	}
	for (int j = 0; j < rodzic2.size(); j++)
	{
		if (czescRodzica.find(rodzic2[j]) == czescRodzica.end())
		{
			potomek1.push_back(rodzic2[j]);
		}
	}
  for (int k = 0; k < rodzic1.size(); k++)
  {
    if(czescRodzica.find(rodzic1[k]) == czescRodzica.end())
    {
      potomek2.push_back(rodzic1[k]);
    }

  }
  czescRodzica.erase(czescRodzica.find(rodzic1[0]));
  for(int l = 0; l < rodzic2.size(); l++)
  {
    if(czescRodzica.find(rodzic2[l]) != czescRodzica.end())
    {
      potomek2.push_back(rodzic2[l]);
    }

  }


	potomek1.push_back(rodzic1[0]);
	potomek2.push_back(rodzic1[0]);

	rezultat.push_back(potomek1);
	rezultat.push_back(potomek2);

	return rezultat;

}

vector<vector<int>> nowaGeneracja(vector<vector<int>> populacjaPosortowana)
{
  vector<vector<int>> wynik;
  int iterator {0};
  int polowaPopulacji = populacjaPosortowana.size()/2;
  if(polowaPopulacji % 2 != 0)
    iterator = polowaPopulacji + 1;
  else 
    iterator = polowaPopulacji;

  for(int i = 0; i < iterator/2; i++) 
  {
    vector<vector<int>> dzieci = krzyzowanie(populacjaPosortowana[i],populacjaPosortowana[iterator-i-1]);

    wynik.push_back(dzieci[0]);
    wynik.push_back(dzieci[1]);
  }

  for(int j = iterator; j < populacjaPosortowana.size()-1; j++)
  {
    wynik.push_back(populacjaPosortowana[j]);
  }

   wynik.push_back(populacjaPosortowana[0]);
  // wynik.push_back(populacjaPosortowana[1]);

  return wynik;
}

void wyswietlGeneracje (vector<vector<int>> generacja,vector<vector<int>> macierzOdleglosci)
{
  for(int i = 0; i < generacja.size(); i++)
  {
    cout << endl;
    for(int j = 0; j < generacja[i].size(); j++)
    {
      cout << generacja[i][j] << " ";
      
    }
		cout << "dlugosc trasy: " << oblicz_trase(macierzOdleglosci, generacja[i]);
  }


}

void zapiszDoPliku(int numerGeneracji, vector<int> trasa, int dlugoscTrasy, ofstream& plikWyjsciowy)
{
	plikWyjsciowy << "generacja: " << numerGeneracji << " ,";
	plikWyjsciowy << "trasa: ";
	for (int i = 0; i < trasa.size(); i++)
		plikWyjsciowy << trasa[i];
	plikWyjsciowy << " ,";
	plikWyjsciowy << "dlugosc trasy: " << dlugoscTrasy;
	plikWyjsciowy << endl;
}
