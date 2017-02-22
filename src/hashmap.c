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

position_t h1(key_p k, bulk_t size, h_code_t *code){
  *code = h0(k, length(k));
  return (*code) % size;
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
  ReturnLog_t log;
  hashList *list;
  h_code_t code;

  switch(hash->method){
    case Chaining:
      log.indH1 = h1(hashKey, length(hashKey), &code);
      log.indHash = log.indH1;
      log.code = code;
      list = ((hashList *)hash->keys) + log.indH1;
      log.localConflicts = list_delete(&list, hashKey);
      log.success = TRUE;
      if(log.localConflicts == -1){
        log.localConflicts = 0;
        log.success = FALSE;
      }
      break;
    case Double_Hash:
    case Quadratic:
    case Linear:
      log.indH1 = h1(hashKey, length(hashKey), &code);
      log.indHash = log.indH1;
      log.code = code;
      log.localConflicts = 0;
      if(strcomp(((key_p)hash->keys) + log.indH1, hashKey) != 0){
        // You lucky bastard. Found it on first try
        key_p *deletedEntry = ((key_p *)hash->keys) + log.indH1;
        free(*(((key_p *)hash->keys) + log.indH1));
        *deletedEntry = NULL;

        log.success = TRUE;
      }else{
        // Haha gonna have to look all over the hash
        do{
          log.indHash = (log.indHash + sizeof(char *)) % hash->size;
          log.localConflicts++;
          if(strcomp(((key_p)hash->keys) + log.indHash, hashKey) == 0){
            key_p *deletedEntry = ((key_p *)hash->keys) + log.indHash;
            free(*(((key_p *)hash->keys) + log.indHash));
            *deletedEntry = NULL;
            // Gotta lucky this time, didn't have to go all the way throw
            break;
          }
        }while(log.indHash != log.indH1);
        if(log.indHash == log.indH1)
          log.success = FALSE;
      }
      break;
    default:
      fprintf(stderr, "There was something wrong! The conflict methodis not valid!\n");
      break;
    }
    return log;
}
