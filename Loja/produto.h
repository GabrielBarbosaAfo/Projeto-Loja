 typedef struct Produto *TProduto;
 void cadastrarProduto(FILE *p);
 void listaProduto(FILE *p);
 int pesquisaIdProduto(unsigned long id, FILE *file);
 int tamanhoProduto();
 float retornaPrecoProd(TProduto p);//retorna o pre�o do produto
 unsigned long retornaIdProd(TProduto p);//ertona o id do produto
 void tamanhoItemProdC(unsigned long id,unsigned int quantEstoque,FILE *file);//atualiza o estoque atraves do menu atualizar pre�o
 void tamanhoItemProdV(unsigned long id,unsigned int quantEstoque,FILE *file);//atualiza o estoque atraves do menu atualizar pre�o
 int validaQuantidade(unsigned long id,FILE *file);
 void porcentagemPositiva(float porcento,FILE *p);//atualiza o estoque atraves do menu atualizar pre�o
 void porcentagemNegativa(float porcento,FILE *p);//atualiza o estoque atraves do menu atualizar pre�o
 void porcentagemNegativaUnico(unsigned long id,float porcento,FILE *file);//atualiza o estoque atraves do menu atualizar pre�o
 void porcentagemPositivaUnico(unsigned long id,float porcento,FILE *file);//atualiza o estoque atraves do menu atualizar pre�o
 unsigned long retornaIdProdTodos(FILE *p,unsigned long idP);
TProduto novoProduto();//aloca a struct produto
