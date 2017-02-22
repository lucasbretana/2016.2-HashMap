#include <stdlib.h>
#include "usefull.h"

int length(const char *k){
  int len = 0;
  while(k[len] != '\0')
      len ++;
  return len;
}

int strcomp(const char *s1, const char *s2)
{
  for ( ; *s1 == *s2; s1++, s2++)
    if (*s1 == '\0')
	    return 0;
  return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

char *strcopy(char *s1, const char *s2)
{
    char *s = s1;
    while ((*s++ = *s2++) != 0);
    return (s1);
}
