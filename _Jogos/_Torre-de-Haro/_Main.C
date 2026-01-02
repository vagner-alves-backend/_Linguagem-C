#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void buffer(); // limpa o buffer do teclado..
void iniciar_jogo(int matriz[][3]); // inicia o jogo..


int main() {

    int matriz[3][3];
    int pecca = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0) {
                matriz[i][j] = pecca;
                pecca = pecca + 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }

    iniciar_jogo(matriz);

    return 0;
}

void buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void iniciar_jogo(int matriz[][3]) {
    int x = 0;
    int y = 0;
    int pecca = 0;

    int pode_mover = 0;

    do {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }   
        printf("qual pecca voce deseja mover? ");
        scanf("%d", &pecca);

        do {
            printf("para qual torre? ");
            scanf("%d", &y);
            buffer();

            for (int i = 2; i >= 0; i--) {
                if (matriz[i][y] == 0) {
                    pode_mover = 1;
                    x = i;
                    i = -1;
                }
            }

            if (pode_mover != 1) {
                printf("Movimento inrregular... Escolha um novo destino---\n\n");
            }
        } while (pode_mover != 1);
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matriz[i][j] == pecca) {
                    matriz[i][j] = 0;
                } 
            }
        } 

        matriz[x][y] = pecca;
        system("cls");
    } while (x != 201);
} 