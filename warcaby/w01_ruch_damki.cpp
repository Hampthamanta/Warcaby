//
// Na razie działa sprawdzanie gdzie damka może się ruszyć
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
    string nazwa_pola;
};

plansza pionek[24];
plansza znak_na_polu[32];
plansza wybrane_pole[32];

string wybor;
string sprawdz_pole;
int numer_pola_gdzie_jest_pionek;
bool mozliwy_ruch = false;

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

void aktualizuj_plansze()
{
    int n = 11;

    system("cls");

    ////////////////////////////////////////////////////////////////////////////////// przełożyć to później do funkcji zamieniającej pionka na damke
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

void ruch_pionka(int pole_pionka, int indeks_pionka)
{

    // pole_pionka jest podane w fukcnji
    bool ruch_w_prawo_gora = true, ruch_w_lewo_gora = true, ruch_w_prawo_dol = true, ruch_w_lewo_dol = true;
    int liczba_ruchow_w_prawo_gora_damki = 0, liczba_ruchow_w_lewo_gora_damki = 0, liczba_ruchow_w_prawo_dol_damki = 0, liczba_ruchow_w_lewo_dol_damki = 0;
    int pola_gdzie_damka_moze_sie_ruszyc[32];

    for (int i = 0; i < 32; i++)
    {
        pola_gdzie_damka_moze_sie_ruszyc[i] = 0; // wyczyszczenie komurek pamieci
    }

    string nazwa_pola_f2;
    int numer_pola_do_ruchu = 0;

    if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 82)
    {
        ruch_w_prawo_gora = false;
        ruch_w_lewo_gora = false;
        cout << "Pionek NIE moze ruszyc sie DO GORY\n"; // gorana krawedz
    }
    if (pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 13 || pionek[indeks_pionka].pole == 15 || pionek[indeks_pionka].pole == 17)
    {
        ruch_w_prawo_dol = false;
        ruch_w_lewo_dol = false;
        cout << "Pionek NIE moze ruszyc sie W DOL\n"; // dolna krawedz
    }
    if (pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 28)
    {
        ruch_w_prawo_gora = false;
        ruch_w_prawo_dol = false;
        cout << "Pionek NIE moze ruszyc sie W PRAWO\n"; // prawa krawedz
    }
    if (pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 11)
    {
        ruch_w_lewo_gora = false;
        ruch_w_lewo_dol = false;
        cout << "Pionek NIE moze ruszyc sie W LEWO\n"; // lewa krawedz
    }

    if (pionek[indeks_pionka].kolor == "bialy" && pionek[indeks_pionka].typ == "pionek")
    {
        ruch_w_prawo_dol = false;
        ruch_w_lewo_dol = false;

        for (int i = 0; i < 24; i++)
        {

            if (ruch_w_prawo_gora == true && ((pole_pionka + 11) == pionek[i].pole))
            {
                ruch_w_prawo_gora = false;
                cout << "Pionek NIE moze ruszyc sie w PRAWO DO GORY\n";
            }
            if (ruch_w_lewo_gora == true && ((pole_pionka + 9) == pionek[i].pole))
            {
                ruch_w_lewo_gora = false;
                cout << "Pionek NIE moze ruszyc sie w LEWO DO GORY\n";
            }
        }
    }
    else if (pionek[indeks_pionka].kolor == "czarny" && pionek[indeks_pionka].typ == "pionek")
    {
        ruch_w_prawo_gora = false;
        ruch_w_lewo_gora = false;

        for (int i = 0; i < 24; i++)
        {

            if (ruch_w_prawo_dol == true && ((pole_pionka - 9) == pionek[i].pole))
            {
                ruch_w_prawo_dol = false;
                cout << "Pionek NIE moze ruszyc sie w PRAWO W DOL\n";
            }

            if (ruch_w_lewo_dol == true && ((pole_pionka - 11) == pionek[i].pole))
            {
                ruch_w_lewo_dol = false;
                cout << "Pionek NIE moze ruszyc sie w LEWO W DOL\n";
            }
        }
    }
    else if (pionek[indeks_pionka].typ == "damka") //////////////////////////////////////////////////////////////// DAMKI SPRAWDZANIE RUCHU
    {
        cout << "\nDAMKA\n";
        ruch_w_prawo_gora = false;
        ruch_w_prawo_dol = false;
        ruch_w_lewo_gora = false; // te sa do zwyklych pionkow
        ruch_w_lewo_dol = false;

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
                    else
                    {
                        rpg = 8;
                        // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                    }
                }
            }
        }
        cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_prawo_gora_damki << " ruchow w prawo gora   -- ta czynnosc jeszcze nie uwzglednia bicia!\n\n";

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
                        // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                    }
                }
            }
        }
        cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_lewo_gora_damki << " ruchow w lewo gora   -- ta czynnosc jeszcze nie uwzglednia bicia!\n\n";

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
                        // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                    }
                }
            }
        }
        cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_prawo_dol_damki << " ruchow w prawo dol   -- ta czynnosc jeszcze nie uwzglednia bicia!\n\n";

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
                        // cout << "\n                 koniec ruchow damki na polu " << pionek[id_pionka].pole << "    rzekoma przeszkoda jako pionek na tym polu " << id_pionka << "\n\n";
                    }
                }
            }
        }
        cout << "                         Wybrana damka moze wykonac " << liczba_ruchow_w_lewo_dol_damki << " ruchow w lewo dol   -- ta czynnosc jeszcze nie uwzglednia bicia!\n\n";

        //
        //   DODAC ZMIANE FLAGI mozliwy_ruch
        //

    } ///////////////////////////////////////////////////////////////////////////////// DAMKI SPRAWDZANIE RUCHU

    if (ruch_w_prawo_gora == true)
    {
        cout << "Pionek MOZE ruszyc sie w PRAWO DO GORY\n";
    }

    if (ruch_w_lewo_gora == true)
    {
        cout << "Pionek MOZE ruszyc sie w LEWO DO GORY\n";
    }

    if (ruch_w_prawo_dol == true)
    {
        cout << "Pionek MOZE ruszyc sie w PRAWO W DOL\n";
    }

    if (ruch_w_lewo_dol == true)
    {
        cout << "Pionek MOZE ruszyc sie w LEWO W DOL\n";
    }

    if (ruch_w_prawo_gora == true || ruch_w_lewo_gora == true || ruch_w_prawo_dol == true || ruch_w_lewo_dol == true)
        mozliwy_ruch = true;

    if (liczba_ruchow_w_lewo_dol_damki > 0 || liczba_ruchow_w_prawo_dol_damki > 0 || liczba_ruchow_w_lewo_gora_damki > 0 || liczba_ruchow_w_prawo_gora_damki > 0)
        mozliwy_ruch = true;

    if (mozliwy_ruch == true)
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
                else // nie wykonano ruchu
                    goto podano_zle_pole_do_ruchu;
            }

            ///////////////////////////////////////////////////////////////////////////////// DAMKI RUCH

            if (pionek[indeks_pionka].typ == "damka")
            {
                for (int i = 0; i < 32; i++)
                {
                    if (numer_pola_do_ruchu == pola_gdzie_damka_moze_sie_ruszyc[i])
                    {
                        cout << "Ruch damki\n";
                        pionek[indeks_pionka].pole = pola_gdzie_damka_moze_sie_ruszyc[i];
                        aktualizuj_plansze();
                    }
                }
            }

            ///////////////////////////////////////////////////////////////////////////////// DAMKI RUCH
        }
    }
    // else
    // {
    //     return;        //                       //        //         ???
    // }

    cout << endl;
}

void sprawdz_pozycje_pionka(string nazwa_pola)
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

int main()
{

    //-------------------------------------------------------------------------------------------------- ustawienia pod sprawdzanie pionka na polu na planszy przez gracza

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

    //-------------------------------------------------------------------------------------------------- ustawienia pod sprawdzanie pionka na polu na planszy przez gracza

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

    // for (int i = 0; i < 24; i++)
    // {
    //     cout << "   " << i << "   " << pionek[i].znak << "   " << pionek[i].kolor << "   " << pionek[i].typ << "   " << pionek[i].pole << endl;
    // }

    cout << endl;
    cout << "                                             __       __             __           " << endl;
    cout << "                        |    |      /\\      |  \\    /         /\\    |  \\   \\  /   " << endl;
    cout << "                        |    |     /  \\     | _/   |         /  \\   |__/    \\/    " << endl;
    cout << "                        | /\\ |    /----\\    | \\    |        /____\\  |  \\    |     " << endl;
    cout << "                        |/  \\|   /      \\   |  \\    \\___   /      \\ |__/    |     " << endl;
    cout << endl;
    cout << "                                 Nacisnij dowolny przycisk aby zaczac             " << endl;
    getch();

    ////////////////////////////////////////////////////////////////   TESTY
    //
    //  // ustawienia pionka do testow
    //

    for (int i = 0; i < 24; i++)
    {
        pionek[i].pole = 0;
    }

    pionek[13].typ = "damka";
    pionek[13].pole = 42;
    pionek[20].typ = "damka";
    pionek[20].pole = 17;
    pionek[18].typ = "damka";
    pionek[18].pole = 71;
    pionek[3].typ = "damka";
    pionek[3].pole = 11;
    pionek[10].typ = "damka";
    pionek[10].pole = 48;
    pionek[8].typ = "damka";
    pionek[8].pole = 82;
    pionek[5].pole = 66;

    //
    //
    ////////////////////////////////////////////////////////////////   TESTY

    while (wybor != "exit" && wybor != "0")
    {
        cout << "----------------------------\n";
        cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\n";
        cout << "Aby zresetowac porgram \"reset\" lub 2\n";
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
                sprawdz_pozycje_pionka(sprawdz_pole);

                if (mozliwy_ruch == false)
                {
                    cout << "Wybrany pionek nie moze wykonac ruchu lub nie znaleziono pionka!\n";
                    goto powtorka_ruchu;
                }
                mozliwy_ruch = false;
            }
        }
        else if (wybor == "reset" || wybor == "2")
        {
            system("cls");
        }
    }

    //--------------------------------------------------------------------------------------------------

    // pionek[0].pole = 51;
    // pionek[1].pole = 53;
    // pionek[2].pole = 55;
    // pionek[3].pole = 57;

    // pionek[20].pole = 42;
    // pionek[13].pole = 44;
    // pionek[14].pole = 46;
    // pionek[15].pole = 11;

    // aktualizuj_plansze();

    // getch();
    return 0;
}
