#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "usefull.h"
#include "hashmap.h"

unsigned int SIZE = TAM_INI;

/*
  Generates the hash code of a key
  Note that this do not return the hash map position
 */
//TODO fix the generation of hash codes
//TODO check if it is ok to start at 1, and end 1 before, because of the "~" around the key
h_code_t h0(void *k, int len){
  char *p = (char *) k;
  h_code_t hash = 2166136261L;
  for(int i=1; i<len-1; i++){
    hash = (hash * 16777619) ^ (p[i]); // Multiply by prime number found to work well
    // hash = hash ^ (p[i]); // xor next byte into the bottom of the hash
  }
  return absh(hash);
}

position_t h1(key *k){
  return h0(k, length(k) % SIZE);
}

position_t h2(key *k){
  return 1 + ( h0(k, length(k)) % (SIZE - 1) );
}
