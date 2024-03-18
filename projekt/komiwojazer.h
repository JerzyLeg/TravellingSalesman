#pragma once

#include <vector>
#include <string>
#include <map> 

using namespace std;

/**
 * \brief   Sprawdzenie arametrow wejsciowych.
 *
 * \details Funkcja sprawdza czy wszystkie parametry wejsciowe zostaly wywolane.
 *          
 *      
 *
 *
 * \param[in]		argc						arg count.
 * \param[in]		argv						arg vector.
 * \param[out]		indeksyPrzelacznikow		mapa indeksow, gdzie znajduja sie odpowiednie przelaczniki.
 *
 * \return			false gdy parametry wejsciowe zostana zle wpisane/ true
 *
 */
bool sprawdzParametryWejsciowe(int argc, char* argv[], map<string, int>& indeksyPrzelacznikow);

/**
 * \brief   Wczytanie parametrow wejsciowych.
 *
 * \details Funkcja sprawdza czy po przelacznikach wystepuje parametr oraz czy parametry sa mozliwe do wykonywania programu.
 *
 *
 *
 *
 * \param[in]		argc						arg count.
 * \param[in]		argv						arg vector.
 * \param[in]		indeksyPrzelacznikow		mapa indeksow, gdzie znajduja sie odpowiednie przelaczniki.
 * \param[out]		liczbaGeneracji				ilosc pokolen ktora ma zostac poddana ewoulucji.
 * \param[out]		liczbaOsobnikow				liczba osobnikow w danym pokoleniu.
 * \param[out]		plikWe						sciezka pliku wejsciowego
 * \param[out]		plikWy						sciezka pliku wyjsciowego
 *
 * \return			false gdy parametry wejsciowe zostana zle wpisane/ true
 *
 */

bool wczytajPrzelaczniki(int argc, char* argv[], int& liczbaGeneracji, int& liczbaOsobnikow, string& plikWe, string& plikWy, map<string, int> indeksyPrzelacznikow);

/**
 * \brief   Macierz wejsciowa.
 *
 * \details Funkcja wczytuje wejsciowy plik tekstowy i zapisuje go jako wektor wektorow.
 *
 *
 *
 *
 * \param[in]		sciezka					sciezka pliku wejsciowego

 *
 * \return			Macierz odleglosci.
 *
 */

vector<vector<int>> wczytajPlik (std::string sciezka);

/**
 * \brief   Generowanie populacji startowej.
 *
 * \details Funkcja losowo generuje pierwsze pokolenie - pierwszy zestaw tras. 
 *
 *
 *
 *
 * \param[in]		iloscMiast					liczba miast, przez ktore komiwojazer musi przejsc
 * \param[in]		rozmiarPopulacji			liczba tras, ktora funkcja ma wygenerowac
 * \param[in]		miastoStartowe				miasto, w ktorym komiwojazer ma trase rozpoczac oraz skonczyc

 *
 * \return			Populacja startowa.
 *
 */

vector<vector<int>> generujPopulacjeStartowa(int iloscMiast, int rozmiarPopulacji, int miastoStartowe);

/**
 * \brief   Obliczanie dlugosci trasy.
 *
 * \details Funkcja oblicza dlugosc pojedynczej trasy.
 *
 *
 *
 *
 * \param[in]		macierz_odleglosci			macierz wejsciowa z odleglciami
 * \param[in]		kolejnosc					indeksy kolejnych miast
 * 
 * 
 * \return			Dlugosc trasy.
 *
 */

int oblicz_trase(vector<vector<int>> macierz_odleglosci, vector<int>kolejnosc);

/**
 * \brief   Sortowanie tras.
 *
 * \details Funkcja sortuje trasy od najkrotszej do najdluzszej/niemozliwej.
 *
 *
 *
 *
 * \param[in]		populacja					zbior tras
 * \param[in]		macierzOdleglosci			wejsciowa macierz z odleglosciami

 *
 * \return			Posortowane trasy nalezace do jednego pokolenia.
 *
 */

vector<vector<int>> sortujPopulacje(vector<vector<int>> populacja, vector<vector<int>> macierzOdleglosci);

/**
 * \brief   Krzyzowanie dwoch tras.
 *
 * \details Funkcja krzyzuje dwie trasy i w rezultacie powstaja dwie nowe trasy.
 *
 *
 *
 *
 * \param[in]		rodzic1						trasa pierwsza do krzyzowania
 * \param[in]		rodzic2						trasa druga do krzyzowania
 *
 * \return			Dwie nowe trasy.
 *
 */

vector<vector<int>> krzyzowanie(vector <int> rodzic1, vector <int> rodzic2);

/**
 * \brief   Generowanie nowych tras potomnych.
 *
 * \details Funkcja wybiera lepsza polowe tras do krzyzowanie, za pom. f. krzyzowania nastepuje krzyzowanie. Najlepszy rezultat z pokolenia zawsze zostaje, gorsza polowa tras jest przepisana.
 *
 *
 *
 *
 * \param[in]		populacjaPosortowana		posortowany zestaw tras w danym pokoleniu
 *
 * \return			nowy zestaw tras - nowa populacja
 *
 */

vector<vector<int>> nowaGeneracja(vector<vector<int>> populacjaPosortowana);

/**
 * \brief   Wyswietlanie danej generacji.
 *
 * \details Funkcja wyswietla zestaw tras jednej generacji oraz ich d³ugosc
 *
 *
 *
 *
 * \param[in]		generacja					zestaw tras
 * \param[in]		macierzOdleglosci			macierz wejsciowa
 *
 */

void wyswietlGeneracje (vector<vector<int>> generacja,vector<vector<int>> macierzOdleglosci);

/**
 * \brief   Zapisanie wyniku do pliku wyjsciowego.
 *
 * \details Funkcja zapisuje do pliku wyjsciowego najkrotsza trase oraz jej dlugosc w kolejnych generacjach.
 *
 *
 *
 *
 * \param[in]		numerGeneracji				numer pokolenia
 * \param[in]		trasa						kolejne miasta w danej trasie
 * \param[in]		dlugoscTrasy				dlugosc trasy
 * \param[out]		plikWyjsciowy				plik z wynikami
 *
 */

void zapiszDoPliku(int numerGeneracji, vector<int> trasa, int dlugoscTrasy, ofstream& plikWyjsciowy);





