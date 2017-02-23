#include <stdlib.h>
#include "usefull.h"

/**
 * Counts the length of a function
 */
int length(const char *k){
  int len = 0;
  if(k == NULL) return 0;
  while(k[len] != '\0')
      len ++;
  return len;
}

/**
 * Compares the two strings s1 and s2.  It returns an integer less than,
 * equal to, or greater than zero if s1 is found, respectively, to be less than,
 * to match, or be greater than s2.
 */
int strcomp(const char *s1, const char *s2)
{
  if((s1 == NULL) && (s2 == NULL)) return 0;
  if(s1 == NULL) return 1;
  if(s2 == NULL) return -1;
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
