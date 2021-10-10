#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>

void upper(char *buffer);
void words(char *buffer);
void vowels(char *buffer);
void *procesohilo(void *param);
void ECHOoff();

// Cantidad De casos posibles en el switch
int conv = 5;

int main(int argc, char **argv)
{
    ECHOoff();
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        perror("No se pudo abrir el archivo: ");
        return (EXIT_FAILURE);
    }

    pthread_t threadID;
    pthread_create(&threadID, NULL, &procesohilo, NULL);

    char buffer[256];
    char *status = NULL;
    // Leer todo el archivo e imprimir segun el conv
    do
    {
        status = fgets(buffer, sizeof(buffer), fin);
        if (status != NULL)
        {
            switch (conv)
            {
                //Codigo para el upper case
            case 1: 
                printf("Original: %s", buffer);                
                upper(buffer);
                sleep(1);
                break;
                //Cuenta la cantidad de palabras
            case 2: 
                printf("Original: %s", buffer);                
                words(buffer);
                sleep(1);
                break;
                //Vowels
            case 3: 
                printf("Original: %s", buffer);                
                vowels(buffer);
                sleep(1);
                break;
                //None
            case 4:
                printf("%s", buffer);
                sleep(1);
                break;
                //default
            default:
                printf("%s", buffer);
                sleep(1);
                break;
            }
        }
    } while (status != NULL);
}

void upper(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        buffer[i] = toupper(buffer[i]);
    }
    printf("Se paso a UPPER: %s", buffer);
}

void words(char *buffer)
{
    int contador = 0;
    int largo = strlen(buffer);

    for (int i = 0; i < largo; i++)
    {
        if (buffer[i] == ' ' && buffer[i + 1] != ' ')
        {
            contador++;
        }
    }
    printf("Se paso a Contar cantidad de palabras: %d\n", contador);
}

void vowels(char *cadena)
{
    int vocales = 0;
    for (int indice = 0; cadena[indice] != '\0'; ++indice)
    {
        char letraActual = tolower(cadena[indice]);
        if (letraActual == 'a' || letraActual == 'e' || letraActual == 'i' || letraActual == 'o' || letraActual == 'u')
        {
            vocales++;
        }
    }
    printf("Se paso a contar cantidad de vocales: %d\n", vocales);
}
void *procesohilo(void *param)
{
    ECHOoff();
    char respuesta[16];
    while (1)
    {
        scanf("%s", respuesta);
        
        for (int i = 0; respuesta[i] != '\0'; ++i)
        {
            respuesta[i] = tolower(respuesta[i]);
        }
        // Comparamos las entradas
        int eqUpper = strcmp(respuesta, "upper");
        int eqWords = strcmp(respuesta, "words");
        int eqVowels = strcmp(respuesta, "vowels");
        int eqNone = strcmp(respuesta, "none");

        // Se cambia el valor de el conv segun lo que entre
        if (eqUpper == 0)
        {
            conv = 1;
        }
        else if (eqWords == 0)
        {
            conv = 2;
        }
        else if (eqVowels == 0)
        {
            conv = 3;
        }
        else if (eqNone == 0)
        {
            conv = 4;
        }
    }
    return NULL;
}
//Se paga el echo (Casi que no)
void ECHOoff()
{
    struct termios term;
    tcgetattr(fileno(stdin), &term);

    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &term);
}