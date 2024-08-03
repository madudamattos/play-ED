#ifndef _PLAYED_H_
#define _PLAYED_H_

#include "Playlist.h"
#include "Usuario.h"

typedef struct PlayED PlayED;

ListaDeUsuario *retornaListaUsuario(PlayED *played);

ListaDePlaylist *retornaListaPlaylists(PlayED *played);

ListaDeMusica *retornaListaMusicas(PlayED *played);

PlayED *criaPlayED(char *caminhoPastaEntrada);

ListaDeUsuario *leListaDeUsuario(char *caminhoPastaEntrada);

void *lePlaylistsUsuarios(char *caminhoPastaEntrada, PlayED *played);

void liberaPlayED(PlayED *played);

void refatoraPlayED(PlayED *played);

void mergePlayED(PlayED *played);

void imprimePlayEDRefatorada(PlayED *played, char *caminhoPastaSaida);

void imprimeSimilaridades(PlayED *played, char *caminhoPastaSaida);

void imprimePlayEDMerged(PlayED *played);

#endif
