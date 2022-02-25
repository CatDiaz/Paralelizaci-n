#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

//Numero de hilos
int n_threads = 4; 
//Contadores
int *contadores = NULL;
//Ejecuciones por nucleo
int n = 10000/n_threads;

//Simulaciones dentro del cuadro unitario, esta en el circulo si 
// x^2 + y^2 < = 1
void* MonteCarlo(void *args){
	double x, y, z;
	int favorables=0;
	int *id = (int*) args;
		//Semilla
	srand(time(NULL));
	
	
	for(int i = 0; i<n; i++){	
		x = (rand() % ((4*n) + 1));
		x = x/(4*n);
		y = (rand() % ((4*n) + 1));
		y = y/(4*n);
		z = (x*x) + (y*y);
	//Comparación si está dentro del círculo
		if(z <= 1){
			favorables = favorables + 1;
		}
	}
	printf("Favorables en hilo # %d: %d\n", *id, favorables);
	contadores[*id] = favorables;
	pthread_exit(0);
	return (NULL);
}
int main(){
	double x, y, z, valor_pi;
	int j, k;



	//Favorables en todos los hilos
	int favorables_tot;
	contadores = new int[n_threads];
	//Definición de los hilos
	pthread_t *thd = new pthread_t[n_threads];
	int *ids = new int[n_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(j=0; j<n_threads; j++){
		ids[j] = j;
		pthread_create(&thd[j],&attr, *MonteCarlo,&ids[j]);
	}
	for(k = 0; k<n_threads; k++){
		pthread_join(thd[k], NULL);
	}
	for(j = 0; j<n_threads; j++){
		favorables_tot = favorables_tot + contadores[j];
	}
	//Favorables / totales es una estimación de pi/4
	valor_pi = 4*(favorables_tot / double(n*n_threads));
	printf("El valor estimado de pi mediante Montecarlo es: %lf \n", valor_pi);
	delete[] thd;
	delete[] ids;
	delete[] contadores;
	return 0;
}
