# HashMap
AED2 class project

# Reference: http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx

# To generate the debugging symbols export a variable DEBUG, with -g i.e. export DEBUG=-g

# RUN
Usage: ./HashMap.out [OPTION] < [ENTRY_FILE]

Simulate the use of a Hash Map using the speficied method for treating colisin.
  -encadeamento		use the chaining method.
  -linear		    use the linear method.
  -quadratica		use the quadratic method.
  -hash_duplo		use the double hash method.
  --help		    shows this text.

Examples:  
  ./HashMap.out -hash_duplo < hash_keys.txt  
  ./HashMap.out -linear < keys.txt
