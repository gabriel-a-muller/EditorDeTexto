#include "lista_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linha {
	celula_t *linha;
	unsigned int posicao;
	unsigned int num_char;
} linha_t;

/*Abre um arquivo texto e retorna um ponteiro para arquivo, se estiver vazio ou invalido retorna NULL.
*/
FILE *abre_arquivo (const char *arquivo);

/*Fecha um arquivo texto, retorna 1 caso nao consiga fechar o arquivo, 0 caso contrario.
*/
int fecha_arquivo(FILE *arq);

/*compara dois valores de celulas,retorna 0 caso ocorra igualdadeo.
*/
int compara(const void *str1,const void *str2);

/*libera o dado dentro da celula;
*/
void libera(void *dado);

/* Imprime o valor dentro da celula;
*/
void imprime (const void *dado);

/* Recebe um parametro para leitura; Pode-se enviar um arquivo ou um valor digitado diretamente no teclado com stdin.
Retorna uma string com o conteudo da linha
*/
char *leitura(FILE *arquivo); //stdin   resposta = leitura(stdin)

/*Manual com todas as operacoes do projeto.
*/
void funcao_h_ajuda();

//retorna os numeros de characteres de uma string.
int numero_de_char(char *string);

/*Cria uma struct linha, que recebe uma celula do buffer para acompanhar.
*/
linha_t *linha_cria();

// Destroi uma linha criada.
void linha_destroi(linha_t **l);

/*Le um arquivo texto, cujo nome eh informado pelo usuario, e armazena no
buffer. Qualquer informacao existente no buffer sera descartada. Ao
concluir a leitura, a linha corrente sera a primeira linha do arquivo.
Retorna 0 caso nao seja possivel ler o arquivo.
arquivo, linha e buffer devem ser validos.
*/
celula_t *funcao_r_leitura(unsigned int *posicao, lista_t *buffer);


int funcao_g(lista_t *l,linha_t *cursor);

/*Insere em uma linha especificada pelo usuário, uma nova linha também
digitada pelo usuário. O editor deve primeiramente pedir ao usuário
que informe a posição (ou seja, a linha) em que a nova linha digitada
deve ser inserida. Após isso, o prompt “l:” solicita a nova linha que
será colocada na posição. Após a inserção, a posição atual do cursor
passa a ser a posição da nova linha
*/



/*Encontra a primeira linha, iniciando pela linha corrente, que contêm uma
string alvo que foi informada pelo usuário.
*/



