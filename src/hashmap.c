#include <stdio.h>
#include <stdlib.h>
#include "usefull.h"
#include "hashmap.h"

unsigned int SIZE = TAM_INI;

// Reference: http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
code h0(void *k, int len){
  unsigned char *p = (unsigned char*) k;
  long long h = 2166136261;
  int i;
  for (i = 0; i < len; i++){
    h = (h * 16777619) ^ p[i];
  }
  return llabs(h);
}

code h1(key *k){
  return llabs(h0(k, length(k)) % SIZE);
}

code h2(key *k){
  return llabs(1 + ( h0(k, length(k)) % (SIZE - 1) ));
}
