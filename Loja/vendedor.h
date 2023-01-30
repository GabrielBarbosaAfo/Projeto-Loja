typedef struct Vendedor *TVendedor;
void cadastroVendedor(FILE *v);
void alteraVendedor(FILE *v);
void consultaVendedor(FILE *v);
void listagemVendedor(FILE *v);
void exclusaoVendedor(FILE *v);
int tamanhoVendedor();
void retornaSenhaVende(char *senha,TVendedor v);
void retornaCpfVende(char *cpf,TVendedor v);
unsigned long retornaIdVende(TVendedor v);//retorna o is da struct vendedor
int pesquisaVendCpf(char *cpf,FILE *v);//pesquisa o cpf do vendedor se estiver alguem com o id informado ele retorna posicao se não ele retorna -1
int pesquisaIdCpfVend(char *cpf, FILE *file);//pesquisa o id do vendedor se estiver alguem com o id informado ele retorna posicao se não ele retorna -1
int pesquisaIdVend(unsigned long id, FILE *file);//pesquisa o id do vendedor se estiver alguem com o id informado ele retorna posicao se não ele retorna -1
TVendedor novoVendedor();//aloca espaço para a struct vendedor
