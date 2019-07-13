#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define size_alocar 100
char *remove_spaces_initals(char *str);
char *remove_space_final(char *str);
char *remove_spaces_both_sides(char *str);

char **split_string2(char *original, char *pattern);
char *spliting_string(char *ptr, char *pattern, int length_pattern, char **returned);

int search_word(char *comando, char *word) /*pesquisa palavra*/
{
    int i = (strstr(comando, word) == NULL);
    //char* i = (strstr(comando, word));
    
    //printf("%s",i);
    return i;//(strstr(comando, word) == NULL);
}

int wait_comand(char *comando)
{
    char ands[2] = {'&', '\0'};
    return search_word(comando, ands);
}

int comando_exit_search(char *comando)
{
    char is_exit[5] = {'e', 'x', 'i', 't', '\0'};
    return search_word(comando, is_exit);
}

char *comando_alocar()
{
    char *comando = (char *)calloc(size_alocar, sizeof(char));
    return comando;
}

char *comando_solicita(char *comando)
{
    comando[0] = '\0';
    setbuf(stdin, NULL);
    printf("user@user-PC: ");
    scanf("%[^\n]s", comando);
    setbuf(stdin, NULL);
    //printf("%s", comando);
    return comando;
}

char **args_alocar()
{
    char **args = (char **)calloc(size_alocar, sizeof(char *));
    for (int i = 0; i < size_alocar; i++)
    {
        args[i] = (char *)calloc(64, sizeof(char));
    }
    return args;
}

int args_fill(char **args, char *comando) /*funcao que preenche os args*/
{
    if (comando[0] == '\0')
    {
        //printf("comando sem argumentos!\n");
        return 0;
    }
    remove_spaces_both_sides(comando);

    int i = 0, col = 0;
    int line = 0;

    int tamanho = strlen(comando);
    //printf("%d", tamanho);
    int controle = 0;
    for (i = 0; i <= tamanho; i++)
    {
        controle = 0;

        if (comando[i] != ' ')
        {
            args[line][col] = comando[i];
            col++;
        }
        else
        {
            args[line][col] = '\0';
            col = 0;
            line++;
            controle = 1;
        }
    }

    if (controle == 0)
    {
        args[++line] = NULL;
    }
    else
    {
        args[line] = NULL;
    }
    //  args_print(args, *line);
    if (strcmp(args[0], "ls") == 0)
    {
        free(args[line]);
        args[line] = strdup("--color");
        args[line + 1] = NULL;
    }
    return 1;
}
/**
 * 
 * 
 * 
 * falta arrumar a parte de imprimir os dados, não esta funcionando.
 * 
 * 
 * 
 * */

void args_print(char **args) /*funcao pra imprimir o vetor de string*/
{
    int i = 0;

    while (args[i] != NULL)
    {
        printf("%s\n", args[i]);
        i++;
    }
}

void comando_deallocate(char *comando)
{
    free(comando);
    comando = NULL;
}

void args_deallocate(char **args) /*funcao de desalocar um vetor de string*/
{
    /*if (args == NULL)
    {
        return;
    }*/
    for (int i = 0; i < size_alocar; i++)
    {
        free(args[i]);
    }
    free(args);
    args = NULL;
}
/*
int last_space(char *str)
{
    int i;
    for (i = 0; *str && *str == ' '; i++, str++)
        ;
    return i;
}

void remove_spaces_initals(char *str)
{
    int index_last_space = last_space(str);
    int i, j;
    for (i = 0, j = index_last_space; str[j]; i++, j++)
        str[i] = str[j];
    str[i + 1] = '\0';
}
*/
void desalocar_Matriz(char **str, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        free(str[i]);
    }
    free(str);
    str = NULL;
}

char *indentify_pattern(char *original, char *pattern)
{
    static char *p = NULL;
    static char *token = NULL;
    static int length_pattern = 0;

    if (length_pattern == -1) // Condição de parada
    {
        length_pattern = 0;
        return NULL;
    }
    if (p == NULL) // Inicializando
    {
        length_pattern = strlen(pattern);
        p = original;
        token = strstr(p, pattern);
        *token = 0;
        return original;
    }
    if (length_pattern > 0) // Iterando
    {
        *token = *pattern;
        p = token + length_pattern;
        token = strstr(p, pattern);
        if (token)
        {
            *token = 0;
            return p;
        }
        else
        {
            length_pattern = -1;
            char *r = p;
            p = NULL;
            return r;
        }
    }
}

char *remove_spaces_initals(char *str)
{
    int i;
    char *p = str;
    for (i = 0; *p && *p == ' '; i++, p++)
        ;
    int index_last_space = i;
    int j;
    for (i = 0, j = index_last_space; str[j]; i++, j++)
        str[i] = str[j];
    str[i] = '\0';
    return str;
}

char *remove_space_final(char *str)
{
    int length = strlen(str), i;
    for (i = length - 1; i >= 0 && str[i] == ' '; i--)
        ;
    str[i + 1] = '\0';
    return str;
}

char *remove_spaces_both_sides(char *str)
{
    return remove_spaces_initals(remove_space_final(str));
}
/*-----------------------------------------------------*/

char **split_string2(char *original, char *pattern)
{
    size_t pattern_length = strlen(pattern);
    size_t n = 0;
    char *p;
    char *token;

    // encontra quantas vezes o modelo aparece na string
    for (p = original; token = strstr(p, pattern); p = token + pattern_length)
        n++;

    char **returned = calloc(n + 2, sizeof(char *)); // MALLOC returned

    if (returned != NULL)
    {
        p = original;
        for (int i = 0; p = spliting_string(p, pattern, pattern_length, &returned[i]); i++)
        {
            if (returned[i] == NULL)
            {
                while (i--)
                    free(returned[i - 1]);
                free(returned);
                return NULL;
            }
        }
    }

    return returned;
}

char *spliting_string(char *ptr, char *pattern, int length_pattern, char **returned)
{
    char *token = strstr(ptr, pattern);
    if (token)
    {
        *token = 0;
        *returned = strdup(ptr);
        *token = *pattern;
        return token + length_pattern;
    }
    *returned = strdup(ptr);
    return NULL;
}