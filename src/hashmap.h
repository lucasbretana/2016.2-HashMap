// Colision method
#define HELP "--help"
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

#define INITIAL_SIZE 500
#define ALPHA 0.75

typedef long long int h_code_t;
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
                void **keys;
                int size;
                ConflictMethods_t method;
} HashMap_t;

/*extern ConflictMethods_t METHOD;
extern int HASH_SIZE;
extern key **HashMap;*/

HashMap_t *hash_initialize(ConflictMethods_t);
void hash_delete(HashMap_t *, key_t *);
void hash_insert(HashMap_t *, key_t *);
void hash_get(HashMap_t *, key_t *);
