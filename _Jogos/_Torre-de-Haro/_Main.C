#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


void buffer(); // limpa o buffer do teclado..
void iniciar_jogo(int matriz[][3]); // inicia o jogo..
void desenhe(int matriz[][3]);//Desenha as peças do jogo..
int menu(); // Menu de navegação...

int main() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    system("cls");

    int matriz[3][3];
    int pecca = 1;
    int nova_partida = 0;
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
    do {
        nova_partida = menu();
        if (nova_partida == 1) {
            pecca = 1;
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
        }
    } while (nova_partida != 2);
    getch();

    return 0;
}

void buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int menu() {
    COORD pos;

    int escolha = 1;
    int tecla;

    pos.X = 70;
    pos.Y = 17;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("---Deseja iniciar uma nova partida?");

    do {
        if (kbhit()) {
            tecla = getch();
            if (tecla != 32) {
                tecla = getch();
                if (escolha == 1) {
                    escolha = 2;
                } else {
                    escolha = 1;
                }
            }
        }

        pos.X = 70;
        pos.Y = 18;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        if (escolha == 1) {
            printf("[ Yes ]");
        } else {
            printf(" Yes    ");
        }

        pos.X = 80;
        pos.Y = 18;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        if (escolha == 2) {
            printf("[ No ]");
        } else {
            printf(" No    ");
        }

    } while (tecla != 32);

    if (escolha == 1) {
        pos.X = 70;
        pos.Y = 17;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("                                         ");

        pos.X = 70;
        pos.Y = 18;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("                                          ");
    }
    return escolha;
}

void iniciar_jogo(int matriz[][3]) {
    COORD pos;

    int eixo_y = 0;
    int pecca = 0;
    int torre = 0;
    int movimentos = 0;
    int movimento_regular = 0;

    int movimentou_base = 0;
    int vitoria = 0;

    do {
        // a função a seguir será responsavel por desenhar a torre---.
        desenhe(matriz);
        pos.X = 94;
        pos.Y = 12;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("---Movimentos [ %d ]", movimentos);

        // a função a seguir sera responsavel por coletar a peça que o jogador deseja movimentar...
        movimento_regular = 0;

        do {
            pos.X = 22;
            pos.Y = 17;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            printf("   ");

            for (int index = 12; index < 18; index++) {
                pos.X = 20;
                pos.Y = index;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                if (index == 12) {
                    printf("---Qual pecca vocce deseja movimentar?");
                } else if (index == 13) {
                    printf("1-   *  ");
                } else if (index == 14) {
                    printf("2-  *** ");
                } else if (index == 15) {
                    printf("3- *****");
                } else if (index == 16) {
                    printf(".............");
                } else if (index == 17) {
                    printf("..: ");
                    scanf("%d", &pecca);
                }
            }
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
                pos.X = 40;
                pos.Y = 20;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                printf("---Movimento inrregular, escolha uma nova pecca...");
            } else {
                pos.X = 40;
                pos.Y = 20;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                printf("                                                        ");
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
            pos.X = 20;
            pos.Y = 19;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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
                pos.X = 40;
                pos.Y = 20;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                printf("---Movimento inrregular, escolha uma nova posiccao...");
            } else {
                pos.X = 40;
                pos.Y = 20;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                printf("                                                         ");
            }
        } while (movimento_regular != 1);

        pos.X = 20;
        pos.Y = 19;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("                                                     ");

        if (pecca == 3) {
            movimentou_base = 1;
        }

        matriz[eixo_y][torre -1] = pecca;
        movimentos++;

        for (int index_x = 0; index_x < 3; index_x++) {
            if (matriz[index_x][torre -1] != 0) {
                vitoria++;
            }
        }

        if (vitoria == 3 && movimentou_base == 1) {
            vitoria = 201;
        } else {
            vitoria = 0;
        }
    } while (vitoria != 201);

    desenhe(matriz);
    pos.X = 94;
    pos.Y = 12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("---Movimentos [ %d ]", movimentos);

    pos.X = 75;
    pos.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("---VICTORY---");

    pos.X = 0;
    pos.Y = 23;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf(" ");
} 


void desenhe(int matriz[][3]) {
    COORD pos;
    int position_x = 70;
    int position_y = 7;
    
    for (int eixo_x = 0; eixo_x < 3; eixo_x++) {
        for (int eixo_y = 0; eixo_y < 3; eixo_y++) {
            
            if (eixo_x == 1) {
                position_x = 82;
            } else if (eixo_x == 2) {
                position_x = 94;
            }

            if (eixo_y == 0) {
                position_y = 7; 
            } else if (eixo_y == 1) {
                position_y = 8;
            } else if (eixo_y == 2) {
                position_y = 9;
            }

            pos.X = position_x;
            pos.Y = position_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

            if (matriz[eixo_y][eixo_x] == 1) {
                printf("  *   "); 
            } else if (matriz[eixo_y][eixo_x] == 2) {
                printf(" ***  ");
            } else if (matriz[eixo_y][eixo_x] == 3) {
                printf("***** ");
            } else if (matriz[eixo_y][eixo_x] == 0) {
                printf("--.-- ");
            }


        }
        printf("\n");
    }
}