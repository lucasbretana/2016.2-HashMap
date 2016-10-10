// Erro code
#define SUCCESS 0
#define INVALID_PARAMETER 1

// Colision method
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

//
#define TAM_INI 500
#define ALPHA 0.75

typedef unsigned int pos;
typedef char key;

pos h(void *, int);
pos h1(key *);
pos h2(key *);
