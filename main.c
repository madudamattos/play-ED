#include "Musica.h"
#include "PlayED.h"
#include "Playlist.h"
#include "Usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TAM_NOME_CAMINHO 100

int main(int argc, char *argv[])
{
    char caminhoPastaEntrada[TAM_NOME_CAMINHO] = "Entrada";
    char caminhoPastaSaida[TAM_NOME_CAMINHO] = "Saida";
    char caminhoPastaMerge[TAM_NOME_CAMINHO] = "Merge";

    PlayED *playED = criaPlayED(caminhoPastaEntrada);

    mkdir(caminhoPastaSaida, 0700);

    refatoraPlayED(playED);

    imprimePlayEDRefatorada(playED, caminhoPastaSaida);

    printf("Refatorada concluida!\n");

    imprimeSimilaridades(playED, caminhoPastaSaida);

    printf("Similaridades concluida!\n");

    mkdir(caminhoPastaMerge, 0700);

    mergePlayED(playED);

    imprimePlayEDMerged(playED);

    printf("Merge concluida!\n");

    liberaPlayED(playED);

    return 0;
}
