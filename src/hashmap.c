#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmap.h"
#include "hashmapJon.h"
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
  char *string = NULL;
  hashList **list;
  // h_code_t code;

  switch(hash->method){
    case Chaining:
      log.indH1 = h1(hashKey, hash->size, &log.code);
      log.indHash = log.indH1;
      list = ((hashList **) hash->keys) + log.indH1;
      log.localConflicts = list_delete(list, hashKey);
      log.success = TRUE;
      if(log.localConflicts == -1){
        log.localConflicts = 1;
        log.success = FALSE;
      }else if(log.localConflicts == -2) {
        log.localConflicts = 0;
        log.success = FALSE;
      }
      break;
    case Double_Hash:
      log = hash_get(hash, hashKey);
      if (log.success) {
        string = *(((key_p *)hash->keys) + log.indHash);
        *(((key_p *)hash->keys) + log.indHash) = NULL;
        free(string);
      }
      break;
    case Quadratic:
      log = hash_get(hash, hashKey);
      if (log.success) {
        string = *(((key_p *)hash->keys) + log.indHash);
        *(((key_p *)hash->keys) + log.indHash) = NULL;
        free(string);
      }
      break;
    case Linear:
      log = hash_get(hash, hashKey);
      if (log.success) {
        string = *(((key_p *)hash->keys) + log.indHash);
        *(((key_p *)hash->keys) + log.indHash) = NULL;
        free(string);
      }
      break;
    default:
      //fprintf(stderr, "There was something wrong! The conflict methodis not valid!\n");
      break;
    }
    if(log.success == TRUE) hash->nEntrys--;
    hash->hashConflicts += log.localConflicts;
    return log;
}

ReturnLog_t hash_get(HashMap_t *hash, key_p hashKey){
  ReturnLog_t log;
  hashList *list;
  switch(hash->method){
    case Chaining:
      {
        log.indH1 = h1(hashKey, hash->size, &log.code);
        log.indHash = log.indH1;
        list = list_get(*( ((hashList **) hash->keys) + log.indH1), hashKey);
        if(list == NULL){
          log.localConflicts = 1;
          log.success = FALSE;
        }else if(list->prev == NULL){
          log.localConflicts = 0;
          if (list->data == NULL) log.success = FALSE;
          else log.success = TRUE;
        }else{
          log.localConflicts = 1;
          log.success = TRUE;
        }
      }
      break;
    case Double_Hash:
      {
        // h'(k, i) = (h1(k) + i * h2(k)) mod size
        log.indH1 = h1(hashKey, hash->size, &log.code);
        unsigned int indH2 = h2(hashKey, hash->size);
        log.success = FALSE;
        char *string;
        for(log.localConflicts = 0; log.localConflicts < hash->size; log.localConflicts ++){
          log.indHash = (log.indH1 + (log.localConflicts * indH2)) % hash->size;
          string = *( ((char **) (*hash).keys) + log.indHash);
          if (strcomp(string, hashKey) == 0) {
            log.success = TRUE;
            break;
          }
          if ((log.indH1 + ((log.localConflicts+1) * indH2)) % hash->size == log.indH1){
            log.success = FALSE;
            break;
          }
        }
      }
      break;
    case Quadratic:
      {
        log.indH1 = h1(hashKey, hash->size, &log.code);
        log.indHash = log.indH1;
        log.success = FALSE;
        char *string;
        for(log.localConflicts = 0; log.localConflicts < hash->size; log.localConflicts ++){
          log.indHash = (log.indH1 + log.localConflicts + log.localConflicts * log.localConflicts) % hash->size;
          string = *( ((char **) (*hash).keys) + log.indHash);
          if (strcomp(string, hashKey) == 0) {
            log.success = TRUE;
            break;
          }
          if ((log.indH1 + (log.localConflicts+1) + (log.localConflicts+1) * (log.localConflicts+1)) % hash->size == log.indH1){
            log.success = FALSE;
            break;
          }
        }
      }
      break;
    case Linear:
      {
        log.indH1 = h1(hashKey, hash->size, &log.code);
        log.localConflicts = 0;
        log.success = FALSE;
        char *string;
        for(log.localConflicts = 0; log.localConflicts < hash->size; log.localConflicts ++){
          log.indHash = (log.indH1 + log.localConflicts) % hash->size;
          string = *( ((char **) (*hash).keys) + log.indHash);
          if (strcomp(string, hashKey) == 0) {
            log.success = TRUE;
            break;
          }
          if ((log.indH1 + log.localConflicts + 1) % hash->size == log.indH1){
            log.success = FALSE;
            break;
          }
        }
      }
      break;
    default:
      //fprintf(stderr, "There was something wrong! The conflict methodis not valid!\n");
      break;
    }
  hash->hashConflicts += log.localConflicts;
  return log;
}

HashMap_t *rehash(HashMap_t *hash){
  // //fprintf(stderr, "Before: %p\t", hash);
  HashMap_t *newHash = hash_initialize(hash->method, hash->size * 2);
  // int indOldHash = 0, indNewHash = 0;

  if(hash->method != Chaining){
    char *string;
    for(unsigned i = 0; i <hash->size ; i++){
      string = *(((key_p *)hash->keys) + i);
      if(string != NULL){
        hash_insert(&newHash, string);
      }
    }
    // fprintf(stderr, "%i foram re inseridas\n",reInserts);
  }else{
    //fprintf(stderr, "\nBegin if else");
    hashList *seeker;
    for(unsigned i = 0; i <hash->size ; i++){
      seeker = *(((hashList**)hash->keys) + i);
      while (seeker != NULL && seeker->data != NULL) {
        if(seeker->data != NULL){
          hash_insert(&newHash, seeker->data);// Não usar juntamente com o debug abaixo.
          // fprintf(stderr, "Reinserindo %s em %i\n",seeker->data, hash_insert(&newHash, seeker->data).indHash);
        }
        seeker = seeker->next;
      }
    }
  }
  hash_free(hash);
  return newHash;
}

void hash_free(HashMap_t *hash){
  // fprintf(stderr, "Tentando o Free em:%p\n",hash);
  if(hash == NULL) return;
  if(hash->method != Chaining){
    int reInserts = 0;
    char *string;
    for(unsigned i=0 ; i<hash->size ; i++){
      string = *(((key_p *)hash->keys) + i);
      if(string != NULL){
        // fprintf(stderr, "removendo:%s\n", string);
        reInserts++;
        // fprintf(stderr, "String:%s\n", *(((key_t **)hash->keys) + i));
        free(string);
      }
      *(((key_t **)hash->keys) + i) = NULL;
    }
    // fprintf(stderr, "%i foram removidos\n",reInserts);
  }else{
    for(unsigned i=0 ; i<hash->size ; i++){
      list_free(*(((hashList **)hash->keys) + i));
      //if(*(((hashList **)hash->keys) + i) != NULL) free(*(((hashList **)hash->keys) + i));
      *(((hashList **)hash->keys) + i) = NULL;
      // if((((hashList **)hash->keys) + i) != NULL) free((((hashList **)hash->keys) + i));
    }
  }
  //  printf("free(hash->keys)");
  free(hash->keys);
  free(hash);
}
