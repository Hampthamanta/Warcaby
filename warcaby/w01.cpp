#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include "w01.h"

using namespace std;

// class plansza
// {
// public:
//     int pole;
//     string kolor;
//     string typ;
//     string znak;
// };

plansza pionek[16];
plansza znak_na_polu[32];

string dane;

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

void aktualizuj_plansze()
{
    { // aktualizacja znakow na planszy
        int n = 11;

        for (int i = 0; i < 16; i++)
        {
            cout << "   " << i << "   " << pionek[i].znak << "   " << pionek[i].kolor << "   " << pionek[i].typ << "   " << pionek[i].pole << endl;
        }

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

            if (n == 31)
                cout << "\n\n\n\nWOW\n\n\n";

            for (int j = 0; j < 16; j++)
            {
                if (pionek[j].pole == n)
                    znak_na_polu[i].znak = pionek[j].znak;
            }
            n += 2;
        }
    }
    cout << endl;
    for (int i = 4; i > 0; i--)
    {
        cout << "    " << i * 2 << " |    " << znak_na_polu[(i * 8 - 4)].znak << "       " << znak_na_polu[(i * 8 - 3)].znak << "       " << znak_na_polu[(i * 8 - 2)].znak << "       " << znak_na_polu[(i * 8 - 1)].znak << "|\n";
        cout << "    " << i * 2 - 1 << " |" << znak_na_polu[(i * 7 - 3)].znak << "       " << znak_na_polu[(i * 7 - 2)].znak << "       " << znak_na_polu[(i * 7 - 1)].znak << "       " << znak_na_polu[(i * 7)].znak << "    |\n";
    }
    cout << endl;
}

int main()
{

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
        pionek[i].kolor = "czarny";
        pionek[i].typ = "pionek";
    }

    for (int i = 8; i < 16; i++)
    {
        pionek[i].znak = "\1"; // "\1" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "bialy";
        pionek[i].typ = "pionek";
    }

    for (int i = 0; i < 16; i++)
    {
        cout << "   " << i << "   " << pionek[i].znak << "   " << pionek[i].kolor << "   " << pionek[i].typ << "   " << pionek[i].pole << endl;
    }

    cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\nAby zresetowac porgram \"reset\" lub 2\n";
    while (dane != "exit" && dane != "0")
    {
        if (dane == "start" || dane == "1")
        {
            cout << "\n      -------------------------------\n    8 |    x       x       x       x|\n    7 |x       x       x       x    |\n    6 |    x       x       x       x|\n";
            cout << "    5 |x       x       x       x    |\n    4 |    x       x       x       x|\n    3 |x       x       x       x    |\n    2 |    x       x       x       x|\n";
            cout << "    1 |x       x       x       x    |\n      -------------------------------\n       A   B   C   D   E   F   G   H\n\n\n";
        }
        else if (dane == "reset" || dane == "2")
        {
            system("cls");
            cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\nAby zresetowac porgram \"reset\" lub 2\n";
        }

        cin >> dane;
    }

    //--------------------------------------------------------------------------------------------------

    aktualizuj_plansze();

    pionek[3].pole = 31;

    aktualizuj_plansze();

    getch();
    return 0;
}
