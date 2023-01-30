#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venda.h"
#include "vendedor.h"
#include "utilitarios.h"
#include "cliente.h"
#include "produto.h"
#include "fornecedor.h"

int pesquisaNotaVend(unsigned long id, FILE *file){
    TNotaFiscal vNF;
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(&vNF,sizeof(TNotaFiscal),1,file)==1){
        if(vNF.id==id){
            return posicao;
        }
        else
           posicao++;
    }
    return -1;

}

int pesquisaCompCli(int id, FILE *file){
    TNotaFiscal vNF;
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(&vNF,sizeof(TNotaFiscal),1,file)==1){
        if(vNF.idCliente==id){
            return posicao;
        }
        else
           posicao++;
    }
    return -1;
}

int pesquisaSenhaVendedor(char *senha,FILE *v){
    TVendedor vend;
    vend=novoVendedor();
    int achou=0,posicao=0;
    char aux[20];

    fseek(v,0,SEEK_SET);
    while(fread(vend,tamanhoVendedor(),1,v)==1&&!achou){
        retornaSenhaVende(aux,vend);
        if(strcmp(senha,aux)==0 && retornaIdVende(vend)>0)
            achou=1;
        else
            posicao++;
    }
    free(vend);
    if(achou)
        return posicao;
    return -1;
}

void efetuarVenda(FILE *vendaNF,FILE *produto,FILE *vend,FILE *cli,FILE *vendaINF){
    TVenda *venda;
    TProduto prod;
    TCliente cliente;
    TNotaFiscal vNF;
    TNotaItemF vNIF,aux;
    int tamanho=1,i,pIC,verifica,opcao,opcaoCli,achou,posicaoProd,validaQP,sair,posNF,dia,mes,ano;
    float total,valorT=0;
    venda=(TVenda*)malloc(sizeof(TVenda)*tamanho);
    char cpf[12],senha[20];
    unsigned long idCli,id;

    if(venda){
        printf("Para efetuar uma venda forneca os dados abaixo:\n");
        printf("CPF do vendedor:");
        setbuf(stdin,NULL);
        fgets(cpf,12,stdin);
        setbuf(stdin,NULL);
        if(pesquisaVendCpf(cpf,vend)!=-1){
            fseek(vend,pesquisaVendCpf(cpf,vend)*tamanhoVendedor(),SEEK_SET);
            printf("\nCPF Encontrado!!!");
            printf("\nForneca sua senha:");
            setbuf(stdin,NULL);
            fgets(senha,20,stdin);
            retiraEnter(senha);
            setbuf(stdin,NULL);
            if(pesquisaSenhaVendedor(cpf,vend)!=1){
                printf("Senha correta\n");
                do{
                    printf("Forneça o id do cliente:\n");
                    scanf("%lu",&idCli);
                    pIC=pesquisaIdVend(idCli,cli);
                    if(pIC!=1){
                        cliente = novoCliente();
                        fseek(cli,pIC*tamanhoCliente(),SEEK_SET);
                        fread(cliente,tamanhoFornecedor(),1,cli);
                        retornaCliente(cliente);
                        free(cliente);
                        do{
                            i=0;
                            printf("\n\nSelecione uma das opções para continuar:\n");
                            printf("1-Adicionar um Produto\n2-Alterar Produto\n3-Remover produto\n4-Gerar nota da compra:\n");
                            scanf("%d",&opcao);
                            switch(opcao){
                                case 1:
                                do{
                                    achou=0;
                                    printf("\nProdutos disponiveis:\n");
                                    listaProduto(produto);
                                    printf("Escolha o id do produto desejado:\n");
                                    scanf("%lu",&id);
                                    posicaoProd=pesquisaIdProduto(id,produto);
                                    validaQP=validaQuantidade(id,produto);
                                    if(posicaoProd!=-1 && validaQP!=-1){
                                        for(i=0;i<tamanho-1;i++){
                                            if(id==venda[i].idProduto){
                                                achou=1;
                                                printf("\nProduto ja esta no carrinho!!!\n");
                                            }

                                        }
                                        if(achou!=1 && posicaoProd!=-1){
                                            venda[i].idProduto=id;
                                            prod = novoProduto();
                                            fseek(produto,posicaoProd*tamanhoProduto(),SEEK_SET);
                                            fread(prod,tamanhoProduto(),1,produto);
                                            printf("Valor do Produto = R$ %.2f\n",retornaPrecoProd(prod));
                                            printf("Forneca a quantidade desejada do produto:\n");
                                            scanf("%u",&venda[i].quantidadeVendida);
                                            total=venda[i].quantidadeVendida*retornaPrecoProd(prod);
                                            printf("Total da compra:%.2f\n",total);
                                            venda[tamanho-1].valorVenda=retornaPrecoProd(prod);
                                            fseek(vendaNF,0,SEEK_END);
                                            fwrite(venda,sizeof(TVenda),1,vendaNF);
                                            free(prod);

                                        }

                                    }
                                    else
                                        printf("\nNenhum Produto com esse id informado ou o produto ja esta no carrinho ou não ha estoque desse produto!!!\n");

                                    printf("Deseja adicinar outro produto?\n1-sim\n2-n�o\n");
                                    scanf("%d",&sair);
                                    if(i==tamanho-1 && achou!=1){
                                        tamanho++;
                                        venda=(TVenda*)realloc(venda,sizeof(TVenda)*tamanho);
                                        if(!venda){
                                            break;
                                        }
                                    }
                                    i++;
                                }while(sair!=2);
                                for(i=0;i<tamanho-1;i++){
                                    printf("\nid Produto=%lu\n",venda[i].idProduto);
                                    printf("Valor Produto=%.2f\n",venda[i].valorVenda);
                                    printf("Quantidade do produto=%u\n",venda[i].quantidadeVendida);
                                }

                                break;

                                case 2:
                                    printf("Escolha o id do produto a ser alterado:\n");
                                    scanf("%lu",&id);
                                    for(i=0;i<tamanho-1;i++){
                                        if(id==venda[i].idProduto){
                                            venda[i].idProduto=id;
                                            prod = novoProduto();
                                            fseek(produto,posicaoProd*tamanhoProduto(),SEEK_SET);
                                            fread(prod,tamanhoProduto(),1,produto);
                                            printf("Valor do Produto = R$ %.2f\n",retornaPrecoProd(prod));
                                            printf("Forneca a quantidade desejada do produto:\n");
                                            scanf("%u",&venda[i].quantidadeVendida);
                                            total=venda[i].quantidadeVendida*retornaPrecoProd(prod);
                                            printf("Total da compra:%.2f\n",total);
                                            venda[tamanho-1].valorVenda=retornaPrecoProd(prod);
                                            fseek(vendaNF,0,SEEK_END);
                                            fwrite(venda,sizeof(TVenda),1,vendaNF);
                                            free(prod);
                                        }
                                        else
                                            printf("O produto não existe ou nao foi adicionado ao carrinho!!!\n");
                                    }

                                        for(i=0;i<tamanho-1;i++){
                                            printf("\nid Produto=%lu\n",venda[i].idProduto);
                                            printf("Valor Produto=%.2f\n",venda[i].valorVenda);
                                            printf("Quantidade do produto=%u\n",venda[i].quantidadeVendida);
                                        }

                                break;

                                case 3:
                                    printf("Escolha o id do produto a ser removido:\n");
                                    scanf("%lu",&id);
                                    for(i=0;i<tamanho-1;i++){
                                        if(id==venda[i].idProduto){
                                            venda[i]=venda[tamanho-2];
                                            tamanho--;
                                        }
                                        else
                                            printf("O produto não existe ou nao foi adicionado ao carrinho!!!\n");
                                    }
                                        for(i=0;i<tamanho;i++){
                                            printf("\nid Produto=%lu\n",venda[i].idProduto);
                                            printf("Valor Produto=%.2f\n",venda[i].valorVenda);
                                            printf("Quantidade do produto=%u\n",venda[i].quantidadeVendida);
                                        }

                                break;

                                case 4:
                                    posNF=(ftell(vendaNF)/sizeof(TNotaFiscal))+1;
                                    printf("\nO ID da sua nota fiscal e:%lu\n",vNF.id=posNF);
                                    printf("O ID do cliente e:%lu\n",vNF.idCliente=idCli);
                                    printf("O do vendedor e:%lu\n",vNF.idVendedor=pesquisaIdCpfVend(cpf,vend));
                                    dataAtual(vNF.dataCompra);
                                    printf("Data atual da compra: %s\n",vNF.dataCompra);

                                    printf("\nDeseja alterar a data da compra? 1-Sim 2-Nao\t");
                                    scanf("%d",&verifica);
                                    if(verifica==1){
                                        do{
                                            printf("\nDigite a nova data: dd/mm/aaaa\t");
                                            scanf("%d/%d/%d",&dia,&mes,&ano);
                                            achou=validaData(dia,mes,ano);
                                            if(achou==-1 && mes>12 && mes<1){
                                                printf("\nData invalida.\n");
                                            }
                                            else
                                                sprintf(vNF.dataCompra,"%.2d/%.2d/%.4d",dia,mes,ano);

                                        }while(achou==-1);
                                    }
                                    for(i=0;i<tamanho-1;i++){
                                        valorT+=venda[i].valorVenda*venda[i].quantidadeVendida;
                                    }

                                    vNF.ValorTotal=valorT;
                                    fseek(vendaNF,0,SEEK_END);
                                    fwrite(&venda,sizeof(TNotaFiscal),1,vendaNF);

                                    fseek(vendaNF,sizeof(TNotaFiscal),SEEK_END);
                                    fread(&venda,sizeof(TNotaFiscal),1,vendaNF);
                                    printf("\n\nID Nota fiscal:%lu\n",vNF.id);
                                    printf("ID cliente:%lu\n",vNF.idCliente);
                                    printf("ID vendedor:%lu\n",vNF.idVendedor);
                                    printf("Data da compra:%s",vNF.dataCompra);
                                    printf("\nValor Total:%.2f",vNF.ValorTotal);

                                    fseek(vendaINF, -20,SEEK_END);
                                    fread (&aux, sizeof (TNotaItemF), 1, vendaINF);
                                    if(ftell(vendaINF)<=0){
                                        aux.id=1;
                                        vNIF.id=aux.id;
                                    }
                                    else{
                                        vNIF.id=aux.id+1;
                                    }

                                    for(i=0;i<tamanho-1;i++){

                                        printf("\nO ID da sua nota de venda de item:%lu\n",vNIF.id);
                                        printf("O id da nota fiscal é:%lu\n",vNIF.idNotaFiscal=vNF.id);
                                        printf("O id do produto é:%lu\n",vNIF.idProduto=venda[i].idProduto=id);
                                        printf("O valor da venda:%.2f\n",vNIF.valorVenda=venda[i].valorVenda);
                                        printf("Quantidade comprada:%u\n\n",vNIF.quantidade=venda[i].quantidadeVendida);
                                        fseek(vendaINF,0,SEEK_END);
                                        fwrite(&vNIF,sizeof(TNotaItemF),1,vendaINF);
                                        tamanhoItemProdV(vNIF.idProduto,vNIF.quantidade,produto);
                                }

                                break;
                            }

                            printf("\nDeseja sair do menu de vendas");
                            printf("(lembrando que se voce sair sem gerar a nota fiscal voce perde o que voce comprou):\n1-Sim\n2-Não\n");
                            scanf("%d",&sair);
                        }while(sair!=1);
                        free(venda);
                    }
                    else
                        printf("\nNenhum ID encontrado!!!\n");

                    printf("\nAlterar o cliente(Se a opcao for não voce saira do menu de vendas):\n1-sim\n2-nao\n");
                    scanf("%d",&opcaoCli);
                }while(opcaoCli!=2);
            }
            else
                printf("Senha incorreta!!!\n");
        }
        else
            printf("\nNenhum cpf encontrado!!!\n");
    }
    else
        printf("\nA aloc��o falhou\n");
}
