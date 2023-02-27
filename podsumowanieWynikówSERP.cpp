#include <iostream>

#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <time.h>
#include "analiza_pliku_google_SERP.h"

#include "podsumowanieWynikówSERP.h"




void przygDoPorowStronSERP(string plikSERP)
{
    char ch;
    fstream plik;

    plik.open("./wyszukane_strony_google/przeanalizowane_wyniki_serp.txt", ios::out);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje!" << endl;
        exit(0);
    }
    plik<<analizaPlikuHTML;
    plik.close();

    cout<<"Wyniki GOOGLE SERP są gotowe."<<endl<<endl<<"Wciśnij klawisz abu kontynuować."<<endl;
    ch=getchar();

    system("clear");
    cout<<"Pobieram pliki..."<<endl;


}

void pobieranieStronHTMLzSERP()
{
    fstream plik;
    string linia[200], linkDoStrony[15], wczytanaLinia, nazwaPobranegoPliku;
    stringstream nazwaPobranegoPlikuStr;
    char zakazaneZnaki[3] = {'(', ')', '^'};
    int zakazaneZnakiRozmiar = sizeof(zakazaneZnaki)/sizeof(zakazaneZnaki[0]);
    int nr_linii=0, nr_liku=1;
    size_t pozycja;


    plik.open("./wyszukane_strony_google/przeanalizowane_wyniki_serp.txt", ios::in);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje!" << endl;
        exit(0);
    }

    while(getline(plik, wczytanaLinia))
    {
        linia[nr_linii] = wczytanaLinia;
        if(linia[nr_linii].substr(0,4)=="LINK")
        {
            linia[nr_linii] = linia[nr_linii].substr(6,300);
            linkDoStrony[nr_liku] = linia[nr_linii];

            cout<<"Pobieram : "<<linkDoStrony[nr_liku]<<endl;
            cout<<"nr_wyniku: "<<nr_liku<<endl;

            for(int i=0; i<zakazaneZnakiRozmiar; i++)
            {
                pozycja = linkDoStrony[nr_liku].find(zakazaneZnaki[i]);
                while (pozycja!=string::npos)
                {
                    cout<<"Znaleziono niedozwolony znak. "<<"Pozcyja: "<<pozycja<<endl;
                    linkDoStrony[nr_liku].insert(pozycja, "\\");
                    cout<<"Nowy link : "<<linkDoStrony[nr_liku]<<endl;
                    pozycja = linkDoStrony[nr_liku].find(zakazaneZnaki[i], pozycja+2);
                }
            }

            nazwaPobranegoPlikuStr << "wynikSERPnr_" << nr_liku << ".html";
            nazwaPobranegoPliku = nazwaPobranegoPlikuStr.str();
            pobierzStroneWWW(linkDoStrony[nr_liku], "./PobraneStrony/", nazwaPobranegoPliku);
            nazwaPobranegoPlikuStr.str("");
            nr_liku++;
        }

        nr_linii++;

    }

    plik.close();

    //cout<<"ls -l ./PobraneStrony/"<<endl;
    //system("ls -l ./PobraneStrony/");

}

string podsumowanieWynikowSERP(string frazaGlowna, int nr_PlikuDoAnalizy)
{

    fstream plik_z_frazami_do_wyszukania;
    string liniaDoFraz,tablicaFraz[100];
    int iloscFraz=0, nr_linii=0, nr_pliku=nr_PlikuDoAnalizy;

    plik_z_frazami_do_wyszukania.open("elementy_do_wyszukania.txt", ios::in);
        if(plik_z_frazami_do_wyszukania.good()==false)
        {
            cout<<"Coś poszło nie tak!" << endl;
            plik_z_frazami_do_wyszukania.close();
            exit(0);
        }

        while(getline(plik_z_frazami_do_wyszukania, liniaDoFraz))
        {
            //cout<<"linia: "<< liniaDoFraz<<endl;
            tablicaFraz[iloscFraz] = liniaDoFraz;
            iloscFraz++;
        }
        //cout<<"iloscFraz: " << iloscFraz << endl;
        string frazaDoWyszukania[iloscFraz];

    plik_z_frazami_do_wyszukania.close();


    plik_z_frazami_do_wyszukania.open("elementy_do_wyszukania.txt", ios::in);
        if(plik_z_frazami_do_wyszukania.good()==false)
        {
            return "Coś poszło nie tak!";
            plik_z_frazami_do_wyszukania.close();
            exit(0);
        }
        liniaDoFraz="";
        while(getline(plik_z_frazami_do_wyszukania, liniaDoFraz))
        {
            frazaDoWyszukania[nr_linii] = liniaDoFraz;
            nr_linii++;
        }
        frazaDoWyszukania[0] = frazaGlowna;

    plik_z_frazami_do_wyszukania.close();

    //--------WYLICZANIE-----------

    int nr_frazy = 0, frazaDoWyszukaniaRozmiar, iloscPlikowHTMLWynikowSERP;

    fstream plik;
    stringstream sStream, sciezkaDoPlikuStream;
    string s, sciezkaDoPliku;
    string linkStrony;
    char ch;

    iloscPlikowHTMLWynikowSERP = ile_plikow_html();
    sStream.str("");

    if(nr_pliku <= iloscPlikowHTMLWynikowSERP)
    {

        sciezkaDoPlikuStream.str("");


        sciezkaDoPlikuStream << "./PobraneStrony/wynikSERPnr_" << nr_pliku << ".html";
        sciezkaDoPliku = sciezkaDoPlikuStream.str();

        string cialoStrony = wypiszCialoStrony(sciezkaDoPliku);


        int ilewPlikuFraz=0, ileKeywords=0;
        int nrNaglowka, nrCzesciLinku=0, nr_wypisywanegoNaglowka = 1;
        int iloscNaglowkow_h=6;
        int iloscTypowPodsumowania=3;


        string slowaKlucze, opis;
        //string naglowek, czescLinku[4];///TUUTAJJJ!!!
        stringstream naglowekStream;
        //ZMIENNE DO PODSUMOWANIA:
        int ilosc_tylkoBody[iloscTypowPodsumowania],
            ilosc_opis[iloscTypowPodsumowania],
            ilosc_slowaKluczowe[iloscTypowPodsumowania],
            ilosc_link[iloscTypowPodsumowania],
            ilosc_h[iloscNaglowkow_h+1][iloscTypowPodsumowania];


        for(int j=0; j<=2; j++)
        {
            ilosc_tylkoBody[j]=0;
            ilosc_opis[j]=0,
            ilosc_slowaKluczowe[j]=0,
            ilosc_link[j]=0;
            for(int i=0;i<=iloscNaglowkow_h;i++)
            {
                ilosc_h[i][j]=0;//cout<<"ilosc_h["<<i<<"]["<<j<<"]: "<<ilosc_h[i][j]<<endl;
            }
        }

        plik.open(sciezkaDoPliku, ios::in);
        if(plik.good())
        {

            int iloscSlowFrazy = iloscSlowWiekszychNizDwieLiterki(frazaDoWyszukania[0]);
            for(int k=1;k<=iloscSlowFrazy;k++)ilosc_tylkoBody[0] = ilosc_tylkoBody[0] + ilosc_frazy_w_fragmencie(cialoStrony, wyjmijSlowo_o_numerze(frazaDoWyszukania[0],k));
            //ilosc_tylkoBody[0] = ilosc_frazy_w_fragmencie(cialoStrony, frazaDoWyszukania[0]);// liczy ilosc frazy gł. w <body>

            sStream << endl << endl << endl << "-------DANE Z WYNIKU SERP NR ["<< nr_pliku << "]-------" << endl;
            //CZŚCI LINKU
            linkStrony = wypiszLinkzPlikuPrzeanalizowanychSERP(nr_pliku);
            int inloscCzesciLinku = ilosc_frazy_w_fragmencie(linkStrony,"/")-1;
            int ilewPlikuFraz_h[iloscNaglowkow_h];
            if(linkStrony[(linkStrony.length())-1]=='/')inloscCzesciLinku--;
            string naglowek, czescLinku[inloscCzesciLinku];///TUUTAJJJ!!!
            string znacznikMetaDescription;

            znacznikMetaDescription = znajdzWypiszFrazeMeta("name=\"keywords\"", sciezkaDoPliku);
            slowaKlucze = wypiszZawartoscArgumentuzZnacznika(znacznikMetaDescription, "content");
            ileKeywords = ile_slow_kluczy(slowaKlucze);
            string slowoKlucz[ileKeywords];


            sStream<<"Link: "<<linkStrony<<endl;

            for(int k=1;k<=iloscSlowFrazy;k++)ilosc_link[0] = ilosc_link[0] + ilosc_frazy_w_fragmencie(linkStrony, wyjmijSlowo_o_numerze(frazaDoWyszukania[0],k));
            //ilosc_link[0] = ilosc_frazy_w_fragmencie(linkStrony,frazaDoWyszukania[0]);

            nrCzesciLinku=0;
            while(czescLinku[nrCzesciLinku].substr(0,7) != "Błąd!")
            {

                czescLinku[nrCzesciLinku] = wypiszCzesciLinku(nr_pliku,nrCzesciLinku);
                sStream<<"Część linku ["<<nrCzesciLinku<<"]: "<<czescLinku[nrCzesciLinku]<<endl;
                ilosc_tylkoBody[2]  = ilosc_tylkoBody[2]    + ilosc_frazy_w_fragmencie(cialoStrony, czescLinku[nrCzesciLinku]);
                ilosc_opis[2]  = ilosc_opis[2]    + ilosc_frazy_w_fragmencie(opis, czescLinku[nrCzesciLinku]);
                nrCzesciLinku++;
                czescLinku[nrCzesciLinku] = wypiszCzesciLinku(nr_pliku,nrCzesciLinku); //TU JEST BŁĄĄĄĄD!!!


            }

            sStream<<"Ilość części linku: "<<nrCzesciLinku<<endl;
            for(int i=0; i<iloscFraz; i++)
            {
                ilosc_h[1][1] = 0;
                ilewPlikuFraz = ilosc_frazy_w_pliku(frazaDoWyszukania[i], sciezkaDoPliku);
                nrNaglowka=1;
                sStream  << "Element: " << frazaDoWyszukania[i] << " | " << "Znaleziono elemetnów: "<<ilewPlikuFraz<<endl;

                //WYPISYWANIE OPIS
                if((frazaDoWyszukania[i]=="name=\"description") && (ilewPlikuFraz>0))
                {

                    znacznikMetaDescription = znajdzWypiszFrazeMeta("name=\"description", sciezkaDoPliku);
                    opis = wypiszZawartoscArgumentuzZnacznika(znacznikMetaDescription, "content");

                    for(int k=1;k<=iloscSlowFrazy;k++)ilosc_opis[0] = ilosc_opis[0] + ilosc_frazy_w_fragmencie(opis, wyjmijSlowo_o_numerze(frazaDoWyszukania[0],k));

                    //ilosc_opis[0] = ilosc_frazy_w_fragmencie(opis,frazaDoWyszukania[0]);

                    sStream<< "      " <<"Opis: "<< opis << endl;
                    if((opis.find("I:")!=string::npos) && (ilewPlikuFraz>1))sStream<< "      "  << "I: Autor wstawił pusty lub nieprawidlowy opis oraz jest więcej niż jedna descripcje. "<< endl;
                    else if(opis=="") sStream << "I: Autor wstawił pusty opis. "<<endl;
                }

                //WYPISYWANIE KEYWORDS

                //znacznikMetaDescription = znajdzWypiszFrazeMeta("name=\"keywords\"", sciezkaDoPliku);
                //slowaKlucze = wypiszZawartoscArgumentuzZnacznika(znacznikMetaDescription, "content");
                //ileKeywords = ile_slow_kluczy(slowaKlucze);
                //string slowoKlucz[ileKeywords];

                if((frazaDoWyszukania[i]=="name=\"keywords") && (ilewPlikuFraz>0))
                {

                    int nrSlowaKluczowego;
                    int iloscSLowKluczy = ile_slow_kluczy(slowaKlucze);

                    for(int k=1;k<=iloscSlowFrazy;k++)ilosc_slowaKluczowe[0] = ilosc_slowaKluczowe[0] + ilosc_frazy_w_fragmencie(slowaKlucze, wyjmijSlowo_o_numerze(frazaDoWyszukania[0],k));

                    nrSlowaKluczowego = 0;
                    //if(iloscSLowKluczy<=15)
                    //{
                        if(iloscSLowKluczy<=15)sStream<< "      " <<"Słowa kluczowe("<<iloscSLowKluczy<<"): " << endl;
                        while(nrSlowaKluczowego<ileKeywords)
                        {

                            slowoKlucz[nrSlowaKluczowego]=wypiszSlowoKlucz(slowaKlucze,nrSlowaKluczowego);
                            // WYPISUJE SLOWA KLUCZE:
                            if(iloscSLowKluczy<=15)sStream<< "      " <<"slowo klucz nr "<< nrSlowaKluczowego+1 << ": " <<slowoKlucz[nrSlowaKluczowego]<<endl;
                            //ilosc_tylkoBody[1] = ilosc_tylkoBody + ilosc_frazy_w_fragmencie(cialoStrony,slowoKlucz[nrSlowaKluczowego]);
                            ilosc_tylkoBody[1]  = ilosc_tylkoBody[1]    + ilosc_frazy_w_fragmencie(cialoStrony, slowoKlucz[nrSlowaKluczowego]);
                            ilosc_opis[1]       = ilosc_opis[1]         + ilosc_frazy_w_fragmencie(opis,        slowoKlucz[nrSlowaKluczowego]);
                            ilosc_link[1]       = ilosc_link[1]         + ilosc_frazy_w_fragmencie(linkStrony,  slowoKlucz[nrSlowaKluczowego]);


                            nrSlowaKluczowego++;

                        }
                    //}
                    if(iloscSLowKluczy>15) sStream<< "      " <<"Słowa kluczowe("<<iloscSLowKluczy<<"): "<< slowaKlucze << endl;// <-- WYPISYWANIE SŁÓW KLUCZOWYCH W JEDNYM CIĄGU

                }



                //WYPISYWANIE NAGLOWKA
                string naglowekDoWypisania[ilewPlikuFraz+1][iloscNaglowkow_h];
                while(nrNaglowka<=iloscNaglowkow_h)
                {

                    naglowekStream.str("");
                    nr_wypisywanegoNaglowka = 1;
                    naglowekStream << "<h"<<nrNaglowka;
                    naglowek = naglowekStream.str();

                    if((frazaDoWyszukania[i]==naglowek) && (ilewPlikuFraz>0))
                    {
                        //string naglowekDoWypisania[ilewPlikuFraz+1][iloscNaglowkow_h];
                        stringstream streamNaglowki;
                        ilewPlikuFraz_h[nrNaglowka]=ilewPlikuFraz;
                        //sStream << "naglowki <h"<<nrNaglowka<<"..: " << endl;
                        while(nr_wypisywanegoNaglowka<=ilewPlikuFraz)
                        {

                            naglowekDoWypisania[nr_wypisywanegoNaglowka][nrNaglowka] = wypiszZawartoscNaglowka(nrNaglowka,cialoStrony, nr_wypisywanegoNaglowka, ilewPlikuFraz);
                            streamNaglowki << naglowekDoWypisania[nr_wypisywanegoNaglowka][nrNaglowka];
                            //sStream << "Nagowek [" << nr_wypisywanegoNaglowka << "]: " << naglowekDoWypisania[nr_wypisywanegoNaglowka][nrNaglowka] <<endl;

                            nr_wypisywanegoNaglowka++;

                        }
                        //sStream<<streamNaglowki.str()<<endl;//sprawdza, czy wszystkie naglowki danego poziomu są w jedne zmiennej
                        //cout<<"STREAM: "<<streamNaglowki.str()<<endl;

                        for(int k=1;k<=iloscSlowFrazy;k++)
                        ilosc_h[nrNaglowka][0]   = ilosc_h[nrNaglowka][0] +
                                                   ilosc_frazy_w_fragmencie(streamNaglowki.str(), wyjmijSlowo_o_numerze(frazaDoWyszukania[0],k));

                        if(ileKeywords>1)
                        for(int m=0;m<ileKeywords;m++)
                        ilosc_h[nrNaglowka][1] = ilosc_h[nrNaglowka][1]
                        + ilosc_frazy_w_fragmencie(streamNaglowki.str(), slowoKlucz[m]);


                        //ilosc_h[nrNaglowka][0] = ilosc_frazy_w_fragmencie(streamNaglowki.str(), frazaDoWyszukania[0]);

                        streamNaglowki.str("");
                        //sStream << "Wybieram nagłowek 6: " << doWypisania[6]<<endl;

                    }
                    nrNaglowka++;
                    //cout<<"NAGŁÓWEK DO WYPISAINA: 3,2: "<<naglowekDoWypisania[3][2]<<endl;

                }


                //s = sStream.str();

            }



            sStream << "-------WYNIKI PODSUMOWUJĄCE NR "<< nr_pliku <<" SERP ZAWIERA-------"<<endl<<endl;
            for(int l=0;l<iloscTypowPodsumowania;l++)
            sStream<<wypiszObliczeniaPodsumowania
                (
                    l,nr_pliku,ilosc_tylkoBody[l],
                    ilosc_opis[l],
                    ilosc_slowaKluczowe[l],
                    ilosc_link[l],
                    ilosc_h[1][l],ilosc_h[2][l],ilosc_h[3][l],ilosc_h[4][l],ilosc_h[5][l],ilosc_h[6][l]
                )
            <<endl;

            //sStream<<wypiszObliczeniaPodsumowania(1,nr_pliku,ilosc_tylkoBody[1],ilosc_opis[1],ilosc_slowaKluczowe[1],ilosc_link[1],ilosc_h[1][1],ilosc_h[2][1],ilosc_h[3][1],ilosc_h[4][1],ilosc_h[5][1],ilosc_h[6][1])<<endl;
            s = sStream.str();

            plik.close();
            nr_pliku++;
        }
        else
        {
            cout<<"Coś poszło nie tak! Plik, który próbuje odczytać jest prawdopodobnie uszkodzony lub otwarty." << endl;
            plik.close();
            nr_pliku++;
            //exit(0);
        }
    }
    else
    {
        return "Plik nie istnieje!";
    }
    if(plik.is_open()==true)plik.close();

    return s;
}

int ilosc_frazy_w_pliku(string fraza, string sciezkaDoPliku)
{
    size_t nPos;
    int liczbaWyszukiwan=0;
    fstream plik;
    string wyszukiwanyElement=fraza, sciezka=sciezkaDoPliku, linia;

    plik.open(sciezkaDoPliku, ios::in);
    if(plik.good()==false)
    {
        cout << "Nie można znalźć pliku!" << endl;
        exit(0);
    }
    if(plik.is_open())
    {
        while(getline(plik, linia))
        {
            if (linia.find(wyszukiwanyElement) != std::string::npos)
            {
                nPos = linia.find(wyszukiwanyElement); // first occurrence
                while(nPos != string::npos)
                {
                    nPos = linia.find(wyszukiwanyElement, nPos + 1);
                    liczbaWyszukiwan++;
                }
            }
        }
    }
    else
    {
        cout<<"Plik nie jest otwarty!"<<endl;
        exit(0);
    }

    plik.close();
    return liczbaWyszukiwan;
}


int ile_plikow_html()
{
    fstream plik;
    string linia;
    string lancuch_z_numerem;
    int iloscPlikow;


    plik.open("./wyszukane_strony_google/przeanalizowane_wyniki_serp.txt", ios::in);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje!" << endl;
        exit(0);
    }

    while(getline(plik, linia))
    {

        if(linia.find("Wszystkich wyników: ") != string::npos)
        {
            if(linia.substr(22, 1)==" ")
            {
                lancuch_z_numerem = linia.substr(21, 1);
            }
            else
            {
                lancuch_z_numerem = linia.substr(21,2);
            }

        }
        iloscPlikow = atoi(lancuch_z_numerem.c_str());

    }
    return iloscPlikow;
}

string znajdzWypiszFrazeMeta(string fraza, string sciezkaDoPliku)
{
    size_t nPos=0, nPos2=0, pozycjaEW=0;
    int liczbaWyszukiwan=0;
    fstream plik;
    string wyszukiwanyElement=fraza, sciezka=sciezkaDoPliku, linia, wynik, napisTagMeta;
    stringstream stream;
    string pomocniczy;
    bool czyZawieraWyszElement = false;
    bool czySzukacwNastepnejLinii = false;
    plik.open(sciezkaDoPliku, ios::in);
    if(plik.good()==false)
    {
        return "Nie można znalźć pliku!";
        exit(0);
    }
    if(plik.is_open())
    {
        //cout<<"TEST 5-1-1-1"<<endl;
        while(getline(plik, linia))
        {

            //szukanie końcówki w następnej linii
            if(czySzukacwNastepnejLinii==true)
            {
                if(linia.find(">") != string::npos)
                {
                    napisTagMeta = napisTagMeta + linia.substr(0,linia.find(">"));
                    return napisTagMeta;
                    czySzukacwNastepnejLinii=false;
                }
                else
                {
                    napisTagMeta = napisTagMeta + linia;
                    czySzukacwNastepnejLinii=true;  //poszukaj w następnej linii
                }
            }
            else
            {
                if (linia.find(wyszukiwanyElement) != std::string::npos) //szukanie nPos(1)
                {
                    pozycjaEW = linia.find(wyszukiwanyElement);
                    if(linia.find("<meta")<pozycjaEW)
                    {
                        nPos = linia.find("<meta");
                        while(linia.find("<meta",nPos)<pozycjaEW)
                        {
                            //znalezione poz. nPos1
                            nPos = linia.find("<meta", nPos);
                            if(linia.find('>', nPos) != string::npos) //szukanie npoz2
                            {
                                czySzukacwNastepnejLinii = false;
                                nPos2 = linia.substr(nPos).find('>');
                                napisTagMeta = linia.substr(nPos, nPos2);
                                if(napisTagMeta.find(wyszukiwanyElement) != string::npos) return napisTagMeta;
                            }
                            else //jeśli w tej linii nie ma to daj resztę tagu do zmiennej i szukaj w następnej linii.
                            {
                                czySzukacwNastepnejLinii = true;
                                napisTagMeta = linia.substr(nPos);
                            }

                            nPos = linia.find("<meta", nPos+1);
                        }
                    }
                    else
                    {
                        nPos = 0;
                        if(linia.find('>', nPos) != string::npos)
                        {
                            nPos2 = linia.substr(nPos).find('>');
                            czySzukacwNastepnejLinii = false;
                            napisTagMeta = linia.substr(nPos, nPos2);
                            return napisTagMeta;
                        }//jeśli w tej linii nie ma to daj resztę tagu do zmiennej i szukaj w następnej linii.
                        else
                        {
                            czySzukacwNastepnejLinii = true;
                            napisTagMeta = linia.substr(nPos);
                        }
                    }
                }
            }

        }

    }
    else return "Wystąpił błąd: Plik nie jest otwarty lub nie istnieje.";
    plik.close();

    return "Coś poszło nie tak: Nieznany błąd.";
}

int ile_slow_kluczy(string slowaKlucze)
{
    string s=slowaKlucze;
    int n=0;
    for(int i=0;i<=s.length();i++)
    {
        if(s[i]==',') n++;

    }
    return n+1;
}

string wypiszSlowoKlucz(string lancuchSlowKluczy, int nrSlowaKlucz)
{
    string slowoKlucz;
    int n=0,i;
    size_t nPos=0, nPos2=0;

    for(i=0;((i<=lancuchSlowKluczy.length())&&(n<=nrSlowaKlucz));i++)
    {
        if(lancuchSlowKluczy[i]==',')
        {
            if(n==nrSlowaKlucz-1)
            {
                nPos=i+2;
            }
            n++;
        }
    }
    lancuchSlowKluczy = lancuchSlowKluczy.substr(nPos);
    nPos2=lancuchSlowKluczy.find(',');
    lancuchSlowKluczy = lancuchSlowKluczy.substr(0,nPos2);
    slowoKlucz = lancuchSlowKluczy;
    return slowoKlucz;
}

string wypiszCialoStrony(string sciezkaDoPliku)
{
    fstream plik;
    string linia, calyPlikTekst, frazaPocz="<body", frazaKon="</body", wynik;
    stringstream stream;
    size_t nPos, nPos2;

    plik.open(sciezkaDoPliku, ios::in);
    if(plik.good()==true)
    {
        while(getline(plik,linia))
        {
            stream<<linia;
        }
        calyPlikTekst = stream.str();

        if(calyPlikTekst.find(frazaPocz) != string::npos)
        {
            wynik = calyPlikTekst.substr
            (
                (calyPlikTekst.find(frazaPocz)),
                (calyPlikTekst.substr(calyPlikTekst.find(frazaPocz)).find(frazaKon))
            );
        }
    }
    else wynik = "Coś jest nie tak z plikiem!\n";

    if(wynik=="") wynik="Coś jest nie tak...";
    //return wynik;
    return wynik;
}


string wypiszZawartoscNaglowka(int nrNaglowka, string cialoStronyDoPrzeszukania, int nrSzukanegoNaglowka, int iloscZnalezionychNaglowkow)
{
    string frazaPoczDoWyszukania, frazaKoczDoWyszukania, wynik, znalezionyNaglokow[iloscZnalezionychNaglowkow];
    stringstream stream;
    size_t nPos=0, nPos2=0;
    int nrZnalezionegoNaglowka=1;
    //nrSzukanegoNaglowka =3;

    stream << "<h" << nrNaglowka;
    frazaPoczDoWyszukania = stream.str();
    stream.str("");
    stream <<"/h" << nrNaglowka << ">";
    frazaKoczDoWyszukania = stream.str();
    stream.str("");


    if(cialoStronyDoPrzeszukania.find(frazaPoczDoWyszukania) != string::npos)
    {
        if(nrZnalezionegoNaglowka<=iloscZnalezionychNaglowkow)
        {
            nPos = cialoStronyDoPrzeszukania.find(frazaPoczDoWyszukania);
            while((nPos != string::npos) && (nrZnalezionegoNaglowka<=iloscZnalezionychNaglowkow) && (nrZnalezionegoNaglowka<=nrSzukanegoNaglowka))
            {
                //wynik = "Szukam innego nagłówka...";

                //stream << nrZnalezionegoNaglowka<< ".: ";
                //stream << cialoStronyDoPrzeszukania.substr(nPos, 120)<< endl;
                nPos2   = cialoStronyDoPrzeszukania.substr(nPos).find(frazaKoczDoWyszukania);
                if(nPos2>1000)
                {
                    nPos2 == 200;
                }

                //stream << cialoStronyDoPrzeszukania.substr(nPos, nPos2+3)<< endl;
                //wynik = stream.str();
                if(nrZnalezionegoNaglowka == nrSzukanegoNaglowka)
                {
                    wynik = cialoStronyDoPrzeszukania.substr(nPos, nPos2+3);
                    //stream << cialoStronyDoPrzeszukania.substr(nPos, nPos2+3)<< endl;
                    //wynik = stream.str();
                }
                nPos = cialoStronyDoPrzeszukania.find(frazaPoczDoWyszukania, nPos+1);
                nrZnalezionegoNaglowka++;
            }
        } else wynik = "Coś jest nie tak! Numer szukanego nagłówka jest większy ni ż sama ilosć nagłówków!";
    }
    else if(wynik=="") wynik="Zawartość jest pusta!";
    else
    {
        wynik = "Coś jest nie tak! Nagłówek ine zostal znaleziony.";
    }


    return wynik;
}


string wypiszLinkzPlikuPrzeanalizowanychSERP(int numerPliku)
{
    fstream plik;
    string linia[200], linkDoStrony[15], wczytanaLinia, nazwaPobranegoPliku;
    stringstream nazwaPobranegoPlikuStr;
    char zakazaneZnaki[3] = {'(', ')', '^'};
    int zakazaneZnakiRozmiar = sizeof(zakazaneZnaki)/sizeof(zakazaneZnaki[0]);
    int nr_linii=0, nr_liku=1;
    size_t pozycja;


    plik.open("./wyszukane_strony_google/przeanalizowane_wyniki_serp.txt", ios::in);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje!" << endl;
        exit(0);
    }

    while(getline(plik, wczytanaLinia))
    {
        linia[nr_linii] = wczytanaLinia;
        if(linia[nr_linii].substr(0,4)=="LINK")
        {
            linia[nr_linii] = linia[nr_linii].substr(6,300);
            linkDoStrony[nr_liku] = linia[nr_linii];

            nazwaPobranegoPlikuStr <<linkDoStrony[numerPliku];
            nazwaPobranegoPliku = nazwaPobranegoPlikuStr.str();

            nazwaPobranegoPlikuStr.str("");
            nr_liku++;
        }

        nr_linii++;

    }

    plik.close();
    return nazwaPobranegoPliku;
}


string wypiszCzesciLinku(int nrWynikuSERP, int nr_warstwyLinku)
{
    fstream plik;
    string linia, liniaPliku[150], liniaWyniku, wynik;
    stringstream stream;
    int nr_linii=0, nr_liniiZwarstwamiStron, iloscWarstw=0;
    size_t nPos;
    plik.open("./wyszukane_strony_google/przeanalizowane_wyniki_serp.txt", ios::in);
    if(plik.good()==true)
    {
        if(nrWynikuSERP<10)stream<<"Wynik [0"<<nrWynikuSERP;
        else stream<<"Wynik ["<<nrWynikuSERP;
        liniaWyniku = stream.str();
        stream.str("");
        while(getline(plik,linia))
        {
            liniaPliku[nr_linii] = linia;
            if(linia.find(liniaWyniku)!= string::npos)nr_liniiZwarstwamiStron = nr_linii;
            nr_linii++;
        }
        while(liniaPliku[nr_liniiZwarstwamiStron+4+iloscWarstw].substr(0,6)=="strona")iloscWarstw++;
        if(nr_warstwyLinku<iloscWarstw)
        wynik = liniaPliku[nr_liniiZwarstwamiStron+4+nr_warstwyLinku].substr(11);
        else wynik = "Błąd! Nie znaleziono warstwy linku!";
    }
    else wynik = "Błąd! Plik z wynikami SERP jest nie dostępny!";
    return wynik;
}

void proceduraWypisywaniaPodsumowaniaSERP(string frazaGlownaSERP)
{
    string frazaGoogleSERP=frazaGlownaSERP, wynikuPlikuSERP, sciezkaPlikuDocelowego;
    stringstream sStream;
    fstream plik;
    int ilePlikow = ile_plikow_html();
    char ch;
    cout<<"Czy wypisać szczegółowe wyniki dla każdego wyniku oddzielnie? "<<endl; //tutaj X
    bool czyWypisacWynikiSzczegolowo = czyTakLubNie(wypisujeZnakTakLubNie());
    system("clear");


    for(int i=1; i<=ilePlikow; i++)
    {
        wynikuPlikuSERP = podsumowanieWynikowSERP(frazaGoogleSERP, i);
        if(czyWypisacWynikiSzczegolowo== true) cout << wynikuPlikuSERP;
        else
        {
            cout<<"Nie wypisuje wyników, kończę program..."<<endl;
            exit(0);
        }
        sStream.str("");sStream<<"./PobraneStrony/Analizy_Stron/wynikuAnalizyPlikuHTMLnr_"<<i<<".txt";
        sciezkaPlikuDocelowego=sStream.str(); sStream.str("");
        plik.open(sciezkaPlikuDocelowego,ios::out);
            plik<<wynikuPlikuSERP;
        plik.close();

        if(czyWypisacWynikiSzczegolowo==true)
        {
            if(i<ilePlikow)
            {
                cout << endl << "Odczytano plik wyniku " << i << ". " << endl << "Wciśnij ENTER by przejść do analizy następnego wyniku..." << endl;
                getchar();
                system("clear");
            }
            else if(i==ilePlikow)
            {
                cout << endl << "To już ostatnia szczegółowa Analiza Pliku SERP. Wciśnij ENTER, by przejść do ogólnego podsumowania." << endl;
                ch=getchar();
                system("clear");
            }
        }
    }
}

bool czyTakLubNie(char odpowiedz)
{
    odpowiedz = tolower(odpowiedz);
    if((odpowiedz=='t') || (odpowiedz=='n'))
    {
        if(odpowiedz=='t') return true;
        else if(odpowiedz=='n') return false;
        else wykrytoBlad("Wykryto nieoczekiwany bląd!", "Znak jest niepoprawny. Zamykam probram...");
    }
    else wykrytoBlad("Wpisano nieodpowiedni znak!", "Znak jest niepoprawny. Zamykam probram...");
}

char wypisujeZnakTakLubNie()
{
    char ch, pch;
    int n;
    string s;

    while(((ch!='t') || (ch!='n')))
    {
        cout << "Wypisz \"t\" lub \"n\": ";
        n=0;
        while((ch = getchar()) != EOF && ch != '\n')
        {
            n++; if(n==1) pch=ch;
        }
        pch=tolower(pch);
        if (((pch=='t') || (pch=='n')) && (n==1)) return pch;
        cout << "\033[A\33\[2K\r";
    }
}

void proceduraWypisywaniaStrumieniowego(string text)
{
    cout << text;
}

string wypiszObliczeniaPodsumowania
(
int typ,//1=FRAZĘ WYSZUKIWANIA JEST ZAWARTA W: 2=ILOŚĆ SŁÓW KLUCZOWYCH(nr_slow_klucz.) MOŻNA ZNALEŹĆ: 3.ILE RAZY CZESCI LINKU ZNAJDUJĄ SIĘ W:
int nr_pliku,
int ilosc_tylkoBody,
int ilosc_opis,
int ilosc_slowaKluczowe,
int ilosc_link,
int ilosc_h1,
int ilosc_h2,
int ilosc_h3,
int ilosc_h4,
int ilosc_h5,
int ilosc_h6
)
{
    string
        wynik,
        nazwa;
    stringstream sStream;

    //sStream << "-------WYNIK NR "<< nr_pliku <<" SERP ZAWIERA-------"<<endl;
    if(typ==0) nazwa = "FRAZĘ WYSZUKIWANIA JEST ZAWARTA W: \n";
    else if(typ==1) nazwa = "ILOŚĆ SŁÓW KLUCZOWYCH MOŻNA ZNALEŹĆ:\n";
    else if(typ==2) nazwa = "ILE RAZY CZESCI LINKU ZNAJDUJĄ SIĘ W:\n";
    else nazwa = "I: nieznany typ wyniku.";

    sStream << nazwa;
    if(typ!=2)
    {

        sStream
        << "tylko w sekcji body:"   << ilosc_tylkoBody      << endl
        << "słowach kluczowych:"    << ilosc_slowaKluczowe  << endl
        << "opis:"                  << ilosc_opis           << endl
        << "link:"                  << ilosc_link           << endl
        << "nagłówki: h1-" << ilosc_h1 << "; h2-" << ilosc_h2 << "; h3-" << ilosc_h3 << "; h4-" << ilosc_h4 << "; h5-"
        << ilosc_h5 << "; h6-" << ilosc_h6 << ";" << endl;

    }
    else if(typ==2)
    {
        sStream
        << "tylko w sekcji body:"   << ilosc_tylkoBody      << endl;
    }

    wynik = sStream.str();
    return wynik;

    // notatki
    /*
    	-------WYNIK NR 1 SERP ZAWIERA-------
FRAZĘ WYSZUKIWANIA JEST ZAWARTA W:
całości:n | tylko <body>: | słowach kluczowych:n | opis:n |
link:n | nagłówki: h1-n,h2-n,h3-n,h4-n,h5-n,h6-n |

ILOŚĆ SŁÓW KLUCZOWYCH(nr_slow_klucz.) MOŻNA ZNALEŹĆ:
całość:n | tylko <body>:n | opis:n | link:n |
nagłówki: h1-n,h2-n,h3-n,h4-n,h5-n,h6-n |

ILE RAZY CZESCI LINKU ZNAJDUJĄ SIĘ W:
całości:n | tylko <body>: | słowach kluczowych:n | opis:n |
nagłówki: h1-n,h2-n,h3-n,h4-n,h5-n,h6-n |
    */
}

int ilosc_frazy_w_fragmencie(string fragmentTekstuDoPrzeszukania, string jakiTekstLiczyc)
{
    size_t pozycja;
    int iloscZnalezionejFrazy = 0;
    fragmentTekstuDoPrzeszukania = toLowerString(fragmentTekstuDoPrzeszukania);
    jakiTekstLiczyc = toLowerString(jakiTekstLiczyc);
    pozycja = fragmentTekstuDoPrzeszukania.find(jakiTekstLiczyc);

    while (pozycja != string::npos)
    {
        iloscZnalezionejFrazy++;
        pozycja = fragmentTekstuDoPrzeszukania.find(jakiTekstLiczyc, pozycja+1);
    }

    return iloscZnalezionejFrazy;
}

string toLowerString(string stringToTransform)
{
    for (int i=0;i<=stringToTransform.length();i++)
    {
        stringToTransform[i] = tolower(stringToTransform[i]);
    }
    return stringToTransform;
}

string wypiszZawartoscArgumentuzZnacznika(string znacznikCalosc, string argument)
{
    size_t pozycja=0;
    string wynik;

    if(znacznikCalosc.find(argument)!=string::npos) pozycja=znacznikCalosc.find(argument);
    else return "Błąd: Znacznik nie posiada wymaganego argumentu.";
    if(znacznikCalosc.find('\"',pozycja)!=string::npos)pozycja=znacznikCalosc.find('\"',pozycja);
    else return "Błąd: Znacznik nie poziada zawartości";
    wynik = znacznikCalosc.substr(pozycja+1, znacznikCalosc.substr(pozycja+1).find('\"'));
    if(wynik=="") wynik = "I: Autor zostawił pusty opis (content=\"\").";

    return wynik;
}

//WYKLUCZAM "SŁOWA", KTÓRE ZAWIERAJĄ  1-2 ZNAKI
string wyjmijSlowo_o_numerze(string tekstDoPrzeszukania, int ktoreSlowo)
{

    //char znakiSpecjalne[30] = {' ', '~', '`', '!', '@', '#', '%', '^', '&', '*', '(', ')', '_', '+', '=', '{', '}', '[', ']', ':', ';', '\"', '\'', '<', ',', '>', '.', '/', '?', '\\'};
    int iloscZnakiSpecjalne=0;
    //int arraySize = sizeof(znakiSpecjalne)/sizeof(znakiSpecjalne[0]);
    int iloscSlow=0;

    size_t pozycja=0, pozycja2=0;
    char przerywnik=' ';
    bool pierwszeSlowo=false;
    string slowo;
    stringstream stream;

    if(tekstDoPrzeszukania=="")return"";
    for(int i=0;i<tekstDoPrzeszukania.length();i++)
    {
        if(tekstDoPrzeszukania[i]!=przerywnik)pierwszeSlowo=true;
        if(pierwszeSlowo==true)stream<<tekstDoPrzeszukania[i];
        if(((tekstDoPrzeszukania[i]==przerywnik) || (i==(tekstDoPrzeszukania.length()-1))) && (pierwszeSlowo==true))
        {
            slowo=stream.str();
            if(i!=(tekstDoPrzeszukania.length()-1))slowo.erase(slowo.length()-1,1);

            if(slowo.length()>2)
            {
                iloscSlow++;
                if(iloscSlow==ktoreSlowo) return slowo;
            }
            stream.str("");
        }
    }
    if(iloscSlow==0)return "";

    slowo=stream.str();
    stream.str("");
    return "";

}


int iloscSlowWiekszychNizDwieLiterki (string tekstDoPrzeszukania)
{

    int iloscSlow=0;

    //size_t pozycja=0, pozycja2=0;
    char przerywnik=' ';
    bool pierwszeSlowo=false;
    string slowo;
    stringstream stream;

    //if(tekstDoPrzeszukania=="")return"";
    for(int i=0;i<tekstDoPrzeszukania.length();i++)
    {
        if(tekstDoPrzeszukania[i]!=przerywnik)pierwszeSlowo=true;
        if(pierwszeSlowo==true)stream<<tekstDoPrzeszukania[i];
        if(((tekstDoPrzeszukania[i]==przerywnik) || (i==(tekstDoPrzeszukania.length()-1))) && (pierwszeSlowo==true))
        {
            slowo=stream.str();
            if(i!=(tekstDoPrzeszukania.length()-1))slowo.erase(slowo.length()-1,1);

            if(slowo.length()>2)
            {
                iloscSlow++;
            }
            stream.str("");
        }
    }
    //if(iloscSlow==0)return "";

    slowo=stream.str();
    stream.str("");
    return iloscSlow;
}

