#include <stdio.h>
#include "funcoes.h"
#include "printMenu.h"

int main(void) {
  int op;
  int mat, t;
  float p;

  ArvBin *arv = criaArv ();
  No *raiz = ponteiroRaiz (arv);
  

  do{
    printMenu ();
    printf("Escolha uma opcao:");
    scanf("%d", &op);
    switch (op){
      case 1:
        printf("Digite as informações do produto\n");
        printf("\nDigite a matricula:  ");
        scanf("%d", &mat);
        printf("\nDigite o tipo:  ");
        scanf("%d", &t);
        printf("\nDigite o preco:  ");
        scanf("%f", &p);
        raiz = inserir (arv, raiz, mat, t, p);
      break;

      case 2:
        printf("Informe a matricula procurada: ");
        scanf("%d", &mat);
        imprimirNo (buscaNo (arv, raiz, mat));
      break;

      case 3:
      break;

      case 4:
      break;

      case 5:
      break;

      case 6:
      break;

      case 7:
      break;

      default:
        printf("Digite uma opcao valida: ");

    }
    
  }while (op != 0);
  return 0;
}