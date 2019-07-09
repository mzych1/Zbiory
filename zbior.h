//nazwa: zbior.h

#include<iostream>
#include<vector>

using namespace std;

class Zbior
{
private:
  string nazwa;
  int iloscEl;
  int *liczby;
public:
  Zbior(int, string);//konstruktor, alokacja pamieci dla tablicy liczb
  Zbior(int, vector <int> &, string);
  ~Zbior();//destruktor, usuwa wczesniej stworzona tablice
  void najwieksza();
  void najmniejszaSuma();
  bool czyTenZbior (string);
  void wypiszNazwe();
  void zmienNazwe(string);
  friend ostream& operator<<(ostream& out, Zbior& zbior);
  friend Zbior operator+(Zbior& zbior1, Zbior& zbior2);//przeciazenie operatora +
  friend void operator+=(Zbior& zbior1, Zbior& zbior2);//przeciazenie peratora +=
  friend Zbior operator*(Zbior& zbior1, Zbior& zbior2);//przeciazenie operatora *
  friend void operator*=(Zbior& zbior1, Zbior& zbior2);//przeciazenie operarora *=
};

