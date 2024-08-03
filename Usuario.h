#ifndef _USUARIO_H_
#define _USUARIO_H_

#include "Playlist.h"
#include <stdio.h>

typedef struct Usuario Usuario;

typedef struct CelulaUsuario CelulaUsuario;

typedef struct ListaDeUsuario ListaDeUsuario;

Usuario *criaUsuario(char *nome);

void atribuiListaDePlaylist(Usuario *usuario, ListaDePlaylist *listaDePlaylist);

ListaDePlaylist *retornaListaPlaylistUsuario(Usuario *usuario);

void atribuiQtdPlaylistsUsuario(Usuario *usuario, int qtdPlaylists);

ListaDeUsuario *criaListaDeUsuario();

void adicionaAmigo(Usuario *usuario, Usuario *amigo);

void insereUsuario(ListaDeUsuario *lista, Usuario *usuario);

char *retornaNomeUsuario(Usuario *usuario);

Usuario *buscaUsuarioPorNome(ListaDeUsuario *lista, char *nome);

void imprimeUsuario(Usuario *usuario);

void imprimeUsuarioArquivo(Usuario *usuario, FILE *arquivo);

void imprimeListaDeUsuario(ListaDeUsuario *usuarios);

void imprimeAmigos(Usuario *usuario);

void destroiListaDeAmigos(Usuario *usuario);

void destroiUsuario(Usuario *usuario);

void destroiListaDeUsuario(ListaDeUsuario *lista);

void destroiListaEUsuarios(ListaDeUsuario *lista);

//-----------------------------------------------------------
// modificado 15/05

Usuario *retornaPrimUsuario(ListaDeUsuario *lista);

Usuario *retornaProxUsuario(ListaDeUsuario *lista, Usuario *usuario);

int ehVaziaListaPlaylistUsuario(Usuario *usuario);

void insereListaPlaylistUsuario(Usuario *usuario, ListaDePlaylist *lista);

// DEGUB TESTANDO COM CELULAS
CelulaUsuario *retornaPrimListaDeUsuario(ListaDeUsuario *lista);

CelulaUsuario *retornaProxListaDeUsuario(CelulaUsuario *celula);

Usuario *retornaUsuarioCelula(CelulaUsuario *celula);

ListaDeUsuario* retornaListaAmigosUsuario(Usuario* user);

void atribuiSimilaridadeAoUsuario(Usuario* user);

int retornaSimilaridadeUsuario(Usuario* user);

#endif
