#ifndef TENSAO_CSV_H
#define TENSAO_CSV_H
#include "tensao_csv.h"
#endif // TENSAO_CSV_H
#ifndef METODOS_NUMERICOS_H
#define METODOS_NUMERICOS_H
#include "metodos_numericos.h"
#endif // METODOS_NUMERICOS_H
#include <math.h>
///**======PARTE 3 DA PRATICA=======**///

//===TENSAO EM RMS===//
double tensao_rms(int *linhas,struct data leitura[] ){

    int i;
    double soma=0,t_rms=0;

    for(i=0;i<*linhas;i=i+1){
        soma=soma+((*(leitura+i)).tensao*(*(leitura+i)).tensao);
    }

    t_rms=sqrt(soma/(*linhas));

return t_rms;
}

//===CORRENTE EM RMS===//
double corrente_rms(int *linhas,struct data leitura[] ){

    int i;
    double soma=0,c_rms=0;

    for(i=0;i<*linhas;i=i+1){
        soma=soma+((*(leitura+i)).corrente*(*(leitura+i)).corrente);
    }

    c_rms=sqrt(soma/(*linhas));

return c_rms;
}

//===POTENCIA MEDIA===//
double potencia_media(int *linhas,struct data leitura[]){

    double pmed=0, *a;
    int i=0;
    a=malloc(*linhas*2*sizeof(double));

    //====DIFERENCA DE TEMPO ENTRE AS LEITURAS====//
    *(a+2*i)=(*(leitura+i)).corrente*(*(leitura+i)).tensao; //v(t)*i(t) valor de fx
    *(a+2*i+1)=diff_tempo(&i,leitura); //aqui deve ser passado o valor da dif de tempo entre cada amostra
    //printf("pot: %lf\n", *(a+2*i));
    //printf("tempo: %lf\n", *(a+2*i+1));

        for(i=1;i<(*linhas);i=i+1){

            *(a+2*i)=(*(leitura+i)).corrente*(*(leitura+i)).tensao;//v(t)*i(t)
            //printf("potencia[%d]: %lf\n",i, *(a+2*i));
            *(a+2*i+1)=diff_tempo(&i,leitura); //aqui deve ser passado o valor da dif de tempo entre cada amostra
            //printf("tempo: %lf\n", *(a+2*i+1));

        }
        for(i=0;i<*linhas;i=i+1){

            (*(leitura+i)).tempo=diff_tempo(&i,leitura);

        }
    //printf("pot media: %lf\n", pmed);

    pmed=3600*((double)1/((*(leitura+*linhas-1)).tempo))*aprox_trapez(a,fx,*linhas); //aproximacao sera feita por amostras

    free(a);

return pmed;
}

//===RELATORIO TXT===//
void gerar_relatorio_txt(struct data leitura[], int *linhas, double *trms, double *crms,double *pmed){

    FILE *relat;
    int i=0;
    float energia;
    //struct data minha_leitura[*linhas];
    relat=fopen("relatorio.txt", "w"); //nao possui protecao pra saber se o arquivo ja existe. talvez se sobreescrever um arquivo antigo com mais medicoes, haja conflito de dados
    //printf("stream pointer %p",relat);
    //prints inicias, fora do loop pois sao unicos
    fprintf(relat,"IRMS=%10.4lfA\n",*crms);
    fprintf(relat,"VRMS=%10.4lfV\n",*trms);
    fprintf(relat,"PMED=%10.4lfW\n",*pmed); ///arrumar a funcao para colocar valor certo

    fprintf(relat,"DATA\tHORA\tCORRENTE\tTENSAO\t\tPOTENCIA\tENERGIA\n");
    //loop de prints dos dados

        //====DIFERENCA DE TEMPO ENTRE AS LEITURAS====//
        for(i=0;i<*linhas;i=i+1){
            (*(leitura+i)).tempo=diff_tempo(&i,leitura);

        }
        i=0;

            energia=((*(leitura+i)).tensao*(*(leitura+i)).corrente*(*(leitura+i)).tempo);
            fprintf(relat,"%d\t%d\t%lf\t%lf\t%lf\t%lf\n",(*(leitura+i)).dia,(*(leitura+i)).hora,(*(leitura+i)).corrente,(*(leitura+i)).tensao,((*(leitura+i)).tensao*(*(leitura+i)).corrente),energia);

        for(i=1;i<*linhas;i=i+1){

            energia=((*(leitura+i)).tensao*(*(leitura+i)).corrente*((*(leitura+i)).tempo-(*(leitura+i-1)).tempo)); //energia entre amostras
            fprintf(relat,"%d\t%d\t%lf\t%lf\t%lf\t%lf\n",(*(leitura+i)).dia,(*(leitura+i)).hora,(*(leitura+i)).corrente,(*(leitura+i)).tensao,((*(leitura+i)).tensao*(*(leitura+i)).corrente),energia);

        }

    fclose(relat);
    printf("Relatorio .txt gerado\n");
}
//===RELATORIO CSV===//
void gerar_relatorio_csv(struct data leitura[], int *linhas){

    FILE *relatcsv;
    int i=0;
    double energia;
    //struct data minha_leitura[*linhas];
    relatcsv=fopen("relatorio.csv", "w"); //nao possui protecao pra saber se o arquivo ja existe. talvez se sobreescrever um arquivo antigo com mais medicoes, haja conflito de dados

        i=0; //o zero eh separado uma vez que não existe elemento anterior para comparar no calculo de energia

            energia=((*(leitura+i)).tensao*(*(leitura+i)).corrente*(*(leitura+i)).tempo);
            fprintf(relatcsv,"%d;%d;%lf;%lf;%lf;%lf\n",(*(leitura+i)).dia,(*(leitura+i)).hora,(*(leitura+i)).corrente,(*(leitura+i)).tensao,((*(leitura+i)).tensao*(*(leitura+i)).corrente),energia);

        for(i=1;i<*linhas;i=i+1){

            energia=((*(leitura+i)).tensao*(*(leitura+i)).corrente*((*(leitura+i)).tempo-(*(leitura+i-1)).tempo));
            fprintf(relatcsv,"%d;%d;%lf;%lf;%lf;%lf\n",(*(leitura+i)).dia,(*(leitura+i)).hora,(*(leitura+i)).corrente,(*(leitura+i)).tensao,((*(leitura+i)).tensao*(*(leitura+i)).corrente),energia);

        }
fclose(relatcsv);
printf("Relatorio .csv gerado\n");
}

void procedimento_tcp(){

    int linhas,i;
    double crms=0, trms=0, pmed=0;

    //===CONTANDO A QUANTIDADE DE LINHAS DO ARQUIVO===//
    linhas=quant_linhas();

    //==ALOCANDO A MEMORIA NECESSARIA PARA A STRUCT===//
    leitura = (struct data *)malloc((linhas+1)*sizeof(struct data));
              //type casting    //alocacao de n espaços do tamanho do "vetor" data

    //====LEITURA ARQUIVO====//
    struct data minha_leitura[linhas];
    leitura_arquivo(linhas, minha_leitura);

    //====DIFERENCA DE TEMPO ENTRE AS LEITURAS====//
        for(i=0;i<linhas;i=i+1){
            (*(leitura+i)).tempo=diff_tempo(&i,minha_leitura);
            //printf("Diferenca de tempo entra amostra 0 e %d: %lf\n", i,(*(leitura+i)).tempo);
        }

    //====VALORES EM RMS E POTENCIA MEDIA====//
    trms=tensao_rms(&linhas, minha_leitura);
    crms=corrente_rms(&linhas, minha_leitura);
    pmed=potencia_media(&linhas,minha_leitura);
    //printf("Valor da tensao em rms eh: %lf\n",trms);
    //printf("Valor da corrente em rms eh: %lf\n",crms);
    //printf("Valor da potencia media: %lf\n",pmed);

    gerar_relatorio_txt(minha_leitura,&linhas,&trms,&crms,&pmed);
    gerar_relatorio_csv(minha_leitura,&linhas);

    free(leitura);
}
