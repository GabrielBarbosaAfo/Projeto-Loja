void efetuarVenda(FILE *vendaNF,FILE *produto,FILE *vend,FILE *cli,FILE *vendaINF);
int pesquisaNotaVend(unsigned long id, FILE *file);
int pesquisaCompCli(int id, FILE *file);
typedef struct{
    unsigned long idProduto;
    unsigned int quantidadeVendida;
    float valorVenda;
}TVenda;
typedef struct{
    unsigned long id,idCliente,idVendedor;
    char dataCompra[11];
    float ValorTotal;
}TNotaFiscal;
typedef struct{
    unsigned long id,idNotaFiscal,idProduto;
    float valorVenda;
    unsigned int quantidade;
}TNotaItemF;
