#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <time.h>
#include "analiza_pliku_google_SERP.h"
#include "podsumowanieWynikówSERP.h"

using namespace std;



//ZAMINNE GLOBALNE
string frazaGoogleSERP;
string analizaSERP;



int main()
{
    //zasady: KISS, proceduralnie
    //string analizaSERP, frazaGoogleSERP = "duży dom we wrocławskim lesie";

    proceduraWypisywaniaStrumieniowego(introText());

    //procesWykonywaniaNowejAnalizySERP(true);

    frazaGoogleSERP = frazaGoogle();
    pobierzStroneWWW(linkDoGoogleSERP(frazaGoogleSERP), "./wyszukane_strony_google/", "serp_google.html");
    analizaSERP = analizaPlikuHTML("./wyszukane_strony_google/serp_google.html");
    proceduraWypisywaniaStrumieniowego(analizaSERP);
    przygDoPorowStronSERP(analizaSERP);
    pobieranieStronHTMLzSERP();


    //proceduraZamianyPlikuPrezentujacyDaneNaCSV();

    return 0;
}


//FUNKCJE


/*
void proceduraZamianyPlikuPrezentujacyDaneNaCSV()
{
    system("mkdir -p ./PobraneStrony/Analizy_Stron/plikiCSV");
    fstream plik;
    string sciezkaDoPliku = "./PobraneStrony/Analizy_Stron/wynikuAnalizyPlikuHTMLnr_1.txt";
    plik.open(sciezkaDoPliku, ios::in);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje!" << endl;
        exit(0);
    }
    string linia;
    string wartosc;
    string dana;
    int nr_linii = 1;

    size_t pozycja;

    while(getline(plik,linia))
    {
        if (linia.find("Link:") != string::npos)
        {
            dana = "Link: ";
            pozycja = linia.find(dana);
            wartosc = linia.substr(pozycja + dana.length());
        }
    }
    cout << wartosc;
}


*/

