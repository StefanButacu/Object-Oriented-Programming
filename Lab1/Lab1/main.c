#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int giveNumberOfFactors(int N, const int D) {
	/*
	* N,D - nr intregi; 2<=D<=N
      Returneaza exponentul lui D in descompunerea in factori primi ai lui N 
	* 
	*/
	int exp = 0;
	while (N % D == 0) {
		exp++;
		N = N / D;
	}
	return exp;
}
void nrZero()
{   // se citesc numere pana la intalnirea lui 0 si afiseaza numarul de zerouri al produsului de numere citite
	int factor2 = 0, factor5 = 0;
	int N;
	printf("%s", "Dati numerele pana la intalnirea lui 0 \n");
	scanf("%d", &N);
	while (N) {
		factor2 += giveNumberOfFactors(N, 2);
		factor5 += giveNumberOfFactors(N, 5);
		scanf("%d", &N);
	}
	if (factor2 <= factor5)
		printf("Produsul numerelor citite are %d zerouri la final\n", factor2);
	else
		printf("Produsul numerelor citite are %d zerouri la final\n", factor5);
}


void sinus() {
	// calculeaza cu aproximare de N sume valoarea lui sinus(x) , x float - citit de la tastatura 
	float x;
	printf("Dati numarul x: ");
	scanf("%f", &x);
	float x_aux = x;
	int N;
	printf("Dati numarul de sume N: ");
	scanf("%d", &N);
	float x_patrat = x * x; 
	float suma = 0; 
	unsigned long long factorial = 1; 
	for (int i = 1; i <= N ; i++) {
		if (i % 2 == 1)
			suma += x / factorial;
		else
			suma -= x/ factorial;
		x *= x_patrat;
		factorial = factorial * (2*i) * (2*i+1);
		printf("sin(%f)[%d] = %f\n", x_aux, i, suma);

	}	
}
int main() {
	int	running = 1;
	while (running) {
		printf("1. Incepeti executarea exercitiului 9\n");
		printf("2. Incepeti executarea exercitiului 1 + 7 =  8 \n");
		printf("3. Exit\n");
		printf(">>>");
		int cmd;
		scanf("%d", &cmd);
		/*
		switch (cmd) {
		case 1: nrZero();
			break;
		case 2: sinus();
			break;
		case 3: running = 0;
			break;
		default: printf("%s", Comanda invalida");
		}
		*/
		if (cmd == 1)
			nrZero();
		else 
			if (cmd == 2)
				sinus();
			else
				running = 0;
			
			}
	return 0;
}