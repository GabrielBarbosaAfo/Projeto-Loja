#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"
#include "utilitarios.h"

struct Fornecedor{
    unsigned long id;
    char nome[100],cnpj[15],email[50],telefone[15];
};

int tamanhoFornecedor(){
    return sizeof(struct Fornecedor);
}
void retornaFornecedor(TFornecedor f){
    printf("Id=%lu\n",f->id);
    printf("nome=%s\n",f->nome);
    printf("cnpj=%s\n",f->cnpj);
    printf("email=%s\n",f->email);
    printf("telefone=%s\n",f->telefone);
}

TFornecedor novoFornecedor(){
    TFornecedor fornecedor=(TFornecedor)malloc(sizeof(struct Fornecedor));
    if(fornecedor)
        return fornecedor;
    return NULL;

}

int validaNome(char *nome,FILE *file){
    TFornecedor fornece;
    fornece=novoFornecedor();
    int posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(fornece,sizeof(struct Fornecedor),1,file)==1){
        if(strcmp(nome,fornece->nome)==0 && fornece->id>0){
            free(fornece);
            return posicao;
        }
        else
            posicao++;
    }
    free(fornece);
    return -1;

}

int buscaCnpj(char *cnpj,FILE *file){
    TFornecedor fornece;
    fornece=novoFornecedor();
    int posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(fornece,sizeof(struct Fornecedor),1,file)==1){
        if(strcmp(cnpj,fornece->cnpj)==0 && fornece->id>0){
            free(fornece);
            return posicao;
        }
        else
            posicao++;
    }
    free(fornece);
    return -1;
}

int pesquisaIdForn(unsigned long id, FILE *file){
    TFornecedor fornece = novoFornecedor();
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(fornece,sizeof(struct Fornecedor),1,file)==1){
        if(fornece->id==id && fornece->id>0){
            free(fornece);
            return posicao;
        }
        else
            posicao++;
    }
    free(fornece);
    return -1;
}

int validaCnpj(char *cnpj){
    int i;

    int multiplica1[12]={5,4,3,2,9,8,7,6,5,4,3,2};
    int multiplica2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};
    int soma=0;
    int resto;
    int digito1,digito2;
    int cnpjauxiliar[12];
    int cnpjauxiliar2[13];

    cnpjauxiliar[0]=cnpj[0]-48;
    cnpjauxiliar[1]=cnpj[1]-48;
    cnpjauxiliar[2]=cnpj[2]-48;
    cnpjauxiliar[3]=cnpj[3]-48;
    cnpjauxiliar[4]=cnpj[4]-48;
    cnpjauxiliar[5]=cnpj[5]-48;
    cnpjauxiliar[6]=cnpj[6]-48;
    cnpjauxiliar[7]=cnpj[7]-48;
    cnpjauxiliar[8]=cnpj[8]-48;
    cnpjauxiliar[9]=cnpj[9]-48;
    cnpjauxiliar[10]=cnpj[10]-48;
    cnpjauxiliar[11]=cnpj[11]-48;

    for(i=0;i<12;i++){

     soma=soma+cnpjauxiliar[i]* multiplica1[i];
    }
    resto=soma%11;
    if(resto<2)
        resto=0;
        else
            resto=11-resto;
    digito1=resto;


    soma=0;
    //segundo digito

    cnpjauxiliar2[0]=cnpj[0]-48;
    cnpjauxiliar2[1]=cnpj[1]-48;
    cnpjauxiliar2[2]=cnpj[2]-48;
    cnpjauxiliar2[3]=cnpj[3]-48;
    cnpjauxiliar2[4]=cnpj[4]-48;
    cnpjauxiliar2[5]=cnpj[5]-48;
    cnpjauxiliar2[6]=cnpj[6]-48;
    cnpjauxiliar2[7]=cnpj[7]-48;
    cnpjauxiliar2[8]=cnpj[8]-48;
    cnpjauxiliar2[9]=cnpj[9]-48;
    cnpjauxiliar2[10]=cnpj[10]-48;
    cnpjauxiliar2[11]=cnpj[11]-48;
    cnpjauxiliar2[12]=digito1;

    for(i=0;i<13;i++){

     soma=soma+cnpjauxiliar2[i]*multiplica2[i];
    }
    resto=soma%11;
    if(resto<2)
        resto=0;
        else
            resto=11-resto;
    digito2=resto;
    if(digito1==cnpj[12]-48 && digito2==cnpj[13]-48)
        return 1;
    else
        return 0;

}

void procuraPrefixoFornecedor(FILE *file){
    TFornecedor fornece = novoFornecedor();
    char prefixo[100],pref[100];
    int cont=0;

    printf("Forne�a o prefixo a ser consultado:\n");
    setbuf(stdin,NULL);
    fgets(prefixo,100,stdin);
    retiraEnter(prefixo);
    maiusculo(prefixo,pref);
    retiraEnter(pref);
    setbuf(stdin,NULL);
    fseek(file,0,SEEK_SET);
    while(fread(fornece,sizeof(struct Fornecedor),1,file)==1)
        if(strncmp(fornece->nome,pref,strlen(pref))==0 && fornece->id>0){
            cont++;
            printf("Id=%lu\n",fornece->id);
            printf("nome=%s\n",fornece->nome);
            printf("cnpj=%s\n",fornece->cnpj);
            printf("email=%s\n",fornece->email);
            printf("telefone=%s\n",fornece->telefone);
        }
    if(!cont)
        printf("Prefixo n�o encontrado!!!");

    free(fornece);
}

void cadastroFornecedor(FILE *f){
        int sair,pos;
        TFornecedor fornece;
        char cnpjFornecedor[15],nome[100];
        fornece=novoFornecedor();
        do{
            printf("Informe o CNPJ:");
            setbuf(stdin,NULL);
            fgets(cnpjFornecedor,15,stdin);
            retiraEnter(cnpjFornecedor);
            setbuf(stdin,NULL);
            buscaCnpj(cnpjFornecedor,f);
            if(validaCnpj(cnpjFornecedor)==1 && buscaCnpj(cnpjFornecedor,f)==-1){
                printf("Digite seu nome:\n");
                setbuf(stdin,NULL);
                fgets(nome,100,stdin);
                retiraEnter(nome);
                setbuf(stdin,NULL);
                if(validaNome(nome,f)==-1){
                    strcpy(fornece->cnpj,cnpjFornecedor);
                    strcpy(fornece->nome,nome);
                    maiusculo(nome,fornece->nome);
                    printf("CNPJ Valido\n");
                    pos=(ftell(f)/sizeof(struct Fornecedor))+1;
                    printf("Seu ID e %lu\n",fornece->id=pos);
                    printf("Forneca seu e-mail\n");
                    setbuf(stdin,NULL);
                    fgets(fornece->email,50,stdin);
                    retiraEnter(fornece->email);
                    setbuf(stdin,NULL);
                    printf("Forneca seu telefone\n");
                    setbuf(stdin,NULL);
                    fgets(fornece->telefone,15,stdin);
                    retiraEnter(fornece->telefone);
                    setbuf(stdin,NULL);
                    fseek(f,0,SEEK_END);
                    fwrite(fornece,sizeof(struct Fornecedor),1,f);
                }
                else
                    printf("Nome repetido!!!\n");
            }
            else
                printf("CNPJ invalido ou repetido!!!\n");


            printf("Deseja abandonar o cadastro?\n1-sim\t2-nao\n");
            scanf("%d",&sair);

        }while(sair!=1);
        free(fornece);
}

void alteraFornecedor(FILE *f){
    int sair;
    unsigned long id;
    char cnpjFornecedor[15],nome[100],email[50],telefone[15];
    TFornecedor fornece;
    fornece=novoFornecedor();

    do{
        printf("\nPara fazer a altera��o forne�a o id:\n");
        scanf("%lu",&id);
        if(pesquisaIdForn(id,f)!=-1){
            printf("Forneca seu novo e-mail:\n");
            setbuf(stdin,NULL);
            fgets(email,50,stdin);
            retiraEnter(email);
            setbuf(stdin,NULL);
            printf("Digite o novo nome:\n");
            setbuf(stdin,NULL);
            fgets(nome,100,stdin);
            retiraEnter(nome);
            setbuf(stdin,NULL);
            printf("Forneca seu novo telefone\n");
            setbuf(stdin,NULL);
            fgets(telefone,15,stdin);
            retiraEnter(telefone);
            setbuf(stdin,NULL);
            printf("Informe o novo cnpj:\n");
            setbuf(stdin,NULL);
            fgets(cnpjFornecedor,15,stdin);
            retiraEnter(cnpjFornecedor);
            setbuf(stdin,NULL);
            if(validaCnpj(cnpjFornecedor)==1){
                fseek(f,pesquisaIdForn(id,f)*sizeof(struct Fornecedor),SEEK_SET);
                strcpy(fornece->cnpj,cnpjFornecedor);
                strcpy(fornece->telefone,telefone);
                strcpy(fornece->email,email);
                maiusculo(nome,fornece->nome);
                printf("Seu id �:%lu\n",fornece->id=id);
                fwrite(fornece,sizeof(struct Fornecedor),1,f);
            }
            else
                printf("CNPJ Invalido!!!\n");

        }
        else
            printf("Nenhum Funcionario com esse dados informados!!!\n");

        printf("Deseja abandonar a altera��o?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(fornece);
}

void consultaFornecedor(FILE *f){
    int sair,opcao,id;
    char cnpj[15];
    TFornecedor fornece;
    fornece=novoFornecedor();

    do{
        printf("Para realizar a consulta informe uma das seguintes informa��es:\n1-ID\n2-CNPJ\n3-Prefixo do nome:\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                printf("Forne�a o id a ser consultado:\n");
                scanf("%d",&id);
                if(pesquisaIdForn(id,f)!=-1){
                    fseek(f,pesquisaIdForn(id,f)*sizeof(struct Fornecedor),SEEK_SET);
                    fread(fornece,sizeof(struct Fornecedor),1,f);
                    printf("Id=%lu\n",fornece->id);
                    printf("nome=%s\n",fornece->nome);
                    printf("cnpj=%s\n",fornece->cnpj);
                    printf("email=%s\n",fornece->email);
                    printf("telefone=%s\n",fornece->telefone);
                }
                else
                    printf("Id n�o encontrado!!!\n");
            break;
            case 2:
                printf("Forne�a o CNPJ a ser consultado:\n");
                setbuf(stdin,NULL);
                fgets(cnpj,15,stdin);
                retiraEnter(cnpj);
                setbuf(stdin,NULL);
                if(buscaCnpj(cnpj,f)!=-1){
                    fseek(f,buscaCnpj(cnpj,f)*sizeof(struct Fornecedor),SEEK_SET);
                    fread(fornece,sizeof(struct Fornecedor),1,f);
                    printf("Id=%lu\n",fornece->id);
                    printf("nome=%s\n",fornece->nome);
                    printf("cnpj=%s\n",fornece->cnpj);
                    printf("email=%s\n",fornece->email);
                    printf("telefone=%s\n",fornece->telefone);
                }
                else
                    printf("CNPJ n�o encontrado!!!\n");
            break;

            case 3:
                procuraPrefixoFornecedor(f);
            break;

        }

        printf("Deseja abandonar a consulta?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(fornece);
}

void listagemFornecedor(FILE *f){
    int sair;
    TFornecedor fornece;
    fornece=novoFornecedor();
    fseek(f,0,SEEK_SET);
    do{
        while(fread(fornece,sizeof(struct Fornecedor),1,f)==1){
            if(fornece->id>0){
                printf("Id=%lu\n",fornece->id);
                printf("nome=%s\n",fornece->nome);
                printf("cnpj=%s\n",fornece->cnpj);
                printf("email=%s\n",fornece->email);
                printf("telefone=%s\n",fornece->telefone);
            }
        }
        printf("Deseja abandonar a Listagem?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(fornece);
}

void exclusaoFornecedor(FILE *f){
    int sair,id,pos;
    TFornecedor fornece;
    fornece=novoFornecedor();
    fseek(f,0,SEEK_SET);
    do{
        printf("Forne�a o id do vendedor que deseja excluir:\n");
        scanf("%d",&id);
        pos=pesquisaIdForn(id,f);
        if(pos!=-1){
            fseek(f,pos*sizeof(struct Fornecedor),SEEK_SET);
            fornece->id=0;
            fwrite(fornece,sizeof(struct Fornecedor),1,f);
        }
        else
            printf("Id n�o encontrado!!!\n");

        printf("Deseja abandonar a Exclus�o?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(fornece);

}

