#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>


//                  Esse jogo ainda está em desenvolvimento... Esse é apenas um esboço inicial..



void buffer(); // Limpa o buffer do teclado...
void iniciar_matriz(int matriz[][3]); // inicializa a matriz com as posições iniciais da torre...
void visual_torre(int matriz[][3]); // desenha as torres...
void desenha(int pecca, int x, int y); // desenha as peccas nas posições corretas...
void selecionado(int x, int y, int pecca, int confirme); // mov as peccas o tabuleiro...
int pode_mov(int x, int lado, int matriz[][3]); //checa se a peça selecionada pode mover...
int destino_pecca(); // seleciona a torre a qual você desejá colocar a peça...

void jogar(int matriz[][3]); // inicia o jogo...

int main() {
    system("cls");

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    int matriz_da_torre[3][3];
    iniciar_matriz(matriz_da_torre);
    visual_torre(matriz_da_torre);
    jogar(matriz_da_torre);

    return 0;
}

void buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void jogar(int matriz[][3]) {
    int x = 0;
    int y = 0;

    int position_x = 70;
    int position_y = 7;
    int confirme = 0;
    int torre = 0;

    int tecla = 0;
    int fim_game = 0;

    selecionado(position_x, position_y, matriz[x][y], 0);
    do {
        tecla = getch();
        if (tecla != 32) {
            tecla = getch();
        }

        switch (tecla)
        {
        case 72:
            if (y > 0) {
                position_y = position_y - 1;
                y = y - 1;
            }
            
            break;

        case 80:
            if (y < 2) {
               position_y = position_y + 1; 
               y = y + 1;
            }
            break;

        case 77:
            if (x > 1) {
                if (matriz[x-1] != 0) {
                    x--;
                    position_x -= 12;
                }
            }
            break;

        case 75:
            if (x < 2) {
                if (matriz[x+1][y] != 0) {
                    x++;
                    position_x += 12;
                }
            }
            break;

        case 32:
            confirme = 1;
            break;
        
        default:
            break;
        }

        visual_torre(matriz);
        printf("\t[%d]", tecla);
        printf("\nx = %d \ny = %d", position_x, position_y);
        selecionado(position_x, position_y, matriz[y][x], confirme);

        if (confirme == 1) {
            torre = destino_pecca();
        }

        confirme = 0;

    } while (fim_game != 1);
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

void selecionado(int x, int y, int pecca, int confirme) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    if (pecca == 1) {
        if (confirme == 1) {
            printf("  %c%c  ", 169, 169);
        } else {
            printf(">   **  ");
        }
    } else if (pecca == 2) {
        if (confirme == 1) {
            printf(" %c%c%c%C ", 169, 169, 169, 169);
        } else {
            printf(">  **** ");
        }
    } else if (pecca == 3) {
        if (confirme == 1) {
            printf("%c%c%c%C%C%C", 169, 169, 169, 169, 169, 169);
        } else {
            printf("> ******");
        }
    } else if (pecca == 4) {
        printf("  %c%c  ", 33, 33);
    } else if (pecca == 5) {
        printf("              ");
    }
}

int destino_pecca() {
    int torre = 1;
    int tecla = 0;

    int x = 70;
    int x_tmp = 70;
    int y = 6;
    selecionado(x, y, 4, 0);
    do {

        tecla = getch();
        if (tecla != 32) {
            tecla = getch();
        }

        switch (tecla)
        {
        case 77:
            if (x == 70 || x == 82) {
                x = x + 12;
                torre = torre + 1;
            } else {
                x = 70;
                torre = 1;
            }
            break;

        case 75:
            if (x == 82 || x == 94) {
                x = x - 12;
                torre = torre - 1;
            } else {
                x = 94;
                torre = 3;
            }
            break;
        }

        for (int  i = 0; i < 3; i++) {
            selecionado(x_tmp, y, 5, 0);
            x_tmp = x_tmp + 12;
        }
        x_tmp = 70;
        selecionado(x, y, 4, 0);
    } while (tecla != 32);

    for (int  i = 0; i < 3; i++) {
        selecionado(x_tmp, y, 5, 0);
        x_tmp = x_tmp + 12;
    }

    return torre;
}

void desenha(int pecca, int x, int y) {
    COORD pos;
    pos.X = x; 
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    if (pecca == 1) {
        printf("  **   ");
    } else if (pecca == 2) {
        printf(" ****  "); 
    }else if (pecca == 3) {
        printf("******  ");
    } else if (pecca == 0) {
        printf("--..--  ");
    }

}

int pode_mov(int x, int lado, int matriz[][3]) {
    int pode_mover = 0;

    if (lado == 1) {
        if (x < 3) {
            for (int i = 0; i < 3; i++) {
                if (matriz[x+1][i] == 0) {
                    pode_mover = 1;
                }
            }
        }
    } else if (lado == 2) {
        if (x > 1) {
            for (int i = 0; i < 3; i++) {
                if (matriz[x-1][i] == 0) {
                    pode_mover = 1;
                }
            }
        }
    }
    
    return pode_mover;
}
