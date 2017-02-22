#ifndef HASHMAP_JON_H
#define HASHMAP_JON_H

#include "hashmap.h"

ReturnLog_t hash_insert(HashMap_t *, key_t *);
ReturnLog_t hash_get(HashMap_t *, key_t *);
HashMap_t *hash_initialize(ConflictMethods_t);
#endif
