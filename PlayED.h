#ifndef _PLAYED_H_
#define _PLAYED_H_

#include "Playlist.h"
#include "Usuario.h"

/**
 * @brief Struct que representa o PlayED.
 */
typedef struct PlayED PlayED;

/**
 * @brief Retorna a lista de usuários do PlayED.
 *
 * @param played O PlayED.
 * @return A lista de usuários.
 */
ListaDeUsuario *retornaListaUsuario(PlayED *played);

/**
 * @brief Retorna a lista de playlists do PlayED.
 *
 * @param played O PlayED.
 * @return A lista de playlists.
 */
ListaDePlaylist *retornaListaPlaylists(PlayED *played);

/**
 * @brief Retorna a lista de músicas do PlayED.
 *
 * @param played O PlayED.
 * @return A lista de músicas.
 */
ListaDeMusica *retornaListaMusicas(PlayED *played);

/**
 * @brief Cria um novo PlayED com o caminho da pasta de entrada.
 *
 * @param caminhoPastaEntrada O caminho da pasta de entrada.
 * @return Um ponteiro para o PlayED criado.
 */
PlayED *criaPlayED(char *caminhoPastaEntrada);

/**
 * @brief Lê a lista de usuários do PlayED no arquivo amizade.txt.
 *
 * @param caminhoPastaEntrada O caminho da pasta de entrada.
 * @return A lista de usuários.
 */
ListaDeUsuario *leListaDeUsuario(char *caminhoPastaEntrada);

/**
 * @brief Lê a divisão de playlists no arquivo playlists.txt, busca os arquivos de playlist por nome, cria as playlists e suas músicas.
 * Insere as playlists nos seus respectivos usuários e no lista de playlists do PlayED.
 *
 * @param caminhoPastaEntrada O caminho da pasta de entrada.
 * @param played O PlayED.
 * @return A lista de playlists.
 */
void *lePlaylistsUsuarios(char *caminhoPastaEntrada, PlayED *played);

/**
 * @brief Separa as músicas em playlists de acordo com o artista.
 * Cria uma nova playlist para cada artista e destroi as playlists original.
 *
 * @param played O PlayED.
 */
void refatoraPlayED(PlayED *played);

/**
 * @brief Imprime o arquivo played-refatorado.txt com a lista de usuários e suas playlists refatoradas.
 * Imprime também a pasta Saida com pastas para cada usuário contendo suas playlists refatoradas.
 *
 * @param played O PlayED.
 * @param caminhoPastaSaida O caminho da pasta de saída.
 */
void imprimePlayEDRefatorada(PlayED *played, char *caminhoPastaSaida);

/**
 * @brief Imprime o arquivo similaridades.txt com as similaridades entre os usuários amigos.
 *
 * @param played O PlayED.
 * @param caminhoPastaSaida O caminho da pasta de saída.
 */
void imprimeSimilaridades(PlayED *played, char *caminhoPastaSaida);

/**
 * @brief Para cada playlist de cada usuário busca playlists do mesmo artista em seus amigos.
 * Caso seja encontrada uma playlist do mesmo artista, as musicas que não estão na playlist original sao adicionadas.
 *
 * @param played O PlayED.
 */
void mergePlayED(PlayED *played);

/**
 * @brief Imprime a pasta Merge com pastas para cada usuário contendo suas playlists após o Merge.
 *
 * @param played O PlayED.
 */
void imprimePlayEDMerged(PlayED *played);

/**
 * @brief Libera a memória alocada para o PlayED, destruindo suas listas e seus conteúdos.
 *
 * @param played O PlayED.
 */
void liberaPlayED(PlayED *played);

#endif
