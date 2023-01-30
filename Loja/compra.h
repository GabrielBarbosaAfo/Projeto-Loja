void efetuarCompra(FILE *comp,FILE *fornecedor,FILE *produto,FILE *compItem);
int pesquisaIdCompra(unsigned long id, FILE *file);
int validaData(int dia,int mes,int ano);
typedef struct{
    unsigned long idProduto;
    unsigned int quantidade;
    float valorUnitario;
}TCompra;
typedef struct{
    unsigned long id,idFornecedor;
    char dataCompra[11];
    float valorTotal;
}TNotaCompra;
typedef struct{
    unsigned long id,idProduto,IdNotaCompra;
    unsigned int quantidade;
    float valorUnitario;
}TItemNotaC;
