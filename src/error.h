#ifndef _ERROR_
#define _ERROR_



/*
    Retorna a mensagem do código de erro atual.
    #### Retorno -> (char *)
*/
char* get_error_message();

/*
    Define o código de erro atual.
    #### Parâmetro:
     - error_code: código do erro.
*/
void set_error_code(int error_code);

/*
    Retorna o código de erro atual.
    #### Retorno:
     - error_code: inteiro que representa o código do erro atual.
*/
int get_error_code();



#endif