#include "linkedList.h"
#include "usefull.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Creates a new doubly linked list with 'value' and returns head's pointer.
 */
hashList* list_create(char *value){
  hashList* head;

  head = malloc(sizeof(hashList));
  if (head == NULL) {
    fprintf(stderr, "Failed to create list\nmalloc returned NULL\n");
    return NULL;
  }
  (*head).data = value;
  (*head).next = NULL;
  (*head).prev = NULL;

  return head;
}

/**
 * Insert 'value' at the end of a list.
 */
void list_insert(hashList *head, char *value){
  hashList *node;
  hashList *last;

  if(head == NULL)
    fprintf(stderr, "Can't insert element in a empty list\n");

  node = malloc(sizeof(hashList));
  if (node == NULL) {
    fprintf(stderr, "Failed to insert element list\nmalloc returned NULL\n");
    return;
  }
  if ((*head).next != NULL) {
    do{
      last = (*head).next;
    }while((*last).next != NULL);
  }else{
    last = head;
  }

  (*node).data = value;
  (*node).prev = last;
  (*node).next = NULL;
  (*last).next = node;

  return;
}


/**
 * Look for 'info' inside the list and returns the node that contains it
 */
hashList* list_get(hashList *head, char *info){
  if (strcomp((*head).data,info) == 0) {
    return head;
  }
  hashList *seeker;
  seeker = head;
  do{
    seeker = (*seeker).next;
  }while(seeker != NULL && strcomp((*seeker).data, info) != 0);
  return seeker;
}

void list_delete(hashList *head, char *info){
  hashList *target;
  hashList *next, *prev;

  target = list_get(head, info);
  if (target == NULL) {
    return;
  }
  next = (*target).next;
  prev = (*target).prev;
  if(prev != NULL){
    (*prev).next=next;
  }
  if(next != NULL){
    (*next).prev=prev;
  }
  free(target);
}
