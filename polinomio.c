#include "polinomio.h"
#define N1 10
#define N2 100
#define N3 1000
#define D1 1.0
#define D2 0.5
#define D3 0.1
#define E 0.001

//retorna módulo
float mod(float x){
	if (x >= 0)
		return x;
	else
		return -1*x;
}

int sinal_trocado(float a, float b){
	if(b >= 0){

		if(a >= 0)
			return 0;
		else
			return 1;
	}
	else{
		if(a >= 0)
			return 1;
		else
			return 0;
	}
}

float lim_pos(struct Polinomio* p){


	if((p->grau%2) && (p->sinal[p->grau] == '-'))
			return -1.0;
	else if((p->grau%2) && (p->sinal[p->grau] == '+'))
		return +1.0;
	else if(p->sinal[p->grau] == '+')
		return +1;
	else
		return -1;


}

float lim_neg(struct Polinomio* p){



	if((p->grau%2) && (p->sinal[p->grau] == '-'))
		return +1.0;
	else if((p->grau%2) && (p->sinal[p->grau] == '+'))
		return -1.0;
	else if(p->sinal[p->grau] == '+')
		return +1;
	else
		return -1;

}
	
	

void acha_grau(struct Polinomio* p){

	int i, max = 0;

	for(i = 0;p->input[i] != '\0'; i++){
		
		if((p->input[i] == 'x') && (max == 0))
			max = 1;
		if((p->input[i] == '^') && ((p->input[i+1]-'0') > max))
			max = p->input[i+1] - '0';
	

	}


	p->grau = max;

	//aloca vetor v
	p->v = (int*) malloc((max+1)*sizeof(int));
	for(i = 0; i < max+1; i++)
		p->v[i] = 0;
	//prepara as raízes também (n raízes só)
	p->r = (float*) malloc((max)*sizeof(float));
	for(i = 0; i < max; i++)
		p->r[i] = 0.0;
	p->sinal = (char*) malloc((max+1)*sizeof(char));
	for(i = 0; i < max+1; i++)
		p->sinal[i] = '+';

}

void printv(struct Polinomio* p){

	int i;

	for(i = 0; i < p->grau+1; i++){
		if(p->v[i]){
		printf("%c", p->sinal[i]);
		printf("%d*x^%d", p->v[i], i);
		}
	}

	printf("\n");
} 
       	
void printr(struct Polinomio* p){

	int i;

	for(i = 0; (i < p->nR) && (i < 5); i++){
			printf("\n r%d = %.2f", i+1, p->r[i]);
		
	}

	printf("\n");
} 



void cria_vetor(struct Polinomio *p){
			
	int i, chave = 0, inf = 0, sup = 0;
	 
     

	while(p->input[chave] != '\0'){

		if(((p->input[chave] == '+') || (p->input[chave] == '-')) && (chave > 0)){

			//se não tem ^, ou é 1 ou é 0
			p->exp = 0;
			//se não tem *, ou é 1 ou é grau 0
			p->coe = 1;
			sup = chave;
			for(i = inf; i < sup; i++){

				if(p->input[i] == 'x')
					p->exp = 1;
					
				if(p->input[i] == '^')
					p->exp = p->input[i+1] - '0';
				if(p->input[i] == '*')
					p->coe = p->input[i-1] - '0';
			}
			if((p->input[inf] == '+') || (p->input[inf] == '-')){
				p->sinal[p->exp] = p->input[inf];
				if(p->exp == 0)
					p->coe = p->input[inf+1] - '0';
			}

			//caso de começar com positivo
			else {
				p->sinal[p->exp] = '+';
				if(p->exp == 0)
					p->coe = p->input[inf] - '0';
				}
		inf = sup;
		p->v[p->exp] = p->coe;

		}
	chave++;	

	}

	//faz do que sobrou
	p->exp = 0;
	p->coe = 1;
	for (i = inf; i < chave; i++){
		if(p->input[i] == 'x')
			p->exp = 1;
		
		if(p->input[i] == '^')
			p->exp = p->input[i+1] - '0';
		if(p->input[i] == '*')
			p->coe = p->input[i-1] - '0';
	}

	if((p->input[inf] == '+') || (p->input[inf] == '-')){
			p->sinal[p->exp] = p->input[inf];
			if(p->exp == 0)
				p->coe = p->input[inf+1] - '0';
		}

		//caso de começar com positivo
		else {
			p->sinal[p->exp] = '+';
			if(p->exp == 0)
				p->coe = p->input[inf] - '0';
		}
		p->v[p->exp] = p->coe;

}

float ex(float base, int expoente){
	int i;
	float total = 1.0;
	for(i = 0; i < expoente; i++)
		total = total*base;
	return total;
}


float valor(struct Polinomio* p, float x){

	int i;
	float total;

	if(p->sinal[0] == '+')
		total = p->v[0];
	else if(p->sinal[0] == '-')
		total = -1*p->v[0];

	for(i = 1; i < p->grau+1; i++){
		
		if(p->sinal[i] == '+')
			total = total + (float )( p->v[i]*ex(x, i));
		else if(p->sinal[i] == '-')	
			total = total - (float )( p->v[i]*ex(x, i));
			

	}
		return total;

}


void derivada(struct Polinomio* p, struct Polinomio* d){

	int i;

	d->grau = p->grau-1;	
	//dereivada tem grau menor que p por uma unidade (vai de p->grau+1 pra p->grau)
	d->v =(int*) malloc((d->grau+1)*sizeof(int));

	d->r =(float*) malloc((d->grau)*sizeof(int));
		
	d->sinal =(char*) malloc((d->grau+1)*sizeof(char));

	for(i = 0; i < d->grau+1; i++){
		d->v[i] = p->v[i+1]*(i+1);
		d->sinal[i] = p->sinal[i+1];
	}
	for(i = 0; i < d->grau; i++)
		//ja inicializa as raizes
		d->r[i] = 0.0;


}


float primitiva(struct Polinomio* p, float x){
	
	int i;
	float total = 0;


	for(i = 0; i < p->grau+1; i++){
		
		if(p->sinal[i] == '+')
			total = total + (float )( p->v[i]*ex(x, i+1)/(i+1));
		else if(p->sinal[i] == '-')
			total = total - (float )( p->v[i]*ex(x, i+1)/(i+1));
		
	}
		return total;

}

float area(struct Polinomio* p, float a, float b){
	float total =  primitiva(p, b) - primitiva(p, a);
	return total;
}

void soma_Riemman(struct Polinomio* p, float a, float b){

	float totalm = 0, totalM = 0, total_medio = 0, dx = (b-a)/N1, i;
	

	//primeiro ciclo
		
	for(i = a; i < b; i = i+dx)
		totalm = totalm + valor(p, i)*dx;
	for(i = a+dx; i < b+dx; i = i+dx)
		totalM = totalM + valor(p, i)*dx;
	for(i = a+dx/2; i < b+dx/2; i = i+dx)
		total_medio = total_medio + valor(p, i)*dx;

	printf("\nAproximação pela esquerda com N = %d: %.3f", N1, totalm);

	printf("\nAproximação pela direita com N = %d: %.3f", N1, totalM);

	printf("\nAproximação pela direita com N = %d: %.3f\n", N1, total_medio);
	

	//zera valor
	totalm = 0;
	totalM = 0;
	total_medio = 0;

	dx = (b-a)/N2;

	for(i = a; i < b; i = i+dx)
		totalm = totalm + valor(p, i)*dx;
	for(i = a+dx; i < b+dx; i = i+dx)
		totalM = totalM + valor(p, i)*dx;
	for(i = a+dx/2; i < b+dx/2; i = i+dx)
		total_medio = total_medio + valor(p, i)*dx;

	printf("\nAproximação pela esquerda com N = %d: %.3f", N2, totalm);

	printf("\nAproximação pela direita com N = %d: %.3f", N2, totalM);

	printf("\nAproximação pela direita com N = %d: %.3f\n", N2, total_medio);

	//zera valor
	totalm = 0;
	totalM = 0;
	total_medio = 0;

	dx = (b-a)/N3;

	for(i = a; i < b; i = i+dx)
		totalm = totalm + valor(p, i)*dx;
	for(i = a+dx; i < b+dx; i = i+dx)
		totalM = totalM + valor(p, i)*dx;
	for(i = a+dx/2; i < b+dx/2; i = i+dx)
		total_medio = total_medio + valor(p, i)*dx;

	printf("\nAproximação pela esquerda com N = %d: %.3f", N3, totalm);

	printf("\nAproximação pela direita com N = %d: %.3f", N3, totalM);

	printf("\nAproximação pela direita com N = %d: %.3f\n", N3, total_medio);
}

	
void aprox(struct Polinomio* p, float x){

	float linear = 0, quadratica = 0;
	struct Polinomio* der1 = (struct Polinomio*) malloc(sizeof(struct Polinomio));
	struct Polinomio* der2 = (struct Polinomio*) malloc(sizeof(struct Polinomio));


	printf("\nP(%.2f) = %.2f", x, valor(p, x));


	derivada(p, der1);
	derivada(der1, der2);
	
	//aproximação com D = 1 (distância de x = 1)
	
	linear = valor(p, x-D1) + (float) valor(der1, x-D1)*D1;
	printf("\nAproximação linear com distância %.2f: %.2f", D1, linear);

	quadratica = valor(p, x-D1) + (float) valor(der1, x-D1)*D1 + (float) valor(der2, x-D1)*D1*D1/2;
	printf("\nAproximação quadratica com distância %.2f: %.2f\n", D1, quadratica);

	//aproximação com D = 0.5 (distância de x = 0.5)
	
	linear = valor(p, x-D2) + (float) valor(der1, x-D2)*D2;
	printf("\nAproximação linear com distância %.2f: %.2f", D2, linear);

	quadratica = valor(p, x-D2) + (float) valor(der1, x-D2)*D2 + (float) valor(der2, x-D2)*D2*D2/2;
	printf("\nAproximação quadratica com distância %.2f: %.2f\n", D2, quadratica);

	//aproximação com D = 0.1 (distância de x = 0.1)
	
	linear = valor(p, x-0.1) + (float) valor(der1, x-0.1)*0.1;
	printf("\nAproximação linear com distância %.2f: %.2f", D3, linear);

	quadratica = valor(p, x-0.1) + (float) valor(der1, x-0.1)*0.1 + (float) valor(der2, x-0.1)*0.01/2;
	printf("\nAproximação quadratica com distância %.2f: %.2f\n", D3, quadratica);


	free(der1->v);
	free(der1->r);
	free(der1->sinal);
	free(der1);

	free(der2->v);
	free(der2->r);
	free(der2->sinal);
	free(der2);


}


float raiz_Newton(struct Polinomio* p, struct Polinomio* d, float a){

	float raiz = a, erro;
	int i = 0;

	raiz = -1*(valor(p, raiz)/valor(d, raiz))+raiz;

	erro = valor(p, raiz);

	while((mod(erro) > E) || i < 10){

		raiz = -1*(valor(p, raiz)/valor(d, raiz))+raiz;

		erro = valor(p, raiz);
		i++;
	}

	return raiz;
}


//botar condicional que polinomio tem que ter grau maior que 1 (if(p->
void acha_Raiz(struct Polinomio* p){

	float raiz, a, b;
	int i;
	struct Polinomio* d = (struct Polinomio*) malloc(sizeof(struct Polinomio));
	//inicializa raizes reais
	p->nR = 0;

	printf("O grau é %d \n", p->grau);

	if(p->grau == 1){
		if(p->sinal[0] == '+')
			b = p->v[0];
		else if(p->sinal[0] == '-')
			b = -p->v[0];
		if(p->sinal[1] == '+')
			a = p->v[1];
		else if(p->sinal[1] == '-')
			a = -p->v[1];

		p->r[0] = -1*(b/a);
		p->nR = 1;
	}
	else{
		derivada(p, d);
		acha_Raiz(d);

		printr(d);
		printf("\n");
		printv(d);

		printf("\n");
		printf("\nD tem %d raizes", d->nR);

		if(d->nR > 0){
			printf("\nEntrou no primeiro\n");
			//olha de -infty até primeira raiz da derivada
			printf("\nP(-infty) = %.1f", lim_neg(p));

			printf("\nP(%.3f) = %.3f",d->r[0]-E,  valor(p, d->r[0]-E));


			//checa se a raiz da derivada é a raiz do polinomio
			if(mod(valor(p, d->r[0])) < E){
				p->r[p->nR] = d->r[0];
				p->nR = p->nR + 1;
				printf("\n mod = %.1f", mod(valor(p, d->r[0])));
			}
			else if(sinal_trocado(lim_neg(p), valor(p, d->r[0]-E))){
				//poe um valor pra derivada ser maior e encurtar caminho
				p->r[p->nR] = raiz_Newton(p, d, d->r[d->nR] - 10);
				p->nR = p->nR + 1;
				printf("\n Newton do primeiro\n");
			}
		
			//acha raízes do meio
			printf("Entrou no loop\n");
			for(i = 1; i < d->nR; i++){

			printf("\nP(%.3f) = %.3f", d->r[i-1]+E, valor(p, d->r[i-1]+E));

			printf("\nP(%.3f) = %.3f",d->r[i]-E, valor(d, d->r[i]-E));

			//checa se a raiz da derivada é a raiz do polinomio
				if(mod(valor(p, d->r[i])) < E){
					p->r[p->nR] = d->r[i];
					p->nR = p->nR + 1;
					printf("\n mod = %.4\nf", mod(valor(p, d->r[i])));
				}
				else if(sinal_trocado(valor(p, d->r[i-1]+10*E), valor(p, d->r[i]-10*E))){
					//checa se P da proxima raiz da derivada é sinal contrário
					p->r[p->nR] = raiz_Newton(p, d, (d->r[i]+d->r[i-1])/2);
					p->nR = p->nR + 1;
					printf("\nNewton do loop\n");
					
				}

		
			}

			printf("\nEntrou no final\n");
			printf("\n última raiz de D = %.1f\n", d->r[d->nR-1]);
			printf("\nP(+infty) = %.1f", lim_pos(p));
			printf("\nP(%.3f) = %.3f", d->r[d->nR-1]+E, valor(p, d->r[d->nR-1]+E));
	
			//acha última
			
			if(sinal_trocado(lim_pos(p), valor(p, d->r[d->nR-1]+10*E))){
				p->r[p->nR] = raiz_Newton(p, d, d->r[d->nR] + 10);
				p->nR = p->nR + 1;
				printf("\nNewton do final\n");
			}

			printf("\nP tem %d raizes\n", p->nR);


		}
		
		//caso da derivada não ter raiz
		else{
			//tem que ter uma raiz por simetria
			p->nR = 1;
			//acha sinal da derivada
			int sinal_der, x = 0;

			if(valor(d, x) > 0)
				sinal_der = 1;
			else
				sinal_der = -1;

			if(sinal_trocado(lim_neg(p), sinal_der))

				p->r[0] = raiz_Newton(p, d, x);

		}

			
			free(d->v);
			free(d->r);
			free(d->sinal);
			free(d);

	}


}
		
void esboco(struct Polinomio *p){
    int i;

    if(p->nR > 0){
        if(valor(p, p->r[0] - E) > 0)
            printf("\nConverge para %.1f se x < %.1f\n", p->r[0], p->r[0]);
        else
            printf("\nDiverge se x < %.1f\n", p->r[0]);

        for(i = 1; i < p->nR; i++){
            if(valor(p, p->r[i] - E) > 0)
                printf("\nConverge para %.1f se %.1f < x < %.1f\n", p->r[i], p->r[i-1], p->r[i]);
            else
                printf("\nConverge para %.1f se %.1f < x < %.1f\n", p->r[i-1], p->r[i-1], p->r[i]);
        }
        if(p->nR >= 0){
            if(valor(p, p->r[p->nR-1] - E) > 0)
                printf("\nConverge para %.1f se x > %.1f\n\n", p->r[p->nR-1], p->r[p->nR-1]);
        else
            printf("\nDiverge se x > %.1f\n\n", p->r[p->nR-1]);

        }
    }

    else{

        printf("\nDiverge para todo x\n");
    }
        

}





