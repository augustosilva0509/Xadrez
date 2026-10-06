#ifndef _ERROR_H_
#define _ERROR_H_

typedef enum Error{
    NONE,
    INVALID_USER_INPUT
} Error;

/*
    Define o erro atual como tratado.
    #### Parâmetro:
     - handled_error_code: o código do erro que foi tratado
    #### Retorno:
     - 0: tudo ocorreu bem;
     - -1: código de erro atual não bate com o código dado;
*/
int error_handled(Error handled_error_code);

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
void set_error_code(Error error_code);

/*
    Retorna o código de erro atual.
    #### Retorno:
     - error_code: inteiro que representa o código do erro atual.
*/
Error get_error_code();



#endif