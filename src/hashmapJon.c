#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmapJon.h"
#include "hashmap.h"
#include "usefull.h"
#include "linkedList.h"

ReturnLog_t hash_insert(HashMap_t *hash, key_p hashKey){
  h_code_t hcode;
  position_t h1_position;
  position_t h2_position;
  ReturnLog_t operationLog;
  h1_position = h1(hashKey, (*hash).size, &hcode);

  operationLog.code = hcode;
  operationLog.indH1 = h1_position;
  int conflict = 0;
  int probing = 0;
  char **aux;
  switch ((*hash).method) {
    case Chaining:
      operationLog.indHash = h1_position;
      switch (list_insert(*(((hashList **)(*hash).keys) + h1_position), hashKey)) {
        case 0:
          conflict = 0;
          operationLog.success = TRUE;
          break;
        case 1:
          conflict = 0;
          operationLog.success = FALSE;
          break;
        case 2:
          conflict = 1;
          operationLog.success = FALSE;
          break;
        case 3:
          conflict = 1;
          operationLog.success = TRUE;
          break;
        default:
          conflict = -1;
          operationLog.success = FALSE;
          break;
      }
      break;
    //All the next 'cases' need to run this test
    case Linear:
      aux = ((char **)(*hash).keys) + h1_position;
      if((*aux) == NULL) {
        (*aux) = malloc(length(hashKey) * sizeof(char *));
        strcopy(*aux, hashKey);

        operationLog.indHash = h1_position;
        operationLog.success = TRUE;
        break; //Leaves if that was no conflict
      }

      operationLog.success = TRUE;
      for (probing = 0; (*aux) != NULL; probing++) {
        conflict += 1;
        if (strcomp((*aux), hashKey) == 0) {
          operationLog.success = FALSE;
          break;
        }
        aux = (((char **)(*hash).keys) + ((h1_position + probing) % (*hash).size));
      }

      (*aux) = malloc(length(hashKey) * sizeof(char *));
      strcopy(*aux, hashKey);
      conflict -= 1; //Because probing started testing position 0;
      probing  -= 1; //Because probing started testing position 0;
      operationLog.indHash = (h1_position + probing) % (*hash).size;
      break;
    case Quadratic:
      aux = ((char **)(*hash).keys) + h1_position;
      h2_position = h2(hashKey, (*hash).size);
      if((*aux) == NULL) {
        (*aux) = malloc(length(hashKey) * sizeof(char *));
        strcopy(*aux, hashKey);

        operationLog.indHash = h1_position;
        operationLog.success = TRUE;
        break; //Leaves if that was no conflict
      }

      operationLog.success = TRUE;
      for (probing = 1, conflict = 1; (*aux) != NULL; probing++, conflict++) {
        // printf("S1:%s\nS2:%s\nProbing:%i\n",(*aux),hashKey,probing);
        if (strcomp((*aux), hashKey) == 0) {
          operationLog.success = FALSE;
          probing++;
          conflict++;
          break;
        }
        aux = ((char **)(*hash).keys) + ((h1_position + probing + probing * probing) % (*hash).size);
        if (((h1_position + probing + probing * probing) % (*hash).size) == h1_position){ // If position has returned to h1, we can't write data in the hash
          operationLog.success = FALSE;
          probing = -666;
          break;
        }
      }
      if (probing < 0) {
        operationLog.indHash = -666;
      }else{
        (*aux) = malloc(length(hashKey) * sizeof(char *));
        strcopy(*aux, hashKey);
        conflict -= 1;
        probing  -= 1;
        operationLog.indHash = (h1_position + probing + probing * probing) % (*hash).size;
      }
      break;
    case Double_Hash:
      aux = ((char **)(*hash).keys) + h1_position;
      h2_position = h2(hashKey, (*hash).size);
      if((*aux) == NULL) {
        (*aux) = malloc(length(hashKey) * sizeof(char *));
        strcopy(*aux, hashKey);

        operationLog.indHash = h1_position;
        operationLog.success = TRUE;
        break; //Leaves if that was no conflict
      }

      operationLog.success = TRUE;
      for (probing = 1, conflict = 1; (*aux) != NULL; probing++, conflict++) {
        // printf("S1:%s\nS2:%s\nProbing:%i\n",(*aux),hashKey,probing);
        if (strcomp((*aux), hashKey) == 0) {
          operationLog.success = FALSE;
          probing++;
          conflict++;
          break;
        }
        aux = ((char **)(*hash).keys) + ((h1_position + (probing * h2_position)) % (*hash).size);
        if (((h1_position + (probing * h2_position)) % (*hash).size) == h1_position){ // If position has returned to h1, we can't write data in the hash
          operationLog.success = FALSE;
          probing = -666;
          break;
        }
      }
      if (probing < 0) {
        operationLog.indHash = -666;
      }else{
        (*aux) = malloc(length(hashKey) * sizeof(char *));
        strcopy(*aux, hashKey);
        conflict -= 1;
        probing  -= 1;
        operationLog.indHash = (h1_position + (probing * h2_position)) % (*hash).size;
      }
      break;
  }
  (*hash).hashConflicts += conflict;
  operationLog.localConflicts = conflict;
  return operationLog;
}

// ReturnLog_t hash_get(HashMap_t *hash, key_p hashKey){
//   ReturnLog_t a;
//   return a;
// }

HashMap_t *hash_initialize(ConflictMethods_t method){
    HashMap_t *h = malloc(sizeof(HashMap_t));
    h->size = INITIAL_SIZE;
    h->method = method;
    h->hashConflicts = 0;
    if(method == Chaining){
      h->keys = malloc(sizeof(hashList**) * h->size);
      //void *p = h->keys;
      for (size_t i = 0; i < h->size; i++) {
        *(((hashList **) h->keys) + i) = list_create();
      }
      //h->keys = p;
    }else{
      h->keys = malloc(sizeof(char **) * h->size); //Vector of pointers
      for (size_t i = 0; i < h->size; i++) {
        *(((char **) h->keys) + i) = NULL;
      }
    }
    return h;
}
