// Colision method
#define CHAINING "-encadeamento"
#define LINEAR "-linear"
#define QUADRATIC "-quadratica"
#define DOUBLE_HASH "-hash_duplo"

//
#define TAM_INI 500
#define ALPHA 0.75

typedef long long int h_code;
typedef unsigned int position;
typedef char key;

h_code h0(void *, int);
position h1(key *);
position h2(key *);
