#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include "Musica.h"
#include <stdio.h>

/**
 * @brief Struct que representa uma playlist.
 */
typedef struct Playlist Playlist;

/**
 * @brief Struct que representa uma célula de uma lista de playlists.
 */
typedef struct CelulaPlaylist CelulaPlaylist;

/**
 * @brief Struct que representa uma lista de playlists.
 */
typedef struct ListaDePlaylist ListaDePlaylist;

/**
 * @brief Cria uma nova playlist com o nome fornecido.
 *
 * @param nome O nome da playlist.
 * @return Um ponteiro para a playlist criada.
 */
Playlist *criaPlaylist(char *nome);

/**
 * @brief Cria uma nova lista vazia de playlists.
 *
 * @return Um ponteiro para a lista de playlists criada.
 */
ListaDePlaylist *criaListaDePlaylist();

/**
 * @brief Insere uma playlist na lista.
 *
 * @param lista A lista de playlists.
 * @param playlist A playlist a ser inserida.
 */
void inserePlaylistNaLista(ListaDePlaylist *lista, Playlist *playlist);

/**
 * @brief Remove uma playlist da lista.
 *
 * @param lista A lista de playlists.
 * @param playlist A playlist a ser removida.
 */
void retiraPlaylistDaLista(ListaDePlaylist *lista, Playlist *playlist);

/**
 * @brief Insere uma música na playlist.
 *
 * @param playlist A playlist.
 * @param musica A música a ser inserida.
 */
void insereMusicaNaPlaylist(Playlist *playlist, Musica *musica);

/**
 * @brief Remove uma música da playlist.
 *
 * @param playlist A playlist.
 * @param musica A música a ser removida.
 */
void retiraMusicaDaPlaylist(Playlist *playlist, Musica *musica);

/**
 * @brief Retorna o nome da playlist.
 *
 * @param playlist A playlist.
 * @return O nome da playlist.
 */
char *retornaNomePlaylist(Playlist *playlist);

/**
 * @brief Retorna a lista de músicas da playlist.
 *
 * @param playlist A playlist.
 * @return A lista de músicas da playlist.
 */
ListaDeMusica *retornaListaMusica(Playlist *playlist);

/**
 * @brief Busca uma playlist na lista pelo nome.
 *
 * @param lista A lista de playlists.
 * @param nome O nome da playlist a ser buscada.
 * @return A playlist encontrada, ou NULL se não existir.
 */
Playlist *buscaPlaylistPorNome(ListaDePlaylist *lista, char *nome);

/**
 * @brief verifica se o nome da playlist é igual ao nome fornecido.
 *
 * @param playlist A playlist.
 */
int ehNomePlaylist(Playlist *playlist1, char *nome);

/**
 * @brief Imprime a playlist no arquivo fornecido.
 *
 * @param playlist A playlist.
 * @param arquivo O arquivo onde a playlist será impressa.
 */
void imprimePlaylistArquivo(Playlist *playlist, FILE *arquivo);

/**
 * @brief Imprime as músicas da playlist no arquivo fornecido.
 *
 * @param playlist A playlist.
 * @param arquivo O arquivo onde as músicas serão impressas.
 */
void imprimeMusicasArquivoPlaylist(Playlist *playlist, FILE *arquivo);

/**
 * @brief Imprime a lista de playlists no arquivo fornecido.
 *
 * @param playlist A playlist.
 * @param arquivo O arquivo onde as playlists serão impressas.
 */
void imprimeListaDePlaylistArquivo(ListaDePlaylist *lista, FILE *arquivo);

/**
 * @brief Retorna a primeira playlist da lista.
 *
 * @param lista A lista de playlists.
 * @return A primeira playlist, ou NULL se a lista estiver vazia.
 */
Playlist *retornaPrimPlaylist(ListaDePlaylist *lista);

/**
 * @brief Retorna a próxima playlist na lista.
 *
 * @param lista A lista de playlists.
 * @param playlist A playlist atual.
 * @return A próxima playlist, ou NULL se a playlist atual for a última.
 */
Playlist *retornaProxPlaylist(ListaDePlaylist *lista, Playlist *playlist);

/**
 * @brief Retorna a primeira música da playlist.
 *
 * @param playlist A playlist.
 * @return A primeira música, ou NULL se a playlist estiver vazia.
 */
Musica *retornaPrimMusicaPlaylist(Playlist *playlist);

/**
 * @brief Retorna a próxima música na playlist.
 *
 * @param playlist A playlist.
 * @param musica A música atual.
 * @return A próxima música, ou NULL se a música atual for a última.
 */
Musica *retornaProxMusicaPlaylist(Playlist *playlist, Musica *musica);

/**
 * @brief Busca uma música na playlist pelo nome.
 *
 * @param playlist A playlist.
 * @param nome O nome da música a ser buscada.
 * @return A música encontrada, ou NULL se não existir.
 */
Musica *buscaMusicaNaListaPlaylist(ListaDePlaylist *lista, Musica *musica);

/**
 * @brief Verifica se a playlist fornecida é vazia.
 *
 * @param playlist A playlist.
 * @return 1 se a playlist está vazia, 0 caso contrário.
 */
int ehVaziaPlaylist(Playlist *playlist);

/**
 * @brief Verifica se a playlist fornecida é a última da lista.
 *
 * @param lista A lista de playlists.
 * @param p A playlist.
 * @return 1 se a playlist é a última, 0 caso contrário.
 */
int ehUltimaPlaylist(ListaDePlaylist *lista, Playlist *p);

/**
 * @brief Verifica se a lista de playlists está vazia.
 *
 * @param lista A lista de playlists.
 * @return 1 se a lista está vazia, 0 caso contrário.
 */
int ehVaziaListaPlaylist(ListaDePlaylist *lista);

/**
 * @brief Verifica se as playlists fornecidas são iguais.
 *
 * @param playlist1 A primeira playlist.
 * @param playlist2 A segunda playlist.
 * @return 1 se as playlists são iguais, 0 caso contrário.
 */
int ehIgualPonteiroPlaylist(Playlist *playlist1, Playlist *playlist2);

/**
 * @brief Destroi a playlist fornecida.
 *
 * @param playlist A playlist.
 */
void destroiPlaylist(Playlist *playlist);

/**
 * @brief Destroi a lista de playlists fornecida.
 *
 * @param lista A lista de playlists.
 */
void destroiListaDePlaylist(ListaDePlaylist *lista);

/**
 * @brief Destroi a lista de playlists e as playlists fornecidas.
 *
 * @param lista A lista de playlists.
 */
void destroiListaEPlaylists(ListaDePlaylist *lista);

#endif
