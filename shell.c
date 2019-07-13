#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    /* fork(), execv(), getpid(), getppid() */
#include <sys/types.h> /* pid_t type */
//#include <errno.h>
#include <sys/wait.h> /* wait() */
#include <string.h>

#include "lib.h"
#include "hist.h"

void child(char **args);
void exe(char *cmd, int is_wait);
void forking(char *cmd, int is_wait);
void father(int is_wait, pid_t child_pid);

void child(char **args)
{
    execvp(args[0], args);
    printf("Unknown command\n");
    exit(0);
}

void father(int is_wait, pid_t child_pid)
{
    if (is_wait == 0)
    {
        int child_status ;
        pid_t tpid;
        tpid = wait(&child_status);
 
        do
        {
            tpid = wait(&child_status);
        } while (tpid != child_pid);
    }
}

void exe(char *cmd, int is_wait)
{
    if (strcmp(cmd, "history") == 0)
        print_historic();
    else
    {
        if (strcmp(cmd, "!!") == 0)
            cmd = get_historic(0);
        else if (cmd[0] == '!')
            cmd = get_historic(atoi(cmd + 1));

        char **args = args_alocar();
        int make_run = args_fill(args, cmd);

        if (make_run)
        {
            pid_t pid = fork();

            if (pid > 0)
                father(is_wait, pid);
            if (pid == 0)
                child(args);

            if (pid < 0) // caso der erro no fork
                perror("fork");
        }
        args_deallocate(args); // FREE args
    }
}

int main()
{
    //string ls = "ls";

    //int should_run = 1;
    char comando[100];
    char *p, *token, *cmd;
    while (1)
    {
        comando[0] = '\0';
        printf("user@user-PC: ");
        scanf("%[^\n]s\0", comando);
        setbuf(stdin, NULL);
        add_historic(comando);
        int is_wait = wait_comand(comando);

        for (p = comando; token = strstr(p, "&"); p = token + 1)
        {
            *token = 0;
            if (strcmp(p, "exit") == 0)
                exit(0);
            if (p[0] != '\0' && p[0] != ' ')
                exe(p, is_wait);
            *token = '&';
        }
        if (strcmp(p, "exit") == 0)
            exit(0);
        exe(p, is_wait);
    }
    return 0;
}

/*acho que to pegando o pid do pai, logo tenho que pegar do filho*/