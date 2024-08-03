#include "PlayED.h"
#include "Musica.h"
#include "Playlist.h"
#include "Usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME_CAMINHO 300

struct PlayED {
  ListaDeUsuario *usuarios;
  ListaDePlaylist *playlists;
  ListaDeMusica *musicas;
};

ListaDeUsuario *retornaListaUsuario(PlayED *played) { return played->usuarios; }

ListaDePlaylist *retornaListaPlaylists(PlayED *played) {
  return played->playlists;
}

ListaDeMusica *retornaListaMusicas(PlayED *played) { return played->musicas; }

PlayED *criaPlayED(char *caminhoPastaEntrada) {
  PlayED *played = (PlayED *)malloc(sizeof(PlayED));
  played->usuarios = leListaDeUsuario(caminhoPastaEntrada);
  played->musicas = criaListaDeMusica();
  played->playlists = criaListaDePlaylist();
  lePlaylistsUsuarios(caminhoPastaEntrada, played);

  return played;
}

// essa função cria a lista de Usuario e le o documento, assinalando o nome de
// cada usuario dentro do played
ListaDeUsuario *leListaDeUsuario(char *caminhoPastaEntrada) {
  char *docAmizade = "amizade.txt";
  char caminhoAmizade[TAM_NOME_CAMINHO];

  snprintf(caminhoAmizade, sizeof(caminhoAmizade), "%s/%s", caminhoPastaEntrada,
           docAmizade);

  FILE *arquivoAmizade = fopen(caminhoAmizade, "r");

  if (!arquivoAmizade) {
    printf("Erro ao abrir o arquivo %s\n", caminhoAmizade);
    return NULL;
  }

  ListaDeUsuario *usuarios = criaListaDeUsuario();

  char nome[100];
  char amigo[100];
  char aux;

  // na primeira linha do arquivo de amizades, enquanto o caracter auxiliar for
  // ';' continua colocando os usuarios na lista
  do {
    fscanf(arquivoAmizade, "%[^;\n]%c", nome, &aux);
    insereUsuario(usuarios, criaUsuario(nome));
  } while (aux == ';');

  // atribuir as amizades dos usuarios que foram colocados na lista
  while (!feof(arquivoAmizade)) {
    fscanf(arquivoAmizade, "%[^;\n];%[^\n]%*c", nome, amigo);
    adicionaAmigo(buscaUsuarioPorNome(usuarios, nome),
                  buscaUsuarioPorNome(usuarios, amigo));
  }

  fclose(arquivoAmizade);

  return usuarios;
}

void *lePlaylistsUsuarios(char *caminhoPastaEntrada, PlayED *played) {
  char *docPlaylist = "playlists.txt";
  char caminhoPlaylist[TAM_NOME_CAMINHO];

  snprintf(caminhoPlaylist, sizeof(caminhoPlaylist), "%s/%s",
           caminhoPastaEntrada, docPlaylist);
  FILE *arquivoPlaylist = fopen(caminhoPlaylist, "r");

  if (!arquivoPlaylist) {
    printf("Erro ao abrir o arquivo %s\n", caminhoPlaylist);
    return NULL;
  }

  char nome[100];
  char nomePlaylist[100];
  char aux = ';';
  int qtdPlaylists;

  // le o arquivo de playlist e vai fazendo atribuição linha a linha
  while (!feof(arquivoPlaylist)) {

    // le cada a linha do arquivo e atribuir as playlists p/ cada usuario
    fscanf(arquivoPlaylist, "%[a-zA-Z]%*c%d%c", nome, &qtdPlaylists, &aux);

    Usuario *user = buscaUsuarioPorNome(played->usuarios, nome);
    atribuiQtdPlaylistsUsuario(user, qtdPlaylists);

    // le nome da playlist, cria ela e adiciona na lista de playlist do
    // usuario
    for (int i = 0; i < qtdPlaylists; i++) {
      fscanf(arquivoPlaylist, "%[^.].txt%*c", nomePlaylist);
      Playlist *playlist = criaPlaylist(nomePlaylist);

      // abre o arquivo de cada playlist e insere cada musica;

      char *docMusicas = nomePlaylist;
      char caminhoMusicas[TAM_NOME_CAMINHO];
      snprintf(caminhoMusicas, sizeof(caminhoMusicas), "%s/%s.txt",
               caminhoPastaEntrada, docMusicas);

      FILE *arquivoMusicas = fopen(caminhoMusicas, "r");

      while (!feof(arquivoMusicas)) {

        char nomeMusica[100] = "\n";
        char nomeArtista[100] = "\n";
        char musicaToda[100] = "\n";

        fscanf(arquivoMusicas, "%[^\n]%*c", musicaToda);
        int i = 0, j = 0, entrouNome = 0;
        for (int j = 0; j < strlen(musicaToda); j++) {

          if (!entrouNome && musicaToda[j] == ' ' && musicaToda[j + 1] == '-' &&
              musicaToda[j + 2] == ' ') {
            entrouNome = 1;
            j = j + 2;
          } else {
            if (entrouNome) {
              nomeMusica[i] = musicaToda[j];
              i++;
            } else
              nomeArtista[j] = musicaToda[j];
          }
        }

        Musica *musica = criaMusica(nomeMusica, nomeArtista);
        insereMusicaNaPlaylist(playlist, musica);
        insereMusica(played->musicas, musica);
      }
      fclose(arquivoMusicas);

      inserePlaylistNaLista(retornaListaPlaylistUsuario(user), playlist);
      inserePlaylistNaLista(played->playlists, playlist);
    }
  }
  fclose(arquivoPlaylist);
}

void liberaPlayED(PlayED *played) {
  destroiListaEMusicas(retornaListaMusicas(played));
  destroiListaEPlaylists(retornaListaPlaylists(played));
  destroiListaEUsuarios(retornaListaUsuario(played));
  free(played);
}

/*Comentário pra guiar o programa:
Esquema de refatoração:
- Pega a primeira pessoa da lista de usuários
    - Pega a primeira playlist dessa pessoa
        - Pega a primeira música da playlist
        - Ve se tem uma playlist já com o nome do artista
          - Se nao tiver, cria a playlist
        - Coloca a música na playlist
        - Retira a música da playlist antiga
    - Repete o processo até a playlist estar vazia
        - Se estiver vazia, destroi a playlist
    - Passa pra proxima playlist
    - Repete o processo até a lista de playlists da pessoa estar vazia
    - Insere a Nova Lista de Playlists na pessoa
- Passa pra proxima pessoa da lista de usuários

funções auxiliares que criei/modifiquei pra ajudar no problema:

MUSICA.C:
- ehVaziaListaPlaylist(ListaDePlaylist *lista)
- retornaProxMusica(ListaDeMusica *lista, Musica *musica)
- retornaPrimMusica(ListaDeMusica *lista)

PLAYLIST.C:
- ehVaziaPlaylist(Playlist* playlist)
- ehVaziaListaPlaylist(ListaDePlaylist* lista)
- retornaPrimMusicaPlaylist(Playlist* playlist)
- retornaProxMusicaPlaylist(Playlist *playlist, Musica *musica)
- ehPlaylistDoArtista(Playlist *playlist, Musica* musica)
- retornaProxPlaylist(ListaDePlaylist *lista, Playlist *playlist)
- retornaPrimPlaylist(ListaDePlaylist *lista)
- buscaPlaylistPorNome(ListaDePlaylist *lista, char *nome)

USUARIO.C:
- retornaPrimUsuario(ListaDeUsuario *lista)
- retornaProxUsuario(ListaDeUsuario *lista, Usuario *usuario)
- ehVaziaListaPlaylistUsuario(Usuario* usuario)
*/

void refatoraPlayED(PlayED *played) {
  Usuario *user = retornaPrimUsuario(played->usuarios);

  // varre a lista de usuarios ate o final
  while (user != NULL) {
    ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);

    // essa nova lista de playlists é organizada por artistas
    ListaDePlaylist *novaListaPlaylist = criaListaDePlaylist();

    // coloca as musicas na playlist nova e tira da antiga ate esvaziar
    while (!ehVaziaListaPlaylistUsuario(user)) {
      Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

      while (!ehVaziaPlaylist(playlist)) {

        Musica *musica = retornaPrimMusicaPlaylist(playlist);
        Playlist *playlistDoArtista = buscaPlaylistPorNome(
            novaListaPlaylist, retornaArtistaMusica(musica));

        // se nao existir uma playlist com o nome do artista vai criar uma nova
        // e colocar na lista nova
        if (playlistDoArtista == NULL) {
          playlistDoArtista = criaPlaylist(retornaArtistaMusica(musica));
          inserePlaylistNaLista(novaListaPlaylist, playlistDoArtista);
          inserePlaylistNaLista(played->playlists, playlistDoArtista);
        }

        insereMusicaNaPlaylist(playlistDoArtista, musica);
        retiraMusicaDaPlaylist(playlist, musica);
      }
      // quando a playlist for vazia tem que retirar da lista de playlist e
      // destruir
      retiraPlaylistDaLista(listaPlaylist, playlist);
      retiraPlaylistDaLista(played->playlists, playlist);
      destroiPlaylist(playlist);
    }

    // quando a lista de playlist do usuario for vazia, bota a nova lista de
    // playlist refatorada no usuario
    destroiListaDePlaylist(listaPlaylist);
    insereListaPlaylistUsuario(user, novaListaPlaylist);
    user = retornaProxUsuario(played->usuarios, user);
  }
}

void imprimePlayEDRefatorada(PlayED *played, char *caminhoPastaSaida) {
  char *docRefatora = "played-refatorada.txt";
  char caminhoRefatora[TAM_NOME_CAMINHO];
  char caminhoPastaUsuario[TAM_NOME_CAMINHO];
  char *nomePlaylist = NULL;
  char caminhoPlaylist[TAM_NOME_CAMINHO];

  snprintf(caminhoRefatora, sizeof(caminhoRefatora), "%s/%s", caminhoPastaSaida,
           docRefatora);

  FILE *arquivoRefatora = fopen(caminhoRefatora, "w");

  if (!arquivoRefatora) {
    printf("Erro ao abrir o arquivo %s\n", caminhoRefatora);
    return;
  }

  Usuario *user = retornaPrimUsuario(played->usuarios);
,
  // varre a lista de usuarios ate o final
  while (user != NULL) {
    imprimeUsuarioArquivo(user, arquivoRefatora);

    snprintf(caminhoPastaUsuario, sizeof(caminhoPastaUsuario), "%s/%s",
             caminhoPastaSaida, retornaNomeUsuario(user));

    mkdir(caminhoPastaUsuario, 0700);

    ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
    Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

    // Gera o arquivo das playlists dentro da pasta
    while (playlist != NULL) {
      nomePlaylist = retornaNomePlaylist(playlist);

      snprintf(caminhoPlaylist, sizeof(caminhoPlaylist), "%s/%s.txt",
               caminhoPastaUsuario, nomePlaylist);

      FILE *arquivoPlaylist = fopen(caminhoPlaylist, "w");

      if (!arquivoPlaylist) {
        printf("Erro ao abrir o arquivo %s\n", caminhoPlaylist);
        return;
      }

      imprimeMusicasArquivoPlaylist(playlist, arquivoPlaylist);

      fclose(arquivoPlaylist);

      playlist = retornaProxPlaylist(listaPlaylist, playlist);
    }

    user = retornaProxUsuario(played->usuarios, user);
  }

  fclose(arquivoRefatora);
}

void imprimeSimilaridades(PlayED *played, char *caminhoPastaSaida) {
  char *docSimilaridades = "similaridades.txt";
  char caminhoSimilaridades[TAM_NOME_CAMINHO];

  snprintf(caminhoSimilaridades, sizeof(caminhoSimilaridades), "%s/%s",
           caminhoPastaSaida, docSimilaridades);

  FILE *arquivoSimilaridades = fopen(caminhoSimilaridades, "w");
  if (!arquivoSimilaridades) {
    printf("Erro ao abrir o arquivo %s\n", caminhoSimilaridades);
  }

  Usuario *user = retornaPrimUsuario(played->usuarios);

  // pega o primeiro usuario da lista de amigos
  while (user != NULL) {
    // pra cada usuario varre a lista de amigos dele
    Usuario *amigo = retornaPrimUsuario(retornaListaAmigosUsuario(user));
    int similaridades = 0;

    // ve se o amigo ja passou no loop, se sim ele pula essa etapa

    while (amigo != NULL) {
      if (!retornaSimilaridadeUsuario(amigo)) {
        // vai olhar todas as musicas da playlist do usuario e ver se o amigo
        // tem uma igual
        ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
        Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

        while (playlist != NULL) {
          Musica *musica = retornaPrimMusicaPlaylist(playlist);

          while (musica != NULL) {
            ListaDePlaylist *listaPlaylistAmigo =
                retornaListaPlaylistUsuario(amigo);
            if (buscaMusicaNaListaPlaylist(listaPlaylistAmigo, musica) !=
                NULL) {
              similaridades++;
            }

            musica = retornaProxMusicaPlaylist(playlist, musica);
          }

          playlist = retornaProxPlaylist(listaPlaylist, playlist);
        }

        fprintf(arquivoSimilaridades, "%s;%s;%d\n", retornaNomeUsuario(user),
                retornaNomeUsuario(amigo), similaridades);
      }

      similaridades = 0;
      amigo = retornaProxUsuario(retornaListaAmigosUsuario(user), amigo);
    }
    atribuiSimilaridadeAoUsuario(user);
    user = retornaProxUsuario(played->usuarios, user);
  }

  fclose(arquivoSimilaridades);
}

void mergePlayED(PlayED *played) {
  Usuario *user = retornaPrimUsuario(played->usuarios);

  // pega o primeiro usuario da lista de amigos
  while (user != NULL) {
    // pra cada usuario varre a lista de amigos dele
    ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
    Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

    // DEBUG
    printf("USUARIO %s\n", retornaNomeUsuario(user));

    while (playlist != NULL) {
      Usuario *amigo = retornaPrimUsuario(retornaListaAmigosUsuario(user));

      // DEBUG
      printf("CHEGOU PLAYLIST %s\n", retornaNomePlaylist(playlist));

      while (amigo != NULL) {

        // DEBUG
        printf("CHEGOU AMIGO %s\n", retornaNomeUsuario(amigo));
        ListaDePlaylist *listaPlaylistAmigo =
            retornaListaPlaylistUsuario(amigo);
        Playlist *playlistAmigo = buscaPlaylistPorNome(
            listaPlaylistAmigo, retornaNomePlaylist(playlist));
        ListaDeMusica *novasMusicas;

        if (playlistAmigo) {
          printf("TEM IGUAL\n");
          Musica *musicaAmigo = retornaPrimMusicaPlaylist(playlistAmigo);
          while (musicaAmigo != NULL) {
            printf("MUSICA %s\n", retornaNomeMusica(musicaAmigo));

            if (!estaNaListaMusica(retornaListaMusica(playlist), musicaAmigo)) {
              printf("ENTRA NA LISTA\n");
              insereMusicaNaPlaylist(playlist, musicaAmigo);
            }
            musicaAmigo = retornaProxMusicaPlaylist(playlistAmigo, musicaAmigo);
          }
        } else {
          printf("NAO TEM IGUAL\n");
        }

        amigo = retornaProxUsuario(retornaListaAmigosUsuario(user), amigo);
      }

      if (ehUltimaPlaylist(listaPlaylist, playlist)) {
        printf("CHEGOU PLAYLIST %s\n", retornaNomePlaylist(playlist));
      }
      playlist = retornaProxPlaylist(listaPlaylist, playlist);
    }

    // DEBUG
    printf("TERMINOU USER\n");
    user = retornaProxUsuario(played->usuarios, user);
  }
}

void imprimePlayEDMerged(PlayED *played) {

  char caminhoPastaUsuario[TAM_NOME_CAMINHO];
  char *nomePlaylist = NULL;
  char caminhoPlaylist[TAM_NOME_CAMINHO];

  Usuario *user = retornaPrimUsuario(played->usuarios);

  // varre a lista de usuarios ate o final
  while (user != NULL) {

    snprintf(caminhoPastaUsuario, sizeof(caminhoPastaUsuario), "Merge/%s",
             retornaNomeUsuario(user));

    mkdir(caminhoPastaUsuario, 0700);

    ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
    Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

    // Gera o arquivo das playlists dentro da pasta
    while (playlist != NULL) {
      nomePlaylist = retornaNomePlaylist(playlist);

      snprintf(caminhoPlaylist, sizeof(caminhoPlaylist), "%s/%s.txt",
               caminhoPastaUsuario, nomePlaylist);

      FILE *arquivoPlaylist = fopen(caminhoPlaylist, "w");

      if (!arquivoPlaylist) {
        printf("Erro ao abrir o arquivo %s\n", caminhoPlaylist);
        return;
      }

      imprimeMusicasArquivoPlaylist(playlist, arquivoPlaylist);

      fclose(arquivoPlaylist);

      playlist = retornaProxPlaylist(listaPlaylist, playlist);
    }

    user = retornaProxUsuario(played->usuarios, user);
  }
}