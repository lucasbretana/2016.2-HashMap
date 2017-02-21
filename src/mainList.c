#include <stdio.h>
#include <stdlib.h>
#include "usefull.h"
#include "hashmap.h"
#include "linkedList.h"

int main(int argc, char const *argv[]) {
  int op;
  hashList *head = NULL;
  char text[10][20];
  char toSearch[20];
  int indice = 0;
  do{
    printf("OP:");
    scanf("%i%*c", &op);
    switch (op) {
      case 1:
        printf("create\n");
        scanf("%s%*c", text[indice]);
        head = list_create(text[indice]);
        indice++;
        break;
      case 2:
        printf("insert\ntext:");
        scanf("%s%*c", text[indice]);
        list_insert(head, text[indice]);
        indice++;
        break;
      case 3:
        printf("get\ntext:");
        scanf("%s%*c", toSearch);
        hashList *tmp;
        tmp = list_get(head, toSearch);
        if (tmp == NULL) printf("Não encontrado\n");
        else printf("%s\n", (*tmp).data);
        break;
      case 4:
        printf("delet\ntext:");
        scanf("%s%*c", toSearch);
        list_delete(head, toSearch);
        break;
      default:
        break;
    }
  }while(op!=5);
  return 0;
}
