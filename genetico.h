#ifndef GENETICO_H_INCLUDED
#define GENETICO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    bool Cromossomo[8][3];
}individuo;

typedef struct{
    individuo Individuo[16];
}populacao;

individuo GenerateIndividuo(){

    individuo p;
    int i, j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 3; j++){
            p.Cromossomo[i][j] = rand() %2;
        }
    }
    return p;
}

populacao GeneratePopulacao(){
    populacao p;
    int c;
    for(c = 0; c < 16; c++){
        p.Individuo[c] = GenerateIndividuo();
    }
    return p;
}

bool testaLinha(individuo i1, int col1, int col2){

    if(i1.Cromossomo[col1][0] != i1.Cromossomo[col2][0])
        return false;
    else if(i1.Cromossomo[col1][1] != i1.Cromossomo[col2][1])
        return false;
    else if(i1.Cromossomo[col1][2] != i1.Cromossomo[col2][2])
        return false;
    else return true;
}


int bintodec(bool vet[3]){
    int i = 4*vet[0] + 2*vet[1] + vet[2];
    return i;
}

/*---------------------
Testar a Diagonal:
1 - Converter as duas linhas para inteiro;
2 - Calcular x, sendo x = col2 - col1;
3 - Calcular y, sendo y = linha1 +|- x;
4 - Se y1 ou y2 for igual a linha2, então existe o conflito.
*/
bool testaDiagonal(individuo i1, int col1, int col2){

    int linha1 = bintodec(i1.Cromossomo[col1]), linha2 = bintodec(i1.Cromossomo[col2]);
    int x = col2 - col1;
    int y1 = linha1 + x, y2 = linha1 - x;
    return ((y1 == linha2)||(y2 == linha2));
}

bool apto(individuo i1, int col1, int col2){
    return((!testaLinha(i1,col1,col2))&&(!testaDiagonal(i1,col1,col2)));
}

int fAptidao(individuo i1){

    int conflitos = 0, i, j;
    for(i = 0; i < 8; i++){
        for(j = i + 1; j < 8; j++){
            if(!apto(i1,i,j))
                conflitos++;
        }
    }
    return conflitos;
}

int minfApt(populacao p){

    int minimo = 0, fmin = fAptidao(p.Individuo[0]), atu, fatu;
    for(atu = 1; atu < 16; atu++){
        fatu = fAptidao(p.Individuo[atu]);
        if(fatu < fmin){
            fmin = fatu;
            minimo = atu;
        }
    }
    return minimo;
}

bool selOtm(populacao p){

    int minimo = minfApt(p), fMin = fAptidao(p.Individuo[minimo]);
    return(fMin == 0);
}

populacao ordenaPopulacao(populacao p){

    int aptidao[16], c;
    for(c = 0; c < 16; c++){
        aptidao[c] = fAptidao(p.Individuo[c]);
    }
    int i, j, minimo, auxint;
    individuo aux;
    for(i = 0; i < 16; i++){
        minimo = i;
        for(j = i + 1; j < 16; j++){
            if(aptidao[j] < aptidao[minimo])
                minimo = j;
        }
        auxint = aptidao[i];
        aptidao[i] = aptidao[minimo];
        aptidao[minimo] = auxint;
        aux = p.Individuo[i];
        p.Individuo[i] = p.Individuo[minimo];
        p.Individuo[minimo] = aux;
    }
    return p;
}

individuo CrossOver(individuo A, individuo B){

    individuo F;
    int i, j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 3; j++){
            if(i%2 == 0){
                F.Cromossomo[i][j] = A.Cromossomo[i][j];
                F.Cromossomo[i][j] = F.Cromossomo[i][j]%2;
            }
            else{
                F.Cromossomo[i][j] = B.Cromossomo[i][j];
                F.Cromossomo[i][j] = F.Cromossomo[i][j]%2;
            }
        }
    }
    return F;
}

populacao copiaPopulacao(populacao p){

    populacao copia;
    int i, j, k;
    for(i = 0; i < 16; i++){
        for(j = 0; j < 8; j++){
            for(k = 0; k < 3; k++){
                copia.Individuo[i].Cromossomo[j][k] = p.Individuo[i].Cromossomo[j][k];
            }
        }
    }
    return copia;
}

populacao Elitismo(populacao p){

    p = ordenaPopulacao(p);
    populacao Nova;
    int c, i = 0;
    for(c = 0; c < 2; c++){

        Nova.Individuo[c] = p.Individuo[c];
    }
    for(c = 2; c < 16; c = c + 2){

        Nova.Individuo[c] = CrossOver(p.Individuo[i],p.Individuo[i+1]);
        Nova.Individuo[c+1] = CrossOver(p.Individuo[i+1],p.Individuo[i]);
        i = i + 2;
    }
    return Nova;
}

populacao novaPopulacao(populacao p){

    populacao Nova;
    Nova = Elitismo(p);
    int i, j, k, c;
    for(c = 0; c < 3; c++){
        i = rand()%16;
        j = rand()%8;
        k = rand()%3;
        Nova.Individuo[i].Cromossomo[j][k] = !Nova.Individuo[i].Cromossomo[j][k];
    }
    return Nova;
}

void printIndividuo(individuo i){

    int x, y;
    for(x = 0; x < 8; x++){
        for(y = 0; y < 3; y++)
            printf("%d ", i.Cromossomo[x][y]);
        printf("\n");
    }
}

void printPopulacao(populacao p){

    int c;
    for(c = 0; c < 16; c++){
        printf("Individuo %d: \n",(c + 1));
        printIndividuo(p.Individuo[c]);
    }
}

void printAllAptidoes(populacao p){

    int c, apt;
    printf("\n");
    printf("Aptidao de todos os individuos: \n");
    for(c = 0; c < 16; c++){
        apt = fAptidao(p.Individuo[c]);
        printf("\n");
        printf("Aptidao %d = %d; \n",(c + 1),apt);
    }
}


#endif // GENETICO_H_INCLUDED
