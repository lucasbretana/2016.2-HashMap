#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "usefull.h"
#include "hashmap.h"
#include "hashmapJon.h"

#define KEY_MAX_SIZE 103

// Operations
#define GET "GET"
#define DELETE "DELETE"
#define INSERT "INSERT"

// Errors
#define SUCCESS 0
#define INVALID_PARAMETER 1

// Local functions
void printHelp(char *);


int main(int argc, char **argv) {
  HashMap_t *Hash;

  if(argc != 2){
    fprintf(stderr, "Must specify the colision method! See --help");
    return INVALID_PARAMETER;
  }

  if(strcomp(argv[1], HELP) == 0){
    printHelp(argv[0]);
    return SUCCESS;
  }
  else if(strcomp(argv[1], CHAINING) == 0)
    Hash = hash_initialize(Chaining, INITIAL_SIZE);
  else if(strcomp(argv[1], LINEAR) == 0)
    Hash = hash_initialize(Linear, INITIAL_SIZE);
  else if(strcomp(argv[1], QUADRATIC) == 0)
    Hash = hash_initialize(Quadratic, INITIAL_SIZE);
  else if(strcomp(argv[1], DOUBLE_HASH) == 0)
    Hash = hash_initialize(Double_Hash, INITIAL_SIZE);
  else{
    fprintf(stderr, "Must specify a valid colision M!");
    printHelp(argv[0]);
    return INVALID_PARAMETER;
  }

  char op[7];
  key_t *in = malloc(sizeof(key_p) * KEY_MAX_SIZE);

  ReturnLog_t log;
  clock_t start = clock();
  while(scanf("%s %[^\n]s", op, in) == 2) {
    if(strcomp(op, DELETE) == 0){
      log = hash_delete(Hash, in);
      printf("%s %s %lld %u %i %u %s\n", DELETE, in, log.code, log.indH1, log.indHash, log.localConflicts, log.success ? "SUCCESS" : "FAIL");
    }else if(strcomp(op, INSERT) == 0){
      log = hash_insert(&Hash, in);
      //fprintf(stderr, "Before the NEW insert\n");
      if (log.indHash < 0)
        printf("%s %s %lld %u %u %s\n", INSERT, in, log.code, log.indH1, log.localConflicts, log.success ? "SUCCESS" : "FAIL");
      else
        printf("%s %s %lld %u %i %u %s\n", INSERT, in, log.code, log.indH1, log.indHash, log.localConflicts, log.success ? "SUCCESS" : "FAIL");
      //fprintf(stderr, "After the OLD insert\n");
    }else if(strcomp(op, GET) == 0){
      log = hash_get(Hash, in);
      printf("%s %s %lld %u %i %u %s\n", GET, in, log.code, log.indH1, log.indHash, log.localConflicts, log.success ? "SUCCESS" : "FAIL");
    }else
      fprintf(stderr, "Invalid operation (%s).", op);
  }
  printf("TOTAL CONFLICTS: %d\n",Hash->hashConflicts);
  free(in);
  hash_free(Hash);
  clock_t end = clock();
  double time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("TOTAL TIME TO RUN: %f\n", time);
  return SUCCESS;
}

/**
 * Just print the help option
 */
void printHelp(char *target){
  printf("Usage: %s [OPTION] < [ENTRY_FILE]\n\n", target);
  printf("Simulate the use of a Hash Map using the speficied M for treating colisions.\n");
  printf("  %s\t\tuse the chaining M.\n", CHAINING);
  printf("  %s\t\tuse the linear M.\n", LINEAR);
  printf("  %s\t\tuse the quadratic M.\n", QUADRATIC);
  printf("  %s\t\tuse the double hash M.\n\n", DOUBLE_HASH);
  printf("  --help\t\tshows this text.\n\n");
  printf("Examples: \n  %s %s < hash_keys.txt\n", target, DOUBLE_HASH);
  printf("  %s %s < hash_keys.txt\n", target, LINEAR);
}
