#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "Musica.h"
#include <stdio.h>

typedef struct Playlist Playlist;

typedef struct CelulaPlaylist CelulaPlaylist;

typedef struct ListaDePlaylist ListaDePlaylist;

Playlist *criaPlaylist(char *nome);

ListaDePlaylist *criaListaDePlaylist();

void inserePlaylistNaLista(ListaDePlaylist *lista, Playlist *playlist);

void retiraPlaylistDaLista(ListaDePlaylist *lista, Playlist *playlist);

void insereMusicaNaPlaylist(Playlist *playlist, Musica *musica);

void retiraMusicaDaPlaylist(Playlist *playlist, Musica *musica);

char *retornaNomePlaylist(Playlist *playlist);

ListaDeMusica *retornaListaMusica(Playlist *playlist);

Playlist *buscaPlaylistPorNome(ListaDePlaylist *lista, char *nome);

int ehNomePlaylist(Playlist *playlist1, char *nome);

void imprimePlaylist(Playlist *playlist);

void imprimePlaylistArquivo(Playlist *playlist, FILE *arquivo);

void imprimeMusicasArquivoPlaylist(Playlist *playlist, FILE *arquivo);

void imprimeListaDePlaylist(ListaDePlaylist *lista);

void imprimeListaDePlaylistArquivo(ListaDePlaylist *lista, FILE *arquivo);

void destroiPlaylist(Playlist *playlist);

void destroiListaDePlaylist(ListaDePlaylist *lista);

void destroiListaEPlaylists(ListaDePlaylist *lista);

Playlist *retornaPrimPlaylist(ListaDePlaylist *lista);

Playlist *retornaProxPlaylist(ListaDePlaylist *lista, Playlist *playlist);

int ehVaziaPlaylist(Playlist *playlist);

int ehUltimaPlaylist(ListaDePlaylist *lista, Playlist *p);

int ehVaziaListaPlaylist(ListaDePlaylist *lista);

int ehPlaylistDoArtista(Playlist *playlist, Musica *musica);

int ehIgualPonteiroPlaylist(Playlist *playlist1, Playlist *playlist2);

Musica *retornaPrimMusicaPlaylist(Playlist *playlist);

Musica *retornaProxMusicaPlaylist(Playlist *playlist, Musica *musica);

Musica *buscaMusicaNaListaPlaylist(ListaDePlaylist *lista, Musica *musica);

void incrementaPlaylist(ListaDeMusica *origem, Playlist *destino);

#endif
