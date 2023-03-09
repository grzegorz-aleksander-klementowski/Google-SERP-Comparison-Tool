#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <time.h>
#include <vector>

//WŁASNE FUNCKJE
#include "analiza_pliku_google_SERP.h"
#include "podsumowanieWynikówSERP.h"
#include "automatyzacja_procesu_analizy_fraz_kluczowych.h"
#include "globals.h"

using namespace std;

void procedura_wybierania_frazy_kluczowej();

//ZAMINNE GLOBALNE



int main()
{
    //zasady: KISS, proceduralnie
    //string analizaSERP, frazaGoogleSERP = "duży dom we wrocławskim lesie";

    procedura_wypisywania_strumieniowego(intro_text());
    procedura_zapytania_uzyt_o_automatyzacje();
    procedura_aktualizowania_folderow();
    procedura_usuwania_przeanalizowanych_plikow();

    if(czyWykonacAutomatyzacje==true)
    {
        procedura_aktualizowania_folderu_autom_analiz();
        vector<string> frazy_kluczowe = wektor_pobieranych_fraz_kluczowych_z_pliku(wypisz_sciezke_do_pliku_txt_z_frazami_kluczowymi());
        int nrFrazy=1;
        for (const auto& fraza : frazy_kluczowe)
        {
            procedura_usuwania_przeanalizowanych_plikow();
            pobier_strone_www(link_do_google_serp(fraza), "./wyszukane_strony_google/", "serp_google.html");
            analizaSERP = analiza_pliku_html("./wyszukane_strony_google/serp_google.html");
            procedura_wypisywania_strumieniowego(analizaSERP);
            przyg_do_porow_stron_serp(analizaSERP);
            pobieranie_stron_html_z_serp();
            procedura_wypisywania_podsumowania_serp(fraza);

            procedura_tworzenia_folderu_doc_dla_analizy_danej_frazy(fraza);
            procedura_archwizowania_zawartosci(fraza);

            dopisz_do_pliku_csv(lokalizacjaWynikowAnalizyCSV, wektor_zapisywania_wynikow_analizy_do_pliku_csv(fraza,nrFrazy++));

            opoznij(5, 10);
        }
        procedura_zakończenia_automatycznego_analizowania_fraz_kluczowych();

    }
    else
    {
        frazaGoogleSERP = fraza_google();

        pobier_strone_www(link_do_google_serp(frazaGoogleSERP), "./wyszukane_strony_google/", "serp_google.html");
        analizaSERP = analiza_pliku_html("./wyszukane_strony_google/serp_google.html");
        procedura_wypisywania_strumieniowego(analizaSERP);
        przyg_do_porow_stron_serp(analizaSERP);
        pobieranie_stron_html_z_serp();

        procedura_wypisywania_podsumowania_serp(frazaGoogleSERP);
    }

    return 0;
}
