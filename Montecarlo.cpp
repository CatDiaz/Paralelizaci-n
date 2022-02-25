#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

//Simulaciones dentro del cuadro unitario, esta en el circulo si 
// x^2 + y^2 < = 1
using namespace std;
int main(){
	
	//Definición
	int n = 10000;
	double x, y, z, valor_pi;
	int favorables, totales;
	
	//Semilla
	srand(time(NULL)); 
	
	//Inicialización de proceso
	favorables = 0;
	totales = 0;
	for(int i = 0; i<n ; i++){
		x = (rand() % (10000 + 1));
		x = x/10000;
		y = (rand() % (10000 + 1));
		y = y/10000;
		z = pow(x,2) + pow(y,2);
		
		//Comparación si está dentro del círculo
		if(z <= 1){
			favorables = favorables + 1;
		}
		totales = totales + 1;
	}
	cout << "Observaciones Favorables: " << favorables << endl;
	cout << "Observaciones Totales: " << totales << endl;

	//Favorables / totales es una estimación de pi/4
	valor_pi = 4*(double(favorables) / double(totales));
	cout << "El valor estimado de pi mediante Montecarlo es: " << valor_pi << endl;
	return 0;
}
