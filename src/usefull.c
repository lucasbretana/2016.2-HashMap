#include <stdlib.h>

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
