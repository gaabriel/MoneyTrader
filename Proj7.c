#include <stdio.h>
#include <stdbool.h>

void tela_principal();
void menu_inicial();
void dispara_funcao();
void insere_usuario();
void remove_usuario();
void insere_troca();
void remove_troca();
void todas_trocas();
void todos_usuarios();
void ver_balanco();
void ver_vinculos();
void buscar_usuario();
void ultimas_trocas();
void encerrar_programa();

void load_users();
void save_users();
void load_trades();
void save_trades();

void insere_user();
void unico_user();
void primeiro_user();
void adiciona_user();
void mostra_user();
int deleta_user();
void deleta_historico();
int conta_users();

void insere_trade();
int verifica_user();
void primeira_trade();
void adiciona_trade();
void mostra_trade();
int deleta_trade();
void trocas_entre();
int conta_trades();

int balanco_credor();
int balanco_devedor();
int nome_do_id();
void balanco_total();

int numero_usuarios();
int nomeia_vinculo();
int calcular_vinculo();

struct st_user {
	int userid;
	int userfullname;
	struct st_user *prox;
}*usernodo;
struct st_trade {
	int tradefrom;
	int tradeto;
	int tradevalue;
	struct st_trade *subseq;
}*tradenodo;
//estruturas iniciais de lsita e ponteiros de refencia

struct arvore {
	int registro;
	struct arvore* esq;
	struct arvore* dir;
};
typedef struct arvore arvore;
//estrutura da arvore

struct userbase_st {
	int basenum;
	int basenome;
};
struct tradebase_st {
	int basecredor;
	int basedevedor;
	int basevalor;
	int baselinha;
};
//estruturas de leitura e escrita dos registros

arvore* cria_nodo();
arvore* insere_nodo();
int id_do_nome();
bool busca_nodo();
int achou_nodo = 0;//escopo do sim ou nao da busca da arvore utilixado é global inicialmente zero

int main() {//carrega dados dos arquivos de registro e chama o menu
	load_users();
	load_trades();
	tela_principal();
}
void tela_principal() {//mostra tela principal e serve de base para a selecao atraves da variavel menu que é modificado na funcao e encaminha o processamento da escolha
	int menu;
	menu_inicial(&menu);
	dispara_funcao(menu);
}
void menu_inicial(int *ptrmenu) {//mostra opcoes e gerencia o transito do software, garantindo que opere corretamente. ponteiro do menu é modificado para uso em sua funcao de origem
	int menu_opt;
	printf("\n********************************************************\nEscolha uma opcao:\n  1.Inserir usuario\t  2.Remover usuario\n  3.Inserir transacao\t  4.Remover transacao\n  5.Ver transacoes\t  6.Listar usuarios\n  7.Ver balanco\t\t  8.Ver vinculos\n  9.Procurar usuario\t  10.Trocas recentes\n  0.Encerrar programa\t\t\t\t");
	scanf("%d",&menu_opt);
	while (menu_opt>10 || menu_opt<0){//se opcao invalida
		printf(">>>> opcao invalida, escolha novamente: ");
		scanf("%d",&menu_opt);
	}
	*ptrmenu = menu_opt;//registra a opcao desejada
}
void dispara_funcao(int seletor) {//recebe a escolha e dispara a respectiva funcao
	switch(seletor){
		case 1:
			insere_usuario();
			break;
		case 2:
			remove_usuario();
			break;
		case 3:
			insere_troca();
			break;
		case 4:
			remove_troca();
			break;
		case 5:
			todas_trocas();
			break;
		case 6:
			todos_usuarios();
			break;
		case 7:
			ver_balanco();
			break;
		case 8:
			ver_vinculos();
			break;
		case 9:
			buscar_usuario();
			break;
		case 10:
			ultimas_trocas();
			break;
		default:
			encerrar_programa();
			break;
	}
}
void insere_usuario() {//pede dados do usuario, verifica se é único e os repassa pra executar a insercao de fato
	int id,nome;
	printf("\n[tecle 0 no usuario para cancelar a operacao]");
	printf("\n\n    Id para o usuario: \t\t");
	scanf("%d",&id);
	unico_user(usernodo,id);//verifica se usuario é unico
	printf("    Nome completo do usuario: \t");
	scanf("%d",&nome);
	insere_user(id,nome);//encaminha insercao
	tela_principal();
}
void remove_usuario() {//pergunta qual usuario sera apagado (se existir), recebe resposta da funcao de apagar se teve sucesso ou ao
	int id;
	if(usernodo==NULL) printf("\n>>> Lista vazia\n");//se vazia
	else {
		printf("\n[tecle 0 no usuario para cancelar a operacao]");
		printf("\n\n    Insira um id para ser apagado: \t");
		scanf("%d",&id);
		if(deleta_user(id)) printf(">>> %d e seus dados apagado com sucesso\n",id);//se sucesso na solicitacao
		else printf(">>> %d nao encontrado na lista\n",id);
	}
	tela_principal();
}
void insere_troca() {//pergunta dados da transacao, verifica validade deles e os encaminha pra insercao
	int credor,devedor,valor;
	printf("\n[tecle 0 no credor, devedor ou valor para cancelar a operacao]");
	printf("\n\n    username do credor: \t");
	scanf("%d",&credor);
	if (verifica_user(usernodo,credor)==0){//se valido
		printf(">>> credor nao existe\n");
		insere_troca();
	}
	printf("    username do devedor: \t");
	scanf("%d",&devedor);
	if (verifica_user(usernodo,devedor)==0) {//se valido
		printf(">>> devedor nao existe\n");
		insere_troca();
	}
	printf("    valor do emprestimo: \t");
	scanf("%d",&valor);
	if (valor==0) {//se valido
		printf(">>> operacao cancelada\n");
		tela_principal();
	}
	while(valor<0) {//se negativo
		printf("\n>>>  valor deve ser positivo: ");
		scanf("%d",&valor);
	}
	insere_trade(credor,devedor,valor);//encmainha insercao
	tela_principal();
}
void remove_troca() {//pergunta os usuarios envolvidos, lista trocas entre eles e pergunta qual operacao sera excluida
	int credor,devedor,valor;
	if(tradenodo==NULL) printf("\n>>> Lista vazia\n");
	else {
		printf("\n[tecle 0 no credor ou devedor para cancelar a operacao]\n");
		printf("\n    credor: \t");
		scanf("%d",&credor);
		if (verifica_user(usernodo,credor)==0) {//se valido
			printf(">>> credor nao existe\n");
			remove_troca();
		}
		printf("    devedor: \t");
		scanf("%d",&devedor);
		if (verifica_user(usernodo,devedor)==0) {//se valido
			printf(">>> devedor nao existe\n");
			remove_troca();
		}
		trocas_entre(tradenodo,credor,devedor);//pede pra listar as relacoes entre eles
		printf("\n\n[tecle 0 no credor ou devedor para cancelar a operacao]\n");
		printf("\n  escolha o valor da troca a ser removida: ");
		scanf("%d",&valor);
		if (valor==0) {//se cancelado
			printf(">>>operacao cancelada\n");
			tela_principal();
		}
		if(deleta_trade(credor,devedor,valor,tradenodo)) printf("\n>>> $%d de %d para %d\tapagado com sucesso\n",valor,credor,devedor);//se sucesso na escolha da operacao a ser apagado
		else printf("\n>>> $%d de %d para %d\tnao encontrado na lista\n",valor,credor,devedor);
	}
	tela_principal();
}
void todas_trocas() {//conta e lista todas as trocas
	if(tradenodo==NULL) printf("\n>>> Lista vazia\n");//vazia
	else {
		printf("\n>>> transacoes na lista:\n\tcredor\tdevedor\tvalor\n");
		mostra_trade(tradenodo);//chama funcao de exibicao total
	}
	printf("\n--> sao %d trocas\n",conta_trades(tradenodo));
	tela_principal();
}
void todos_usuarios() {//conta e lista todos os usuarios
	if(usernodo==NULL) printf("\n>>> Lista vazia\n");//vazia
	else {
		printf("\n>>> usuarios cadastrados:\n\tusuario\t\tnome\n");
		mostra_user(usernodo);//chama funcao de exibicao total
	}
	printf("\n--> sao %d users\n",conta_users(usernodo));
	tela_principal();
}
void ver_balanco() {//lista operacoes do usuario e calcula o "saldo"
	int id;
	printf("\n[tecle 0 no usuario para cancelar a operacao]");
	printf("\n\n    Solicitar balanco de que usuario? \t");
	scanf("%d",&id);
	if (verifica_user(usernodo,id)==0) {//se entrada invalida
		printf(">>> usuario nao existe\n");
		ver_balanco();
	}
	balanco_total(tradenodo,id,balanco_credor(tradenodo,id)-balanco_devedor(tradenodo,id));//solicita execucao das operacoes d e balanco
	tela_principal();
}
void ver_vinculos() {//gera matriz de adjecencias em que mostra o "saldo" entre usuarios
	int i,j,k;
	int n_usuarios = numero_usuarios(usernodo);
	if(tradenodo==NULL){
		printf("\n>>> Lista de transacoes vazia\n");
		tela_principal();
	}
	int matriz[n_usuarios][n_usuarios];//inicia matriz
	for (i=0; i<n_usuarios; i++){
		for (j=0; j<n_usuarios; j++) {//preenche matriz
			matriz[i][j] = calcular_vinculo(tradenodo,i,j,usernodo);
		}
	}
	printf("\n=================== VINCULOS ===================\n");//fazz o llop de exibicao
	for (k=0; k<n_usuarios; k++) printf("\t%d",nomeia_vinculo(k,usernodo));
	for (i=0; i<n_usuarios; i++){
		printf("\n\n%d",nomeia_vinculo(i,usernodo));
		for (j=0; j<n_usuarios; j++) {
			printf("\t%d",matriz[i][j]);
		}
	}
	printf("\n");
	tela_principal();
}
void buscar_usuario() {//passa a lista de usuarios para a arvore, pergunta e encaminha pedido pra busca
	struct arvore* raiz = NULL;//garante arvore vazia
	struct st_user *nodo_m;
	nodo_m = usernodo;
	if(nodo_m==NULL) printf("\n>>> Lista de usuarios vazia\n");
	else {//cria arvore caso existam usuarios
		while(nodo_m!=NULL) {//loop de preenchimento
			raiz = insere_nodo(raiz,nodo_m->userfullname);
			nodo_m = nodo_m->prox;
		}
	}
	int nome;
	printf("\n[tecle 0 no usuario para cancelar a operacao]");
	printf("\n\n    Qual o nome a ser procurado? ");
	scanf("%d",&nome);
	if(nome==0) {//se cancelado);
		printf(">>> operacao cancelada\n");
		free(raiz);
		tela_principal();
	}
	if(nome!=0){//se pedido é valido
		if(busca_nodo(raiz,nome)==true) printf(">>> Busca realizada com sucesso\n");//se encontrou resultados
		else {//se nao teve sucesso
			printf(">>> Nome: %d nao encontrado\n",nome);
			buscar_usuario();
		}
	}
	tela_principal();
}
void ultimas_trocas() {//passa a lista de transacoes pra matriz, conta e exibe as ultimas dez trocas primeiro
	struct st_trade *nododez;
	int k=0;
	int num_trades = conta_trades(tradenodo);
	if(num_trades==0) {//se vazia
		printf("\n>>> Lista vazia\n");
		tela_principal();
	}
	int troca[num_trades][3];
	nododez = tradenodo;
	while(nododez!=NULL) {//cria amtriz para dos as transacoes do sistema
		troca[k][0] = nododez->tradefrom;
		troca[k][1] = nododez->tradeto;
		troca[k][2] = nododez->tradevalue;
		nododez = nododez->subseq;
		k++;
	}
	printf("\n============== dez mais recentes ==============\n\tpos\tcredor\tdevedor\tvalor\n");
	int foidez = k-10;
	int ranking=0;
	while(k>0){//exibe a partir das mais recentes, quando exibiu 10 freia loop
		if(foidez==k) break;
		k--;
		ranking++;
		printf("\t%d.\t%d\t%d\t%d\n",ranking,troca[k][0],troca[k][1],troca[k][2]);
	}
	tela_principal();
}
void encerrar_programa() {//salva as listas nos respectivos arquivos e encerra a sessao
	save_users(usernodo);
	save_trades(tradenodo);
	printf("\nopcao 0, o programa sera encerrado...\n");
	exit(1);
}

/****************************************************************************************************/

void load_users(){//prepara a leitura da base de usuarios e os re-insere no sistema
  FILE * file;
	int anterior=NULL;
	struct userbase_st *leitura=malloc(sizeof(struct userbase_st));
	file= fopen("userbase.bin", "rb");//inicia leitura
	//printf("basenum\tbasenome\n",leitura->basenum,leitura->basenome);
	if (file != NULL) {
		while(1){//enquanto tiver itens a serem lidos, os lê e insere de novo no sistema
			fread(leitura, sizeof(struct userbase_st), 1, file);
			if (leitura->basenum==anterior) break;//se esta recomeçado a leitura do arquivo freia a leitura
			anterior=leitura->basenum;
			insere_user(leitura->basenum,leitura->basenome);
			//printf("%d \t %d\n",leitura->basenum,leitura->basenome);
		}
	}
	fclose(file);
	free(leitura);
}
void save_users(struct st_user *nodo_m){//apaga o arquivo atual substituindo por um vazio, e acrescenta um a um a lista atual
	FILE * file;
	struct userbase_st *escreve=malloc(sizeof(struct userbase_st));
	file= fopen("userbase.bin", "wb");//apaga arquivo salvo anterior e cria um em branco
	fclose(file);
	nodo_m=usernodo;
	if(nodo_m!=NULL) {
		//printf("\n>>> usuarios a serem salvos:\n\tusuario\t\tnome\n");
		while(nodo_m!=NULL) {
			//printf("\t%d\t\t%d\n",nodo_m->userid,nodo_m->userfullname);
			escreve->basenum = nodo_m->userid;
			escreve->basenome = nodo_m->userfullname;
			file= fopen("userbase.bin", "ab");//instrucao para adicionar linha ao final do arquivo
			if (file != NULL) {
				fwrite(escreve, sizeof(struct userbase_st), 1, file);
				fclose(file);
			}
			nodo_m=nodo_m->prox;
		}
	} else remove("userbase.bin");//se nada pra preencher, apaga arquivo de registro
	free(escreve);
}
void load_trades(){//acessa o registro de trocas e os re-insere
  FILE * file;
	int num_anterior=NULL;
	struct tradebase_st *check=malloc(sizeof(struct tradebase_st));
	file= fopen("tradebase.bin", "rb");//inicia leitura
	//printf("linha\tcred\tdeve\tvalor\n");
	if (file != NULL) {
		while(1){//enquanto tiver itens a serem lidos, os lê e insere de novo no sistema
			fread(check, sizeof(struct tradebase_st), 1, file);
			if (check->baselinha==num_anterior) break;//se esta recomeçado a leitura do arquivo freia a leitura
			else {
				//printf("%d.\t%d\t%d\t%d\n",check->baselinha,check->basecredor,check->basedevedor,check->basevalor);
				num_anterior=check->baselinha;
				insere_trade(check->basecredor,check->basedevedor,check->basevalor);
			}
		}
	}
	fclose(file);
	free(check);
}
void save_trades(struct st_trade *nodo_t){//apaga o arquivo atual substituindo por um vazio, e acrescenta um a um a lista atual
	FILE * file;
	int conta=0;
	struct tradebase_st *anota=malloc(sizeof(struct tradebase_st));
	file= fopen("tradebase.bin", "wb");//apaga arquivo salvo anterior e cria um em branco
	fclose(file);
	nodo_t=tradenodo;
	if(nodo_t!=NULL) {
		//printf("\n>>> trocas a serem salvas:\n\tfrom\tto\tvalor\tpos\n");
		while(nodo_t!=NULL) {
			//printf("\t%d\t%d\t%d\t%d\n",nodo_t->tradefrom,nodo_t->tradeto,nodo_t->tradevalue,conta+1);
			anota->basecredor=nodo_t->tradefrom;
			anota->basedevedor=nodo_t->tradeto;
			anota->basevalor=nodo_t->tradevalue;
			anota->baselinha=conta+1;
			file= fopen("tradebase.bin", "ab");//instrucao para adicionar linha ao final do arquivo
			if (file != NULL) {
				fwrite(anota, sizeof(struct tradebase_st), 1, file);
				fclose(file);
			}
			conta++;
			nodo_t=nodo_t->subseq;
		}
	} else remove("tradebase.bin");//se nada pra preencher, apaga arquivo de registro
	free(anota);
}

/****************************************************************************************************/

int numero_usuarios(struct st_user *nodo_m){//conta e retorna o numero de usuarios
	nodo_m = usernodo;
	int n_usuarios = 0;
	if(nodo_m==NULL) return 0;//se vazia
	while(nodo_m!=NULL) {//percorre, conta e reotrna numero total
		n_usuarios++;
		nodo_m = nodo_m->prox;
	}
	return n_usuarios;
}
int nomeia_vinculo(int nome,struct st_user *nodo_m){//passa a ordem do elemento na matriz para seu id
	nodo_m = usernodo;
	int posicao = 0;
	while(nodo_m!=NULL) {//pega o registro real do item e o retorna pra ilustrar o cabecalho da matriz
		if(posicao==nome) {
			nome = nodo_m->userid;
			break;//se ja encontrou freia o loop
		}
		posicao++;
		nodo_m = nodo_m->prox;
	}
	return nome;
}
int calcular_vinculo(struct st_trade *nodo_t,int from,int to,struct st_user *nodo_m){//recebe dois usuarios, verifica todas as transacoes entre eles e retorna o saldo final
	int saldo = 0;
	nodo_t = tradenodo;
	nodo_m = usernodo;
	int percorrefrom = 0;
	while(nodo_m!=NULL) {
		if (percorrefrom==from) {//se posicao desejada é o item a ser visto, guarda e freia loop
			from = nodo_m->userid;
			break;
		}
		percorrefrom++;
		nodo_m = nodo_m->prox;
	}
	nodo_m = usernodo;
	int percorreto = 0;
	while(nodo_m!=NULL) {
		if (percorreto==to) {//se posicao desejada é o item a ser visto, guarda e freia loop
			to = nodo_m->userid;
			break;
		}
		percorreto++;
		nodo_m = nodo_m->prox;
	}
	while(nodo_t!=NULL) {//verifica retornos das diferenças e os soma fazendo uma especie de balanco que é retornado
		if(nodo_t->tradefrom==from && nodo_t->tradeto==to) saldo = saldo+nodo_t->tradevalue;
		if(nodo_t->tradefrom==to && nodo_t->tradeto==from) saldo = saldo-nodo_t->tradevalue;
		nodo_t = nodo_t->subseq;
	}
	return saldo;
}

/****************************************************************************************************/

arvore* cria_nodo(int registro) {
	arvore* novo_nodo = malloc(sizeof(arvore));
	novo_nodo->registro = registro;
	novo_nodo->esq = NULL;
	novo_nodo->dir = NULL;
	return novo_nodo;
}
arvore* insere_nodo(arvore* raiz,int registro) {//verifica posicao do nodo e escolhe se cria nodo ou muda de posicao. retorna o nodo para a funcao de origem manipula-lo
	if (raiz==NULL) {//se primeiro nodo, raiz da arvore
		raiz = cria_nodo(registro);
		return raiz;
	} else if (registro <= raiz->registro) {//direcionadores de hierarquia quando nao é o inicial
		raiz->esq = insere_nodo(raiz->esq, registro);
	}else{
		raiz->dir = insere_nodo(raiz->dir, registro);
	}
	return raiz;
}
int id_do_nome(struct st_user *nodo_m,int nome,int pular) {//recebe o nome e retorna o respectivo id
	int vez = 0;
	nodo_m = usernodo;
	while(nodo_m!=NULL) {
		if (nodo_m->userfullname==nome) {//se é valor igual ao desejado
			if (vez==pular) return nodo_m->userid;//se esta na posicao desejada
			vez++;
		}
		nodo_m = nodo_m->prox;
	}
}
bool busca_nodo(arvore* raiz,int registro) {//procura registro recebido, se achaou exibe, se nao, escoolhe uma direcao e segue a recursividade
	int achou=0;//variavel de controle
	if(raiz==NULL) return false;//se vazia
	else if (raiz->registro == registro) {//exibe se encontrado e segue recursividade
		printf("    -->    %d\t(%d)\n",raiz->registro,id_do_nome(usernodo,raiz->registro,achou_nodo));
		achou++;
		achou_nodo++;
		busca_nodo(raiz->esq,registro);
	}
	else if (registro<= raiz->registro) return busca_nodo(raiz->esq,registro);
	else return busca_nodo(raiz->dir,registro);
	achou_nodo = 0;//sempre zerado para garantir que nao sofra interferencias causadas pela recursividade
	if (achou>0) return true;//retorna verdadeiro se achou algo e falso caso contrario
	else return false;
}

/****************************************************************************************************/

int balanco_credor(struct st_trade *nodo_t ,int id) {//procura todas as transacoes de determinado usuario como credor e retorna a soma
	int saldo=0;
	nodo_t = tradenodo;
	if(nodo_t==NULL) return;
	printf("\n-------- Credor --------\n");
	while(nodo_t!=NULL) {
		if(nodo_t->tradefrom==id) {//exibe e soma operacoes em que usuario foi credor
			printf(" $%d para %d (user: %d)\n",nodo_t->tradevalue,nome_do_id(usernodo,nodo_t->tradeto),nodo_t->tradeto);
			saldo += nodo_t->tradevalue;
		}
		nodo_t = nodo_t->subseq;
	}
	printf("------ total: $%d ------\n",saldo);
	return saldo;//retorna soma dessas operacoes
}
int balanco_devedor(struct st_trade *nodo_t ,int id) {//procura todas as transacoes de determinado usuario como devedor e retorna a soma
	int saldo=0;
	nodo_t = tradenodo;
	if(nodo_t==NULL) return;
	printf("\n-------- Devedor --------\n");
	while(nodo_t!=NULL) {
		if(nodo_t->tradeto==id) {//exibe e soma operacoes em que usuario foi deveedor
			printf(" $%d para %d (user: %d)\n",nodo_t->tradevalue,nome_do_id(usernodo,nodo_t->tradefrom),nodo_t->tradefrom);
			saldo += nodo_t->tradevalue;
		}
		nodo_t = nodo_t->subseq;
	}
	printf("------- total: $%d -------\n",saldo);
	return saldo;//retorna soma dessas operacoes
}
int nome_do_id(struct st_user *nodo_m,int id) {//transforma id em nome
	nodo_m = usernodo;
	while(nodo_m!=NULL) {//acha id e retorna o nome dele
		if(nodo_m->userid==id) return nodo_m->userfullname;
		nodo_m = nodo_m->prox;
	}
}
void balanco_total(struct st_trade *nodo_t,int id,int total) {//exibe todas operacoes do usuario e recebe a diferença entre os retornos de credor e devedor
	nodo_t = tradenodo;
	if(nodo_t==NULL) {//se vazia
		printf("\n>>> Lista de transacoes vazia\n");
		tela_principal();
	}
	printf("\n------- Historico -------\n");
	while(nodo_t!=NULL) {
		if(nodo_t->tradefrom==id || nodo_t->tradeto==id) {//lsita dodas operacoes em ordem de criacao envolvendo o usuario
			if(nodo_t->tradefrom==id) printf(" $%d para %d (user: %d)\n",nodo_t->tradevalue,nome_do_id(usernodo,nodo_t->tradeto),nodo_t->tradeto);
			else printf(" $-%d para %d (user: %d)\n",nodo_t->tradevalue,nome_do_id(usernodo,nodo_t->tradefrom),nodo_t->tradefrom);
		}
		nodo_t = nodo_t->subseq;
	}
	printf("\n >>> total: $%d\n",total);//exibe resultado do balanco
}

/****************************************************************************************************/

void insere_trade(int from,int to,int value) {//se vazia pede pra iniciar, caso contrario pede pra adicionar elemento a lsita
	struct st_trade *temp;
	temp = tradenodo;
	if(temp==NULL) primeira_trade(from,to,value);
	else adiciona_trade(from,to,value);
}
int verifica_user(struct st_user *nodo_m,int id) {//recebe usuario e retorna 1 se foi encontrado
	nodo_m = usernodo;
	if(id==0) {// se pedido de cancelar
		printf(">>> operacao cancelada\n");
		tela_principal();
	}
	if(nodo_m==NULL) {//se vazia
		printf(">>> registro sem usuarios\n");
		tela_principal();
	}
	while(nodo_m!=NULL) {//percorre lista, se existe usuario retorna 1
		if(nodo_m->userid==id) return 1;
		nodo_m = nodo_m->prox;
	}
	return 0;
}
void primeira_trade(int from,int to,int value) {//recebe dados e aloca o primeiro elemento da lista
	struct st_trade *temp;
	temp = (struct st_trade *)malloc(sizeof(struct st_trade));
	temp->tradefrom = from;
	temp->tradeto = to;
	temp->tradevalue = value;
	if(tradenodo== NULL) {//garante que é a primeira entrada
		tradenodo = temp;
		tradenodo->subseq = NULL;
	}else{
		temp->subseq = tradenodo;
		tradenodo = temp;
	}
}
void adiciona_trade(int from,int to,int value) {//pega dados e o adiciona a lsita. temp e seguinte servem para percorrer.
	struct st_trade *temp,*seguinte;//auxiliar e cursor
	temp = (struct st_trade *)malloc(sizeof(struct st_trade));
	temp->tradefrom = from;
	temp->tradeto = to;
	temp->tradevalue = value;
	seguinte=(struct st_trade *)tradenodo;
	while(seguinte->subseq != NULL) seguinte = seguinte->subseq;//procura ultimo item
	seguinte->subseq = temp;
	seguinte = temp;
	seguinte->subseq = NULL;
}
void mostra_trade(struct st_trade *nodo_t) {//percorre e exibe elementos na lista de trocas
	nodo_t = tradenodo;
	if(nodo_t==NULL) return;
	while(nodo_t!=NULL) {
		printf("\t%d\t%d\t%d\n",nodo_t->tradefrom,nodo_t->tradeto,nodo_t->tradevalue);
		nodo_t = nodo_t->subseq;
	}
}
int deleta_trade(int from,int to,int value,struct st_trade *nodo_t) {//recebe informacoes da troca desejada, a encontra, e a exclui. retorna 1 se sucesso. temp e prev para percorrer
	struct st_trade *temp, *prev;//cursor e auxiliar
	temp = tradenodo;
	while(temp!=NULL) {//corre a lista
		if(temp->tradefrom==from) {
			if(temp->tradeto==to) {
				if(temp->tradevalue==value) {//garante que validou os tres parametros
					if(temp==tradenodo) {//garante que esta trabalhando com a lista atual, retorna 1 quando acha
						tradenodo = temp->subseq;
						free(temp);
						return 1;
					}else{
						prev->subseq = temp->subseq;
						free(temp);
						return 1;
					}
				}else{
					prev = temp;
					temp = temp->subseq;
				}
			}else{
				prev = temp;
				temp = temp->subseq;
			}
		}else{
			prev = temp;
			temp = temp->subseq;
		}
	}
	return 0;
}
void trocas_entre(struct st_trade *nodo_t,int from,int to) {//percorre a lsita e exibe os desejados envolvendo from e to
	nodo_t = tradenodo;
	if(nodo_t==NULL) return;//se vazia
	while(nodo_t!=NULL) {//exibir os encontrados
		if(nodo_t->tradefrom==from) {
			if(nodo_t->tradeto==to) {
				printf("\n\t de %d para %d\t$%d",nodo_t->tradefrom,nodo_t->tradeto,nodo_t->tradevalue);
			}
		}
		nodo_t = nodo_t->subseq;
	}
}
int conta_trades(struct st_trade *nodo_t) {//varre a lista pra retornar a quantidade de trocas
	nodo_t = tradenodo;
	int contador=0;
	if(nodo_t==NULL) return contador;//se vazia retorna 0
	while(nodo_t!=NULL) {//soma existentes e retorna a quantidade
		contador++;
		nodo_t = nodo_t->subseq;
	}
	return contador;
}

/****************************************************************************************************/

void insere_user(int id,int name) {//se vazia pede pra iniciar, caso contrario pede pra adicionar elemento a lsita
	struct st_user *temp;
	temp = usernodo;
	if(temp==NULL) primeiro_user(id,name);
	else adiciona_user(id,name);
}
void unico_user(struct st_user *nodo_m,int id) {//recebe candidato a entrar e verifica se ja possui um semelhante nos registros
	nodo_m = usernodo;
	if(id==0) {//se cancelada
		printf(">>> operacao cancelada\n");
		tela_principal();
	}
	if(nodo_m==NULL) return;//se lista vazia
	while(nodo_m!=NULL) {//se encontrou elemento na lista, caso contrario segue adiante
		if(nodo_m->userid==id) {
			printf(">>> %d ja existe, tente outro id\n",nodo_m->userid);
			insere_usuario();
		}
		nodo_m = nodo_m->prox;
	}
}
void primeiro_user(int id,int name) {//recebe dados e aloca o primeiro elemento da lista
	struct st_user *temp;
	temp = (struct st_user *)malloc(sizeof(struct st_user));//aloca espaco
	temp->userid = id;
	temp->userfullname = name;
	if(usernodo== NULL){//confirma lsita vazia e estabelece o primeiro
		usernodo = temp;
		usernodo->prox = NULL;
	}else{
		temp->prox = usernodo;
		usernodo = temp;
	}
}
void adiciona_user(int id,int name) {//recebe dados e adiciona mais um elemento à lsita. temp e seguinte sao utilizados para percorrer.
	struct st_user *temp,*seguinte;
	temp = (struct st_user *)malloc(sizeof(struct st_user));//reserva espaço pro novo elemento
	temp->userid = id;
	temp->userfullname = name;
	seguinte = (struct st_user *)usernodo;//molda para percorrer e receber dados
	while(seguinte->prox!=NULL) seguinte = seguinte->prox;
	seguinte->prox = temp;
	seguinte = temp;
	seguinte->prox = NULL;
}
void mostra_user(struct st_user *nodo_m) {//varre e exibe elemnetos na lista de usuarios
	nodo_m = usernodo;
	if(nodo_m==NULL) return;//se vazia
	while(nodo_m!=NULL) {//printa se existe e segue
		printf("\t%d\t\t%d\n",nodo_m->userid,nodo_m->userfullname);
		nodo_m = nodo_m->prox;
	}
}
int deleta_user(int id) {//procura usuario desejado e o exclui, requisita funcao para apagar os dados dele e  retorna 1 se sucesso. temp e anterior sao utilizados para percorrer
	struct st_user *temp, *anterior;
	temp = usernodo;
	if(id==0) {//caso tenha pedido pra voltar ao menu principal
		printf(">>> operacao cancelada\n");
		tela_principal();
	}
	while(temp!=NULL) {
		if(temp->userid==id) {//se a posicao é o id desejado e retorna positivo se encontrou
			if(temp==usernodo){//comparacao visa garantir que temp esta trtbalhando corretamente
				usernodo = temp->prox;
				deleta_historico(temp->userid,tradenodo);
				free(temp);
				return 1;
			}else{
				anterior->prox=temp->prox;
				deleta_historico(temp->userid,tradenodo);
				free(temp);
				return 1;
			}
		}else{//seguir adiante
			anterior = temp;
			temp = temp->prox;
		}
	}
	return 0;
}
void deleta_historico(int usuario,struct st_trade *nodo_t) {//recebe usuario e requisita a delecao de todas as operacoes em que ele esta envolvido. temp e prev sao utilizados para percorrer
	struct st_trade *temp, *prev;
	temp = tradenodo;
	while(temp!=NULL) {//usuario envolvido, pede delecao e pra seguir a busca
		if(temp->tradefrom==usuario || temp->tradeto==usuario) {//
			deleta_trade(temp->tradefrom,temp->tradeto,temp->tradevalue,tradenodo);
			prev = temp;
			temp = temp->subseq;
		}else{//usuario nao envolvido, segue adiante
			prev = temp;
			temp = temp->subseq;
		}
	}
}
int conta_users(struct st_user *nodo_m){//varre a lista pra retornar a quantidade de usuuarios.
	nodo_m = usernodo;
	int contador=0;
	if(nodo_m==NULL) return contador;//lista vaiz retorna zero
	while(nodo_m!=NULL) {
		contador++;
		nodo_m = nodo_m->prox;
	}
	return contador;//retorna quantidade
}
