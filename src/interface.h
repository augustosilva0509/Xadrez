#ifndef _INTERFACE_H_
#define _INTERFACE_H_
/*
    Desenha e imprime o tabuleiro no terminal.
    #### Parãmetro:
    - board[8][8]: o estado do tabuleiro que deseja imprimir na tela.
*/
void draw_match_interface(int board[8][8]);

/*
    Imprime uma mensagem no terminal.
    #### Parâmetro:
    - message: a string que você quer imprimir no terminal.
*/
void print_message(char* message);

#endif