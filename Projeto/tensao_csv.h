#ifndef TENSAO_CSV_H_INCLUDED
#define TENSAO_CSV_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//====ESTRUTURA DE ARMAZENAMENTO DAS VARIAVEIS====//
 struct data {
    int hora,minuto,segundo,dia,mes,ano;
    double tempo, tensao, corrente;
}*leitura;

//====PROTOTIPOS====//
void medicoes_csv();
int quant_linhas();
void procedimento_tcp();
void leitura_arquivo(int lines, struct data leitura[]);
double potencia(int n,struct data leitura[]);
double diff_tempo(int *amostra,struct data leitura[]);
double tensao_rms(int *linhas,struct data leitura[]);
double corrente_rms(int *linhas,struct data leitura[] );
double potencia_media(int *linhas,struct data leitura[]);
void gerar_relatorio_txt(struct data leitura[], int *linhas, double *trms, double *crms,double *pmed);
void gerar_relatorio_csv(struct data leitura[], int *linhas);
void procedimento_tcp();
double funcao_integral (double x);
#endif // TENSAO_CSV_H_INCLUDED
