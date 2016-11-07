#include <stdlib.h>
#include "usefull.h"

int length(const char *k){
  int len = 0;
  while(k[len] != '\0')
      len ++;
  return len;
}

int strcomp(const char *s1, const char *s2){
  if((s1 == NULL) && (s2 == NULL)) return 0;
  if(s1 == NULL) return length(s2) * -1;
  if(s2 == NULL) return length(s1);

  int l1 = length(s1);
  int l2 = length(s2);
  if(l1 != l2)
    return l1 - l2;

  int i = 0;
  while((s1[i] != '\0') && (s2[i] != '\0')){
    if(s1[i] != s2[i]){
      return s1[i] - s2[i];
    }
    i++;
  }
  return 0;
}

h_code_t absh(h_code_t hash){
  if(hash < 0)
    return hash * -1;
  else
    return hash;
}
