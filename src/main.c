#include <stdio.h>
#include <Windows.h>
#include "interface.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int board[8][8] = {0};
    draw_match_interface(board);
    return 0;
}