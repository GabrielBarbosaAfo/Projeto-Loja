#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cliente.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "produto.h"
#include "venda.h"
#include "compra.h"
#include "atualizaPreco.h"

void menuCliente();
void menuVendedor();
void menuFornecedor();
void menuProduto();
void menuVenda();
void menuCompra();
void atualizaPreco();
void relatorios();

int main(){
    int opcao;
    setlocale(LC_ALL,"portuguese");
    do{
        printf("\n\nBem vindo a loja!!!\nEscolha a opcao em que voce se enquadra:");
        printf("\n1-Cliente\n2-Vendedor\n3-Fornecedor\n4-Cadastrar um produto\n5-Efetuar uma venda\n6-Efetuar uma compra\n7-Atualizar preco\n8-Sair da loja\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                menuCliente();
                break;
            case 2:
                menuVendedor();
                break;
            case 3:
                menuFornecedor();
                break;
            case 4:
                menuProduto();
                break;
            case 5:
                menuVenda();
                break;
            case 6:
                menuCompra();
                break;
            case 7:
                atualizaPreco();
                break;
        }
    } while (opcao != 8);
  return 0;
}

void menuCliente(){
    int opcao,sair;
    FILE *cliente;
    cliente=fopen("cliente.dat","rb+");
    if(cliente==NULL)
        cliente=fopen("cliente.dat","wb+");
    if(cliente!=NULL){
        do{
        printf("\nEscolha a opcao desejada no Menu do Cliente:\n");
        printf("\n1-Cadastro\n2-Alteração\n3-Consulta\n4-Listagem\n5-Exclusão\n6-Sair do Menu do Cliente\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                cadastroCliente(cliente);

            break;

            case 2:
                alteraCliente(cliente);

            break;

            case 3:
                consultaCliente(cliente);

            break;

            case 4:
                listagemCliente(cliente);

            break;

            case 5:
                exclusaoCliente(cliente);

            break;
        }
        printf("\nDeseja abandonar o menu do cliente?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
        }while(sair!=1);
            fclose(cliente);
    }
}

void menuVendedor(){
    int opcao,sair;
    FILE *vendedor;
    vendedor=fopen("vendedor.dat","rb+");
    if(vendedor==NULL)
    vendedor=fopen("vendedor.dat","wb+");
    if(vendedor!=NULL){
        do{
            printf("\nEscolha a opcao desejada no Menu do Vendedor:\n");
            printf("1-Cadastro\n2-Alteração\n3-Consulta\n4-Listagem\n5-Exclusão\n6-Sair do Menu do Vendedor\n");
            scanf("%d",&opcao);
            switch(opcao){
                case 1:
                    cadastroVendedor(vendedor);

                break;

                case 2:
                    alteraVendedor(vendedor);

                break;

                case 3:
                    consultaVendedor(vendedor);

                break;

                case 4:
                    listagemVendedor(vendedor);

                break;

                case 5:
                    exclusaoVendedor(vendedor);

                break;
            }

            printf("\nDeseja abandonar o menu do vendedor?\n1-sim\t2-nao\n");
            scanf("%d",&sair);
        }while(sair!=1);
        fclose(vendedor);
    }
}

void menuFornecedor(){

    int opcao,sair;
    FILE *fornecedor;
    fornecedor=fopen("fornecedor.dat","rb+");
    if(fornecedor==NULL)
    fornecedor=fopen("fornecedor.dat","wb+");
    if(fornecedor!=NULL){
        do{
            printf("\nEscolha a opcao desejada no Menu do fornecedor:\n");
            printf("1-Cadastro\n2-Alteração\n3-Consulta\n4-Listagem\n5-Exclusão\n6-Sair do Menu do Fornecedor\n");
            scanf("%d",&opcao);
            switch(opcao){
                case 1:
                    cadastroFornecedor(fornecedor);
                break;

                case 2:
                    alteraFornecedor(fornecedor);
                break;

                case 3:
                    consultaFornecedor(fornecedor);

                break;

                case 4:
                    listagemFornecedor(fornecedor);

                break;

                case 5:
                    exclusaoFornecedor(fornecedor);

                break;
            }

            printf("\nDeseja abandonar o menu do fornecedor?\n1-sim\t2-nao\n");
            scanf("%d",&sair);
        }while(sair!=1);
        fclose(fornecedor);
    }
}

void menuProduto(){
    int sair;
    FILE *produto;
    produto=fopen("produto.dat","rb+");
    if(produto==NULL)
        produto=fopen("produto.dat","wb+");
    if(produto!=NULL){
       do{
            cadastrarProduto(produto);

            printf("\nDeseja abandonar o cadastro de produtos?\n1-sim\t2-nao\n");
            scanf("%d",&sair);
       }while(sair!=1);
    fclose(produto);
    }
}
void menuVenda(){
    int sair;
    FILE *vendaNF;
    vendaNF=fopen("vendaNF.dat","rb+");
    if(vendaNF==NULL)
        vendaNF=fopen("vendaNF.dat","wb+");
    if(vendaNF!=NULL){
        FILE *vendaINF;
        vendaINF=fopen("vendaINF.dat","rb+");
        if(vendaINF==NULL)
            vendaINF=fopen("vendaINF.dat","wb+");
        if(vendaINF!=NULL){
            FILE *produto;
            produto=fopen("produto.dat","rb+");
            if(produto==NULL)
                produto=fopen("produto.dat","wb+");
            if(produto!=NULL){
                FILE *vendedor;
                vendedor=fopen("vendedor.dat","rb+");
                if(vendedor==NULL)
                    vendedor=fopen("vendedor.dat","wb+");
                if(vendedor!=NULL){
                    FILE *cliente;
                    cliente=fopen("cliente.dat","rb+");
                    if(cliente==NULL)
                        cliente=fopen("cliente.dat","wb+");
                    if(cliente!=NULL){
                        do{
                            efetuarVenda(vendaNF,produto,vendedor,cliente,vendaINF);

                            printf("\nDeseja para de vender?\n1-sim\t2-nao\n");
                            scanf("%d",&sair);
                        }while(sair!=1);
                    fclose(cliente);
                    }
                fclose(vendedor);
                }
            fclose(produto);
            }
        fclose(vendaNF);
        }
    fclose(vendaINF);
    }
}

void menuCompra(){
    FILE *compra;
    compra=fopen("compra.dat","rb+");
    if(compra==NULL)
        compra=fopen("compra.dat","wb+");
    if(compra!=NULL){
        FILE *compraItem;
        compraItem=fopen("compraItem.dat","rb+");
        if(compraItem==NULL)
            compraItem=fopen("compraItem.dat","wb+");
        if(compraItem!=NULL){
            FILE *fornecedor;
            fornecedor=fopen("fornecedor.dat","rb+");
            if(fornecedor==NULL)
                fornecedor=fopen("fornecedor.dat","wb+");
            if(fornecedor!=NULL){
                FILE *produto;
                produto=fopen("produto.dat","rb+");
                if(produto==NULL)
                    produto=fopen("produto.dat","wb+");
                if(produto!=NULL){
                    FILE *vendaNF;
                    vendaNF=fopen("vendaNF.dat","rb+");
                    if(vendaNF==NULL)
                        vendaNF=fopen("vendaNF.dat","wb+");
                    if(vendaNF!=NULL){
                        FILE *vendaINF;
                        vendaINF=fopen("vendaINF.dat","rb+");
                        if(vendaINF==NULL)
                            vendaINF=fopen("vendaINF.dat","wb+");
                        if(vendaINF!=NULL){


                            efetuarCompra(compra,fornecedor,produto,compraItem);

                        fclose(vendaINF);
                        }
                    fclose(vendaNF);
                    }
                fclose(produto);
                }
            fclose(compra);
            }
        fclose(fornecedor);
        }
    fclose(compraItem);
    }
}

void atualizaPreco(){
    FILE *atPreco;
    atPreco=fopen("atPreco.dat","rb+");
    if(atPreco==NULL)
        atPreco=fopen("atPreco.dat","wb+");
    if(atPreco!=NULL){
        FILE *produto;
        produto=fopen("produto.dat","rb+");
        if(produto==NULL)
            produto=fopen("produto.dat","wb+");
        if(produto!=NULL){

            atualizaP(atPreco,produto);

            fclose(produto);
        }
        fclose(atPreco);
    }
}