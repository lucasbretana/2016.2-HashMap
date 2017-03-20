# HashMap
AED2 class project

### RUN
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

### Bugs encontrados na saída do professor
  - Insert do rehash não esta contanto os conflitos correntamente.  
    - Ex: output_500_linear_FNV, linha 375.  
    A chave deveria ser inserida na pos 366 e foi inserida na pos 370 mas 0 conflitos foram comtabilizados.
    Na nossa implementação nós mantivemos o número apropriado de conflitos (da posição inserida pre rehash)
  - Ainda quanto a inserção após o rehash mas apenas no caso do encadeamento existem alguns falsos conflitos.  
    - Ex: output_500_chain_FNV, linha 397  
    Um conflito é apontato ao tentar insererir uma chave na pos 47, o que indica que a cabeça da lista já esta ocupada. Entretanto após o rehash nenhum endereço foi remapeado para lá e após o rehash ainda nenhuma chave é escrita na pos 47.  
    Este mesmo erro de falso conflito após o rehash acontece várias vezes.  
  - Quanto ao get (e consequentemente quanto a delete também) no caso do linear,do hash quadrático e hash duplo algumas sondagens terminam com *falha* depois de poucas interações de me maneira que nos parece bem arbitrária. Isso não está certo, está? Caso parácemos a bsuca ao encontrar uma posição vazia na Hash alguns dados presentes na hash poderiam não ser encontrados. Na *nossa* implementação fizemos a sondagem dar a volta em toda a hash ou entrar em loop antes de poder afrimar que houve uma falha.  
