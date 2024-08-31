#include "Musica.h"
#include <stdlib.h>
#include <string.h>

struct Musica
{
    char *nome;
    char *artista;
};

struct CelulaMusica
{
    Musica *musica;
    CelulaMusica *prox;
    CelulaMusica *ant;
};

struct ListaDeMusica
{
    CelulaMusica *prim;
    CelulaMusica *ult;
};

Musica *criaMusica(char *nome, char *artista)
{
    Musica *musica = (Musica *)malloc(sizeof(Musica));

    musica->nome = strdup(nome);
    musica->artista = strdup(artista);

    return musica;
}

ListaDeMusica *criaListaDeMusica()
{
    ListaDeMusica *lista = (ListaDeMusica *)malloc(sizeof(ListaDeMusica));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

void insereMusica(ListaDeMusica *lista, Musica *musica)
{
    CelulaMusica *nova = (CelulaMusica *)malloc(sizeof(CelulaMusica));

    nova->musica = musica;
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

void retiraMusica(ListaDeMusica *lista, Musica *musica)
{
    if (lista == NULL || musica == NULL)
        return;

    CelulaMusica *p = lista->prim;
    CelulaMusica *anterior = NULL;

    while (p != NULL && !ehIgualPonteiroMusica(p->musica, musica))
    {
        anterior = p;
        p = p->prox;
    }

    if (p == NULL)
        return;

    if (anterior == NULL)
    {
        lista->prim = p->prox;
    }
    else
    {
        anterior->prox = p->prox;
    }

    if (p->prox == NULL)
    {
        lista->ult = anterior;
    }

    free(p);
}

char *retornaNomeMusica(Musica *musica)
{
    if (!musica)
        return NULL;

    return musica->nome;
}

char *retornaArtistaMusica(Musica *musica)
{
    if (!musica)
        return NULL;

    return musica->artista;
}

int estaNaListaMusica(ListaDeMusica *lista, Musica *musica)
{
    if (musica == NULL || lista == NULL)
        return 0;

    CelulaMusica *p = lista->prim;

    while (p != NULL)
    {
        if (ehIgualMusica(p->musica, musica))
        {
            return 1;
        }
        p = p->prox;
    }

    return 0;
}

int ehIgualArtista(char *artista1, char *artista2)
{
    if (strcmp(artista1, artista2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ehIgualNome(char *nome1, char *nome2)
{
    if (strcmp(nome1, nome2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ehIgualMusica(Musica *musica1, Musica *musica2)
{
    if (ehIgualNome(musica1->nome, musica2->nome) &&
        ehIgualArtista(musica1->artista, musica2->artista))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ehIgualPonteiroMusica(Musica *musica1, Musica *musica2)
{
    if (musica1 == musica2)
    {
        return 1;
    }
    return 0;
}

Musica *buscaMusicaPorArtista(ListaDeMusica *lista, char *artista)
{
    if (artista == NULL || lista == NULL)
        return NULL;

    CelulaMusica *p = lista->prim;

    while (p != NULL)
    {
        if (ehIgualArtista(p->musica->artista, artista))
        {
            return p->musica;
        }
        p = p->prox;
    }

    return NULL;
}

Musica *buscaMusicaPorNome(ListaDeMusica *lista, char *nome)
{
    if (nome == NULL || lista == NULL)
        return NULL;

    CelulaMusica *p = lista->prim;

    while (p != NULL)
    {
        if (ehIgualNome(p->musica->nome, nome))
        {
            return p->musica;
        }
        p = p->prox;
    }

    return NULL;
}

int ehVaziaListaMusica(ListaDeMusica *lista)
{
    if (lista->prim == NULL)
    {
        return 1;
    }
    return 0;
}

Musica *retornaProxMusica(ListaDeMusica *lista, Musica *musica)
{
    if (musica == lista->ult->musica)
        return NULL;

    CelulaMusica *p = lista->prim;
    while (p != NULL)
    {
        if (ehIgualMusica(p->musica, musica))
        {
            return p->prox->musica;
        }
        p = p->prox;
    }
    return NULL;
}

Musica *retornaPrimMusica(ListaDeMusica *lista) { return lista->prim->musica; }

CelulaMusica *retornaPrimListaDeMusica(ListaDeMusica *lista)
{
    if (!lista)
        return NULL;

    return lista->prim;
}

CelulaMusica *retornaProxListaDeMusica(CelulaMusica *celula)
{
    if (!celula)
        return NULL;

    return celula->prox;
}

Musica *retornaMusicaCelula(CelulaMusica *celula)
{
    if (!celula)
        return NULL;

    return celula->musica;
}

void destroiMusica(Musica *musica)
{
    if (!musica)
        return;

    free(musica->nome);
    free(musica->artista);
    free(musica);
}

void destroiListaDeMusica(ListaDeMusica *lista)
{
    if (!lista)
        return;

    CelulaMusica *p = lista->prim;
    CelulaMusica *t;

    while (p != NULL)
    {
        t = p->prox;
        free(p);
        p = t;
    }

    free(lista);
}

void destroiListaEMusicas(ListaDeMusica *lista)
{
    if (!lista)
        return;

    CelulaMusica *p = lista->prim;
    CelulaMusica *t;

    while (p != NULL)
    {
        t = p->prox;
        destroiMusica(p->musica);
        free(p);
        p = t;
    }

    free(lista);
}
