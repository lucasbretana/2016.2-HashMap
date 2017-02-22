#include "linkedList.h"
#include "usefull.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Creates a new doubly linked list with a empty head.
 * @returns Pointer to list's head.
 */
hashList* list_create(){
  hashList* head;

  head = malloc(sizeof(hashList));
  if (head == NULL) {
    fprintf(stderr, "Failed to create list\nmalloc returned NULL\n");
    return NULL;
  }
  (*head).data = NULL;
  (*head).next = NULL;
  (*head).prev = NULL;

  return head;
}

/**
 * Insert 'value' at the end of a list.
 * @returns 0 if 'value' was inserted in the head.
 */
int list_insert(hashList *head, char *value){
  hashList *node;
  hashList *last;
  char *myValue;

  if(head == NULL){
    return -1;
  }
  node = malloc(sizeof(hashList));
  if (node == NULL) {
    return -1;
  }
  if((*head).data == NULL){ //If head is empty, write info in head;
    myValue = malloc(length(value) * sizeof(char));
    (*head).data = myValue;
    return 0;
  }else{
    fprintf(stderr, "Head was not empty\n");
    if ((*head).next != NULL) { //If head isn't the last element then
      last = head;
      do{                       //Go to the last element
        last = (*last).next;
        if (strcomp((*last).data,value) == 0){
          fprintf(stderr, "STINGS: S1:%s, S2:%s",(*last).data,value);
          return 2; //Value already inside the list, abort
        }
      }while((*last).next != NULL);
    }else{                      //So head IS the last element
      if (strcomp((*head).data,value) == 0) return 1; //Value already in the head, abort
      last = head;              //The head is the last element
    }
    //Now that we have the last element in the list
    myValue = malloc(length(value) * sizeof(char));
    (*head).data = myValue;
    (*node).prev = last;
    (*node).next = NULL;
    (*last).next = node;
    //Now the new node is the new last elemnet.
    return 3;
  }

}

/**
 * Look for 'info' inside the list.
 * @returns node that contains 'info' or NULL if not found.
 */
hashList* list_get(hashList *head, char *info){
  if (strcomp((*head).data,info) == 0) { //If the info is at the head
    return head;
  }
  hashList *seeker;
  seeker = head;
  do{
    seeker = (*seeker).next;
  }while(seeker != NULL && strcomp((*seeker).data, info) != 0); //Seek info or the end of the list
  return seeker; //Return NULL or element's node
}

/**
 * Removes 'info' from list poited by head;
 */
int list_delete(hashList **listHead, char *info){
  hashList *head = *listHead;
  hashList *target;
  hashList *next, *prev;
  int nConfl = 0;
  target = list_get(head, info);
  if (target == NULL) {     //Element was not in the list.
    *listHead = head;
  }
  next = (*target).next;
  prev = (*target).prev;

  if(target == head){
    free((*target).data);
    (*target).data = NULL;        //Leave head empty.
    if ((*target).next != NULL) { //If the head is not the last element I can free it.
      free(target);
      target = next;              //Now the second elemnet is the new head.
    }
  }else{                          //The target is a node.
    nConfl = 1;
    if(prev != NULL){
      (*prev).next=next;
    }
    if(next != NULL){
      (*next).prev=prev;
    }
    free(target);
  }
  *listHead = target;
  return nConfl;
}
