#include "Playlist.h"
#include <stdlib.h>
#include <string.h>

struct Playlist
{
    char *nome;
    ListaDeMusica *listaDeMusica;
};

struct CelulaPlaylist
{
    Playlist *playlist;
    CelulaPlaylist *prox;
    CelulaPlaylist *ant;
};

struct ListaDePlaylist
{
    CelulaPlaylist *prim;
    CelulaPlaylist *ult;
};

Playlist *criaPlaylist(char *nome)
{
    Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));

    playlist->nome = strdup(nome);
    playlist->listaDeMusica = criaListaDeMusica();

    return playlist;
}

ListaDePlaylist *criaListaDePlaylist()
{
    ListaDePlaylist *lista = (ListaDePlaylist *)malloc(sizeof(ListaDePlaylist));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

void inserePlaylistNaLista(ListaDePlaylist *lista, Playlist *playlist)
{
    CelulaPlaylist *nova = (CelulaPlaylist *)malloc(sizeof(CelulaPlaylist));

    nova->playlist = playlist;
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

void retiraPlaylistDaLista(ListaDePlaylist *lista, Playlist *playlist)
{
    if (lista == NULL || playlist == NULL)
        return;

    CelulaPlaylist *p = lista->prim;
    CelulaPlaylist *anterior = NULL;

    while (p != NULL && p->playlist != playlist)
    {
        anterior = p;
        p = p->prox;
    }

    if (p == NULL)
        return;

    if (playlist == lista->prim->playlist && playlist == lista->ult->playlist)
    {
        lista->prim = NULL;
        lista->ult = NULL;
    }
    else
    {
        if (anterior == NULL)
            lista->prim = p->prox;
        else
            anterior->prox = p->prox;

        if (p == lista->ult)
            lista->ult = anterior;
    }

    free(p);
}

void insereMusicaNaPlaylist(Playlist *playlist, Musica *musica)
{
    insereMusica(playlist->listaDeMusica, musica);
}

void retiraMusicaDaPlaylist(Playlist *playlist, Musica *musica)
{
    retiraMusica(playlist->listaDeMusica, musica);
}

char *retornaNomePlaylist(Playlist *playlist) { return playlist->nome; }

ListaDeMusica *retornaListaMusica(Playlist *playlist)
{
    return playlist->listaDeMusica;
}

void imprimePlaylistArquivo(Playlist *playlist, FILE *arquivo)
{
    fprintf(arquivo, "%s.txt", playlist->nome);
}

void imprimeMusicasArquivoPlaylist(Playlist *playlist, FILE *arquivo)
{
    ListaDeMusica *listaMusica = retornaListaMusica(playlist);
    CelulaMusica *celulaMusica = retornaPrimListaDeMusica(listaMusica);
    Musica *musica = retornaMusicaCelula(celulaMusica);

    while (musica != NULL)
    {
        fprintf(arquivo, "%s - %s\n", retornaArtistaMusica(musica),
                retornaNomeMusica(musica));

        celulaMusica = retornaProxListaDeMusica(celulaMusica);
        musica = retornaMusicaCelula(celulaMusica);
    }
}

Playlist *buscaPlaylistPorNome(ListaDePlaylist *lista, char *nome)
{
    if (nome == NULL || lista == NULL)
        return NULL;

    CelulaPlaylist *p = lista->prim;

    while (p != NULL)
    {
        if (ehNomePlaylist(p->playlist, nome))
            return p->playlist;
        p = p->prox;
    }

    return NULL;
}

int ehNomePlaylist(Playlist *playlist1, char *nome)
{
    return strcmp(playlist1->nome, nome) == 0;
}

void imprimeListaDePlaylistArquivo(ListaDePlaylist *lista, FILE *arquivo)
{
    CelulaPlaylist *p = lista->prim;

    while (p != NULL)
    {
        fprintf(arquivo, ";%s.txt", retornaNomePlaylist(p->playlist));
        p = p->prox;
    }
}

Playlist *retornaPrimPlaylist(ListaDePlaylist *lista)
{
    return lista->prim->playlist;
}

Playlist *retornaProxPlaylist(ListaDePlaylist *lista, Playlist *playlist)
{
    if (playlist == lista->ult->playlist)
        return NULL;

    CelulaPlaylist *p = lista->prim;
    while (p != NULL)
    {
        if (ehIgualPonteiroPlaylist(p->playlist, playlist))
            return p->prox->playlist;

        p = p->prox;
    }
    return NULL;
}

Musica *retornaPrimMusicaPlaylist(Playlist *playlist)
{
    if (playlist == NULL)
        return NULL;
    Musica *musica = retornaPrimMusica(playlist->listaDeMusica);
    return musica;
}

Musica *retornaProxMusicaPlaylist(Playlist *playlist, Musica *musica)
{
    if (playlist == NULL || musica == NULL)
        return NULL;
    return retornaProxMusica(playlist->listaDeMusica, musica);
}

Musica *buscaMusicaNaListaPlaylist(ListaDePlaylist *lista, Musica *musica)
{
    Playlist *playlist = retornaPrimPlaylist(lista);
    char *nomeMusica = retornaNomeMusica(musica);
    char *nomeArtista = retornaArtistaMusica(musica);

    while (playlist != NULL)
    {
        Musica *musicaPlaylist = retornaPrimMusicaPlaylist(playlist);

        while (musicaPlaylist != NULL)
        {
            if (ehIgualMusica(musica, musicaPlaylist))
                return musicaPlaylist;

            musicaPlaylist = retornaProxMusica(retornaListaMusica(playlist), musicaPlaylist);
        }

        playlist = retornaProxPlaylist(lista, playlist);
    }

    return NULL;
}

int ehVaziaPlaylist(Playlist *playlist)
{
    return ehVaziaListaMusica(playlist->listaDeMusica);
}

int ehUltimaPlaylist(ListaDePlaylist *lista, Playlist *p)
{
    return p == lista->ult->playlist;
}

int ehVaziaListaPlaylist(ListaDePlaylist *lista)
{
    return lista->prim == NULL;
}

int ehIgualPonteiroPlaylist(Playlist *playlist1, Playlist *playlist2)
{
    if (playlist1 == playlist2)
        return 1;

    return 0;
}

void destroiPlaylist(Playlist *playlist)
{
    if (!playlist)
        return;

    free(playlist->nome);
    destroiListaDeMusica(playlist->listaDeMusica);
    free(playlist);
}

void destroiListaDePlaylist(ListaDePlaylist *lista)
{
    if (!lista)
        return;

    CelulaPlaylist *aux = lista->prim;
    CelulaPlaylist *prox;

    while (aux != NULL)
    {
        prox = aux->prox;
        free(aux);
        aux = prox;
    }

    free(lista);
}

void destroiListaEPlaylists(ListaDePlaylist *lista)
{
    if (!lista)
        return;

    CelulaPlaylist *aux = lista->prim;
    CelulaPlaylist *prox;

    while (aux != NULL)
    {
        prox = aux->prox;
        destroiPlaylist(aux->playlist);
        free(aux);
        aux = prox;
    }

    free(lista);
}