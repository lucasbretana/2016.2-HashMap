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
  return llabs(hash);
}

/**
 * Calculates the position in the given hash for the given key
 * Also puts the generated code in the code pointer
 */
position_t h1(key_p k, bulk_t size, h_code_t *code){
  *code = h0(k, length(k));
  return (*code) % size;
}

/**
 * Calculates the position in the given hash for the given key, to be used
 * in the double hash
 */
position_t h2(key_p k, bulk_t size){
  return 1 + ( h0(k, length(k)) % (size - 1) );
}

/**
 * If it is Chaining, then to remove it must find in the list
 * If it is Double_Hash then is start to look in the hash list using the double
 * hash deslocation, stop when you found or when you run size of hash times
 * If it is Double_Hash then is start to look in the hash list using the
 * quadratic deslocation, stop when you found or when you run size of hash times
 * If is is Linear then is start to look in the hash list, stop when you found
 * it or look where it started
 */
ReturnLog_t hash_delete(HashMap_t *hash, key_p hashKey){
  ReturnLog_t log;
  hashList *list;
  h_code_t code;

  switch(hash->method){
    case Chaining:
      {
        log.indH1 = h1(hashKey, length(hashKey), &code);
        log.indHash = log.indH1;
        log.code = code;
        list = ((hashList *)hash->keys) + log.indH1;
        log.localConflicts = list_delete(&list, hashKey);
        log.success = TRUE;
        if(log.localConflicts == -1){
          log.localConflicts = 1;
          log.success = FALSE;
        }
      }
      break;
    case Double_Hash:
      {
        // h'(k, i) = (h1(k) + i * h2(k)) mod size
        log.indH1 = h1(hashKey, hash->size, &code);
        unsigned int indH2 = h2(hashKey, hash->size);
        log.indHash = log.indH1;
        log.code = code;
        log.localConflicts = 0;
        log.success = FALSE;
        for(unsigned i = 0; i <hash->size ; i++){
          log.indHash = (log.indHash + i * indH2) % hash->size;
          char *string;
          string = *(((key_p *)hash->keys) + log.indHash);
          if(strcomp(string, hashKey) == 0){
            log.success = TRUE;
            *(((key_p *)hash->keys) + log.indHash) = NULL;
            free(string);
          }else{
            log.localConflicts = i - log.localConflicts; // Sum +1, except on the first move
          }
        }
      }
      break;
    case Quadratic:
      {
        // h'(k, i) = (h1(k) +i^2) mod size
        log.indH1 = h1(hashKey, hash->size, &code);
        log.indHash = log.indH1;
        log.code = code;
        log.localConflicts = 0;
        log.success = FALSE;
        for(unsigned i = 0; i <hash->size ; i++){
          log.indHash = (log.indHash + i*i) % hash->size;
          char *string;
          string = *(((key_p *)hash->keys) + log.indHash);
          if(strcomp(string, hashKey) == 0){
            log.success = TRUE;
            *(((key_p *)hash->keys) + log.indHash) = NULL;
            free(string);
          }else{
            log.localConflicts = i - log.localConflicts; // Sum +1, except on the first move
          }
        }
      }
      break;
    case Linear:
      {
        // On this case what we have is a char ** || key_p *
        // h'(k, i) = (h1(k) +i) mod size
        log.indH1 = h1(hashKey, hash->size, &code);
        log.indHash = log.indH1;
        log.code = code;
        log.localConflicts = 0;
        log.success = FALSE;
        for(unsigned i = 0; i <hash->size ; i++){
          log.indHash = (log.indHash + i) % hash->size;
          char *string;
          string = *(((key_p *)hash->keys) + log.indHash);
          if(strcomp(string, hashKey) == 0){
            log.success = TRUE;
            *(((key_p *)hash->keys) + log.indHash) = NULL;
            free(string);
          }else{
            log.localConflicts = i - log.localConflicts; // Sum +1, except on the first move
          }
        }
      }
      break;
    default:
      fprintf(stderr, "There was something wrong! The conflict methodis not valid!\n");
      break;
    }
    return log;
}

ReturnLog_t hash_get(HashMap_t *hash, key_p hashKey){
  ReturnLog_t log;
  
  return log;
}
