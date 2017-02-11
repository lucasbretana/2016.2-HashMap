// Colision method
#define HELP "--help"
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

#define TAM_INI 500
#define ALPHA 0.75

typedef enum {
                Chaining = 1, 
                Linear = 2, 
                Quadratic = 3, 
                Double_Hash = 4
              } ConflictMethods_t;
extern const ConflictMethods_t METHOD;

typedef long long int h_code_t;
typedef unsigned int position_t;
typedef char key;

h_code_t h0(void *, int);
position_t h1(key *);
position_t h2(key *);
position_t position(key*k);
