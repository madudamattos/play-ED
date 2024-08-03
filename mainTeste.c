

// #include "Musica.h"
// #include "Playlist.h"
// #include "Usuario.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main(int argc, char *argv[]) {

//   Musica *musica1 = criaMusica("musica1", "artista1");
//   Musica *musica2 = criaMusica("musica2", "artista2");
//   Musica *musica3 = criaMusica("Teste (Acustico)", "artista3");
//   Musica *musica4 = criaMusica("musica4", "artista4");

//   Playlist *playlist1 = criaPlaylist("playlist1");

//   insereMusicaNaPlaylist(playlist1, musica1);
//   insereMusicaNaPlaylist(playlist1, musica2);
//   insereMusicaNaPlaylist(playlist1, musica3);
//   insereMusicaNaPlaylist(playlist1, musica4);

//   Musica *musica5 = criaMusica("musica5", "artista5");
//   Musica *musica6 = criaMusica("musica6", "artista6");
//   Musica *musica7 = criaMusica("musica7", "artista7");
//   Musica *musica8 = criaMusica("musica8", "artista8");

//   Playlist *playlist2 = criaPlaylist("playlist2");

//   insereMusicaNaPlaylist(playlist2, musica5);
//   insereMusicaNaPlaylist(playlist2, musica6);
//   insereMusicaNaPlaylist(playlist2, musica7);
//   insereMusicaNaPlaylist(playlist2, musica8);

//   // testador funcoes de busca do musica
//   if (ehIgualMusica(musica1, musica1)) {
//     printf("musica 1 é igual musica 1\n");
//   } else {
//     printf("musica 1 diferente de musica 1\n");
//   }

//   if (ehIgualMusica(musica1, musica2)) {
//     printf("musica 1 é igual musica 2\n");
//   } else {
//     printf("musica 1 diferente de musica 2\n");
//   }

//   // compara artistas
//   char *artistaMusica1 = retornaArtistaMusica(musica1);

//   if (ehIgualArtista(artistaMusica1, "artista1")) {
//     printf("artista musica 1 é igual artista 1\n");
//   } else {
//     printf("artista musica 1 diferente de artista 1\n");
//   }

//   char *artistaMusica2 = retornaArtistaMusica(musica2);

//   if (ehIgualArtista(artistaMusica2, "artista1")) {
//     printf("artista musica 2 é igual artista 1\n");
//   } else {
//     printf("artista musica 2 diferente de artista 1\n");
//   }

//   // compara nomes

//   char *nome1 = retornaNomeMusica(musica1);

//   if (ehIgualNome(nome1, "musica1")) {
//     printf("nome musica 1 é igual nome musica 1\n");
//   } else {
//     printf("nome musica 1 diferente de nome musica 1\n");
//   }
//   char *nome2 = retornaNomeMusica(musica2);

//   if (ehIgualNome(nome2, "musica1")) {
//     printf("nome musica 2 é igual nome musica 2\n");
//   } else {
//     printf("nome musica 2 diferente de nome musica 2\n");
//   }

//   ListaDePlaylist *listaDePlaylist = criaListaDePlaylist();

//   inserePlaylistNaLista(listaDePlaylist, playlist1);
//   inserePlaylistNaLista(listaDePlaylist, playlist2);

//   Usuario *usuario1 = criaUsuario("João");
//   Usuario *usuario2 = criaUsuario("Maria");
//   Usuario *usuario3 = criaUsuario("Pedro");

//   atribuiListaDePlaylist(usuario1, listaDePlaylist);
//   atribuiListaDePlaylist(usuario2, listaDePlaylist);
//   atribuiListaDePlaylist(usuario3, listaDePlaylist);

//   adicionaAmigo(usuario1, usuario2);
//   adicionaAmigo(usuario1, usuario3);

//   imprimeUsuario(usuario1);

//   imprimeUsuario(usuario2);

//   imprimeUsuario(usuario3);

//   //----------------------------------------------------

//   ListaDeMusica *listaDeMusica1 = criaListaDeMusica();

//   if (ehVaziaListaMusica(listaDeMusica1))
//     printf("A lista 1 de musica é vazia\n");
//   else
//     printf("A lista 1 possui musicas\n");

//   insereMusica(listaDeMusica1, musica1);
//   insereMusica(listaDeMusica1, musica2);
//   insereMusica(listaDeMusica1, musica3);
//   insereMusica(listaDeMusica1, musica4);

//   if (ehVaziaListaMusica(listaDeMusica1))
//     printf("A lista 1 de musica é vazia\n");
//   else
//     printf("A lista 1 possui musicas\n");

//   printf("primeira musica da lista 1: %s\n",
//          retornaNomeMusica(retornaPrimMusica(listaDeMusica1)));

//   printf("A próxima musica da lista 1 é: %s",
//          retornaNomeMusica(retornaProxMusica(listaDeMusica1, musica2)));

//   retornaPrimMusicaPlaylist(playlist1);

//   printf("\n----------------------------------------------\n");

//   Playlist *p3 = criaPlaylist("David Guetta");

//   if (ehVaziaPlaylist(p3))
//     printf("p3 é vazia\n");

//   insereMusicaNaPlaylist(p3, musica1);
//   insereMusicaNaPlaylist(p3, musica2);
//   insereMusicaNaPlaylist(p3, musica3);

//   if (ehVaziaPlaylist(p3))
//     printf("p3 é vazia\n");

//   retiraMusicaDaPlaylist(p3, musica1);

//   printf("A primeira musica da p3 é: %s",
//          retornaNomeMusica(retornaPrimMusicaPlaylist(p3)));

//   Musica *musica29 = criaMusica("Musica29", "Rihanna");

//   Playlist *p5 = criaPlaylist("Rihanna");

//   if (ehPlaylistDoArtista(p5, musica29))
//     printf("playlist 5 é do artista 29\n");
//   else
//     printf("artista diferente\n");
//   int ehPlaylistDoArtista(Playlist * playlist, Musica * musica);

//   printf("Primeira playlist da lista: %s\n",
//          retornaNomePlaylist(retornaPrimPlaylist(listaDePlaylist)));

//   printf("A proxima playlist é %s\n",
//          retornaNomePlaylist(retornaProxPlaylist(listaDePlaylist, playlist1)));

//   if (ehVaziaListaPlaylistUsuario(usuario1))
//     printf("vazia");
//   else {
//     printf(" nao vazia");
//   }

//   retiraPlaylistDaLista(listaDePlaylist, playlist1);
//   retiraPlaylistDaLista(listaDePlaylist, playlist2);

//   if (ehVaziaListaPlaylistUsuario(usuario1))
//     printf("vazia");
//   else {
//     printf(" nao vazia");
//   }

  
//   // destroiListaDePlaylist(listaDePlaylist);

//   // destroiListaDeMusica(listaDeMusica);
//   // destroiListaDeMusica(listaDeMusica2);

//   // destroiListadeAmigos(usuario1);
//   // destroiListadeAmigos(usuario2);
//   // destroiListadeAmigos(usuario3);

//   // destroiUsuario(usuario1);
//   // destroiUsuario(usuario2);
//   // destroiUsuario(usuario3);
// }
