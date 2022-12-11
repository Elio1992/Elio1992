#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

int main (void) {
    int fifolectura, fifoescritura;
    char mensaje[100];
    char respuesta[1000];

    while (true) {
        //Limpio el array de la tabla que recibe.
        memset(respuesta, 0, sizeof respuesta);

        //Manda un número que el usuario escribe
        printf("ENVIA UN NÚMERO\n");
        printf("Escribe un número: \t");
        scanf("%s" , mensaje);

        fifoescritura = open ( "FIFO2", 1);
        write (fifoescritura , mensaje , strlen(mensaje));
        close(fifoescritura);

		//Si mensaje es igual a 0 termina
        if(strcmp(mensaje, "0") == 0) {
            break;
        }

        //Recibe la tabla de multiplicar del otro proceso
        printf("ESPERANDO RESUPESTA\n");
        fifolectura = open ( "FIFO", 0);
        printf("RESPUESTA RECIBIDA--> ");
        read(fifolectura, respuesta, sizeof respuesta);
        printf("\n");
        close(fifolectura);


        const char s[2] = "\n";
        char *token;
        int i = 1;
        /* get the first token */
        token = strtok(respuesta, s);

        while( token != NULL ) {
            printf( "%i * %s = %s\n", i, mensaje, token );

            token = strtok(NULL, s);
            i++;
        }


    }
}