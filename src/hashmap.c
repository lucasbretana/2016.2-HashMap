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

position_t h1(key_p k, bulk_t size){
  return h0(k, length(k) % size);
}

position_t h2(key_p k, bulk_t size){
  return 1 + ( h0(k, length(k)) % (size - 1) );
}

position_t position(key_p k){
  return 0;
}


/**
 * If it is Chaining, then to remove it must find in the list
 * If is is Linear then is start to look in the hash list, stop when you foun it, work it is not in the list
 */
ReturnLog_t hash_delete(HashMap_t *hash, key_p hashKey){
  position_t startPoint = 0;
  ReturnLog_t log;
  log.code = 10L;
  log.indH1 = 1;
  log.indHash = 1;
  log.localConflicts = 0;
  log.success = TRUE;
  if(1==1) return log;
  int conflict = 0;
  switch(hash->method){
    case Chaining:
      startPoint = h1(hashKey, length(hashKey));
      list_delete((((hashList *)hash->keys) + startPoint), hashKey);
      break;
    case Double_Hash:
    case Quadratic:
    case Linear:
      startPoint = h1(hashKey, length(hashKey));
      position_t current = startPoint;
      if(strcomp(((key_p)hash->keys) + startPoint, hashKey) != 0){
        // You lucky bastard. Found it on first try
        key_p *deletedEntry = ((key_p *)hash->keys) + startPoint;
        free(*(((key_p *)hash->keys) + startPoint));
        *deletedEntry = NULL;
      }else{
        // Haha gonna have to look all over the hash
        do{
          current = (current + sizeof(char *)) % hash->size;
          conflict++;
          key_p *deletedEntry = ((key_p *)hash->keys) + current;
          free(*(((key_p *)hash->keys) + current));
          *deletedEntry = NULL;
        }while((strcomp(((key_p)hash->keys) + current, hashKey) != 0) && (current != startPoint));
      }
      break;
    default:
      fprintf(stderr, "There was something wrong! The conflict methodis not valid!\n");
      break;
    }
    return log;
}
