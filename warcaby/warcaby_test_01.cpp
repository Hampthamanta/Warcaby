

// Jak o czymś myślę to często nie umiem tego od razu wytłumaczyć innej osobie co tam się zrodziło w tej mojej głowie xd
// Więc może to sprawi, że uda ci się zrozumieć mój sposób myślenia o tym. Mam taką nadzieje
// Przejrzyj to i powiedz co ty na to
// No i powiedz jak ty na to patrzysz, nie na podstawie tego czegoś co zrobiłem

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>

using namespace std;

class plansza
{
public:
    int pole;
    string kolor;
    string typ;
    string znak;
};

int main()
{

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

    // szkic planszy  w konsoli z numerami wykozystywanych pol
    cout << "\n      -------------------------------\n    8 |   82      84      86      88|\n    7 |71     73      75      77    |\n    6 |   62      64      66      68|\n";
    cout << "    5 |51     53      55      57    |\n    4 |   42      44      46      48|\n    3 |31     33      35      37    |\n    2 |   22      24      26      28|\n";
    cout << "    1 |11     13      15      17    |\n      -------------------------------\n       A   B   C   D   E   F   G   H\n\n\n";

    plansza pionek[16]; // klasa plansza o obiektach czyli pionkach

    // ustawienie startowych pozycji pionkow
    // pionek[0].pole = 11;
    // pionek[1].pole = 13;
    // pionek[2].pole = 15;
    // pionek[3].pole = 17;
    // pionek[4].pole = 22;
    // pionek[5].pole = 24;
    // pionek[6].pole = 26;
    // pionek[7].pole = 28;
    // pionek[8].pole = 71;
    // pionek[9].pole = 73;
    // pionek[10].pole = 75;
    // pionek[11].pole = 77;
    // pionek[12].pole = 82;
    // pionek[13].pole = 84;
    // pionek[14].pole = 86;
    // pionek[15].pole = 88;

    {               // to, i to wyzej robi to samo
        int n = 11; // a to chyba ladniej wyglada, nwm xd
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
        pionek[i].znak = "\1"; // "\1" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "czarny";
        pionek[i].typ = "pionek";
    }

    for (int i = 8; i < 16; i++)
    {
        pionek[i].znak = "\2"; // "\2" to wstawienie znaku buzki z ASCII
        pionek[i].kolor = "bialy";
        pionek[i].typ = "pionek";
    }

    // wstawilem takie symbole za pionki bo inne mi nie dzialaja, nie wiem dlaczego

    for (int i = 0; i < 16; i++)
    {
        cout << "   " << i << "   " << pionek[i].znak << "   " << pionek[i].kolor << "   " << pionek[i].typ << "   " << pionek[i].pole << endl;
    }

    getch();
    return 0;
}