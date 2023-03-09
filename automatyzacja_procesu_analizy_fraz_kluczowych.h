#ifndef AUTOMATYZACJA_PROCESU_ANALIZY_FRAZ_KLUCZOWYCH_H_INCLUDED
#define AUTOMATYZACJA_PROCESU_ANALIZY_FRAZ_KLUCZOWYCH_H_INCLUDED

void procedura_zapytania_uzyt_o_automatyzacje();
void procedura_automatycznego_pobierania_fraz_kluczowych();
void opoznij(int minSekundy, int maxSekundy);
void procedura_zakończenia_automatycznego_analizowania_fraz_kluczowych();
void procedura_aktualizowania_folderu_autom_analiz();
void procedura_tworzenia_folderu_doc_dla_analizy_danej_frazy(string nazwaFrazyKluczowej);
void procedura_archwizowania_zawartosci(std::string nazwaFrazyKluczowej);
void procedura_usuwania_zawartosci_katalogu(const string& sciezkaDoKatalogu);
void procedura_usuwania_przeanalizowanych_plikow();
void zapisz_nowy_plik_csv(const std::string& nazwa_pliku, const std::vector<std::vector<std::string>>& dane);
void dopisz_do_pliku_csv(const std::string& nazwa_pliku, const std::vector<std::vector<std::string>>& dane);
void procedura_aktualizowania_folderow();
std::string wypisz_zapytanie_o_automatyzacje();
std::string wypisz_potwierdzenie_czy_automatyzowac(bool czyWykAutomatycznie);
std::string wypisz_sciezke_do_pliku_txt_z_frazami_kluczowymi();
std::vector<std::string> wektor_pobieranych_fraz_kluczowych_z_pliku(const std::string sciezkaDoPliku);
vector<vector<string>> wektor_zapisywania_wynikow_analizy_do_pliku_csv(std::string frazaKluczowa, int nrAnalizowanejFrazy);
std::vector<std::vector<std::string>> wektor_wiersza_naglowkowego_tabeli_csv_analizy_autom();

#endif // AUTOMATYZACJA_PROCESU_ANALIZY_FRAZ_KLUCZOWYCH_H_INCLUDED
