#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "intercalacao.h"
#include "nomes.h"
#include "cliente.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef struct vetor{
    TCliente *cli;
    FILE *f;
}TVet;

/*
 * Definicao de tipo para no de arvore de vencedores
 */
typedef struct No {
    TCliente *vencedor;
    struct No *endVencedor;
    FILE *f;
    struct No *pai;
    struct No *dir;
    struct No *esq;
} TNo;

void adicionarNovoArq(char* novoNome,Nomes *nome_particoes);

void intercalacao_basico(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes) {

    int fim = 0; //variavel que controla fim do procedimento
    FILE *out; //declara ponteiro para arquivo

    //abre arquivo de saida para escrita
    if ((out = fopen(nome_arquivo_saida, "wb")) == NULL) {
        printf("Erro ao abrir arquivo de sa?da\n");
    } else {
        //cria vetor de parti??es
        TVet v[num_p];

        //abre arquivos das particoes, colocando variavel de arquivo no campo f do vetor
        //e primeiro cliente do arquivo no campo cli do vetor
        for (int i=0; i < num_p; i++) {
            v[i].f = fopen(nome_particoes->nome, "rb");
            if (v[i].f != NULL) {
                TCliente *c = le_cliente(v[i].f);
                if (c == NULL) {
                    //arquivo estava vazio
                    //coloca HIGH VALUE nessa posi??o do vetor
                    v[i].cli = cliente(INT_MAX, "");
                }
                else {
                    //conseguiu ler cliente, coloca na posi??o atual do vetor
                    v[i].cli = c;
                }
            }
            else {
                fim = 1;
            }
            nome_particoes = nome_particoes->prox;
        }

        while (!(fim)) { //conseguiu abrir todos os arquivos
            int menor = INT_MAX;
            int pos_menor;
            //encontra o cliente com menor chave no vetor
            for(int i = 0; i < num_p; i++){
                if(v[i].cli->cod_cliente < menor){
                    menor = v[i].cli->cod_cliente;
                    pos_menor = i;
                }
            }
            if (menor == INT_MAX) {
                fim = 1; //terminou processamento
            }
            else {
                //salva cliente no arquivo de sa?da
                salva_cliente(v[pos_menor].cli, out);
                //atualiza posi??o pos_menor do vetor com pr?ximo cliente do arquivo
                TCliente *c = le_cliente(v[pos_menor].f);
                if (c == NULL) {
                    //arquivo estava vazio
                    //coloca HIGH VALUE nessa posi??o do vetor
                    v[pos_menor].cli = cliente(INT_MAX, "");
                }
                else {
                    v[pos_menor].cli = c;
                }

            }
        }

        //fecha arquivos das parti??es de entrada
        for(int i = 0; i < num_p; i++){
            fclose(v[i].f);
        }
        //fecha arquivo de sa?da
        fclose(out);
    }
}

void intercalacao_arv_vencedores(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes){
    //TODO: Implementar essa função
}

void intercalacao_otima(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes, int f) {
    FILE **particoes = malloc((f - 1) * sizeof(FILE));
    FILE *out;
    int QuantidadeParticoesAbertas = 0;
    int contadorNovasParticoes=0;

    Nomes particoesAtuais = *nome_particoes;
    char nomeNovaParticao[30] = {0};

    //rodar até restar uma partição
    do{

        //limpando array de nome da nova particao
        for(int cont = 0 ; cont < 30 ; cont++){
            nomeNovaParticao[cont] = 0;
        }

        contadorNovasParticoes++;
        for (int cont = 0; cont < (f - 1); cont++) {
            particoes[cont] = fopen(nome_particoes->nome, "rw");
            QuantidadeParticoesAbertas++;
            if (nome_particoes->prox == NULL) {
                break;
            }
            nome_particoes = nome_particoes->prox;
        }

        //criando nome da nova particao
        strcat(nomeNovaParticao,"nova");
        char str[12];
        sprintf(str, "%d", contadorNovasParticoes);
        strcat(nomeNovaParticao,str);
        strcat(nomeNovaParticao,".dat");

        //adicionando nova partição na lista de partições que precisão ser organizadas
        adicionarNovoArq(nomeNovaParticao,nome_particoes);

        //organizando as partições em uma nova partição
        intercalacao_basico(nomeNovaParticao,QuantidadeParticoesAbertas,&particoesAtuais);

        //atualizando quantidade de numero de partições restantes
        num_p = num_p - (QuantidadeParticoesAbertas - 1);

        //fechando todas as partições abertas
        for(int cont =0; cont < QuantidadeParticoesAbertas ;cont++){
            fclose(particoes[cont]);
        }

    }while (num_p>1);

    //salvando a partição final na partição de saida
    if ((out = fopen(nome_arquivo_saida, "wb")) == NULL) {
        printf("Erro ao abrir arquivo de saida\n");
    } else {
        TCliente* c;
        FILE* fp = fopen(nomeNovaParticao, "rb");
        while ((c = le_cliente(fp)) != NULL){
            //imprime_cliente(c);
            salva_cliente(c, out);
        }
        fclose(fp);
        free(c);
        free(particoes);
    }
    fclose(out);
}

void adicionarNovoArq(char* novoNome,Nomes *nome_particoes){
    while (1){
        if (nome_particoes->prox != NULL){
            nome_particoes = nome_particoes->prox;
        }else{
            nome_particoes->prox = cria_nomes(novoNome,NULL);
            break;
        }
    }
}