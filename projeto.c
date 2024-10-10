#include "polinomio.h"

int main(){

	float x, a, b;

	char input_usuario = ' ';

	//declara polinomio, derivada e antiderivada
	struct Polinomio* p = (struct Polinomio*) malloc(sizeof(struct Polinomio));


	p->input[0] = '\0';
	p->v = NULL;
	p->r = NULL;	


	printf("P(x) = ");
	scanf("%99s", p->input);

	acha_grau(p);
	cria_vetor(p);

	printf("P(x) = ");
	printv(p);


	while(input_usuario != 'S'){

		printf("\nO que deseja fazer? (pressione I para integrar, V para calcular valor, \n R para achar raízes e S para sair): ");

		scanf(" %c", &input_usuario);

		if(input_usuario == 'V'){

			printf("Digite um valor de x: ");
			scanf("%f", &x);

			printf("P(%.2f) = %.2f", x, valor(p, x));

			aprox(p, x);
		}

		else if(input_usuario == 'R'){


			if(p->grau > 0){

				acha_Raiz(p);
				if(p->nR > 0){
					printf("As raízes são: ");

					printr(p);
				}
				else
				printf("Não tem raízes");

			}





		}

		else if(input_usuario == 'I'){
			printf("Digite o ponto inicial: ");
			scanf("%f", &a);
			
			printf("Digite o ponto final: ");
			scanf("%f", &b);
			
			printf("\n %.2f", b);
			printf("\nS P(x)dx = %.3f \n", area(p, a, b));
			printf(" %.2f\n", a);

			soma_Riemman(p, a, b);
		}
	
	}


	free(p->v);
	free(p->r);
	free(p->sinal);
	free(p);


}
