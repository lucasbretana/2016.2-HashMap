#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "usefull.h"
#include "hashmap.h"

unsigned int SIZE = TAM_INI;

// Reference: http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
/*
  Generates the hash code of a key
  Note that this do not return the hash map position
 */
//TODO fix the generation of hash codes
//TODO check if it is ok to start at 1, and end 1 before, because of the "" around the key
h_code h0(void *k, int len){
  unsigned char *p = (unsigned char*) k;
  h_code h = 2166136261L;
  int i;
  for (i = 1; i < len-1; i++){
    h = (long long int) pow((h * 16777619), p[i]);
    // printf(" %lld\n", h);
  }
  return llabs(h);
}

position h1(key *k){
  return h0(k, length(k) % SIZE);
}

position h2(key *k){
  return 1 + ( h0(k, length(k)) % (SIZE - 1) );
}
