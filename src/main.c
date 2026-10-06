#include <stdio.h>
#include <Windows.h>
#include "interface.h"
#include "input_handler.h"
#include "error.h"

#define DEBUG

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int board[8][8] = {{2,3,4,5,6,4,3,2},{1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{7,7,7,7,7,7,7,7},{8,9,10,11,12,10,9,8}};
    
    draw_match_interface(board);

    int *user_input = NULL;
    do{
        if(get_error_code() == INVALID_USER_INPUT){
            print_message(get_error_message());
            print_message(" | Tente novamente\n");
            error_handled(INVALID_USER_INPUT);
        }
        user_input = get_user_ingame_input();
        
    }while(user_input == NULL);

    #ifdef DEBUG
    printf("%d,%d -> %d,%d", user_input[0], user_input[1], user_input[2], user_input[3]);
    #endif

    
    return 0;
}