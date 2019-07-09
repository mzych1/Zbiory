//nazwa: main.cpp
//projekt 1 - wykonywane działań na zbiorach 
//zadanie 12
//autor: Magdalena Zych
//grupa I5
//prowadzacy: Aleksandra Pasnikowska
//data: 03.2018

#include <iostream>
#include <cstdlib>
#include"zbior.h"
#include <vector>
#include <string>

using namespace std;

char menu(bool);
void nowy(), wyjscie(), pokazZbiory(), testy(), dzialanie145(int), sumaCzescWspolna(int);
bool poprawnaNazwa(string);

vector <Zbior*> wektor;

int main()
{
  bool czysc=false;
  for(int i=0; ;i++)
    switch(menu(czysc))
    {
      case '1': dzialanie145(1); break;
      case '2': sumaCzescWspolna(2); break;
      case '3': sumaCzescWspolna(3); break;
      case '4': dzialanie145(4); break;
      case '5': dzialanie145(5); break;
      case '6': nowy(); break;
      case '7': testy(); break;
      case '8': wyjscie(); break;
    }
  return 0;
}

char menu(bool czysc)
{
  char wybor;
  cout<<"-----------------------------------------"<<endl;
  cout<< "Wybierz czynnosc:" << endl;
  cout<<"1.Wypisanie zbioru"<<endl;//przeciazenie operatora << OK
  cout<<"2.Suma zbiorow"<<endl;//przeciazenie operatora +
  cout<<"3.Czesc wspolna zbiorow"<<endl;//przeciazenie operatora *
  cout<<"4.Najwieksza liczba ze zbioru"<<endl;//OK
  cout<<"5.Liczba o najmniejszej sumie cyfr"<<endl;//OK
  cout<<"6.Dodanie nowego zbioru"<<endl;//OK
  cout<<"7.Testowanie"<<endl;//zrobic
  cout<<"8.Wyjscie"<<endl;//OK
do
  {
    if(czysc)
      cin.ignore( 1000, '\n' );
    czysc=true;
    cin>>wybor;

  }while(wybor!='1' && wybor!='2' && wybor!='3' && wybor!='4' && wybor!='5' && wybor!='6' && wybor!='7' && wybor!='8');
  return wybor;
}

void nowy()
{
  string n;
  int el;
  cout<<"Podaj nazwe zbioru (musi sie zaczynac litera): ";
  do
  {
    cin.ignore( 1000, '\n' );
    cin>>n;
  }while(poprawnaNazwa(n)==0);

  cout<<"Podaj ilosc elementow zbioru "<<n<<": ";

  do
  {
    cin.clear();//czyszczenie flagi bledu
    cin.ignore( 1000, '\n' );//jak nie dziala cin.sync() to sprobowac tego
    cin>>el;
  }while(cin.good()==0 || el<0);

  wektor.push_back(new Zbior(el, n));
}

void wyjscie()
{
  for(unsigned int i=0; i<wektor.size(); i++)
  {
    delete wektor[i];//niszczenie obiektow stworzonych w trakie dzialania programu
  }

  wektor.clear();//czy trzeba to robic
  exit(0);
}

bool poprawnaNazwa(string n)
{
  for(unsigned int i=0; i<wektor.size(); i++)
  {
    if(wektor[i]->czyTenZbior(n))
    {
      cout<<"Zbior o podanej nazwie juz istnieje"<<endl;
      return false;
    }
  }
  if((n[0]>='a' && n[0]<='z') || (n[0]>='A' && n[0]<='Z'))//warunek czy nazwa zaczyna sie od litery
    return true;

  cout<<"Niepoprawna nazwa"<<endl;
  return false;
}

void pokazZbiory()
{
  cout<<"Istniejace zbiory: ";

    for(int i=0; i<(int)wektor.size(); i++)
      wektor[i]->wypiszNazwe();

    cout<<endl;
}

void testy()
{
  Zbior *zbior1, *zbior2, *zbior3, *zbiorSuma, *zbiorCzWsp;//wskazniki na obiekty tworzone na potrzeby testow
  vector <int> liczbyTest;
//tworzenie obiektow
  zbior3 = new Zbior(liczbyTest.size(), liczbyTest, "PUSTY");//kiedy w wektorze nie ma jeszcze zadnych liczb
  cout<<endl;
  liczbyTest.push_back(1111);
  liczbyTest.push_back(4000);

  zbior1 = new Zbior(liczbyTest.size(), liczbyTest, "A");//gdy w wektorze sa 2 liczby
  cout<<endl;
  liczbyTest[0]=4444;
  liczbyTest[1]=1000;
  liczbyTest.push_back(1111);

  zbior2 = new Zbior(3, liczbyTest, "B");//gdy wektorze sa 3 liczby
  cout<<endl;
  cout<<endl<<"Wypisywanie zbiorow: "<<endl<<*zbior1<<*zbior2<<*zbior3<<endl;
//liczby o najmniejszej sumie cyfr
  zbior1->najmniejszaSuma();
  zbior2->najmniejszaSuma();
  zbior3->najmniejszaSuma();
  cout<<endl;
//najwieksze liczby w zbiorach
  zbior1->najwieksza();
  zbior2->najwieksza();
  zbior3->najwieksza();
  cout<<endl;
//sumowanie, nowy obiekt
  zbiorSuma = new Zbior ((*zbior1)+(*zbior2));
  zbiorSuma->zmienNazwe("suma_A_i_B");//ustawienie nazwy stworzonego obiektu
  zbiorSuma->wypiszNazwe();
  cout<<endl<<*zbiorSuma<<endl;
//czesc wspolna, nowy obiekt
  zbiorCzWsp = new Zbior ((*zbior1)*(*zbior2));
  zbiorCzWsp->zmienNazwe("czesc_wspolna_A_i_B");//ustawienie nazwy stworzonego obiektu
  zbiorCzWsp->wypiszNazwe();
  cout<<endl<<*zbiorCzWsp<<endl;

  (*zbior2)*=(*zbior1);
  cout<<*zbior2;
  (*zbior1)+=(*zbior2);
  cout<<*zbior1;
  (*zbior2)*=(*zbior3);
  cout<<*zbior2;
  (*zbior1)+=(*zbior3);
  cout<<*zbior1;

//usuwanie obiektow
  delete zbior1;
  delete zbior2;
  delete zbior3;
  delete zbiorSuma;
  delete zbiorCzWsp;
}

void dzialanie145(int wybor) //funkcja realizujaca wypisywanie zbioru, zwracanie najwiekszej liczby i zwracanie liczb o najmniejszej sumie cyfr
{
  string n;
  bool czyWywolano=false;

  if(wektor.size()==0)
    cout<<"Nie istnieje zaden zbior"<<endl;
  else
  {
    switch(wybor)
    {
    case 1: cout<<"Zbior o jakiej nazwie wypisac? "<<endl; break;
    case 4: cout<<"W ktorym zbiorze szukac najwiekszej liczby? "<<endl; break;
    case 5: cout<<"W ktorym zbiorze szukac liczb o najmniejszej sumie cyfr? "<<endl; break;
    }
    pokazZbiory();

    while(czyWywolano==0)
    {
      cin>>n;

    for(unsigned int i=0; i<wektor.size(); i++)
    {
      if(wektor[i]-> czyTenZbior(n))
      {
        switch(wybor)
        {
        case 1: cout<<*wektor[i]<<endl; break;
        case 4: wektor[i]->najwieksza(); break;
        case 5: wektor[i]->najmniejszaSuma(); break;
        }
        czyWywolano=true;
      }
    }

    if(czyWywolano==0)
      cout<<"Nie istnieje zbior o podanej nazwie "<<endl;
    }
  }
}

void sumaCzescWspolna(int wybor)//funkcja realizujaca sume i czesc wspolna zbiorow
{
  string n1, n2, n3;
  int i1=-1, i2=-1;
  bool czyByl = false, poprNazwa=true;

  if(wektor.size()==0)
    cout<<"Nie istnieje zaden zbior"<<endl;
  else
    {
      if(wybor==2)
        cout<<"Ktore 2 zbiory zsumowac?"<<endl;
      else
        cout<<"Czesc wspolna ktorych 2 zbiorow wyznaczyc?"<<endl;
      pokazZbiory();

      while(i1<0 || i2<0)//oczekiwanie na dane do momentu az oba zbiory zostana poprawnie podane
      {
        if(i1<0)
          cin>>n1;
        if(i2<0)
          cin>>n2;

      for(unsigned int i=0; i<wektor.size(); i++)
      {
        if(wektor[i]-> czyTenZbior(n1))
          i1=i;
        if(wektor[i]-> czyTenZbior(n2))
          i2=i;
      }

      if(i1<0)
        cout<<"Pierwszy podany zbior nie istnieje. Nalezy podac inna nazwe zbioru: "<<endl;
      if(i2<0)
        cout<<"Drugi podany zbior nie istnieje. Nalezy podac inna nazwe zbioru: "<<endl;
      }
      if(wybor==2)
        cout<<"Podaj nazwe zbioru ktory bedzie suma wybranych zbiorow (nie moze to byc zbior ktory juz istnieje, a nie jest sumowany): ";
      else
        cout<<"Podaj nazwe zbioru ktory bedzie czescia wspolna wybranych zbiorow (nie moze to byc zbior, ktory juz istnieje a nie jest na nim aktualnie wykonywana operacja): ";
      do
      {
       if(!poprNazwa)
          cout<<"Niepoprawna nazwa (nazwa zbioru musi zaczynac sie od litery)"<<endl;
        //cin.ignore( 1000, '\n' );
        czyByl=false;
        cin>>n3;
        for(int i=0; i<(int)wektor.size(); i++)//sprawdzanie czy podano nowa nazwe
          if(wektor[i]->czyTenZbior(n3) && i!=i1 && i!=i2)
          {
            czyByl=true;
            cout<<"Zbior o podanej nazwie juz istnieje i nie jest sumowany"<<endl;
          }
        if(!czyByl)
          poprNazwa=false;
      }while(!((n3[0]>='a' && n3[0]<='z') || (n3[0]>='A' && n3[0]<='Z')) || czyByl==true);

      if(n3==n1)
      {
        if(wybor==2)
          *wektor[i1]+=*wektor[i2];
        else
          *wektor[i1]*=*wektor[i2];
        return;
      }
      if(n3==n2)
      {
        if(wybor==2)
          *wektor[i2]+=*wektor[i1];
        else
          *wektor[i2]*=*wektor[i1];
          return;
      }
      if(wybor==2)
        wektor.push_back(new Zbior (*(wektor[i1])+*(wektor[i2])));//tworzenie nowego obiektu - sumy wybranych wczesniej zbiorow
      else
      wektor.push_back(new Zbior ((*wektor[i1])*(*wektor[i2])));//tworzenie nowego obiiektu - czesci wspolnej wybranych wczesniej zbiorow

      wektor[wektor.size()-1]->zmienNazwe(n3);//ustawienie nazwy stworzonego obiektu
      wektor[wektor.size()-1]->wypiszNazwe();
      cout<<endl;
    }
}
