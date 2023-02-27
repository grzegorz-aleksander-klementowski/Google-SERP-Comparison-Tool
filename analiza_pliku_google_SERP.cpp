#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#include "analiza_pliku_google_SERP.h"


using namespace std;


string introText()
{
    string opis = "Jest to program napisany jako aspekt inżynierski dla Wyższej Szkoły Informatyki i Zarządzania COPERNICUS we Wrocławiu. \n\nProgram ma na celu porównanie stron internetowychm, ich słów kluczowych, tytułów jak i również opisów. Program samodzielnie wyszuka strony internetowe po wpisaniu danej frazy i porówna strony internetowe, których adresy znalazły się na pierwszej stronie wyszukiwarki po wprowadzeniu frazy.\n\n";
    return opis;
}

string frazaGoogle()
    {
        const int maxFrazaChar = 70;
        const int minFrazaChar = 0;
        bool czyNiedozwolonyZnak=true;
        bool czyZaDługie;
        bool czyZaKrotkie;
        string fraza;

        cout << "Wpisz daną frazę dla wyszukiwarki: ";
        getline(cin, fraza);


        while((fraza.size() > maxFrazaChar) || (fraza.size() <= minFrazaChar) || (czyNiedozwolonyZnak == true))
        {

            if(fraza.size() > maxFrazaChar)
            {
                cout << "Fraza jest za długa! "; cout << "Wpisz ponownie frazę: "; getline(cin, fraza);
            }
            if(fraza.size() <= minFrazaChar)
            {
                cout << "Nie wpisałeś frazy! "; cout << "Wpisz ponownie frazę: "; getline(cin, fraza);
            }

            czyNiedozwolonyZnak=false;



            for(int i=0;i<=fraza.length();i++)
            {
                if(fraza[i]=='^')
                {
                    cout << "Wykryto niedozwolony znak(^)! " << endl;
                    czyNiedozwolonyZnak = true;
                    cout << "Wpisz ponownie frazę: "; getline(cin, fraza);
                }
            }

        }

        return fraza;
    }

string linkDoGoogleSERP(string wpisanaFraza)
{

    string fraza, przedrostekLinkGoogle="https://www.google.com/search?q=", calyLinkGoogle, komenda;

    fraza = wpisanaFraza;

    //szukanie spacji w  frazie
    for (int i = 0; i <= fraza.length(); i++)
    {
        if(fraza[i] == ' '){

        fraza[i] = '+';
        }
    }

    calyLinkGoogle = przedrostekLinkGoogle + fraza;
    //cout << "CAŁY LINK GOOGLE: " << calyLinkGoogle << endl;
    return calyLinkGoogle;


}

void pobierzStroneWWW(string link, string celDolcelowyPobrania, string nazwijPobranaStroneWWW)
{

    string curl_argumenty=" -L -H \"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:44.0) Gecko/20100101 Firefox/44.0\" ";
    string komenda = "curl " + curl_argumenty + link + " > " + celDolcelowyPobrania + nazwijPobranaStroneWWW;

    celDolcelowyPobrania = "mkdir -p "+ celDolcelowyPobrania;
    char folderDocelowy[celDolcelowyPobrania.length()];
    for(int i=0; i<=celDolcelowyPobrania.length(); i++)
    {
        folderDocelowy[i]=celDolcelowyPobrania[i];
    }
    system(folderDocelowy); //jeśli nie  ma folderu, to  zostanie stworzony.

    char komendaChar[komenda.length()];
    for (int i = 0; i <= komenda.length(); i++)
    {
        komendaChar[i] = komenda[i];
    }
    cout << endl << endl<< endl;

    system(komendaChar);
    system("clear");


}

string analizaPlikuHTML(string sciezka)
{
    fstream plik;
    plik.open(sciezka, ios::in);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje!" << endl;
        exit(0);
    }

    string linia;
    int nr_linii = 1;

    int count = 0;
    string textHTML;
    string opisSERP;

    int numWynikuSERP = 1;
    bool czyToWszystkieWynikiGoogleMaps = false;
    size_t nPos;
    size_t nPos1;
    size_t nPos2;
    string sprawdzanyLancuch;
    string SERPgoogleMaps = "<span><h3", SERPgoogle = "<h3";
    stringstream wynikSERPstream;
    string wynikSERP;


    int mainSERPnumber = 0;
    int mapSERPnumber = 0;
    int typWyniku;
    int newSERPnumber;

    wynikSERPstream<<"WYNIKI GOOGLE SERP:" << endl << endl;
    //Analiza pliku HTML
    while(getline(plik, linia))
    {

        if (linia.find("403. That’s an error.") != std::string::npos)
        {
            wykrytoBlad("403. That’s an error.", "Znaleziono błąd 403. Oznacza to, że proawdopodobnie Google zablokowało pobieranie SERP z powodu polityki firmy");

            plik.close();
            exit(0);
        }
        if (linia.find("400. That’s an error.") != std::string::npos)
        {
            wykrytoBlad("400. That’s an error.", "Znaleziono błąd 400. Serwer nie może przetworzyć żądania, ponieważ jest zniekształcone. Nie należy próbować ponownie.");

            plik.close();
            exit(0);
        }
        if (linia.find("302 Moved") != std::string::npos)
        {
            wykrytoBlad("302 Moved", "Znaleziono błąd 302. Dokument został przeniesiony.");

            plik.close();
            exit(0);
        }else{}

        if (linia.find(SERPgoogle) != std::string::npos)
        {

            nPos = linia.find(SERPgoogle); // first occurrence
            count = 1;

                while(nPos != string::npos)
                {cout<<"Test 3 pass"<<endl;
                    count++;
                    typWyniku = jakiTypWynikuSERP(linia,nPos);
                    if(typWyniku==1)
                    {
                        mapSERPnumber++;
                        newSERPnumber = mapSERPnumber;
                    }
                    else if(typWyniku == 2)
                    {cout<<"Test 3-2 pass"<<endl;
                        //nic nie rór
                    }
                    else if(typWyniku == 3)
                    {cout<<"Test 3-2 pass"<<endl;
                        //nic nie rób
                    }
                    else
                    {
                        mainSERPnumber++;
                        newSERPnumber = mainSERPnumber;
                    }
                    wynikSERPstream << wypiszNaglowekWynikuSERP(nPos, linia, newSERPnumber, SERPgoogle, SERPgoogleMaps) << endl;

                    nPos = linia.find(SERPgoogle, nPos + 1);
                }
        }
        else nr_linii++;cout<<"Test 5 pass"<<endl;
    }cout<<"Test 6 pass"<<endl;
    wynikSERPstream << endl << "Wszystkich wyników: " << mainSERPnumber << endl;
    wynikSERP = wynikSERPstream.str();
    cout<<"Test 7 pass"<<endl;
    plik.close();
    cout<<"Test 8 pass"<<endl;
    system("clear");
    return wynikSERP;

}

void wykrytoBlad(string blad, string opis)
{
    cout << "Wykryto błąd!" << endl << "Bląd: " << blad << endl << opis << endl << endl;
    exit(0);
}

string wypiszNaglowekWynikuSERP(size_t pozycja, string linia, int numerSERP, string znacznikGoogleSERP, string znacznikGoogleMapsSERP)
{cout<<"Test 3-5-1 pass"<<endl;
    int typWynnikuSERP = jakiTypWynikuSERP(linia, pozycja);
    int iloscZnakowDoFrazy = 60;
    size_t nPos = pozycja+iloscZnakowDoFrazy;
    string textHTML = linia.substr(nPos, 200);
    size_t nPos2 = textHTML.find("</");
    textHTML = linia.substr(nPos, nPos2);
    stringstream textNaglowekSERPstream;
    string textNaglowekSERP;
    string textHTML_link;
    string textHTML_link_2;
    string link;
cout<<"Test 3-5-2 pass"<<endl;
    if(typWynnikuSERP==1)
    {cout<<"Test 3-5-3 pass"<<endl;
        if(numerSERP==1)
        {cout<<"Test 3-5-3-1 pass"<<endl;
            textNaglowekSERPstream << "------Wyniki z Google maps------\n" << numerSERP << ".: "<< "Wyniki z Google maps: " << textHTML;
        }
        else if(numerSERP==3)
        {cout<<"Test 3-5-3-2 pass"<<endl;
            textNaglowekSERPstream << numerSERP << ".: "<< "Wyniki z Google maps: " << textHTML << "\n--------------------------------";
        }
        else
        {cout<<"Test 3-5-3-3 pass"<<endl;
            textNaglowekSERPstream << numerSERP << ".: "<< "Wyniki z Google maps: " << textHTML;
        }
cout<<"Test 3-5-4 pass"<<endl;
        textNaglowekSERP = textNaglowekSERPstream.str();
        return(textNaglowekSERP);

    }

    if(typWynnikuSERP==2)
    {cout<<"Test 3-5-6 pass"<<endl;
        textNaglowekSERPstream << "----Informacja z Wikipedii----\n Wynik z Wikipedii: " << textHTML << "\n------------------------------";
        textNaglowekSERP = textNaglowekSERPstream.str();
        return(textNaglowekSERP);
    }
    if(typWynnikuSERP==3)
    {cout<<"Test 3-5-7 pass"<<endl;
        textNaglowekSERPstream << "-----Informacja-----\n Wynik: " << textHTML << "\n--------------------";
        textNaglowekSERP = textNaglowekSERPstream.str();
        return(textNaglowekSERP);
    }
    else
    {cout<<"Test 3-5-8 pass"<<endl;
        if(numerSERP<10)
        {
            textNaglowekSERPstream << "Wynik [0" << numerSERP << "]: " << textHTML << endl;cout<<"Test 3-8-8-1 pass"<<endl;
        }
        else
        {
            textNaglowekSERPstream << "Wynik [" << numerSERP << "]: " << textHTML << endl;
        }

        textNaglowekSERPstream << "OPIS STRONY: " << endl << wypiszWarstwyStrony(pozycja, linia) << endl;cout<<"Test 3-8-8-3 pass"<<endl;
        link = wypiszLink(pozycja, linia);cout<<"Test 3-8-8-4 pass"<<endl;
        textNaglowekSERPstream << "WARSTWY STRONY: "<< endl << wypiszWarstwyStronyPoprawione(link);cout<<"Test 3-8-8-5 pass"<<endl;

        textNaglowekSERPstream << "LINK: " << link << endl;cout<<"Test 3-8-8-6 pass"<<endl;
        textNaglowekSERPstream << "--------------------------------";
        cout<<"Test 3-8-8-7 pass"<<endl;
        textNaglowekSERP = textNaglowekSERPstream.str();cout<<"Test 3-5-9 pass"<<endl;
        return(textNaglowekSERP);
    }
    cout<<"Test 3-8-10 pass"<<endl;
}
string wypiszLink(size_t pozycja, string linia)
{
    cout<<"Test 3-8-8-3-1 pass"<<endl;
    size_t nPos;
    string textHTML_link;
    size_t nPos2;
    string textHTML_link_2;
    string wynik="Błąd z czytaniem linku";

    cout<<"Test 3-8-8-3-2 pass"<<endl;
    nPos = pozycja;
    int potencjalnaDlugoscLiku=3;
    cout<<"Test 3-8-8-3-3 pass"<<endl;
    while(((linia.substr(pozycja-potencjalnaDlugoscLiku,8)).find("https://") == string::npos) && (potencjalnaDlugoscLiku<=pozycja))
    {
        potencjalnaDlugoscLiku++;
    }
    cout<<"ZNALAZŁEM! find(\"https:)"<<endl;
    cout<<"pozycja: "<<pozycja<<endl;
    cout<<"potencjalnaDlugoscLiku: "<<potencjalnaDlugoscLiku<<endl;
    cout<<"pozycja-potencjalnaDlugoscLiku: "<<pozycja-potencjalnaDlugoscLiku<<endl;
    cout<<"Test 3-8-8-3-3-1 pass"<<endl;
    if(pozycja>=potencjalnaDlugoscLiku)
    {
        textHTML_link = linia.substr(nPos-potencjalnaDlugoscLiku,potencjalnaDlugoscLiku);



        //textHTML_link = linia.substr(nPos-350,350);
        cout<<"Test 3-8-8-3-4 pass"<<endl;
        //textHTML_link = linia.substr(nPos-250, 250);

        if(textHTML_link.find("https://") != string::npos)
        {
            nPos = textHTML_link.find("https://");

            cout<<"Test 3-8-8-3-5 pass"<<endl;
            if(nPos > potencjalnaDlugoscLiku)
            {cout<<"Test 3-8-8-3-6 pass"<<endl;
                nPos = textHTML_link.find("http://");cout<<"Test 3-8-8-3-7 pass"<<endl;
            }
            if(textHTML_link.find("&amp");cout<<"Test 3-8-8-3-8 pass")
            {
                nPos2= textHTML_link.find("&amp");cout<<"Test 3-8-8-3-8 pass"<<endl;
                textHTML_link_2 = textHTML_link.substr(nPos, nPos2);cout<<"Test 3-8-8-3-9 pass"<<endl;
                nPos2= textHTML_link_2.find("&amp");cout<<"Test 3-8-8-3-10 pass"<<endl;
                textHTML_link_2 = textHTML_link.substr(nPos, nPos2);cout<<"Test 3-8-8-3-11 pass"<<endl;
                if((textHTML_link_2[textHTML_link_2.length()-1])=='>')
                {cout<<"Test 3-8-8-3-12 pass"<<endl;
                    nPos2= textHTML_link_2.find("&amp");
                    textHTML_link_2 = textHTML_link.substr(nPos, nPos2);
                    cout<<"Test 3-8-8-3-13 pass"<<endl;
                    wynik = textHTML_link_2;
                }
                cout<<"Test 3-8-8-3-14 pass"<<endl;
            }
            else
            {
                wynik = "Błąd! Link jest zepsuty";
            cout << wynik;
            exit(0);
            }
        }
/*
        else
        {
            wynik = "Nie znaleziono linku!";
            cout << wynik;
            //exit(0);
        }
*/
    }
    else
    {
        cout<<"Pozycja jest na krótka! "<<pozycja<<endl;
        wynik = "Pozycja jest na krótka! \n";
    }


    return(wynik);

}

string wypiszWarstwyStrony(size_t pozycja2, string linia)
{
    string strona[10];
    int iloscZnakowDoFrazy = 60;
    size_t nPos = pozycja2+iloscZnakowDoFrazy;
    string textHTML = linia.substr(nPos, 400);
    size_t nPos2 = textHTML.find("</");
    size_t nPos3 = nPos+nPos2+44;
    textHTML = linia.substr(nPos3, 1200);

    string opisWynikuSERP = textHTML;

    size_t nPos4 = textHTML.find("</");
    size_t nPosPoczOpisu;
    size_t nPosKoniecOpisu;
    opisWynikuSERP  = opisWynikuSERP.substr(nPos4+83, 300);
    nPosPoczOpisu   = opisWynikuSERP.find('>');
    while((opisWynikuSERP.substr(nPosPoczOpisu,2)[1])=='<')
    {
        opisWynikuSERP  = opisWynikuSERP.substr(nPosPoczOpisu+1, 300);
        nPosPoczOpisu   = opisWynikuSERP.find('>');
        opisWynikuSERP  = opisWynikuSERP.substr(nPosPoczOpisu+1, 300);

    }
    if(((opisWynikuSERP.substr(0,5))=="<span"))
        {
            if(opisWynikuSERP.find(" · </span>") < 150)
            {
                nPosPoczOpisu = opisWynikuSERP.find(" · </span>");
                opisWynikuSERP = opisWynikuSERP.substr(nPosPoczOpisu+11);
                nPosKoniecOpisu = opisWynikuSERP.find("</div>");
                opisWynikuSERP = opisWynikuSERP.substr(0, nPosKoniecOpisu);
            }
            else
            {
                opisWynikuSERP = textHTML;
                nPosPoczOpisu = opisWynikuSERP.find("</span></div></div><div><div class=\"BNeawe s3v9rd AP7Wnd\">");
                opisWynikuSERP = opisWynikuSERP.substr(nPosPoczOpisu+58);
                nPosKoniecOpisu = opisWynikuSERP.find("</div>");
                opisWynikuSERP = opisWynikuSERP.substr(0,nPosKoniecOpisu);
            }
        }
        else
        {
            nPosKoniecOpisu = opisWynikuSERP.find("</div");
            opisWynikuSERP = opisWynikuSERP.substr(0,nPosKoniecOpisu);
            if(opisWynikuSERP=="")
            {
                 opisWynikuSERP = textHTML;
            }
            if(opisWynikuSERP.substr(0,4)=="<div")
            {
                opisWynikuSERP = textHTML;
                nPosPoczOpisu = opisWynikuSERP.find(" · </span>");
                opisWynikuSERP = opisWynikuSERP.substr(nPosPoczOpisu+11);
                nPosKoniecOpisu = opisWynikuSERP.find("<");
                opisWynikuSERP = opisWynikuSERP.substr(0, nPosKoniecOpisu);
            }
        }



    textHTML = linia.substr(nPos3, nPos4);
    size_t nPos5 = 0;
    size_t nPos6 = textHTML.find(" › ");
    string opisSERP;
    string textHTMLnext = textHTML;
    int numerStrony = 0;
    stringstream warstwyStronSERPstream;

    if(nPos6 > nPos4)
    {
        strona[numerStrony] = textHTML.substr(nPos5,nPos6);
        opisSERP = "całość: " + textHTML + "\nStrona Główna: " + strona[numerStrony] + "\n (bez podstron)";
    }
    else
    {
        strona[numerStrony] = textHTMLnext.substr(nPos5,nPos6);
        warstwyStronSERPstream << "całość: " << textHTML << endl << numerStrony << ". Strona Główna: " << strona[numerStrony] << "\n";
        opisSERP = warstwyStronSERPstream.str();


        while(nPos6 < nPos4)
        {
            numerStrony++;

            textHTMLnext = textHTMLnext.substr(nPos6+5, 100);
            nPos6 = textHTMLnext.find(" › ");
            strona[numerStrony] = textHTMLnext.substr(0, nPos6);
            warstwyStronSERPstream << numerStrony << ". Podstrona: " << strona[numerStrony] << "\n";
            opisSERP = warstwyStronSERPstream.str();
        }

    }

    //return opisSERP;
    return opisWynikuSERP;

}

string wypiszWarstwyStronyPoprawione(string link)
{
    size_t nPos;
    size_t nPos2;
    size_t koniecPodstrony;
    int numerStrony=0;
    bool koniecLinku = false;
    string warstwyStrony[10];
    stringstream wynikWarstwyStronyStream;
    string wynikWarstwyStrony;

    if(link.substr(0,5) == "https") nPos = 8;
    else if(link.substr(0,4) == "http") nPos = 7;
    else nPos = 0;

    link = link.substr(nPos,350);
    nPos2 = link.find('/');
    warstwyStrony[numerStrony] = link.substr(0,nPos2);
    wynikWarstwyStronyStream << "strona " << numerStrony << ".: " << warstwyStrony[numerStrony] << endl;


    while(koniecLinku == false)
    {
        numerStrony++;

        nPos = nPos2+1;
        link = link.substr(nPos,350);
        nPos2 = link.find('/');
        if(nPos2>350)
        {
            nPos2=350;
            //link = link.substr(nPos,350);
            koniecLinku = true;
        }
        warstwyStrony[numerStrony] = link.substr(0,nPos2);
        if(warstwyStrony[numerStrony]=="")
        {
            //wynikWarstwyStronyStream << "COŚ TU NIE GRA! strona " << numerStrony << ".: " << warstwyStrony[numerStrony] << endl;
        }
        else wynikWarstwyStronyStream << "strona " << numerStrony << ".: " << warstwyStrony[numerStrony] << endl;

    }
    wynikWarstwyStrony = wynikWarstwyStronyStream.str();
    return wynikWarstwyStrony;

}

int funkcjaNumerSERP(bool czyToMapa, int numerSERP, int numerSERPgmaps)
{
    if(czyToMapa==true)
    {
        numerSERPgmaps++;
        return numerSERPgmaps;
    }
    else
    {
        numerSERP++;
        return numerSERP;
    }
}

int jakiTypWynikuSERP(string linia, size_t pozycja)
{
    size_t nPos = pozycja;
    string sprawdzanyLancuch;
    string znacznikSERP = "data-deferred=\"1\"></div><span>";
    int typeSERP;

    if(znacznikSERP=="data-deferred=\"1\"></div><span>")
    {
        sprawdzanyLancuch = linia.substr(nPos-30, 30);
        //cout << "\nEj, funkcja działa i wypadlo DWA!!! " << znacznikSERP.compare(sprawdzanyLancuch) << endl;

        if(znacznikSERP.compare(sprawdzanyLancuch)==0)
        {
            return 3;
        }
        else
        {znacznikSERP = "data-deferred=\"1\"></a></div><span>";}

    }
    if(znacznikSERP=="data-deferred=\"1\"></a></div><span>")
    {
        sprawdzanyLancuch = linia.substr(nPos-34, 34);

        if(znacznikSERP.compare(sprawdzanyLancuch)==0)
        {
            return 2;
        }
        else
        {
            znacznikSERP="<span><h3";
        }
    }

    if(znacznikSERP=="<span><h3")
    {

        sprawdzanyLancuch = linia.substr(nPos-6, 9);

        if(znacznikSERP.compare(sprawdzanyLancuch)==0)
        {
            return 1;
        }
        else
        {}
    }
    else
    {
        wykrytoBlad("Typ wyniku SERP się niezgadza.", "Coś poszło nie tak, sprawdź funkcje wykrywania typów wyniku SERP. Google mógl spowodować zmiany w kodzie, zaaktualizuj program.");
        return 0;
    }
 return 0;
}

