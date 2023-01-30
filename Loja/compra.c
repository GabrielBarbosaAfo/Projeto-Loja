#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "compra.h"
#include "fornecedor.h"
#include "produto.h"
#include "utilitarios.h"

int pesquisaIdCompra(unsigned long id, FILE *file){
    TCompra car;
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(&car,sizeof(TCompra),1,file)==1){
        if(car.idProduto==id && car.idProduto>0){
            return posicao;
        }
        else
            posicao++;
    }
    return -1;
}

void efetuarCompra(FILE *comp,FILE *fornecedor,FILE *produto,FILE *compItem){
    TCompra *car;
    TFornecedor forne;
    TProduto prod;
    TNotaCompra notaComp;
    TItemNotaC itemNota,aux;
    int tamanho=1,i,posicaoFor,posicaoProd,opcao,sair,achou,posNC,verifica,dia,mes,ano;
    car=(TCompra*)malloc(sizeof(TCompra)*tamanho);
    float total,valorT=0;
    unsigned long id,idForn;
    if(car){
        printf("Para efetuar uma compra digite o id do Fornecedor:\n");
        scanf("%lu",&idForn);
        posicaoFor=pesquisaIdForn(idForn,fornecedor);
        if(posicaoFor!=-1){
            forne = novoFornecedor();
            fseek(fornecedor,posicaoFor*tamanhoFornecedor(),SEEK_SET);
            fread(forne,tamanhoFornecedor(),1,fornecedor);
            retornaFornecedor(forne);
            free(forne);
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
                        if(posicaoProd!=-1){
                            for(i=0;i<tamanho-1;i++)
                                if(id==car->idProduto){
                                    achou=1;
                                    printf("\nProduto ja esta no carrinho!!!\n");
                                }
                            if(achou!=1 && posicaoProd!=-1){
                                car[i].idProduto=id;
                                prod = novoProduto();
                                fseek(produto,posicaoProd*tamanhoProduto(),SEEK_SET);
                                fread(prod,tamanhoProduto(),1,produto);
                                printf("Valor do Produto = R$ %.2f\n",retornaPrecoProd(prod));
                                printf("Forneca a quantidade desejada do produto:\n");
                                scanf("%u",&car[i].quantidade);
                                total=car[i].quantidade*retornaPrecoProd(prod);
                                printf("Total da compra:%.2f\n",total);
                                car[tamanho-1].valorUnitario=retornaPrecoProd(prod);
                                fseek(comp,0,SEEK_END);
                                fwrite(car,sizeof(TCompra),1,comp);
                                free(prod);

                            }

                        }
                        else
                            printf("\nNenhum Produto com esse id informado ou o produto ja esta no carrinho!!!\n");

                        printf("Deseja adicinar outro produto?\n1-sim\n2-n�o\n");
                        scanf("%d",&sair);
                        if(i==tamanho-1 && achou!=1){
                            tamanho++;
                            car=(TCompra*)realloc(car,sizeof(TCompra)*tamanho);
                            if(!car){
                            break;
                            }
                        }
                        i++;
                    }while(sair!=2);

                    break;

                    case 2:
                        printf("Escolha o id do produto a ser alterado:\n");
                        scanf("%lu",&id);
                        for(i=0;i<tamanho-1;i++){
                            if(id==car[i].idProduto){
                                car[i].idProduto=id;
                                prod = novoProduto();
                                fseek(produto,posicaoProd*tamanhoProduto(),SEEK_SET);
                                fread(prod,tamanhoProduto(),1,produto);
                                printf("Valor do Produto = R$ %.2f\n",retornaPrecoProd(prod));
                                printf("Forne�a a quantidade desejada do produto:\n");
                                scanf("%u",&car[i].quantidade);
                                total=car[i].quantidade*retornaPrecoProd(prod);
                                printf("Total da compra:%.2f\n",total);
                                car[tamanho-1].valorUnitario=retornaPrecoProd(prod);
                                fseek(comp,0,SEEK_END);
                                fwrite(car,sizeof(TCompra),1,comp);
                                free(prod);
                            }
                            else
                                printf("O produto não existe ou nao foi adicionado ao carrinho!!!\n");
                        }

                            for(i=0;i<tamanho-1;i++){
                                printf("\nid Produto=%lu\n",car[i].idProduto);
                                printf("Valor Produto=%.2f\n",car[i].valorUnitario);
                                printf("Quantidade do produto=%u\n",car[i].quantidade);
                            }

                    break;

                    case 3:
                        printf("Escolha o id do produto a ser removido:\n");
                        scanf("%lu",&id);
                        for(i=0;i<tamanho-1;i++){
                            if(id==car[i].idProduto){
                                car[i]=car[tamanho-2];
                                tamanho--;
                            }
                            else
                                printf("O produto não existe ou nao foi adicionado ao carrinho!!!\n");
                        }
                            for(i=0;i<tamanho-1;i++){
                                printf("\nid Produto=%lu\n",car[i].idProduto);
                                printf("Valor Produto=%.2f\n",car[i].valorUnitario);
                                printf("Quantidade do produto=%u\n",car[i].quantidade);
                            }

                    break;

                    case 4:
                        posNC=(ftell(comp)/sizeof(TNotaCompra))+1;
                        printf("\nO id da nota da sua compra e = %lu\n",notaComp.id=posNC);
                        printf("Fornecedor id=%lu\n",notaComp.idFornecedor=idForn);
                        dataAtual(notaComp.dataCompra);
                        printf("Data atual da compra: %s",notaComp.dataCompra);

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
                                    sprintf(notaComp.dataCompra,"%.2d/%.2d/%.4d",dia,mes,ano);

                            }while(achou==-1);
                        }
                        for(i=0;i<tamanho-1;i++){
                            valorT+=car[i].valorUnitario*car[i].quantidade;
                        }

                        notaComp.valorTotal=valorT;
                        fseek(comp,0,SEEK_END);
                        fwrite(&notaComp,sizeof(TNotaCompra),1,comp);

                        fseek(comp,sizeof(TNotaCompra),SEEK_END);
                        fread(&notaComp,sizeof(TNotaCompra),1,comp);
                        printf("\n\nID da Nota de Compra:%lu\n",notaComp.id);
                        printf("ID Fornecedor:%lu\n",notaComp.idFornecedor);
                        printf("Data da Compra:%s\n",notaComp.dataCompra);
                        printf("Valor:%.2f\n\n",notaComp.valorTotal);

                        fseek(compItem, -20,SEEK_END);
                            fread (&aux, sizeof (TItemNotaC), 1, compItem);
                            if(ftell(compItem)<0){
                                aux.id=(ftell(compItem)/sizeof(TItemNotaC))+1;
                            }
                            else{
                                itemNota.id=aux.id+1;
                            }

                        for(i=0;i<tamanho-1;i++){

                            printf("\nO ID da sua nota de compra de item:%lu\n",itemNota.id);
                            printf("O id do produto é:%lu\n",itemNota.idProduto=car[i].idProduto);
                            printf("O id da nota das compras:%lu\n",itemNota.IdNotaCompra=notaComp.id);
                            printf("A quantidade comprada do item:%u\n",itemNota.quantidade=car[i].quantidade);
                            printf("Valor unitario do item:%.2f\n\n",itemNota.valorUnitario=car[i].valorUnitario);
                            fseek(compItem,0,SEEK_END);
                            fwrite(&itemNota,sizeof(TItemNotaC),1,compItem);
                            tamanhoItemProdC(itemNota.idProduto,itemNota.quantidade,produto);
                        }

                    break;

                }
                printf("Deseja sair do menu de compras");
                printf("(lembrando que se voce sair sem gerar a nota fiscal voce perde o que voce comprou):\n1-Sim\n2-Não\n");
                scanf("%d",&sair);
            }while(sair!=1);
            free(car);
        }
        else
            printf("\nNenhum fornecedor com esse id cadastrado!!!\n");
    }
    else
        printf("\nFalha ao alocar memoria!!!\n");


}
