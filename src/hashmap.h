// Colision method
#define HELP "--help"
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

#define INITIAL_SIZE 500
#define ALPHA 0.75

typedef enum {
                Chaining = 1, 
                Linear = 2, 
                Quadratic = 3, 
                Double_Hash = 4
              } ConflictMethods_t;
extern ConflictMethods_t METHOD;
extern int HASH_SIZE;

typedef long long int h_code_t;
typedef unsigned int position_t;
typedef char key;

void hash_delete(key *);
void hash_insert(key *);
void hash_get(key *);
