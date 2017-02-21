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

  if(head == NULL){
    fprintf(stderr, "Can't insert element in a empty list\n");
    return -1;
  }
  node = malloc(sizeof(hashList));
  if (node == NULL) {
    fprintf(stderr, "Failed to insert element list\nmalloc returned NULL\n");
    return -1;
  }
  if((*head).data == NULL){ //If head is empty, write info in head;
    (*head).data = value;
    return 0;
  }else{
    if ((*head).next != NULL) { //If head isn't the last element then
      do{                       //Go to the last element
        last = (*head).next;
      }while((*last).next != NULL);
    }else{                      //Else
      last = head;              //The head is the last element
    }
    (*node).data = value;
    (*node).prev = last;
    (*node).next = NULL;
    (*last).next = node;
    //Now the new node is the new last elemnet.
    return 1;
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
hashList* list_delete(hashList *head, char *info){
  hashList *target;
  hashList *next, *prev;

  target = list_get(head, info);
  if (target == NULL) {     //Element was not in the list.
    return head;
  }
  next = (*target).next;
  prev = (*target).prev;

  if(target == head){
    (*target).data = NULL;  //Leave head empty.
    if ((*target).next != NULL) { //If the head is not the last element I can free it.
      free(target);
      target = next;        //Now the second elemnet is the new head.
    }
  }else{                    //The target is a node.
    if(prev != NULL){
      (*prev).next=next;
    }
    if(next != NULL){
      (*next).prev=prev;
    }
    free(target);
  }

  return target;
}
