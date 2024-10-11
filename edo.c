#include "polinomio.h"


int main(){
    struct Polinomio* p = (struct Polinomio*) malloc(sizeof(struct Polinomio));

    p->r = NULL;
    p->v = NULL;
    p->sinal = NULL;

    printf("digite a EDO:\n");
    printf("x' = ");
    scanf("%s", p->input);

    acha_grau(p);
    cria_vetor(p);
    acha_Raiz(p);
    printr(p);
    esboco(p);

    return 0;


}


