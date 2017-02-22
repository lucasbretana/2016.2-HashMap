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
  size_t probing = 0;
  char *aux;
  switch ((*hash).method) {
    case Chaining:
      conflict = list_insert((*hash).keys, hashKey);

      operationLog.indHash = h1_position;
      switch (conflict) {
        case 0:
          operationLog.localConflicts = 0;
          operationLog.success = TRUE;
          break;
        case 1:
          operationLog.localConflicts = 0;
          operationLog.success = FALSE;
          break;
        case 2:
          operationLog.localConflicts = 1;
          operationLog.success = FALSE;
          break;
        case 3:
          operationLog.localConflicts = 1;
          operationLog.success = TRUE;
          break;
        default:
          operationLog.localConflicts = -1;
          operationLog.success = FALSE;
          break;
      }
      break;
    //All the next 'cases' need to run this test
    if(((char *)(*hash).keys + h1_position) == NULL) {
      char **p;
      p = ((*hash).keys + h1_position);
      *p = hashKey;

      operationLog.indHash = h1_position;
      operationLog.success = TRUE;
      break; //Leaves if that was no conflict
    }
    case Linear:
      for (probing = h1_position; aux != NULL; probing++) {
        aux = (*hash).keys + ((h1_position + probing) % (*hash).size);
        conflict += 1;
        if (strcomp(aux, hashKey) == 0) {
          operationLog.success = FALSE;
          break;
        }
      }
      aux = hashKey;
      break;
    case Quadratic:
      for (probing = 0; aux != NULL; probing++) {
        aux = (*hash).keys + ((h1_position + (probing * probing)) % (*hash).size);
        conflict += 1;
        if (strcomp(aux, hashKey) == 0) {
          operationLog.success = FALSE;
          break;
        }
      }
      aux = hashKey;
      break;
      case Double_Hash:
      h2_position = h2(hashKey, (*hash).size);
      for (probing = 0; aux != NULL; probing++) {
        aux = (*hash).keys + ((h1_position + (probing * h2_position)) % (*hash).size);
      }
      if (strcomp(aux, hashKey) == 0) {
        operationLog.success = FALSE;
        break;
      }
      aux = hashKey;
      break;
  }
  (*hash).hashConflicts += conflict;
  operationLog.localConflicts = conflict;
  return operationLog; //TODO arrumar retorno
}

ReturnLog_t hash_get(HashMap_t *hash, key_p hashKey){

}

HashMap_t *hash_initialize(ConflictMethods_t method){
    HashMap_t *h = malloc(sizeof(HashMap_t));
    h->size = INITIAL_SIZE;
    h->method = method;
    h->hashConflicts = 0;
    if(method == Chaining){
      h->keys = malloc(sizeof(hashList*) * h->size);
      void *p = h->keys;
      for (size_t i = 0; i < h->size; i++) {
        h->keys += i;
        h->keys = (void *) list_create();
      }
      h->keys = p;
    }
    else{
      h->keys = malloc(sizeof(key_p) * h->size);
    }
    return h;
}
