#include <stdio.h>
#include <Windows.h>

/*
    Desenha o tabuleiro no terminal.
*/
void draw(int tabuleiro[8][8]);
/*
    Realiza a função módulo em n1.
     - Retorna n1 caso n1 seja maior do que 0.
     - Retorna n1*(-1) caso n1 seja menor do que 0.
*/
int modulus(int n1);
/*
    Verifica se o movimento dado pelo usuário é válido.
     - Retorna 0 caso não seja válido e 1 caso seja um movimento válido.
*/
int validateMove(int tabuleiro[8][8], int y0, int x0, int y, int x, int can_en_passant[2], int can_castle[2][2]);
/*
    Verifica se a captura de peça é legal.
     - Retorna 0 caso não seja uma captura valida.
     - Returna 1 caso não seja uma captura.
     - Retorna 2 caso seja uma captura válida.
*/
int validateCapture(int op_piece, int piece);
/*
    Verifica se a casa na posição x,y está em cheque.
     - Retorna 1 caso esteja e 0 caso não.
     - who_plays = 1 representa as brancas, who_plays = 0 representa as pretas.
     - *check_direction é a direção na qual vem o cheque.
     - is_king_valid, indica se o rei pode contar como peça para dar o cheque. 
*/
int squareChecked(int board[8][8], int who_plays, int x, int y, int* check_direction, int is_king_valid, int* check_count);
/*
    Faz as mudanças no tabuleiro.
     - Trata do movimento da torre no roque.
*/
void changeBoard(int board[8][8], int x0, int y0, int x, int y);
/*
    Verifica se o caminho que a peca vai tomar está livre.
     - Retorna 1 caso esteja livre, e 0 caso não.
*/
int verifyClearPath(int board[8][8], int x0, int y0, int x, int y);
/*
    Verifica se a peça movimentada é a de quem deve jogar.
     - Retorna 0 caso a peça não for do jogador atual, e 1 caso seja.
     - who_plays = 1 representa as brancas, who_plays = 0 representa as pretas.
    
*/
int verifyWhoPlays(int board[8][8], int who_plays, int x0, int y0);
/*
    Verifica se o rei do jogador está em cheque.
     - Retorna 0 falso, e 1 verdadeiro.
     - who_plays = 1 representa as brancas, who_plays = 0 representa as pretas.
*/
int verifyCheck(int board[8][8], int who_plays);
/*
    Verifica se o cheque resulta em um chequemate.
     - Retorna 0 falso, e 1 verdadeiro.
     - who_plays = 1 representa as brancas, who_plays = 0 representa as pretas.
*/
int verifyCheckmate(int board[8][8], int who_plays);
/*
    Verifica se o jogador em cheque pode recusa-lo, comendo uma peça ou jogando outra em frente.
*/
int canRefuseCheck(int board[8][8], int who_plays, int check_direction, int x, int y);

int main(){
    SetConsoleOutputCP(CP_UTF8);
    /*
        Matriz Tabuleiro
         - Cada peca preta terá um identificador, 1=peao; 2=torre; 3=cavalo;  4=bispo;  5=rainha;  6=rei.
         - Cada peca branca terá um identificador, 7=peao; 8=torre; 9=cavalo; 10=bispo; 11=rainha; 12=rei.
         - Peça nula é identificada como 0.
    */
    int tabuleiro[8][8] = {{2,3,4,5,6,4,3,2},{1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{7,7,7,7,7,7,7,7},{8,9,10,11,12,10,9,8}};
    //int tabuleiro[8][8] = {{2,3,4,5,6,4,3,2},{1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,2,0,0,0},{0,0,1,2,3,0,0,0},{7,0,0,0,0,2,0,0},{0,0,0,0,12,0,0,0}};
    /*
        Array canEnPassant:
         - index 0: representa a coluna que foi feito o último movimento de duas casas com o peão das brancas
         - index 1: representa a coluna que foi feito o último movimento de duas casas com o peão das pretas
         - valor -1 representa que não teve nenhum movimento de duas casas com o peão do determinado jogador.
    */
    int can_en_passant[2] = {-1,-1};
    /*
        Matriz can_castle:
         - Representa a possibilidade de fazer o roque em cada lado do rei de cada jogador.
         - Sendo 1 possível, e 0 não possível.
    */
    int can_castle[2][2] = {{1,1},{1,1}};
    
    int valid_move = 0;
    int x0=-1; int y0=-1; int x=-1; int y=-1;
    char c_x0, c_x;
    int who_plays = 0;
    int in_check = 0;
    
    while(1==1){
        draw(tabuleiro);
        while(valid_move==0){
            scanf(" %c%d %c%d", &c_x0, &y0, &c_x, &y);
            switch(c_x0){
            case 'a':
                x0=0;
                break;
            case 'b':
                x0=1;
                break;
            case 'c':
                x0=2;
                break;
            case 'd':
                x0=3;
                break;
            case 'e':
                x0=4;
                break;
            case 'f':
                x0=5;
                break;
            case 'g':
                x0=6;
                break;
            case 'h':
                x0=7;
                break;
            default:
                x0= -1;
                break;
            }
            switch(c_x){
            case 'a':
                x=0;
                break;
            case 'b':
                x=1;
                break;
            case 'c':
                x=2;
                break;
            case 'd':
                x=3;
                break;
            case 'e':
                x=4;
                break;
            case 'f':
                x=5;
                break;
            case 'g':
                x=6;
                break;
            case 'h':
                x=7;
                break;
            default:
                x= -1;
                break;
            }
            switch(y0){
            case 1:
                y0=7;
                break;
            case 2:
                y0=6;
                break;
            case 3:
                y0=5;
                break;
            case 4:
                y0=4;
                break;
            case 5:
                y0=3;
                break;
            case 6:
                y0=2;
                break;
            case 7:
                y0=1;
                break;
            case 8:
                y0=0;
                break;
            default:
                y0= -1;
                break;
            }
            switch(y){
            case 1:
                y=7;
                break;
            case 2:
                y=6;
                break;
            case 3:
                y=5;
                break;
            case 4:
                y=4;
                break;
            case 5:
                y=3;
                break;
            case 6:
                y=2;
                break;
            case 7:
                y=1;
                break;
            case 8:
                y=0;
                break;
            default:
                y= -1;
                break;
            }
            if(x0==-1 || y0==-1 || x==-1 || y==-1){
                printf("Movimento invalido! %d,%d -> %d,%d\n", x0,y0,x,y);
                continue;
            }
            
            if(verifyWhoPlays(tabuleiro, who_plays, x0, y0) == 0){
                continue;
            }
            valid_move = validateMove(tabuleiro, x0, y0, x, y, can_en_passant, can_castle);
        }
        changeBoard(tabuleiro, x0, y0, x, y);
        if(x0 == 0 && y0 == 0){
            can_castle[1][0] = 0;
        }
        else if(x0 == 0 && y0 == 7){
            can_castle[0][0] = 0;
        }
        else if(x0 == 7 && y0 == 0){
            can_castle[1][1] = 0;
        }
        else if(x0 == 7 && y0 == 7){
            can_castle[0][1] = 0;
        }
        else if(x0 == 4 && y0 == 7){
            can_castle[0][0] = 0;
            can_castle[0][1] = 0;
        }
        else if(x0 == 4 && y0 == 0){
            can_castle[1][0] = 0;
            can_castle[1][1] = 0;
        }
        who_plays = (who_plays==0) ? 1 : 0;
        valid_move=0;
        fflush(stdin);
        in_check = verifyCheck(tabuleiro, who_plays);
        printf("%s em cheque: %d\n", (who_plays)?"pretas":"brancas", in_check);

        if(in_check == 1){
            printf("%s em chequemate: %d\n", (who_plays)?"pretas":"brancas", verifyCheckmate(tabuleiro, who_plays));
        }
        
        system("pause");
        x0 = -1; y0 = -1; x = -1; y = -1;
    }
    
    return 0;
}

int verifyStalemate(int board[8][8], int who_plays){

}

int canMove(int board[8][8], int x, int y){

}

int canRefuseCheck(int board[8][8], int who_plays, int check_direction, int x, int y){
    int refuse_check = 0;
    int is_king_check = 0;
    switch (check_direction)
    {
    case 0:
        if(squareChecked(board, (who_plays) ? 0 : 1, x+2, y+1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 1:
        if(squareChecked(board, (who_plays) ? 0 : 1, x-2, y+1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 2:
        if(squareChecked(board, (who_plays) ? 0 : 1, x+2, y-1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 3:
        if(squareChecked(board, (who_plays) ? 0 : 1, x-2, y-1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 4:
        if(squareChecked(board, (who_plays) ? 0 : 1, x+1, y+2, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 5:
        if(squareChecked(board, (who_plays) ? 0 : 1, x-1, y+2, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 6:
        if(squareChecked(board, (who_plays) ? 0 : 1, x+1, y-2, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 7:
        if(squareChecked(board, (who_plays) ? 0 : 1, x-1, y-2, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 8:
        if(squareChecked(board, (who_plays) ? 0 : 1, x+1, y+1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 9:
        if(squareChecked(board, (who_plays) ? 0 : 1, x-1, y+1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 10:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x+i, y, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y][x+i]!=0)
                break;
        }
        break;
    case 11:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x, y+i, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y+i][x]!=0)
                break;
        }
        break;
    case 12:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x+i, y+i, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y+i][x+i]!=0)
                break;
        }
        break;
    case 13:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x-i, y, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y][x-i]!=0)
                break;
        }
        break;
    case 14:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x, y-i, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y-i][x]!=0)
                break;
        }
        break;
    case 15:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x-i, y-i, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y-i][x-i]!=0)
                break;
        }
        break;
    case 16:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x+i, y-i, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y-i][x+i]!=0)
                break;
        }
        break;
    case 17:
        for(int i=1;i<8;i++){
            if(squareChecked(board, (who_plays) ? 0 : 1, x-i, y+i, NULL, 0, NULL)){
                refuse_check = 1;
                break;
            }
            if(board[y+i][x-i]!=0)
                break;
        }
        break;
    case 18:
        if(squareChecked(board, (who_plays) ? 0 : 1, x+1, y-1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    case 19:
        if(squareChecked(board, (who_plays) ? 0 : 1, x-1, y-1, NULL, 0, NULL))
            refuse_check = 1;
        break;
    default:
        break;
    }
    return refuse_check;
}

int verifyCheck(int board[8][8], int who_plays){
    int x, y;
    int in_check = 0;
    int king = (who_plays) ? 6 : 12;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == king){
                x = j;
                y = i;
            }
        }
    }
    int check_direction = 0;
    int check_count = 0;
    in_check = squareChecked(board, who_plays, x, y, &check_direction, 0, &check_count);
    if(in_check && check_count == 1){
        in_check = (canRefuseCheck(board, who_plays, check_direction, x, y)) ? 0 : 1;
    }
    return in_check;
}

int verifyCheckmate(int board[8][8], int who_plays){
    int x, y;
    int king = (who_plays) ? 6: 12;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == king){
                x = j;
                y = i;
            }
        }
    }
    
    int checks = 1;
    if(x-1 >= 0){
        if(squareChecked(board, who_plays, x-1, y, NULL, 1, NULL) == 1 || board[y][x-1] != 0){
            checks++;
        }
        if(y-1 >= 0){
            if(squareChecked(board, who_plays, x-1, y-1, NULL, 1, NULL) == 1 || board[y-1][x-1] != 0){
                checks++;
            }
        }
        else{
            checks++;
        }
        if(y+1 < 8){
            if(squareChecked(board, who_plays, x-1, y+1, NULL, 1, NULL) == 1 || board[y+1][x-1] != 0){
                checks++;
            }
        }
        else{
            checks++;
        }
    }
    else{
        checks += 3;
    }

    if(x+1 < 8){
        if(squareChecked(board, who_plays, x+1, y, NULL, 1, NULL) == 1 || board[y][x+1] != 0){
            checks++;
        }
        if(y-1 >= 0){
            if(squareChecked(board, who_plays, x+1, y-1, NULL, 1, NULL) == 1 || board[y-1][x+1] != 0){
                checks++;
            }
        }
        else{
            checks++;
        }
        
        if(y+1 < 8){
            if(squareChecked(board, who_plays, x+1, y+1, NULL, 1, NULL) == 1 || board[y+1][x+1] != 0){
                checks++;
            }
        }
        else{
            checks++;
        }
    }
    else{
        checks += 3;
    }

    if(y-1 >= 0){
        if(squareChecked(board, who_plays, x, y-1, NULL, 1, NULL) == 1 || board[y-1][x] != 0){
            checks++;
        }
    }
    else{
        checks++;
    }

    if(y+1 < 8){
        if(squareChecked(board, who_plays, x, y+1, NULL, 1, NULL) == 1 || board[y+1][x] != 0){
            checks++;
        }
    }
    else{
        checks++;
    }
    return (checks == 9) ? 1 : 0;
}

int verifyWhoPlays(int board[8][8], int who_plays, int x0, int y0){
    if(who_plays==0 && board[y0][x0] <= 6){
        printf("Vez das brancas!\n");
        return 0;
    }
    else if(who_plays==1 && board[y0][x0] >= 7){
        printf("Vez das pretas!\n");
        return 0;
    }
    return 1;
}

int modulus(int n){
    if(n < 0){
        n = n*(-1);
    }
    return n;
}

int validateMove(int tabuleiro[8][8], int x0, int y0, int x, int y, int can_en_passant[2], int can_castle[2][2]){
    int valid_move = 0;
    int valid_capture = validateCapture(tabuleiro[y][x], tabuleiro[y0][x0]);
    int mult_x = 1;
    int mult_y = 1;
    if(valid_capture == 0){
        return 0;
    }

    switch (tabuleiro[y0][x0])
    {
    case 0: // VAZIO
        return 0;
        break;
    case 2: // TORRE PRETA
    case 8: // TORRE BRANCA
        if((modulus(x-x0) != 0 && modulus(y-y0) == 0) || (modulus(x-x0) == 0 && modulus(y-y0) != 0)){
            valid_move = 1;
        }
        if(verifyClearPath(tabuleiro,x0,y0,x,y) == 0){
            valid_move = 0;
        }
        break;
    case 4: // BISPO PRETO
    case 10: // BISPO BRANCO
        if(modulus(x-x0) - modulus(y-y0) == 0){
            valid_move = 1;
        }
        if(verifyClearPath(tabuleiro,x0,y0,x,y) == 0){
            valid_move = 0;
        }
        break;
    case 5: // DAMA PRETA
    case 11: // DAMA BRANCA
        if(((modulus(x-x0) != 0 && modulus(y-y0) == 0) || (modulus(x-x0) == 0 && modulus(y-y0) != 0)) || (modulus(x-x0) - modulus(y-y0) == 0)){
            valid_move = 1;
        }
        if(verifyClearPath(tabuleiro,x0,y0,x,y) == 0){
            valid_move = 0;
        }
        break;
    case 3: // CAVALO PRETO
    case 9: // CAVALO BRANCO
        if((modulus(x-x0)==2 && modulus(y-y0)==1) || (modulus(x-x0)==1 && modulus(y-y0)==2)){
            valid_move = 1;
        }
        break;
    case 1: // PEAO PRETO
        if(y-y0 == 2 && x-x0==0 && y0 == 1){
            valid_move = 1;
            can_en_passant[1] = x;
        }
        else if(y-y0 == 1 && x-x0==0){
            valid_move = 1;
        }
        else if(y-y0 == 1 && modulus(x-x0)==1 && valid_capture == 2){
            valid_move = 1;
        }
        else if(y-y0 == 1 && modulus(x-x0)==1 && can_en_passant[0] == x){
            valid_move = 1;
        }
        break;
    case 7: // PEAO BRANCO
        if(y-y0 == -2 && x-x0==0 && y0 == 6){
            valid_move = 1;
            can_en_passant[1] = x;
        }
        else if(y-y0 == -1 && x-x0==0){
            valid_move = 1;
        }
        else if(y-y0 == -1 && modulus(x-x0)==1 && valid_capture == 2){
            valid_move = 1;
        }
        else if(y-y0 == -1 && modulus(x-x0)==1 && can_en_passant[0] == x){
            valid_move = 1;
        }
        break;
    case 6: // REI PRETO
        if((modulus(x-x0) <= 1 && modulus(y-y0) <= 1)){
            valid_move = 1;
        }
        else if(x-x0 == -2 && y-y0 == 0 && can_castle[1][0] == 1 && squareChecked(tabuleiro, 1, x0+1, y, NULL, 1, NULL) == 0 && tabuleiro[y0][x0-1] == 0){
            valid_move = 1;
        }
        else if(x-x0 == 2 && y-y0 == 0 && can_castle[1][1] == 1 && squareChecked(tabuleiro, 1, x0+1, y, NULL, 1, NULL) == 0 && tabuleiro[y0][x0+1] == 0){
            valid_move = 1;
        }
        if(squareChecked(tabuleiro, 1, x, y, NULL, 1, NULL) == 1){
            valid_move = 0;
        }
        break;
    case 12: // REI BRANCO
        if((modulus(x-x0) <= 1 && modulus(y-y0) <= 1)){
            valid_move = 1;
        }
        else if(x-x0 == -2 && y-y0 == 0 && can_castle[0][0] == 1 && squareChecked(tabuleiro, 0, x0-1, y, NULL, 1, NULL) == 0 && tabuleiro[y0][x0-1] == 0){
            valid_move = 1;
        }
        else if(x-x0 == 2 && y-y0 == 0 && can_castle[0][1] == 1 && squareChecked(tabuleiro, 0, x0+1, y, NULL, 1, NULL) == 0 && tabuleiro[y0][x0+1] == 0){
            valid_move = 1;
        }
        if(squareChecked(tabuleiro, 0, x, y, NULL, 1, NULL) == 1){
            valid_move = 0;
        }
        break;
    default:
        break;
    }
    return valid_move;
}

int verifyClearPath(int board[8][8], int x0, int y0, int x, int y){
    int clear_path = 1;
    int mult_x = 1;
    int mult_y = 1;
    int dist = 0;

    if(modulus(x-x0) != 0 && modulus(y-y0) == 0){
        mult_y = 0;
        dist = modulus(x-x0);
        if(x < x0){
            mult_x = -1;
        }
    }
    else if(modulus(x-x0) == 0 && modulus(y-y0) != 0){
        mult_x = 0;
        dist = modulus(y-y0);
        if(y < y0){
            mult_y = -1;
        }
    }
    else if(modulus(x-x0) - modulus(y-y0) == 0){
        dist = modulus(x-x0);
        if(x < x0){
            mult_x = -1;
        }
        if(y < y0){
            mult_y = -1;
        }
    }

    for(int i=1; i < dist; i++){
        if(board[y0+i*mult_y][x0+i*mult_x] != 0){
            clear_path = 0;
        }
    }
    return clear_path;
}

int validateCapture(int op_piece, int piece){
    if(op_piece == 0){
        return 1;
    }
    else if((piece<=6 && op_piece<=6 || piece>=7 && op_piece>=7))
        return 0;
    return 2;
}

int squareChecked(int board[8][8], int who_plays, int x, int y, int* check_direction, int is_king_valid, int* check_count){
    int check = 0;
    int oponent_pieces[6] = {1,2,3,4,5,6};
    if(who_plays == 1){
        for(int i=0;i<6;i++){
            oponent_pieces[i] += 6;
        }
    }
        
    // CAVALOS
    if(x+2 < 8 && y+1 < 8){
        if(board[y+1][x+2] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 0;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x-2 >= 0 && y+1 < 8){
        if(board[y+1][x-2] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 1;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x+2 < 8 && y-1 >= 0){
        if(board[y-1][x+2] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 2;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x-2 >= 0 && y-1 >= 0){
        if(board[y-1][x-2] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 3;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x+1 < 8 && y+2 < 8){
        if(board[y+2][x+1] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 4;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x-1 >= 0 && y+2 < 8){
        if(board[y+2][x-1] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 5;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x+1 < 8 && y-2 >= 0){
        if(board[y-2][x+1] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 6;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    if(x-1 >= 0 && y-2 >= 0){
        if(board[y-2][x-1] == oponent_pieces[2]){
            check = 1;
            if(check_direction!=NULL)
                *check_direction = 7;
            if(check_count!=NULL)
                *check_count += 1;
        }
    }
    // PEOES
    if(who_plays==1){
        if(y+1 < 8){
            if(x-1 >= 0){
                if(board[y+1][x-1] == oponent_pieces[0]){
                    check = 1;
                if(check_direction!=NULL)
                    *check_direction = 8;
                if(check_count!=NULL)
                    *check_count += 1;
                }
            }
            if(x+1 < 8){
                if(board[y+1][x+1] == oponent_pieces[0]){
                    check = 1;
                if(check_direction!=NULL)
                    *check_direction = 9;
                if(check_count!=NULL)
                    *check_count += 1;
                }
            }
        }
    } else {
        if(y-1 >=0){
            if(x-1 >= 0){
                if(board[y-1][x-1] == oponent_pieces[0]){
                    check = 1;
                if(check_direction!=NULL)
                    *check_direction = 18;
                if(check_count!=NULL)
                    *check_count += 1;
                }
            }
            if(x+1 < 8){
                if(board[y-1][x+1] == oponent_pieces[0]){
                    check = 1;
                if(check_direction!=NULL)
                    *check_direction = 19;
                if(check_count!=NULL)
                *check_count += 1;
                }
            }
        }
    }
    
    // DEMAIS PEÇAS
    int continue_direction[8] = {1,1,1,1,1,1,1,1};
    for(int i=1;i<8;i++){
        if(x+i < 8 && continue_direction[0] == 1){
            if(board[y][x+i] != 0){
                continue_direction[0] = 0;
            }
            if(board[y][x+i] == oponent_pieces[1] || board[y][x+i] == oponent_pieces[4] || (board[y][x+i] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 10;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
        if(y+i < 8 && continue_direction[1] == 1){
            if(board[y+i][x] != 0){
                continue_direction[1] = 0;
            }
            if(board[y+i][x] == oponent_pieces[1] || board[y+i][x] == oponent_pieces[4] || (board[y+i][x] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 11;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
        if(x+i < 8 && y+i < 8 && continue_direction[2] == 1){
            if(board[y+i][x+i] != 0){
                continue_direction[2] = 0;
            }
            if(board[y+i][x+i] == oponent_pieces[3] || board[y+i][x+i] == oponent_pieces[4] || (board[y+i][x+i] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 12;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }

        if(x-i >= 0 && continue_direction[3] == 1){
            if(board[y][x-i] != 0){
                continue_direction[3] = 0;
            }
            if(board[y][x-i] == oponent_pieces[1] || board[y][x-i] == oponent_pieces[4] || (board[y][x-i] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 13;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
        if(y-i >= 0 && continue_direction[4] == 1){
            if(board[y-i][x] != 0){
                continue_direction[4] = 0;
            }
            if(board[y-i][x] == oponent_pieces[1] || board[y-i][x] == oponent_pieces[4] || (board[y-i][x] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 14;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
        if(x-i >= 0 && y-i >= 0 && continue_direction[5] == 1){
            if(board[y-i][x-i] != 0){
                continue_direction[5] = 0;
            }
            if(board[y-i][x-i] == oponent_pieces[3] || board[y-i][x-i] == oponent_pieces[4] || (board[y-i][x-i] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 15;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
        if(x+i < 8 && y-i >= 0 && continue_direction[6] == 1){
            if(board[y-i][x+i] != 0){
                continue_direction[6] = 0;
            }
            if(board[y-i][x+i] == oponent_pieces[3] || board[y-i][x+i] == oponent_pieces[4] || (board[y-i][x+i] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 16;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
        if(x-i >= 0 && y+i < 8 && continue_direction[7] == 1){
            if(board[y+i][x-i] != 0){
                continue_direction[7] = 0;
            }
            if(board[y+i][x-i] == oponent_pieces[3] || board[y+i][x-i] == oponent_pieces[4] || (board[y+i][x-i] == oponent_pieces[5] && i == 1 && is_king_valid == 1)){
                check = 1;
                if(check_direction!=NULL)
                    *check_direction = 17;
                if(check_count!=NULL)
                    *check_count += 1;
                break;
            }
        }
    }
    
    
    return check;
}

void changeBoard(int board[8][8], int x0, int y0, int x, int y){
    board[y][x] = board[y0][x0];
    board[y0][x0] = 0;
    if(board[y][x] == 12){
        if(x-x0 == -2){
            board[y][x+1] = 8;
            board[y][0] = 0;
            
        }
        else if(x-x0 == 2){
            board[y][x-1] = 8;
            board[y][7] = 0;
        }
    }
    else if(board[y][x] == 6){
        if(x-x0 == -2){
            board[y][x+1] = 2;
            board[y][0] = 0;
            
        }
        else if(x-x0 == 2){
            board[y][x-1] = 2;
            board[y][7] = 0;
        }
    }

}

void draw(int tabuleiro[8][8]){
    char* pieces[12]={"♙","♖","♘","♗","♕","♔","♟","♜","♞","♝","♛","♚"};
    system("cls");
    printf(" ╔══╤══╤══╤══╤══╤══╤══╤══╗\n");
    for(int i=0;i<8;i++){
        printf("%d│", 8-i);
        for(int j=0;j<8;j++){
            if(tabuleiro[i][j]!=0){
                printf("%s │", pieces[tabuleiro[i][j]-1]);
            }
            else{
                if(i%2==0){
                    if(j%2==0){
                        printf("██│");
                    } else {
                        printf("░░│");
                    }
                } else {
                    if(j%2==0){
                        printf("░░│");
                    } else {
                        printf("██│");
                    }
                }
            }
        }
        if(i!=7){
            printf("\n ╟──┼──┼──┼──┼──┼──┼──┼──╢\n");
        }else{
            printf("\n ╚══╧══╧══╧══╧══╧══╧══╧══╝\n");
        }
    }
    printf("  a  b  c  d  e  f  g  h\n\n");
}
