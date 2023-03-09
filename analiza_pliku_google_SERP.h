#ifndef ANALIZA_PLIKU_GOOGLE_SERP_H_INCLUDED
#define ANALIZA_PLIKU_GOOGLE_SERP_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>


using namespace std;

void pobier_strone_www(string link, string celDolcelowyPobrania, string nazwijPobranaStroneWWW);   //Pobiera plik Google z wynikami wyszukiwania
void wykryto_błąd(string blad="Nieoczekiwany błąd", string opis="Wykryto nieoczekiwany błąd, który nie został opisany. Zamykam program...");                 // wypisuje informacje o błędzie
bool czy_zawiera_wyniki_google_maps(string znacznikSERPgoogleMaps, string l, size_t pozycja); //sprawdza czy znajdują się wyniki z Google Maps
int funkcja_numer_serp(bool czyToMapa, int numerSERP, int numerSERPgmaps); //zwraca numer wyniku
int jaki_typ_wyniku_serp(string l, size_t pozycja);            // zwraca typ wyniku (0-zwykły, 1=Google mapy,2=informacje)
string intro_text();           //wypisuje tekst początkowy o programie
string fraza_google();       // wymożliwia użytkownikowi wpisanie frazy Google i ją analizuje
string link_do_google_serp(string wpisanaFraza);  //tworzy link do Google SERP
string analiza_pliku_html(string sciezkaPliku);    //Analiza pliku HTML
string wypisz_nagłówek_wyniku_serp(size_t pozycja, string linia, int numerSERP, string znacznikGoogleSERP, string znacznikGoogleMapsSERP); //Wypisuje wynik SERP
string wypisz_link(size_t pozycja, string linia);            // wypisuje link z wyniku
string wypisz_warstwy_strony(size_t pozycja2, string linia);  // wypisuje opis wyniku z Googel
string wypisz_warstwy_srony_poprawione(string link);          // wypisuje warstwy strony

#endif // ANALIZA_PLIKU_GOOGLE_SERP_H_INCLUDED
