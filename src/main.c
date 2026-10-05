#include <stdio.h>
#include <Windows.h>
#include "interface.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int board[8][8] = {{2,3,4,5,6,4,3,2},{1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{7,7,7,7,7,7,7,7},{8,9,10,11,12,10,9,8}};
    
    draw_match_interface(board);
    return 0;
}