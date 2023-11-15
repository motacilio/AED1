#include "datas.h"
#include <stdlib.h>

#define IGUAL 0
#define MENOR -1
#define MAIOR 1
#define FALSE 0
#define TRUE 1


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
