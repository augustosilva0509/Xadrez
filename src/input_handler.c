#include "input_handler.h"
#include "error.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Transforma a posição do tabuleiro em indice da matriz
    #### Parâmetros:
    - x1 e x2: a..g
    - y1 e y2: 1..8

    #### Retorno -> (int *):
    - -1: erro
    - &index_pos: {x1, y1, x2, y2}; (alocado dinamicamente)
    
*/
int *pos_to_matrix_index(char x1, int y1, char x2, int y2)
{
    int *index_pos = (int *)malloc(sizeof(int) * 4);
    switch (x1)
    {
    case 'a':
        index_pos[0] = 0;
        break;
    case 'b':
        index_pos[0] = 1;
        break;
    case 'c':
        index_pos[0] = 2;
        break;
    case 'd':
        index_pos[0] = 3;
        break;
    case 'e':
        index_pos[0] = 4;
        break;
    case 'f':
        index_pos[0] = 5;
        break;
    case 'g':
        index_pos[0] = 6;
        break;
    case 'h':
        index_pos[0] = 7;
        break;
    default:
        CHESS_ERROR_CODE = 1;
        return NULL;
    }
    switch (x2)
    {
    case 'a':
        index_pos[2] = 0;
        break;
    case 'b':
        index_pos[2] = 1;
        break;
    case 'c':
        index_pos[2] = 2;
        break;
    case 'd':
        index_pos[2] = 3;
        break;
    case 'e':
        index_pos[2] = 4;
        break;
    case 'f':
        index_pos[2] = 5;
        break;
    case 'g':
        index_pos[2] = 6;
        break;
    case 'h':
        index_pos[2] = 7;
        break;
    default:
        CHESS_ERROR_CODE = 1;
        return NULL;
    }
    switch (y1)
    {
    case 1:
        index_pos[1] = 7;
        break;
    case 2:
        index_pos[1] = 6;
        break;
    case 3:
        index_pos[1] = 5;
        break;
    case 4:
        index_pos[1] = 4;
        break;
    case 5:
        index_pos[1] = 3;
        break;
    case 6:
        index_pos[1] = 2;
        break;
    case 7:
        index_pos[1] = 1;
        break;
    case 8:
        index_pos[1] = 0;
        break;
    default:
        CHESS_ERROR_CODE = 1;
        return NULL;
    }
    switch (y2)
    {
    case 1:
        index_pos[3] = 7;
        break;
    case 2:
        index_pos[3] = 6;
        break;
    case 3:
        index_pos[3] = 5;
        break;
    case 4:
        index_pos[3] = 4;
        break;
    case 5:
        index_pos[3] = 3;
        break;
    case 6:
        index_pos[3] = 2;
        break;
    case 7:
        index_pos[3] = 1;
        break;
    case 8:
        index_pos[3] = 0;
        break;
    default:
        CHESS_ERROR_CODE = 1;
        return NULL;
    }
}

int* get_user_ingame_input(){
    int y1,y2;
    char x1,x2;
    print_message("Digite o movimento (ex.: e2 e4): ");
    scanf("%c%d %c%d ", &x1, &y1, &x2, &y2);
    fflush(stdin);
    return pos_to_matrix_index(x1,y1,x2,y2);
}