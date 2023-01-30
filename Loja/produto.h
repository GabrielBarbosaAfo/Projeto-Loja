 typedef struct Produto *TProduto;
 void cadastrarProduto(FILE *p);
 void listaProduto(FILE *p);
 int pesquisaIdProduto(unsigned long id, FILE *file);
 int tamanhoProduto();
 float retornaPrecoProd(TProduto p);//retorna o preço do produto
 unsigned long retornaIdProd(TProduto p);//ertona o id do produto
 void tamanhoItemProdC(unsigned long id,unsigned int quantEstoque,FILE *file);//atualiza o estoque atraves do menu atualizar preço
 void tamanhoItemProdV(unsigned long id,unsigned int quantEstoque,FILE *file);//atualiza o estoque atraves do menu atualizar preço
 int validaQuantidade(unsigned long id,FILE *file);
 void porcentagemPositiva(float porcento,FILE *p);//atualiza o estoque atraves do menu atualizar preço
 void porcentagemNegativa(float porcento,FILE *p);//atualiza o estoque atraves do menu atualizar preço
 void porcentagemNegativaUnico(unsigned long id,float porcento,FILE *file);//atualiza o estoque atraves do menu atualizar preço
 void porcentagemPositivaUnico(unsigned long id,float porcento,FILE *file);//atualiza o estoque atraves do menu atualizar preço
 unsigned long retornaIdProdTodos(FILE *p,unsigned long idP);
TProduto novoProduto();//aloca a struct produto
