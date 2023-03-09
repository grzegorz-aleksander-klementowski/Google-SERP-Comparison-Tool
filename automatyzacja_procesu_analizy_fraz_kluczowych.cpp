#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <filesystem>

#include <ctime>
#include <iomanip>
#include <sstream>

#include "podsumowanieWynikówSERP.h"
#include "globals.h"

using namespace std;
namespace fs = std::filesystem;

string wypisz_zapytanie_o_automatyzacje()
{
    return "Program posiadania możliwość wpisywania ręcznie frazy kluczowej do wyszukiwania Google, lub pobrać frazy kluczowe z listy, aby wszystkie pokolei przeanalizować i zapisać wyniki w pliku txt. \nCzy chcesz  pobrać frazy z pliku txt i automatycznie je przeanalizować (t), czy ręcznie wpisać frazę kluczową (n)?\n";
}

string wypisz_potwierdzenie_czy_automatyzowac(bool czyWykAutomatycznie)
{
    if(czyWykAutomatycznie==true)return"Wybrano automatyczne analizowanie fraz kluczowych.";
    else return"Wybrano ręczne analizowanie fraz kluczowych.";
}

void procedura_zapytania_uzyt_o_automatyzacje()
{
    cout<<wypisz_zapytanie_o_automatyzacje()<<endl;
    czyWykonacAutomatyzacje = czy_tak_lub_nie(wypisuje_znak_tak_lub_nie());
    cout<<wypisz_potwierdzenie_czy_automatyzowac(czyWykonacAutomatyzacje)<<endl;
}



//-------procedura_automatycznego_pobierania_fraz_kluczowych-------------



string wypisz_informacje_i_zapytanie_czy_uzytkownik_chce_sam_wybrac_plik_zrodlowy()
{
    return"Frazy kluczowe zostaną pobrane z pliku tekstowego w formacie txt. Możesz użyć domyślnego pliku lub podać ścieżkę do swojego wybranego pliku. \nCzy chcesz użyć pliku domyślnego (t), czy podać ścieżkę do pliku (n)? ";
}

string wypisz_informacje_jak_modyfikowac_plik_domyslny_z_fraz_klucz()
{
    return"Wybrałeś domyslny plik, w którym znajdują się frazy kluczowe. \nDomyślny plik znajduje się w folderze z projektem, ścieżka do pliku: ./default.txt. \nNatomiast, jesli jeszcze nie dodałeś fraz kluczowych, możesz je dodać teraz. Możesz edytować plik. Program odczytuje frazy kluczowe z każdej lini, więc w każdej oddzielnej linii, wpisz oddzielną frazę kluczową. ";
}

string wypisz_sciezke_uzytkownika()
{
    string sciezkaDoPliku;
    fstream plik;

    cout<<"Wybrałeś, aby użyć swojego pliku. Aby poprawnie plik zadziałał, w pliku tekstowym, który chcesz wybrać, do każdej linii wpisz frazy kluczowe, tak, abym w każdej linii, znajdowała się oddzielna fraza kluczowa."<<endl;
    cout<<"Wpisz ścieżkę do pliku, w którym znajdują się frazy kluczowe: ";
    cin>>sciezkaDoPliku;

    plik.open(sciezkaDoPliku, ios::in);
    while(plik.fail())
    {
        cout<<"E: Nie takiego pliku lub plik jest uszkodzony. Wybierz inny plik: ";
        cin>>sciezkaDoPliku;
        //sciezkaDoPliku="./default.txt";
    }

    cout<<"I: Plik istnieje."<<endl;
    plik.close();
    return sciezkaDoPliku;;
}

string wypisz_sciezke_do_pliku_txt_z_frazami_kluczowymi()
{
    bool czyUzycPlikuDomyslnegotxt;
    string sciezkaDoPlikuZFrazamiKluczowymi;

    cout<<wypisz_informacje_i_zapytanie_czy_uzytkownik_chce_sam_wybrac_plik_zrodlowy()<<endl;
    czyUzycPlikuDomyslnegotxt=czy_tak_lub_nie(wypisuje_znak_tak_lub_nie());
    if(czyUzycPlikuDomyslnegotxt==true)
    {
        sciezkaDoPlikuZFrazamiKluczowymi="./default.txt";
        cout<<wypisz_informacje_jak_modyfikowac_plik_domyslny_z_fraz_klucz();
        char ch=getchar();
        return sciezkaDoPlikuZFrazamiKluczowymi;
    }
    else
    {
        sciezkaDoPlikuZFrazamiKluczowymi=wypisz_sciezke_uzytkownika();
        return sciezkaDoPlikuZFrazamiKluczowymi;
    }
    return sciezkaDoPlikuZFrazamiKluczowymi;
}

vector<string> wektor_pobieranych_fraz_kluczowych_z_pliku(const string sciezkaDoPliku)
{
    fstream plik;
    plik.open(sciezkaDoPliku, ios::in);
    if(plik.good()==true)
    {

        string linia;
        string wartosc;
        vector<string> frazy_kluczowe;
        int nr_linii = 1;

        size_t pozycja;

        while(getline(plik, linia))
        {
            frazy_kluczowe.push_back(linia);
            nr_linii++;
        }

        return frazy_kluczowe;
        //cout<<"frazy kluczore 1:"<<frazy_kluczowe[1]<<endl;
        //k=getchar();

    }
    else
    {
        cout << "Plik nie istnieje!" << endl;
        char ch=getchar();exit(0);
    }

    plik.close();

}

// funkcja z opóźnieniem
void opoznij(int minSekundy, int maxSekundy) {
    int opoznienie = rand() % (maxSekundy - minSekundy + 1) + minSekundy;
    std::this_thread::sleep_for(std::chrono::seconds(opoznienie));
}

void procedura_usuwania_zawartosci_katalogu(const string& sciezkaDoKatalogu)
{
    for (auto& entry : fs::directory_iterator(sciezkaDoKatalogu))
    {
        if (fs::is_regular_file(entry))
        {
            fs::remove(entry.path());
        }
    }
}

void procedura_usuwania_przeanalizowanych_plikow()
{

    procedura_usuwania_zawartosci_katalogu("./ostatnie_analizy_stron/");
    procedura_usuwania_zawartosci_katalogu("./pobrane_strony/");
    procedura_usuwania_zawartosci_katalogu("./wyszukane_strony_google/");

}



vector<vector<string>> wektor_wiersza_naglowkowego_tabeli_csv_analizy_autom()
{
    vector<vector<string>> wierszNaglowkowy;
    vector<string> wiersz;

    wiersz.push_back("Nr pliku.");
    wiersz.push_back("Fraza Kluczowa");
    wiersz.push_back("nr frazy kluczowej");
    wiersz.push_back("nr pozycji wyn. org.");
    wiersz.push_back("link");
    wiersz.push_back("ilość części linku");
    wiersz.push_back("Błąd lub przekierowanie");
    wiersz.push_back("ilość frazy kluczowej");
    //--------------------------------------------
    fstream plik;
    plik.open("elementy_do_wyszukania.txt", ios::in);
    if (plik.is_open())
    {
        // tutaj można czytać dane z pliku
        string linia;
        getline(plik, linia);//pominięcie pierwszej pustej linii.
        while(getline(plik, linia))
        {
            wiersz.push_back(linia);
        }
        plik.close();
    }
    else
    {
        cerr << "Nie udało się otworzyć pliku, aby pobrać dane do zapisania analizy.\n";
    }
    //------------------------------///
    wiersz.push_back("fraza kluczowa w sekcji body");
    wiersz.push_back("fraza kluczowa w słowach kluczowych");
    wiersz.push_back("fraza kluczowa w opisie");
    wiersz.push_back("fraza kluczowa w linku");
    wiersz.push_back("fraza kluczowa w h1");
    wiersz.push_back("fraza kluczowa w h2");
    wiersz.push_back("fraza kluczowa w h3");
    wiersz.push_back("fraza kluczowa w h4");
    wiersz.push_back("fraza kluczowa w h5");
    wiersz.push_back("fraza kluczowa w h6");
    wiersz.push_back("słowa kluczowe w sekcji body");
    wiersz.push_back("słowa kluczowe w słowach kluczowych");
    wiersz.push_back("słowa kluczowe w opisie");
    wiersz.push_back("słowa kluczowe w linku");
    wiersz.push_back("słowa kluczowe w h1");
    wiersz.push_back("słowa kluczowe w h2");
    wiersz.push_back("słowa kluczowe w h3");
    wiersz.push_back("słowa kluczowe w h4");
    wiersz.push_back("słowa kluczowe w h5");
    wiersz.push_back("słowa kluczowe w h6");
    wiersz.push_back("ile razy części linku w sekcji body");
    wierszNaglowkowy.push_back(wiersz);

    // Zwróć wektor wiersza nagłówka
    return wierszNaglowkowy;
}

void zapisz_nowy_plik_csv(const string& nazwa_pliku, const vector<vector<string>>& dane) {
    ofstream plik(nazwa_pliku);
    if (plik.is_open()) {
        for (const auto& wiersz : dane) {
            for (const auto& komorka : wiersz) {
                plik << komorka << ",";
            }
            plik << "\n";
        }
        plik.close();
    }
    else
    {
        cerr << "Nie udało się otworzyć pliku.\n";
    }
}

void dopisz_do_pliku_csv(const string& nazwa_pliku, const vector<vector<string>>& dane) {
    ofstream plik(nazwa_pliku, std::ios::app); // dodanie flagi app
    if (plik.is_open()) {
        for (const auto& wiersz : dane) {
            for (const auto& komorka : wiersz) {
                plik << komorka << ",";
            }
            plik << "\n";
        }
        plik.close();
    }
    else
    {
        cerr << "Nie udało się otworzyć pliku.\n";
    }
}

void procedura_archwizowania_zawartosci(string nazwaFrazyKluczowej)
{
    string sciezkaDocelowa = lokalizacjaArchiwumAnalizy +"/" + nazwaFrazyKluczowej+ "/";
    fs::copy("./ostatnie_analizy_stron", sciezkaDocelowa + "ostatnie_analizy_stron", fs::copy_options::recursive);
    fs::copy("./pobrane_strony", sciezkaDocelowa + "pobrane_strony", fs::copy_options::recursive);
    fs::copy("./wyszukane_strony_google", sciezkaDocelowa + "wyszukane_strony_google", fs::copy_options::recursive);
}

void procedura_tworzenia_folderu_doc_dla_analizy_danej_frazy(string nazwaFrazyKluczowej)
{
    string folderName=lokalizacjaArchiwumAnalizy+"/"+nazwaFrazyKluczowej;
    fs::create_directories(folderName);

}

void procedura_aktualizowania_folderow()
{
    fs::create_directories("./ostatnie_analizy_stron");
    fs::create_directories("./pobrane_strony");
    fs::create_directories("./wyniki_z_automatycznej_analizy");
    fs::create_directories("./wyszukane_strony_google");
}


void procedura_aktualizowania_folderu_autom_analiz()
{

    // Pobranie aktualnej daty i godziny
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Formatowanie daty i godziny
    std::stringstream ss;
    ss << "./wyniki_z_automatycznej_analizy/" << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H-%M-%S");
    std::string folder_name = ss.str();
    lokalizacjaArchiwumAnalizy = folder_name;
    //ss.str() << "/" << nazwaFrazyKluczowej;

    // Utworzenie folderu
    //fs::create_directory("./wyniki_z_automatycznej_analizy/");
    fs::create_directories(folder_name);

    //string nazwaPliku=lokalizacjaArchiwumAnalizy+"/dane_z_automatycznej_analizy_plikow.csv";
    //lokalizacjaWynikowAnalizyCSV = nazwaPliku;
    lokalizacjaWynikowAnalizyCSV=lokalizacjaArchiwumAnalizy+"/dane_z_automatycznej_analizy_plikow.csv";
    zapisz_nowy_plik_csv(lokalizacjaWynikowAnalizyCSV, wektor_wiersza_naglowkowego_tabeli_csv_analizy_autom());

}

vector<vector<string>> wektor_zapisywania_wynikow_analizy_do_pliku_csv(string frazaKluczowa, int nrAnalizowanejFrazy)
{
    vector<vector<string>> tabelaWartosciZAnalizyPlikow;
    const fs::path directory = "./ostatnie_analizy_stron/";

    int nrPozycji=0;


    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            fstream plik;
            stringstream strumien;
            string nazwaPliku;
            vector<string> wiersz;
            static int  nrPliku=0;
                        nrPliku++;
                        strumien << nrPliku;
                    string nrPlikuStr=strumien.str();
                    strumien.str("");

            strumien<<nrAnalizowanejFrazy;
            string nrAnalizowanejFrazyStr=strumien.str();
            strumien.str("");

            nrPozycji++;
            strumien << nrPozycji;
            string nrPozycjiStr=strumien.str();
            strumien.str("");

            wiersz.push_back(nrPlikuStr);
            wiersz.push_back(frazaKluczowa);
            wiersz.push_back(nrAnalizowanejFrazyStr);
            //wiersz.push_back(nrPozycjiStr);

            nazwaPliku = "./ostatnie_analizy_stron/wyniku_analizypliku_HTML_nr_"+nrPozycjiStr+".txt";
            plik.open(nazwaPliku);
            if(plik.good()==true)
            {
                string linia;
                while(getline(plik,linia))
                {
                    size_t pozycjaLink = linia.find("Link:");
                    if(pozycjaLink!= string::npos)
                    {
                        string wartosc = linia.substr(pozycjaLink+6);
                        wartosc="\""+wartosc+"\"";
                        wiersz.push_back(wartosc);
                    }
                    else
                    {
                        size_t pozycja = linia.rfind(":");
                        if(pozycja!= string::npos)
                        {
                            string wartosc = linia.substr(pozycja+1);
                            wiersz.push_back(wartosc);
                        }
                    }
                }
                plik.close();
                tabelaWartosciZAnalizyPlikow.push_back(wiersz);
            }
            else
            {
                cerr << "Nie udało się otworzyć pliku, aby pobrać dane do zapisania analizy.\nNawa pliku: "<<nazwaPliku<<endl;
                exit(0);
            }
        }
    }

    return tabelaWartosciZAnalizyPlikow;

}

void procedura_zakończenia_automatycznego_analizowania_fraz_kluczowych()
{
    cout<<"Zostrały przeanalizowane wszystkie frazy kluczowe. Wyniki zostały zapisane do dolderu ./wyniki_z_automatycznej_analizy/. ";
    char ch=getchar();
}


