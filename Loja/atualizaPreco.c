#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atualizaPreco.h"
#include "utilitarios.h"
#include "produto.h"

int listagemLista(unsigned long id, FILE *file){
    TListaAtualiza listaA;
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(&listaA,sizeof(TListaAtualiza),1,file)==1){
        if(listaA.idProduto==id){
            return posicao;
        }
        else
           posicao++;
    }
    return -1;

}

void atualizaP(FILE *atPreco,FILE *produto){
    int opcaoPT,opcaoPU,opcaoP,posicaoProd,idProd;
    unsigned long id;
    float porcento;
    TListaAtualiza listaA;

    printf("\nPara atualizar o preco digite uma das opcoes a seguir:\n");
    printf("1-Atualizar o preço de todos os produtos\n2-Atualizar o preco de um produto:\n");
    scanf("%d",&opcaoP);
    if(opcaoP==1){
        printf("Voce quer abaixar o preco ou aumentar?\n1-abaixar\n2-aumentar\n");
        scanf("%d",&opcaoPT);
        if(opcaoPT==1){
            printf("\nQual a porcentagem que voce quer aumentar:");
            scanf("%f",&porcento);
            porcentagemNegativa(porcento/100,produto);
            printf("\nProdutos com o novo preco:\n");
            listaProduto(produto);
            idProd=retornaIdProdTodos(produto,listaA.idProduto);
            while(idProd!=1){
                printf("O ID do produto:%lu\n",listaA.idProduto=id);
                dataAtual(listaA.dataAlteracao);
                printf("A data da alteração:%s\n",listaA.dataAlteracao);
                printf("A porcentagem de desconto:%.2f\n",listaA.valor=porcento);
                fseek(atPreco,0,SEEK_SET);
                fwrite(&listaA,sizeof(TListaAtualiza),1,atPreco);

            }

        }
        if(opcaoP==2){
            printf("\nQual a porcentagem que voce quer aumentar:");
            scanf("%f",&porcento);
            porcentagemPositiva(porcento/100,produto);
            printf("\nProdutos com o novo preco:\n");
            listaProduto(produto);
            idProd=retornaIdProdTodos(produto,listaA.idProduto);
            while(idProd!=1){
                printf("O ID do produto:%lu\n",listaA.idProduto=id);
                dataAtual(listaA.dataAlteracao);
                printf("A data da alteração:%s\n",listaA.dataAlteracao);
                printf("A porcentagem de desconto:%.2f\n",listaA.valor=porcento);
                fseek(atPreco,0,SEEK_SET);
                fwrite(&listaA,sizeof(TListaAtualiza),1,atPreco);

            }

        }
    }
    if(opcaoP==2){
        printf("Voce quer abaixar o preco ou aumentar?\n1-abaixar\n2-aumentar\n");
        scanf("%d",&opcaoPU);
        if(opcaoPU==1){
            printf("Informe o Id do produto a ser alterado:");
            scanf("%lu",&id);
            posicaoProd=pesquisaIdProduto(id,produto);
            if(posicaoProd!=-1){
                printf("\nQual a porcentagem que voce quer aumentar:");
                scanf("%f",&porcento);
                porcentagemNegativaUnico(id,porcento,produto);
                printf("\nProdutos com o novo preco:\n");
                listaProduto(produto);
                printf("\nListagem\n");
                printf("O ID do produto:%lu\n",listaA.idProduto=id);
                dataAtual(listaA.dataAlteracao);
                printf("A data da alteração:%s\n",listaA.dataAlteracao);
                printf("A porcentagem de desconto:%.2f\n",listaA.valor=porcento);
                fseek(atPreco,0,SEEK_SET);
                fwrite(&listaA,sizeof(TListaAtualiza),1,atPreco);

            }
        }
        if(opcaoPU==2){
            printf("\nQual a porcentagem que voce quer aumentar:");
            scanf("%f",&porcento);
            porcentagemPositiva(porcento/100,produto);
            printf("\nProdutos com o novo preco:\n");
            listaProduto(produto);
            printf("\nListagem\n");
            printf("O ID do produto:%lu\n",listaA.idProduto=id);
            dataAtual(listaA.dataAlteracao);
            printf("A data da alteração:%s\n",listaA.dataAlteracao);
            printf("A porcentagem de desconto:%.2f\n",listaA.valor=porcento);
            fseek(atPreco,0,SEEK_SET);
            fwrite(&listaA,sizeof(TListaAtualiza),1,atPreco);

        }
    }

}
