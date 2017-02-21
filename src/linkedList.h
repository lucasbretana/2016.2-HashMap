typedef struct hashList{
  char *data;
  struct hashList *next;
  struct hashList *prev;
}hashList;

hashList* list_create();
hashList* list_get(hashList *, char *);
void list_insert(hashList *, char *);
hashList* list_delete(hashList *, char *);
