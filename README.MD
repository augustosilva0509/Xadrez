# Xadrez

Um jogo de xadrez usando da interface de linha de comando (CLI) do terminal.

### Objetivos de aprendizado com o projeto
- Desenvolver o meu primeiro projeto real usando o Git e o GitHub;
- Aprender a estrutura de um projeto desenvolvido em C;
- Aprender boas práticas de desenvolvimento de software;
- Desafiar os meus conhecimentos, assim como compreender o meu código antigo e não finalizado do mesmo projeto.

# Definição do projeto

## Interface
- Inteiramente no terminal; 
- O tabuleiro e as peças de xadrez serão representados através de caracteres especiais;
- O tabuleiro será apresentado junto as informações de localização - númeração 1..8 e letras a..h.

## Entradas do usuário
- Para realizar um movimento, o usuário deverá informar o local de origem da peça e o local de destino;
- As entradas serão realizadas em turnos, brancas e pretas.

## Regras do jogo
Serão seguidas as regras oficiais da FIDE.

## Sistema
1. Deve ser capaz de identificar jogadas inválidas, sendo elas:
    - Obstrução no caminho;
    - Peça cravada;
    - Direção inválida;
    - Alcance inválido;
    - Uso de peças do oponente.

2. Deve ser capaz de identificar o fim de um jogo, sendo as condições de fim de jogo:
    - Xeque-mate;
    - Afogamento;
    - Peças insuficientes;
    - Repetição;
    - 50 lances sem captura.

3. Deve tratar a entrada do usuário devidamente.