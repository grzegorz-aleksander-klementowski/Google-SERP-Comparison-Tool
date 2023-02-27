#ifndef PODSUMOWANIEWYNIKóWSERP_H_INCLUDED
#define PODSUMOWANIEWYNIKóWSERP_H_INCLUDED

void przygDoPorowStronSERP(string plikSERP);
void pobieranieStronHTMLzSERP();
void proceduraWpisaniaZnakuTakLubNie();
void proceduraWypisywaniaPodsumowaniaSERP(string frazaGlownaSERP);
void proceduraWypisywaniaStrumieniowego(string text);
void proceduraZamianyPlikuPrezentujacyDaneNaCSV();
void procesWykonywaniaNowejAnalizySERP(bool czyWykonacNowaAnalizeSERP);
char wypisujeZnakTakLubNie();
int ilosc_frazy_w_pliku(string fraza, string sciezkaDoPliku); //(PRZY OTWARTYM PLIKU!)wyciąga do pliku txt najważniejsze elementy SEO z pliku HTML
int ile_plikow_html();
int ile_slow_kluczy(string slowaKlucze);
int ilosc_frazy_w_fragmencie(string fragmentTekstuDoPrzeszukania, string jakiTekstLiczyc);
int iloscSlowWiekszychNizDwieLiterki (string tekstDoPrzeszukania); //liczy ilosc słów z tekstu, które posiadają więcej niż dwie literki.
bool czyTakLubNie(char odpowiedz='n');
string znajdzWypiszFrazeMeta(string fraza, string sciezkaDoPliku);
string podsumowanieWynikowSERP(string frazaGlowna, int nr_PlikuDoAnalizy);
string wypiszSlowoKlucz(string lancuchSlowKluczy, int nrSlowaKlucz);
string wypiszCialoStrony(string sciezkaDoPliku);
string wypiszZawartoscNaglowka(int nrNaglowka, string cialoStronyDoPrzeszukania, int nrZnalezionegoNaglowka, int iloscNaglowkow);
string wypiszLinkzPlikuPrzeanalizowanychSERP(int numerPliku);
string wypiszCzesciLinku(int nrWynikuSERP, int nr_warstwyLinku);
string wypiszObliczeniaPodsumowania
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
string toLowerString(string stringToTransform);
string wypiszZawartoscArgumentuzZnacznika(string znacznikCalosc, string argument);
string wyjmijSlowo_o_numerze(string tekstDoPrzeszukania, int ktoreSlowo); //wyjmuje słowo o numerze bez podliczania wyrazów jedno i dwu literowych



extern std::string frazaGoogleSERP;



#endif // PODSUMOWANIEWYNIKóWSERP_H_INCLUDED
