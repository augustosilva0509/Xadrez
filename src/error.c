#include "error.h"

int CHESS_ERROR_CODE = 0;

void set_error(int error_code){
    CHESS_ERROR_CODE = error_code;
    return;
}

int get_error_code(){
    return CHESS_ERROR_CODE;
}

char* get_error_message(){
    switch (CHESS_ERROR_CODE)
    {
    case 1:
        return "Entrada inválida.";
    }
    return "Código de erro não encontrado.";
}