#include "PlayED.h"
#include "Musica.h"
#include "Playlist.h"
#include "Usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TAM_NOME_CAMINHO 300

struct PlayED
{
    ListaDeUsuario *usuarios;
    ListaDePlaylist *playlists;
    ListaDeMusica *musicas;
};

ListaDeUsuario *retornaListaUsuario(PlayED *played)
{
    if (!played)
        return NULL;

    return played->usuarios;
}

ListaDePlaylist *retornaListaPlaylists(PlayED *played)
{
    if (!played)
        return NULL;

    return played->playlists;
}

ListaDeMusica *retornaListaMusicas(PlayED *played)
{
    if (!played)
        return NULL;

    return played->musicas;
}

ListaDeUsuario *leListaDeUsuario(char *caminhoPastaEntrada)
{
    char *docAmizade = "amizade.txt";
    char caminhoAmizade[TAM_NOME_CAMINHO];

    sprintf(caminhoAmizade, "%s/%s", caminhoPastaEntrada, docAmizade);

    FILE *arquivoAmizade = fopen(caminhoAmizade, "r");

    if (!arquivoAmizade)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoAmizade);
        return NULL;
    }

    ListaDeUsuario *usuarios = criaListaDeUsuario();

    char nome[100];
    char amigo[100];
    char aux;

    // na primeira linha do arquivo de amizades, enquanto o caracter auxiliar for ';' continua colocando os usuarios na lista
    do
    {
        fscanf(arquivoAmizade, "%[^;\n]%c", nome, &aux);
        insereUsuario(usuarios, criaUsuario(nome));
    } while (aux == ';');

    // atribuir as amizades dos usuarios que foram colocados na lista
    while (!feof(arquivoAmizade))
    {
        fscanf(arquivoAmizade, "%[^;\n];%[^\n]%*c", nome, amigo);
        adicionaAmigo(buscaUsuarioPorNome(usuarios, nome),
                      buscaUsuarioPorNome(usuarios, amigo));
    }

    fclose(arquivoAmizade);

    return usuarios;
}

void *lePlaylistsUsuarios(char *caminhoPastaEntrada, PlayED *played)
{
    char *docPlaylist = "playlists.txt";
    char caminhoPlaylist[TAM_NOME_CAMINHO];

    sprintf(caminhoPlaylist, "%s/%s", caminhoPastaEntrada, docPlaylist);
    FILE *arquivoPlaylist = fopen(caminhoPlaylist, "r");

    if (!arquivoPlaylist)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoPlaylist);
        return NULL;
    }

    char nome[100];
    char nomePlaylist[100];
    char aux = ';';
    int qtdPlaylists;

    // le o arquivo de playlist e vai fazendo atribuição linha a linha
    while (!feof(arquivoPlaylist))
    {

        // le cada a linha do arquivo e atribuir as playlists p/ cada usuario
        fscanf(arquivoPlaylist, "%[a-zA-Z]%*c%d%c", nome, &qtdPlaylists, &aux);

        Usuario *user = buscaUsuarioPorNome(played->usuarios, nome);
        atribuiQtdPlaylistsUsuario(user, qtdPlaylists);

        // le nome da playlist, cria ela e adiciona na lista de playlist do
        // usuario
        for (int i = 0; i < qtdPlaylists; i++)
        {
            fscanf(arquivoPlaylist, "%[^.].txt%*c", nomePlaylist);
            Playlist *playlist = criaPlaylist(nomePlaylist);

            // abre o arquivo de cada playlist e insere cada musica;

            char *docMusicas = nomePlaylist;
            char caminhoMusicas[TAM_NOME_CAMINHO];
            sprintf(caminhoMusicas, "%s/%s.txt", caminhoPastaEntrada, docMusicas);

            FILE *arquivoMusicas = fopen(caminhoMusicas, "r");

            while (!feof(arquivoMusicas))
            {

                char nomeMusica[100] = "\n";
                char nomeArtista[100] = "\n";
                char musicaToda[100] = "\n";

                fscanf(arquivoMusicas, "%[^\n]%*c", musicaToda);
                int i = 0, j = 0, entrouNome = 0;
                for (int j = 0; j < strlen(musicaToda); j++)
                {

                    if (!entrouNome && musicaToda[j] == ' ' && musicaToda[j + 1] == '-' && musicaToda[j + 2] == ' ')
                    {
                        entrouNome = 1;
                        j = j + 2;
                    }
                    else
                    {
                        if (entrouNome)
                        {
                            nomeMusica[i] = musicaToda[j];
                            i++;
                        }
                        else
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

PlayED *criaPlayED(char *caminhoPastaEntrada)
{
    PlayED *played = (PlayED *)malloc(sizeof(PlayED));
    played->usuarios = leListaDeUsuario(caminhoPastaEntrada);
    played->musicas = criaListaDeMusica();
    played->playlists = criaListaDePlaylist();
    lePlaylistsUsuarios(caminhoPastaEntrada, played);

    return played;
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
*/

void refatoraPlayED(PlayED *played)
{
    Usuario *user = retornaPrimUsuario(played->usuarios);

    // varre a lista de usuarios ate o final
    while (user != NULL)
    {
        int qtdePlaylists = 0;
        ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);

        // essa nova lista de playlists é organizada por artistas
        ListaDePlaylist *novaListaPlaylist = criaListaDePlaylist();

        // coloca as musicas na playlist nova e tira da antiga ate esvaziar
        while (!ehVaziaListaPlaylistUsuario(user))
        {
            Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

            while (!ehVaziaPlaylist(playlist))
            {

                Musica *musica = retornaPrimMusicaPlaylist(playlist);
                Playlist *playlistDoArtista = buscaPlaylistPorNome(
                    novaListaPlaylist, retornaArtistaMusica(musica));

                // se nao existir uma playlist com o nome do artista vai criar uma nova
                // e colocar na lista nova
                if (playlistDoArtista == NULL)
                {
                    playlistDoArtista = criaPlaylist(retornaArtistaMusica(musica));
                    inserePlaylistNaLista(novaListaPlaylist, playlistDoArtista);
                    inserePlaylistNaLista(played->playlists, playlistDoArtista);
                    qtdePlaylists++;
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
        atribuiQtdPlaylistsUsuario(user, qtdePlaylists);
        user = retornaProxUsuario(played->usuarios, user);
    }
}

void imprimePlayEDRefatorada(PlayED *played, char *caminhoPastaSaida)
{
    char *docRefatora = "played-refatorada.txt";
    char caminhoRefatora[TAM_NOME_CAMINHO];
    char caminhoPastaUsuario[100];
    char *nomePlaylist = NULL;
    char caminhoPlaylist[TAM_NOME_CAMINHO];

    sprintf(caminhoRefatora, "%s/%s", caminhoPastaSaida, docRefatora);

    FILE *arquivoRefatora = fopen(caminhoRefatora, "w");

    if (!arquivoRefatora)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoRefatora);
        return;
    }

    Usuario *user = retornaPrimUsuario(played->usuarios);

    // varre a lista de usuarios ate o final
    while (user != NULL)
    {
        imprimeUsuarioArquivo(user, arquivoRefatora);

        sprintf(caminhoPastaUsuario, "%s/%s", caminhoPastaSaida, retornaNomeUsuario(user));

        mkdir(caminhoPastaUsuario, 0700);

        ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
        Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

        // gera o arquivo das playlists dentro da pasta
        while (playlist != NULL)
        {
            nomePlaylist = retornaNomePlaylist(playlist);

            sprintf(caminhoPlaylist, "%s/%s.txt", caminhoPastaUsuario, nomePlaylist);

            FILE *arquivoPlaylist = fopen(caminhoPlaylist, "w");

            if (!arquivoPlaylist)
            {
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

/*Comentário pra guiar o programa:
Esquema de similaridades:
-Pega o primeiro usuário da lista de usuários
- Pega o primeiro amigo da lista de amigos desse usuário
    -  Verifica se esse amigo já passou pelo loop principal (flag similaridade = 1)
    - Se for, passa pro próximo amigo
        - Caso não seja, abre a lista de playlist do usuário, pega a primeira playlist
            - pega a primeira música dessa playlist
                - busca essa música na lista de playlist do amigo
                    - se essa musica existir, aumenta o contador similaridades
            -passa pra próxima musica e repete o processo ate o final da playlist
        - Passa para próxima playlist ate o final da lista de playlist
    -imprime no arquivo a quantidade de similaridades entre os dois amigos
    - reseta o contador de similaridade
    - passa pro próximo amigo ate chegar no final da lista de amigos
- Marca o usuario com a flag similaridade
- passa pro próximo usuário até chegar no ultimo
*/

void imprimeSimilaridades(PlayED *played, char *caminhoPastaSaida)
{
    char *docSimilaridades = "similaridades.txt";
    char caminhoSimilaridades[TAM_NOME_CAMINHO];

    sprintf(caminhoSimilaridades, "%s/%s", caminhoPastaSaida, docSimilaridades);

    FILE *arquivoSimilaridades = fopen(caminhoSimilaridades, "w");
    if (!arquivoSimilaridades)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoSimilaridades);
    }

    Usuario *user = retornaPrimUsuario(played->usuarios);

    // pega o primeiro usuario da lista de amigos
    while (user != NULL)
    {
        // pra cada usuario varre a lista de amigos dele
        Usuario *amigo = retornaPrimUsuario(retornaListaAmigosUsuario(user));
        int similaridades = 0;

        // ve se o amigo ja passou no loop, se sim ele pula essa etapa

        while (amigo != NULL)
        {
            if (!retornaSimilaridadeUsuario(amigo))
            {
                // vai olhar todas as musicas da playlist do usuario e ver se o amigo
                // tem uma igual
                ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
                Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

                while (playlist != NULL)
                {
                    Musica *musica = retornaPrimMusicaPlaylist(playlist);

                    while (musica != NULL)
                    {
                        ListaDePlaylist *listaPlaylistAmigo =
                            retornaListaPlaylistUsuario(amigo);
                        if (buscaMusicaNaListaPlaylist(listaPlaylistAmigo, musica) != NULL)
                            similaridades++;

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

/*Comentário pra guiar o programa:
Esquema de merge:
- Pega a primeira pessoa da lista de usuários
    - Pega a primeira playlist dessa pessoa
        - Pega a primeira música da playlist
          - Pega o primeiro amigo da pesssoa
            - Verifica se o amigo tem a playlist de mesmo nome
            - Se não tiver pula o processo
            - Se tiver, passa pelas músicas da playlist do amigo
                - Verifica se a música da playlist do amigo está na playlist da pessoa
                - Se não estiver, coloca a música na playlist da pessoa
        - Passa por todos os amigos da pessoa
    - Passa por todas as playlists da pessoa
- Passa por todas as pessoas da lista de usuários
*/

void mergePlayED(PlayED *played)
{
    Usuario *user = retornaPrimUsuario(played->usuarios);

    // varre a lista de usuarios ate o final
    while (user != NULL)
    {
        ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
        Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

        // varre a lista de playlist do usuario
        while (playlist != NULL)
        {
            Usuario *amigo = retornaPrimUsuario(retornaListaAmigosUsuario(user));

            // varre a lista de amigos do usuario
            while (amigo != NULL)
            {
                ListaDePlaylist *listaPlaylistAmigo =
                    retornaListaPlaylistUsuario(amigo);
                Playlist *playlistAmigo = buscaPlaylistPorNome(
                    listaPlaylistAmigo, retornaNomePlaylist(playlist));
                ListaDeMusica *novasMusicas;

                // se o amigo tiver a playlist com o mesmo nome busca as musicas
                if (playlistAmigo)
                {
                    Musica *musicaAmigo = retornaPrimMusicaPlaylist(playlistAmigo);

                    // varre a lista de musicas do amigo
                    while (musicaAmigo != NULL)
                    {
                        // se a musica do amigo nao estiver na playlist do usuario insere
                        if (!estaNaListaMusica(retornaListaMusica(playlist), musicaAmigo))
                            insereMusicaNaPlaylist(playlist, musicaAmigo);
                        musicaAmigo = retornaProxMusicaPlaylist(playlistAmigo, musicaAmigo);
                    }
                }

                amigo = retornaProxUsuario(retornaListaAmigosUsuario(user), amigo);
            }

            playlist = retornaProxPlaylist(listaPlaylist, playlist);
        }

        user = retornaProxUsuario(played->usuarios, user);
    }
}

void imprimePlayEDMerged(PlayED *played)
{
    char caminhoPastaUsuario[100];
    char *nomePlaylist = NULL;
    char caminhoPlaylist[TAM_NOME_CAMINHO];

    Usuario *user = retornaPrimUsuario(played->usuarios);

    while (user != NULL)
    {
        sprintf(caminhoPastaUsuario, "Merge/%s", retornaNomeUsuario(user));

        mkdir(caminhoPastaUsuario, 0700);

        ListaDePlaylist *listaPlaylist = retornaListaPlaylistUsuario(user);
        Playlist *playlist = retornaPrimPlaylist(listaPlaylist);

        // gera o arquivo das playlists dentro da pasta
        while (playlist != NULL)
        {
            nomePlaylist = retornaNomePlaylist(playlist);

            sprintf(caminhoPlaylist, "%s/%s.txt", caminhoPastaUsuario, nomePlaylist);

            FILE *arquivoPlaylist = fopen(caminhoPlaylist, "w");

            if (!arquivoPlaylist)
            {
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

void liberaPlayED(PlayED *played)
{
    destroiListaEMusicas(retornaListaMusicas(played));
    destroiListaEPlaylists(retornaListaPlaylists(played));
    destroiListaEUsuarios(retornaListaUsuario(played));
    free(played);
}
