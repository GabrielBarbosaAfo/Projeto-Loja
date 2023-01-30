#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "utilitarios.h"

struct Produto{
    unsigned long id;
    unsigned int quantEstoque;
    char nome[100];
    float precoUnitario;
};

TProduto novoProduto(){
    TProduto produto=(TProduto)malloc(sizeof(struct Produto));
    if(produto)
        return produto;
    return NULL;

}

unsigned long retornaIdProdTodos(FILE *p,unsigned long idP){
    TProduto produto;
    produto=novoProduto();
    while (fread (produto, sizeof (struct Produto), 1, p)==1){
        produto->id=idP;
        free(produto);
        return idP;
    }
    free(produto);
    return -1;
}

unsigned long retornaIdProd(TProduto p){
    return p->id;
}

float retornaPrecoProd(TProduto p){
    return p->precoUnitario;
}

int tamanhoProduto(){
    return sizeof(struct Produto);
}

int validaQuantidade(unsigned long id,FILE *file){
    int posicaoProd;
    TProduto prod=novoProduto();
    posicaoProd=pesquisaIdProduto(id,file);
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fread(prod,sizeof(struct Produto),1,file);
    if(prod->quantEstoque<=0){
        free(prod);
        return -1;
    }
    else{
        free(prod);
        return 0;
    }
}

void tamanhoItemProdC(unsigned long id,unsigned int quantEstoque,FILE *file){
    int posicaoProd;
    TProduto prod=novoProduto();
    posicaoProd=pesquisaIdProduto(id,file);
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fread(prod,sizeof(struct Produto),1,file);
    prod->quantEstoque+=quantEstoque;
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fwrite(prod,sizeof(struct Produto),1,file);
    free(prod);
}

void tamanhoItemProdV(unsigned long id,unsigned int quantEstoque,FILE *file){
    int posicaoProd;
    TProduto prod=novoProduto();
    posicaoProd=pesquisaIdProduto(id,file);
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fread(prod,sizeof(struct Produto),1,file);
    prod->quantEstoque-=quantEstoque;
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fwrite(prod,sizeof(struct Produto),1,file);
    free(prod);
}

int pesquisaIdProduto(unsigned long id, FILE *file){
    TProduto produto = novoProduto();
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(produto,sizeof(struct Produto),1,file)==1){
        if(produto->id==id && produto->id>0){
            free(produto);
            return posicao;
        }
        else
            posicao++;
    }
    free(produto);
    return -1;
}

void porcentagemPositiva(float porcento,FILE *p){
    TProduto produto;
    produto=novoProduto();
    unsigned long posicao=0;
    fseek (p, 0, SEEK_SET);
    while (fread (produto, sizeof (struct Produto), 1, p)==1){
        produto->precoUnitario/=porcento;
        fseek(p,posicao*sizeof(struct Produto),SEEK_SET);
        fwrite(produto,sizeof(struct Produto),1,p);
        posicao++;
        fseek(p,posicao*sizeof(struct Produto),SEEK_SET);
    }
    free(produto);
}

void porcentagemNegativa(float porcento,FILE *p){
    TProduto produto;
    produto=novoProduto();
    unsigned long posicao=0;
    fseek (p, 0, SEEK_SET);
    while (fread (produto, sizeof (struct Produto), 1, p)==1){
        produto->precoUnitario*=porcento;
        fseek(p,posicao*sizeof(struct Produto),SEEK_SET);
        fwrite(produto,sizeof(struct Produto),1,p);
        posicao++;
        fseek(p,posicao*sizeof(struct Produto),SEEK_SET);
    }
    free(produto);
}

void porcentagemNegativaUnico(unsigned long id,float porcento,FILE *file){
    int posicaoProd;
    TProduto prod=novoProduto();
    posicaoProd=pesquisaIdProduto(id,file);
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fread(prod,sizeof(struct Produto),1,file);
    prod->precoUnitario*=porcento;
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fwrite(prod,sizeof(struct Produto),1,file);
    free(prod);
}

void porcentagemPositivaUnico(unsigned long id,float porcento,FILE *file){
    int posicaoProd;
    TProduto prod=novoProduto();
    posicaoProd=pesquisaIdProduto(id,file);
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fread(prod,sizeof(struct Produto),1,file);
    prod->precoUnitario/=porcento;
    fseek(file,posicaoProd*sizeof(struct Produto),SEEK_SET);
    fwrite(prod,sizeof(struct Produto),1,file);
    free(prod);
}

void listaProduto(FILE *p){
    TProduto produto;
    produto=novoProduto();
    fseek (p, 0, SEEK_SET);
    while (fread (produto, sizeof (struct Produto), 1, p)==1){
        printf ("\nDados do Produto\n");
        printf ("ID: %lu\n", produto->id);
        printf ("Nome: %s\n", produto->nome);
        printf ("Quantidade no Estoque: %u\n", produto->quantEstoque);
        printf ("Preco unitario: %.2f\n", produto->precoUnitario);
    }
    free(produto);
}



void cadastrarProduto(FILE *p){
    int pos;
    char nome[100];
    TProduto produto;
    produto=novoProduto();
    fseek(p,0,SEEK_END);
    printf("Bem vindo ao cadastro de produto!!!\n");
    pos=(ftell(p)/sizeof(struct Produto))+1;
    printf("O ID do seu produto e = %lu\n",produto->id=pos);
    printf("Forne�a o nome do produto:\n");
    setbuf(stdin,NULL);
    fgets(nome,100,stdin);
    maiusculo(nome,produto->nome);
    setbuf(stdin,NULL);
    printf("nome=%s\n",produto->nome);
    produto->quantEstoque=0;
    printf("quantidade em estoque = %u\n",produto->quantEstoque);
    printf("Forne�a o pre�o do produto:\n");
    scanf("%f",&produto->precoUnitario);
    printf("Pre�o=%.2f\n",produto->precoUnitario);
    fwrite(produto,sizeof(struct Produto),1,p);
    listaProduto(p);

    free(produto);
}

