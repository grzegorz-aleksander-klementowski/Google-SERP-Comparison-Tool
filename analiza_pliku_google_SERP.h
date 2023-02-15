#ifndef ANALIZA_PLIKU_GOOGLE_SERP_H_INCLUDED
#define ANALIZA_PLIKU_GOOGLE_SERP_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>


using namespace std;

string introText();           //wypisuje tekst początkowy o programie
string frazaGoogle();       // wymożliwia użytkownikowi wpisanie frazy Google i ją analizuje
string linkDoGoogleSERP(string wpisanaFraza);  //tworzy link do Google SERP
void pobierzStroneWWW(string link, string celDolcelowyPobrania, string nazwijPobranaStroneWWW);   //Pobiera plik Google z wynikami wyszukiwania
string analizaPlikuHTML(string sciezkaPliku);    //Analiza pliku HTML
bool czyZawieraWynikiGoogleMaps(string znacznikSERPgoogleMaps, string l, size_t pozycja); //sprawdza czy znajdują się wyniki z Google Maps
void wykrytoBlad(string blad="Nieoczekiwany błąd", string opis="Wykryto nieoczekiwany błąd, który nie został opisany. Zamykam program...");                 // wypisuje informacje o błędzie
string wypiszNaglowekWynikuSERP(size_t pozycja, string linia, int numerSERP, string znacznikGoogleSERP, string znacznikGoogleMapsSERP); //Wypisuje wynik SERP
int funkcjaNumerSERP(bool czyToMapa, int numerSERP, int numerSERPgmaps); //zwraca numer wyniku
int jakiTypWynikuSERP(string l, size_t pozycja);            // zwraca typ wyniku (0-zwykły, 1=Google mapy,2=informacje)
string wypiszLink(size_t pozycja, string linia);            // wypisuje link z wyniku
string wypiszWarstwyStrony(size_t pozycja2, string linia);  // wypisuje opis wyniku z Googel
string wypiszWarstwyStronyPoprawione(string link);          // wypisuje warstwy strony

#endif // ANALIZA_PLIKU_GOOGLE_SERP_H_INCLUDED
