//
// Na razie dzia³a sprawdzanie gdzie damka mo¿e siê ruszyæ
//

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <windows.h>

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
int numer_pola_gdzie_jest_pionek;
bool mozliwy_ruch = false;
bool mozliwe_bicie = false;

bool ruch_w_prawo_gora = true, ruch_w_lewo_gora = true, ruch_w_prawo_dol = true, ruch_w_lewo_dol = true;

//ZMIANY TUTAJJJJ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool zbijanie_prawo_gora = true, zbijanie_lewo_gora = true, zbijanie_prawo_dol = true, zbijanie_lewo_dol = true;
bool zbijanie_damka_pg = true, zbijanie_damka_lg = true, zbijanie_damka_pd = true, zbijanie_damka_ld = true;

//ZMIANY
bool istnienie_zbijanego_pionka_pg = false;
bool istnienie_zbijanego_pionka_lg = false;
bool istnienie_zbijanego_pionka_pd = false;
bool istnienie_zbijanego_pionka_ld = false;

int ile_mozliwych_ruchow_bialych = 0, ile_mozliwych_ruchow_czarnych = 0;

int *pola_gdzie_damka_moze_sie_ruszyc;
int liczba_ruchow_w_prawo_gora_damki = 0, liczba_ruchow_w_lewo_gora_damki = 0, liczba_ruchow_w_prawo_dol_damki = 0, liczba_ruchow_w_lewo_dol_damki = 0;

int id_pionka_ktory_moze_zbic_damka_pg = -1, id_pionka_ktory_moze_zbic_damka_pd = -1, id_pionka_ktory_moze_zbic_damka_lg = -1, id_pionka_ktory_moze_zbic_damka_ld = -1;

//
// biale pioneki: \2, damki: \3
//
// czarne pionki: \1, damki: \6
//

//      -------------------------------
//    8 |   82      84      86      88|
//    7 |71     73      75      77    |
//    6 |   62      64      66      68|
//    5 |51     53      55      57    |
//    4 |   42      44      46      48|
//    3 |31     33      35      37    |
//    2 |   22      24      26      28|
//    1 |11     13      15      17    |
//      -------------------------------
//       A   B   C   D   E   F   G   H

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
//
//
//
//
//
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
//
//
//
//
//
//
//
//
//
//
//

void aktualizuj_plansze()
{
    int n = 11;

    system("cls");

    ////////////////////////////////////////////////////////////////////////////////// prze³o¿yæ to póŸniej do funkcji zamieniaj¹cej pionka na damke
    //////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < 24; i++)
    {
        if (pionek[i].typ == "damka")
        {
            if (i < 12)
                pionek[i].znak = "\3"; // dla bialych
            else
                pionek[i].znak = "\6"; // dla czarnych
        }
    }
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

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
//
//
//
//
//
//
//
//
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
//
//
//
//
//
//
//
//
//
//
//

int sprawdz_indeks_pionka(int nr_pola) // funkcja sprawdza czy na podanym polu znajduje sie pionek, jezeli tak to zwraca jego inkeds(id),
{                                      //                                      jezeli nie ma tam pionka to zwraca 0
    int id_pola = -1;

    for (int j = 0; j < 24; j++) // to jest na razie dla wszystkich pionkow. Pozniej podzielic na biale i czarne
    {
        if (nr_pola == pionek[j].pole)
        {
            id_pola = j;
            cout << "Na wybranym polu zajduje sie " << pionek[j].typ << " " << pionek[j].kolor << " o indeksie " << j << endl;
        }
    }

    return id_pola;
}

//ZMIANY!!!
//sprawdza jaki kolor jest na polu
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
//
//
//
//
//
//
//
//
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

// ZMIANY!!!!!!!!!!!!!!!!!!!!!!!
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

//ZMIANYY!!!!!!!!!!!
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

        if (((pole_pionka - 9) == pionek[i].pole) && (zbijanie_prawo_dol = true))
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
//
//
//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    pola_gdzie_damka_moze_sie_ruszyc = new int[32]; // ta tablica nie usuwa sie wraz z koncem tej funkcji

    for (int i = 0; i < 32; i++)
    {
        pola_gdzie_damka_moze_sie_ruszyc[i] = 0; // wyczyszczenie komorek pamieci
    }

    int id_pionka = -1;
    int szukane_pole = 0;

    // ruch w prawo gora
    for (int rpg = 0; rpg < 7; rpg++) // maksymalna liczba ruchow damki po jednej przekatenej PRAWO GORA (DAMKA)
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
                else // id_pionka != -1
                {
                    rpg = 8;
                    id_pionka_ktory_moze_zbic_damka_pg = id_pionka;
                    // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                }
            }
        }
    }
    cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_prawo_gora_damki << " ruchow w prawo gora   -- ta czynnosc jeszcze nie uwzglednia bicia!\n";

    // ruch w lewo gora
    for (int rlg = 0; rlg < 7; rlg++) // maksymalna liczba ruchow damki po jednej przekatenej LEWO GORA (DAMKA)
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
    cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_lewo_gora_damki << " ruchow w lewo gora   -- ta czynnosc jeszcze nie uwzglednia bicia!\n";

    // ruch w prawy dol
    for (int rpd = 0; rpd < 7; rpd++) // maksymalna liczba ruchow damki po jednej przekatenej PRAWO DOL (DAMKA)
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
    cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_prawo_dol_damki << " ruchow w prawo dol   -- ta czynnosc jeszcze nie uwzglednia bicia!\n";

    // ruch w lewy dol
    for (int rld = 0; rld < 7; rld++) // maksymalna liczba ruchow damki po jednej przekatenej LEWO DOL (DAMKA)
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
    cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_lewo_dol_damki << " ruchow w lewo dol   -- ta czynnosc jeszcze nie uwzglednia bicia!\n\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sprawdz_mozliwe_bicia_damki(int indeks_pionka)
{
    //sprawdzanie czy w pg jest pionek ktorego mozna zbic///////////////////////////////////////
    if (id_pionka_ktory_moze_zbic_damka_pg == -1)
    {
        zbijanie_damka_pg = false;
    }
    //jesli jest, to sprawdzamy czy na polu za nim znajduje sie pionek
    else
    {
       for (int h = 0; h<24; h++)
       {
         if((pionek[id_pionka_ktory_moze_zbic_damka_pg].pole + 11) == pionek[h].pole)
        {
            zbijanie_damka_pg = false;
        }
       }
       //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
       if((pionek[id_pionka_ktory_moze_zbic_damka_pg].kolor == pionek[indeks_pionka].kolor))
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
       for (int h = 0; h<24; h++)
       {
         if((pionek[id_pionka_ktory_moze_zbic_damka_lg].pole + 9) == pionek[h].pole)
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
       for (int h = 0; h<24; h++)
       {
         if((pionek[id_pionka_ktory_moze_zbic_damka_pd].pole - 9) == pionek[h].pole)
        {
            zbijanie_damka_pd = false;
        }
       }
        //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
       if(pionek[id_pionka_ktory_moze_zbic_damka_pg].kolor == pionek[indeks_pionka].kolor)
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
       for (int h = 0; h<24; h++)
       {
         if((pionek[id_pionka_ktory_moze_zbic_damka_ld].pole - 11) == pionek[h].pole)
        {
            zbijanie_damka_ld = false;
        }
       }
        //sprawdzamy czy kolor pionka ktorego chcemy zbic jest przeciwny
       if(pionek[id_pionka_ktory_moze_zbic_damka_ld].kolor == pionek[indeks_pionka].kolor)
       {
           zbijanie_damka_ld = false;
       }
    }

    if (zbijanie_damka_pg == true)
        cout << "damka MOZE zbijac prawogora" << endl;
    else
        cout << "damka nie moze zbijac prawogora" << endl;
    if (zbijanie_damka_lg == true)
        cout << "damka MOZE zbijac lewogora" << endl;
     else
        cout << "damka nie moze zbijac lewogora" << endl;
    if (zbijanie_damka_pd == true)
        cout << "damka MOZE zbijac prawodol" << endl;
     else
        cout << "damka nie moze zbijac prawodol" << endl;
    if (zbijanie_damka_ld == true)
        cout << "damka MOZE zbijac lewodol" << endl;
     else
        cout << "damka nie moze zbijac lewodol" << endl;
}
//
//
//
//
//
//
//
//
//
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

        //ZMIANYY TUTAJ!!!
        zbijanie_prawo_gora = true,
        zbijanie_lewo_gora = true,
        zbijanie_prawo_dol = true,
        zbijanie_lewo_dol = true;

        istnienie_zbijanego_pionka_pg = false;
        istnienie_zbijanego_pionka_lg = false;
        istnienie_zbijanego_pionka_pd = false;
        istnienie_zbijanego_pionka_ld = false;
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

    string nazwa_pola_f2;
    int numer_pola_do_ruchu = 0;

    sprawdz_mozliwy_ruch_pionka_krawedzie_funkcja(indeks_pionka);
    //ZMIANYYYYY
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

    // dzia³a i nie chce mi siê tego zmieniaæ
    //  ||
    //  ||
    //  \/

    else if (pionek[indeks_pionka].typ == "damka") // DAMKI SPRAWDZANIE RUCHU
        sprawdz_mozliwe_ruchy_damki(indeks_pionka);
        sprawdz_mozliwe_bicia_damki(indeks_pionka);

    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //

    // dla pionkow
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
            cout << "Pionek NIE moze ruszyc sie w LEWO W DOL\n";

        //BICIE!!!
        if (zbijanie_prawo_gora == true && istnienie_zbijanego_pionka_pg == true)
            cout << "Pionek MOZE zbijać w PRAWO DO GORY\n";
        else
            cout << "Pionek NIE może zbijać w PRAWO DO GORY\n";

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

    //if (mozliwe_bicie ==true)
    //{
    //    mozliwy_ruch = false;
    //}
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
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
                goto podano_zle_pole_do_ruchu;

            for (int i = 0; i < 24; i++)
            {
                if (numer_pola_do_ruchu == pionek[i].pole)
                    goto podano_zle_pole_do_ruchu;
            }

            if (pionek[indeks_pionka].typ == "pionek")
            {
                if ((((pionek[indeks_pionka].pole + 11) == numer_pola_do_ruchu) && (ruch_w_prawo_gora == true)) || (((pionek[indeks_pionka].pole + 9) == numer_pola_do_ruchu) && (ruch_w_lewo_gora == true)) || (((pionek[indeks_pionka].pole - 11) == numer_pola_do_ruchu) && (ruch_w_lewo_dol == true)) || (((pionek[indeks_pionka].pole - 9) == numer_pola_do_ruchu) && (ruch_w_prawo_dol == true)))
                {
                    cout << "Ruch pionka\n";
                    pionek[indeks_pionka].pole = numer_pola_do_ruchu;
                    aktualizuj_plansze();
                }
                //ZMIANY!!!! zbijanie
                else if ((((pionek[indeks_pionka].pole + 22) == numer_pola_do_ruchu) && (zbijanie_prawo_gora == true)) || (((pionek[indeks_pionka].pole + 18) == numer_pola_do_ruchu) && (zbijanie_lewo_gora == true)) || (((pionek[indeks_pionka].pole - 18) == numer_pola_do_ruchu) && (zbijanie_prawo_dol == true)) || (((pionek[indeks_pionka].pole - 22) == numer_pola_do_ruchu) && (zbijanie_lewo_dol == true)))
                {

                    //ustawienie pola pionka zbijanego na 0

                    if ((((pionek[indeks_pionka].pole + 22) == numer_pola_do_ruchu) && (zbijanie_prawo_gora == true)))
                    {
                        pionek[sprawdz_indeks_pionka((pole_pionka + 11))].pole = 0;
                    }
                    if ((((pionek[indeks_pionka].pole + 18) == numer_pola_do_ruchu) && (zbijanie_lewo_gora == true)))
                    {
                        pionek[sprawdz_indeks_pionka((pole_pionka + 9))].pole = 0;
                    }
                    if ((((pionek[indeks_pionka].pole - 18) == numer_pola_do_ruchu) && (zbijanie_prawo_dol == true)))
                    {
                        pionek[sprawdz_indeks_pionka((pole_pionka - 9))].pole = 0;
                    }
                    if ((((pionek[indeks_pionka].pole - 22) == numer_pola_do_ruchu) && (zbijanie_lewo_dol == true)))
                    {
                        pionek[sprawdz_indeks_pionka((pole_pionka - 11))].pole = 0;
                    }

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
                        cout << "Ruch damki\n";
                        pionek[indeks_pionka].pole = pola_gdzie_damka_moze_sie_ruszyc[i];
                        aktualizuj_plansze();
                        wykonano_ruch = true;
                    }
                }

                if (wykonano_ruch == false)
                    goto podano_zle_pole_do_ruchu;
            }
        }
    }
    delete[] pola_gdzie_damka_moze_sie_ruszyc;

    cout << endl;
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//

void wykonaj_ruch(string nazwa_pola)
{
    int nr_pola = 0;
    int id_pola = 0;

    nr_pola = sprawdz_numer_pola(nazwa_pola);
    if (nr_pola == 0)
        return;
    id_pola = sprawdz_indeks_pionka(nr_pola);
    if (id_pola == -1) // nie moze byc 0, bo to jest pierwszy indeks pionka
        return;

    ruch_pionka(nr_pola, id_pola);
}

//
//
//
//
//
//
//
//
//
//
//
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
//
//

void sprawdz_czy_jest_mozliwy_ruch()
{
    bool mozliwy_ruch_bialych = true, mozliwy_ruch_czarnych = true;
    ile_mozliwych_ruchow_bialych = 0;
    ile_mozliwych_ruchow_czarnych = 0;

    // int lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[24];
    int *lista_indeksow_p_i_d_ktore_moga_wykonac_ruch = new int[24];

    for (int i = 0; i < 24; i++)
    {
        lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] = 0;
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

    cout << "\n   1/0 biale --> " << mozliwy_ruch_bialych << "    1/0 czarne --> " << mozliwy_ruch_czarnych;
    cout << "\n   ile biale --> " << ile_mozliwych_ruchow_bialych << "    ile czarne --> " << ile_mozliwych_ruchow_czarnych << "\n\n";

    cout << "indeksy pionkow i damek, ktore moga wykonac ruch:\n";
    for (int i = 0; i < 24; i++)
    {
        if (lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] != 0)
            cout << "   " << lista_indeksow_p_i_d_ktore_moga_wykonac_ruch[i] << "\n";
    }

    delete[] lista_indeksow_p_i_d_ktore_moga_wykonac_ruch;
    delete[] pola_gdzie_damka_moze_sie_ruszyc;
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

int main()
{

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

    //-------------------------------------------------------------- ustawienia pod sprawdzanie pionka na polu na planszy przez gracza

    ustawienie_pionkow_na_planszy(); // pierwsze ustawienie

    //------------------------------------------------

    pionek[12].pole = 42;
    // pionek[13].pole = 44;
    // pionek[14].pole = 46;
    // pionek[15].pole = 48;

    pionek[13].typ = "damka";
    pionek[10].typ = "damka";
    pionek[11].typ = "damka";

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
    getch();
    system("cls");

    while (wybor != "exit" && wybor != "0")
    {
        cout << "----------------------------\n";
        cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\n";
        cout << "Aby zresetowac porgram \"reset\" lub 2\n";

        //
        //
        cout << "sprawdz mozliwosc ruchow -- 3\n";
        //
        //

        cin >> wybor;

        if (wybor == "start" || wybor == "1")
        {
            system("cls");
            aktualizuj_plansze(); // pierwsze ustawienie

        powtorka_ruchu:
            cout << "Podaj pole pionka: ";
            cin >> sprawdz_pole;

            if (sprawdz_pole != "exit" && sprawdz_pole != "0") // do przerwania podawania pola
            {
                wykonaj_ruch(sprawdz_pole);

                if (mozliwy_ruch == false && mozliwe_bicie == false)
                {
                    cout << "Wybrany pionek nie moze wykonac ruchu, bicia lub nie znaleziono pionka!\n";
                    goto powtorka_ruchu;
                }
                mozliwy_ruch = false;
                mozliwe_bicie = false;
            }
        }
        else if (wybor == "reset" || wybor == "2")
        {
            system("cls");
            ustawienie_pionkow_na_planszy();
        }
        else if (wybor == "3")
        {
            sprawdz_czy_jest_mozliwy_ruch();
        }
    }

    //--------------------------------------------------------------------------------------------------

    // getch();
    return 0;
}
