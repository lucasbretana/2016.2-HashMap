// Colision method
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

//
#define TAM_INI 500
#define ALPHA 0.75

typedef long long int h_code_t;
typedef unsigned int position_t;
typedef char key;

h_code_t h0(void *, int);
position_t h1(key *);
position_t h2(key *);
