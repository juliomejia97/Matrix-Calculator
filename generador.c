/* Funcion: Archivo que genera una matriz de n*m en un archivo. Matriz almacenada en formato texto.
   Elaborado por: M. Curiel
   Nota: faltan las validaciones a las llamadas al sistema y la documentacion correspondiente.  Las matrices que genera este codigo no son dispersas, pero el formato generado ser'a el mismo de los casos de prueba. 
*/
 


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

void init ( int **matriz,int nfil, int ncol) {
int i;
int j;
for ( i = 0 ; i < nfil ; i ++ ) {
for ( j = 0 ; j < ncol ; j ++ ) {
  /*Este codigo lo deben modificar para generar las matrices dispersas */
matriz[i ][ j ] = rand ()%2;
}
}
}

int main ( int argc , char * argv []) {

 int **rows,*col,m,n, i,j, numero;

 FILE *fp;
  
  

 /* n es el numero de filas y m es el numero de columnas */
 
 n = atoi(argv[1]);
 m = atoi(argv[2]);

 fp = fopen(argv[3], "w");
 printf("Valor de N es %d y M es  %d\n", n,m);

 // creacion de la matriz
 rows  = (int **)malloc(n*sizeof(int *));
 
 for (i = 0; i< n; i++) 
   rows[i]= (int *) malloc(m*sizeof(int));


 init(rows, n,m);
// Impresion de la matriz
 for (i = 0; i< n; i++) {   
  for (j = 0; j< m; j++) 
    fprintf (fp,"%d ", rows[i][j]);
  fprintf(fp,"\n");

 }

 fclose(fp);

}


 /*
init ( p1.matriz );
printf("Matriz impresa 1 \n");
mprintf(p1.matriz);
printf("Matriz impresa 2 \n");
mprintf(p2.matriz); */
