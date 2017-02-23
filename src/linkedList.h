#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct hashList{
  char *data;
  struct hashList *next;
  struct hashList *prev;
}hashList;

hashList* list_create();
hashList* list_free();
hashList* list_get(hashList *, char *);
int list_insert(hashList *, char *);
int list_delete(hashList **, char *);
#endif
