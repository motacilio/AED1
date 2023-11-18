#include "datas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IGUAL 0
#define MENOR -1
#define MAIOR 1
#define FALSE 0
#define TRUE 1


// arquivo .h
typedef struct data Data;

Data *criaData (unsigned int dia, unsigned int mes, unsigned int ano);
Data * copiaData (Data d);
void liberaData (Data * d);
Data * somaDiasData (Data d, unsigned int dias);
Data * subtrairDiasData (Data d, unsigned int dias);
void atribuirData (Data * d, unsigned int dia, unsigned int mes, unsigned int ano);
unsigned int obtemDiaData (Data d);
unsigned int obtemMesData (Data d);
unsigned int obtemAnoData (Data d);
unsigned int bissextoData (Data d);
int comparaData (Data d1, Data d2);
unsigned int numeroDiasDatas (Data d1, Data d2);
unsigned int numeroMesesDatas (Data d1, Data d2);
unsigned int numeroAnosDatas(Data d1, Data d2);
unsigned int obtemDiaSemanaData (Data d);

char * imprimeData (Data d, char * formato);
void opcoes();


// arquivo.c

void opcoes(){
    printf("1. Criar uma data\n");
    printf("2. Copiar uma data\n");
    printf("3. Apagar uma data\n");
    printf("4. Adicioar n dias a uma data\n");
    printf("5. Subtrair n dias de uma data\n");
    printf("6. Atribuir uma data nova a uma data existente: \n");
    printf("7. Retorna o dia de uma data\n");
    printf("8. Retorna o mes de uma data\n");
    printf("9. Retorna o ano de uma data\n");
    printf("10. Verifica se o ano de uma data é bissexto\n");
    printf("11. Verifica se a data D1 é maior, menor ou igual a uma data D2\n");
    printf("12. Retorna o número de dias que existe entre as datas d1 e d2\n");
    printf("13. Retorna o número de meses que existe entre as datas d1 e d2\n");
    printf("14. Retorna o numero de anos que existem entre as datas d1 e d2\n");
    printf("15. Retorna o dia da semana de uma data\n");
    printf("16. Imprime uma data\n");
    printf("0 - para o programa\n");
    printf("99 - mostra as opcoes novamente\n");

}

struct data{
    unsigned int dia;
    unsigned int mes;
    unsigned int ano;
};

Data *criaData(unsigned int dia, unsigned int mes, unsigned int ano){
    Data *data = (Data *) calloc(1, sizeof(Data));
    data->dia = dia;
    data->mes = mes;
    data->ano = ano;
    return data;
}

Data * copiaData (Data d){
    Data *copia = criaData(d.dia, d.mes, d.ano);
    return copia;
}

void liberaData (Data * d){
    if(d != NULL){
    free(d);
    d = NULL;
    }
}

// Funcao auxiliar pra calcular o numero de dias em um mês
unsigned int diasNoMes(Data d) {
    unsigned int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d.mes == 2 && bissextoData(d)) {
        return 29;
    } else {
        return diasPorMes[d.mes];
    }
}

Data *somaDiasData(Data d, unsigned int dias) {
    Data *dPos = (Data *)calloc(1, sizeof(Data));
    dPos->ano = d.ano;
    dPos->mes = d.mes;
    dPos->dia = d.dia;

    while (dias > 0) {
        unsigned diasMesAtual = diasNoMes(*dPos);

        if (dias + dPos->dia > diasMesAtual) {
            dias -= (diasMesAtual - dPos->dia + 1);
            dPos->dia = 1;

            if (dPos->mes == 12) {
                dPos->mes = 1;
                dPos->ano++;
            } else {
                dPos->mes++;
            }
        } else {
            dPos->dia += dias;
            dias = 0;
        }
    }

    return dPos;
}

Data *subtrairDiasData(Data d, unsigned int dias) {
    Data *dAnt = (Data *)calloc(1, sizeof(Data));
    dAnt->ano = d.ano;
    dAnt->mes = d.mes;
    dAnt->dia = d.dia;

    while (dias > 0) {
        if (dAnt->dia > dias) {
            dAnt->dia -= dias;
            dias = 0;
        } else {
            dias -= dAnt->dia;  
            if (dAnt->mes == 1) {
                dAnt->mes = 12;
                dAnt->ano--;
            } else {
                dAnt->mes--;
            }
            int diasMesAnterior = diasNoMes(*dAnt);
            dAnt->dia = diasMesAnterior;
        }
    }

    return dAnt;
}

void atribuirData (Data * d, unsigned int dia, unsigned int mes, unsigned int ano){
    if(d == NULL){
        printf("Data inexistente\n");
    } else{
        d->dia = dia;
        d->ano = ano;
        d->mes = mes;
    }
}

unsigned int obtemDiaData (Data d){
    return d.dia;
}

unsigned int obtemMesData (Data d){
    return d.mes;
}

unsigned int obtemAnoData (Data d){
    return d.ano;
}


unsigned int bissextoData(Data d){
    if((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0)){
        return TRUE;
    } 
    return FALSE;
}

int comparaData (Data d1, Data d2){
    if(d1.ano > d2.ano){
        return MAIOR;
    } else if (d1.ano == d2.ano){
        if(d1.mes > d2.mes){
            return MAIOR;
        } else if(d1.mes == d2.mes){
            if(d1.dia > d2.dia){
                return MAIOR;
            } else if(d1.dia == d2.dia){
                return IGUAL;
            } else {
                return MENOR;
            }
        }
    } 

    return MENOR; 
    
}

unsigned int numeroDiasDatas (Data d1, Data d2){
    unsigned int dias = 0;
    if(comparaData(d1, d2) == IGUAL){
        return 0;
    } else if(comparaData(d1, d2) == MAIOR){
        Data dAux = d2;
        d2 = d1;
        d1 = dAux;
    } 
    while(comparaData(d1, d2) != IGUAL){
        dias++;
        d1.dia++;
        if(d1.dia > diasNoMes(d1)){
            d1.dia = 1;
            d1.mes++;
            if(d1.mes > 12){
                d1.mes = 1;
                d1.ano++;
            }
        }
    }
    return dias;
}

unsigned int numeroMesesDatas(Data d1, Data d2){
    unsigned int meses = 0;
    if(comparaData(d1, d2) == MAIOR){
        Data auxData = d2;
        d2 = d1;
        d1 = auxData;
    }
    while(comparaData(d1, d2) != IGUAL){
        meses++;
        d1.mes++;
        if(d1.mes > 12){
            d1.mes = 1;
            d1.ano++;
        }
    }    
    return meses;
}    

unsigned int numeroAnosDatas(Data d1, Data d2){
     if(comparaData(d1, d2) == MENOR){
        Data auxData = d1;
        d1 = d2;
        d2 = auxData;
    }
    unsigned int anos = d1.ano - d2.ano;
    return anos;
}

unsigned int obtemDiaSemanaData (Data d){
    unsigned int dia = d.dia;
    unsigned int m = 0;
    unsigned int a = 0;
    if(d.mes == 1){
       m = 13;
       a = d.ano - 1;
    } else if(d.mes == 2){
        m = 14;
        a = d.ano - 1;
    } else {

        m = d.mes;
        a = d.ano;
    }

    int k = dia + 2*m + ((3*(m + 1))/5) + a + (a/4) - (a/100) + (a/400) + 2;
    return(k % 7);

}

char * imprimeData (Data d, char * formato){
    char *dataFormatada = (char *)malloc(sizeof(char) * 11);
    if (strcmp(formato, "ddmmaaaa") == 0){
        snprintf(dataFormatada, 11, "%02u/%02u/%04u", d.dia, d.mes, d.ano);
    } else if (strcmp(formato, "aaaammdd") == 0){
        snprintf(dataFormatada, 11, "%04u/%02u/%02u", d.ano, d.mes, d.dia);
    } else if (strcmp(formato, "aaaa") == 0){
        snprintf(dataFormatada, 11, "%04u", d.ano);
    } else if (strcmp(formato, "mm") == 0){
        snprintf(dataFormatada, 11, "%02u", d.mes);
    } else if (strcmp(formato, "dd") == 0){
        snprintf(dataFormatada, 11, "%02u", d.dia);
    } else if (strcmp(formato, "ddmm") == 0){
        snprintf(dataFormatada, 11, "%02u%02u", d.dia, d.mes);
    } return dataFormatada;
}



// corpo principal

int main(){
    opcoes();

    Data *datas = NULL;
    int numDatas = 0;
    int data, data2; 
    int opcao = -1;
    

    while(opcao != 0){
        printf("Digite sua opcao: \n");
        scanf("%d", &opcao);

        if(opcao == 1){
            unsigned int dia, mes, ano;

            printf("Dia: ");
            scanf("%u", &dia);
            printf("Mes: ");
            scanf("%u", &mes);
            printf("Ano: ");
            scanf("%u", &ano);
            if (dia > 31 || (mes > 12) || (mes == 2 && dia > 29) || (ano < 1900 || ano > 2200)) {
                printf("Erro. Data inválida.\n");
            } else {
                Data *d = criaData(dia, mes, ano);
                datas = (Data *)realloc(datas, (numDatas + 1) * sizeof(Data));

                if (datas == NULL) {
                    printf("Erro ao alocar memória\n");
                    continue;
                }

                datas[numDatas] = *d;
                numDatas++;
                printf("Data %d criada com sucesso!\n", numDatas);             
            }   
        
        } else if(opcao == 2){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;

            datas = (Data *)realloc(datas, (numDatas + 1) * sizeof(Data));
            if (datas == NULL) {
                printf("Erro ao alocar memória\n");
                return 1;
            }   
            Data *copia = copiaData(datas[data]);
            datas[numDatas] = *copia;
            numDatas++;
            printf("Data %d criada com sucesso!\n", numDatas);             


        } else if(opcao == 3){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;

            liberaData(&datas[data]);
            printf("Data %d liberada!\n", ++data);
        } else if (opcao == 4) {
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;
            printf("Digite os dias: \n");
            int dias;
            scanf("%d", &dias);

        
            if (data >= 0 && data < numDatas) {
                datas[data] = *somaDiasData(datas[data], dias);
                printf("Data %d atualizada com sucesso!\n", data + 1);
            } else {
                printf("Erro. Índice de data inválido.\n");
            }            


        }else if(opcao == 5){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;
            printf("Digite os dias: \n");
            int dias; scanf("%d", &dias); 

             if (data >= 0 && data < numDatas) {
                datas[data] = *subtrairDiasData(datas[data], dias);
                printf("Data %d atualizada com sucesso!\n", data + 1);
            } else {
                printf("Erro. Índice de data inválido.\n");
            }           

        } else if(opcao == 6){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;

             if (data >= 0 && data < numDatas) {
                 unsigned int dia, mes, ano;

                printf("Dia: \n");
                scanf("%u", &dia);
                printf("Mes: \n");
                scanf("%u", &mes);
                printf("Ano: \n");
                scanf("%u", &ano);
                if (dia > 31 || (mes > 12) || (mes == 2 && dia > 29) || (ano < 1900 || ano > 2200)) {
                    printf("Erro. Data inválida.\n");
                } else {
                    atribuirData(&datas[data], dia, mes, ano);   
                }   
                printf("Data %d atualizada com sucesso!\n", ++data);
            } else {
                printf("Erro. Índice de data inválido.\n");
            
            }
        } else if(opcao == 7){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;

            if (data >= 0 && data < numDatas) {
                printf("Dia: %d\n", obtemDiaData(datas[data]));
            } else {
                printf("Erro. Índice de data inválido.\n");
            }     
        } else if(opcao == 8){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;

            if (data >= 0 && data < numDatas) {
                printf("Mes: %d\n", obtemMesData(datas[data]));
            } else {
                printf("Erro. Índice de data inválido.\n");
            }     
        } else if(opcao == 9){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;

            if (data >= 0 && data < numDatas) {
                printf("Ano: %d\n", obtemAnoData(datas[data]));
            } else {
                printf("Erro. Índice de data inválido.\n");
            }     
        } else if(opcao == 10){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;
            int isBissexto = bissextoData(datas[data]);
            if(isBissexto == TRUE){
                printf("O ano %d eh bissexto", datas[data].ano);
            } else{
                 printf("O ano %d nao eh bissexto", datas[data].ano);
            }
        } else if(opcao == 11){
            printf("Digite a data:\n");
            scanf("%d", &data); data--;
            printf("Digite a segunda data:\n");
            scanf("%d", &data2); data2--;

            int resultadoComp = comparaData(datas[data], datas[data2]);

            if(resultadoComp == 1){
                printf("A data %s é maior que %s\n", imprimeData(datas[data], "ddmmaaaa"), imprimeData(datas[data2], "ddmmaaaa"));
            } else if(resultadoComp == 0){
                printf("As datas sao iguais\n");
            } else{
                printf("A data %s e menor que %s\n", imprimeData(datas[data], "ddmmaaaa"), imprimeData(datas[data2], "ddmmaaaa"));
            }
        } else if(opcao == 12){
            printf("Digite a data:\n");
            scanf("%d", &data); data--;
            printf("Digite a segunda data:\n");
            scanf("%d", &data2); data2--;

            unsigned int dias = numeroDiasDatas(datas[data], datas[data2]);
            printf("Existem %u dias entre %s e %s\n", dias, imprimeData(datas[data], "ddmmaaaa"), imprimeData(datas[data2], "ddmmaaaa"));

        }  else if(opcao == 13){
            printf("Digite a data:\n");
            scanf("%d", &data); data--;
            printf("Digite a segunda data:\n");
            scanf("%d", &data2); data2--;

            unsigned int dias = numeroMesesDatas(datas[data], datas[data2]);
            printf("Existem %u meses entre %s e %s\n", dias, imprimeData(datas[data], "ddmmaaaa"), imprimeData(datas[data2], "ddmmaaaa"));

        } else if(opcao == 14){
            printf("Digite a data:\n");
            scanf("%d", &data); data--;
            printf("Digite a segunda data:\n");
            scanf("%d", &data2); data2--;

            unsigned int anos = numeroAnosDatas(datas[data], datas[data2]);
            printf("Existem %u anos entre %s e %s\n", anos, imprimeData(datas[data], "ddmmaaaa"), imprimeData(datas[data2], "ddmmaaaa"));

        } else if(opcao == 15){
            printf("Digite a data:\n");
            scanf("%d", &data); data--;

            int resto = obtemDiaSemanaData(datas[data]);
            if(resto == 0){
                printf("A data %s eh um sabado!\n", imprimeData(datas[data], "ddmmaaaa"));
            } else if(resto == 1){
                printf("A data %s eh um domingo!\n", imprimeData(datas[data], "ddmmaaaa"));
            } else if(resto == 2){
                printf("A data %s eh uma segunda!\n", imprimeData(datas[data], "ddmmaaaa"));
            } else if(resto == 3){
                printf("A data %s eh uma terca!\n", imprimeData(datas[data], "ddmmaaaa"));
            } else if(resto == 4){
                printf("A data %s eh uma quarta\n", imprimeData(datas[data], "ddmmaaaa"));
            } else if(resto == 5){
                printf("A data %s eh uma quinta!\n", imprimeData(datas[data], "ddmmaaaa"));
            } else  if(resto == 6){
                printf("A data %s eh uma sexta!\n", imprimeData(datas[data], "ddmmaaaa"));
            } else{
                printf("Erro\n");
            }

        }
         else if(opcao == 16){
            printf("Digite a data:\n");
            scanf("%d", &data);
            data--;
            printf("Digite o formato(1.aaaa  2.mm  3.dd  4.ddmm  5.ddmmaaaa  6.aaaammdd):");
            int formato;
            scanf("%d", &formato);
            if(formato == 1){
                printf("Data formatada: %s\n", imprimeData(datas[data], "aaaa"));
            } else if(formato == 2){
                printf("Data formatada: %s\n", imprimeData(datas[data], "mm"));
            } else if(formato == 3){
                printf("Data formatada: %s\n", imprimeData(datas[data], "dd"));
            } else if(formato == 4){
                printf("Data formatada: %s\n", imprimeData(datas[data], "ddmm"));
            } else if(formato == 5){
                printf("Data formatada: %s\n", imprimeData(datas[data], "ddmmaaaa"));
            } else if(formato == 6){
                printf("Data formatada: %s\n", imprimeData(datas[data], "aaaammdd"));
            }
            
        }
        else if(opcao == 0){
            for(int i = 0; i < numDatas; i++){
                free(&datas[data]);
            }
            free(datas);
            break;
        } else if(opcao == 99){
            opcoes();
        }



    }

}