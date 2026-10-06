#include "error.h"

char* get_error_message(){
    switch (CHESS_ERROR_CODE)
    {
    case 1:
        return "Entrada inválida.";
    }
    return "Código de erro não encontrado.";
}