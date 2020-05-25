// SnakeC.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//


#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;
bool gameOver = false;
const int Breite = 20;
const int Hoehe = 20;
int x, y, ApfelX, ApfelY, score = 0;
int SchwanzX[400], SchwanzY[400];
int nSchwanz = 0;
enum e_Richtung { STOP = 0, Links, Rechts, Oben, Unten };
e_Richtung dir;

void ApfelSpawn()
{
    ApfelX = rand() % Breite;
    ApfelY = rand() % Hoehe;
    if (x == ApfelX && y == ApfelY)
    {
        ApfelSpawn();
    }
    for (int i = 0; i < nSchwanz; i++)
    {
        if (SchwanzX[i] == ApfelX && SchwanzY[i] == ApfelY)
        {
            ApfelSpawn();
        }
    }
}

void Setup()
{
    dir = STOP;
    x = Breite / 2;
    y = Hoehe / 2;
    ApfelSpawn();

    score = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < Breite + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < Hoehe; i++)
    {
        for (int j = 0; j < Breite; j++)
        {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("X");
            else if (i == ApfelY && j == ApfelX)
                printf("A");
            else
            {
                bool print = false;
                for (int k = 0; k < nSchwanz; k++)
                {
                    if (SchwanzX[k] == j && SchwanzY[k] == i)
                    {
                        printf("x");
                        print = true;
                    }
                }
                if (!print)
                    printf(" ");
            }


            if (j == Breite - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < Breite + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %i \n", score);
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != Rechts)
            {
                dir = Links;
            }
            break;


        case 'd':
            if (dir != Links)
            {
                dir = Rechts;
            }
            break;


        case 'w':
            if (dir != Unten)
            {
                dir = Oben;
            }
            break;


        case 's':
            if (dir != Oben)
            {
                dir = Unten;
            }
            break;

        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int HilfsvarX = SchwanzX[0];
    int HilfsvarY = SchwanzY[0];
    int Hilfsvar2X, Hilfsvar2Y;
    SchwanzX[0] = x;
    SchwanzY[0] = y;
    for (int i = 1; i < nSchwanz; i++)
    {
        Hilfsvar2X = SchwanzX[i];
        Hilfsvar2Y = SchwanzY[i];
        SchwanzX[i] = HilfsvarX;
        SchwanzY[i] = HilfsvarY;
        HilfsvarX = Hilfsvar2X;
        HilfsvarY = Hilfsvar2Y;
    }
    switch (dir)
    {
    case Links:
        x--;
        break;
    case Rechts:
        x++;
        break;
    case Oben:
        y--;
        break;
    case Unten:
        y++;
        break;
    default:
        break;
    }
    //if (x > Breite || x < 0 || y > Hoehe || y < 0)
    //  gameOver = true;
    if (x >= Breite) x = 0; else if (x < 0) x = Breite - 1;
    if (y >= Hoehe) y = 0; else if (y < 0) y = Hoehe - 1;

    for (int i = 0; i < nSchwanz; i++) //
        if (SchwanzX[i] == x && SchwanzY[i] == y)
            gameOver = true;

    if (x == ApfelX && y == ApfelY) //Apfel essen
    {
        score += 10;
        ApfelSpawn();
        nSchwanz++;
    }
}

int main()
{
    srand(time(NULL));
    char Start = '3';
    printf("\n    ####  #   #   ##   #  #  ####\n");
    printf("    #     ##  #  #  #  # #   #  \n");
    printf("    ####  # # #  #  #  ##    ####\n");
    printf("       #  #  ##  ####  # #   #  \n");
    printf("    ####  #   #  #  #  #  #  ####\n\n");
    printf("Spiel Starten (1)\nSpielanleitung (2)\nSpiel beenden (3)\n");
    scanf_s(" %c", &Start);
    while (Start != '3')
    {
        if (gameOver == false && Start == '1')
        {
            Setup();
            while (!gameOver)
            {
                Draw();
                Input();
                Logic();
                Sleep(40);
            }
        }
        if (Start == '2')
        {
            system("cls");
            printf("Spielanleitung\n\n");
            printf("Das Ziel des Spiels ist es so viele Aepfel wie moeglich zu essen ohne dabei zu sterben.\n");
            printf("Man stirbt wenn man seinen Schwanz beisst.\n");//leicht
            printf("Mit 'W' bewegt man sich nach oben, mit 'S' nach unten, mit 'A' nach links, mit 'D' nach rechts.\nMit 'X' kann man das Spiel jederzeit beenden.\n\n");
        }
        if (Start != '1' && Start != '2' && Start != '3')
        {
            system("cls");
            printf("Falsche Eingabe, bitte erneut versuchen:\n\n");
        }
        gameOver = false;
        printf("Spiel Starten (1)\nSpielanleitung (2)\nSpiel beenden (3)\n");
        scanf_s(" %c", &Start);
        if (Start == '1')
        {
            nSchwanz = 0;
        }
    }
    return 0;
}