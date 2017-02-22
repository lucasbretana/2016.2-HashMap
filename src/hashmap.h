#ifndef HASHMAP_H
#define HASHMAP_H
// Colision method
#define HELP "--help"
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"
// Static values
#define INITIAL_SIZE 500
#define ALPHA 0.75

typedef long long int h_code_t;
typedef unsigned int bulk_t;
typedef unsigned int position_t;
typedef char key_t;
typedef key_t *key_p;
typedef enum _ConflictMethods_t{
                Chaining = 1,
                Linear = 2,
                Quadratic = 3,
                Double_Hash = 4
} ConflictMethods_t;
typedef struct _HashMap_t{
                void *keys;
                bulk_t size;
                ConflictMethods_t method;
                int numConflicts;
                unsigned long long int insertTime;
                unsigned long long int deleteTime;
                unsigned long long int getTime;
} HashMap_t;
typedef enum _boolean_t{
              true,
              false = 0
} Boolean_t;
typedef struct _ReturnLog{
                h_code_t code;
                unsigned int indH1;
                unsigned int indHash;
                unsigned int numConflicts;
                Boolean_t success;
} ReturnLog_t;

/*extern ConflictMethods_t METHOD;
extern int HASH_SIZE;
extern key **HashMap;*/

h_code_t h0(void *, int);
position_t h1(key_p, bulk_t);
position_t h2(key_p, bulk_t);
position_t position(key_p);

ReturnLog_t hash_delete(HashMap_t *, key_t *);
// void hash_insert(HashMap_t *, key_t *);
// void hash_get(HashMap_t *, key_t *);

#endif
