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
extern const ConflictMethods_t METHOD;
extern int HASH_SIZE;

typedef long long int h_code_t;
typedef unsigned int position_t;
typedef char key;

extern void hash_delete(char *);
extern void hash_insert(char *);
extern void hash_get(char *);
