#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "genetico.h"
#include <conio.h>

void printTabuleiro(populacao p){

    int i = minfApt(p), c, vet[8];
    for(c = 0; c < 8; c++){
        vet[c] = bintodec(p.Individuo[i].Cromossomo[c]);
    }
    system("cls");
    printf("__________________________\n");
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 0, vet[1] == 0,  vet[2] == 0,  vet[3] == 0, vet[4] == 0, vet[5] == 0, vet[6] == 0, vet[7] == 0);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 1, vet[1] == 1,  vet[2] == 1,  vet[3] == 1, vet[4] == 1, vet[5] == 1, vet[6] == 1, vet[7] == 1);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 2, vet[1] == 2,  vet[2] == 2,  vet[3] == 2, vet[4] == 2, vet[5] == 2, vet[6] == 2, vet[7] == 2);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 3, vet[1] == 3,  vet[2] == 3,  vet[3] == 3, vet[4] == 3, vet[5] == 3, vet[6] == 3, vet[7] == 3);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 4, vet[1] == 4,  vet[2] == 4,  vet[3] == 4, vet[4] == 4, vet[5] == 4, vet[6] == 4, vet[7] == 4);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 5, vet[1] == 5,  vet[2] == 5,  vet[3] == 5, vet[4] == 5, vet[5] == 5, vet[6] == 5, vet[7] == 5);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 6, vet[1] == 6,  vet[2] == 6,  vet[3] == 6, vet[4] == 6, vet[5] == 6, vet[6] == 6, vet[7] == 6);
    printf("| %d  %d  %d  %d  %d  %d  %d  %d |\n",
           vet[0] == 7, vet[1] == 7,  vet[2] == 7,  vet[3] == 7, vet[4] == 7, vet[5] == 7, vet[6] == 7, vet[7] == 7);
    printf("__________________________\n");
}

int main(){

    populacao p;
    srand((unsigned)time(NULL));
    p = GeneratePopulacao();
    int i = 0;
    while(!selOtm(p)){
        p = novaPopulacao(p);
        i++;
        printf("Iteracao %d. \n",i);
    }
    printf("Apos %d iteracoes:\n",i);
    printf("Pressione alguma tecla para ver o tabuleiro: ");
    getch();
    printTabuleiro(p);
    return 0;
}
