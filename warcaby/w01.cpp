#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include "w01.h"

using namespace std;

plansza pionek[16];
plansza znak_na_polu[32];

string wybor;

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
    int n = 11;

    // for (int i = 0; i < 16; i++) // wypisanie pionkow
    // {
    //     cout << "   " << i << "   " << pionek[i].znak << "   " << pionek[i].kolor << "   " << pionek[i].typ << "   " << pionek[i].pole << endl;
    // }

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

    cout << "\n      -------------------------------\n";
    cout << "    " << 8 << " |    " << znak_na_polu[28].znak << "       " << znak_na_polu[29].znak << "       " << znak_na_polu[30].znak << "       " << znak_na_polu[31].znak << "|\n";
    cout << "    " << 7 << " |" << znak_na_polu[24].znak << "       " << znak_na_polu[25].znak << "       " << znak_na_polu[26].znak << "       " << znak_na_polu[27].znak << "    |\n";
    cout << "    " << 6 << " |    " << znak_na_polu[20].znak << "       " << znak_na_polu[21].znak << "       " << znak_na_polu[22].znak << "       " << znak_na_polu[23].znak << "|\n";
    cout << "    " << 5 << " |" << znak_na_polu[16].znak << "       " << znak_na_polu[17].znak << "       " << znak_na_polu[18].znak << "       " << znak_na_polu[19].znak << "    |\n";
    cout << "    " << 4 << " |    " << znak_na_polu[12].znak << "       " << znak_na_polu[13].znak << "       " << znak_na_polu[14].znak << "       " << znak_na_polu[15].znak << "|\n";
    cout << "    " << 3 << " |" << znak_na_polu[8].znak << "       " << znak_na_polu[9].znak << "       " << znak_na_polu[10].znak << "       " << znak_na_polu[11].znak << "    |\n";
    cout << "    " << 2 << " |    " << znak_na_polu[4].znak << "       " << znak_na_polu[5].znak << "       " << znak_na_polu[6].znak << "       " << znak_na_polu[7].znak << "|\n";
    cout << "    " << 1 << " |" << znak_na_polu[0].znak << "       " << znak_na_polu[1].znak << "       " << znak_na_polu[2].znak << "       " << znak_na_polu[3].znak << "    |\n";
    cout << "      -------------------------------\n";
    cout << "       A   B   C   D   E   F   G   H\n";
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
        pionek[i].kolor = "bialy";
        pionek[i].typ = "pionek";
    }

    for (int i = 8; i < 16; i++)
    {
        pionek[i].znak = "\1"; // "\1" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "czarny";
        pionek[i].typ = "pionek";
    }

    for (int i = 0; i < 16; i++)
    {
        cout << "   " << i << "   " << pionek[i].znak << "   " << pionek[i].kolor << "   " << pionek[i].typ << "   " << pionek[i].pole << endl;
    }

    cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\nAby zresetowac porgram \"reset\" lub 2\n";
    while (wybor != "exit" && wybor != "0")
    {
        if (wybor == "start" || wybor == "1")
        {
            cout << "\n      -------------------------------\n    8 |    x       x       x       x|\n    7 |x       x       x       x    |\n    6 |    x       x       x       x|\n";
            cout << "    5 |x       x       x       x    |\n    4 |    x       x       x       x|\n    3 |x       x       x       x    |\n    2 |    x       x       x       x|\n";
            cout << "    1 |x       x       x       x    |\n      -------------------------------\n       A   B   C   D   E   F   G   H\n\n\n";
        }
        else if (wybor == "reset" || wybor == "2")
        {
            system("cls");
            cout << "Warcaby\n\nWpisz \"start\" lub 1 aby rozpoczac\nAby zakonczyc program \"exit\" lub 0\nAby zresetowac porgram \"reset\" lub 2\n";
        }

        cin >> wybor;
    }

    //--------------------------------------------------------------------------------------------------

    aktualizuj_plansze();

    pionek[0].pole = 51;
    pionek[1].pole = 53;
    pionek[2].pole = 55;
    pionek[3].pole = 57;

    pionek[12].pole = 62;
    pionek[13].pole = 64;
    pionek[14].pole = 66;
    pionek[15].pole = 11;

    aktualizuj_plansze();

    getch();
    return 0;
}
