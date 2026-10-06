#include "error.h"
#include <string.h>

char* get_error_message(){
    char *error_message = "Código de erro não encontrado.";
    switch (ERROR_CODE)
    {
    case 1:
        return "Entrada inválida.";
    }
    return error_message;
}