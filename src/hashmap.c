#include <stdlib.h>
#include "usefull.h"
#include "hashmap.h"

unsigned int SIZE = TAM_INI;

// Reference: http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
pos h(void *k, int len){
  unsigned char *p = k;
  unsigned h = 2166136261;
  int i;
  for (i = 0; i < len; i++){
    h = (h * 16777619) ^ p[i];
  }
  return h;
}

pos h1(key *k){
  return h(k, length(k)) % SIZE;
}

pos h2(key *k){
  return 1 + ( h(k, length(k)) % (SIZE - 1) );
}
