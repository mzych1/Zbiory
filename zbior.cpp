//nazwa: zbior.cpp

#include<iostream>
#include"zbior.h"
#include <algorithm>
#include <vector>

using namespace std;

Zbior::Zbior(int el, string n)//konstruktor w ktorym wpisuje sie liczby z klawiatury
 {
  bool czyByla=false;
  iloscEl=el;
  nazwa=n;
  liczby=new int [iloscEl];//alokacja pamieci dla tablicy liczb 4cyfrowych

  if(iloscEl!=0)
    cout<<"Podaj elementy zbioru-liczby czterocyfrowe (kazda liczbe zaakceptowac klawiszem ENTER): "<<endl;

  for(int i=0; i<iloscEl; i++)
    {
      do
      {
          czyByla=false;
          cin.clear();
          cin.ignore( 1000, '\n' );
          cin>>liczby[i];
          if(cin.good())//sprawdzanie czy liczba moze byc dodana tylko gdy podana zostala liczba (a nie inny znak)
          for(int j=0; j<i; j++)//sprawdzanie czy podana liczba moze byc dodana do zbioru (liczby w zbiorze nie moga sie powtarzac)
          {
            if(liczby[j]==liczby[i])
            {
              cout<<"Podana liczba wystepuje juz w zbiorze "<<nazwa<<endl;
              czyByla=true;
            }
            if(czyByla)
              break;
          }
      }while(!cin.good() || liczby[i]<1000 || liczby[i]>9999 || czyByla);
      cout<<"Liczbe dodano do zbioru"<<endl;
    }
  if(iloscEl!=0)//posortowanie liczb w tablicy, dla ulatwienia przy porownywaniu itp
    sort(liczby, liczby + iloscEl);

  cout<<"Uruchomiono konstruktor na rzecz obiektu z klasy Zbior o nazwie "<<nazwa<<endl;
 }

Zbior::Zbior(int el, vector <int> & wektorLiczb, string n="")//konstruktor do tworzenia obiektow przy operacji sumy i czesci wspolnej oraz do testow
{
  nazwa=n;
  iloscEl=el;
  if(iloscEl!=0)
  {
    liczby=new int [iloscEl];

    for(int i=0; i<iloscEl; i++)//dodawanie liczb z wektora do zbioru
      liczby[i]=wektorLiczb[i];
    sort(liczby, liczby + iloscEl);
  }
  cout<<"Uruchomiono konstruktor na rzecz obiektu z klasy Zbior o nazwie "<<nazwa;
}

Zbior::~Zbior()//usuwanie tablicy liczb 4cyfrowych
{
  delete [] liczby;
  cout<<"Uruchomiono destruktor na rzecz obiektu z klasy Zbior o nazwie "<<nazwa<<endl;
}

void Zbior::najmniejszaSuma()
{
  int *sumyCyfr;
  int sumaMin=40, t=0, s=0, d=0, j=0;

  if(!iloscEl)//jesli wybrany zbior jest pusty to nie ma w nim liczby o najmniejszej sumie cyfr
    cout<<"Zbior "<<nazwa<<" jest pusty (nie ma w nim liczby o najmniejszej sumie cyfr)"<<endl;
  else
  {
    sumyCyfr  = new int [iloscEl];//tablica w ktorej beda sumy cyfr odpowiednich liczb ze zbioru
    for(int i=0; i<iloscEl; i++)
    {
      t=liczby[i]/1000;
      s=(liczby[i]-1000*t)/100;
      d=(liczby[i]-1000*t-100*s)/10;
      j=liczby[i]-1000*t-100*s-10*d;
      sumyCyfr[i] = t+s+d+j;
      if(sumyCyfr[i]<sumaMin)
        sumaMin=sumyCyfr[i];
    }
    cout<<"Liczba/y o najmniejszej sumie cyfr w zbiorze "<<nazwa<<": ";
    for(int i=0; i<iloscEl; i++)
    {
      if(sumyCyfr[i]==sumaMin)
        cout<<liczby[i]<<" ";
    }
    cout<<endl;
    delete [] sumyCyfr;
  }
}

ostream& operator<<(ostream& out, Zbior& zbior)
{
if(zbior.iloscEl==0)
  out<<zbior.nazwa<<"=0 (zbior pusty)"<<endl;
else
  {
    out<<zbior.nazwa<<"={ ";
    for(int j=0; j<zbior.iloscEl; j++)
      {
        out<<zbior.liczby[j];
        if(j!=zbior.iloscEl-1) out<<", ";
      }
    out<<"}"<<endl;
  }
return out;
}

bool Zbior::czyTenZbior (string n)
{
  if(nazwa==n)
    return true;
  else
    return false;
}

void Zbior::wypiszNazwe()
{
  cout<<nazwa<<" ";
}

void Zbior::najwieksza()
{
  if(iloscEl==0)
    {
      cout<<"Zbior "<<nazwa<<" jest pusty (nie ma w nim najwiekszej liczby)"<<endl;
      return;
    }

    cout<<"Najwieksza liczba w zbiorze "<<nazwa<<" to "<<liczby[iloscEl-1]<<endl;
}

Zbior operator+(Zbior& zbior1, Zbior& zbior2)//suma zbiorow - powstaje przy tym nowy zbior; po tej operacji nalezy zmienic nazwe nowego obiektu
{
  vector <int> liczbySuma;
//dodawanie liczb z obu zbiorow do wektora
  for(int i=0;i<zbior1.iloscEl;i++)
    liczbySuma.push_back(zbior1.liczby[i]);

  for(int i=0;i<zbior2.iloscEl;i++)
    liczbySuma.push_back(zbior2.liczby[i]);

  sort(liczbySuma.begin(), liczbySuma.end());

  for(unsigned int i=1; i<liczbySuma.size();i++)//poczatek dla i=1, bo element musi miec poprzedni element z ktorym jest porownywany
  {
    if(liczbySuma[i]==liczbySuma[i-1])
      {
        liczbySuma.erase(liczbySuma.begin()+i);
        i--;//zmniejszenie i aby kazdy element byl porownany z poprzednikiem, element zostaje usuniety czyli zmniejsza sie wektor.size
      }
  }

  cout<<"Wykonano dzialanie: "<<zbior1.nazwa<<" [suma] "<<zbior2.nazwa<<endl;

  return Zbior((int)liczbySuma.size(), liczbySuma);
}

void operator+=(Zbior& zbior1, Zbior& zbior2)//suma zbiorow - zbior1 staje sie suma wybranych zbiorow OK
{
  vector <int> liczbySuma;
//dodawanie liczb z obu zbiorow do wektora
  for(int i=0;i<zbior1.iloscEl;i++)
    liczbySuma.push_back(zbior1.liczby[i]);

  for(int i=0;i<zbior2.iloscEl;i++)
    liczbySuma.push_back(zbior2.liczby[i]);

  sort(liczbySuma.begin(), liczbySuma.end());

  for(unsigned int i=1; i<liczbySuma.size();i++)//poczatek dla i=1, bo element musi miec poprzedni element z ktorym jest porownywany
  {
    if(liczbySuma[i]==liczbySuma[i-1])
      {
        liczbySuma.erase(liczbySuma.begin()+i);
        i--;//zmniejszenie i aby kazdy element byl porownany z poprzednikiem,elemest zostaje usuniety czyli zmniejsza sie wektor.size
      }
  }
  if(liczbySuma.size()!=zbior1.iloscEl)
  {
    if(zbior1.iloscEl!=0)
      delete [] zbior1.liczby;//usuniecie starej tablicy z liczbami
    zbior1.iloscEl=liczbySuma.size();
    if(zbior1.iloscEl!=0)
      zbior1.liczby=new int [zbior1.iloscEl];//stworzenie nowej tablicy o aktualnej liczbie elementow
  }
  for(int i=0; i<zbior1.iloscEl;i++)
    zbior1.liczby[i]=liczbySuma[i];

  cout<<"Wykonano dzialanie: "<<zbior1.nazwa<<" = "<<zbior1.nazwa<<" [suma] "<<zbior2.nazwa<<endl;
}

Zbior operator*(Zbior& zbior1, Zbior& zbior2)//czesc wspolna zbiorow - powstaje przy tym nowy zbior; po tej operacji nalezy zmienic nazwe nowego obiektu
{
  vector <int> liczbyIloczyn;
  vector <int> noweLiczby;
  //dodawanie elementow z obu zbiorow do wektora
  for(int i=0;i<zbior1.iloscEl;i++)
    liczbyIloczyn.push_back(zbior1.liczby[i]);

  for(int i=0;i<zbior2.iloscEl;i++)
    liczbyIloczyn.push_back(zbior2.liczby[i]);

  sort(liczbyIloczyn.begin(), liczbyIloczyn.end());

  for(int i=1; i<(int)liczbyIloczyn.size();i++)
    if(liczbyIloczyn[i]==liczbyIloczyn[i-1])
      noweLiczby.push_back(liczbyIloczyn[i]);

  cout<<"Wykonano dzialanie: "<<zbior1.nazwa<<" [czesc wspolna] "<<zbior2.nazwa<<endl;
  return Zbior((int)noweLiczby.size(), noweLiczby);
}

void operator*=(Zbior& zbior1, Zbior& zbior2)//czesc wspolna zbiorow - zbior1 staje sie czescia wspolna wybranych zbiorow
{
  vector <int> liczbyIloczyn;
  vector <int> noweLiczby;
  //dodawanie elementow z obu zbiorow do wektora
  for(int i=0;i<zbior1.iloscEl;i++)
    liczbyIloczyn.push_back(zbior1.liczby[i]);

  for(int i=0;i<zbior2.iloscEl;i++)
    liczbyIloczyn.push_back(zbior2.liczby[i]);

  sort(liczbyIloczyn.begin(), liczbyIloczyn.end());

  for(int i=1; i<(int)liczbyIloczyn.size();i++)
    if(liczbyIloczyn[i]==liczbyIloczyn[i-1])//jesli liczba taka sama jak poprzednia, to dodac do zbioru czesci wspolnej
      noweLiczby.push_back(liczbyIloczyn[i]);

  if(zbior1.iloscEl!=noweLiczby.size())
  {
    if(zbior1.iloscEl!=0)
      delete [] zbior1.liczby;//usuniecie starej tablicy liczb
    zbior1.iloscEl=noweLiczby.size();
    if(zbior1.iloscEl!=0)
      zbior1.liczby=new int [zbior1.iloscEl];//stworzenie nowej tablicy o aktualnej liczbie elementow
  }

  for(int i=0; i<zbior1.iloscEl; i++)
    zbior1.liczby[i]=noweLiczby[i];

  cout<<"Wykonano dzialanie: "<<zbior1.nazwa<<" = "<<zbior1.nazwa<<" [czesc wspolna] "<<zbior2.nazwa<<endl;
}

void Zbior::zmienNazwe(string n)
{
  nazwa=n;
}
