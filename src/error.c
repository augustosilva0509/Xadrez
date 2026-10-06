#include "error.h"
#include <stdlib.h>
#include <stdio.h>

#define DEBUG

Error error_status = NONE;

void error_handled(Error handled_error_code){
    if(error_status == handled_error_code){
        error_status = NONE;
        return;
    }
    #ifdef DEBUG
    printf("Erro desconhecido, não tratado. Verifique a última chamada de error_handled()");
    #endif
    exit(-1);
}

void set_error_code(Error error_code){
    error_status = error_code;
    return;
}

Error get_error_code(){
    return error_status;
}

char* get_error_message(){
    switch (error_status)
    {
    case 1:
        return "Entrada inválida.";
    }
    return "Código de erro não encontrado.";
}