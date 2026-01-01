#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void buffer(); // Limpa o buffer do teclado...
void iniciar_matriz(int matriz[][3]); // inicializa a matriz com as posições iniciais da torre...
void visual_torre(int matriz[][3]); // desenha as torres...
void desenha(int pecca, int x, int y); // desenha as peccas nas posições corretas...

int main() {
    system("cls");

    int matriz_da_torre[3][3];
    iniciar_matriz(matriz_da_torre);
    visual_torre(matriz_da_torre);

    return 0;
}

void buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void visual_torre(int matriz[][3]) {
    int x = 70;
    int y = 7;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0) {
                x = 70;
            } else if (i == 1) {
                x = 82;
            } else if (i == 2) {
                x = 94;
            }

            if (j == 0) {
                y = 7;
            } else if (j == 1) {
                y = 8;
            } else if (j == 2) {
                y = 9;
            }
            if (matriz[j][i] != 0) {
                desenha(matriz[j][i], x, y);
            } else {
                desenha(0, x, y);
            }
        }
        printf("\n");
    }
}

void iniciar_matriz(int matriz[][3]) {
    int pecca = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0) {
                pecca++;
                matriz[i][j] = pecca;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void desenha(int pecca, int x, int y) {
    COORD pos;
    pos.X = x; 
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    if (pecca == 1) {
        printf("  **  ");
    } else if (pecca == 2) {
        printf(" **** "); 
    }else if (pecca == 3) {
        printf("******");
    } else if (pecca == 0) {
        printf("--..--");
    }

}
