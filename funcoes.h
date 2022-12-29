/*Armazena as funções básicas da árvore binária de busca balanceada*/
/*
Criar a árvore
Inserir um nó
Editar um nó 
Remover um nó
Apagar a árvore
*/

/*Definição da struct*/
typedef struct infoProduto InfoProduto;
typedef struct no No;
typedef struct arvBin ArvBin;

/*Criar a estrutura da árvore*/
ArvBin *criaArv ();
/*Criar o nó*/
No *CriaNo (int mat, int t, int p);
/*Retorna o ponteiro para a raíz da árvore*/
No* ponteiroRaiz (ArvBin* arv);
/*Calcular a altura do no*/
int alturaNo (No *n);
/*Retorna a maior altura da maior subárvore de um nó*/
int maiorAltura (int alturaEsquerda, int alturaDireita);
/*Calcular o fator de balanceamento*/
int fatorBalanceamento (No *n);
/*Rotações da árvore balanceada*/
No *rotacaoEsquerda (ArvBin *arv, No *pai);
No *rotacaoDireita (ArvBin *arv, No *pai);
No *rotacaoDireitaEsquerda (ArvBin *arv, No *pai);
No *rotacaoEsquerdaDireita (ArvBin *arv, No *pai);
/*Utiliza as funções de rotação para balancear a árvore baseado nos casos em que devem ser utilizadas*/
No *balancear (ArvBin *arv, No* n);
No *inserir (ArvBin *arv, No *n, int mat, int t, float p);

/*Leituras da árvore binária*/
/*Visita a raíz, o filho da esquerda e o filho da direita*/
void imprimirPreOrdem (No* pai);

/*Visita o filho da esquerda, a raiz e depois o filho da direita*/
void imprimirEmOrdem (No* pai);

/*Visita o filho da esquerda, o filho da direita e depois a raiz*/
void imprimirPosOrdem (No* pai);

/*Busca uma matrícula cadastrada na árvore retorna NULL se não for cadastrada*/
No *buscaNo (ArvBin *arv, No *raiz, int mat);
void imprimirNo (No* n);

