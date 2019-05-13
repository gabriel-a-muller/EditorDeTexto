#include "editor.h"

FILE *abre_arquivo(const char *arquivo) {
	if(arquivo==NULL)
		return NULL;	
	FILE *document;
	document = fopen(arquivo,"r");
	if (document == NULL)
		return NULL;
	else 
		return document;
}

FILE *abre_arquivo_w(const char *arquivo) {
	if(arquivo==NULL)
		return NULL;
	FILE *document;
	document = fopen(arquivo,"w");	
	if (document == NULL)
		return NULL;
	else
		return document;
}

int fecha_arquivo(FILE *arq) {
	if(arq==NULL)
		return 1;
	return fclose(arq);
}

int compara(const void *str1, const void *str2) {
	if(str1==NULL || str2==NULL)
		return -1;	
	return strcmp(str1,str2); //vai retornar 0 caso seja igual.
}

void libera(void *dado) {  //verificar
	if(dado==NULL)
		return;
	free(dado);
	return;
}

void imprime (const void *dado) {  //verificar
	if(dado==NULL)
		return;	
	printf("%s",(char*)dado);
	//printf("\n");
	return;
}

char *leitura(FILE *arquivo) {   //a posicao do arquivo vai ser salva??? como posso inserir no buffer todas as linhas???
	if (arquivo==NULL)
		return NULL;
	char *str = (char*) malloc(sizeof(char)*33);
	if(str==NULL)
		return NULL;
	int posicao = 0;
	int tam = 0;
	while (1) {
		fgets(str+posicao, 33, arquivo);
		tam = strlen(str+posicao);
		if(tam==32) {
			if(str[31+posicao] == '\n') {
				str[31+posicao]='\0';
				break;
			} 
			posicao+=32;
			char *tmp = (char*)realloc(str,posicao+33);
			if(tmp==NULL) {
				free(str);
				//str=NULL;
				return NULL;
			}
		str = tmp;
		}
		else 
			break;					

	}
	//printf("%d",tam+33);
	return str;
}

void funcao_h_ajuda() {
	printf("----------------------------------------------------------------------------------------------:\nAJUDA:\n");
	printf("R: Lê um arquivo com o nome informado pelo usuario e insere no editor de texto.\n"
   "Atenção: Toda informação no editor sera descartada.\n\n");
	printf("W: Escreve o conteudo do editor em um arquivo com o nome informado pelo usuario.\n\n");
	printf("I: Insere uma nova linha especificada pelo usuario. Primeiramente informe a posição, em seguida, digite a linha a ser inserida.\n\n");
	printf("D: Apaga a linha corrente e move para a próxima linha.\n\n");
	printf("F: Procura uma linha que contenha uma string informada pelo usuario.\n\n");
	printf("L: Mostra o tamanho de caracteres da linha atual e a quantidade de linhas existentes no editor.\n\n"); 
	printf("C: Troca a linha fornecida pelo usuario por um texto tambem fornecido pelo usuario.\n\n");
	printf("Q: finaliza o editor.\n\n");
	printf("N: Avança para a próxima linha.\n\n");
	printf("P: Volta para a linha anterior.\n\n");
	printf("B: Início: vai para a primeira linha.\n\n");
	printf("E: Fim: vai para a ultima linha.\n\n");
	printf("G: Vai para uma linha fornecida pelo usuario.\n\n");
	printf("S: Substitui uma linha escolhida pelo usuario com a linha atual.\n\n");
	printf("V: Visualiza todo o conteudo do editor na tela.\n\n");
	//printf("P.S: Sempre que algum comando necessite de uma linha inserida pelo usuario, deve ser digitado o numero da linha 		desejada.\n");
	printf("----------------------------------------------------------------------------------------------\n");
}

int numero_de_char(char *string){
	if(string==NULL) {
		printf("LINHA NULA!\n");	
		return 0;
	}
	else {
		int tam = 0;
		if(strlen(string) != 0)
			tam = (strlen(string) - 1);
		return tam;
	}
}

linha_t *linha_cria() {
	linha_t *l = (linha_t*) malloc(sizeof(linha_t));
	if(l==NULL)
		return NULL;

	l->linha 	= NULL;
	l->posicao  = 0;
	l->num_char = 0;
	return l;
}

void linha_destroi(linha_t **l) {
	if(l==NULL || *l==NULL)
		return;
	//if((*l)->linha!=NULL)
		//free((*l)->linha);
	free(*l);
	*l=NULL;
	return;
}

celula_t *funcao_r_leitura(unsigned int *posicao, lista_t *buffer) {
	if(posicao==NULL || buffer ==NULL)
		return NULL;
	char arquivo[100];
	arquivo[0] = '\0';
	printf("Insira o nome do arquivo a ser lido: ");
	scanf("%s",arquivo);
	FILE *doc;
	doc = abre_arquivo(arquivo);
	fgetc(doc);
	if(feof(doc)) {
		printf("Arquivo esta vazio!\n");
		return NULL;
	}
	rewind(doc);	
	unsigned int pos=0;
	char *string=NULL;
	while(!feof(doc)) {
		string = leitura(doc);
		lista_insere_posicao(buffer,pos,string);
		pos++;
		}
	*posicao = pos;
	return lista_cabeca(buffer);
}

int funcao_g(lista_t *l,linha_t *cursor) {
	if(cursor->linha==NULL){
		printf("EDITOR NULO!\n");
		return 0;
	}
	else {
		unsigned int x;
		printf("Numero de l: ");
		scanf("%d",&x);
		if(x>lista_tamanho(l) || x==0) {
			printf("Linha buscada nao existente!\n");
			return 0;
		}		
		else {
			x--;
			cursor->linha 	 = busca_celula(l,x);
			cursor->posicao	 = x;
			cursor->num_char = numero_de_char(lista_dado(cursor->linha));
			return 1;
		}
	}
}

int main () {


	lista_t *buffer = lista_cria(imprime,libera,compara);
	char operacao[16];
	operacao[0]='\0';
	printf("Digite um comando para entrada (H ou ? para ajuda): ");
	scanf("%s",operacao);
	linha_t *cursor = linha_cria();
	while (operacao[0] != 'Q' && operacao[0] != 'q') {
	
		if(operacao[0] == 'h' || operacao[0] == 'H' || operacao[0] == '?') {
			funcao_h_ajuda();
		}
		
		if(operacao[0] == 'v' || operacao[0] == 'V') {
			if(cursor->linha == NULL)
				printf("Editor vazio!\n");
			lista_imprime(buffer);			
		}

		if(operacao[0] == 'r' || operacao[0] == 'R') {
			char x[7];
			x[0] = '\0';
			printf("Voce esta prestes a descartar todo conteudo do editor, tem certeza? (S/N): ");
			scanf("%s",x);
			if(x[0]=='S' || x[0] == 's') {
				unsigned int posicao;
				lista_destroi(&buffer);
				lista_t *buffer2  = lista_cria(imprime,libera,compara);
				cursor->linha 	 = funcao_r_leitura(&posicao,buffer2);
				cursor->posicao  = 0;
				cursor->num_char = numero_de_char(lista_dado(cursor->linha));
				buffer = buffer2;	
			}
		}

		if(operacao[0]=='i' || operacao[0] == 'I') {
			unsigned int posicao=0;
			char *str;
			printf("Digite a posicao que deseja inserir a nova linha: ");			
			scanf("%d",&posicao);
			getchar();
			posicao--;
			printf("l:");
			str = leitura(stdin); //VERIFICAR COM SAMUEL;
			lista_insere_posicao(buffer,posicao,str);
			//printf("Resultado da insere: %d\n",x);
			celula_t *linha = busca_celula(buffer,posicao);
			//printf("%s",str);
			//printf("%p\n",linha);
			if(posicao > lista_tamanho(buffer)) {
				posicao = lista_tamanho(buffer) - 1;
			}
			cursor->linha = linha;
			cursor->posicao = posicao;
			//printf("%p\n",lista_dado(cursor->linha));
			cursor->num_char = numero_de_char(lista_dado(cursor->linha));
		}

		if(operacao[0]=='n' || operacao[0] == 'N') {
			if(cursor->linha==NULL)
				printf("EDITOR NULO!\n");
			if(lista_proximo(cursor->linha)==NULL)
				printf("Linha final atingida.\n");
			else {
				cursor->linha = lista_proximo(cursor->linha);
				cursor->posicao++;
				cursor->num_char = numero_de_char(lista_dado(cursor->linha));
			}
		}
			
		if(operacao[0]=='p' || operacao[0] == 'P') {
			if(cursor->linha==NULL)
				printf("EDITOR NULO!\n");
			if(lista_anterior(cursor->linha)==NULL)
				printf("Linha inicial atingida.\n");
			else {
				cursor->linha = lista_anterior(cursor->linha);
				cursor->posicao--;
				cursor->num_char = numero_de_char(lista_dado(cursor->linha));
			}	
		}

		if(operacao[0]=='b' || operacao[0] == 'B') {
			if(cursor->linha==NULL)
				printf("EDITOR NULO!\n");
			else {
				cursor->linha = lista_cabeca(buffer);
				cursor->posicao=0;
				cursor->num_char = numero_de_char(lista_dado(cursor->linha));
			}
		}

		if(operacao[0]=='e' || operacao[0] == 'E') {
			if(cursor->linha==NULL)
				printf("EDITOR NULO!\n");
			else {
				cursor->linha 	 = lista_cauda(buffer);
				cursor->posicao	 = lista_tamanho(buffer)-1;
				cursor->num_char = numero_de_char(lista_dado(cursor->linha));
			}
		}	
			
		if(operacao[0]=='g' || operacao[0] == 'G') {
			funcao_g(buffer,cursor);
		}

		if(operacao[0]=='d' || operacao[0] == 'D') {	
			char x[7];
			x[0] = '\0';
			printf("Voce esta prestes a descartar a linha corrente, tem certeza? (S/N): ");
			scanf("%s",x);
			if(x[0]=='S' || x[0] == 's'){
				char *elem;
				celula_t *aux;
				if(lista_eh_cauda(buffer, cursor->linha)==1){
					aux = lista_anterior(cursor->linha);
					cursor->posicao--;
				}
				else { //(lista_eh_cabeca(buffer,cursor->linha)==1 && lista_eh_cauda(buffer, cursor->linha)!=1)
					aux = lista_proximo(cursor->linha);
				}
		
				if(lista_remove(buffer,cursor->linha,(void**)&elem)==1) {
					libera(elem); // ta certo?????					
					cursor->linha = aux;
					cursor->num_char = numero_de_char(lista_dado(cursor->linha));
				}
				else 
						printf("ERRO NA OPERACAO 'D', FALHOU EM REMOVER A LINHA!\n");
			}
		}

		if(operacao[0]=='C' || operacao[0] == 'c') {
			char *string,*substituta;	
			printf("Digite a string a ser substituida: ");
			getchar();
			string = leitura(stdin);
			int tam = strlen(string);
			if(string[tam-1] == '\n') {
				string[tam-1] = '\0';
			}
			char *linha = lista_dado(cursor->linha);
			char *aux = NULL;
			aux = strstr(linha,string);
			if (aux != NULL) {
				printf("Digite o texto substituto: ");
				//getchar();
				substituta = leitura(stdin);
				printf("Substituta: %s",substituta);
				tam = strlen(substituta);
				if(substituta[tam-1] == '\n') {
					substituta[tam-1] = '\0';
				}
				size_t novo_tam = strlen(linha) - strlen(string) + strlen(substituta);
				char *nova_string = (char*)malloc(novo_tam + 1);
				if (nova_string == NULL) {
					printf("Falha na alocacao de memoria 'nova_string'\n");	
					return 0;				
				}
				//copiando a parte da antiga string ate a substring
				memcpy(nova_string, linha, aux - linha);
				// copiando a substring
				memcpy(nova_string + (aux - linha), substituta, strlen(substituta));
				// copiando o restante da antiga substring
				strcpy(nova_string + (aux - linha) + strlen(substituta), aux + strlen(string));
				printf("\n");
				printf("Antiga: %s\nNova: %s", linha, nova_string);
				char *elem;
				if(lista_remove(buffer,cursor->linha,(void**)&elem)==1) {
					libera(elem);
					lista_insere_posicao(buffer,cursor->posicao,(const void*)nova_string);
					cursor->linha = busca_celula(buffer,cursor->posicao);
					cursor->num_char = numero_de_char(lista_dado(cursor->linha));
				}
			}
			else 
				printf("Substring nao encontrada!\n");			
		}	
		


		if(operacao[0]=='F' || operacao[0] == 'f') { //as vezes ao digitar o comando F o programa finaliza.
			if(cursor->linha==NULL)
				printf("EDITOR NULO!\n");
			else {			
				char *string;
				//char string[100];
				//string[0] = '\0';
				printf("Digite a string a ser buscada: ");
				getchar();
				string = leitura(stdin);
				char *aux = NULL;
				int tam = strlen(string);
				//printf("Tamanho da string: %d\n", tam);
				if(string[tam-1] == '\n') {
					string[tam-1] = '\0';
					tam = strlen(string);
					//printf("Tamanho atualizado da string: %d\n", tam);
				}
				aux = strstr(lista_dado(cursor->linha),string);
				while(aux==NULL && cursor->linha != lista_cauda(buffer)) {
					cursor->linha = lista_proximo(cursor->linha);
					aux = strstr(lista_dado(cursor->linha),string);
					cursor->posicao++;
					//printf("%p\n",aux);
				}			
				if(cursor->linha==lista_cauda(buffer)) {
					printf("Substring nao encontrada!\n");
					cursor->linha = lista_cabeca(buffer);
					cursor->posicao = 0;
					cursor->num_char = numero_de_char(lista_dado(cursor->linha));
				}
				else {
					printf("Linha que contem a substring: %d\n", (cursor->posicao) + 1);
					printf("l: %s", (char*)lista_dado(cursor->linha));
					//printf("Posicao da substring: %d\n", aux);
					cursor->num_char = numero_de_char(lista_dado(cursor->linha));
				}
				free(string);
			}
		}



			/*unsigned int posicao=0;
			char *str;			
			//scanf("Digite a posicao que deseja inserir a nova linha: %d\n",&posicao);
			//posicao--;
			printf("Insira a linha a ser buscada:");
			str = leitura(stdin); //VERIFICAR COM SAMUEL;			
			cursor->linha 	 = lista_busca_recursiva(buffer,str,);
			cursor->posicao  = busca_posicao(buffer,cursor->linha);
			cursor->num_char = numero_de_char(lista_dado(cursor->linha));
		}*/
			
		if(operacao[0] == 'S' || operacao[0] == 's'){
			//unsigned int x;
			//scanf("Numero da linha a ser substituida: %d", &x);	
			int t = funcao_g(buffer,cursor);
			if(t==1) {
				printf("Linha encontrada: %s\n", (char*)lista_dado(cursor->linha));
				char d[4];
				d[0] = '\0';
				printf("Tem certeza que queres substituir esta linha? (S/N): ");			
				scanf("%s",d);
				getchar();
				if(d[0]=='S' || d[0] == 's') {
					char *str;
					printf("linha substituta: ");
					str = leitura(stdin);
					int i = lista_insere_proximo(buffer,cursor->linha,str);
					if(i!=1) {
						printf("Falha ao inserir valor! (Funcao S)\n");
						return 0;
					}
					char *elem;
					int j = lista_remove(buffer,cursor->linha,(void*)&elem);
					if(j!=1) {
						printf("Falha ao remover a celula! (funcao S)\n");
						return 0;
					}
					libera(elem);
					cursor->linha = lista_busca_recursiva(buffer,str,lista_cabeca(buffer));
					cursor->posicao = busca_posicao(buffer,cursor->linha);
					cursor->num_char = numero_de_char(lista_dado(cursor->linha));
				}
			}
		}

		if(operacao[0] == 'W' || operacao[0] == 'w'){
			char arquivo[100];
			arquivo[0] = '\0';
			printf("Digite o nome do arquivo a ser criado: ");
			scanf("%s", arquivo);      	//&?????
			FILE *doc = abre_arquivo_w(arquivo);
			if(doc!=NULL) {
				celula_t *aux = lista_cabeca(buffer);
				while(aux!=NULL) {
					fputs(lista_dado(aux),doc);
					aux = lista_proximo(aux);
				}
			}
			fecha_arquivo(doc);
		}
		
		if(operacao[0]=='L' || operacao[0] == 'l') {
			printf("\n");
			printf("Numero de characteres da linha: %d\n", cursor->num_char);
			printf("Numero de linhas: %d\n", lista_tamanho(buffer));
			printf("Posicao da linha corrente: %d\n", (cursor->posicao) + 1);
			if(strlen(lista_dado(cursor->linha)) == 0)
				printf("Linha corrente: \n");
			else 
				printf("Linha corrente: %s", (char*)lista_dado(cursor->linha));
			printf("-------------------------------------------------------------------------------------\n");
			printf("\n");
		}	
		
		else {		
			int n = lista_tamanho(buffer);
			if(n == 0) 
				cursor->posicao = 0;
			printf("\n");
			//printf("-------------------------------------------------------------------------------------\n");
			printf("Linha corrente: %d\n",(cursor->posicao)+1);
			if(n!= (-1))		
				printf("Quantidade de linhas: %d\n", n);
			else 
				printf("Quantidade de linhas: 0\n");
			printf("-------------------------------------------------------------------------------------\n");
			printf("\n");		
		}
		operacao[0] = '\0';
		printf("Digite um comando para entrada (H ou ? para ajuda): ");
		scanf("%s",operacao);
	}
//	printf("Saiu do while q!\n");
	lista_destroi(&buffer);
	linha_destroi(&cursor);
	return 0;
	}

