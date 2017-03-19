#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmapJon.h"
#include "hashmap.h"
#include "usefull.h"
#include "linkedList.h"

ReturnLog_t hash_insert(HashMap_t **h, key_p hashKey){
  HashMap_t *hash = *h;
  position_t h2_position;
  ReturnLog_t opLog;
  // fprintf(stderr, "size out f:%i\n", (*hash).size);
  opLog.indH1 = h1(hashKey, (*hash).size, &opLog.code);
  opLog.localConflicts = 0;
  int probing = 0;
  char **aux;
  //This block finds the position on wich insert key
  switch ((*hash).method) {
    case Chaining:
      opLog.indHash = opLog.indH1;
      switch (list_insert( *( ((hashList **)(*hash).keys) + opLog.indH1), hashKey)) {
        case 0:
          opLog.localConflicts = 0;
          opLog.success = TRUE;
          break;
        case 1:
          // fprintf(stderr, "Falied to insert :%s\n",hashKey);
          opLog.localConflicts = 0;
          opLog.success = FALSE;
          break;
        case 2:
          // fprintf(stderr, "Falied to insert :%s\n",hashKey);
          opLog.localConflicts = 1;
          opLog.success = FALSE;
          break;
        case 3:
          opLog.localConflicts = 1;
          opLog.success = TRUE;
          break;
        case -1: //Same as default
        default:
          fprintf(stderr, "Something has faild, maybe a malloc\n");
          fprintf(stderr, "Falied to insert :%s\n",hashKey);
          // list_free(*( ((hashList **)(*hash).keys) + opLog.indH1));
          // list_create( ((hashList **)(*hash).keys) + opLog.indH1);
          break;
      }
      break;
    case Linear:
      aux = ((char **)(*hash).keys) + opLog.indH1;
      opLog.success = TRUE;
      if((*aux) == NULL) {
        opLog.indHash = opLog.indH1;
        insertString(aux, hashKey);
        break; //Leaves if that was no opLog.localConflicts
      }

      do {
        if (strcomp((*aux), hashKey) == 0) {
          opLog.success = FALSE;
          break;
        }
        probing ++;
        opLog.localConflicts++;
        aux = (((char **)(*hash).keys) + ((opLog.indH1 + probing) % (*hash).size));
      } while((*aux) != NULL);
      if (opLog.success) {
        insertString(aux, hashKey);
      }
      opLog.indHash = (opLog.indH1 + probing) % (*hash).size;
      break;
    case Quadratic:
      aux = ((char **)(*hash).keys) + opLog.indH1;
      opLog.success = TRUE;
      if((*aux) == NULL) {
        insertString(aux, hashKey);
        opLog.indHash = opLog.indH1;
        break; //Leaves if that was no opLog.localConflicts
      }
      do {
        if (strcomp((*aux), hashKey) == 0) {
          opLog.success = FALSE;
          break;
        }
        probing ++;
        opLog.localConflicts++;
        if (((opLog.indH1 + probing + probing * probing) % (*hash).size) == opLog.indH1){ // If position has returned to h1, we can't write data in the hash
          opLog.success = FALSE;
          probing = -1;
          break;
        }
        aux = (((char **)(*hash).keys) + ((opLog.indH1 + probing + probing * probing) % (*hash).size));
      } while((*aux) != NULL);
      if (probing < 0) {
        opLog.indHash = -1;
      }else{
        if (opLog.success) {
          insertString(aux, hashKey);
        }
        opLog.indHash = (opLog.indH1 + probing + probing * probing) % (*hash).size;
      }
      break;
    case Double_Hash:
      aux = ((char **)(*hash).keys) + opLog.indH1;
      opLog.success = TRUE;
      h2_position = h2(hashKey, (*hash).size);
      if((*aux) == NULL) {
        insertString(aux, hashKey);
        opLog.indHash = opLog.indH1;
        break; //Leaves if that was no opLog.localConflicts
      }
      do {
        if (strcomp((*aux), hashKey) == 0) {
          opLog.success = FALSE;
          break;
        }
        probing ++;
        opLog.localConflicts++;
        if (((opLog.indH1 + (probing * h2_position)) % (*hash).size) == opLog.indH1){ // If position has returned to h1, we can't write data in the hash
          opLog.success = FALSE;
          probing = -1;
          break;
        }
        aux = (((char **)(*hash).keys) + ((opLog.indH1 + (probing * h2_position)) % (*hash).size));
      } while((*aux) != NULL);
      if (probing < 0) {
        opLog.indHash = -1;
      }else{
        if (opLog.success) {
          insertString(aux, hashKey);
        }
        opLog.indHash = (opLog.indH1 + (probing * h2_position)) % (*hash).size;
      }
      break;
  }
  (*hash).hashConflicts += opLog.localConflicts;
  if(opLog.success){
    (*hash).nEntrys++;
    if( ( ((*hash).nEntrys * 1.0) / ((float) (*hash).size) ) >= ALPHA){
      // fprintf(stderr, "Key that caused rehash:%s\n || nEntrys:%i || h->size:%i || Calc:%f\n", hashKey, hash -> nEntrys, hash -> size, ( ((*hash).nEntrys * 1.0) / ((float) (*hash).size) ) );
      (*h) = rehash(hash);
    }
  }else{
    // fprintf(stderr, "Sting that faild:%s\nnEntrys:%i\n",hashKey, hash->nEntrys);
  }
  // if (hash->nEntrys > 760) {
  //   exit(-1);
  // }
  return opLog;
}

HashMap_t *hash_initialize(ConflictMethods_t method, unsigned int size){
    HashMap_t *h = malloc(sizeof(HashMap_t));
    (*h).size = size;
    (*h).nEntrys = 0;
    (*h).method = method;
    if(method == Chaining){
      (*h).keys = malloc(sizeof(hashList**) * size);
      //void *p = (*h).keys;
      for (size_t i = 0; i < size; i++) {
        *(((hashList **) (*h).keys) + i) = list_create();
      }
      //(*h).keys = p;
    }else{
      (*h).keys = malloc(sizeof(char **) * size); //Vector of pointers
      for (size_t i = 0; i < size; i++) {
        *(((char **) (*h).keys) + i) = NULL;
      }
    }
    return h;
}

void insertString(char **area, char *content){
  int size = length(content) + 1; //string size + 1 for the '\0'
  (*area) = malloc(size * sizeof(char));
  strcopy(*area, content);
}
