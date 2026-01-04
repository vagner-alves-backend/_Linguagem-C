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

    int tecla = 0;

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
        do {
            printf("---Qual pecca voce deseja movimentar?\n");
            printf("[1]  *  \n[2] *** \n[3]*****\n............\n..: ");
            scanf("%d", &pecca);
            buffer();

            for (int eixo_x_for = 0; eixo_x_for < 3; eixo_x_for++) {
                for (int eixo_y_for = 0; eixo_y_for < 3; eixo_y_for++) {
                    if (matriz[eixo_x_for][eixo_y_for] == pecca) {
                        if (eixo_x_for == 0) {
                            movimento_regular = 1;
                            eixo_x = eixo_x_for;
                        } else if (matriz[eixo_x_for -1][eixo_y_for] == 0) {
                            movimento_regular = 1;
                            eixo_x = eixo_x_for;
                        }
                    }
                }
            }

            if (movimento_regular != 1) {
                printf("\t---Movimento inrregular, escolha uma nova pecca...\n\n");
            }
        } while (movimento_regular != 1);
        printf("\t\tx = %d\tpecca = %d\n", eixo_x, pecca);


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
                    } else if (matriz[eixo_y_for][torre -2] > pecca) {
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
        printf("\t\ttorre [%d], torre_calc[%d], y = %d\n", torre, torre-1, eixo_x);
        


        vitoria = 1;
    } while (vitoria != 1);
} 