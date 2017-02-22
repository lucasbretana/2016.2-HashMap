#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmapJon.h"
#include "hashmap.h"
#include "usefull.h"
#include "linkedList.h"

void hash_insert(HashMap_t *hash, key_p hashKey){
  position_t h1_position = h1(hashKey, (*hash).size);
  position_t h2_position;
  int conflict = 0;
  int probing = 0;
  char *aux;
  switch ((*hash).method) {
    case Chaining:
      conflict += list_insert((*hash).keys, hashKey);
      break;
    //All the next 'cases' need to run this test
    if(((char *)(*hash).keys + h1_position) == NULL) {
      char **p;
      p = ((*hash).keys + h1_position);
      *p = hashKey;
      break; //Leaves if that was no conflict
    }
    aux = ((char *)(*hash).keys + h1_position); //Set it variable as it is the same in all 'cases'.
    case Linear:
      // aux = ((char *)(*hash).keys + h1_position);
      for (probing = h1_position; aux != NULL; probing++) {
        if(probing >= (*hash).size){ //Reached the end of the hash, go back to the top.
          aux = (*hash).keys;
        }else{
          aux += 1;
        }
        conflict += 1;
      }
      aux = hashKey;
      break;
    case Quadratic:
      // aux = ((char *)(*hash).keys + h1_position);
      for (size_t i = 0, probing = h1_position; aux != NULL; i++, probing++) {
        if(probing >= (*hash).size){ //Reached the end of the hash, go back to the top.
          aux = (*hash).keys;
        }else{
          aux += (i*i);
        }
      }
      aux = hashKey;
      break;
    case Double_Hash:
      // aux = ((char *)(*hash).keys + h1_position);
      h2_position = h2(hashKey, (*hash).size);
      for (size_t i = 0; aux != NULL; i++) {
        aux = (*hash).keys + ((h1_position + (i * h2_position)) % (*hash).size);
      }
      aux = hashKey;
      break;
  }
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
