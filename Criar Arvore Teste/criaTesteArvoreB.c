#include <stdio.h>
#include <stdlib.h>

#define MAXCHAVES 4


typedef struct {
    int contaChaves;
    int chave[MAXCHAVES];
    int filho[MAXCHAVES+1];
} PAGINA;


void printPagina(PAGINA* pag){
    int i;
    printf("\n-------------------------------");
    printf("\nNumero de Chaves: %d\n", pag->contaChaves);
    for(i=0; i<pag->contaChaves; i++){
        printf("\nChave[%d]: %d", i, pag->chave[i]);
    }
    printf("\n");
    for(i=0; i<MAXCHAVES+1; i++){
        printf("\nFilho[%d]: %d", i, pag->filho[i]);
    }
    printf("\n-------------------------------\n");
}


int novoRRN(FILE* arq){
    int offset, tamanhoPag, tamanhoCab;
    fseek(arq, 0, SEEK_END);
    offset = ftell(arq);
    tamanhoPag = sizeof(PAGINA);
    tamanhoCab = sizeof(int);
    return ( (offset-tamanhoCab)/tamanhoPag );
}


void escrevePagina(FILE* arq, int numChaves, int chave1, int chave2, int chave3, int chave4, int filho1, int filho2, int filho3, int filho4, int filho5){

    fseek(arq, 0, SEEK_END);
    int RRN = novoRRN(arq);
    printf("\n\nInserindo nova pagina no RRN: %d", RRN);

    PAGINA* pag = malloc(sizeof(PAGINA));
    pag->contaChaves = numChaves;
    pag->chave[0] = chave1;
    pag->chave[1] = chave2;
    pag->chave[2] = chave3;
    pag->chave[3] = chave4;
    pag->filho[0] = filho1;
    pag->filho[1] = filho2;
    pag->filho[2] = filho3;
    pag->filho[3] = filho4;
    pag->filho[4] = filho5;
    fwrite(pag, sizeof(PAGINA), 1, arq);
    printPagina(pag);
}


void escreveCabecalho(FILE* arq, int raizArvore){
    fseek(arq, 0, SEEK_SET);
    fwrite(&raizArvore, sizeof(int), 1, arq);
}


int main(){

    FILE* arq = fopen("arvoreTeste.txt", "wb");

    escreveCabecalho(arq, 2);
    escrevePagina(arq, 2, 1, 2, 0, 0, -1, -1, -1, -1, -1);
    escrevePagina(arq, 2, 4, 5, 0, 0, -1, -1, -1, -1, -1);
    escrevePagina(arq, 1, 3, 0, 0, 0, 0, 1, -1, -1, -1);

    fclose(arq);

    return 0;
}
