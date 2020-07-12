/* Ejemplo: matriz.c
	Integrantes: Brayan Garcia y Julio Mejia
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])

{

  int status, i,nprocesos,cuantos, fil, k,l, sum;
   int matriz[6][6]={{1,1,1,1,1,1},{2,2,2,2,2,2},{3,3,3,3,3,3},{4,4,4,4,4,4},{5,5,5,5,5,5},{6,6,6,6,6,6}};
   pid_t childpid;

   /* coloque aqui el código para obtener el número de procesos de la línea de argumentos */ 
   sum = 0;
   nprocesos = atoi(argv[1]);

   cuantos = 6/nprocesos;
   status = 0;
   l = 0;

   for (i = 0; i < nprocesos; ++i) { // Creación de los procesos.
 // Añada las líneas de código para que los hijos sepan que filas deben sumar.
     if ((childpid = fork()) < 0) {
       perror("fork:");
       exit(1);
     }
     if(childpid ==0){
     for(k = status; k < status+cuantos; k++){
     for(l = 0; l < 6; l++){
     sum += matriz[k][l];
     }
     }
     printf("La suma de el proceso %d",i+1);
     printf(" es: %d\n",sum);
     exit(0); 
     }
     status +=cuantos;
     }
     
   // El padre espera por todos los hijos que creo.
   for (i = 0; i < nprocesos; ++i)
     wait(&status);
   printf("El padre termina\n");

}
