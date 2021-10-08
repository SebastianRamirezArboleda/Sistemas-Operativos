#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

 int main(int argc, char *argv[]) {
    pid_t pidC;
    char *bsh;
    char text[20];
    int fd[2];
    pipe(fd);
    pidC = fork();
    int num[argc-1];

    switch (pidC)
    {
    case -1:
        printf("Error Creando Proceso Hijo");
        exit(EXIT_FAILURE);
    case 0:

        for(short i=0; i<argc-1;i++){
            read(fd[0],text,20);
            num[i] = strtol(text,&bsh,10);
        }
        float nume=0;
        for(short i=0;i<argc-1;i++){
            nume = nume + num[i];
        }
        nume = nume / (argc-1);
        printf("%f",nume);
        sprintf(text,"%f", nume);
        write(fd[1],text,20);
        break;
    default:
        for(short i=1;i<argc;i++){
            write(fd[1],argv[i],20);
        }
        wait(NULL);
        read(fd[0],text,20);
        printf("El resultado fue: %s",text);
        close(fd[0]);
        close(fd[1]);
        break;
    }
    exit(EXIT_SUCCESS);

 }