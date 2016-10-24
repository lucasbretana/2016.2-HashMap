#include <stdlib.h>
#include "usefull.h"

int length(char *k){
  int len = 0;
  while(k[len] != '\0')
      len ++;
  return len;
}

int strcomp(char *s1, char *s2){
  if((s1 == NULL) && (s2 == NULL)) return 0;
  if(s1 == NULL) return length(s2) * -1;
  if(s2 == NULL) return length(s1);

  int l1 = length(s1);
  int l2 = length(s2);
  if(l1 != l2)
    return l1 - l2;

  int i = 0;
  while((s1[i] != '\0') && (s2[i] != '\0')){
    l1 = s1[i] - s2[i];
    i++;
  }
  return l1;
}

h_code_t absh(h_code_t hash){
  if(hash < 0)
    return hash * -1;
  else
    return hash;
}

// h_code_t powlld(long long int base, int e){
//   long long int res = 1L;
//   // piece of cake
//   // if(base % 2 == 0){
//   //   if(base == 2)
//   //     return base << e;
//   //   return ;
//   // }
//   for(int i=0 ; i<e ; i++){
//     res = res * base;
//   }
//   return base;
// }
