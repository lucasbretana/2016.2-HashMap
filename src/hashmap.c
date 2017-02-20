#include "hashmap.h"
#include "usefull.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

position_t h1(key_t *k, size_t size){
  return h0(k, length(k) % size);
}

position_t h2(key_t *k, size_t size){
  return 1 + ( h0(k, length(k)) % (size - 1) );
}

position_t position(key_t *k){
  return 0;
}

void hash_insert(HashMap_t *hash, key_t *hashKey){
}
void hash_delete(HashMap_t *hash, key_t *hashKey){
}
void hash_get(HashMap_t *hash, key_t *hashKey){
    if(strcomp(hash->keys[h1(hashKey, length(hashKey)), hashKey) == 0){
        // FIND IT
        // No conflicts, first try
        printf("Found it");
    }
}

HashMap_t *hash_initialize(ConflictMethods_t method){
    HashMap_t *h = malloc(sizeof(HashMap_t));
    h->size = INITIAL_SIZE;
    h->method = method;
    h->keys = malloc(sizeof(key_t *) * h->size);
    return h;
}
