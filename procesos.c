/*
Archivo: procesos.c
Realizado por: Julio Mejía y Brayan García
Contiene: implementación de las funcionen que permiten cargar una matriz
realizar una partición equitativa por procesos y determinar la cantidad
0's que hay en la matriz
Fecha última modificación: 19/09/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int** cargarMatriz(char* archivo, int M, int N);
int revisarMatriz(int** matriz, int M, int N, float porcentaje, int nprocesos);

int main(int argc, char *argv[])
{
  int M, N, status, i,nprocesos,cuantos, fil, k,l, sum;
  char* archivo;
  float porcentaje=atoi(argv[5]);
  int** matriz=cargarMatriz(argv[3],M,N);
  int dispersa=(M*N*porcentaje);
  if(argc != 6){
    printf("Cantidad de argumentos no validos\n");
    exit(1);
  }
  archivo=argv[3];
  nprocesos= atoi(argv[4]);
  porcentaje/=100;
  M = atoi(argv[1]);
  N = atoi(argv[2]);
  sum = revisarMatriz(matriz,M,N,porcentaje,nprocesos);
  printf("M= %i ",M);
  printf("N= %i \n",N);
  printf("P= %f \n",porcentaje);
	printf("La matriz en el archivo %s", archivo);
        printf(" tiene un total de %d ceros, por tanto,", sum);
	if(!(M*N*porcentaje<=(sum)))
   	{
           printf(" no");
	}
        printf(" se considera dispersa. Se requiere %d ceros.\n", dispersa);

}
/*
Función: Revisar Matriz
Parámetros de entrada: matriz, dimensiones, números de procesos deseados por el usuario
Valor de salida: cantidad de ceros en el archivo
Descripción: La función crea la cantidad de hijos solicitados y le indica
a cada uno de ellos la cantidad de filas que debe tomar para determinar
la cantidad de los no ceros
*/
int revisarMatriz(int** matriz, int M, int N, int nprocesos)
{
   int cuantos;
   int status = 0;
   int l = 0,k=0,sum=0,i;
   pid_t childpid;
   FILE *fp1;
   char *arch = "datos.txt";
   int datoA;
   char linea[N];

   for (i = nprocesos; i>0  ; --i) {
     cuantos = (M-status)/i;
     if ((childpid = fork()) < 0) {
       perror("fork:");
       exit(1);
     }
     if(childpid ==0){
     for(k = status; k < status+cuantos; k++){
       for(l = 0; l < N; l++){
        if(matriz[k][l]!=0){
         sum ++;
	      }
       }
     }
     if(sum>=255){
       fp1 = fopen(arch,"w");
       fprintf(fp1,"%d",sum);
       fclose(fp1);
       exit(255);
     }
     exit(sum);
   }
     status +=cuantos;
     }
   for (i = 0; i < nprocesos; ++i){
     wait(&status);
     if((status/256)==255){
       fp1 = fopen(arch,"r");
       fgets(linea,N,fp1);
       datoA = atoi(linea);
       sum += datoA;
     }
    sum+=(status/256);
   }
   return (M*N-sum);
}
/*
Función: Cargar Matriz
Parámetros de entrada: dirección del archivo y dimensiones de la matriz
Valor de salida: doble apuntador de la matriz que se ha creado
Descripción: La función apartir de un archivo crea y carga una matriz
con las dimensiones indicadas
*/
int** cargarMatriz(char* archivo, int M, int N){

  FILE *fp;
  char linea[(2*N)+2];
  char *token;
  int filas, cols;
  int** matriz = (int**)malloc(filas*sizeof(int *));
  fp=fopen(archivo,"r");
  if(fp==NULL){
    printf("El archivo no se encontro\n");
    exit(1);
  }

  filas = M;
  cols = N;
  for(int i = 0; i < filas; i++){
    matriz[i] = (int*)malloc(cols*sizeof(int));
    fgets(linea,(2*N)+2,fp);
    token = strtok(linea," ");
    matriz[i][0] = atoi(token);
    for(int j=1; j < cols; j++){
      token = strtok(NULL," ");
      matriz[i][j] = atoi(token);
    }
  }
  fclose(fp);
  return matriz;
}


}
