// Colision method
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

//
#define TAM_INI 500
#define ALPHA 0.75

typedef long long int code;
// int64_t code;
typedef char key;

code h0(void *, int);
code h1(key *);
code h2(key *);
