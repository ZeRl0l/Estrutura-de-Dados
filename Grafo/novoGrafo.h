#define TAM 40
#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

/* FUN��ES PARA GRAFO SEM PESO */
struct no{
    int vertice;
    struct no* prox;
};

typedef struct no no;

struct Grafo{
    int numVertices;
    int* visitado;
    struct no** listaAdj;//precisa de ponteiro de ponteiro pra salvar em um vetor bidimensional, com isso a gente cria um vetor de lista ligada.
};

typedef struct Grafo Grafo;

/*FUN��O PARA CRIAR OS N�S*/

struct no* criaNo(int v){
    struct no* novoNo = malloc(sizeof(struct no));
    novoNo->vertice = v;
    novoNo->prox = NULL;
    return novoNo;
}

/*FUN��O PARA CRIAR O GRAFO*/

struct Grafo* criaGrafo(int v){
   struct Grafo* g = malloc(sizeof(struct Grafo));
    g->numVertices = v;

    g->listaAdj = malloc(v * sizeof(struct no*));

    g->visitado = malloc(v * sizeof(int));

    int i;
    for(i = 0; i < v; i++){
        g->listaAdj[i] = NULL;
        g->visitado[i] = 0;
    }
    return g;
}

/*FUN��O PARA ADICIONAR ARESTAS*/

void addAresta(struct Grafo* g, int vi, int vf){

    // adiciona aresta do vi para o vf
    struct no* novoNo = criaNo(vf);
    novoNo->prox = g->listaAdj[vi];
    g->listaAdj[vi] = novoNo;

    //adiciona aresta do vf para o vi
    novoNo = criaNo(vi);
    novoNo->prox = g->listaAdj[vf];
    g->listaAdj[vf] = novoNo;
}

/*FUN��O PARA IMPRIMIR O GRAFO*/

void imprime(struct Grafo* g){

    int v;
    for(v = 0; v < g->numVertices; v++){
        struct no* aux = g->listaAdj[v];
        printf("\n Lista de Adjacencia do vertice %d\n ", v);
        while(aux){
            printf("%d -> ", aux->vertice);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}

/*BUSCA EM PROFUNDIDADE (DFS)*/

void DFS(Grafo* g, int v){
    struct no* listaAdj = g->listaAdj[v];
    struct no* aux = listaAdj;

    g->visitado[v] = 1;
    printf("  Visitado %d \n", v);

    while(aux!=NULL){

        int vConectado = aux->vertice;

        if(g->visitado[vConectado] == 0){
            DFS(g, vConectado);
        }
        aux = aux->prox;
    }
}

/*BUSCA EM LARGURA (BFS)*/

struct fila{
    int itens[TAM];
    int frente;
    int atras;
};

struct fila* criaFila() {
    struct fila* f = malloc(sizeof(struct fila));
    f->frente = -1;
    f->atras = -1;
    return f;
}


int estaVazia(struct fila* f) {
    if(f->atras == -1)
        return 1;
    else
        return 0;
}

void enfila(struct fila* f, int v){
    if(f->atras == TAM-1)
        printf("\nFila esta cheia!!");
    else {
        if(f->frente == -1)
            f->frente = 0;
        f->atras++;
        f->itens[f->atras] = v;
    }
}

int defila(struct fila* f){
    int item;
    if(estaVazia(f)){
        printf("  Fila esta vazia");
        item = -1;
    }
    else{
        item = f->itens[f->frente];
        f->frente++;
        if(f->frente > f->atras){
            printf("Redefinindo fila ");
            f->frente = f->atras = -1;
        }
    }
    return item;
}

void imprimeFila(struct fila* f) {
    int i = f->frente;

    if(estaVazia(f)) {
        printf("  Fila esta vazia");
    } else {
        printf("\n  Fila contem \n");
        for(i = f->frente; i < f->atras + 1; i++) {
                printf("  %d ", f->itens[i]);
        }
    }
}

void BFS(Grafo* g, int vInicial) {

    struct fila* f = criaFila();

    g->visitado[vInicial] = 1;
    enfila(f, vInicial);

    while(!estaVazia(f)){
        imprimeFila(f);
        int vAtual = defila(f);
        printf("Visitado %d\n", vAtual);

       struct no* aux = g->listaAdj[vAtual];

       while(aux) {
            int verticeAdj = aux->vertice;

            if(g->visitado[verticeAdj] == 0){
                g->visitado[verticeAdj] = 1;
                enfila(f, verticeAdj);
            }
            aux = aux->prox;
       }
    }
}

/*FUN��O PARA EXCLUIR O GRAFO*/

void excluiGrafo(Grafo *g){
    if(g){
        if(g->listaAdj){
            int v;
            //liberar os n�s
            for(v=0; v < g->numVertices; v++){
                struct no *primeiro = g->listaAdj[v];
                while(primeiro){
                    struct no* aux = primeiro;
                    primeiro = primeiro->prox;
                    aux = NULL;
                    free(aux);
                }
            }
            // liberar o vetor da lista de adjacencia
            free(g->listaAdj);

        }
        //liberar o grafo
        free(g);
    }
}

/*MENUS*/


/* FUN��ES PARA CRIAR O GRAFO COM PESO */

typedef struct adjacencia{
    int vertice;  //Vetice Final
    TIPOPESO peso; //Peso ou Caminho
    struct adjacencia* prox;  //Proximo item
} ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;  //Cabe�a da lista ligada 1 -> "Num"
}VERTICE;

typedef struct grafo {
   int vertices; //S�o os pontinhos
   int arestas;    //S�o as arestas ou "caminhos" do grafo
   VERTICE *adj;//Ponteiro para um vetor de listas "Arrajo de vertices"
}GRAFO;


GRAFO *criaGrafo(int v){
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));
    int i;
    for(i=0; i<v;i++)
        g->adj[i].cab = NULL;
    return(g);
}

ADJACENCIA *criaAdj(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return(temp);
}

bool criaAresta(GRAFO *gr,int vi,int vf, TIPOPESO p){
    if(!gr) return(false);
    if((vf<0)||(vf>= gr->vertices))
        return(false);
    if((vi<0)||(vi>=gr->vertices))
        return(false);
    ADJACENCIA *novo = criaAdj(vf,p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return(true);
}

void imprime(GRAFO *gr){
    printf("  Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
    int i;
    for(i=0; i<gr->vertices; i++){
        printf("  v%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad){
            printf("  v%d(%d) ", ad->vertice,ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

/*ALGORITMO DE DIJKSTRA*/

//O algoritmo de Dijkstra soluciona o problema
//do caminho mais curto num grafo dirigido
//ou nao dirigido, com arestas de peso n�o negativo
void inicializaD(GRAFO *g, int *d, int *p, int s){
    int v;
    for(v=0; v<g->vertices;v++){
        d[v] = INT_MAX/2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relaxa(GRAFO *g, int *d, int *p, int u, int v){
    ADJACENCIA *ad = g->adj[u].cab;
    while(ad && ad->vertice != v)
        ad = ad->prox;
    if(ad){
        if(d[v]>d[u] + ad->peso){
            d[v] = d[u] + ad->peso;
            p[v] = u;
        }
    }
}

int *dijkstra(GRAFO *g, int s){
    int *d = (int *) malloc(g->vertices* sizeof(int));
    int p[g->vertices];
    bool aberto[g->vertices];
    inicializaD(g,d,p,s);

    int i;
    for(i=0;i<g->vertices;i++)
        aberto[i] = true;

    while(existeAberto(g,aberto)){
        int u = menorDist(g,aberto,d);
        aberto[u] = false;
        ADJACENCIA *ad = g->adj[u].cab;
        while(ad){
            relaxa(g,d,p,u,ad->vertice);
            ad = ad->prox;
        }
    }
    return(d);
}

//Varre o arranjo de abertos
//Se encontrar um true retorna true
//Ou seja que achou, se n�o retorna false
bool existeAberto(GRAFO *g, int *aberto){
    int i;
    for(i=0;i<g->vertices;i++)
        if(aberto[i]) return(true);
    return(false);
}

//Dentre todos os abertos necessita
//achar o que possui menor dist�ncia
int menorDist(GRAFO *g, int *aberto, int *d){
    int i;
    for(i=0; i<g->vertices; i++)
        if(aberto[i]) break;
    if(i==g->vertices) return(-1);
    int menor = i;
    for(i=menor+1; i<g->vertices;  i++)
        if(aberto[i] && (d[menor]>d[i]))
            menor = i;
        return(menor);
}

char menu_principal()
{
    printf("  1 - Grafo sem peso\n");
    printf("  2 - Grafo com peso\n");
    printf("  ESCOLHA UM OP%c%cO: ",128,199);

    return getche();
}

char sub_menuSP()
{
    printf("  1 - Criar grafo\n");
    printf("  2 - Inserir no grafo\n");
    printf("  3 - Listar grafo\n");
    printf("  4 - Busca em Profundidade\n");
    printf("  5 - Busca em Largura\n");
    printf("  6 - Excluir grafo\n");
    printf("  9 - Voltar ao menu principal\n");
    printf("  0 - Sair do aplicativo\n\n");
    printf("  ESCOLHA UM OP%c%cO: ",128,199);
    return getche();
}


char sub_menuExcluir()
{
    printf("  1 - Deseja recriar o grafo\n");
    printf("  2 - Sair do Programa\n");
    printf("  ESCOLHA UM OP%c%cO: ",128,199);

    return getche();
}

char sub_menuCP()
{
    printf("  1 - Criar grafo\n");
    printf("  2 - Inserir no grafo\n");
    printf("  3 - Listar grafo\n");
    printf("  4 - Algoritmo de Dijkstra\n");
    printf("  9 - Voltar ao menu principal\n");
    printf("  0 - Sair do aplicativo\n\n");
    printf("  ESCOLHA UM OP%c%cO: ",128,199);
    return getche();
}

