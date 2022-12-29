#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
/*Definição dos dados da struct*/
/*Este struct armazena as informações sobre o produto*/
struct infoProduto{
  /*A matrícula é um código único e faz referência ao produto*/
  int matricula;
  int tipo;
  float preco;
};

struct no{
  /*Armazena todas as informações sobre os produtos*/
  struct infoProduto info;
  /*Os ponteiros seguintes apontam para os nós filhos a esquerda e a direita*/
  No* direita;
  No* esquerda;
  /*O campo altura é utilizado para calcular o fator de balanceamento da árvore binária*/
  int altura;
};

struct arvBin{
  /*Ponteiro que leva para a raiz da árvore binária*/
  No* raiz;
  /*Informa a quantidade de nós cadastrados*/
  int qtdNo;
};


/*Funções de criação*/
/*Criar a estrutura da árvore*/
ArvBin *criaArv (){
  ArvBin *arv = (ArvBin*) calloc (1, sizeof(ArvBin));
  /*No caso de a árvore não puder ser alocada o programa mostra a mensagem de erro e encerra*/
  if (arv == NULL){
    printf("ERRO: os dados nao foram armazenados!\n");
    getchar();
    exit(1);
  }
  /*Garante que os dados foram iniciados como nulos*/
  arv->qtdNo = 0;
  arv->raiz = NULL;
  return arv;
}
/*Criar o nó*/
No *criaNo (int mat, int t, int p){
  /*Realizar o alocamento do novo nó*/
  No *n = (No*) calloc (1, sizeof(No));
  
  /*Verificação de alocação*/
  if(n == NULL){
    printf("ERRO: no nao alocado\n");
    return NULL;
  }
  
  /*Insere os dados fornecidos pelo usuário no nó criado*/
  n->info.matricula = mat;
  n->info.tipo = t;
  n->info.preco = p;
  /*Toda vez que um novo nó é inserido trata-se de um nó folha por conta disso a altura é inicializada com 0 bem como os ponteiros direita e esquerda apontando para NULL*/
  n->altura = 0;
  n->direita = NULL;
  n->esquerda = NULL;

  
  /*Retorna o nó criado com as informações inseridas*/
  return n;
  
}
/*Retorna o ponteiro para a raíz da árvore*/
/*Permite fazer referência a raiz da árvore mesmo estando na main*/
No* ponteiroRaiz (ArvBin* arv){
  return arv->raiz;
}

/*Para inserir um novo nó na árvore balanceada é necessário verificar se essa inserção irá gerar um desbalanceamento e se esse for gerado reallizar as rotações adequadas. A fim de realizar essa operações tem-se o calculo do fator de balanceamento*/
/*Calcular a altura do no*/
int alturaNo (No *n){
  /*Se o nó for nulo a função retorna -1*/
  if (n == NULL){
    return -1;
  }
  else{
    return n->altura;
  }
}
/*Retorna a maior altura da maior subárvore de um nó*/
int maiorAltura (int alturaEsquerda, int alturaDireita){
  if (alturaEsquerda > alturaDireita){
    return alturaEsquerda;
  }
  else{
    return alturaDireita;
  }
}
/*Calcular o fator de balanceamento*/
int fatorBalanceamento (No *n){
  if (n != NULL){
    return (alturaNo (n->esquerda) - alturaNo (n->direita));
  }
  else{
    return 0;
  }
}

/*Rotações da árvore balanceada*/
/*A rotação à esquerda é realizada:
  1) Tornando o nó filho a direita o nó pai
  2) Tornando o antigo nó pai o nó filho a esquerda
  3) Se o novo nó pai houver um filho a esquerda esse irá virar o nó filho a direita do antigo nó avó (antigo nó pai do processo anterior)  */
No *rotacaoEsquerda (ArvBin *arv, No *pai){
  /*Para realizar esse processo serão utilizados os auxiliares abaixo*/
  /*Seus nomes são dados em relação a suas posições iniciais (anteriores a rotação à esquerda)*/
  No *filhoDir, *netoEsq;

  /*Posicionamento dos ponteiros auxiliares*/
  filhoDir = pai->direita;
  netoEsq = filhoDir->esquerda;

  /*Processo de rotação*/
  /*Verifica se o nó desbalanceado é a raiz da árvore a raiz é atulaizada*/
  if (pai == arv->raiz){
    arv->raiz = filhoDir;
  }
  filhoDir->esquerda = pai;
  pai->direita = netoEsq;
  

  /*Atualizar o campo altura dos nós*/
  /*Atura do antigo nó pai*/
  pai->altura = maiorAltura (alturaNo (pai->esquerda), alturaNo (pai->direita)) +1;
  filhoDir->altura = maiorAltura (alturaNo (filhoDir->esquerda), alturaNo (filhoDir->direita)) +1;  
  
  return filhoDir;
}

/*A rotação a direita:
    1) Torna o nó filho à esquerda o novo nó pai
    2) Torna o antigo nó pai o filho a direita do novo nó pai
    3) Se o novo nó pai houver um filho a direita esse irá virar o nó filho a esquerda do antigo nó avó (antigo nó pai do processo anterior)*/
No *rotacaoDireita (ArvBin *arv, No *pai){
  /*Cria os auxiliares*/
  No *filhoEsquerda, *netoDireita;
  
  /*Posicionamento dos ponteiros auxiliares*/
  filhoEsquerda = pai->esquerda;
  netoDireita = filhoEsquerda->direita;

  /*Processo de rotação*/
  /*Verifica se o nó desbalanceado é a raiz da árvore a raiz é atulaizada*/
  if (pai == arv->raiz){
    arv->raiz = filhoEsquerda;
  }
  filhoEsquerda->direita = pai;
  pai->esquerda = netoDireita;

  /*Atualizar o campo altura dos nós*/
  /*Atura do antigo nó pai*/
  pai->altura = maiorAltura (alturaNo (pai->esquerda), alturaNo (pai->direita)) +1;
  filhoEsquerda->altura = maiorAltura (alturaNo (filhoEsquerda->esquerda), alturaNo (filhoEsquerda->direita)) +1; 
  
  return filhoEsquerda;
}

/*Realiza uma rotação simples para a direita e depois uma rotação simples para a esquerda*/
No *rotacaoDireitaEsquerda (ArvBin *arv, No *pai){
  pai->direita = rotacaoDireita (arv, pai->direita);
  return rotacaoEsquerda (arv, pai);
}

/*Realiza uma rotação simples para a esquerda e depois uma rotação simples para a direita*/
No *rotacaoEsquerdaDireita (ArvBin *arv, No *pai){
  pai->esquerda = rotacaoEsquerda (arv, pai->esquerda);
  return rotacaoDireita (arv, pai);
}

/*Utiliza as funções de rotação anteriormente implementadas em suas situações de uso*/
No *balancear (ArvBin *arv, No* n){
  /*fb é a variável utilizada para armazenar o fator de balanceamento do nó recebido*/
  int fb = fatorBalanceamento (n);

  //Rotação à direita
  /*Para que ocorra essa rotação o nó desbalanceado chamado n deve ser menor do que -1 (-2,-3, ...) e o fator de balanceamento do seguinte nó a direteita deve ser negativo*/
  if (fb < -1 && fatorBalanceamento (n->direita) <= 0){
    n = rotacaoEsquerda (arv, n);
  }

  //Rotação à esquerda
  /*Para que ocorra essa rotação o nó desbalanceado chamado n deve ser maior do que 1 (2,3, ...) e o fator de balanceamento do seguinte nó a esquerda deve ser positivo*/
  else if (fb > 1 && fatorBalanceamento (n->esquerda) >= 0){
    n = rotacaoDireita (arv, n);
  }
  /*Para que ocorra essa rotação o nó desbalanceado chamado n deve ser maior do que 1 (2,3, ...) e o fator de balanceamento do seguinte nó a esquerda deve ser negativo*/
  //Rotação dupla à esquerda
  else if (fb > 1 && fatorBalanceamento (n->esquerda) < 0){
    n = rotacaoDireita (arv, n);
  }

  //Rotação dupla à direita
  /*Para que ocorra essa rotação o nó desbalanceado chamado n deve ser menor do que -1 (-2,-3, ...) e o fator de balanceamento do seguinte nó a direteita deve ser positivo*/
  /*Não é utilizado um else pois sua situação deve ser descrita para que seja utilizada no caso correto*/
  else if (fb < -1 && fatorBalanceamento (n->direita) > 0){
    n = rotacaoDireita (arv, n);
  }

  return n;
}

/*Inserção*/
No *inserir (ArvBin *arv, No *n, int mat, int t, float p){
  /*Verifica se a árvore encontra-se vazia*/
  if (arv->raiz == NULL){
    No *n1 = criaNo (mat, t, p);
    if(n1 == NULL){
      printf("ERRO: alocacao do no mal sucedida\n");
      exit(1);
    }
    arv->raiz = n1;
    return n1;
  }
  /*Se tiver um nó na árvore executa a outra função*/
  else{
    if (n == NULL){
      No *n1 = criaNo (mat, t, p);
      if(n1 == NULL){
      printf("ERRO: alocacao do no mal sucedida\n");
      exit(1);
    }
      return n1;
    }
    else{
      if(n->info.matricula == mat){
      printf("Matricula ja cadastrada\n");
      getchar();
      return;
      }
      else if (mat < n->info.matricula){
        n->esquerda = inserir (arv, n->esquerda, mat, t, p);
      }
      else{
        n->direita = inserir (arv, n->direita, mat, t, p);
      }
    }
    /*Atualiza a altura de cada nó percorrido até que chegue no local de inserção*/
    n->altura = maiorAltura (alturaNo (n->esquerda), alturaNo (n->direita)) + 1;
    printf("Altura: %d\n", n->altura);
    /*Verifica a necessidade de rebalanceamento da árvore após a atualização das alturas*/
    n = balancear (arv, n);
    //return n;
  }
  
}


/*Leituras da árvore binária*/
/*Visita a raíz, o filho da esquerda e o filho da direita*/
void imprimirPreOrdem (No* pai){
  if (pai != NULL){
    /*Realiza o print da informação dos produtos*/
    printf("Matricula: %d       ", pai->info.matricula);
    printf("tipo: %d       ", pai->info.tipo);
    printf("Preco: %f       \n\n", pai->info.preco);
    /*Realiza o print das informações do filho da esquerda*/
    imprimirPreOrdem (pai->esquerda);
    /*Realiza o print das informações do filho da direita*/
    imprimirPreOrdem (pai->direita);
  }
  else {
    printf("Nao existem produtos cadastrados!\n");
  }
}

/*Visita o filho da esquerda, a raiz e depois o filho da direita*/
void imprimirEmOrdem (No* pai){
 if (pai != NULL){ 
  /*Realiza o print das informações do filho da esquerda*/
    imprimirEmOrdem (pai->esquerda);
  /*Realiza o print da informação dos produtos*/
    printf("Matricula: %d       ", pai->info.matricula);
    printf("tipo: %d       ", pai->info.tipo);
    printf("Preco: %f       \n\n", pai->info.preco);
    /*Realiza o print das informações do filho da direita*/
    imprimirEmOrdem (pai->direita);
  }
  else {
    printf("Nao existem produtos cadastrados!\n");
  }
}

/*Visita o filho da esquerda, o filho da direita e depois a raiz*/
void imprimirPosOrdem (No* pai){
  if (pai != NULL){ 
  /*Realiza o print das informações do filho da esquerda*/
    imprimirPosOrdem (pai->esquerda);
  /*Realiza o print das informações do filho da direita*/
    imprimirPosOrdem (pai->direita);
  /*Realiza o print da informação dos produtos*/
    printf("Matricula: %d       ", pai->info.matricula);
    printf("tipo: %d       ", pai->info.tipo);
    printf("Preco: %f       \n\n", pai->info.preco);
    
  }
  else {
    printf("Nao existem produtos cadastrados!\n");
  }
}

