#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>

int _Menu();//Menu de navegação do game...
void _Mov_Menu(int _position); //Movimenta pelo menu...
void _Ocultar_Menu();//Ocultar o menu para que o jogo inicie...

void _Desenhe_Tabuleiro(int tab[][12]);//Desenhar Tabuleiro...
void _Iniciar_Matriz(int tab[][12]);//Iniciara a matriz...
int _Iniciar_Jogo(int tab[][12]);//Iniciara o game..

void _Desenha(int x, int y, int desenhe);//Irá desenhar as peças do jogo...
int _Mover_Pecca_X(int x, int pecca, int rotate, int bloco);//Irá calcular a posição X da peça...
int _Mover_Pecca_Y(int y, int pecca, int rotate, int bloco);//Irá calcular a posição Y da peça...
int _Tem_Parrede(int x, int pecca, int rotaccao); // Verifica se a peça chegou no limite do tabulero...
int _Tem_Pecca(int tab[][12], int pecca, int rotaccao, int x, int y, int lado);//Verifica se tem uma peça no local para onde você deseja mover a peça atual...
void _Venceu(int tab[][12]);//Checa se uma linha foi completada com sucesso.. 
void _Atualizar_Tabuleiro(int tab[][12], int y); // Atualizar a posição das peças..
int _Sorteie_P();//Sorteia a proxima peça...

void _Nova_Partida(int tab[][12]);//Iicia uma nova partida..


int main() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    system("cls");
    int _continue = 0;

    
    int _Tabuleiro[25][12];//Matriz do jogo..

    do {
        _continue = _Menu();
        if (_continue == 1) {
            _Ocultar_Menu();
            _Iniciar_Matriz(_Tabuleiro);
            _Desenhe_Tabuleiro(_Tabuleiro);
            do {
                _continue = _Iniciar_Jogo(_Tabuleiro);
            } while (_continue != 0);
        }
    } while (_continue != 0);

    getch();
    system("cls");

    return 0;
}

int _Menu() {
    COORD pos;
    int selecionado = 1;

    pos.X = 70;
    pos.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("---Menu---");

    int _Tecla = 0;
    do {
        _Mov_Menu(selecionado);
        _Tecla = getch();
        if (_Tecla != 32) {
            _Tecla = getch();
        }
        
        if (_Tecla == 80) {
            if (selecionado < 3) {
                selecionado++; 
            } else {
                selecionado = 1;
            }
        } else if (_Tecla == 72) {
            if (selecionado > 1) {
                selecionado--;
            } else {
                selecionado = 3;
            }
        }
    } while (_Tecla != 32);

    return  selecionado;
}

void _Mov_Menu(int _position) {
    COORD pos;
    pos.X = 68;
    pos.Y = 7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    
    if (_position == 1) {
        printf(">  Play  <");
    } else {
        printf("Play       ");
    }

    pos.X = 68;
    pos.Y = 8;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    
    if (_position == 2) {
        printf(">  Historico  <");
    } else {
        printf("Historico         ");
    }

    pos.X = 68;
    pos.Y = 9;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    
    if (_position == 3) {
        printf(">  Configuracoes  <");
    } else {
        printf("Configuracoes      ");
    }
}

void _Ocultar_Menu() {
    COORD pos;

    pos.X = 70;
    pos.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("                     ");

    pos.X = 68;
    pos.Y = 7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("                     ");

    pos.X = 68;
    pos.Y = 8;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("                     ");

    pos.X = 68;
    pos.Y = 9;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("                     ");
}

int _Iniciar_Jogo(int tab[][12]) {
    COORD pos;
    int _Derrota = 0;

    int x = 12;
    int x_anerior = 0;

    int y = 3;

    int _Pecca = _Sorteie_P(); // 1 = T.. 2 = L.. 3 == I.. 4 = Z.. 5 = Quadrado...
    int rotaccao = 1;
    int rotacca_acionada = 0;
    int rotaccao_tmp = 0;
    int rotate = 0;

    int _Mover = 0;
    int obstaculo = 0;

    int selecionado = 1;
    do {
        x_anerior = x;

        for (int i = 2; i < 22; i+=2) {
            _Desenha(i, 3, 4);
        }
        
        if (kbhit()) {
            _Mover = getch();
            _Mover = getch();

            switch (_Mover) {
                case 77: // Move a peça para Direita...
                    if (_Tem_Parrede(x+2, _Pecca, rotaccao) == 1 && _Tem_Pecca(tab, _Pecca, rotaccao, x, y, 2) == 1) {
                        x = x+2;
                    }
                    break;

                case 75: // Move a peça para Esquerda...
                    if (_Tem_Parrede(x-2, _Pecca, rotaccao) == 1 && _Tem_Pecca(tab, _Pecca, rotaccao, x, y, 1) == 1) {
                        x = x-2;
                    }
                    break;

                case 72:
                    if (rotaccao != 4) {
                        rotate = rotaccao + 1;
                    } else {
                        rotate = 1;
                    }
                    if (_Tem_Parrede(x, _Pecca, rotate) == 1 && _Tem_Pecca(tab, _Pecca, rotate, x, y, 1) == 1) {
                        if (rotaccao < 4) {
                            rotaccao++;
                        } else {
                            rotaccao = 1;
                        }
                        rotacca_acionada = 1;
                    }
                
                    break;
            }
        }

        for (int i = 1; i < 5; i++) {
            if (rotacca_acionada == 1) {
                if (rotaccao == 1) {
                    rotaccao_tmp = 4; 
                } else {
                    rotaccao_tmp = rotaccao-1;
                }
                _Desenha(_Mover_Pecca_X(x_anerior, _Pecca, rotaccao_tmp, i), _Mover_Pecca_Y(y-1, _Pecca, rotaccao_tmp, i), 2);//Apaga...
            } else {
                _Desenha(_Mover_Pecca_X(x_anerior, _Pecca, rotaccao, i), _Mover_Pecca_Y(y-1, _Pecca, rotaccao, i), 2);//Apaga...
            }
        } 

        for (int i = 1; i < 5; i++) {
            _Desenha(_Mover_Pecca_X(x, _Pecca, rotaccao, i), _Mover_Pecca_Y(y, _Pecca, rotaccao, i), 1);//Desenha..
        } 
        rotacca_acionada = 0;

        for (int i = 1; i < 5; i++) {
            if (tab[_Mover_Pecca_Y(y+1, _Pecca, rotaccao, i)][_Mover_Pecca_X(x, _Pecca, rotaccao, i)/2] == 1) {
                obstaculo = 1;
                i = 5;
            }
        }

        if (tab[y+1][1] != 2 && obstaculo != 1) {
            y++;
        } else {
            for (int i = 1; i < 5; i++) {
                tab[_Mover_Pecca_Y(y, _Pecca, rotaccao, i)][_Mover_Pecca_X(x, _Pecca, rotaccao, i)/2] = 1;
            }
            _Venceu(tab);

            y = 3;
            x = 12;
            obstaculo = 0;
            rotaccao = 1;
            _Pecca = _Sorteie_P();

            for (int i = 1; i < 11; i++) {
                if (tab[4][i] == 1) {
                    _Derrota = 1;
                }
            } 
        }
        Sleep(100);
    } while (_Derrota != 1);

    pos.X = 70;
    pos.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("---Deseja---");

    do {
        pos.X = 65;
        pos.Y = 7;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        if (selecionado == 1) {
            printf("[ play ]");
        } else {
            printf("  play      ");
        }

        pos.X = 80;
        pos.Y = 7;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        if (selecionado == 2) {
            printf("[ end ]");
        } else {
            printf("  end         ");
        }

        _Mover = getch();
        if (_Mover == 77 || _Mover == 75) {
            if (selecionado == 1) {
                selecionado = 2;
            } else {
                selecionado = 1;
            }
        }
    } while (_Mover != 32);

    pos.X = 70;
    pos.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("                  ");

    pos.X = 79;
    pos.Y = 7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("               ");

    pos.X = 64;
    pos.Y = 7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("                 ");

    if (selecionado == 1) {
        _Nova_Partida(tab);
        return 1;
    } else {
        pos.X = 64;
        pos.Y = 5;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("[  Game Over... ]");
    }

    return 0;
}

void _Nova_Partida(int tab[][12]) {
    for (int i = 0; i < 24; i++) {
        for (int j = 1; j < 11; j++) {
            if (i == 3) {
                tab[i][j] = 3;
            } else {
                tab[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < 24; i++) {
        for (int j = 1; j < 11; j++) {
            _Desenha(j*2, i, 3);
        }
        Sleep(30);
    }

    for (int i = 0; i < 24; i++) {
        for (int j = 10; j > 0; j--) {
            if (i == 3) {
                _Desenha(j*2, i, 4); 
            } else {
               _Desenha(j*2, i, 2); 
            }
            
        }
        Sleep(30);
    }
}

int _Sorteie_P() {
    int p = 0;
    srand(time(NULL));
    while (p == 0) {
        p = rand() %5;
    } 

    return p;
}


void _Venceu(int tab[][12]) {
    int cont = 0;
    for (int i = 23; i > 3; i--) {
        for (int j = 1; j < 11; j++) {
            if (tab[i][j] == 1) {
                cont++;
            }
        }
        if (cont == 10) {
            for (int j = 1; j < 11; j++) {
                tab[i][j] = 0;
            } 

            printf("\n\n\n");
            for (int ind = i; ind > 3; ind--) {
                for (int j = 1; j < 11; j++) {                
                    if (tab[ind][j] == 1 && tab[ind+1][j] == 0) {
                        tab[ind][j] = 0;
                        tab[ind+1][j] = 1;
                    }
                }
            }


            for (int j = 2; j < 22; j += 2) {
                _Desenha(j, i, 3);
                Sleep(20);
            }

            for (int j = 20; j > 0; j -= 2) {
                _Desenha(j, i, 2);
                Sleep(20);
            }
            _Atualizar_Tabuleiro(tab, i++);
            i = i + 1;
        }
        cont = 0;
    }
}

void _Atualizar_Tabuleiro(int tab[][12], int y) {
    for (int i = y; i > 3; i--) {
        for (int j = 10; j >= 1; j--) {
            if (tab[i][j] == 1) {
                _Desenha(j * 2, i, 1);
            } else if (tab[i][j] == 0) {
                _Desenha(j * 2, i, 2);
            }
        }
    }
}

void _Desenha(int x, int y, int desenhe) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    
    if (desenhe == 1) { //Desenhar Peça...
        printf(" %c ", 254);
    } else if (desenhe == 2) { // Apague peça...
        printf("   ");
    } else if (desenhe == 3) {
        printf(" = ");
    } else if (desenhe == 4) {
        printf(" . ");
    }
}

void _Iniciar_Matriz(int tab[][12]) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 12; j++) {
            if (j == 0 || j == 11) {
                tab[i][j] = 4;
            } else if (i == 24) {
                tab[i][j] = 2;
            } else if (i == 3) {
                tab[i][j] = 3;
            } else {
                tab[i][j] = 0;
            }
        }
    }
}

void _Desenhe_Tabuleiro(int tab[][12]) {
    COORD pos;

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 12; j++) {
            pos.X = j*2;
            pos.Y = i;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            
            if (tab[i][j] == 4) {
                printf(" + ");
            } else if (tab[i][j] == 3) {
                printf(" . ");
            } else if (tab[i][j] == 2) {
                printf(" - ");
            } else {
                printf("   ");
            }
        } 
        printf("\n");
    }
}


int _Mover_Pecca_X(int x, int pecca, int rotate, int bloco) {
    switch (pecca) {
        case 1: // Posição X do T...
            if (rotate == 1) {
                if (bloco == 2 || bloco == 4) {
                    x = x - 2;
                } else if (bloco == 3) {
                    x = x - 4;
                }
            } else if (rotate == 2) {
                if (bloco != 1) {
                    x = x - 2;
                }
            } else if (rotate == 3) {
                if (bloco == 2 || bloco == 4) {
                    x  = x - 2;
                } else if (bloco == 3) {
                    x = x - 4;
                }
            } else if (rotate == 4) {
                if (bloco == 4) {
                    x = x - 2;
                }
            }
            break;
        
        case 2: // L
            if (rotate == 1) {
                if (bloco != 1) {
                    x = x - 2;
                }
            } else if (rotate == 2) {
                if (bloco == 2) {
                    x = x - 2;
                } else if (bloco == 3 || bloco == 4) {
                    x = x - 4;
                }
            } else if (rotate == 3) {
                if (bloco == 4) {
                    x = x - 2;
                }
            } else if (rotate == 4) {
                if (bloco == 2) {
                    x = x - 2;
                } else if (bloco == 3) {
                    x = x - 4;
                }
            }
            break;

        case 3:// I
            if (rotate == 2 || rotate == 4) {
                if (bloco == 2) {
                    x = x - 2; 
                } else if (bloco == 3) {
                    x = x - 4;
                } else if (bloco == 4) {
                    x = x - 6;
                }
            }
            break;

        case 4:// Z
            if (rotate == 1 || rotate == 3) {
                if (bloco == 2 || bloco == 3) {
                    x = x - 2;
                } else if (bloco == 4) {
                    x = x - 4;
                }
            } else if (rotate == 2 || rotate == 4) {
                if (bloco == 3 || bloco == 4) {
                    x = x - 2;
                }
            } 
            break;

        case 5:
            if (bloco == 3 || bloco == 4) {
                x = x - 2;
            }
            break;
    }

    return x;
}

int _Mover_Pecca_Y(int y, int pecca, int rotate, int bloco) {
    switch (pecca) {
        case 1:
            if (rotate == 1) {
                if (bloco == 4) {
                    y  = y - 1;
                }
            } else if (rotate == 2) {
                if (bloco == 1 || bloco == 3) {
                    y = y - 1;
                } else if (bloco == 4) {
                    y = y - 2;
                }
            } else if (rotate == 3) {
                if (bloco != 4) {
                    y = y - 1;
                }
            } else if (rotate == 4) {
                if (bloco == 2 || bloco == 4) {
                    y  = y - 1;
                } else if (bloco == 3) {
                    y = y - 2;
                }
            }
            break;

        case 2: // L
            if (rotate == 1) {
                if (bloco == 3) {
                    y = y - 1;
                } else if (bloco == 4) {
                    y = y - 2;
                }
            } else if (rotate == 2) {
                if (bloco != 4) {
                    y = y - 1;
                }
            } else if (rotate == 3) {
                if (bloco == 2) {
                    y = y - 1;
                } else if (bloco == 3 || bloco == 4) {
                    y = y - 2;
                }
            } else if (rotate == 4) {
                if (bloco == 4) {
                    y = y - 1;
                }
            }
            break;
        
        case 3:
            if (rotate == 1 || rotate == 3) {
                if (bloco == 2) {
                    y = y - 1;
                } else if (bloco == 3) {
                    y = y - 2;
                } else if (bloco == 4) {
                    y = y - 3;
                }
            }
            break;

        case 4:
            if (rotate == 1) {
                if (bloco == 3 || bloco == 4) {
                    y = y - 1;
                }
            } else if (rotate == 2 || rotate == 4) {
                if (bloco == 1 || bloco == 3) {
                    y = y - 1;
                } else if (bloco == 2) {
                    y = y - 2;
                } 
            } else if (rotate == 3) {
                if (bloco == 1 || bloco == 2) {
                    y = y - 1;
                }
            } 
            break;

        case 5:
            if (bloco == 2 || bloco == 3) {
                y = y - 1;
            }
            break;
    }

    return y;
}

int _Tem_Pecca(int tab[][12], int pecca, int rotaccao, int x, int y, int lado) {
    int pode_mover = 0;
    int tem_pecca = 0;

    switch (pecca)  {
        case 1: // T
            if (lado == 1) {
                if (rotaccao == 1) {
                    if (tab[y][(x - 6) / 2] == 1 || tab[y+1][(x - 4) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 2) {
                    if (tab[y-1][(x - 4) / 2] == 1 || tab[y][(x - 4) / 2] == 1 || tab[y+1][(x - 4) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 3) {
                    if (tab[y-1][(x - 4) / 2] == 1 || tab[y][(x - 6) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 4) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][(x + 2) / 2] == 1 || tab[y-2][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            } else if (lado == 2) {
                if (rotaccao == 1) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][x / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 2) {
                    if (tab[y+1][x/2] == 1 || tab[y][(x + 2) / 2] == 1 || tab[y-1][x / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 3) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y+1][x/2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 4) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][(x + 2) / 2] == 1 || tab[y-2][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            }
            break;

        case 2: // L
            if (lado == 1) {
                if (rotaccao == 1) {
                    if (tab[y][(x - 4) / 2] == 1 || tab[y-1][(x - 4) / 2] == 1 || tab[y-2][(x - 4) / 2] == 1) {
                        tem_pecca = 1;
                    }    
                } else if (rotaccao == 2) {
                    if (tab[y+1][(x - 6) / 2] == 1 || tab[y][(x - 6) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 3) {
                    if (tab[y][(x - 2) / 2] == 1 || tab[y-1][(x - 2) / 2] == 1 || tab[y-2][(x - 4) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 4) {
                    if (tab[y][(x - 6) / 2] == 1 || tab[y+1][(x - 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            } else if (lado == 2) {
                if (rotaccao == 1) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][x - 2] == 1 || tab[y-2][(x - 2) / 2] == 1) {
                        tem_pecca = 1;
                    }    
                } else if (rotaccao == 2) {
                    if (tab[y+1][(x - 2) / 2] == 1 || tab[y][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 3) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][(x + 2) / 2] == 1 || tab[y-2][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 4) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y+1][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            }
            break;

        case 3:
            if (lado == 1) {
                if (rotaccao == 1 || rotaccao == 3) {
                    if (tab[y][(x - 2) / 2] == 1 || tab[y-1][(x - 2) / 2] == 1 || tab[y-2][(x - 2) / 2] == 1 || tab[y-3][(x - 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 2 || rotaccao == 4) {
                    if (tab[y][(x - 8) / 2] == 1) {
                        tem_pecca = 1;
                    } 
                }
            } else if (lado == 2) {
                if (rotaccao == 1 || rotaccao == 3) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][(x + 2) / 2] == 1 || tab[y-2][(x + 2) / 2] == 1 || tab[y-3][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 2 || rotaccao == 4) {
                    if (tab[y][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            }
            break;

        case 4:
            if (lado == 1) {
                if (rotaccao == 1) {
                    if (tab[y][(x - 4) / 2] == 1 || tab[y-1][(x - 6) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 2 || rotaccao == 4) {
                    if (tab[y+1][(x - 4) / 2] == 1 || tab[y][(x - 4) / 2] == 1 || tab[y-1][(x - 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 3) {
                    if (tab[y-1][(x - 4) / 2] == 1 || tab[y][(x - 6) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            } else if (lado == 2) {
                if (rotaccao == 1 || rotaccao == 3) {
                    if (tab[y][(x + 2) / 2] == 1 || tab[y-1][x / 2] == 1) {
                        tem_pecca = 1;
                    }
                } else if (rotaccao == 2 || rotaccao == 4) {
                    if (tab[y+1][x / 2] == 1 || tab[y][(x + 2) / 2] == 1 || tab[y-1][(x + 2) / 2] == 1) {
                        tem_pecca = 1;
                    }
                }
            }
            break;

        case 5:
            if (lado == 1) {
                if (tab[y][(x - 4) / 2] == 1 || tab[y-1][(x - 4) / 2] == 1) {
                    tem_pecca = 1;
                }
            } else if (lado == 2) {
                if (tab[y][(x + 2) / 2] == 1 || tab[y - 1][(x + 2) / 2] == 1) {
                    tem_pecca = 1;
                }
            }
            break;
    }

    if (tem_pecca != 1) {
        pode_mover = 1;
    }

    return pode_mover;
}

int _Tem_Parrede(int x, int pecca, int rotaccao) {
    int pode_mover = 0;

    switch (pecca)  {
        case 1: // T
            if (rotaccao == 1 || rotaccao == 3) {
                if (x - 4 >= 2 && x  <= 20) {
                    pode_mover = 1;
                }
            } else if (rotaccao == 2 || rotaccao == 4) {
                if (x - 2 >= 2 && x <= 20) {
                    pode_mover = 1;
                }
            }
            break;

        case 2: // L
            if (rotaccao == 1 || rotaccao == 3) {
                if (x - 2 >= 2 && x <= 20) {
                    pode_mover = 1;
                }
            } else if (rotaccao == 2 || rotaccao == 4) {
                if (x - 4 >= 2 && x <= 20) {
                    pode_mover = 1;
                }
            }
            break;

        case 3:
            if (rotaccao == 1 || rotaccao == 3) {
                if (x >= 2 && x <= 20) {
                    pode_mover = 1;
                }
            } else if (rotaccao == 2 || rotaccao == 4) {
                if (x - 6 >= 2 && x <= 20) {
                    pode_mover = 1;
                } 
            }
            break;

        case 4:
            if (rotaccao == 1 || rotaccao == 3) {
                if (x - 4 >= 2 && x <= 20) {
                    pode_mover = 1;
                }
            } else if (rotaccao == 2 || rotaccao == 4) {
                if (x - 2 >= 2 && x <= 20) {
                    pode_mover = 1;
                }
            }
            break; 

        case 5:
            if (x - 2 >= 2 && x <= 20) {
                pode_mover = 1;
            }
            break;
    }

    return pode_mover;
}