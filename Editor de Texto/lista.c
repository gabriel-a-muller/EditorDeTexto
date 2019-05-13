#include "lista_privado.h"

//coloque aqui a implementacao das operacoes do TDA lista duplamente encadeada generico

lista_t *lista_cria(void (*imp)(const void *), void (*libera)(void *), int (*comparar)(const void *, const void *)) {

	lista_t *l = (lista_t*) malloc(sizeof(lista_t));
	if (l==NULL)
		return NULL;
	
	l->cabeca 	= NULL;
	l->cauda  	= NULL;
	l->tamanho	= 0;
	l->imprime	= imp;	
	l->destruir = libera;	
	l->compara	= comparar;

	return l;
}

void lista_destroi(lista_t **l) {
	
	if(l==NULL || *l==NULL)
		return;
	
	if((*l)->tamanho==0) {
		free(*l);
		*l = NULL;
		return;
	}
	celula_t *aux;
	while ((*l)->cabeca != NULL) {
		aux = (*l)->cabeca;
		if((*l)->destruir != NULL)
			(*l)->destruir(aux->dado);
		
		(*l)->cabeca = aux->prox;
		free(aux);         
	}
	free(*l);
	*l = NULL;
}

int lista_vazia(lista_t *l) {

	if(l==NULL)
		return -1;
	if(l->tamanho==0)
		return 1;
	else
		return 0;
}
	
int lista_tamanho(lista_t *l) {
	
	if(l==NULL)
		return -1;
	else
		return l->tamanho;
}

celula_t *lista_cabeca(lista_t *l) {  //return lista-cabeca, NULL caso esteja vazia ou nao exista

	if(l==NULL || l->tamanho==0)
		return NULL;
	return l->cabeca;
}

celula_t *lista_cauda(lista_t *l) {

	if(l==NULL || l->tamanho==0)
		return NULL;
	return l->cauda;
}

void *lista_dado(celula_t *c) { //duvida void e retorna NULL 	
	if(c==NULL || c->dado==NULL)
		return NULL;
	return c->dado;
}

celula_t *lista_proximo(celula_t *c) {
	if(c==NULL || c->prox==NULL)
		return NULL;
	return c->prox;
}

celula_t *lista_anterior(celula_t *c) {
	if(c==NULL || c->ant==NULL)
		return NULL;
	return c->ant;
}

int lista_eh_cabeca(lista_t *l, celula_t *c) {
	if(l==NULL || c==NULL || l->tamanho==0)
		return -1;	
	if(l->cabeca == c)
		return 1;
	return 0;
}

int lista_eh_cauda(lista_t *l, celula_t *c) {
	if(l==NULL || c==NULL || l->tamanho==0)
		return -1;	
	if(l->cauda == c)
		return 1;
	return 0;
}

int lista_insere_proximo(lista_t *l, celula_t *c, const void *elem) {
	if(l==NULL || elem==NULL)
		return 0;
	celula_t *node = (celula_t*) malloc(sizeof(celula_t));
	if (node==NULL)
		return 0;
	if(c==NULL) {
		if(l->tamanho==0) {
			l->cabeca  = node;
			l->cauda   = node;
			node->prox = NULL;
			node->ant  = NULL;
		}
		else {
			node->prox = l->cabeca;
			node->ant  = NULL;
			l->cabeca->ant = node;
			l->cabeca = node;
		}
	}	
	else {
		if(c==l->cauda)
			l->cauda = node;	
		else
			c->prox->ant = node;
		node->prox	 = c->prox;
		node->ant 	 = c;			
		c->prox		 = node;
	}
	node->dado =  (void*)elem;
	l->tamanho++;
	return 1;
}

int lista_insere_anterior(lista_t *l, celula_t *c, const void *elem){
	if(l==NULL || elem==NULL)
		return 0;
	celula_t *node = (celula_t*) malloc(sizeof(celula_t));
	if (node==NULL)
		return 0;

	if(c==NULL || c==l->cabeca) {
		if(l->tamanho==0) {
			l->cauda   = node;
			l->cabeca  = node;
			node->prox = NULL;
			node->ant  = NULL;
		}
		else{		
			node->prox = l->cabeca;
			node->ant  = NULL;
			l->cabeca->ant = node;  //e se nao houver um um l->cabeca?
			l->cabeca = node;
		}
		
	}	
	else {
		c->ant->prox = node;
		node->prox	 = c;
		node->ant 	 = c->ant;			
		c->ant		 = node;
	}
	node->dado = (void*)elem;
	l->tamanho++;
	return 1;
}

int lista_insere_posicao(lista_t *l, unsigned int posicao, const void *elem) {
	if(l==NULL || elem==NULL)
		return 0;
	celula_t *aux;
	if(posicao >= l->tamanho) 
		return lista_insere_proximo(l,l->cauda,elem);			
	aux  = l->cabeca;
	for(int i=0;i<posicao;i++)
		aux = aux->prox;
	//node = aux;
	return lista_insere_anterior(l,aux,elem);		
}	

int lista_remove(lista_t *l, celula_t *c, void **elem) {
	if (l==NULL || l->tamanho == 0 || c==NULL || elem == NULL || *elem == NULL) 
		return 0;
	*elem = c->dado;
	//celula_t *aux;
	if (l->cabeca == l->cauda) {
		l->cauda  = NULL;			
		l->cabeca = NULL;
		free(c);
		c = NULL;   
		l->tamanho--;
		return 1;
	}		
	if (c==l->cabeca) {
		c->prox->ant = NULL;
		l->cabeca = c->prox;
		free(c);
		c = NULL;  //???????
		l->tamanho--;
		return 1;
	}
	if(c==l->cauda) {
		c->ant->prox = NULL;
		l->cauda = c->ant;	
		free(c);
		c = NULL; //????????
		l->tamanho--;
		return 1;
	}
	else {
		c->prox->ant = c->ant;
		c->ant->prox = c->prox;
		free(c);
		c = NULL;
		l->tamanho--;		
		return 1;
	}
}	

void lista_imprime(lista_t *l){
	if(l==NULL || l->tamanho==0 || l->imprime==NULL)
		return;
	celula_t *aux = l->cabeca;
	while(aux != NULL) {
		l->imprime(aux->dado);
		aux = aux->prox;
	}
}

int lista_insere_ordenado(lista_t *l, const void *elem) {
	if(l==NULL || elem == NULL) 
		return 0;
	if(l->compara == NULL) 
		return lista_insere_proximo(l,l->cauda,elem);
	int resultado;	
	celula_t *aux = l->cabeca;
	while (aux!=NULL) {
		resultado = l->compara(elem,aux->dado);
		if (resultado == 0)
			return lista_insere_proximo(l,aux,elem);
		if(resultado == -1)
			return lista_insere_anterior(l,aux,elem);
		aux = aux->prox;
	}
	return lista_insere_proximo(l,l->cauda,elem);
}		

celula_t *lista_busca_recursiva(lista_t *l, const void *elem, celula_t *c) {
	if (l==NULL || elem==NULL || c==NULL || l->tamanho==0)
		return NULL;
	if(c->dado == elem)
		return c;		
	return lista_busca_recursiva(l,elem,c->prox);
}

lista_t *lista_separa(lista_t *l, const void *elem) {
	if(l==NULL || elem==NULL)
		return NULL;
	celula_t *node = lista_busca_recursiva(l,elem,l->cabeca);
	if(node == NULL || node==l->cauda)
		return NULL;
	lista_t *l2 = lista_cria(l->imprime,l->destruir,l->compara);
	node->prox->ant = NULL;
	l2->cabeca = node->prox;
	node->prox = NULL;
	l2->cauda  = l->cauda;
	l->cauda   = node;
	int i=0;	
	celula_t *aux = l2->cabeca;	
	while(aux!=NULL) {
		aux = aux->prox;
		i++;
	}
	l2->tamanho = i;
	l->tamanho  = l->tamanho - i;
	return l2;
}
	

lista_t *lista_concatena_e_destroi(lista_t **l1, lista_t **l2) {
	if((*l1) == NULL || (*l2)==NULL)
		return NULL;
	if((*l1)->tamanho == 0 && (*l2)->tamanho == 0)
		return NULL;
	if((*l2)->tamanho == 0) {
		lista_t *l = lista_cria((*l1)->imprime,(*l1)->destruir,(*l1)->compara);
		l->cabeca = (*l1)->cabeca;
		l->cauda  = (*l1)->cauda;
		l->tamanho = (*l1)->tamanho;
		(*l1)->cabeca = NULL;
		(*l1)->cauda  = NULL;
		lista_destroi(l1);
		lista_destroi(l2);   
		return l;	
	}
	if((*l1)->tamanho != 0 && (*l2)->tamanho != 0) {
		lista_t *l = lista_cria((*l1)->imprime,(*l1)->destruir,(*l1)->compara);
		(*l1)->cauda->prox = (*l2)->cabeca;
		(*l2)->cabeca->ant = (*l1)->cauda;
		l->cabeca 		= (*l1)->cabeca;
		l->cauda		= (*l2)->cauda;
		l->tamanho      = ((*l1)->tamanho + (*l2)->tamanho);
		(*l2)->cabeca = NULL;
		(*l2)->cauda  = NULL;
		(*l1)->cabeca = NULL;
		(*l1)->cauda  = NULL;
		lista_destroi(l1);
		lista_destroi(l2);   
		return l;
	}
	else {
		lista_t *l = lista_cria((*l2)->imprime,(*l2)->destruir,(*l2)->compara);
		l->cabeca = (*l2)->cabeca;
		l->cauda  = (*l2)->cauda;
		l->tamanho = (*l2)->tamanho;
		(*l2)->cabeca = NULL;
		(*l2)->cauda  = NULL;
		lista_destroi(l1);
		lista_destroi(l2);   
		return l;
	}	
}

celula_t *busca_celula(lista_t *l, unsigned int posicao) {
	if(l==NULL) {
		
		return NULL;
	}
	
	if(posicao >= l->tamanho) {
		return l->cauda;
	}

	celula_t* aux=l->cabeca;
	for(int i=0;i<posicao;i++)
		aux = aux->prox;
	return aux;
}

unsigned int busca_posicao(lista_t *l, celula_t *c) {
	if(l==NULL || c==NULL) {
		printf("Buffer vazio! Erro na funcao busca_posicao!\n");
		return 0;
	}
	celula_t *aux = l->cabeca;
	int i=0;
	while (aux != c) {
		aux = aux->prox;
		i++;
	}
	return i;
}
