#include <stdio.h>
#include <stdlib.h>


// arquivo .h
typedef struct paciente Paciente;
typedef struct lista Lista;
typedef struct hora_atual HoraAtual;
Lista *Lista_criar();
HoraAtual *HoraAtual_criar();
Paciente *Paciente_criar(int h, int m, int c);
void Lista_adicionar_fim(Lista *L, int h, int m, int c);
void Lista_imprimir(Lista *L);
int VerificarCondicaoCritica(Lista *pacientes, HoraAtual *atendimento);

//arquivo.c
struct paciente{
    int h;
    int m;
    int c;
    Paciente *proxPaciente;
};

struct lista{
    Paciente *inicio;
};

struct hora_atual{
    int h;
    int m;
};

HoraAtual *HoraAtual_criar(){
    HoraAtual *hora = (HoraAtual *) calloc(1, sizeof(HoraAtual));
    hora->h = 7;
    hora->m = 0;

    return hora; 
}
//Funcao para criar listas
Lista *Lista_criar(){
    Lista *L = (Lista *) calloc(1, sizeof(Lista));
    L->inicio = NULL;

    return L;
}

Paciente *Paciente_criar(int h, int m, int c){
    Paciente *p = (Paciente *)calloc(1, sizeof(Paciente));
    p->h = h;
    p->m = m;
    p->c = c;
    p->proxPaciente = NULL;

    return p; 
}

void Lista_adicionar_fim(Lista *L, int h, int m, int c){
    Paciente *p = Paciente_criar(h, m, c);

    if(L->inicio == NULL){
        L->inicio = p;
    } else{
        Paciente *pAtual = L->inicio;

        while(pAtual->proxPaciente != NULL){
            pAtual = pAtual->proxPaciente;
        }
        pAtual->proxPaciente = p;
    }   
}

void Lista_imprimir(Lista *L){
    Paciente *pAtual = L->inicio;

    int i = 1;
    while(pAtual != NULL){
        printf("Paciente %d\n", i++);
        printf("Hora de chegada: %02d:%02d\n", pAtual->h, pAtual->m);
        printf("Tempo ate ficar critico: %d\n", pAtual->c);
        pAtual = pAtual->proxPaciente;
    }
}

int VerificarCondicaoCritica(Lista *L, HoraAtual *atendimento){
    int c = 0;
    Paciente *pAux = L->inicio;

    while(pAux != NULL){
        int tempoPassou = (atendimento->h - pAux->h) * 60 + (atendimento->m - pAux->m);
        if(tempoPassou > pAux->c){
            c++;
        }

        atendimento->m += 30;
        if(atendimento->m == 60){
            atendimento->h++;
            atendimento->m = 0;
        } 
        pAux = pAux->proxPaciente;
    }
    return c;
}



// arquivo main


int main(){

    HoraAtual *hora =  HoraAtual_criar();
    Lista *pacientes = Lista_criar();
    int numPac = 0; 
    while(numPac <= 0 || numPac > 50){
        scanf("%d", &numPac);
    }
    int i;
    for (i = 0; i < numPac; i++) {
        int h, m, c;
        do {
            scanf("%d %d %d", &h, &m, &c);
        } while ((h < 7 || h > 19) || (m < 0 || m > 60) || (c < 0 || c > 720));

        Lista_adicionar_fim(pacientes, h, m, c);
    }


    int condicao = VerificarCondicaoCritica(pacientes, hora);
    printf("%d", condicao);

    //Lista_imprimir(pacientes);

}
