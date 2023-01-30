#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "utilitarios.h"

struct Cliente{
    unsigned long id;
    char nome[100],cpf[12],email[50],telefone[15];
};

//retorna os parametros da struct cliente
void retornaCliente(TCliente c){
    printf("Id=%lu\n",c->id);
    printf("nome=%s\n",c->nome);
    printf("cpf=%s\n",c->cpf);
    printf("email=%s\n",c->email);
    printf("telefone=%s\n",c->telefone);
}

//retorna o tamanho da struct
int tamanhoCliente(){
    return sizeof(struct Cliente);
}

//verifica se a cpf iguais
int pesquisa(char *cpf,FILE *file){
    TCliente cli = novoCliente();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(cli,sizeof(struct Cliente),1,file)==1&&!achou)
        if(strcmp(cpf,cli->cpf)==0 && cli->id>0)
            achou=1;
        else
            posicao++;
    free(cli);
    if(achou)
        return posicao;
    return -1;
}

//pesquisa o id do cliente e se n�o encontrar retorna -1
int pesquisaId(unsigned long id, FILE *file){
    TCliente cli = novoCliente();
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(cli,sizeof(struct Cliente),1,file)==1){
        if(cli->id==id && cli->id>0){
            free(cli);
            return posicao;
        }
        else
           posicao++;
    }
    free(cli);
    return -1;
}

//procura o prefixo a ser consulto no cliente
void procuraPrefixo(FILE *file){
    TCliente cli = novoCliente();
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
    while(fread(cli,sizeof(struct Cliente),1,file)==1)
        if(strncmp(cli->nome,pref,strlen(pref))==0 && cli->id>0){
            cont++;
            printf("Id=%lu\n",cli->id);
            printf("nome=%s\n",cli->nome);
            printf("cpf=%s\n",cli->cpf);
            printf("email=%s\n",cli->email);
            printf("telefone=%s\n",cli->telefone);
        }
    if(!cont)
        printf("Prefixo n�o encontrado!!!");

    free(cli);
}

//alocando memoria
TCliente novoCliente(){

    TCliente cliente=(TCliente)malloc(sizeof(struct Cliente));
    if(cliente)
        return cliente;
    return NULL;

}



void cadastroCliente(FILE *c){
        int sair,pos;
        TCliente pessoa;
        char cpfCliente[12],nome[100];
        pessoa=novoCliente();
        do{
            printf("Informe o cpf:");
            setbuf(stdin,NULL);
            fgets(cpfCliente,12,stdin);
            retiraEnter(cpfCliente);
            setbuf(stdin,NULL);
            if(validarCpf(cpfCliente)==1 && pesquisa(cpfCliente,c)==-1){
                strcpy(pessoa->cpf,cpfCliente);
                printf("CPF Valido\n");
                pos=(ftell(c)/sizeof(struct Cliente))+1;
                printf("Seu ID e %lu\n",pessoa->id=pos);
                printf("Digite seu nome:\n");
                setbuf(stdin,NULL);
                fgets(nome,100,stdin);
                retiraEnter(nome);
                setbuf(stdin,NULL);
                maiusculo(nome,pessoa->nome);
                printf("Forneca seu e-mail\n");
                setbuf(stdin,NULL);
                fgets(pessoa->email,50,stdin);
                retiraEnter(pessoa->email);
                setbuf(stdin,NULL);
                printf("Forneca seu telefone\n");
                setbuf(stdin,NULL);
                fgets(pessoa->telefone,15,stdin);
                retiraEnter(pessoa->telefone);
                setbuf(stdin,NULL);
                fseek(c,0,SEEK_END);
                fwrite(pessoa,sizeof(struct Cliente),1,c);
            }
            else
                printf("CPF invalido ou repetido!!!\n");

            printf("Deseja abandonar o cadastro?\n1-sim\t2-nao\n");
            scanf("%d",&sair);

        }while(sair!=1);
        free(pessoa);
}

void alteraCliente(FILE *c){
    int sair;
    unsigned long id;
    char cpfCliente[12],nome[100];
    TCliente pessoa;
    pessoa=novoCliente();

    do{
        printf("\nPara fazer a altera��o forne�a o id:\n");
        scanf("%lu",&id);
        if(pesquisaId(id,c)!=-1){
            fseek(c,pesquisaId(id,c)*sizeof(struct Cliente),SEEK_SET);
            printf("Informe o novo cpf\n");
            setbuf(stdin,NULL);
            fgets(cpfCliente,12,stdin);
            retiraEnter(cpfCliente);
            setbuf(stdin,NULL);
            if(validarCpf(cpfCliente)==1){
                strcpy(pessoa->cpf,cpfCliente);
                printf("Seu id �:%lu\n",pessoa->id=id);
                printf("Digite o novo nome:\n");
                setbuf(stdin,NULL);
                fgets(nome,100,stdin);
                retiraEnter(nome);
                setbuf(stdin,NULL);
                maiusculo(nome,pessoa->nome);
                printf("Forneca seu novo e-mail\n");
                setbuf(stdin,NULL);
                fgets(pessoa->email,50,stdin);
                retiraEnter(pessoa->email);
                setbuf(stdin,NULL);
                printf("Forneca seu novo telefone\n");
                setbuf(stdin,NULL);
                fgets(pessoa->telefone,15,stdin);
                retiraEnter(pessoa->telefone);
                setbuf(stdin,NULL);
                fwrite(pessoa,sizeof(struct Cliente),1,c);
            }
            else
                printf("CPF Invalido!!!");

        }
        else
            printf("Nenhum Funcionario com esse dados informados!!!\n");

        printf("Deseja abandonar a altera��o?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(pessoa);
}

void consultaCliente(FILE *c){
    int sair,opcao,id;
    char cpf[12];
    TCliente pessoa;
    pessoa=novoCliente();

    do{
        printf("Para realizar a consulta informe uma das seguintes informa��es:\n1-ID\n2-CPF\n3-Prefixo do nome:\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                printf("Forne�a o id a ser consultado:\n");
                scanf("%d",&id);
                if(pesquisaId(id,c)!=-1 && pessoa->id>0){
                    fseek(c,pesquisaId(id,c)*sizeof(struct Cliente),SEEK_SET);
                    fread(pessoa,sizeof(struct Cliente),1,c);
                    printf("Id=%lu\n",pessoa->id);
                    printf("nome=%s\n",pessoa->nome);
                    printf("cpf=%s\n",pessoa->cpf);
                    printf("email=%s\n",pessoa->email);
                    printf("telefone=%s\n",pessoa->telefone);
                }
                else
                    printf("Id n�o encontrado!!!\n");
            break;
            case 2:
                printf("Forne�a o CPF a ser consultado:\n");
                setbuf(stdin,NULL);
                fgets(cpf,12,stdin);
                retiraEnter(cpf);
                setbuf(stdin,NULL);
                if(pesquisa(cpf,c)!=-1 && pessoa->id>0){
                    fseek(c,pesquisa(cpf,c)*sizeof(struct Cliente),SEEK_SET);
                    fread(pessoa,sizeof(struct Cliente),1,c);
                    printf("Id=%lu\n",pessoa->id);
                    printf("nome=%s\n",pessoa->nome);
                    printf("cpf=%s\n",pessoa->cpf);
                    printf("email=%s\n",pessoa->email);
                    printf("telefone=%s\n",pessoa->telefone);
                }
                else
                    printf("CPF n�o encontrado!!!\n");
            break;

            case 3:
                procuraPrefixo(c);

            break;

        }

        printf("Deseja abandonar a consulta?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(pessoa);
}

void listagemCliente(FILE *c){
    int sair;
    TCliente pessoa;
    pessoa=novoCliente();
    fseek(c,0,SEEK_SET);
    do{
        while(fread(pessoa,sizeof(struct Cliente),1,c)==1){
            if(pessoa->id>0){
                printf("Id=%lu\n",pessoa->id);
                printf("nome=%s\n",pessoa->nome);
                printf("cpf=%s\n",pessoa->cpf);
                printf("email=%s\n",pessoa->email);
            }
        }
        printf("Deseja abandonar a Listagem?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(pessoa);
}

void exclusaoCliente(FILE *c){
    int sair,id,pos;
    TCliente pessoa;
    pessoa=novoCliente();
    fseek(c,0,SEEK_SET);
    do{
        printf("Forne�a o id da pessoa que deseja excluir:\n");
        scanf("%d",&id);
        pos=pesquisaId(id,c);
        if(pos!=-1){
            fseek(c,pos*sizeof(struct Cliente),SEEK_SET);
            pessoa->id=0;
            fwrite(pessoa,sizeof(struct Cliente),1,c);
        }
        else
            printf("Id n�o encontrado!!!\n");

        printf("Deseja abandonar a Exclus�o?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(pessoa);
}

