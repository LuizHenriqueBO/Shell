/* Historico de strings com no maximo 10 elementos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char HISTORIC[10][100] = {0};
int index_historic = 0;
int length_historic = 10;

void add_historic(char *value);     //  Adiciona um valor ao historico
char *get_historic(int pos);        //  Recupera um valor do historico, dado uma posicao
void free_historic();               //  Libera os espaços alocados com o historico
void print_historic();              //  Imprime o estado atual do historico

void add_historic(char *value)
{
    if (value[0] != '\0' && value[0] != '!' && (strcmp(value, "history") != 0))  // efetua um filtro sobre a entrada no histórico
    {
        strcpy(HISTORIC[index_historic], value);                        //  Adicionando dado no histórico
        index_historic = (index_historic + 1) % length_historic;        //  Incremento o indice da lista circular
    }
}

char *get_historic(int pos)                                             //  Função para pegar os históricos
{
    int i = index_historic - pos - 1;                                   //  Buscando a posição do index
    return HISTORIC[(length_historic + i) % length_historic];           //  Retornando o resultado
}

void free_historic()                                                    //  Libera o espaço de memória heap
{                                                                       //  utilizado para armazenar o histórico
    for (int i = 0; i < length_historic; i++)                            
        free(HISTORIC[i]);                                              //  Libera a posição    
}

void print_historic()                                                   //  imprimir historico
{
    for (int i = 0; i < length_historic && HISTORIC[i][0]; i++)         //  enquanto tiver algo no histórico,
        printf("%d: %s\n", i, get_historic(i));                         //  busca o histórico pelo index e imprima-o    
}