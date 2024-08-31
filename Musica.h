#ifndef _MUSICA_H
#define _MUSICA_H

#include <stdio.h>

/**
 * @brief Struct que representa uma música.
 */
typedef struct Musica Musica;

/**
 * @brief Struct que representa uma célula de uma lista de músicas.
 */
typedef struct CelulaMusica CelulaMusica;

/**
 * @brief Struct que representa uma lista de músicas.
 */
typedef struct ListaDeMusica ListaDeMusica;

/**
 * @brief Cria uma nova música com o nome e artista fornecidos.
 *
 * @param nome O nome da música.
 * @param artista O artista da música.
 * @return Um ponteiro para a música criada.
 */
Musica *criaMusica(char *nome, char *artista);

/**
 * @brief Cria uma nova lista vazia de músicas.
 *
 * @return Um ponteiro para a lista de músicas criada.
 */
ListaDeMusica *criaListaDeMusica();

/**
 * @brief Insere uma música na lista.
 *
 * @param lista A lista de músicas.
 * @param musica A música a ser inserida.
 */
void insereMusica(ListaDeMusica *lista, Musica *musica);

/**
 * @brief Remove uma música da lista.
 *
 * @param lista A lista de músicas.
 * @param musica A música a ser removida.
 */
void retiraMusica(ListaDeMusica *lista, Musica *musica);

/**
 * @brief Retorna o nome da música.
 *
 * @param musica A música.
 * @return O nome da música.
 */
char *retornaNomeMusica(Musica *musica);

/**
 * @brief Retorna o artista da música.
 *
 * @param musica A música.
 * @return O artista da música.
 */
char *retornaArtistaMusica(Musica *musica);

/**
 * @brief Verifica se uma música está na lista.
 *
 * @param lista A lista de músicas.
 * @param musica A música a ser verificada.
 * @return 1 se a música está na lista, 0 caso contrário.
 */
int estaNaListaMusica(ListaDeMusica *lista, Musica *musica);

/**
 * @brief Verifica se dois artistas são iguais.
 *
 * @param artista1 O primeiro artista.
 * @param artista2 O segundo artista.
 * @return 1 se os artistas são iguais, 0 caso contrário.
 */
int ehIgualArtista(char *artista1, char *artista2);

/**
 * @brief Verifica se dois nomes são iguais.
 *
 * @param nome1 O primeiro nome.
 * @param nome2 O segundo nome.
 * @return 1 se os nomes são iguais, 0 caso contrário.
 */
int ehIgualNome(char *nome1, char *nome2);

/**
 * @brief Verifica se duas músicas são iguais.
 *
 * @param musica1 A primeira música.
 * @param musica2 A segunda música.
 * @return 1 se as músicas são iguais, 0 caso contrário.
 */
int ehIgualMusica(Musica *musica1, Musica *musica2);

/**
 * @brief Verifica se dois ponteiros de música são iguais.
 *
 * @param musica1 O primeiro ponteiro de música.
 * @param musica2 O segundo ponteiro de música.
 * @return 1 se os ponteiros de música são iguais, 0 caso contrário.
 */
int ehIgualPonteiroMusica(Musica *musica1, Musica *musica2);

/**
 * @brief Procura uma música pelo artista na lista.
 *
 * @param lista A lista de músicas.
 * @param artista O artista a ser procurado.
 * @return Um ponteiro para a música encontrada, ou NULL se não encontrada.
 */
Musica *buscaMusicaPorArtista(ListaDeMusica *lista, char *artista);

/**
 * @brief Procura uma música pelo nome na lista.
 *
 * @param lista A lista de músicas.
 * @param nome O nome a ser procurado.
 * @return Um ponteiro para a música encontrada, ou NULL se não encontrada.
 */
Musica *buscaMusicaPorNome(ListaDeMusica *lista, char *nome);

/**
 * @brief Verifica se a lista de músicas está vazia.
 *
 * @param lista A lista de músicas.
 * @return 1 se a lista está vazia, 0 caso contrário.
 */
int ehVaziaListaMusica(ListaDeMusica *lista);

/**
 * @brief Retorna a próxima música na lista.
 *
 * @param lista A lista de músicas.
 * @param musica A música atual.
 * @return Um ponteiro para a próxima música, ou NULL se a música atual for a última.
 */
Musica *retornaProxMusica(ListaDeMusica *lista, Musica *musica);

/**
 * @brief Retorna a primeira música na lista.
 *
 * @param lista A lista de músicas.
 * @return Um ponteiro para a primeira música, ou NULL se a lista estiver vazia.
 */
Musica *retornaPrimMusica(ListaDeMusica *lista);

/**
 * @brief Retorna a primeira célula da lista de músicas.
 *
 * @param lista A lista de músicas.
 * @return Um ponteiro para a primeira célula, ou NULL se a lista estiver vazia.
 */
CelulaMusica *retornaPrimListaDeMusica(ListaDeMusica *lista);

/**
 * @brief Retorna a próxima célula na lista de músicas.
 *
 * @param celula A célula atual.
 * @return Um ponteiro para a próxima célula, ou NULL se a célula atual for a última.
 */
CelulaMusica *retornaProxListaDeMusica(CelulaMusica *celula);

/**
 * @brief Retorna a música armazenada na célula.
 *
 * @param celula A célula.
 * @return Um ponteiro para a música armazenada na célula.
 */
Musica *retornaMusicaCelula(CelulaMusica *celula);

/**
 * @brief Destroi uma música.
 *
 * @param musica A música a ser destruída.
 */
void destroiMusica(Musica *musica);

/**
 * @brief Destroi uma lista de músicas.
 *
 * @param lista A lista de músicas a ser destruída.
 */
void destroiListaDeMusica(ListaDeMusica *lista);

/**
 * @brief Destroi uma lista de músicas e todas as suas músicas.
 *
 * @param lista A lista de músicas a ser destruída.
 */
void destroiListaEMusicas(ListaDeMusica *lista);

#endif