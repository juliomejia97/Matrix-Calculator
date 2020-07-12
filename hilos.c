/*
Archivo: hilos.c
Realizado por: Julio Mejía y Brayan García
Contiene: implementación de las funcionen que permiten cargar una matriz
realizar una partición equitativa mediante hilos y determinar la cantidad
0's que hay en la matriz
Fecha última modificación: 19/09/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

int** matriz; //doble apuntador de la matriz
int sum = 0; //Suma de números diferentes de cero
int guia = 0; //Variable global que indica en que fila se ha sumado
int cantidadC; //cantidad de columnas
int cantidadF; //Cantidad de filas
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; /*
Variable global de tipo mutex que espera hasta que el hilo termine
*/

void* cargarMatriz(char* archivo, int M, int N);
int revisarMatriz(int M, int N, int nhilos);
void *sumar(void *args);
int dispersa;
int main(int argc, char *argv[])
{
  int M, N, status, i,nhilos,cuantos, fil, k,l, num;
  char* archivo;
    float porcentaje=atoi(argv[5]);
  if(argc != 6){
    printf("Cantidad de argumentos no validos\n");
    exit(1);
  }
  archivo=argv[3];
  nhilos= atoi(argv[4]);
  porcentaje/=100;
  M = atoi(argv[1]);
  N = atoi(argv[2]);
  cantidadC = N;
  cantidadF = M;

    if((matriz = (int**)malloc (M*sizeof(int *)))==NULL)
  {
   printf("No hay memoria suficiente\n");
    exit(0);
  }
  for(i = 0; i < M;i++)
  if((matriz[i] = (int*)malloc (N*sizeof(int)))==NULL)
  {
   printf("No hay memoria suficiente\n");
   exit(0);
  }

  cargarMatriz(argv[3],M,N);
  num = revisarMatriz(M,N,nhilos);
  dispersa=(M*N*porcentaje);
  printf("M= %i ",M);
  printf("N= %i \n",N);
  printf("P= %f \n",porcentaje);
	printf("La matriz en el archivo %s", archivo);
  printf(" tiene un total de %d ceros, por tanto,", num);
	if(!(M*N*porcentaje<=(num)))
   	{
           printf(" no");
	}
        printf(" se considera dispersa. Se requiere %d ceros.\n", dispersa);

}



/*
Función: revisarMatriz
Parámetros de entrada: dimensión de la matriz y número de hilos
Valor de salida: cantidad de 0's de la matriz
Descripción: La funcion crea los hilos e indica la cantidad de filas que le
corresponde a cada uno
*/
int revisarMatriz(int M, int N, int nhilos)
{
   guia = 0;
   pthread_t threads[nhilos]; // arreglo de identificadores
   int tarea_ids[nhilos];
   int rc, t, i, fila, status;
   status = 0;
    for(t = nhilos; t >0; t--){
        threads[t-1] = t;
        fila = (M-status)/(t);
        tarea_ids[t-1] = fila;
        status += fila;
        if((rc = pthread_create(&threads[t-1],NULL,sumar,(void *)&tarea_ids[t-1]) ) )
        {
           printf("No se creo el hilo\n");
        }
   }
    for(t = 0; t < nhilos; t++){
        pthread_join(threads[t],NULL);
    }

   return (M*N-sum);
}
/*
Función: Sumar
Parámetros de entrada: argumentos (cantidad de filas debe sumar el hilo)
Valor de salida: no tiene
Descripción: La función bloquea el computador y espera a que el hilo termine,
luego suma las filas que le corresponde y determina la cantidad de no 0's que
hay en la matriz
*/
void *sumar(void *args){
    pthread_mutex_lock( &mutex1 );
    int *filas_ptr,filas;
    filas_ptr = (int*)args;
    filas = *filas_ptr;
        for(int i=guia;i < filas+(guia); i++){
            for(int j=0; j < cantidadC; j++){
                if(matriz[i][j]!=0){
                    sum ++;
                }
            }
    }

    guia += filas;
    pthread_mutex_unlock( &mutex1 );
    pthread_exit(NULL);

}
/*
Función: Cargar Matriz
Parámetros de entrada: dirección del archivo y dimensiones de la matriz
Valor de salida: No retorna nada
Descripción: La función carga la matriz y la asgina a la variable global
*/
void* cargarMatriz(char* archivo, int M, int N){

  FILE *fp1;
  fp1=fopen(archivo,"r");
  char linea[(2*N)+2];
  int fila,col;
  fila = 0;
  col=0;
  int i,val;
  i=0;
  while(fgets(linea,(N*2)+2,fp1)!=NULL){

    for(i = 0; i < 2*N-1; i++){

	     if(linea[i]!=' '){
         val= (int) linea[i];
	       val-= 48;
	       matriz[fila][col] =  val;
	       col++;
       }

    }
  col=0;
  fila++;

  }

fclose(fp1);

}
