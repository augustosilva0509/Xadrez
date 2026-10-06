#include "error.h"

char* get_error_message(){
    switch (ERROR_CODE)
    {
    case 1:
        return "Entrada inválida.";
    }
    return "Código de erro não encontrado.";
}