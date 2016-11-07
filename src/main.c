#include <stdio.h>
#include <string.h>
#include "usefull.h"
#include "hashmap.h"

void printHelp(char *);
short int METHOD = 0;

int main(int argc, char **argv) {
  if(argc != 2){
    fprintf(stderr, "Must specify the colision method! See --help");
    return INVALID_PARAMETER;
  }

  if(strcomp(argv[1], HELP) == 0){
    printHelp(argv[0]);
    return SUCCESS;
  }
  else if(strcomp(argv[1], CHAINING) == 0)
    METHOD = 1;
  else if(strcomp(argv[1], LINEAR) == 0)
    METHOD = 2;
  else if(strcomp(argv[1], QUADRATIC) == 0)
    METHOD = 3;
  else if(strcomp(argv[1], DOUBLE_HASH) == 0)
    METHOD = 4;
  else{
    fprintf(stderr, "Must specify a valid colision method!");
    printHelp(argv[0]);
    return INVALID_PARAMETER;
  }

  char op[7], in[100];
  h_code_t code = 0L;
  position_t pos = 0;
  while(scanf("%s %s", op, in) == 2){
    scanf("%s %s", op, in);
    code = h0(in, length(in));
    pos = position(code);
  }

 return SUCCESS;
}

void printHelp(char *target){
  printf("Usage: %s [OPTION] < [ENTRY_FILE]\n\n", target);
  printf("Simulate the use of a Hash Map using the speficied method for treating colisin.\n");
  printf("  %s\t\tuse the chaining method.\n", CHAINING);
  printf("  %s\t\tuse the linear method.\n", LINEAR);
  printf("  %s\t\tuse the quadratic method.\n", QUADRATIC);
  printf("  %s\t\tuse the double hash method.\n\n", DOUBLE_HASH);
  printf("  --help\t\tshows this text.\n\n");
  printf("Examples: \n  %s %s < hash_keys.txt\n", target, DOUBLE_HASH);
  printf("  %s %s < keys.txt\n", target, LINEAR);
}
