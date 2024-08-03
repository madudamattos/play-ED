#include "Musica.h"
#include "PlayED.h"
#include "Playlist.h"
#include "Usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME_CAMINHO 100

int main(int argc, char *argv[]) {
  char caminhoPastaSaida[TAM_NOME_CAMINHO] = "Saida";
  char caminhoPastaMerge[TAM_NOME_CAMINHO] = "Merge";
  char caminhoPastaEntrada[TAM_NOME_CAMINHO] = "Entrada2";

  PlayED *playED = criaPlayED(caminhoPastaEntrada);

  mkdir(caminhoPastaSaida, 0700);

  refatoraPlayED(playED);

  imprimePlayEDRefatorada(playED, caminhoPastaSaida);

  printf("refatorada concluida\n");

  imprimeSimilaridades(playED, caminhoPastaSaida);

  printf("similaridades concluida\n");

  mkdir(caminhoPastaMerge, 0700);

  mergePlayED(playED);

  imprimePlayEDMerged(playED);

  liberaPlayED(playED);

  return 0;
}
