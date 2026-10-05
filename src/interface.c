#include "interface.h"

int main(){
    return 0;
}

void draw_match_interface(int board[8][8]){
    char* pieces[12]={"♙","♖","♘","♗","♕","♔","♟","♜","♞","♝","♛","♚"};
    system("cls");
    printf(" ╔══╤══╤══╤══╤══╤══╤══╤══╗\n");
    for(int i=0;i<8;i++){
        printf("%d│", 8-i);
        for(int j=0;j<8;j++){
            if(board[i][j]!=0){
                printf("%s │", pieces[board[i][j]-1]);
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