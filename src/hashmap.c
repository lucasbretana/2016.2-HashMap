#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmap.h"
#include "usefull.h"
#include "linkedList.h"
/*
 * Generates the hash code of a key
 * Note that this do not return the hash map position
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
 * Allocate memory for a hash with 'size' entrys.
 * @param  method          The conflict method handler.
 * @param  size            Inicial Size of the hash.
 * @return                 Pointer to the hash.
 */
HashMap_t *hash_initialize(ConflictMethods_t method, unsigned int size){
    HashMap_t *h = malloc(sizeof(HashMap_t));
    (*h).size = size;
    (*h).nEntrys = 0;
    (*h).method = method;
    if(method == Chaining){
      (*h).keys = malloc(sizeof(hashList**) * size); //List of linkedLists
      for (size_t i = 0; i < size; i++) {
        *(((hashList **) (*h).keys) + i) = list_create(); // Allocate each empty head.
      }
    }else{
      (*h).keys = malloc(sizeof(char **) * size); //List of Strings
      for (size_t i = 0; i < size; i++) {
        *(((char **) (*h).keys) + i) = NULL; // Set String to NULL
      }
    }
    return h;
}

/**
 * Simply inserts a string. Used to avoid reppeating code.
 */
void insertString(char **area, char *content){
  int size = length(content) + 1; //string size + 1 for the '\0'
  (*area) = malloc(size * sizeof(char));
  strcopy(*area, content);
}

/**
 * Inserts 'hashKey' in hash 'h'
 * @param  h           Pointer of pointer to the hash with may change if it gets rehashed.
 * @param  hashKey     String to be inserted.
 * @return             Log containing information about the insertion.
 */
ReturnLog_t hash_insert(HashMap_t **h, key_p hashKey){
  HashMap_t *hash = *h;
  position_t h2_position;
  ReturnLog_t opLog; //Log to be returned
  opLog.indH1 = h1(hashKey, (*hash).size, &opLog.code);
  opLog.localConflicts = 0;
  int probing = 0;
  char **aux;
  //Main block for inserting the key on the hash based on it's conflict method
  switch ((*hash).method) {
    case Chaining:
      opLog.indHash = opLog.indH1; //On Chaining the position the key is inserted is always equals to H1
      switch (list_insert( *( ((hashList **)(*hash).keys) + opLog.indH1), hashKey)) {
        case 0:
          opLog.localConflicts = 0;
          opLog.success = TRUE;
          break;
        case 1:
          opLog.localConflicts = 0;
          opLog.success = FALSE;
          break;
        case 2:
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
          break;
      }
      break;
    case Linear:
      aux = ((char **)(*hash).keys) + opLog.indH1; //Set aux to H1's position on the list of strings
      opLog.success = TRUE;
      if((*aux) == NULL) { //If position is empty
        opLog.indHash = opLog.indH1;
        insertString(aux, hashKey);
        break; //All done
      }
      do {
        if (strcomp((*aux), hashKey) == 0) { //If string is already in the hash
          opLog.success = FALSE;
          break;
        }
        probing ++;
        opLog.localConflicts++;
        aux = (((char **)(*hash).keys) + ((opLog.indH1 + probing) % (*hash).size)); //Get next position
      } while((*aux) != NULL); //Stops if its a free position
      if (opLog.success) { //If string was not in the hash
        insertString(aux, hashKey);
      }
      opLog.indHash = (opLog.indH1 + probing) % (*hash).size; //Saves on log the position that the key was stored
      break;
    case Quadratic:
      aux = ((char **)(*hash).keys) + opLog.indH1; //Set aux to H1's position on the list of strings
      opLog.success = TRUE;
      if((*aux) == NULL) { //If position is empty
        insertString(aux, hashKey);
        opLog.indHash = opLog.indH1;
        break; //All done
      }
      do {
        if (strcomp((*aux), hashKey) == 0) { //If string is already in the hash
          opLog.success = FALSE;
          break;
        }
        probing ++;
        opLog.localConflicts++;
        if (((opLog.indH1 + probing + probing * probing) % (*hash).size) == opLog.indH1){ // If position has returned to h1, the search will get in loop
          opLog.success = FALSE;
          probing = -1; //Used to indicate that search found a loop
          break;
        }
        aux = (((char **)(*hash).keys) + ((opLog.indH1 + probing + probing * probing) % (*hash).size)); //Get next position (H1 + i + i^2)
      } while((*aux) != NULL); //Stops if its a free position
      if (probing < 0) { //If search found a loop
        opLog.indHash = -1; //Set a fail to insert
      }else{
        if (opLog.success) { //If string was not in the hash
          insertString(aux, hashKey);
        }
        opLog.indHash = (opLog.indH1 + probing + probing * probing) % (*hash).size; //Saves on log the position that the key was stored
      }
      break;
    case Double_Hash:
      aux = ((char **)(*hash).keys) + opLog.indH1; //Set aux to H1's position on the list of strings
      opLog.success = TRUE;
      h2_position = h2(hashKey, (*hash).size);
      if((*aux) == NULL) { //If position is empty
        insertString(aux, hashKey);
        opLog.indHash = opLog.indH1;
        break; //All done
      }
      do {
        if (strcomp((*aux), hashKey) == 0) { //If string is already in the hash
          opLog.success = FALSE;
          break;
        }
        probing ++;
        opLog.localConflicts++;
        if (((opLog.indH1 + (probing * h2_position)) % (*hash).size) == opLog.indH1){ // If position has returned to h1, the search will get in loop
          opLog.success = FALSE;
          probing = -1;
          break;
        }
        aux = (((char **)(*hash).keys) + ((opLog.indH1 + (probing * h2_position)) % (*hash).size)); //Get next position (H1 + (i * H2))
      } while((*aux) != NULL); //Stops if its a free position
      if (probing < 0) { //If search found a loop
        opLog.indHash = -1; //Set a fail to insert
      }else{
        if (opLog.success) { //If string was not in the hash
          insertString(aux, hashKey);
        }
        opLog.indHash = (opLog.indH1 + (probing * h2_position)) % (*hash).size; //Saves on log the position that the key was stored
      }
      break;
  }

  (*hash).hashConflicts += opLog.localConflicts; //Stores on the hash the number of conflicts
  if(opLog.success){
    (*hash).nEntrys++;
    if( ( ((*hash).nEntrys * 1.0) / ((float) (*hash).size) ) >= ALPHA){
      (*h) = rehash(hash);
    }
  }
  return opLog;
}

/**
 * If it is Chaining, then to remove it must find in the list
 * If it is Double_Hash then is start to look in the hash list using the double
 * hash deslocation, stop when you found, got a loop or when you run size of hash times
 * If it is Quadratic then is start to look in the hash list using the
 * quadratic deslocation, stop when you found, got a loop or when you run size of hash times
 * If is is Linear then is start to look in the hash list, stop when you found
 * it or look where it started
 */
ReturnLog_t hash_delete(HashMap_t *hash, key_p hashKey){
  ReturnLog_t log;
  char *string = NULL;
  hashList **list;

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
    }
  hash->hashConflicts += log.localConflicts;
  return log;
}

HashMap_t *rehash(HashMap_t *hash){
  HashMap_t *newHash = hash_initialize(hash->method, hash->size * 2);

  if(hash->method != Chaining){
    char *string;
    for(unsigned i = 0; i < hash->size ; i++){
      string = *(((key_p *)hash->keys) + i);
      if(string != NULL){
        hash_insert(&newHash, string);
      }
    }
  }else{
    hashList *seeker;
    for(unsigned i = 0; i <hash->size ; i++){
      seeker = *(((hashList**)hash->keys) + i);
      while (seeker != NULL && seeker->data != NULL) {
        if(seeker->data != NULL){
          hash_insert(&newHash, seeker->data);
        }
        seeker = seeker->next;
      }
    }
  }
  hash_free(hash);
  return newHash;
}

void hash_free(HashMap_t *hash){
  if(hash == NULL) return;
  if(hash->method != Chaining){
    int reInserts = 0;
    char *string;
    for(unsigned i=0 ; i<hash->size ; i++){
      string = *(((key_p *)hash->keys) + i);
      if(string != NULL){
        reInserts++;
        free(string);
      }
      *(((key_t **)hash->keys) + i) = NULL;
    }
  }else{
    for(unsigned i=0 ; i<hash->size ; i++){
      list_free(*(((hashList **)hash->keys) + i));
      *(((hashList **)hash->keys) + i) = NULL;
    }
  }
  free(hash->keys);
  free(hash);
}
