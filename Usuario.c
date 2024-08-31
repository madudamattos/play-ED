#include "Usuario.h"
#include <stdlib.h>
#include <string.h>

struct Usuario
{
    char *nome;
    int qtdPlaylists;
    int similardades;
    ListaDePlaylist *playlists;
    ListaDeUsuario *amigos;
};

struct CelulaUsuario
{
    Usuario *usuario;
    CelulaUsuario *prox;
    CelulaUsuario *ant;
};

struct ListaDeUsuario
{
    CelulaUsuario *prim;
    CelulaUsuario *ult;
};

Usuario *criaUsuario(char *nome)
{
    Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));

    usuario->nome = strdup(nome);
    usuario->qtdPlaylists = 0;
    usuario->similardades = 0;
    usuario->playlists = criaListaDePlaylist();
    usuario->amigos = criaListaDeUsuario();

    return usuario;
}

void atribuiQtdPlaylistsUsuario(Usuario *usuario, int qtdPlaylists)
{
    usuario->qtdPlaylists = qtdPlaylists;
}

void atribuiListaDePlaylist(Usuario *usuario, ListaDePlaylist *listaDePlaylist)
{
    usuario->playlists = listaDePlaylist;
}

ListaDeUsuario *criaListaDeUsuario()
{
    ListaDeUsuario *lista = (ListaDeUsuario *)malloc(sizeof(ListaDeUsuario));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

void insereUsuario(ListaDeUsuario *lista, Usuario *usuario)
{
    CelulaUsuario *nova = (CelulaUsuario *)malloc(sizeof(CelulaUsuario));

    nova->usuario = usuario;
    nova->prox = NULL;

    if (lista->prim == NULL)
    {
        lista->prim = nova;
        lista->ult = nova;
        nova->ant = NULL;
    }
    else
    {
        lista->ult->prox = nova;
        nova->ant = lista->ult;
        lista->ult = nova;
    }
}

void adicionaAmigo(Usuario *usuario, Usuario *amigo)
{
    if (!usuario || !amigo)
        return;

    insereUsuario(usuario->amigos, amigo);
    insereUsuario(amigo->amigos, usuario);
}

char *retornaNomeUsuario(Usuario *usuario)
{
    if (!usuario)
        return NULL;

    return usuario->nome;
}

ListaDePlaylist *retornaListaPlaylistUsuario(Usuario *usuario)
{
    if (!usuario)
        return NULL;

    return usuario->playlists;
}

Usuario *buscaUsuarioPorNome(ListaDeUsuario *lista, char *nome)
{
    if (nome == NULL || lista == NULL)
        return NULL;

    CelulaUsuario *p = lista->prim;

    while (p != NULL)
    {
        if (strcmp(p->usuario->nome, nome) == 0)
        {
            return p->usuario;
        }
        p = p->prox;
    }

    return NULL;
}

void imprimeUsuarioArquivo(Usuario *usuario, FILE *arquivo)
{
    fprintf(arquivo, "%s;%d", usuario->nome, usuario->qtdPlaylists);
    imprimeListaDePlaylistArquivo(usuario->playlists, arquivo);
    fprintf(arquivo, "\n");
}

int ehIgualPonteiroUsuario(Usuario *usuario1, Usuario *usuario2)
{
    if (!usuario1 || !usuario2)
        return 0;

    return usuario1 == usuario2;
}

Usuario *retornaPrimUsuario(ListaDeUsuario *lista)
{
    if (!lista)
        return NULL;

    return lista->prim->usuario;
}

Usuario *retornaProxUsuario(ListaDeUsuario *lista, Usuario *usuario)
{
    if (usuario == lista->ult->usuario)
        return NULL;

    CelulaUsuario *p = lista->prim;
    while (p != NULL)
    {
        if (ehIgualPonteiroUsuario(p->usuario, usuario))
        {
            return p->prox->usuario;
        }
        p = p->prox;
    }
    return NULL;
}

int ehVaziaListaPlaylistUsuario(Usuario *usuario)
{
    if (!usuario)
        return 1;

    return ehVaziaListaPlaylist(usuario->playlists);
}

void insereListaPlaylistUsuario(Usuario *usuario, ListaDePlaylist *lista)
{
    if (!usuario)
        return;

    usuario->playlists = NULL;
    usuario->playlists = lista;
}

ListaDeUsuario *retornaListaAmigosUsuario(Usuario *user)
{
    if (!user)
        return NULL;

    return user->amigos;
}

void atribuiSimilaridadeAoUsuario(Usuario *user)
{
    if (!user)
        return;

    user->similardades = 1;
}

int retornaSimilaridadeUsuario(Usuario *user)
{
    if (!user)
        return 0;

    return user->similardades;
}

void destroiListaDeAmigos(Usuario *usuario)
{
    if (!usuario)
        return;

    destroiListaDeUsuario(usuario->amigos);
}

void destroiUsuario(Usuario *usuario)
{
    if (!usuario)
        return;

    destroiListaDePlaylist(usuario->playlists);
    destroiListaDeAmigos(usuario);
    free(usuario->nome);
    free(usuario);
}

void destroiListaDeUsuario(ListaDeUsuario *lista)
{
    if (!lista)
        return;

    CelulaUsuario *aux = lista->prim;
    CelulaUsuario *prox;

    while (aux != NULL)
    {
        prox = aux->prox;
        free(aux);
        aux = prox;
    }

    free(lista);
}

void destroiListaEUsuarios(ListaDeUsuario *lista)
{
    if (!lista)
        return;

    CelulaUsuario *aux = lista->prim;
    CelulaUsuario *prox;

    while (aux != NULL)
    {
        prox = aux->prox;
        destroiUsuario(aux->usuario);
        free(aux);
        aux = prox;
    }

    free(lista);
}