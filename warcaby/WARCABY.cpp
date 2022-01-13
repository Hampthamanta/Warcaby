#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <windows.h>
#include <vector>

using namespace std;

class plansza
{
public:
    int pole;
    string kolor;
    string typ;
    string znak;
};

class ustawienie_planszy
{
public:
    string znak;
};

class ustawienie_pol
{
public:
    int pole;
    string nazwa_pola;
};

plansza pionek[24];
ustawienie_planszy znak_na_polu[32];
ustawienie_pol wybrane_pole[32];

string wybor;
string sprawdz_pole;
string nazwa_pola_f2;
int numer_pola_gdzie_jest_pionek;
bool mozliwy_ruch = false;
bool mozliwe_bicie = false, mozliwe_bicie_komputera = false;

bool ruch_w_prawo_gora = true, ruch_w_lewo_gora = true, ruch_w_prawo_dol = true, ruch_w_lewo_dol = true;

bool mozliwy_ruch_bialych = true, mozliwy_ruch_czarnych = true;
int ile_mozliwych_ruchow_bialych = 0, ile_mozliwych_ruchow_czarnych = 0;
bool mozliwe_bicie_bialych_komp = false, mozliwe_bicie_czarnych_komp = false;

int lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[24];
int lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[24];
int pola_gdzie_damka_moze_sie_ruszyc[32];
int liczba_ruchow_w_prawo_gora_damki = 0, liczba_ruchow_w_lewo_gora_damki = 0, liczba_ruchow_w_prawo_dol_damki = 0, liczba_ruchow_w_lewo_dol_damki = 0;

bool zbijanie_prawo_gora = true, zbijanie_lewo_gora = true, zbijanie_prawo_dol = true, zbijanie_lewo_dol = true;
bool zbijanie_damka_pg = true, zbijanie_damka_lg = true, zbijanie_damka_pd = true, zbijanie_damka_ld = true;

bool istnienie_zbijanego_pionka_pg = false;
bool istnienie_zbijanego_pionka_lg = false;
bool istnienie_zbijanego_pionka_pd = false;
bool istnienie_zbijanego_pionka_ld = false;

int id_pionka_ktory_moze_zbic_damka_pg = -1, id_pionka_ktory_moze_zbic_damka_pd = -1, id_pionka_ktory_moze_zbic_damka_lg = -1, id_pionka_ktory_moze_zbic_damka_ld = -1;

bool czyja_tura = true; // "true" - ruch białych, "false" - ruch czarnych
bool wybrano_poprawnie_pionka_tury = false;

string kto_gra = "0"; // "1" - gracz na gracza, "2"- gracz na komputer, "3" - komputer na komputer.  Może kiedyś się przyda xd

char pauza; // do debugera w vs

//
// biale pioneki: \2, damki: \3
//
// czarne pionki: \1, damki: \6
//

//       +---+---+---+---+---+---+---+---+
//     8 |   |82 |   |84 |   | 86|   | 88|
//       +---+---+---+---+---+---+---+---+
//     7 | 71|   | 73|   |75 |   | 77|   |
//       +---+---+---+---+---+---+---+---+
//     6 |   |62 |   |64 |   | 66|   | 68|
//       +---+---+---+---+---+---+---+---+
//     5 | 51|   |53 |   | 55|   | 57|   |
//       +---+---+---+---+---+---+---+---+
//     4 |   | 42|   | 44|   | 46|   | 48|
//       +---+---+---+---+---+---+---+---+
//     3 | 31|   | 33|   | 35|   | 37|   |
//       +---+---+---+---+---+---+---+---+
//     2 |   |22 |   |24 |   | 26|   | 28|
//       +---+---+---+---+---+---+---+---+
//     1 | 11|   | 13|   | 15|   | 17|   |
//       +---+---+---+---+---+---+---+---+
//         A   B   C   D   E   F   G   H
//
//
//
//FUNKCJE____FUNKCJE____FUNKCJE____FUNKCJE____FUNKCJE____FUNKCJE____
void ustawienie_pionkow_na_planszy();
void zamiana_pionka_na_damke();
void aktualizuj_plansze();
int sprawdz_numer_pola(string nazwa_pola_f);
int sprawdz_indeks_pionka(int nr_pola);
string sprawdz_kolor_pionka(int nr_pola);

void sprawdz_mozliwy_ruch_pionka_krawedzie_funkcja(int indeks_pionka);
void sprawdz_mozliwe_bicie_pionka_krawedzie_funkcja(int indeks_pionka);

void sprawdz_mozliwy_ruch_pionka_bialego_funkcja(int pole_pionka);
void sprawdz_mozliwy_ruch_pionka_czarnego_funkcja(int pole_pionka);
void sprawdz_mozliwe_bicie_pionka_funkcja(int pole_pionka);
void sprawdz_mozliwe_ruchy_damki(int indeks_pionka);
void sprawdz_mozliwe_bicia_damki(int indeks_pionka);

void ruch_pionka(int pole_pionka, int indeks_pionka);

void wykonaj_ruch(string nazwa_pola);
void wykonaj_ruch_komputera(int id);
void wywolanie_ruchu_komputera();

void ile_mozliwych_ruchow_pionkow_funkcja(int indeks_pionka);
void sprawdz_czy_jest_mozliwy_ruch();
void sprawdz_czy_jest_mozliwe_zbicie();

void sprawdz_zakonczenie_gry();

void GraczVsGracz();
void GraczVsKomputer();
void KomputerVsKomputer();

//
//
//
//
//
//

void ustawienie_pionkow_na_planszy()
{
    int n = 11;
    for (int i = 0; i < 24; i++)
    {
        if (i == 4)
            n = 22;
        else if (i == 8)
            n = 31;
        else if (i == 12)
            n = 62;
        else if (i == 16)
            n = 71;
        else if (i == 20)
            n = 82;
        pionek[i].pole = n;
        n += 2;
    }

    // ustawienia pionkow
    for (int i = 0; i < 12; i++)
    {
        pionek[i].znak = "\2"; // "\2" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "bialy";
        pionek[i].typ = "pionek";
    }

    for (int i = 12; i < 24; i++)
    {
        pionek[i].znak = "\1"; // "\1" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "czarny";
        pionek[i].typ = "pionek";
    }
}

//
//
//

void zamiana_pionka_na_damke()
{
    for (int i = 0; i < 12; i++) // dla bialych
    {
        if (pionek[i].typ == "pionek")
        {
            if (pionek[i].pole == 82 || pionek[i].pole == 84 || pionek[i].pole == 86 || pionek[i].pole == 88)
            {
                pionek[i].typ = "damka";
                pionek[i].znak = "\3";
            }
        }
    }

    for (int i = 12; i < 24; i++) // dla czarnych
    {
        if (pionek[i].typ == "pionek")
        {
            if (pionek[i].pole == 11 || pionek[i].pole == 13 || pionek[i].pole == 15 || pionek[i].pole == 17)
            {
                pionek[i].typ = "damka";
                pionek[i].znak = "\6";
            }
        }
    }
}

//
//
//

void aktualizuj_plansze()
{
    system("cls");

    int n = 11;

    for (int k = 0; k < 32; k++) // ustawienie znakow na polach czarnych
    {
        znak_na_polu[k].znak = "x";
    }

    for (int i = 0; i < 32; i++)
    {
        if (i == 4)
            n = 22;
        else if (i == 8)
            n = 31;
        else if (i == 12)
            n = 42;
        else if (i == 16)
            n = 51;
        else if (i == 20)
            n = 62;
        else if (i == 24)
            n = 71;
        else if (i == 28)
            n = 82;

        for (int j = 0; j < 24; j++) // wstawienia znakow pionkow na pola czarne
        {
            if (pionek[j].pole == n)
                znak_na_polu[i].znak = pionek[j].znak;
        }

        n += 2;
    }

    // rysowanie planszy w konsoli
    cout << "\n\n      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 8 << " |   | " << znak_na_polu[28].znak << " |   | " << znak_na_polu[29].znak << " |   | " << znak_na_polu[30].znak << " |   | " << znak_na_polu[31].znak << " |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 7 << " | " << znak_na_polu[24].znak << " |   | " << znak_na_polu[25].znak << " |   | " << znak_na_polu[26].znak << " |   | " << znak_na_polu[27].znak << " |   |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 6 << " |   | " << znak_na_polu[20].znak << " |   | " << znak_na_polu[21].znak << " |   | " << znak_na_polu[22].znak << " |   | " << znak_na_polu[23].znak << " |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 5 << " | " << znak_na_polu[16].znak << " |   | " << znak_na_polu[17].znak << " |   | " << znak_na_polu[18].znak << " |   | " << znak_na_polu[19].znak << " |   |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 4 << " |   | " << znak_na_polu[12].znak << " |   | " << znak_na_polu[13].znak << " |   | " << znak_na_polu[14].znak << " |   | " << znak_na_polu[15].znak << " |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 3 << " | " << znak_na_polu[8].znak << " |   | " << znak_na_polu[9].znak << " |   | " << znak_na_polu[10].znak << " |   | " << znak_na_polu[11].znak << " |   |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 2 << " |   | " << znak_na_polu[4].znak << " |   | " << znak_na_polu[5].znak << " |   | " << znak_na_polu[6].znak << " |   | " << znak_na_polu[7].znak << " |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "    " << 1 << " | " << znak_na_polu[0].znak << " |   | " << znak_na_polu[1].znak << " |   | " << znak_na_polu[2].znak << " |   | " << znak_na_polu[3].znak << " |   |\n";
    cout << "      +---+---+---+---+---+---+---+---+\n";
    cout << "        A   B   C   D   E   F   G   H\n\n";
}

//
//
//

int sprawdz_numer_pola(string nazwa_pola_f) // funkcja sprawdzajaca podana nazwe pola przez gracza i zwraca numer tego pola, jezeli jest to pole czarne(uzytkowe)
{
    transform(nazwa_pola_f.begin(), nazwa_pola_f.end(), nazwa_pola_f.begin(), ::toupper); // do obslugi malych liter

    int nr_pola = 0;

    for (int i = 0; i < 32; i++)
    {
        if (nazwa_pola_f == wybrane_pole[i].nazwa_pola)
        {
            cout << "Wybrane pole " << wybrane_pole[i].nazwa_pola << " ma indeks na plaszny rowny " << wybrane_pole[i].pole << "\n";
            nr_pola = wybrane_pole[i].pole;
        }
    }

    return nr_pola; // gdy gracz nie poda czarnego pola to funkcja zwraca 0
}

//
//
//

int sprawdz_indeks_pionka(int nr_pola) // funkcja sprawdza czy na podanym polu znajduje sie pionek, jezeli tak to zwraca jego inkeds(id),
{                                      //                                      jezeli nie ma tam pionka to zwraca -1
    int id_pola = -1;

    for (int j = 0; j < 24; j++) // to jest na razie dla wszystkich pionkow. Pozniej podzielic na biale i czarne
    {
        if (nr_pola == pionek[j].pole)
        {
            id_pola = j;
            // cout << "Na wybranym polu zajduje sie " << pionek[j].typ << " " << pionek[j].kolor << " o indeksie " << j << endl;
        }
    }

    return id_pola;
}

//
//
//

string sprawdz_kolor_pionka(int nr_pola)
{
    string kolor;
    for (int k = 0; k < 24; k++)
    {
        if (nr_pola == pionek[k].pole)
        {
            kolor = pionek[k].kolor;
        }
    }
    return kolor;
}

//
//
//

void sprawdz_mozliwy_ruch_pionka_krawedzie_funkcja(int indeks_pionka)
{
    if (pionek[indeks_pionka].typ == "pionek")
    {
        if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 82)
        {
            ruch_w_prawo_gora = false;
            ruch_w_lewo_gora = false;
        }
        if (pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 13 || pionek[indeks_pionka].pole == 15 || pionek[indeks_pionka].pole == 17)
        {
            ruch_w_prawo_dol = false;
            ruch_w_lewo_dol = false;
        }
        if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 28)
        {
            ruch_w_prawo_gora = false;
            ruch_w_prawo_dol = false;
        }
        if (pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 11)
        {
            ruch_w_lewo_gora = false;
            ruch_w_lewo_dol = false;
        }
    }
}

//
//
//

void sprawdz_mozliwe_bicie_pionka_krawedzie_funkcja(int indeks_pionka)
{
    if (pionek[indeks_pionka].typ == "pionek")
    {
        if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 82 || pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 73 || pionek[indeks_pionka].pole == 75 || pionek[indeks_pionka].pole == 77)
        {
            zbijanie_prawo_gora = false;
            zbijanie_lewo_gora = false;
        }
        if (pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 13 || pionek[indeks_pionka].pole == 15 || pionek[indeks_pionka].pole == 17 || pionek[indeks_pionka].pole == 22 || pionek[indeks_pionka].pole == 24 || pionek[indeks_pionka].pole == 26 || pionek[indeks_pionka].pole == 28)
        {
            zbijanie_prawo_dol = false;
            zbijanie_lewo_dol = false;
        }
        if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 77 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 57 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 37 || pionek[indeks_pionka].pole == 28 || pionek[indeks_pionka].pole == 17)
        {
            zbijanie_prawo_gora = false;
            zbijanie_prawo_dol = false;
        }
        if (pionek[indeks_pionka].pole == 82 || pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 62 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 42 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 22 || pionek[indeks_pionka].pole == 11)
        {
            zbijanie_lewo_gora = false;
            zbijanie_lewo_dol = false;
        }
    }
}

//
//
//

void sprawdz_mozliwy_ruch_pionka_bialego_funkcja(int pole_pionka)
{
    ruch_w_prawo_dol = false;
    ruch_w_lewo_dol = false;

    for (int i = 0; i < 24; i++)
    {
        if (ruch_w_prawo_gora == true && ((pole_pionka + 11) == pionek[i].pole))
            ruch_w_prawo_gora = false;

        if (ruch_w_lewo_gora == true && ((pole_pionka + 9) == pionek[i].pole))
            ruch_w_lewo_gora = false;
    }
}

//
//
//

void sprawdz_mozliwy_ruch_pionka_czarnego_funkcja(int pole_pionka)
{
    ruch_w_prawo_gora = false;
    ruch_w_lewo_gora = false;

    for (int i = 0; i < 24; i++)
    {
        if (ruch_w_prawo_dol == true && ((pole_pionka - 9) == pionek[i].pole))
            ruch_w_prawo_dol = false;

        if (ruch_w_lewo_dol == true && ((pole_pionka - 11) == pionek[i].pole))
            ruch_w_lewo_dol = false;
    }
}

//
//
//

void sprawdz_mozliwe_bicie_pionka_funkcja(int pole_pionka)
{
    //sprawdzanie czy na polu na które chce się ruszyć jest pionek
    for (int i = 0; i < 24; i++)
    {
        if ((pole_pionka + 22) == pionek[i].pole)
            zbijanie_prawo_gora = false;

        if ((pole_pionka + 18) == pionek[i].pole)
            zbijanie_lewo_gora = false;

        if ((pole_pionka - 18) == pionek[i].pole)
            zbijanie_prawo_dol = false;

        if ((pole_pionka - 22) == pionek[i].pole)
            zbijanie_lewo_dol = false;
    }

    //sprawdzenie czy jest pionek na polu które chcemy zbić i jakiego jest koloru

    for (int i = 0; i < 24; i++)
    {
        if (((pole_pionka + 11) == pionek[i].pole) && (zbijanie_prawo_gora == true))
        {
            istnienie_zbijanego_pionka_pg = true;
            if (sprawdz_kolor_pionka((pole_pionka + 11)) == (pionek[sprawdz_indeks_pionka(pole_pionka)].kolor))
            {
                zbijanie_prawo_gora = false;
            }
        }

        if (((pole_pionka + 9) == pionek[i].pole) && (zbijanie_lewo_gora == true))
        {
            istnienie_zbijanego_pionka_lg = true;
            if (sprawdz_kolor_pionka((pole_pionka + 9)) == (pionek[sprawdz_indeks_pionka(pole_pionka)].kolor))
            {
                zbijanie_lewo_gora = false;
            }
        }

        if (((pole_pionka - 11) == pionek[i].pole) && (zbijanie_lewo_dol == true))
        {
            istnienie_zbijanego_pionka_ld = true;
            if (sprawdz_kolor_pionka((pole_pionka - 11)) == (pionek[sprawdz_indeks_pionka(pole_pionka)].kolor))
            {
                zbijanie_lewo_dol = false;
            }
        }

        if (((pole_pionka - 9) == pionek[i].pole) && (zbijanie_prawo_dol == true))
        {
            istnienie_zbijanego_pionka_pd = true;
            if (sprawdz_kolor_pionka((pole_pionka - 9)) == (pionek[sprawdz_indeks_pionka(pole_pionka)].kolor))
            {
                zbijanie_prawo_dol = false;
            }
        }
    }
}

//
//
//

void sprawdz_mozliwe_ruchy_damki(int indeks_pionka)
{
    liczba_ruchow_w_prawo_gora_damki = 0;
    liczba_ruchow_w_lewo_gora_damki = 0;
    liczba_ruchow_w_prawo_dol_damki = 0;
    liczba_ruchow_w_lewo_dol_damki = 0;

    id_pionka_ktory_moze_zbic_damka_pg = -1;
    id_pionka_ktory_moze_zbic_damka_pd = -1;
    id_pionka_ktory_moze_zbic_damka_lg = -1;
    id_pionka_ktory_moze_zbic_damka_ld = -1;

    for (int i = 0; i < 32; i++)
    {
        pola_gdzie_damka_moze_sie_ruszyc[i] = 0; // wyzerowanie komórek pamieci
    }

    int id_pionka = -1;
    int szukane_pole = 0;

    // ruch w prawo gora
    for (int rpg = 0; rpg < 7; rpg++) // maksymalna liczba ruchow damki po jednej przekatenej PRAWO GORA
    {
        if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 28 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 82)
        {
            rpg = 8;
        }
        else
        {
            szukane_pole = ((rpg * 11) + (pionek[indeks_pionka].pole + 11));
            if (szukane_pole == 88 || szukane_pole == 86 || szukane_pole == 84 || szukane_pole == 82 || szukane_pole == 68 || szukane_pole == 48 || szukane_pole == 28)
            {
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_prawo_gora_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[rpg] = szukane_pole;
                    rpg = 8;
                }
                else
                {
                    rpg = 8;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
            else
            {
                // cout << "     szukane_pole wynosi: " << szukane_pole << endl;
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_prawo_gora_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[rpg] = szukane_pole;
                    // cout << "      moziwy ruch na pole " << szukane_pole << "\n\n";
                }
                else
                {
                    rpg = 8;
                    id_pionka_ktory_moze_zbic_damka_pg = id_pionka;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
        }
    }

    // ruch w lewo gora
    for (int rlg = 0; rlg < 7; rlg++) // maksymalna liczba ruchow damki po jednej przekatenej LEWO GORA
    {
        if (pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 82)
        {
            rlg = 8;
        }
        else
        {
            szukane_pole = ((rlg * 9) + (pionek[indeks_pionka].pole + 9));
            if (szukane_pole == 86 || szukane_pole == 84 || szukane_pole == 82 || szukane_pole == 71 || szukane_pole == 51 || szukane_pole == 31)
            {
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1) // gdy wyszukane pole jest puste
                {
                    liczba_ruchow_w_lewo_gora_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[(rlg + 8)] = szukane_pole;
                    rlg = 8;
                }
                else
                {
                    rlg = 8;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
            else
            {
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_lewo_gora_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[(rlg + 8)] = szukane_pole;
                }
                else
                {
                    rlg = 8;
                    id_pionka_ktory_moze_zbic_damka_lg = id_pionka;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
        }
    }

    // ruch w prawy dol
    for (int rpd = 0; rpd < 7; rpd++) // maksymalna liczba ruchow damki po jednej przekatenej PRAWO DOL
    {
        if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 28 || pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 13 || pionek[indeks_pionka].pole == 15 || pionek[indeks_pionka].pole == 17)
        {
            rpd = 8;
        }
        else
        {
            szukane_pole = ((pionek[indeks_pionka].pole - 9) - (rpd * 9));
            if (szukane_pole == 68 || szukane_pole == 48 || szukane_pole == 28 || szukane_pole == 11 || szukane_pole == 13 || szukane_pole == 15 || szukane_pole == 17)
            {
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_prawo_dol_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[(rpd + 16)] = szukane_pole;
                    rpd = 8;
                }
                else
                {
                    rpd = 8;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
            else
            {
                // cout << "     szukane_pole wynosi: " << szukane_pole << endl;
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_prawo_dol_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[(rpd + 16)] = szukane_pole;
                    // cout << "      moziwy ruch na pole " << szukane_pole << "\n\n";
                }
                else
                {
                    rpd = 8; // konczy petle liczenia ruchow
                    id_pionka_ktory_moze_zbic_damka_pd = id_pionka;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
        }
    }

    // ruch w lewy dol
    for (int rld = 0; rld < 7; rld++) // maksymalna liczba ruchow damki po jednej przekatenej LEWO DOL
    {
        if (pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 13 || pionek[indeks_pionka].pole == 15 || pionek[indeks_pionka].pole == 17)
        {
            rld = 8;
        }
        else
        {
            szukane_pole = ((pionek[indeks_pionka].pole - 11) - (rld * 11));
            if (szukane_pole == 71 || szukane_pole == 51 || szukane_pole == 31 || szukane_pole == 11 || szukane_pole == 13 || szukane_pole == 15 || szukane_pole == 17)
            {
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_lewo_dol_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[(rld + 24)] = szukane_pole;
                    rld = 8;
                }
                else
                {
                    rld = 8;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
            else
            {
                // cout << "     szukane_pole wynosi: " << szukane_pole << endl;
                id_pionka = sprawdz_indeks_pionka(szukane_pole);
                if (id_pionka == -1)
                {
                    liczba_ruchow_w_lewo_dol_damki++;
                    pola_gdzie_damka_moze_sie_ruszyc[(rld + 24)] = szukane_pole;
                    // cout << "      moziwy ruch na pole " << szukane_pole << "\n\n";
                }
                else
                {
                    rld = 8;
                    id_pionka_ktory_moze_zbic_damka_ld = id_pionka;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
        }
    }
}

//
//
//

void sprawdz_mozliwe_bicia_damki(int indeks_pionka)
{
    zbijanie_damka_pg = true;
    zbijanie_damka_lg = true;
    zbijanie_damka_pd = true;
    zbijanie_damka_ld = true;
    //sprawdzanie czy w pg jest pionek ktorego mozna zbic///////////////////////////////////////
    if (id_pionka_ktory_moze_zbic_damka_pg == -1)
    {
        zbijanie_damka_pg = false;
    }
    //jesli jest, to sprawdzamy czy na polu za nim znajduje sie pionek
    else
    {
        for (int h = 0; h < 24; h++)
        {
            if ((pionek[id_pionka_ktory_moze_zbic_damka_pg].pole + 11) == pionek[h].pole)
            {
                zbijanie_damka_pg = false;
            }
        }
        //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
        if ((pionek[id_pionka_ktory_moze_zbic_damka_pg].kolor == pionek[indeks_pionka].kolor))
        {
            zbijanie_damka_pg = false;
        }
    }
    //sprawdzanie czy w lg jest pionek ktorego mozna zbic///////////////////////////////////////
    if (id_pionka_ktory_moze_zbic_damka_lg == -1)
    {
        zbijanie_damka_lg = false;
    }
    //jesli jest, to sprawdzamy czy na polu za nim znajduje sie pionek
    else
    {
        for (int h = 0; h < 24; h++)
        {
            if ((pionek[id_pionka_ktory_moze_zbic_damka_lg].pole + 9) == pionek[h].pole)
            {
                zbijanie_damka_lg = false;
            }
        }
        //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
        if (pionek[id_pionka_ktory_moze_zbic_damka_lg].kolor == pionek[indeks_pionka].kolor)
        {
            zbijanie_damka_lg = false;
        }
    }
    //sprawdzanie czy w pd jest pionek ktorego mozna zbic//////////////////////////////////////
    if (id_pionka_ktory_moze_zbic_damka_pd == -1)
    {
        zbijanie_damka_pd = false;
    }
    //jesli jest, to sprawdzamy czy na polu za nim znajduje sie pionek
    else
    {
        for (int h = 0; h < 24; h++)
        {
            if ((pionek[id_pionka_ktory_moze_zbic_damka_pd].pole - 9) == pionek[h].pole)
            {
                zbijanie_damka_pd = false;
            }
        }
        //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
        if (pionek[id_pionka_ktory_moze_zbic_damka_pg].kolor == pionek[indeks_pionka].kolor)
        {
            zbijanie_damka_pd = false;
        }
    }
    //sprawdzanie czy w ld jest pionek ktorego mozna zbic//////////////////////////////////////
    if (id_pionka_ktory_moze_zbic_damka_ld == -1)
    {
        zbijanie_damka_ld = false;
    }
    //jesli jest, to sprawdzamy czy na polu za nim znajduje sie pionek
    else
    {
        for (int h = 0; h < 24; h++)
        {
            if ((pionek[id_pionka_ktory_moze_zbic_damka_ld].pole - 11) == pionek[h].pole)
            {
                zbijanie_damka_ld = false;
            }
        }
        //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
        if (pionek[id_pionka_ktory_moze_zbic_damka_ld].kolor == pionek[indeks_pionka].kolor)
        {
            zbijanie_damka_ld = false;
        }
    }
}

//
//
//

void ruch_pionka(int pole_pionka, int indeks_pionka)
{
    if (pionek[indeks_pionka].typ == "pionek")
    {
        ruch_w_prawo_gora = true; // przy wywolaniu funkcji te parametry musza sie resetowac
        ruch_w_lewo_gora = true;
        ruch_w_prawo_dol = true;
        ruch_w_lewo_dol = true;

        zbijanie_prawo_gora = true;
        zbijanie_lewo_gora = true;
        zbijanie_prawo_dol = true;
        zbijanie_lewo_dol = true;

        istnienie_zbijanego_pionka_pg = false;
        istnienie_zbijanego_pionka_lg = false;
        istnienie_zbijanego_pionka_pd = false;
        istnienie_zbijanego_pionka_ld = false;

        zbijanie_damka_pg = false;
        zbijanie_damka_lg = false;
        zbijanie_damka_pd = false;
        zbijanie_damka_ld = false;
    }
    else if (pionek[indeks_pionka].typ == "damka")
    {
        ruch_w_prawo_gora = false;
        ruch_w_prawo_dol = false;
        ruch_w_lewo_gora = false;
        ruch_w_lewo_dol = false;
    }

    liczba_ruchow_w_prawo_gora_damki = 0;
    liczba_ruchow_w_lewo_gora_damki = 0;
    liczba_ruchow_w_prawo_dol_damki = 0;
    liczba_ruchow_w_lewo_dol_damki = 0;

    int numer_pola_do_ruchu = 0;

    sprawdz_mozliwy_ruch_pionka_krawedzie_funkcja(indeks_pionka);
    sprawdz_mozliwe_bicie_pionka_krawedzie_funkcja(indeks_pionka);

    if (pionek[indeks_pionka].kolor == "bialy" && pionek[indeks_pionka].typ == "pionek")
    {
        sprawdz_mozliwy_ruch_pionka_bialego_funkcja(pole_pionka);
        sprawdz_mozliwe_bicie_pionka_funkcja(pole_pionka);
    }
    else if (pionek[indeks_pionka].kolor == "czarny" && pionek[indeks_pionka].typ == "pionek")
    {
        sprawdz_mozliwy_ruch_pionka_czarnego_funkcja(pole_pionka);
        sprawdz_mozliwe_bicie_pionka_funkcja(pole_pionka);
    }

    else if (pionek[indeks_pionka].typ == "damka") // DAMKI SPRAWDZANIE RUCHU
    {
        sprawdz_mozliwe_ruchy_damki(indeks_pionka);
        sprawdz_mozliwe_bicia_damki(indeks_pionka);
    }

    //
    //
    //

    // dla damek -- komunikaty gdzie moze sie ruszyc
    if (pionek[indeks_pionka].typ == "damka")
    {
        if (liczba_ruchow_w_prawo_gora_damki != 0)
            cout << "\t Wybrana damka moze wykonac " << liczba_ruchow_w_prawo_gora_damki << " ruchow w prawo gora\n";

        if (liczba_ruchow_w_lewo_gora_damki != 0)
            cout << "\t Wybrana damka moze wykonac " << liczba_ruchow_w_lewo_gora_damki << " ruchow w lewo gora\n";

        if (liczba_ruchow_w_prawo_dol_damki != 0)
            cout << "\t Wybrana damka moze wykonac " << liczba_ruchow_w_prawo_dol_damki << " ruchow w prawo dol\n";

        if (liczba_ruchow_w_lewo_dol_damki != 0)
            cout << "\t Wybrana damka moze wykonac " << liczba_ruchow_w_lewo_dol_damki << " ruchow w lewo dol\n\n";

        if (zbijanie_damka_pg == true)
            cout << "damka MOZE zbijac PRAWO DO GORY" << endl;
        else
            cout << "damka NIE moze zbijac PRAWO DO GORY" << endl;
        if (zbijanie_damka_lg == true)
            cout << "damka MOZE zbijac LEWO DO GORY" << endl;
        else
            cout << "damka NIE moze zbijac LEWO DO GORY" << endl;
        if (zbijanie_damka_pd == true)
            cout << "damka MOZE zbijac PRAWO W DOL" << endl;
        else
            cout << "damka NIE moze zbijac PRAWO W DOL" << endl;
        if (zbijanie_damka_ld == true)
            cout << "damka MOZE zbijac LEWO W DOL" << endl;
        else
            cout << "damka NIE moze zbijac LEWO W DOL" << endl;
        cout << endl;
    }

    // dla pionkow -- komunikaty gdzie moze sie ruszyc
    if (pionek[indeks_pionka].typ == "pionek")
    {
        if (ruch_w_prawo_gora == true)
            cout << "Pionek MOZE ruszyc sie w PRAWO DO GORY\n";
        else
            cout << "Pionek NIE moze ruszyc sie w PRAWO DO GORY\n";

        if (ruch_w_lewo_gora == true)
            cout << "Pionek MOZE ruszyc sie w LEWO DO GORY\n";
        else
            cout << "Pionek NIE moze ruszyc sie w LEWO DO GORY\n";

        if (ruch_w_prawo_dol == true)
            cout << "Pionek MOZE ruszyc sie w PRAWO W DOL\n";
        else
            cout << "Pionek NIE moze ruszyc sie w PRAWO W DOL\n";

        if (ruch_w_lewo_dol == true)
            cout << "Pionek MOZE ruszyc sie w LEWO W DOL\n";
        else
            cout << "Pionek NIE moze ruszyc sie w LEWO W DOL\n\n";

        if (zbijanie_prawo_gora == true && istnienie_zbijanego_pionka_pg == true)
            cout << "Pionek MOZE zbijac w PRAWO DO GORY\n";
        else
            cout << "Pionek NIE moze zbijac w PRAWO DO GORY\n";

        if (zbijanie_lewo_gora == true && istnienie_zbijanego_pionka_lg == true)
            cout << "Pionek MOZE zbijac w LEWO DO GORY\n";
        else
            cout << "Pionek NIE moze zbijac w LEWO DO GORY\n";

        if (zbijanie_prawo_dol == true && istnienie_zbijanego_pionka_pd == true)
            cout << "Pionek MOZE zbijac w PRAWO W DOL\n";
        else
            cout << "Pionek NIE moze zbijac w PRAWO W DOL\n";

        if (zbijanie_lewo_dol == true && istnienie_zbijanego_pionka_ld == true)
            cout << "Pionek MOZE zbijac w LEWO W DOL\n";
        else
            cout << "Pionek NIE moze zbijac w LEWO W DOL\n";
        cout << endl;
    }

    //
    //
    //

    // dla pionkow
    if (ruch_w_prawo_gora == true || ruch_w_lewo_gora == true || ruch_w_prawo_dol == true || ruch_w_lewo_dol == true)
        mozliwy_ruch = true;

    if (zbijanie_prawo_gora == true || zbijanie_lewo_gora == true || zbijanie_prawo_dol == true || zbijanie_lewo_dol == true)
        mozliwe_bicie = true;

    // dla damek
    if (liczba_ruchow_w_lewo_dol_damki > 0 || liczba_ruchow_w_prawo_dol_damki > 0 || liczba_ruchow_w_lewo_gora_damki > 0 || liczba_ruchow_w_prawo_gora_damki > 0)
        mozliwy_ruch = true;

    if (zbijanie_damka_pg == true || zbijanie_damka_lg == true || zbijanie_damka_pd == true || zbijanie_damka_ld == true)
        mozliwe_bicie = true;

    //
    //
    //

    if (mozliwy_ruch == true || mozliwe_bicie == true)
    {
    podano_zle_pole_do_ruchu:
        cout << "\nPodaj pole na planszy gdzie chesz ruszyc wybranego pionka: ";
        cin >> nazwa_pola_f2;

        if (nazwa_pola_f2 != "0") // okienko wyjscia z wyboru pola
        {

            numer_pola_do_ruchu = sprawdz_numer_pola(nazwa_pola_f2);

            if ((numer_pola_do_ruchu == 0))
            {
                aktualizuj_plansze();
                goto podano_zle_pole_do_ruchu;
            }

            for (int i = 0; i < 24; i++)
            {
                if (numer_pola_do_ruchu == pionek[i].pole)
                    goto podano_zle_pole_do_ruchu;
            }

            if (pionek[indeks_pionka].typ == "pionek")
            {
                if ((((pionek[indeks_pionka].pole + 11) == numer_pola_do_ruchu) && (ruch_w_prawo_gora == true)) || (((pionek[indeks_pionka].pole + 9) == numer_pola_do_ruchu) && (ruch_w_lewo_gora == true)) || (((pionek[indeks_pionka].pole - 11) == numer_pola_do_ruchu) && (ruch_w_lewo_dol == true)) || (((pionek[indeks_pionka].pole - 9) == numer_pola_do_ruchu) && (ruch_w_prawo_dol == true)))
                {
                    // cout << "Ruch pionka\n";
                    pionek[indeks_pionka].pole = numer_pola_do_ruchu;
                    aktualizuj_plansze();
                }
                else if ((((pionek[indeks_pionka].pole + 22) == numer_pola_do_ruchu) && (zbijanie_prawo_gora == true)) || (((pionek[indeks_pionka].pole + 18) == numer_pola_do_ruchu) && (zbijanie_lewo_gora == true)) || (((pionek[indeks_pionka].pole - 18) == numer_pola_do_ruchu) && (zbijanie_prawo_dol == true)) || (((pionek[indeks_pionka].pole - 22) == numer_pola_do_ruchu) && (zbijanie_lewo_dol == true)))
                {
                    //ustawienie pola pionka zbijanego na 0

                    if ((((pionek[indeks_pionka].pole + 22) == numer_pola_do_ruchu) && (zbijanie_prawo_gora == true)))
                    {
                        int h = sprawdz_indeks_pionka((pionek[indeks_pionka].pole + 11));
                        if (h == -1)
                            goto podano_zle_pole_do_ruchu;
                        else
                            pionek[h].pole = 0;
                    }
                    else if ((((pionek[indeks_pionka].pole + 18) == numer_pola_do_ruchu) && (zbijanie_lewo_gora == true)))
                    {
                        int h = sprawdz_indeks_pionka((pionek[indeks_pionka].pole + 9));
                        if (h == -1)
                            goto podano_zle_pole_do_ruchu;
                        else
                            pionek[h].pole = 0;
                    }
                    else if ((((pionek[indeks_pionka].pole - 18) == numer_pola_do_ruchu) && (zbijanie_prawo_dol == true)))
                    {
                        int h = sprawdz_indeks_pionka((pionek[indeks_pionka].pole - 9));
                        if (h == -1)
                            goto podano_zle_pole_do_ruchu;
                        else
                            pionek[h].pole = 0;
                    }
                    else if ((((pionek[indeks_pionka].pole - 22) == numer_pola_do_ruchu) && (zbijanie_lewo_dol == true)))
                    {
                        int h = sprawdz_indeks_pionka((pionek[indeks_pionka].pole - 11));
                        if (h == -1)
                            goto podano_zle_pole_do_ruchu;
                        else
                            pionek[h].pole = 0;
                    }
                    else
                        goto podano_zle_pole_do_ruchu;

                    pionek[indeks_pionka].pole = numer_pola_do_ruchu;

                    aktualizuj_plansze();
                }
                else // nie wykonano ruchu
                    goto podano_zle_pole_do_ruchu;
            }

            if (pionek[indeks_pionka].typ == "damka")
            {
                bool wykonano_ruch = false;

                for (int i = 0; i < 32; i++)
                {
                    if (numer_pola_do_ruchu == pola_gdzie_damka_moze_sie_ruszyc[i])
                    {
                        // cout << "Ruch damki\n";
                        pionek[indeks_pionka].pole = pola_gdzie_damka_moze_sie_ruszyc[i];
                        aktualizuj_plansze();
                        wykonano_ruch = true;
                    }
                }

                if ((((pionek[id_pionka_ktory_moze_zbic_damka_pg].pole + 11) == numer_pola_do_ruchu) && (zbijanie_damka_pg == true)) || (((pionek[id_pionka_ktory_moze_zbic_damka_lg].pole + 9) == numer_pola_do_ruchu) && (zbijanie_damka_lg == true)) || (((pionek[id_pionka_ktory_moze_zbic_damka_pd].pole - 9) == numer_pola_do_ruchu) && (zbijanie_damka_pd == true)) || (((pionek[id_pionka_ktory_moze_zbic_damka_ld].pole - 11) == numer_pola_do_ruchu) && (zbijanie_damka_ld == true)))
                {
                    if ((((pionek[id_pionka_ktory_moze_zbic_damka_pg].pole + 11) == numer_pola_do_ruchu) && (zbijanie_damka_pg == true)))
                    {
                        pionek[id_pionka_ktory_moze_zbic_damka_pg].pole = 0;
                    }
                    if ((((pionek[id_pionka_ktory_moze_zbic_damka_lg].pole + 9) == numer_pola_do_ruchu) && (zbijanie_damka_lg == true)))
                    {
                        pionek[id_pionka_ktory_moze_zbic_damka_lg].pole = 0;
                    }
                    if ((((pionek[id_pionka_ktory_moze_zbic_damka_pd].pole - 9) == numer_pola_do_ruchu) && (zbijanie_damka_pd == true)))
                    {
                        pionek[id_pionka_ktory_moze_zbic_damka_pd].pole = 0;
                    }
                    if ((((pionek[id_pionka_ktory_moze_zbic_damka_ld].pole - 11) == numer_pola_do_ruchu) && (zbijanie_damka_ld == true)))
                    {
                        pionek[id_pionka_ktory_moze_zbic_damka_ld].pole = 0;
                    }

                    pionek[indeks_pionka].pole = numer_pola_do_ruchu;
                    aktualizuj_plansze();
                    wykonano_ruch = true;
                }

                if (wykonano_ruch == false)
                    goto podano_zle_pole_do_ruchu;
            }
        }
    }

    cout << endl;
}

//
//
//

void wykonaj_ruch(string nazwa_pola)
{
    int nr_pola = 0;
    int id_podanego_pionka = 0;

    wybrano_poprawnie_pionka_tury = false;

    nr_pola = sprawdz_numer_pola(nazwa_pola);
    if (nr_pola == 0)
        return;
    id_podanego_pionka = sprawdz_indeks_pionka(nr_pola);
    if (id_podanego_pionka == -1) // nie moze byc 0, bo to jest pierwszy indeks pionka
        return;

    for (int i = 0; i < 12; i++)
    {
        if (czyja_tura == true && id_podanego_pionka == i) // podano pionka białego w turze dla białych
        {
            wybrano_poprawnie_pionka_tury = true;
            ruch_pionka(nr_pola, id_podanego_pionka);
        }
    }

    for (int i = 12; i < 24; i++)
    {
        if (czyja_tura == false && id_podanego_pionka == i) // podanno pionka czarnego w turze dla czarnych
        {
            wybrano_poprawnie_pionka_tury = true;
            ruch_pionka(nr_pola, id_podanego_pionka);
        }
    }
}

//
//
//

void sprawdz_czy_jest_mozliwe_zbicie()
{
    mozliwe_bicie_bialych_komp = false;
    mozliwe_bicie_czarnych_komp = false;

    for (int i = 0; i < 24; i++)
    {
        lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i] = -1;
    }

    for (int i = 0; i < 24; i++)
    {
        istnienie_zbijanego_pionka_pg = false;
        istnienie_zbijanego_pionka_lg = false;
        istnienie_zbijanego_pionka_pd = false;
        istnienie_zbijanego_pionka_ld = false;

        zbijanie_damka_pg = false;
        zbijanie_damka_lg = false;
        zbijanie_damka_pd = false;
        zbijanie_damka_ld = false;

        zbijanie_prawo_gora = false;
        zbijanie_lewo_gora = false;
        zbijanie_prawo_dol = false;
        zbijanie_lewo_dol = false;

        if (pionek[i].pole != 0)
        {

            if (pionek[i].typ == "pionek")
            {
                zbijanie_prawo_gora = true;
                zbijanie_lewo_gora = true;
                zbijanie_prawo_dol = true;
                zbijanie_lewo_dol = true;

                sprawdz_mozliwe_bicie_pionka_krawedzie_funkcja(i);
                sprawdz_mozliwe_bicie_pionka_funkcja(pionek[i].pole);

                if ((zbijanie_prawo_gora == true && istnienie_zbijanego_pionka_pg == true) || (zbijanie_lewo_gora == true && istnienie_zbijanego_pionka_lg == true) || (zbijanie_prawo_dol == true && istnienie_zbijanego_pionka_pd == true) || (zbijanie_lewo_dol == true && istnienie_zbijanego_pionka_ld == true))
                {
                    if (i < 12) // komputer białe
                        mozliwe_bicie_bialych_komp = true;
                    else // komputer czarne
                        mozliwe_bicie_czarnych_komp = true;

                    lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i] = i;
                }
            }
            else if (pionek[i].typ == "damka")
            {

                sprawdz_mozliwe_ruchy_damki(i);
                sprawdz_mozliwe_bicia_damki(i);

                if (zbijanie_damka_pg == true || zbijanie_damka_lg == true || zbijanie_damka_ld == true || zbijanie_damka_pd == true)
                {
                    if (i < 12) // komputer białe
                        mozliwe_bicie_bialych_komp = true;
                    else // komputer czarne
                        mozliwe_bicie_czarnych_komp = true;

                    lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i] = i;
                }
            }
        }
    }

    // if (mozliwe_bicie_bialych_komp == true)
    //     cout << "\n\t\t\tBiale moga zbijac\n\n";
    // if (mozliwe_bicie_czarnych_komp == true)
    //     cout << "\n\t\t\tCzarne moga zbijac\n\n";
}

//
//
//

void wykonaj_ruch_komputera(int id)
{
    // getch();

    // numer_pola_do_ruchu_k
    // poprawy_ruch_komputera_k

    int numer_pola_do_ruchu = 0;
    bool poprawy_ruch_komputera = false;

podano_zle_pole_do_ruchu_K:

    if ((mozliwe_bicie_czarnych_komp == true && pionek[id].kolor == "czarny") || (mozliwe_bicie_bialych_komp == true && pionek[id].kolor == "bialy"))
    {

        if (pionek[id].typ == "pionek")
        {
            int los_ruchu = rand() % 4;
            if (los_ruchu == 0)
                numer_pola_do_ruchu = (pionek[id].pole + 22);
            if (los_ruchu == 1)
                numer_pola_do_ruchu = (pionek[id].pole + 18);
            if (los_ruchu == 2)
                numer_pola_do_ruchu = (pionek[id].pole - 22);
            if (los_ruchu == 3)
                numer_pola_do_ruchu = (pionek[id].pole - 18);

            for (int i = 0; i < 32; i++) // czy pole nie jest po za plansza
            {
                if (numer_pola_do_ruchu == wybrane_pole[i].pole)
                    poprawy_ruch_komputera = true;
            }

            zbijanie_prawo_gora = true;
            zbijanie_lewo_gora = true;
            zbijanie_prawo_dol = true;
            zbijanie_lewo_dol = true;

            sprawdz_mozliwe_bicie_pionka_krawedzie_funkcja(id);
            sprawdz_mozliwe_bicie_pionka_funkcja(pionek[id].pole);

            if ((((pionek[id].pole + 22) == numer_pola_do_ruchu) && (zbijanie_prawo_gora == true)))
            {
                int h = sprawdz_indeks_pionka((pionek[id].pole + 11));
                if (h == -1)
                    goto podano_zle_pole_do_ruchu_K;
                else
                    pionek[h].pole = 0;
            }
            else if ((((pionek[id].pole + 18) == numer_pola_do_ruchu) && (zbijanie_lewo_gora == true)))
            {
                int h = sprawdz_indeks_pionka((pionek[id].pole + 9));
                if (h == -1)
                    goto podano_zle_pole_do_ruchu_K;
                else
                    pionek[h].pole = 0;
            }
            else if ((((pionek[id].pole - 18) == numer_pola_do_ruchu) && (zbijanie_prawo_dol == true)))
            {
                int h = sprawdz_indeks_pionka((pionek[id].pole - 9));
                if (h == -1)
                    goto podano_zle_pole_do_ruchu_K;
                else
                    pionek[h].pole = 0;
            }
            else if ((((pionek[id].pole - 22) == numer_pola_do_ruchu) && (zbijanie_lewo_dol == true)))
            {
                int h = sprawdz_indeks_pionka((pionek[id].pole - 11));
                if (h == -1)
                    goto podano_zle_pole_do_ruchu_K;
                else
                    pionek[h].pole = 0;
            }
            else
            {
                goto podano_zle_pole_do_ruchu_K;
            }

            pionek[id].pole = numer_pola_do_ruchu; // ruch i zbicie (KOMP)

            aktualizuj_plansze();
        }
        else if (pionek[id].typ == "damka")
        {

            sprawdz_mozliwe_ruchy_damki(id);
            sprawdz_mozliwe_bicia_damki(id);

            int los_ruchu = rand() % 4;
            if (los_ruchu == 0)
                numer_pola_do_ruchu = (pionek[id_pionka_ktory_moze_zbic_damka_pg].pole + 11);
            if (los_ruchu == 1)
                numer_pola_do_ruchu = (pionek[id_pionka_ktory_moze_zbic_damka_lg].pole + 9);
            if (los_ruchu == 2)
                numer_pola_do_ruchu = (pionek[id_pionka_ktory_moze_zbic_damka_ld].pole - 11);
            if (los_ruchu == 3)
                numer_pola_do_ruchu = (pionek[id_pionka_ktory_moze_zbic_damka_pd].pole - 9);

            for (int i = 0; i < 32; i++) // czy pole nie jest po za plansza
            {
                if (numer_pola_do_ruchu == wybrane_pole[i].pole)
                    poprawy_ruch_komputera = true;
            }

            if ((((pionek[id_pionka_ktory_moze_zbic_damka_pg].pole + 11) == numer_pola_do_ruchu) && (zbijanie_damka_pg == true)))
            {
                pionek[id_pionka_ktory_moze_zbic_damka_pg].pole = 0;
            }
            else if ((((pionek[id_pionka_ktory_moze_zbic_damka_lg].pole + 9) == numer_pola_do_ruchu) && (zbijanie_damka_lg == true)))
            {
                pionek[id_pionka_ktory_moze_zbic_damka_lg].pole = 0;
            }
            else if ((((pionek[id_pionka_ktory_moze_zbic_damka_pd].pole - 9) == numer_pola_do_ruchu) && (zbijanie_damka_pd == true)))
            {
                pionek[id_pionka_ktory_moze_zbic_damka_pd].pole = 0;
            }
            else if ((((pionek[id_pionka_ktory_moze_zbic_damka_ld].pole - 11) == numer_pola_do_ruchu) && (zbijanie_damka_ld == true)))
            {
                pionek[id_pionka_ktory_moze_zbic_damka_ld].pole = 0;
            }
            else
                goto podano_zle_pole_do_ruchu_K;

            pionek[id].pole = numer_pola_do_ruchu; // ruch i zbicie (KOMP)
            aktualizuj_plansze();
        }
        if (poprawy_ruch_komputera == false)
            goto podano_zle_pole_do_ruchu_K;
    }
    else // ruch bez zbicia
    {
        if (pionek[id].typ == "pionek")
        {
            int los_ruchu = rand() % 2;
            if (pionek[id].kolor == "czarny")
            {
                if (los_ruchu == 0)
                    numer_pola_do_ruchu = (pionek[id].pole - 9);
                else if (los_ruchu == 1)
                    numer_pola_do_ruchu = (pionek[id].pole - 11);
            }
            else if (pionek[id].kolor == "bialy")
            {
                if (los_ruchu == 0)
                    numer_pola_do_ruchu = (pionek[id].pole + 9);
                else if (los_ruchu == 1)
                    numer_pola_do_ruchu = (pionek[id].pole + 11);
            }
        }
        else if (pionek[id].typ == "damka")
        {
            sprawdz_mozliwe_ruchy_damki(id);
            vector<int> pola_damki_komputera;
            for (int i = 0; i < 32; i++)
            {
                if (pola_gdzie_damka_moze_sie_ruszyc[i] != 0)
                    pola_damki_komputera.push_back(pola_gdzie_damka_moze_sie_ruszyc[i]);
            }

            int los_ruchu = rand() % pola_damki_komputera.size();
            numer_pola_do_ruchu = pola_damki_komputera[los_ruchu];
        }

        if (sprawdz_indeks_pionka(numer_pola_do_ruchu) != -1)
            goto podano_zle_pole_do_ruchu_K;

        for (int i = 0; i < 32; i++) // czy pole nie jest po za plansza
        {
            if (numer_pola_do_ruchu == wybrane_pole[i].pole)
                poprawy_ruch_komputera = true;
        }

        if (poprawy_ruch_komputera == true)
        {
            if (pionek[id].typ == "pionek")
            {
                if (((pionek[id].pole + 11) == numer_pola_do_ruchu) || ((pionek[id].pole + 9) == numer_pola_do_ruchu) || ((pionek[id].pole - 11) == numer_pola_do_ruchu) || ((pionek[id].pole - 9) == numer_pola_do_ruchu))
                {
                    pionek[id].pole = numer_pola_do_ruchu; // Ruch pionka (KOMPUTER)
                    aktualizuj_plansze();
                }
                else // nie wykonano ruchu
                    goto podano_zle_pole_do_ruchu_K;
            }

            if (pionek[id].typ == "damka")
            {
                bool wykonano_ruch = false;

                for (int i = 0; i < 32; i++)
                {
                    if (numer_pola_do_ruchu == pola_gdzie_damka_moze_sie_ruszyc[i])
                    {
                        pionek[id].pole = pola_gdzie_damka_moze_sie_ruszyc[i]; //Ruch damki (KOMPUTER)
                        aktualizuj_plansze();
                        wykonano_ruch = true;
                    }
                }

                if (wykonano_ruch == false)
                    goto podano_zle_pole_do_ruchu_K;
            }
        }
        else // poprawy_ruch_komputera== false
            goto podano_zle_pole_do_ruchu_K;
    }
}

//
//
//

void ile_mozliwych_ruchow_pionkow_funkcja(int indeks_pionka)
{
    ruch_w_prawo_gora = true; // przy wywolaniu funkcji te parametry musza sie resetowac
    ruch_w_lewo_gora = true;
    ruch_w_prawo_dol = true;
    ruch_w_lewo_dol = true;

    int pole_pionka = pionek[indeks_pionka].pole;

    sprawdz_mozliwy_ruch_pionka_krawedzie_funkcja(indeks_pionka);

    if (pionek[indeks_pionka].kolor == "bialy")
        sprawdz_mozliwy_ruch_pionka_bialego_funkcja(pole_pionka);
    else if (pionek[indeks_pionka].kolor == "czarny")
        sprawdz_mozliwy_ruch_pionka_czarnego_funkcja(pole_pionka);

    if (ruch_w_prawo_gora == true)
        ile_mozliwych_ruchow_bialych++;

    if (ruch_w_lewo_gora == true)
        ile_mozliwych_ruchow_bialych++;

    if (ruch_w_prawo_dol == true)
        ile_mozliwych_ruchow_czarnych++;

    if (ruch_w_lewo_dol == true)
        ile_mozliwych_ruchow_czarnych++;
}

//
//
//

void sprawdz_czy_jest_mozliwy_ruch()
{
    mozliwy_ruch_bialych = true;
    mozliwy_ruch_czarnych = true;
    ile_mozliwych_ruchow_bialych = 0;
    ile_mozliwych_ruchow_czarnych = 0;

    for (int i = 0; i < 24; i++)
    {
        lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] = -1; // -1 bo 0 to indeks pierwszego pionka
    }

    for (int i = 0; i < 24; i++) // sprawdza mozliwe ruchy pionkow
    {
        if (pionek[i].pole != 0) // odrzuca to zbite pionki. Pole zbitych pionkow bedzie ustawiane na 0
        {
            if (pionek[i].typ == "pionek")
            {
                ile_mozliwych_ruchow_pionkow_funkcja(i);

                if (ruch_w_prawo_gora == true || ruch_w_lewo_gora == true || ruch_w_prawo_dol == true || ruch_w_lewo_dol == true)
                    lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] = i;
            }
            else if (pionek[i].typ == "damka") // sprawdza mozliwe ruchy damek
            {
                if (pionek[i].kolor == "bialy")
                {
                    sprawdz_mozliwe_ruchy_damki(i);

                    for (int k = 0; k < 32; k++)
                    {
                        if (pola_gdzie_damka_moze_sie_ruszyc[k] != 0)
                        {
                            ile_mozliwych_ruchow_bialych++;
                            lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] = i;
                        }
                    }
                }
                else if (pionek[i].kolor == "czarny")
                {
                    sprawdz_mozliwe_ruchy_damki(i);

                    for (int k = 0; k < 32; k++)
                    {
                        if (pola_gdzie_damka_moze_sie_ruszyc[k] != 0)
                        {
                            ile_mozliwych_ruchow_czarnych++;
                            lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] = i;
                        }
                    }
                }
            }
        }
    }

    if (ile_mozliwych_ruchow_bialych == 0)
        mozliwy_ruch_bialych = false;
    if (ile_mozliwych_ruchow_czarnych == 0)
        mozliwy_ruch_czarnych = false;

    // cout << "\n   1/0 biale --> " << mozliwy_ruch_bialych << "    1/0 czarne --> " << mozliwy_ruch_czarnych;
    // cout << "\n   ile biale --> " << ile_mozliwych_ruchow_bialych << "    ile czarne --> " << ile_mozliwych_ruchow_czarnych << "\n\n";

    // cout << "indeksy pionkow i damek, ktore moga wykonac ruch:\n";
    // for (int i = 0; i < 24; i++)
    // {
    //     if (lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] != -1) // -1 bo 0 to indeks pierwszego pionka
    //         cout << "   " << lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] << "\t" << i << "\t" << pionek[i].kolor << "\t" << pionek[i].typ << "\n";
    // }
}

//
//
//

void sprawdz_zakonczenie_gry()
{
    zamiana_pionka_na_damke();
    sprawdz_czy_jest_mozliwy_ruch();
    sprawdz_czy_jest_mozliwe_zbicie();

    bool czy_sa_biale_pionki_na_planszy = false, czy_sa_czarne_pionki_na_planszy = false;
    for (int i = 0; i < 24; i++)
    {
        if (i < 12 && czy_sa_biale_pionki_na_planszy == false) // biale
        {
            if (pionek[i].pole != 0)
                czy_sa_biale_pionki_na_planszy = true;
        }
        else if (i >= 12 && czy_sa_czarne_pionki_na_planszy == false) // czarne
        {
            if (pionek[i].pole != 0)
                czy_sa_czarne_pionki_na_planszy = true;
        }
    }

    if (mozliwe_bicie_bialych_komp == false && mozliwe_bicie_czarnych_komp == false)
    {
        bool napis_resetu = false;

        if (czy_sa_biale_pionki_na_planszy == true && czy_sa_czarne_pionki_na_planszy == true) // wyłączenie tych opcji przy możliwym wykonaniu zbicia
        {

            if (mozliwy_ruch_bialych == false && mozliwy_ruch_czarnych == false)
            {
                sprawdz_pole = "0";
                napis_resetu = true;
                cout << "\n\tRemis, biale i czarne pionki nie moga wykonac ruchu\n\n";
                ustawienie_pionkow_na_planszy();
            }
            else if (mozliwy_ruch_bialych == false && mozliwy_ruch_czarnych == true)
            {
                sprawdz_pole = "0";
                napis_resetu = true;
                cout << "\n\tbiale pionki nie moga wykonac ruchu\n\n";
                ustawienie_pionkow_na_planszy();
            }
            else if (mozliwy_ruch_bialych == true && mozliwy_ruch_czarnych == false)
            {
                sprawdz_pole = "0";
                napis_resetu = true;
                cout << "\n\tczarne pionki nie moga wykonac ruchu\n\n";
                ustawienie_pionkow_na_planszy();
            }
        }
        else if (czy_sa_biale_pionki_na_planszy == true && czy_sa_czarne_pionki_na_planszy == false)
        {
            sprawdz_pole = "0";
            napis_resetu = true;
            cout << "\n\tbiale pionki wygraly\n\n";
            ustawienie_pionkow_na_planszy();
        }
        else if (czy_sa_biale_pionki_na_planszy == false && czy_sa_czarne_pionki_na_planszy == true)
        {
            sprawdz_pole = "0";
            napis_resetu = true;
            cout << "\n\tczarne pionki wygraly\n\n";
            ustawienie_pionkow_na_planszy();
        }

        if (napis_resetu == true)
        {
            cout << "\n\t\tRESET GRY\n\n";
            Sleep(3000);
        }
    }
}

//
//
//

void wywolanie_ruchu_komputera()
{
    sprawdz_czy_jest_mozliwy_ruch();
    sprawdz_czy_jest_mozliwe_zbicie();

    int lista_id_ruchow_k[12];
    int n_los = 0;

    for (int i = 0; i < 12; i++)
    {
        lista_id_ruchow_k[i] = -1;
    }

    int los_id = -1;

blad_w_los:

    if (czyja_tura == false)
    {
        if (mozliwe_bicie_czarnych_komp == false)
        {
            int ii = 0;
            for (int i = 12; i < 24; i++)
            {
                if (lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] != -1)
                {
                    lista_id_ruchow_k[ii] = lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i];
                    ii++;
                    n_los++;
                }
            }
            los_id = rand() % n_los;
        }
        else if (mozliwe_bicie_czarnych_komp == true)
        {
            int ii = 0;
            for (int i = 12; i < 24; i++)
            {
                if (lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i] != -1)
                {
                    lista_id_ruchow_k[ii] = lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i];
                    ii++;
                    n_los++;
                }
            }
            los_id = rand() % n_los;
        }
    }

    if (czyja_tura == true)
    {

        if (mozliwe_bicie_bialych_komp == false)
        {
            int ii = 0;
            for (int i = 0; i < 12; i++)
            {
                if (lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] != -1)
                {
                    lista_id_ruchow_k[ii] = lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i];
                    ii++;
                    n_los++;
                }
            }
            los_id = rand() % n_los;
        }
        else if (mozliwe_bicie_bialych_komp == true)
        {
            int ii = 0;
            for (int i = 0; i < 12; i++)
            {
                if (lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i] != -1)
                {
                    lista_id_ruchow_k[ii] = lista_indeksow_p_i_d_ktore_moga_wykonac_zbicie[i];
                    ii++;
                    n_los++;
                }
            }
            los_id = rand() % n_los;
        }
    }

    if (los_id < 0)
        goto blad_w_los;

    //cout << "\n\n\t n_los " << n_los << "\t los_id " << los_id << "\t pionek o wylos. id " << lista_id_ruchow_k[los_id] << "\n";

    wykonaj_ruch_komputera(lista_id_ruchow_k[los_id]);

    sprawdz_zakonczenie_gry();

    czyja_tura = !czyja_tura; // zmiana tury
}

//
//
//

void GraczVsGracz()
{
    aktualizuj_plansze();
    mozliwy_ruch = false;
    mozliwe_bicie = false;

    bool zabezp_przed_anul_ruch = true;

    while (sprawdz_pole != "0") // wyjście z gry turowej
    {
        zabezp_przed_anul_ruch = true;

    powtorka_ruchu_turowego:

        if (czyja_tura == true)
            cout << "Ruch bialych\n";
        else if (czyja_tura == false)
            cout << "Ruch czarnych\n";

        cout << "Podaj pole pionka: ";
        cin >> sprawdz_pole;

        if (sprawdz_pole != "exit" && sprawdz_pole != "0") // przerwanie ruchu
        {
            wykonaj_ruch(sprawdz_pole);

            if ((mozliwy_ruch == false && mozliwe_bicie == false) || wybrano_poprawnie_pionka_tury == false)
            {
                cout << "Wybrany pionek nie moze wykonac ruchu lub nie znaleziono pionka!\n";
                Sleep(1000);
                aktualizuj_plansze();
                goto powtorka_ruchu_turowego;
            }
            mozliwy_ruch = false;
            mozliwe_bicie = false;
        }

        if (nazwa_pola_f2 == "0")
        {
            aktualizuj_plansze();
            zabezp_przed_anul_ruch = false;
        }

        sprawdz_zakonczenie_gry();

        if (zabezp_przed_anul_ruch == true)
            czyja_tura = !czyja_tura; // zmiana tury
    }
}

//
//
//

void GraczVsKomputer()
{
    aktualizuj_plansze();
    mozliwy_ruch = false;
    mozliwe_bicie = false;

    bool zabezp_przed_anul_ruch = true;

    while (sprawdz_pole != "0") // wyjście z gry turowej
    {
        zabezp_przed_anul_ruch = true;

        if (czyja_tura == true) // ruch gracza
        {

        powtorka_ruchu_turowego_GvsK:
            cout << "Ruch bialych, gracza\n";
            cout << "Podaj pole pionka: ";
            cin >> sprawdz_pole;

            if (sprawdz_pole != "exit" && sprawdz_pole != "0") // przerwanie ruchu
            {
                wykonaj_ruch(sprawdz_pole);

                if ((mozliwy_ruch == false && mozliwe_bicie == false) || wybrano_poprawnie_pionka_tury == false)
                {
                    cout << "Wybrany pionek nie moze wykonac ruchu lub nie znaleziono pionka! (G vs. K)\n";
                    Sleep(1000);
                    aktualizuj_plansze();
                    goto powtorka_ruchu_turowego_GvsK;
                }
                mozliwy_ruch = false;
                mozliwe_bicie = false;
            }

            if (nazwa_pola_f2 == "0")
            {
                aktualizuj_plansze();
                zabezp_przed_anul_ruch = false;
            }

            sprawdz_zakonczenie_gry();

            if (zabezp_przed_anul_ruch == true)
                czyja_tura = !czyja_tura; // zmiana tury na komputera
        }

        else if (czyja_tura == false) // ruch komputera - czarne pionki
        {
            cout << "Ruch czarnych, komputera\n";
            Sleep(1500);
            wywolanie_ruchu_komputera();
        }
    }
}

//
//
//

void KomputerVsKomputer()
{
    int tempo_gry = 50;

    aktualizuj_plansze();

    while (sprawdz_pole != "0") // pętla gry komputerów
    {
        // getch();

        if (czyja_tura == true) // ruch komputera 1 - biale
        {
            cout << "Ruch bialych, komputera 1\n";
            Sleep(tempo_gry);

            wywolanie_ruchu_komputera();
        }

        else if (czyja_tura == false) // ruch komputera 2 - czarne
        {
            cout << "Ruch czarnych, komputera 2\n";
            Sleep(tempo_gry);

            wywolanie_ruchu_komputera();
        }
    }
}

//
//
//
//
//
//

int main()
{
    srand(time(nullptr));

    //---------------------------------------------------------------- ustawienia pod sprawdzanie pionka na polu na planszy przez gracza

    {
        int n = 11;
        for (int i = 0; i < 32; i++)
        {
            if (i == 4)
                n = 22;
            else if (i == 8)
                n = 31;
            else if (i == 12)
                n = 42;
            else if (i == 16)
                n = 51;
            else if (i == 20)
                n = 62;
            else if (i == 24)
                n = 71;
            else if (i == 28)
                n = 82;

            wybrane_pole[i].pole = n; // do wybierania pionka/pola przez gracza
            n += 2;
        }
    }

    wybrane_pole[0].nazwa_pola = "A1";
    wybrane_pole[1].nazwa_pola = "C1";
    wybrane_pole[2].nazwa_pola = "E1";
    wybrane_pole[3].nazwa_pola = "G1";

    wybrane_pole[4].nazwa_pola = "B2";
    wybrane_pole[5].nazwa_pola = "D2";
    wybrane_pole[6].nazwa_pola = "F2";
    wybrane_pole[7].nazwa_pola = "H2";

    wybrane_pole[8].nazwa_pola = "A3";
    wybrane_pole[9].nazwa_pola = "C3";
    wybrane_pole[10].nazwa_pola = "E3";
    wybrane_pole[11].nazwa_pola = "G3";

    wybrane_pole[12].nazwa_pola = "B4";
    wybrane_pole[13].nazwa_pola = "D4";
    wybrane_pole[14].nazwa_pola = "F4";
    wybrane_pole[15].nazwa_pola = "H4";

    wybrane_pole[16].nazwa_pola = "A5";
    wybrane_pole[17].nazwa_pola = "C5";
    wybrane_pole[18].nazwa_pola = "E5";
    wybrane_pole[19].nazwa_pola = "G5";

    wybrane_pole[20].nazwa_pola = "B6";
    wybrane_pole[21].nazwa_pola = "D6";
    wybrane_pole[22].nazwa_pola = "F6";
    wybrane_pole[23].nazwa_pola = "H6";

    wybrane_pole[24].nazwa_pola = "A7";
    wybrane_pole[25].nazwa_pola = "C7";
    wybrane_pole[26].nazwa_pola = "E7";
    wybrane_pole[27].nazwa_pola = "G7";

    wybrane_pole[28].nazwa_pola = "B8";
    wybrane_pole[29].nazwa_pola = "D8";
    wybrane_pole[30].nazwa_pola = "F8";
    wybrane_pole[31].nazwa_pola = "H8";

    //------------------------------------------------

    ustawienie_pionkow_na_planszy(); // pierwsze ustawienie

    //------------------------------------------------

    system("cls");
    cout << endl;
    cout << "                                             __       __             __           " << endl;
    cout << "                        |    |      /\\      |  \\    /         /\\    |  \\   \\  /   " << endl;
    cout << "                        |    |     /  \\     | _/   |         /  \\   |__/    \\/    " << endl;
    cout << "                        | /\\ |    /----\\    | \\    |        /____\\  |  \\    |     " << endl;
    cout << "                        |/  \\|   /      \\   |  \\    \\___   /      \\ |__/    |     " << endl;
    cout << endl;
    cout << "                                 Nacisnij dowolny przycisk aby zaczac             " << endl;
    _getch();
    system("cls");

    while (wybor != "exit" && wybor != "0")
    {
        sprawdz_pole = " ";

        system("cls");

        cout << endl;
        cout << "                                             __       __             __           " << endl;
        cout << "                        |    |      /\\      |  \\    /         /\\    |  \\   \\  /   " << endl;
        cout << "                        |    |     /  \\     | _/   |         /  \\   |__/    \\/    " << endl;
        cout << "                        | /\\ |    /----\\    | \\    |        /____\\  |  \\    |     " << endl;
        cout << "                        |/  \\|   /      \\   |  \\    \\___   /      \\ |__/    |     " << endl;
        cout << endl;

        cout << "                                         \n";
        cout << "nacisnij \"1\" aby ZACZAC GRE" << endl
             << endl;
        cout << "\"reset\" lub 2  - reset gry" << endl
             << endl;
        cout << "\"exit\" lub 0 - wyjdz z gry" << endl;
        //
        //

        cin >> wybor;

        if (wybor == "reset" || wybor == "2")
        {
            system("cls");
            ustawienie_pionkow_na_planszy();
        }
        //----------------------------------------------------------------------------------------------------------------------------------------- GRA TUROWA

        else if (wybor == "1") // gra turowa, "0" aby z niej wyjść
        {
            kto_gra = "0";
            while (kto_gra != "1" && kto_gra != "2" && kto_gra != "3") // kto_gra != "1" && kto_gra != "2" && kto_gra != "3"
            {
                system("cls");
                cout << "Podaj kto gra:\n gracz vs. gracz - 1\n gracz vs. komputer - 2 \n komputer vs. komputer - 3 \n";
                cin >> kto_gra;
                cout << kto_gra << endl;
            }

            czyja_tura = true; // "true" - ruch bialych, "false" - ruch czarnych,   białe zaczynają gre

            if (kto_gra == "1")
                GraczVsGracz();
            else if (kto_gra == "2")
                GraczVsKomputer();
            else if (kto_gra == "3")
                KomputerVsKomputer();
        }

        //----------------------------------------------------------------------------------------------------------------------------------------- GRA TUROWA
    }

    // _getch();
    return 0;
}
