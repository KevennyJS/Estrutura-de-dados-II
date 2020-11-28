#ifndef INTERCALACAO_H
#define INTERCALACAO_H

#include "nomes.h"
#include "cliente.h"

// Executa o algoritmo de intercalacao de particoes
// nome_arquivo_saida: nome do arquivo de sa?da
// num_p: numero de particoes a serem intercaladas
// nome_particoes: lista encadeada com nomes das particoes de entrada
void intercalacao_basico(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes);

// Executa o algoritmo de intercalacao de particoes usando arvore de vencedores
// nome_arquivo_saida: nome do arquivo de sa?da
// num_p: numero de particoes a serem intercaladas
// nome_particoes: lista encadeada com nomes das particoes de entrada
void intercalacao_arv_vencedores(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes);

// Executa o algoritmo de intercalacao de particoes usando intercalacao ótima
// nome_arquivo_saida: nome do arquivo de sa?da
// num_p: numero de particoes a serem intercaladas
// nome_particoes: lista encadeada com nomes das particoes de entrada
// f: numero máximo de arquivos que podem ser abertos de cada vez
void intercalacao_otima(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes, int f);

#endif