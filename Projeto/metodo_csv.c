#ifndef METODOS_NUMERICOS_H
#define METODOS_NUMERICOS_H
#include "metodos_numericos.h"
#endif // METODOS_NUMERICOS_H
#ifndef TENSAO_CSV_H
#define TENSAO_CSV_H
#include "tensao_csv.h"
#endif // TENSAO_CSV_H
///**======PARTE 2 DA PRATICA=======**///

//====CONTADOR DE LINHAS====//
int quant_linhas(){

    char dummy;
    int lin=0;

    FILE *arch;
    arch=fopen("medicoes.csv","r");
        do{
            dummy=fgetc(arch);
            if((dummy=='\n')){ lin=lin+1; } //a cada aparecimento do caracter nova linha, logicamente, lemos uma nova linha
        } while(dummy!=EOF);
    fclose(arch);
    return lin;
    }

//====LEITURA DO ARQUIVO====//
void leitura_arquivo(int lines, struct data leitura[]){

    FILE *med;
    med=fopen("medicoes.csv","r");
    int i=0;
    char a=0;
    a=a*a;//linha feita somente para remover o aviso dado pelo compilador

          do{
                                                                                //obs: prints de verificacao comentados
            fscanf(med,"%d",&(*(leitura+i)).mes); //mes
            //printf("%d/",(*(leitura+i)).mes);
            a=getc(med); //le e ignora a '/'
            //printf("Char ignorado: %c\nmes:%d\n",a,(*(leitura+i)).mes);
            fscanf(med,"%d",&(*(leitura+i)).dia); //dia
            //printf("%d/",(*(leitura+i)).dia);
            a=getc(med); //le e ignora a '/'
            //printf("Char ignorado: %c\n",a);
            fscanf(med,"%d",&(*(leitura+i)).ano); //ano
            //printf("%d;",(*(leitura+i)).ano);
            a=getc(med); //le e ignora o ';'
            //printf("Char ignorado: %c\n",a);
            fscanf(med,"%d",&(*(leitura+i)).hora); //hora
            //printf("%d:",(*(leitura+i)).hora);
            a=getc(med); //le e ignora o ':'
            //printf("Char ignorado: %c\n",a);
            fscanf(med,"%d",&(*(leitura+i)).minuto); //minuto
            //printf("%d:",(*(leitura+i)).minuto);
            a=getc(med); //le e ignora o ':'
            //printf("Char ignorado: %c\n",a);
            fscanf(med,"%d",&(*(leitura+i)).segundo); //segundo
            //printf("%d;",(*(leitura+i)).segundo);
            a=getc(med); //le e ignora o ';'
            //printf("Char ignorado: %c\n",a);
            fscanf(med,"%lf",&(*(leitura+i)).corrente); //corrente
            //printf("%.5lf;",(*(leitura+i)).corrente);
            a=getc(med); //le e ignora o ';'
            //printf("Char ignorado: %c\n",a);
            fscanf(med,"%lf",&(*(leitura+i)).tensao); //tensao
            //printf("%.5lf\n",(*(leitura+i)).tensao);

            i=i+1;

         }while (i<lines); //sabendo a quantidade de linhas, podemos ler o arquivo por completo

    fclose(med);
    printf("Leitura do .csv de medicoes realizada.\n");
}

//====FUNCAO DADA PELO PROFESSOR REFERENTE A PARTE====//
double diff_tempo(int *amostra,struct data leitura[]){

    struct tm t_inicio, t_fim;
    struct tm ;

    t_inicio.tm_isdst=-1;
    t_inicio.tm_mday=(*leitura).dia;
    t_inicio.tm_mon=(*leitura).mes - 1;
    t_inicio.tm_year=(*leitura).ano - 1900;
    t_inicio.tm_hour=(*leitura).hora;
    t_inicio.tm_min=(*leitura).minuto;
    t_inicio.tm_sec=(*leitura).segundo;

    t_fim.tm_isdst=-1;
    t_fim.tm_mday=(*(leitura+*amostra)).dia;
    t_fim.tm_mon=(*(leitura+*amostra)).mes - 1;
    t_fim.tm_year=(*(leitura+*amostra)).ano - 1900;
    t_fim.tm_hour=(*(leitura+*amostra)).hora;
    t_fim.tm_min=(*(leitura+*amostra)).minuto;
    t_fim.tm_sec=(*(leitura+*amostra)).segundo;

return (difftime( mktime(&t_fim), mktime(&t_inicio) )/(double)(3600) );
}
//====FUNCAO PRINCIPAL DA ROTINA DE LEITURA DE MEDICOES====//
void medicoes_csv(){

    int linhas=0;//, amostra;
    //===CONTANDO A QUANTIDADE DE LINHAS DO ARQUIVO===//
    linhas=quant_linhas();
    //printf("Quantidade de linhas: %d\n", linhas);
    //==ALOCANDO A MEMORIA NECESSARIA PARA A STRUCT===//
    leitura =(struct data *)malloc((linhas+1)*sizeof(struct data));
    //====LEITURA ARQUIVO====//
    struct data minha_leitura[linhas]; //vetor da estrutura
    leitura_arquivo(linhas, minha_leitura);
    //===LIBERANDO O ESPAÇO ALOCADO DINAMICAMENTE===//
    free(leitura);
}

