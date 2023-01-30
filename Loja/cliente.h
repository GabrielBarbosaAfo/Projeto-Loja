#include <stdio.h>
typedef struct Cliente *TCliente;
void cadastroCliente(FILE *c);
void alteraCliente(FILE *c);
void consultaCliente(FILE *c);
void listagemCliente(FILE *c);
void exclusaoCliente(FILE *c);
int pesquisaId(unsigned long id, FILE *file);//pesquisa o id para ver se tem um igual
int pesquisa(char *cpf,FILE *file);//pesquisa o cpf para não ter iguais no cadstramento
void retornaCliente(TCliente c);//exibe os parametros da struct cliente
int tamanhoCliente();//retorna o tamanho da struct cliente
TCliente novoCliente();//aloca memoria para a struct cleinte

