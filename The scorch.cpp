#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
struct gracze
{
    string imie;
    int wygrane=0;
    int przegrane=0;
};
void gra(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[]);
void czekaj(int czas);
void pisz_menu();
void zasady(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[]);
void tryb_gry(char &tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[]);
void dziala(char plansza[2][21],int &dzialo_pierwsze,int &dzialo_drugie);
void pisz_plansze(char plansza[2][21]);
void wiatry(char wiatr[2]);
void bot(int &moc,int &kat);
void czy_dobra_wartosc(int &moc,int &kat);
bool czy_trafil(int tryb,int tura,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[]);
void imiona(char imie_gracza1[],char imie_gracza2[],char tryb);
void data(char godzina[]);
void Scorch(char imie_gracza1[],char imie_gracza2[],char wiatr[],int dzialo_pierwsze,int dzialo_drugie,bool trafienie,int tura);
void rozgrywka(int &nr_rozgrywki);
void analiza(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[]);
int ilos_gier(gracze gracze[],int ile, int i);
double ilosc_strzalow(gracze gracze[],int i,int buf[]);
void wygrane_przegrane(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[]);
void czas_strzalu(gracze gracze[],int i,int &k,char godziny[]);
void pisz_rozgrywke();
void wznow(int &dzialo_pierwsze,int &dzialo_drugie,char wiatr[],char plansza[2][21]);
void skutecznosc(int i,gracze gracze[],int buf[]);
int main()
{
    srand(time(NULL));
    char tryb;
    int dzialo_pierwsze,dzialo_drugie;
    char imie_gracza1[20];
    char imie_gracza2[20]="Komputer";
    char wiatr[2];
    char  plansza[2][21]=                                                     //Inicjalizacja tablicy
    {

        {'_','_','_','_','_','_','_','_','_','_','|','_','_','_','_','_','_','_','_','_','_',},
        {'A','B','C','D','E','F','G','H','I','J',' ','K','L','M','N','O','P','Q','R','S','T'}
    };
    gra(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
    return 0;
}
void czekaj(int czas)
{
    time_t ile = time(0);
    while ((time(0) - ile) < czas);
}



void pisz_menu()
{
    cout<<setw(50)<<"WITAJ W WALCE NA DZIALA"<<endl;
    cout<<"Wybierz tryb gry: "<<endl;
    cout<<"1-Gra dla jednego gracza"<<endl;   //menu glowne
    cout<<"2-Gra dla dwoch gracza"<<endl;
    cout<<"3-Wznowienie rozgrywki z dowolnego momentu"<<endl;
    cout<<"4-Zasady gry"<<endl;
    cout<<"5-Analiza wygranych komputera i graczy"<<endl;
    cout<<"6-Statystyki wybranego gracza"<<endl;
    cout<<"7-Wyjscie z programu"<<endl;
}


void zasady(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[])
{
    cout << "1. Gra polega na wyeliminowaniu dziala przeciwnika" << endl;
    cout << "2. W grze bierze udzial 2 graczy lub 1 gracz + komputer." << endl;
    cout << "3. Gra rozgrywana jest na planszy o dlugosci 20 znakow podzielonej na pol" << endl;
    cout << "4. Kazde pole ma przypisane oznaczenie A-T" << endl;
    cout << "5.Polozenie dziala(zajmujacego 1 pole) kazdego z graczy jest losowane na poczatku rozgrywki"<<endl;
    cout<< " w przedzialach A-J dla gracza pierwszego i K-T dla gracza drugiego" << endl;
    cout << "6.Rozgrywka sklada sie z dwoch faz, w ktorych kolejno gracze podaja wartosc predkosci (0%-100%)"<<endl;
    cout<<"i kat jego wystrzelenia (0-90)" << endl;
    cout << "7.W kazdej rundzie jest wyznaczany wiatr, losowy parametr okreslajacy o ile pol zmieniona bedzie trajektoria strzalu."<<endl;
    cout<<"Wiatr moze wiac w lewo lub prawo" << endl;
    cout << "8. Gra konczy sie w momencie zniszczenia przeciwnika" << endl;
    system("pause");
    system("cls");
    gra(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
}


void tryb_gry(char &tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[])
{
    cin>>tryb;

    if(tryb=='1')
        cout<<"Rozpoczynamy przygode dla jednego gracza"<<endl<<endl;                           //tryb albo Ty+bot albo Ty+druga osoba, zawsze grasz jakos gracz pierwszy
    else if(tryb=='2')
        cout<<"Rozpoczynamy przygode dla dwoch graczy"<<endl<<endl;
    else if(tryb=='3');
    else if(tryb=='4')
        zasady(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
    else if(tryb=='5')
    {
        analiza(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
    }

    else if(tryb=='6')
    {
        wygrane_przegrane(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
    }
    else if(tryb=='7')
    {
        cout<<"KONCZYMY!"<<endl;
        exit(0);
    }
    else
    {
        cout<<"Wybrano zly przycisk. Prosze wybrac ponownie lub wyjsc"<<endl;
        cin.clear();
        cin.sync();
        tryb_gry(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
    }
}


void dziala(char plansza[2][21],int &dzialo_pierwsze,int &dzialo_drugie)
{
    dzialo_pierwsze=rand()%10;
    dzialo_drugie=(rand()%10)+11;
    plansza[0][dzialo_pierwsze]='X';
    plansza[0][dzialo_drugie]='X';
    cout<<"Gracz pierwszy wylosowal dzialo na pozycji "<<plansza[1][dzialo_pierwsze]<<endl;
    cout<<"Gracz drugi wylosowal dzialo na pozycji "<<plansza[1][dzialo_drugie]<<endl<<endl<<endl;      //losowanie pozycji dzial graczy

}


void pisz_plansze(char plansza[2][21])
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<21; j++)             //wypisywanie tablicy
            cout<<plansza[i][j];
        cout<<endl;
    }

}


void wiatry(char wiatr[2])
{
    wiatr[0]=(rand()%5);
    int a=(rand()%2);                                //losowanie wiatru
    if(a==0)
        wiatr[1]='L';
    else
        wiatr[1]='P';

}


void bot(int &moc,int &kat)
{
    //bot kiedy gram z botem a human jak graja dwaj ludzie
    moc=rand()%100;
    kat=rand()%90;
}


void human(int &moc,int &kat)            //wpisywanie parametrow strzalu
{
    cout<<"moc [0%-100%]: ";
    while(!(cin>>moc))
    {
        cin.clear();
        cin.sync();
        cout<<"Podales litere! Nie probuj oszukac programu"<<endl;
    }
    cout<<endl;
    cout<<"kat [0-90]: ";
    while(!(cin>>kat))
    {
        cin.clear();
        cin.sync();
        cout<<"Podales litere! Nie probuj oszukac programu"<<endl;
    }
    cout<<endl;
}


void czy_dobra_wartosc(int &moc,int &kat)              //sprawdzanie czy nie wpisano wartosci ze zlego przedzialu
{
    while(moc<0 or moc>100 or kat<0 or kat>90)
    {
        if(moc<0 or moc>100)
        {
            cout<<"Zla wartosc sily!"<<endl;
            cout<<"Podaj ja ponownie"<<endl;
            cout<<"moc [0%-100%]: ";
            while(!(cin>>moc))
            {
                cin.clear();
                cin.sync();
                cout<<"Podales litere! Nie probuj oszukac programu"<<endl;
            }
            cout<<endl;

        }
        if(kat<0 or kat>90)
        {
            cout<<"Zla wartosc kata!"<<endl;
            cout<<"Podaj ja ponownie"<<endl;
            cout<<"kat [0-90]: ";
            while(!(cin>>kat))
            {
                cin.clear();
                cin.sync();
                cout<<"Podales litere! Nie probuj oszukac programu"<<endl;
            }
            cout<<endl;
        }
    }
}


bool czy_trafil(int tryb,int tura,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[]) //sprawdzanie trafienia na podstawie tryby gry i algorytmu trafienia
{
    int moc,kat;
    if(tryb=='1')
    {
        if(tura%2==1)
        {
            human(moc,kat);
            czy_dobra_wartosc(moc,kat);
        }
        else
        {
            bot(moc,kat);
            czekaj(1);
            cout<<"moc [0%-100%]: "<<moc<<endl;
            czekaj(1);
            cout<<"kat [0-90]: "<<kat<<endl;
            czekaj(1);
        }
    }
    else
    {
        human(moc,kat);
        czy_dobra_wartosc(moc,kat);
    }

    int zasieg=(pow(moc,2)*sin(2*M_PI*kat/180))/10;                        //Liczenie zasiegu ze wzoru
    int roznica=dzialo_drugie-dzialo_pierwsze;                                  //roznica miedzy pozychami graczy
    if(tura%2==1)                                                               //Zaleznie od tego kto gra(ja czy przeciwnik) to wiatr roznie wplywa na nasze strzaly
    {

        if(wiatr[1]=='L')
            roznica=roznica-wiatr[0];
        else
            roznica=roznica+wiatr[0];
    }
    else
    {
        if(wiatr[1]=='L')
            roznica=roznica+wiatr[0];
        else
            roznica=roznica-wiatr[0];
    }
    if(zasieg>=roznica*10 && zasieg<=roznica*10+50)
    {
        czekaj(1);
        cout<<"Trafiony"<<endl<<endl<<endl;
        czekaj(1);
        system("cls");
        return true;
    }
    else
    {
        czekaj(1);
        cout<<"PUDLO"<<endl<<endl<<endl;
        if(tryb=='1')
        {
            if(tura%2==1)
                if(zasieg>roznica*10)
                    cout<<"Strzeliles ze daleko!"<<endl;
                else
                    cout<<"Strzeliles za blisko!"<<endl;
        }
        else
        {
            if(zasieg>roznica*10)
                cout<<"Strzeliles ze daleko!"<<endl;
            else
                cout<<"Strzeliles za blisko!"<<endl;
        }
        czekaj(1);
        system("cls");
        return false;
    }
}


void gra(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[]) //glowna funkcja gry
{
    bool prawda=false;
    pisz_menu();
    tryb_gry(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
    if(tryb=='3')
    {
        wznow(dzialo_pierwsze,dzialo_drugie,wiatr,plansza);                  //jak kontynuacja gry to wywoluje inna funkcje
    }
    else
    {
        dziala(plansza,dzialo_pierwsze,dzialo_drugie);
    }
    imiona(imie_gracza1,imie_gracza2,tryb);
    int tura=1;
    pisz_rozgrywke();
    pisz_plansze(plansza);

    while(1)                                                  //zliczanie trafien, 3 trafienia zeby wygrac
    {
        if(!(tryb=='3' and tura==1))
        {
            if(tura%2==1)                                 //wiatr zmienia sie po strzale obu graczy, czyli co druga ture
            {

                wiatry(wiatr);
            }
        }
        if(tryb=='3')
        {
            cout<<"ZMIENIAM PRAWDE"<<endl;
            tryb='1';
            prawda=true;
        }
        if(tryb=='1')
        {
            if(tura%2==1)
            {
                cout<<"TURA GRACZA "<<imie_gracza1<<endl<<endl;
            }
            else
            {
                cout<<"TURA KOMPUTERA"<<endl<<endl;
            }
        }
        else
        {
            if(tura%2==1)
            {
                cout<<"TURA GRACZA "<<imie_gracza1<<endl<<endl;
            }
            else
            {
                cout<<"TURA GRACZA "<<imie_gracza2<<endl<<endl;
            }
        }
        cout<<imie_gracza1<<setw(20)<<imie_gracza2<<endl<<endl;                             //problem z konwersja strina na inta i wlasciwym jego wypisaniem
        if( (tura==1 || tura==2) && prawda==true )
        {

            cout<<"Wiatr: "<<wiatr[0]<<wiatr[1]<<endl;
        }
        else
        {
            cout<<"Wiatr: "<<(int)wiatr[0]<<wiatr[1]<<endl;
        }
        if(tura%2==1)
            cout<<endl;
        cout<<endl;
        bool trafienie=czy_trafil(tryb,tura,plansza,dzialo_pierwsze,dzialo_drugie,wiatr);                                  //zapisywanie danych do pliku
        Scorch(imie_gracza1,imie_gracza2,wiatr,dzialo_pierwsze,dzialo_drugie,trafienie,tura);
        if(trafienie)
        {
            if(tura%2==1)
            {
                cout<<"Wygral "<<imie_gracza1<<endl;
                exit(0);
            }
            else
            {
                cout<<"Wygral "<<imie_gracza2<<endl;
                exit(0);
            }
        }
        pisz_plansze(plansza);
        tura++;
    }
}


void pisz_rozgrywke()
{
    int nr_rozgrywki=0;
    fstream plik,plik1;
    rozgrywka(nr_rozgrywki);
    if (!(nr_rozgrywki==0))                    //jak pliku juz by³
    {
        plik.open("Scorch.txt",ios::out| ios::app);
        if (!plik)
        {
            cerr << "Nieudane otwarcie pliku "
                 <<plik1<< " do odczytu " << endl;
            exit(1);
        }
        plik<<"#Rozgrywka "<<nr_rozgrywki+1<<endl<<endl;
        plik.close();

    }
    else                                          //jak pliku nie bylo i to pierwsze otwarcie
    {

        plik.open("Scorch.txt",ios::out | ios::app);
        plik<<"Gra Scorch ver.1.0.Autor:Mateusz Kowalewski,grupa 1,kierunek AiR,Wydzial ETI"<<endl<<endl;
        plik<<"#Rozgrywka 1"<<endl<<endl;
        plik.close();
        nr_rozgrywki++;
    }

}


void imiona(char imie_gracza1[],char imie_gracza2[],char tryb)
{
    if(tryb=='1' or tryb=='3')
    {
        cout<<"Podaj swoje imie"<<endl;                                              //podawanie imion graczy
        cin>>imie_gracza1;
    }
    else
    {
        cout<<"Podaj imie gracza 1"<<endl;
        cin>>imie_gracza1;
        cout<<"Podaj imie gracza 2"<<endl;
        cin>>imie_gracza2;
    }
}


void Scorch(char imie_gracza1[],char imie_gracza2[],char wiatr[],int dzialo_pierwsze,int dzialo_drugie,bool trafienie,int tura)
{
    char godzina[20];                                                           //zapisywanie danych do pliku
    fstream plik;
    plik.open("Scorch.txt",ios::out | ios::app);
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(1);
    }
    data(godzina);
    if(tura%2==1)
        plik<<"#"<<godzina<<","<<imie_gracza1<<","<<dzialo_pierwsze<<","<<dzialo_drugie<<","<<(int)wiatr[0]<<","<<trafienie<<endl<<endl;
    else
        plik<<"#"<<godzina<<","<<imie_gracza2<<","<<dzialo_drugie<<","<<dzialo_pierwsze<<","<<(int)wiatr[0]<<","<<trafienie<<endl<<endl;
    plik.close();


}


void data(char godzina[])                                                 //odczytanie daty w prawidlowym formacie
{
    time_t czas;
    struct tm * data;
    time(&czas);
    data = localtime( & czas );

    strftime( godzina,30,"%Y-%m-%d.%X", data );
}


void rozgrywka(int &nr_rozgrywki)                    //znalezienie ostatniego numeru rozgrywki
{
    fstream plik;
    string napis;
    size_t cos;
    plik.open("Scorch.txt",ios::in);                               //zliczenie ile bylo rozgrywek w danym przedziale czasu
    if (!plik)
    {
        nr_rozgrywki=0;
    }
    getline(plik,napis);
    while(plik)
    {
        getline(plik,napis);
        getline(plik,napis);
        cos=napis.find("Rozgrywka");
        if(cos!=string::npos)
        {
            nr_rozgrywki++;
        }
    }
    plik.close();
}


void analiza(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[])
{
    int dlugosc_napisu,ile=0;
    int wygrane_komputera=0;
    char konwersator;
    fstream plik;
    string napis,szukana;
    size_t cos;
    plik.open("Scorch.txt",ios::in);           //otwarcie pliku
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(0);
    }
    cout<<"Z jakiego okresu chcesz zobaczyc statysyki wygranych?"<<endl;
    cout<<"Podaj date w formacie #RRRR-MM-DD.GG "<<endl;
    cout<<"Gdzie RRRR oznacza rok MM oznacza numer miesiaca DD oznacza dzien a GG oznacza godzine w formacie 24 godzinnym"<<endl;
    cin>>szukana;

    getline(plik,napis);
    getline(plik,napis);
    getline(plik,napis);
    cos=napis.find("Rozgrywka");                  //zjechanie do pierwszej rozgrywki

    if(cos!=string::npos)
    {
        while(plik)
        {

            getline(plik,napis);
            getline(plik,napis);                             //pierwszy zapis stanu gry i znalezienie własciwej daty
            cos=napis.find(szukana);
            if(cos!=string::npos)
            {

                dlugosc_napisu=napis.length();                         //sprawdzenie czy wygrał komputer
                konwersator=napis[dlugosc_napisu-1];
                cos=napis.find("Komputer");
                if(cos!=string::npos)
                {
                    if(konwersator=='1')
                    {
                        wygrane_komputera++;
                    }
                }
            }
        }
    }
    plik.close();
    plik.open("Scorch.txt",ios::in);                               //zliczenie ile bylo rozgrywek w danym przedziale czasu
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(0);
    }
    getline(plik,napis);
    while(plik)
    {
        getline(plik,napis);
        getline(plik,napis);
        cos=napis.find("Rozgrywka");
        if(cos!=string::npos)
        {
            getline(plik,napis);
            getline(plik,napis);
            cos=napis.find(szukana);
            if(cos!=string::npos)
                ile++;
        }
    }
    plik.close();
    cout<<"Ilosc wygranych komputera w podanych przedziale czasu to "<<wygrane_komputera<<endl;
    cout<<"Ilosc wygranych gracza w podanych przedziale czasu to "<<ile-wygrane_komputera<<endl;

    system("pause");
    system("cls");
    gra(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);

}


int ilos_gier(gracze gracze[],int ile, int i)
{
    int ilosc=0;
    fstream plik;
    string napis;
    size_t cos;
    plik.open("Scorch.txt",ios::in);
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(0);
    }
    getline(plik,napis);
    while(plik)
    {
        getline(plik,napis);
        getline(plik,napis);
        cos=napis.find("Rozgrywka");                  //Jak spotkal napis "Rozgrywka" to dodaje 1
        if(cos!=string::npos)
        {
            getline(plik,napis);
            getline(plik,napis);
            cos=napis.find(gracze[i].imie);
            if(cos!=string::npos)
            {
                ilosc++;
            }
        }

    }

    plik.close();

    return ilosc;

}


void wygrane_przegrane(char tryb,char plansza[2][21],int dzialo_pierwsze,int dzialo_drugie,char wiatr[],char imie_gracza1[],char imie_gracza2[])
{

    fstream plik;
    string napis;
    int zwyciestwa=0,ile=0,gry=0,wejscie=0;
    int buf[10];
    size_t cos;
    int k=0;
    char godziny[80];
    int godziny1[80];
    double srednia=0;

    cout<<"Dla ilu graczy chcesz zrobic zestawienie?"<<endl;
    cin>>ile;
    gracze gracze[ile];
    cout<<"Jakie sa ich imiona/pseudonimy? Podawaj jeden i naciskaj enter!"<<endl;           //ilosc graczy



    for(int i=0; i<ile; i++)
    {
        cin>>gracze[i].imie;
    }


    for(int i=0; i<ile; i++)
    {
        plik.open("Scorch.txt",ios::in);
        if (!plik)
        {
            cerr << "Nieudane otwarcie pliku "
                 << plik<< " do odczytu " << endl;
            exit(0);
        }
        getline(plik,napis);
        getline(plik,napis);
        getline(plik,napis);
        cos=napis.find("Rozgrywka");                                //Szukanie rozgrywki
        if(cos!=string::npos)
        {
            while(plik)
            {
                getline(plik,napis);
                getline(plik,napis);
                cos=napis.find(gracze[i].imie);                     //szukanie czy to rozgrywka tego gracza
                if(cos!=string::npos)
                {
                    if(napis[napis.length()-1]=='1')                     //sprawdzanie czy wygral
                    {
                        gracze[i].wygrane++;
                    }
                }
            }
        }
        plik.close();
    }


    for(int i=0; i<ile; i++)
    {
        gracze[i].przegrane=ilos_gier(gracze,ile,i);                                      //cale zestawienie
        cout<<"Zestawienie dla gracza "<<gracze[i].imie<<endl;
        cout<<"Srednia ilosc oddanych strzalow: "<<(ilosc_strzalow(gracze,i,buf)/gracze[i].przegrane)<<endl;
        cout<<"Maksymalna ilosc oddanych strzalow: "<<buf[gracze[i].przegrane-1]<<endl;
        cout<<"Minimalna ilosc oddanych strzalow: "<<buf[0]<<endl;
        cout<<"Przegrane: "<<abs(gracze[i].przegrane-gracze[i].wygrane)<<endl;
        cout<<"Wygrane: "<<gracze[i].wygrane<<endl;
        skutecznosc(i,gracze,buf);
        czas_strzalu(gracze,i,k,godziny);

        for(int i=0; i<k-1; i++)                                                   //srednia czas oddawania strzalu
        {

            godziny[i]=abs(godziny[i+1]-godziny[i]);
            if(godziny[i]==0)
                godziny[i]=10;
        }
        k--;
        sort( godziny, godziny + k, greater < int >() );
        for(int i=0; i<k; i++)
        {
            srednia=srednia+godziny[i];
        }
        srednia=srednia/k;

        cout<<"Sredni czas oddawania strzalu: "<<double(srednia)<<endl;
        cout<<"Minimalny czas oddawania strzalu: "<<(int)godziny[k-1]<<endl;
        cout<<"Maksymalny czas oddawania strzalu: "<<(int)godziny[0]<<endl<<endl<<endl;
        for(int i=0; i<10; i++)
            buf[i]=0;
    }
    system("pause");
    system("cls");
    gra(tryb,plansza,dzialo_pierwsze,dzialo_drugie,wiatr,imie_gracza1,imie_gracza2);
}


double ilosc_strzalow(gracze gracze[],int i,int buf[])
{
    int ilosc=0,j=-1,ilosc_razem=0;
    fstream plik;
    string napis;
    size_t cos,cos1;
    plik.open("Scorch.txt",ios::in);
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(0);
    }
    getline(plik,napis);
    getline(plik,napis);
    getline(plik,napis);
    cos=napis.find("Rozgrywka");
    if(cos!=string::npos)
    {
        while(plik)
        {
            getline(plik,napis);
            getline(plik,napis);
            cos=napis.find(gracze[i].imie);                             //szuka rozgrywki, jak znajdzie to sprawdza czy gracz sie zgadza, potem liczy strzaly
            if(cos!=string::npos)
            {
                while(plik)
                {
                    getline(plik,napis);
                    getline(plik,napis);
                    cos=napis.find("Rozgrywka");
                    if(cos!=string::npos)
                    {
                        break;                                                        //wychodzi jak znajdzie rozgrywke
                    }
                    cos1=napis.find(gracze[i].imie);
                    if(cos1!=string::npos)
                    {
                        ilosc++;
                        ilosc_razem++;
                    }

                }
                j++;
                buf[j]=ilosc+1;                                    //zapisywanie do tablicy ilosci strzalow na rozgrywke
                ilosc=0;
            }
        }
    }
    j=j+1;
    sort( buf, buf + j);                              //sortowanie tablicy

    plik.close();
    return ilosc_razem+j;

}


void czas_strzalu(gracze gracze[],int i,int &k,char godziny[])
{

    fstream plik;
    string napis,napis1;
    size_t cos;
    plik.open("Scorch.txt",ios::in);
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(0);
    }
    getline(plik,napis);
    getline(plik,napis);
    getline(plik,napis);
    cos=napis.find("Rozgrywka");
    if(cos!=string::npos)
    {
        while(plik)
        {
            getline(plik,napis);
            getline(plik,napis);
            cos=napis.find(gracze[i].imie);
            if(cos!=string::npos)
            {
                while(plik)
                {
                    napis1=napis[19];                                               //zapisywanie do tablicy sekund czasu strzalu w ktorych zostala wystrzelona
                    godziny[k]=strtol(napis1.c_str(), NULL, 10);
                    k++;
                    getline(plik,napis);
                    getline(plik,napis);
                    cos=napis.find("Rozgrywka");
                    if(cos!=string::npos)
                    {
                        break;
                    }
                }

            }
        }
    }
    plik.close();
}


void wznow(int &dzialo_pierwsze,int &dzialo_drugie,char wiatr[2],char plansza[2][21])
{
    string szukana,napis,napis1;
    size_t cos;
    fstream plik;
    int dlugosc;

    cout<<"Od jakiej daty chcialbys wznowic rozgrywke? Date podaj w formacie #RRRR-MM-DD.gg:mm:ss"<<endl;
    cout<<"Gdzie RRRR oznacza rok MM miesiac DD dzien gg godzine mm minute a ss sekunde."<<endl;
    cin>>szukana;
    plik.open("Scorch.txt",ios::in);
    if (!plik)
    {
        cerr << "Nieudane otwarcie pliku "
             << plik<< " do odczytu " << endl;
        exit(0);
    }

    while(plik)
    {

        getline(plik,napis);
        cos=napis.find(szukana);
        if(cos!=string::npos)
        {

            dlugosc=napis.length();                                  //wczytanie wiatru i pozycji dzial z pliku do zmiennych
            wiatr[0]=napis[dlugosc-3];
            int a=(rand()%2);
            if(a==0)
                wiatr[1]='L';
            else
                wiatr[1]='P';
            napis1=napis[dlugosc-8];
            dzialo_pierwsze=strtol(napis1.c_str(), NULL, 10);
            napis1=napis[dlugosc-5];
            dzialo_drugie=strtol(napis1.c_str(), NULL, 10);
            if(dzialo_drugie==0)
                dzialo_drugie=20;
            else
                dzialo_drugie=dzialo_drugie+10;
        }
    }

    plansza[0][dzialo_pierwsze]='X';                                        //ustawienie pozycji
    plansza[0][dzialo_drugie]='X';
    cout<<"Gracz pierwszy wylosowal dzialo na pozycji "<<plansza[1][dzialo_pierwsze]<<endl;
    cout<<"Gracz drugi wylosowal dzialo na pozycji "<<plansza[1][dzialo_drugie]<<endl<<endl<<endl;
    plik.close();
}


void skutecznosc(int i,gracze gracze[],int buf[])
{
    double a=ilosc_strzalow(gracze,i,buf)+1;
    double b= gracze[i].wygrane;
    double skutecznosc=b/a;                                                  //liczenie skutecznosci
    skutecznosc=skutecznosc*100;
    cout<<"Skutecznosc: "<<skutecznosc<<"%"<<endl;
}
