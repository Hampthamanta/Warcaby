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

plansza pionek[16];
plansza znak_na_polu[32];
plansza wybrane_pole[32];

string wybor;
string sprawdz_pole;
int numer_pola_gdzie_jest_pionek;
bool mozliwy_ruch = false;

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

    for (int k = 0; k < 32; k++)
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

        for (int j = 0; j < 16; j++)
        {
            if (pionek[j].pole == n)
                znak_na_polu[i].znak = pionek[j].znak;
        }

        n += 2;
    }

    cout << "\n      +---+---+---+---+---+---+---+---+\n";
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
    cout << "        A   B   C   D   E   F   G   H\n";
}

int sprawdz_numer_pola(string nazwa_pola_f)
{
    transform(nazwa_pola_f.begin(), nazwa_pola_f.end(), nazwa_pola_f.begin(), ::toupper);

    int nr_pola = 0;

    for (int i = 0; i < 32; i++)
    {
        if (nazwa_pola_f == wybrane_pole[i].nazwa_pola)
        {
            cout << "Wybrane pole " << wybrane_pole[i].nazwa_pola << " ma indeks na plaszny rowny " << wybrane_pole[i].pole << "\n";
            nr_pola = wybrane_pole[i].pole;
        }
    }

    return nr_pola;
}

int sprawdz_indeks_pionka(int nr_pola)
{
    int id_pola = 0;

    for (int j = 0; j < 16; j++) // to jest na razie dla wszystkich pionkow. Pozniej podzielic na biale i czarne
    {
        if (nr_pola == pionek[j].pole)
        {
            id_pola = j;
            cout << "Na wybranym polu zajduje sie " << pionek[j].typ << " " << pionek[j].kolor << " o indeksie " << j << endl;
            // przydzielenie gdzies nr_pola jako pola gdzie znajduje sie podany pionek oraz indeksu pionka
        }
    }

    return id_pola;
}

void ruch_pionka(int pole_pionka, int indeks_pionka)
{

    // pole_pionka jest podane w fukcnji
    bool ruch_w_prawo_gora = true, ruch_w_lewo_gora = true, ruch_w_prawo_dol = true, ruch_w_lewo_dol = true;
    bool znaleziono_pionka = false;

    bool zbijanie_prawo_gora = true, zbijanie_lewo_gora = true, zbijanie_prawo_dol = true, zbijanie_lewo_dol = true;

    for (int j = 0; j < 16; j++)
    {
        if (pole_pionka == pionek[j].pole)
        {
            indeks_pionka = j;
            znaleziono_pionka = true;
            // cout << "\n\n\n"
            //      << pionek[j].pole << "    " << pionek[j].kolor << "    " << pionek[j].typ << "\n\n\n";
        }
    }

    if (znaleziono_pionka == true)
    {
        string nazwa_pola_f2;
        int numer_pola_do_ruchu = 0;

        if (pionek[indeks_pionka].kolor == "bialy" && pionek[indeks_pionka].typ == "pionek")
        {
            ruch_w_prawo_dol = false;
            ruch_w_lewo_dol = false;
            zbijanie_prawo_dol = false;
            zbijanie_lewo_dol = false;

            for (int i = 0; i < 16; i++)
            {
                if (ruch_w_prawo_gora == true && ((pole_pionka + 11) == pionek[i].pole || pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 28))
                {
                    ruch_w_prawo_gora = false;
                    cout << "Pionek NIE moze ruszyc sie w PRAWO DO GORY\n";
                }
                if (ruch_w_lewo_gora == true && ((pole_pionka + 9) == pionek[i].pole || pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 11))
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

            for (int i = 0; i < 16; i++)
            {
                if (ruch_w_prawo_dol == true)
                {
                    if ((pole_pionka - 9) == pionek[i].pole || pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 28)
                    {
                        ruch_w_prawo_dol = false;
                        cout << "Pionek NIE moze ruszyc sie w PRAWO W DOL\n";
                    }
                }

                if (ruch_w_lewo_dol == true)
                {
                    if ((pole_pionka - 11) == pionek[i].pole || pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 11)
                    {
                        ruch_w_lewo_dol = false;
                        cout << "Pionek NIE moze ruszyc sie w LEWO W DOL\n";
                    }
                }
            }
        }

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

        if (ruch_w_lewo_dol == true || ruch_w_lewo_gora == true || ruch_w_prawo_dol == true || ruch_w_lewo_dol == true)
        {
            mozliwy_ruch = true;
        }

        if (mozliwy_ruch == true)
        {
            cout << "\n\nPodaj pole na planszy gdzie chesz ruszyc wybranego pionka: ";
            cin >> nazwa_pola_f2;
            numer_pola_do_ruchu = sprawdz_numer_pola(nazwa_pola_f2);

            if (pionek[indeks_pionka].typ == "pionek")
            {
                if ((pionek[indeks_pionka].pole + 11) == numer_pola_do_ruchu || (pionek[indeks_pionka].pole + 9) == numer_pola_do_ruchu || (pionek[indeks_pionka].pole - 11) == numer_pola_do_ruchu || (pionek[indeks_pionka].pole - 9) == numer_pola_do_ruchu)
                {
                    cout << "Ruch pionka\n";
                    pionek[indeks_pionka].pole = numer_pola_do_ruchu;
                    aktualizuj_plansze();
                }
            }
        }
    }
    else
    {
        cout << "Na tym polu nie ma rzadnego pionka!\n";
    }
    cout << endl;
}

// Zbijanie pionk�w

if (pionek[indeks_pionka].kolor == "bialy" && pionek[indeks_pionka].typ == "pionek")
{
    zbijanie_prawo_dol = false;
    zbijanie_lewo_dol = false;


    for (int i = 0; i < 16; i++)
    {    // sprawdzam pola na ktore po prostu nie moze sie ruszyc
        if (zbijanie_prawo_gora == true && (pole_pionka + 22) == pionek[i].pole || pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 82 || pionek[indeks_pionka].pole == 73 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 75 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 77 || pionek[indeks_pionka].pole == 88 || pionek[indeks_pionka].pole == 57 || pionek[indeks_pionka].pole == 68 || pionek[indeks_pionka].pole == 37 || pionek[indeks_pionka].pole == 48 || pionek[indeks_pionka].pole == 17 || pionek[indeks_pionka].pole == 28 )
        {
            // sprawdzanie czy stoi tam pionek
            if (zbijanie_prawo_gora == true && (pole_pionka + 11) == pionek[i].pole);
            {
                //co sie stanie jesli bedzie tam bialy pionek (sprawdza kt�ry pionek ma to pole i sprawdza jego kolor
                for (i = 0; i < 16; i++)
                {
                    if (pionek[i].pole == (pole_pionka + 11))
                    {
                        if (pionek[i].kolor == "bialy")
                        {
                            cout << "NIE MOZESZ ZBIC SWOJEGO PIONKA" << endl;
                            zbijanie_prawo_gora = false;
                            // tutaj musi wr�ci� do miejsca gdzie wybiera�o si� pole

                        } 
                        else
                        {
                            cout << "ZBIJASZ PIONKA PRZECIWNIKA" << endl;
                            pionek[i].pole == 0;
                        }
                    }
                }

            }
            
            zbijanie_prawo_gora = false;
            cout << "Pionek NIE moze zbija� w PRAWO DO GORY\n";
        }
        if (zbijanie_lewo_gora == true && (pole_pionka + 18) == pionek[i].pole || pionek[indeks_pionka].pole == 11 || pionek[indeks_pionka].pole == 22 || pionek[indeks_pionka].pole == 31 || pionek[indeks_pionka].pole == 42 || pionek[indeks_pionka].pole == 51 || pionek[indeks_pionka].pole == 62 || pionek[indeks_pionka].pole == 71 || pionek[indeks_pionka].pole == 82 || pionek[indeks_pionka].pole == 73 || pionek[indeks_pionka].pole == 84 || pionek[indeks_pionka].pole == 75 || pionek[indeks_pionka].pole == 86 || pionek[indeks_pionka].pole == 77 || pionek[indeks_pionka].pole == 88 )
        {
           zbijanie_lewo_gora = false;
            cout << "Pionek NIE moze zbija� w LEWO DO GORY\n";
        }
    }
}
}

void sprawdz_pozycje_pionka(string nazwa_pola)
{
    int nr_pola = 0;
    int id_pola = 0;
    cout << "\n";

    nr_pola = sprawdz_numer_pola(nazwa_pola);
    id_pola = sprawdz_indeks_pionka(nr_pola);

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
        for (int i = 0; i < 16; i++)
        {
            if (i == 4)
                n = 22;
            else if (i == 8)
                n = 71;
            else if (i == 12)
                n = 82;
            pionek[i].pole = n;
            n += 2;
        }
    }

    // ustawienia pionkow
    for (int i = 0; i < 8; i++)
    {
        pionek[i].znak = "\2"; // "\2" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "bialy";
        pionek[i].typ = "pionek";
    }

    for (int i = 8; i < 16; i++)
    {
        pionek[i].znak = "\1"; // "\1" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "czarny";
        pionek[i].typ = "pionek";
    }

    // for (int i = 0; i < 16; i++)
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

    while (wybor != "exit" && wybor != "0")
    {
        cout << "----------------------------\n";
        cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\n";
        cout << "Aby zresetowac porgram \"reset\" lub 2\nAby wybrac pionka \"wybierz\" lub 3\n";
        cin >> wybor;

        if (wybor == "start" || wybor == "1")
        {
            system("cls");
            aktualizuj_plansze(); // pierwsze ustawienie

        powtorka_ruchu:
            cout << "Podaj pole pionka: ";
            cin >> sprawdz_pole;

            if (sprawdz_pole != "exit")
            {
                sprawdz_pozycje_pionka(sprawdz_pole);

                if (mozliwy_ruch == false)
                {
                    cout << "Wybrany pionek nie moze wykonac ruchu!\n";
                    goto powtorka_ruchu;
                }
            }
        }
        else if (wybor == "reset" || wybor == "2")
        {
            system("cls");
        }

        // else if (wybor == "ruch" || wybor == "4")
        // {
        //     cout << "Podaj pole pionka aby nim ruszyc(11,13,22...): ";
        //     cin >> numer_pola_gdzie_jest_pionek;
        //     cout << endl;
        //     ruch_pionka(numer_pola_gdzie_jest_pionek);
        // }
    }

    //--------------------------------------------------------------------------------------------------

    // pionek[0].pole = 51;
    // pionek[1].pole = 53;
    // pionek[2].pole = 55;
    // pionek[3].pole = 57;

    // pionek[12].pole = 62;
    // pionek[13].pole = 64;
    // pionek[14].pole = 66;
    // pionek[15].pole = 11;

    // aktualizuj_plansze();

    // getch();
    return 0;
}
