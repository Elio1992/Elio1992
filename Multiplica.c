#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

void enteroACadena(unsigned int numero, char *bufer) {
    sprintf(bufer, "%u", numero); //%u de unsigned int
}

int main (void) {

    int fifolectura, fifoescritura;
    char numeroPersona[100];
    char tabla[1000];
    char bufferMultiplicacion[10];

    while (true) {
        //Limpio los array en cada bucle
        memset(numeroPersona, 0, sizeof numeroPersona);
        memset(tabla, 0, sizeof tabla);

        //Leo el número recibido
        printf("ESPERANDO NÚMERO\n");
        fifolectura = open ( "FIFO2", 0);
        printf("NÚMERO RECIBIDO--> ");
        read(fifolectura, numeroPersona, 100);
        close (fifolectura);
        printf("%s\n", numeroPersona);

        if(strcmp(numeroPersona, "0") == 0) {
            break;
        }

        //Convierte el char que recibe a int
        int numeroRecibido = atoi(numeroPersona);

        //Multiplica y concatena los resultados en un char[] llamado tabla
        for (int i = 1; i <= 10; ++i) {
            memset(bufferMultiplicacion, 0, sizeof bufferMultiplicacion);

            unsigned int multiplicacion = (i * numeroRecibido);
            enteroACadena(multiplicacion, bufferMultiplicacion);

            strcat(tabla, (const char *) &bufferMultiplicacion); //Añade número multplicado a tabla

            char saltoLinea[2] = "\n";
            strcat(tabla, (const char *) &saltoLinea); //Añade un salto de línea a tabla
        }

        //Manda la tabla al otro proceso.
        fifoescritura = open ("FIFO", 1);
        write(fifoescritura, tabla, strlen(tabla));
        close(fifoescritura);
        }
}



