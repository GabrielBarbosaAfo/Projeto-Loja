void atualizaP(FILE *atPreco,FILE *produto);
int listagemLista(unsigned long id, FILE *file);
typedef struct{
    unsigned long idProduto;
    char dataAlteracao[11];
    float valor;
}TListaAtualiza;
