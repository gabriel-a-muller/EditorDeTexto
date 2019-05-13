#ifndef lista_interface_h
#define lista_interface_h
#include <stdlib.h>
#include <stdio.h>
//define o tipo lista_t
typedef struct lista lista_t;

//define o tipo celula_t
typedef struct celula celula_t;

/*
 * Cria uma lista e a inicializa como lista vazia. 
 * "imp" eh um ponteiro para uma funcao de impressao dos dados armazenados dentro da lista. Deve ser usado em "lista_imprime". 
 * o argumento "libera" prove uma maneira de liberar dinamicamente os dados dentro da celula quando "lista_destroi" eh chamada. 
 * Para uma lista onde os dados nao devem ser liberados, libera deve ser NULL 
 * "comparar" eh um ponteiro para funcao de comparacao entre dois dados armazenados na lista. 
 * Deve retornar -1 se o primeiro eh menor que o segundo, 0 se forem iguais, ou 1 se o primeiro for maior que o segundo   
 * Pre: nenhuma
 * Pos: Retorna um ponteiro para uma lista vazia se houver memaria disponivel
 */
lista_t *lista_cria(void (*imp)(const void *), void (*libera)(void *), int (*comparar)(const void *, const void *));

/*
 * Destroi a lista especificada em "l". Nenhuma operacao eh permitida apos a funcao, a nao ser que lista cria seja chamada novamente. 
 * Destroi todos os elementos armazenados na lista se o ponteiro "destruir" for valido
 * Pre: "l" deve ser uma lista valida criada previamente atraves da funcao lista cria
 * Pos: os recursos da lista foram liberados com sucesso e a lista "l" torna-se nula
 */
void lista_destroi(lista_t **l);

/*
 * Retorna 1 se a lista estiver vazia, 0 caso contrario
 * Pre: a lista deve existir
 * Pos: retorna 1 caso a lista estiver vazia, 0 se nao estiver. Retorna -1 caso a lista nao existir
 */
int lista_vazia(lista_t *l);

/*
 * Retorna o tamanho da lista
 * Pre: a lista deve existir
 * Pos: retorna o tamanho da lista. Retorna -1 caso a lista nao existir
 */
int lista_tamanho(lista_t *l);

/*
 * Retorna a celula cabeca da lista
 * Pre: a lista deve existir
 * Pos: retorna a celula cabeca da lista. Retorna NULL caso a lista estiver vazia ou nao existir
 */
celula_t *lista_cabeca(lista_t *l);

/*
 * Retorna a celula cauda da lista
 * Pre: a lista deve existir
 * Pos: retorna a celula cauda da lista. Retorna NULL caso a lista estiver vazia ou nao existir
 */
celula_t *lista_cauda(lista_t *l);

/*
 * Retorna o dado armazenado dentro da celula "c".
 * Pre: a celula deve existir
 * Pos: retorna o dado armazenado dentro de "c" ou NULL caso "c" for invalido
 */
void *lista_dado(celula_t *c);

/*
 * Retorna a celula que esta imediamente apos a celula recebida como parametro.
 * Pre: a celula deve existir
 * Pos: retorna a celula apos "c" ou NULL caso "c" for invalido
 */
celula_t *lista_proximo(celula_t *c);

/*
 * Retorna a celula que esta imediamente antes a celula recebida como parametro.
 * Pre: a celula deve existir
 * Pos: retorna a celula que esta antes de "c" ou NULL caso "c" for invalido
 */
celula_t *lista_anterior(celula_t *c);

/*
 * Retorna 1 caso a celula recebida como parametro for a celula cabeca da lista "l", 0 caso contrario.
 * Pre: a lista deve existir e a celula recebida como parametro deve ser valida
 * Pos: retorna 1 se "c" for cabeca de "l", 0 caso contrario. Retorna -1 se a lista "l" ou a celula "c" forem invalidas ou se a lista estiver vazia
 */
int lista_eh_cabeca(lista_t *l, celula_t *c);

/*
 * Retorna 1 caso a celula recebida como parametro for a celula cauda da lista "l", 0 caso contrario.
 * Pre: a lista deve existir e a celula recebida como parametro deve ser valida
 * Pos: retorna 1 se "c" for cauda de "l", 0 caso contrario. Retorna -1 se a lista "l" ou a celula "c" forem invalidas ou se a lista estiver vazia
 */
int lista_eh_cauda(lista_t *l, celula_t *c);

/*
 * Insere um elemento na lista imeadiamente apos um elemento determinado e recebido como parametro da funcao (celula "c").
 * Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista. 
 * Retorna 1 caso conseguir inserir, 0 caso contrario
 * Pre: A lista e o novo elemento a ser inserido devem ser validos
 * Pos: O elemento recebido como parametro eh inserido logo apos a celula "c" ou na cabeca da lista
 */
int lista_insere_proximo(lista_t *l, celula_t *c, const void *elem);

/*
 * Insere um elemento na lista imeadiamente antes a um elemento determinado e recebido como parametro da funcao (celula "c").
 * Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista. 
 * Retorna 1 caso conseguir inserir, 0 caso contrario
 * Pre: A lista e o novo elemento a ser inserido devem ser validos
 * Pos: O elemento recebido como parametro eh inserido antes da celula "c" ou na cabeca da lista
 */
int lista_insere_anterior(lista_t *l, celula_t *c, const void *elem);

/*
 * Insere um elemento na lista na posicao especificada por "posicao". Caso "posicao" seja maior que o tamanho da lista, insere o elemento na cauda da lista.
 * A ordem das posicoes da lista segue a mesma utilizada em vetores (0 eh equivalente a primeira posicao na lista, 1 a segunda e assim por diante)
 * Retorna 1 caso conseguir inserir, 0 caso contrario
 * Pre: A lista e o novo elemento a ser inserido devem ser validos
 * Pos: O elemento recebido como parametro eh inserido logo apos a celula "c" ou na cabeca da lista. Retorna 1 caso conseguir inserir, 0 caso contrario
 */
int lista_insere_posicao(lista_t *l,  unsigned int posicao, const void *elem);

/* 
 * Remove o elemento conhecido e recebido como parametro. Retorna o conteudo do elemento removido em uma variavel recebida como parametro. 
 * Retorna 1 caso conseguir remover, 0 caso contrario.
 * Pre: a lista deve existir e nao deve estar vazia, a celula a ser removida e a variavel recebida para armazenar o conteudo removido devem ser validas
 * Pos: a lista tera um elemento a menos e seu conteudo sera retornado dentro de uma variavel recebida como parametro
 * Retorna 1 caso conseguir remover, 0 caso contrario
 */
int lista_remove(lista_t *l, celula_t *c, void **elem);

/*
 * Imprime os elementos da lista atraves do ponteiro de funcao "imprime", comecando pela cabeca da lista
 * Pre: a lista deve existir e o ponteiro "imprime" deve ser valido
 * Pos: Os elementos sao impressos usando o ponteiro "imprime"
 */
void lista_imprime(lista_t *l);

/*
 * Insere um novo elemento na lista de formacelula_t *busca_celula(lista_t *l, const unsigned int posicao); ordenada (crescente). Caso o ponteiro "elem" tenha um valor igual a um elemento que estiver na lista, a insercao de "elem" deve ser feita logo apos.
 * Eh responsabilidade de quem chama o gerenciamento da memoria de "elem", onde ela devera permanecer valida enquanto estiver dentro da lista.
 * Caso o ponteiro de funcao "compara" for NULL, a insercao de "elem" deve ser feita na cauda da lista.
 * Retorna 1 caso conseguir inserir, 0 caso contrario
 * Pre: a lista deve existir e "elem" deve ser valido
 * Pos: o elemento recebido pela operacao eh inserido de forma ordenada (crescente)
 * OBS: considere que a lista ja esta ordenada, ou seja, nao precisa ordenar antes de usar a funcao
 */
int lista_insere_ordenado(lista_t *l, const void *elem);

/*
 * Funcao recursiva que retorna a celula da lista que contem o elemento recebido como parametro. A comparacao deve ser feita usando ponteiros, e nao a funcao de comparacao internda da lista.
 * A celula "c" recebida deve ser usada para finalizar a recursao.
 * Pre: a lista, o elemento e a celula recebidas devem ser validas. A lista nao pode estar vazia
 * Pos: Retorna a celula que contem o elemento ou NULL caso o elemento nao estiver na lista recebida
 */
celula_t *lista_busca_recursiva(lista_t *l, const void *elem, celula_t *c);

/*
 * Separa a lista recebida como parametro em duas, de tal forma que a segunda lista comece na primeira celula logo apos a celula que contem o elemento recebido como parametro.
 * A funcao deve retornar um ponteiro para a segunda sub-divisao da lista original, enquanto l deve continuar apontando para o primeiro elemento da primeira sub-divisao da lista.
 * Se o elemento recebido como parametro for NULL ou nao estiver na lista "l", a funcao nao faz nada e retorna NULL. 
 * A nova lista deve ter os mesmos ponteiros internos (imprime, compara e destruir) da lista "l"
 * Pre: lista deve existir e o elemento recebido como parametro deve ser valido
 * Pos: retorna um ponteiro para a nova lista que inicia logo apos a celula que contem "elem". Esta celula torna-se a cauda da lista "l". Retorna NULL caso nao conseguir separar a lista
 */
lista_t *lista_separa(lista_t *l, const void *elem);

/*
 * Concatena duas listas recebidas como parametro e retorna a lista resultante da concatenacao.
 * Depois da funcao ser chamada, as listas "l1" e "l2" nao sao mais validas (serao destruidas) e suas celulas estarao dentro da lista retornada.
 * A nova lista deve ter os mesmos ponteiros internos (imprime, compara e destruir) da lista "l1" ou da lista "l2" se a "l1" for vazia
 * Pre: "l1" e "l2" devem ser listas validas (observe que elas podem ser vazias).
 * Pos: retorna uma nova lista contendo a concatenacao das duas listas recebidas como parametro. Retorna NULL caso nao conseguir concatenar as duas listas. 
 * Retorna NULL se ambas forem vazias (sem destrui-las). 
 * Apos a execucao, l1 e l2 nao sao mais listas validas e foram destruidas.
 */
lista_t *lista_concatena_e_destroi(lista_t **l1, lista_t **l2);

//retorna uma celula em determinada posicao, caso posicao seja maior que o tamanho da lista, retorna a cauda da lista.
celula_t *busca_celula(lista_t *l, unsigned int posicao);

unsigned int busca_posicao(lista_t *l, celula_t *c);
#endif
