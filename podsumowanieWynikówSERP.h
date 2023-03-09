#ifndef PODSUMOWANIEWYNIKóWSERP_H_INCLUDED
#define PODSUMOWANIEWYNIKóWSERP_H_INCLUDED
#include <string>
#include "utils.hpp"

using namespace std;

void przyg_do_porow_stron_serp(string plikSERP);
void pobieranie_stron_html_z_serp();
void procedura_wpisania_znaku_tak_lub_nie();
void procedura_wypisywania_podsumowania_serp(string frazaGlownaSERP);
void procedura_wypisywania_strumieniowego(string text);
void procedura_zamiany_pliku_prezentujacy_dane_na_txt();
void proces_wykonywania_nowej_analizy_serp(bool czyWykonacNowaAnalizeSERP);
char wypisuje_znak_tak_lub_nie();
int ilosc_frazy_w_pliku(string fraza, string sciezkaDoPliku); //(PRZY OTWARTYM PLIKU!)wyciąga do pliku txt najważniejsze elementy SEO z pliku HTML
int ile_plikow_html();
int ile_slow_kluczy(string slowaKlucze);
int ilosc_frazy_w_fragmencie(string fragmentTekstuDoPrzeszukania, string jakiTekstLiczyc);
int ilosc_slow_wiekszych_niz_dwie_literki(string tekstDoPrzeszukania); //liczy ilosc słów z tekstu, które posiadają więcej niż dwie literki.
bool czy_tak_lub_nie(char odpowiedz='n');
bool czy_plik_jest_pusty(const string& nazwaPliku);
string znajdz_wypisz_fraze_meta(string fraza, string sciezkaDoPliku);
string podsumowanie_wyników_serp(string frazaGlowna, int nr_PlikuDoAnalizy);
string wypisz_słowo_klucz(string lancuchSlowKluczy, int nrSlowaKlucz);
string wypisz_cialo_strony(string sciezkaDoPliku);
string wypisz_zawartosc_naglowka(int nrNaglowka, string cialoStronyDoPrzeszukania, int nrZnalezionegoNaglowka, int iloscNaglowkow);
string wypisz_link_z_pliku_przeanalizowanych_wyników_serp(int numerPliku);
string wypisz_czesci_linku(int nrWynikuSERP, int nr_warstwyLinku);
string wypisz_obliczenia_podsumowania
(
int typ = 1,//1=FRAZĘ WYSZUKIWANIA JEST ZAWARTA W: 2=ILOŚĆ SŁÓW KLUCZOWYCH(nr_slow_klucz.) MOŻNA ZNALEŹĆ: 3.ILE RAZY CZESCI LINKU ZNAJDUJĄ SIĘ W:
int nr_pliku = 1,
int ilosc_tylkoBody = 0,
int ilosc_opis = 0,
int ilosc_slowaKluczowe = 0,
int ilosc_link = 0,
int ilosc_h1 = 0,
int ilosc_h2 = 0,
int ilosc_h3 = 0,
int ilosc_h4 = 0,
int ilosc_h5 = 0,
int ilosc_h6 = 0
);
string to_lower_string(string stringToTransform);
string wypisz_zawartość_argumentu_z_znacznika(string znacznikCalosc, string argument);
string wyjmij_slowo_o_numerze(string tekstDoPrzeszukania, int ktoreSlowo); //wyjmuje słowo o numerze bez podliczania wyrazów jedno i dwu literowych







#endif // PODSUMOWANIEWYNIKóWSERP_H_INCLUDED
