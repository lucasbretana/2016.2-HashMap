#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmap.h"
#include "usefull.h"
#include "linkedList.h"
/*
  Generates the hash code of a key
  Note that this do not return the hash map position
 */
h_code_t h0(void *k, int len){
  char *p = (char *) k;
  h_code_t hash = 2166136261L;
  for(int i=1; i<len-1; i++){
    hash = hash * 16777619;  	// Multiply by prime number found to work well
    hash = hash ^ (p[i]); 	// xor next byte into the bottom of the hash
  }
  return hash;
}

position_t h1(key_p k, size_t size){
  return h0(k, length(k) % size);
}

position_t h2(key_p k, size_t size){
  return 1 + ( h0(k, length(k)) % (size - 1) );
}

position_t position(key_p k){
  return 0;
}

void hash_insert(HashMap_t *hash, key_p hashKey){
  position_t hashed_by_h1 = h1(hashKey, (*hash).size);
  int conflict = 0;
  switch ((*hash).method) {
    case Chaining:
      conflict += list_insert((*hash).keys, hashKey);
      break;
    case Linear:
    case Quadratic:
    case Double_Hash:
      if(((char **)(*hash).keys + hashed_by_h1) == NULL) {
        void *p = ((char **)(*hash).keys + hashed_by_h1);
        p = hashKey;
        p = NULL;
        break;
      }
    case Linear:
      void *aux = ((char **)(*hash).keys + hashed_by_h1);
      do {
        aux += 1;
        conflict += 1;
      } while(aux!=NULL);
      aux = hashKey;
      break;
    case Quadratic:
    void *aux = ((char **)(*hash).keys + hashed_by_h1);
      for (size_t i = 0; aux!=NULL; i++) {
          aux += (i*i);
          conflict += 1;
      }
      aux = hashKey;
      break;
    case Double_Hash:
      break;
  }
  list_insert((hash->keys)+ hashed_by_h1, hashKey);
}
void hash_delete(HashMap_t *hash, key_p hashKey){
}
void hash_get(HashMap_t *hash, key_p hashKey){
  if(hash->method != Chaining){}
    // if(strcomp(((key_p) hash->keys[h1(hashKey, length(hashKey))]), hashKey) == 0){
    //     // FIND IT0
    //     // No confl0icts, first try
    //     printf("Found it");
    // }
}

HashMap_t *hash_initialize(ConflictMethods_t method){
    HashMap_t *h = malloc(sizeof(HashMap_t));
    h->size = INITIAL_SIZE;
    h->method = method;
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
