#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define LARGEUR 30
#define HAUTEUR 15
#define MAX_TAILLE 200

typedef struct { int x, y; } Point;
Point serpent[MAX_TAILLE], pomme;
int longueur, dirX, dirY, score, gameOver, pommes_mangees;

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setLCDColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void cacherCurseur() {
    CONSOLE_CURSOR_INFO info = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void genererPomme() {
    pomme.x = rand() % LARGEUR;
    pomme.y = rand() % HAUTEUR;
}

void reset() {
    longueur = 3; dirX = 1; dirY = 0; score = 0; gameOver = 0;
    for (int i = 0; i < longueur; i++) {
        serpent[i].x = LARGEUR / 2 - i;
        serpent[i].y = HAUTEUR / 2;
    }
    genererPomme();
}

void dessinerCadre() {
    printf("+");
    for (int i = 0; i < LARGEUR; i++) printf("-");
    printf("+\n");
    for (int y = 0; y < HAUTEUR; y++) {
        printf("¦");
        for (int x = 0; x < LARGEUR; x++) printf(" ");
        printf("¦\n");
    }
    printf("+");
    for (int i = 0; i < LARGEUR; i++) printf("-");
    printf("+\n");
}

void afficher() {
    gotoxy(0, 0);
    dessinerCadre();

    // Affiche serpent et pomme
    for (int i = 0; i < longueur; i++) {
        gotoxy(serpent[i].x + 1, serpent[i].y + 1);
        printf(i == 0 ? "0" : "�");
    }

    gotoxy(pomme.x + 1, pomme.y + 1);
    printf("?");

    // Affiche score et pommes mangees
    gotoxy(0, HAUTEUR + 2);
    printf("Score: %d | Pommes: %d/3", score, pommes_mangees);

    // Manger la pomme
    if (serpent[0].x == pomme.x && serpent[0].y == pomme.y) {
        pommes_mangees++;
        score += 10;
        if (pommes_mangees >= 3) {
            if (longueur < MAX_TAILLE) longueur++;
            pommes_mangees = 0;
        }
        genererPomme();
    }
}

void deplacer() {
    // Deplacer le corps
    for (int i = longueur - 1; i > 0; i--) {
        serpent[i].x = serpent[i - 1].x;
        serpent[i].y = serpent[i - 1].y;
    }
    
    // Deplacer la tête
    serpent[0].x += dirX;
    serpent[0].y += dirY;

    // Collision mur
    if (serpent[0].x < 0 || serpent[0].x >= LARGEUR || serpent[0].y < 0 || serpent[0].y >= HAUTEUR)
        gameOver = 1;

    // Collision corps
    for (int i = 1; i < longueur; i++)
        if (serpent[0].x == serpent[i].x && serpent[0].y == serpent[i].y)
            gameOver = 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand((unsigned)time(NULL));
    setLCDColor();
    cacherCurseur();
    reset();

    while (!gameOver) {
        afficher();

        if (_kbhit()) {
            int c = _getch();
            if (c == 224) c = _getch();
            switch (c) {
                case 72: if (dirY == 0) { dirX = 0; dirY = -1; } break; // Haut
                case 80: if (dirY == 0) { dirX = 0; dirY = 1; } break;  // Bas
                case 75: if (dirX == 0) { dirX = -1; dirY = 0; } break; // Gauche
                case 77: if (dirX == 0) { dirX = 1; dirY = 0; } break;  // Droite
            }
        }

        deplacer();
        Sleep(100);
    }

    gotoxy(0, HAUTEUR + 7);
    printf("=== GAME OVER ===\nScore final : %d\n", score);
    return 0;
}
