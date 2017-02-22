#ifndef HASHMAP_JON_H
#define HASHMAP_JON_H

#include "hashmap.h"

int hash_insert(HashMap_t *, key_t *);
void hash_get(HashMap_t *, key_t *);
HashMap_t *hash_initialize(ConflictMethods_t);
#endif
