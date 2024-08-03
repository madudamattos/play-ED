#ifndef _MUSICA_H
#define _MUSICA_H

#include <stdio.h>

typedef struct Musica Musica;

typedef struct CelulaMusica CelulaMusica;

typedef struct ListaDeMusica ListaDeMusica;

Musica *criaMusica(char *nome, char *artista);

ListaDeMusica *criaListaDeMusica();

void insereMusica(ListaDeMusica *lista, Musica *musica);

void retiraMusica(ListaDeMusica *lista, Musica *musica);

char *retornaNomeMusica(Musica *musica);

char *retornaArtistaMusica(Musica *musica);

int estaNaListaMusica(ListaDeMusica *lista, Musica *musica);

int ehIgualArtista(char *artista1, char *artista2);

int ehIgualNome(char *nome1, char *nome2);

int ehIgualMusica(Musica *musica1, Musica *musica2);

int ehIgualPonteiroMusica(Musica *musica1, Musica *musica2);

Musica *buscaMusicaPorArtista(ListaDeMusica *lista, char *artista);

Musica *buscaMusicaPorNome(ListaDeMusica *lista, char *nome);

void imprimeMusica(Musica *musica);

void imprimeListaDeMusica(ListaDeMusica *lista);

void destroiMusica(Musica *musica);

void destroiListaDeMusica(ListaDeMusica *lista);

void destroiListaEMusicas(ListaDeMusica *lista);

int ehVaziaListaMusica(ListaDeMusica *lista);

Musica *retornaProxMusica(ListaDeMusica *lista, Musica *musica);

Musica *retornaPrimMusica(ListaDeMusica *lista);

CelulaMusica *retornaPrimListaDeMusica(ListaDeMusica *lista);

CelulaMusica *retornaProxListaDeMusica(CelulaMusica *celula);

Musica *retornaMusicaCelula(CelulaMusica *celula);

#endif