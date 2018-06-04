#include "metodos_numericos.h" //referente a primeira parte da pratica
#include "tensao_csv.h" //referente a segunda e terceira parte da pratica

int main (){

    int menu;

    printf("==============================MENU==============================\n");
    printf("1 - Aproximacao pelo metodo dos trapezios\n2 - Analise de tensao em arquivo .csv\n");
    printf("3 - RMS de tensao e corrente e potencia de amostras\n");
    scanf("%d",&menu);

        switch(menu){
            case 1:
            variaveis_trapez();
            break;
            case 2:
            medicoes_csv();
            break;
            case 3:
            procedimento_tcp();
            break;
            default:
            break;
        }

    system("pause");

return 0;
}

