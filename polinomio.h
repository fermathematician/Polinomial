#include <stdio.h>
#include <stdlib.h>
#define N 100


struct Polinomio {

	char input[N];
	char* sinal;
	//vetor de inteiros
	int *v;
	float *r;
	int coe, exp, grau, nR;

};

//printa polinomio a partir do vetor v e sinal
void printv(struct Polinomio* p);

//printa as raízes reais
void printr(struct Polinomio* p);

//cria sinal e v a partir de input
void cria_vetor(struct Polinomio* p);

//determina grau do polinomio a partir do input e aloca sinal, v e raiz com base nele
void acha_grau(struct Polinomio* p);

//calcula exponencial para expoentes inteiros
float ex(float base, int expoente);

//calcula valor do polinomio no ponto x
float valor(struct Polinomio* p, float x);

//cria polinomio que é derivada do original
void derivada(struct Polinomio* p, struct Polinomio* d);

//retorna o valor da primitivaa no ponto dado
float primitiva(struct Polinomio* p, float x);

//retorna area do polinomio no intervalo dado
float area(struct Polinomio* p, float a, float b);

//retorna aproximação com N = 10, 100 e 1000 para retângulos do lado esquerdo, direito e ponto médio
void soma_Riemman(struct Polinomio* p, float a, float b);

//retorna aproximação liinear e quadrática a uma distância D = 1, 0.5 e 0.1 do ponto especificado
void aprox(struct Polinomio* p, float x);

//determina a raiz pelo método de Newton
float raiz_Newton(struct Polinomio* p, struct Polinomio* d, float a);

void acha_Raiz(struct Polinomio* p);

float mod(float x);

int sinal_trocado(float a, float b);

float lim_pos(struct Polinomio* p);

float lim_neg(struct Polinomio* p);

void esboco(struct Polinomio* p);
