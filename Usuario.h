#ifndef _USUARIO_H_
#define _USUARIO_H_

#include "Playlist.h"
#include <stdio.h>

/**
 * @brief Struct que representa um usuário.
 */
typedef struct Usuario Usuario;

/**
 * @brief Struct que representa uma célula de uma lista de usuários.
 */
typedef struct CelulaUsuario CelulaUsuario;

/**
 * @brief Struct que representa uma lista de usuários.
 */
typedef struct ListaDeUsuario ListaDeUsuario;

/**
 * @brief Cria um novo usuário com o nome fornecido.
 *
 * @param nome O nome do usuário.
 * @return Um ponteiro para o usuário criado.
 */
Usuario *criaUsuario(char *nome);

/**
 * @brief Atribui a lista de playlists de um usuário.
 *
 * @param usuario O usuário.
 * @param listaDePlaylist A lista de playlists.
 */
void atribuiListaDePlaylist(Usuario *usuario, ListaDePlaylist *listaDePlaylist);

/**
 * @brief Retorna a lista de playlists de um usuário.
 *
 * @param usuario O usuário.
 * @return A lista de playlists.
 */
ListaDePlaylist *retornaListaPlaylistUsuario(Usuario *usuario);

/**
 * @brief Atribui a quantidade de playlists de um usuário.
 *
 * @param usuario O usuário.
 * @param qtdPlaylists A quantidade de playlists.
 */
void atribuiQtdPlaylistsUsuario(Usuario *usuario, int qtdPlaylists);

/**
 * @brief Cria uma nova lista vazia de usuários.
 *
 * @return Um ponteiro para a lista de usuários criada.
 */
ListaDeUsuario *criaListaDeUsuario();

/**
 * @brief Insere um usuário na lista de amigo de outro usuário e vice-versa.
 *
 * @param usuario O usuário a ser inserido.
 * @param amigo O amigo a ser inserido.
 */
void adicionaAmigo(Usuario *usuario, Usuario *amigo);

/**
 * @brief Insere um usuário na lista.
 *
 * @param lista A lista de usuários.
 * @param usuario O usuário a ser inserido.
 */
void insereUsuario(ListaDeUsuario *lista, Usuario *usuario);

/**
 * @brief Retorna o nome de um usuário.
 *
 * @param usuario O usuário.
 * @return O nome do usuário.
 */
char *retornaNomeUsuario(Usuario *usuario);

/**
 * @brief Busca um usuário na lista de usuários.
 *
 * @param lista A lista de usuários.
 * @param nome O nome do usuário a ser buscado.
 * @return O usuário encontrado.
 */
Usuario *buscaUsuarioPorNome(ListaDeUsuario *lista, char *nome);

/**
 * @brief Imprime um usuário no arquivo.
 *
 * @param usuario O usuário.
 * @param arquivo O arquivo de saída.
 */
void imprimeUsuarioArquivo(Usuario *usuario, FILE *arquivo);

/**
 * @brief Verifica se um usuário é igual a outro.
 *
 * @param usuario1 O primeiro usuário.
 * @param usuario2 O segundo usuário.
 * @return 1 se os usuários são iguais, 0 caso contrário.
 */
int ehIgualPonteiroUsuario(Usuario *usuario1, Usuario *usuario2);

/**
 * @brief Retorna o primeiro usuário da lista.
 *
 * @param lista A lista de usuários.
 * @return O primeiro usuário da lista.
 */
Usuario *retornaPrimUsuario(ListaDeUsuario *lista);

/**
 * @brief Retorna o próximo usuário da lista.
 *
 * @param lista A lista de usuários.
 * @param usuario O usuário atual.
 * @return O próximo usuário da lista.
 */
Usuario *retornaProxUsuario(ListaDeUsuario *lista, Usuario *usuario);

/**
 * @brief Verifica se a lista de playlists de um usuário é vazia.
 *
 * @param usuario O usuário.
 * @return 1 se a lista de playlists é vazia, 0 caso contrário.
 */
int ehVaziaListaPlaylistUsuario(Usuario *usuario);

/**
 * @brief Atribui uma lista de playlists a um usuário.
 *
 * @param usuario O usuário.
 * @param lista A lista de playlists.
 */
void insereListaPlaylistUsuario(Usuario *usuario, ListaDePlaylist *lista);

/**
 * @brief Retorna a lista de amigos de um usuário.
 *
 * @param usuario O usuário.
 * @return A lista de amigos.
 */
ListaDeUsuario *retornaListaAmigosUsuario(Usuario *user);

/**
 * @brief Torna verdadeira a flag similaridade do usuário.
 *
 * @param user O usuário.
 */
void atribuiSimilaridadeAoUsuario(Usuario *user);

/**
 * @brief Retorna a flag similaridade do usuário.
 *
 * @param user O usuário.
 * @return A flag similaridade.
 */
int retornaSimilaridadeUsuario(Usuario *user);

/**
 * @brief Destroi a lista de amigos de um usuário.
 *
 * @param user O usuário.
 */
void destroiListaDeAmigos(Usuario *usuario);

/**
 * @brief Destroi um usuário.
 *
 * @param usuario O usuário.
 */
void destroiUsuario(Usuario *usuario);

/**
 * @brief Destroi a lista de usuários.
 *
 * @param lista A lista de usuários.
 */
void destroiListaDeUsuario(ListaDeUsuario *lista);

/**
 * @brief Destroi a lista de usuários e os usuários.
 *
 * @param lista A lista de usuários.
 */
void destroiListaEUsuarios(ListaDeUsuario *lista);

#endif
