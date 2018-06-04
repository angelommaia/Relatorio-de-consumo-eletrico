/*
// pointer to functions
#include <stdio.h>


double fx (double x){
double funcao_integrada;

    funcao_integrada=(1/(x*x));

return (funcao_integrada);

}


double aprox_trapez (double *a, double (*functocall)(double)){

double h,aprox,soma=0;
int n,i;

    //===LEITURA DOS LIMITES DE INTEGRACAO E QUANTIDADE DE SUB INTERVALOS===//
    printf("Informe o valor dos limites de integracao [a,b]\na: ");
    scanf("%lf", a);
    printf("b: ");
    scanf("%lf", (a+1)); //(a+1) é o endereco de memoria do segundo elemento do vetor a[2]
    //printf("Intervalo de integracao definido: [%f;%f]\n",*a,*(a+1));
    printf("Informe a quantidade de sub intervalos:\nn: ");

    scanf("%d",&n);
    /*if(n%2==1){
        n=n+1;
    }*/
    double y[n],x[n];

    //printf("\nQuantidade de sub intervalos: %d\n",n);

    //===CALCULO DA LARGURA DOS SUB INTERVALOS===//
    //printf("Calculo de h: (%f-%f)/%d\n",*(a+1),*a,n);
    h=(double)((*(a+1)-*a)/n);
    //printf("Largura de cada sub divisao do intervalo [%f,%f]: %f\n\n",*a,*(a+1), h);

    //===CALCULO DOS PONTOS NA FUNCAO E DO SOMATORIO GERAL===//
    for(i=0;i<=n;i=i+1){
        x[i]=*a+i*h;
        y[i]=(*functocall)(x[i]);
        soma=soma+y[i];
        printf("Valor de f[%d]: %25.5lf\n",i, y[i]);
        printf("Soma parcial:  %25.5lf\n",soma);
    }

    aprox=(h/2*((y[0]/2+y[n]/2)+soma));

return (aprox);
}

int main (){

double n,a[2];

    *a=2;
    *(a+1)=2;

    printf("Funcao de teste: f=1/(x^2)\nCalculo de integral por trapezios\n");

    n = aprox_trapez (a, fx);
    printf("\nAproximacao:  %lf\n",n);


return 0;
}
*/
