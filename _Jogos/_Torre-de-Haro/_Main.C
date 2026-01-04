#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//                          Em desenvolvimento---.

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
    int eixo_x = 0;
    int eixo_y = 0;

    int pecca = 0;
    int torre = 0;
    int movimentos = 0;
    int movimento_regular = 0;
    int vitoria = 0;

    do {
        system("cls");
        // a função a seguir será responsavel por desenhar a torre---.
        for (int eixo_x_for = 0; eixo_x_for < 3; eixo_x_for++) {
            printf("\t\t");
            for (int eixo_y_for = 0; eixo_y_for < 3; eixo_y_for++) {
                printf("%d ", matriz[eixo_x_for][eixo_y_for]);
            }
            printf("\n");
        }

        // a função a seguir sera responsavel por coletar a peça que o jogador deseja movimentar...
        movimento_regular = 0;
        printf("---Qual pecca voce deseja movimentar?\n");
        printf("[1]  *  \n[2] *** \n[3]*****\n............\n..: ");
        scanf("%d", &pecca);
        buffer();
        do {

            for (int eixo_x_for = 0; eixo_x_for < 3; eixo_x_for++) {
                for (int eixo_y_for = 0; eixo_y_for < 3; eixo_y_for++) {
                    if (matriz[eixo_x_for][eixo_y_for] == pecca) {
                        if (eixo_x_for == 0) {
                            movimento_regular = 1;
                        } else if (matriz[eixo_x_for -1][eixo_y_for] == 0) {
                            movimento_regular = 1;
                        }
                    }
                }
            }

            if (movimento_regular != 1) {
                printf("\t---Movimento inrregular, escolha uma nova pecca...\n\n");
                printf("---Qual pecca voce deseja movimentar? ");
                scanf("%d", &pecca);
                buffer();
            }
        } while (movimento_regular != 1);

        for (int index_x = 0; index_x < 3; index_x++) {
            for (int index_y = 0; index_y < 3; index_y++) {
                if (matriz[index_x][index_y] == pecca) {
                    matriz[index_x][index_y] = 0;
                }
            }
        }

        // a função a seguir permite o jogador escolher a torre para onde deseja mandar a peça selecionada...
        movimento_regular = 0;
        do {
            printf("---Para qual torre deseja realocar a pecca? ");
            scanf("%d", &torre);
            buffer();

            for (int eixo_y_for = 2; eixo_y_for >= 0; eixo_y_for--) {
                if (matriz[eixo_y_for][torre -1] == 0) {
                    if (eixo_y_for == 2) {
                        movimento_regular = 1;
                        eixo_y = eixo_y_for;
                        eixo_y_for = -1;
                    } else if (matriz[eixo_y_for +1][torre -1] > pecca) {
                        movimento_regular = 1;
                        eixo_y = eixo_y_for;
                        eixo_y_for = -1;
                    }
                }
            }

            if (movimento_regular != 1) {
                printf("\t---Movimento inrregular, escolha uma nova posiccao...\n\n");
            }
        } while (movimento_regular != 1);

        matriz[eixo_y][torre -1] = pecca;
        movimentos++;
        if (pecca == 4) {
            vitoria = 1;
        }
    } while (vitoria != 1);
} 