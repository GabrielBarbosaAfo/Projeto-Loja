typedef struct Fornecedor *TFornecedor;
void cadastroFornecedor(FILE *f);
void listagemFornecedor(FILE *f);
void consultaFornecedor(FILE *f);
void alteraFornecedor(FILE *f);
void exclusaoFornecedor(FILE *f);
int tamanhoFornecedor();
void retornaFornecedor(TFornecedor f);//retorna o tamanho da struct fornecedor
int pesquisaIdForn(unsigned long id, FILE *file);//pesquisa o id do fornecedor se a iguais retorna posicao se n retorna -1
int validaNome(char *nome,FILE *file);//valida o nome para saber se a nomes iguais
int buscaCnpj(char *cnpj,FILE *file);//valida o cnpj caso tenha cnpj iguais
TFornecedor novoFornecedor();
