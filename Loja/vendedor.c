#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendedor.h"
#include "utilitarios.h"

struct Vendedor{
    unsigned long id;
    char nome[100],cpf[12],email[50],telefone[15],password[20];
};

//aloca��o de memoria
TVendedor novoVendedor(){

    TVendedor vendedor=(TVendedor)malloc(sizeof(struct Vendedor));
    if(vendedor)
        return vendedor;
    return NULL;

}

//retorna o tamanho da struct
int tamanhoVendedor(){
    return sizeof(struct Vendedor);
}
void retornaSenhaVende(char *senha,TVendedor v){
    strcpy(senha,v->password);
}
void retornaCpfVende(char *cpf,TVendedor v){
    strcpy(cpf,v->cpf);
}
unsigned long retornaIdVende(TVendedor v){
    return v->id;
}

//verifica se a cpf iguais
int pesquisaVendCpf(char *cpf,FILE *v){
    TVendedor vend = novoVendedor();
    int achou=0,posicao=0;

    fseek(v,0,SEEK_SET);
    while(fread(vend,sizeof(struct Vendedor),1,v)==1&&!achou)
        if(strcmp(cpf,vend->cpf)==0 && vend->id>0)
            achou=1;
        else
            posicao++;
    free(vend);
    if(achou)
        return posicao;
    return -1;
}

int pesquisaEmail(char *email,FILE *v){
    TVendedor vend = novoVendedor();
    int posicao=0;

    fseek(v,0,SEEK_SET);
    while(fread(vend,sizeof(struct Vendedor),1,v)==1){
        if(strcmp(email,vend->email)==0 && vend->id>0){
            free(vend);
            return posicao;
        }
        else
            posicao++;
    }
    free(vend);
    return -1;
}

int pesquisaIdCpfVend(char *cpf, FILE *file){
    TVendedor vend = novoVendedor();
    unsigned long id;

    fseek(file,0,SEEK_SET);
    while(fread(vend,sizeof(struct Vendedor),1,file)==1){
        if(strcmp(cpf,vend->cpf)==0){
            id=vend->id;
            free(vend);
            return id;
        }
    }
    free(vend);
    return -1;
}

int pesquisaIdVend(unsigned long id, FILE *file){
    TVendedor vend = novoVendedor();
    int posicao=0;
    fseek(file,0,SEEK_SET);
    while(fread(vend,sizeof(struct Vendedor),1,file)==1){
        if(vend->id==id && vend->id>0){
            free(vend);
            return posicao;
        }
        else
            posicao++;
    }
    free(vend);
    return -1;
}

void procuraPrefixoVend(FILE *file){
    TVendedor vend = novoVendedor();
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
    while(fread(vend,sizeof(struct Vendedor),1,file)==1)
        if(strncmp(vend->nome,pref,strlen(pref))==0 && vend->id>0){
            cont++;
            printf("Id=%lu\n",vend->id);
            printf("nome=%s\n",vend->nome);
            printf("cpf=%s\n",vend->cpf);
            printf("email=%s\n",vend->email);
            printf("telefone=%s\n",vend->telefone);
        }
    if(!cont)
        printf("Prefixo n�o encontrado!!!");

    free(vend);
}

void cadastroVendedor(FILE *v){
        int sair,pos;
        TVendedor vend;
        char cpfCliente[12],nome[100],email[50];
        vend=novoVendedor();
        do{
            printf("\nForne�a seu email:");
            setbuf(stdin,NULL);
            fgets(email,50,stdin);
            retiraEnter(email);
            setbuf(stdin,NULL);
            if(pesquisaEmail(email,v)==-1){
                printf("\nInforme o cpf:");
                setbuf(stdin,NULL);
                fgets(cpfCliente,12,stdin);
                retiraEnter(cpfCliente);
                setbuf(stdin,NULL);
                if(validarCpf(cpfCliente)==1 && pesquisaVendCpf(cpfCliente,v)==-1){
                    strcpy(vend->cpf,cpfCliente);
                    strcpy(vend->email,email);
                    printf("CPF Valido\n");
                    pos=(ftell(v)/sizeof(struct Vendedor))+1;
                    printf("Seu ID e %lu\n",vend->id=pos);
                    printf("Digite seu nome:\n");
                    setbuf(stdin,NULL);
                    fgets(nome,100,stdin);
                    retiraEnter(nome);
                    setbuf(stdin,NULL);
                    maiusculo(nome,vend->nome);
                    printf("Forneca seu telefone\n");
                    setbuf(stdin,NULL);
                    fgets(vend->telefone,15,stdin);
                    retiraEnter(vend->telefone);
                    setbuf(stdin,NULL);
                    printf("Forne�a uma senha:");
                    setbuf(stdin,NULL);
                    fgets(vend->password,20,stdin);
                    retiraEnter(vend->password);
                    setbuf(stdin,NULL);
                    fseek(v,0,SEEK_END);
                    fwrite(vend,sizeof(struct Vendedor),1,v);

                }
                else
                    printf("CPF invalido ou repetido!!!\n");

            }
            else
                printf("Email repetido!!!\n");

            printf("Deseja abandonar o cadastro?\n1-sim\t2-nao\n");
            scanf("%d",&sair);

        }while(sair!=1);
        free(vend);
}

void alteraVendedor(FILE *v){
    int sair;
    unsigned long id;
    char cpfCliente[12],nome[100],email[50];
    TVendedor vend;
    vend=novoVendedor();

    do{
        printf("\nPara fazer a altera��o forne�a o id:\n");
        scanf("%lu",&id);
        if(pesquisaIdVend(id,v)!=-1){
            printf("Informe o novo cpf\n");
            setbuf(stdin,NULL);
            fgets(cpfCliente,12,stdin);
            retiraEnter(cpfCliente);
            setbuf(stdin,NULL);
            if(validarCpf(cpfCliente)==1){
                printf("\nInforme seu novo email:");
                setbuf(stdin,NULL);
                fgets(email,50,stdin);
                retiraEnter(email);
                setbuf(stdin,NULL);
                if(pesquisaEmail(email,v)==-1){
                    fseek(v,pesquisaIdVend(id,v)*sizeof(struct Vendedor),SEEK_SET);
                    strcpy(vend->cpf,cpfCliente);
                    strcpy(vend->email,email);
                    printf("Seu id �:%lu\n",vend->id=id);
                    printf("Digite o novo nome:\n");
                    setbuf(stdin,NULL);
                    fgets(nome,100,stdin);
                    retiraEnter(nome);
                    setbuf(stdin,NULL);
                    maiusculo(nome,vend->nome);
                    printf("Forneca seu novo telefone\n");
                    setbuf(stdin,NULL);
                    fgets(vend->telefone,15,stdin);
                    retiraEnter(vend->telefone);
                    setbuf(stdin,NULL);
                    printf("Forne�a sua nova senha:");
                    setbuf(stdin,NULL);
                    fgets(vend->password,20,stdin);
                    retiraEnter(vend->password);
                    setbuf(stdin,NULL);
                    fwrite(vend,sizeof(struct Vendedor),1,v);
                }
                else
                    printf("Email ja cadastrado!!!\n");
            }
            else
                printf("CPF Invalido!!!");

        }
        else
            printf("Nenhum Funcionario com esse dados informados!!!\n");

        printf("Deseja abandonar a altera��o?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(vend);
}

void consultaVendedor(FILE *v){
    int sair,opcao,id;
    char cpf[12];
    TVendedor vend;
    vend=novoVendedor();

    do{
        printf("Para realizar a consulta informe uma das seguintes informa��es:\n1-ID\n2-CPF\n3-Prefixo do nome:\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                printf("Forne�a o id a ser consultado:\n");
                scanf("%d",&id);
                if(pesquisaIdVend(id,v)!=-1){
                    fseek(v,pesquisaIdVend(id,v)*sizeof(struct Vendedor),SEEK_SET);
                    fread(vend,sizeof(struct Vendedor),1,v);
                    printf("Id=%lu\n",vend->id);
                    printf("nome=%s\n",vend->nome);
                    printf("cpf=%s\n",vend->cpf);
                    printf("email=%s\n",vend->email);
                    printf("telefone=%s\n",vend->telefone);
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
                if(pesquisaVendCpf(cpf,v)!=-1){
                    fseek(v,pesquisaVendCpf(cpf,v)*sizeof(struct Vendedor),SEEK_SET);
                    fread(vend,sizeof(struct Vendedor),1,v);
                    printf("Id=%lu\n",vend->id);
                    printf("nome=%s\n",vend->nome);
                    printf("cpf=%s\n",vend->cpf);
                    printf("email=%s\n",vend->email);
                    printf("telefone=%s\n",vend->telefone);
                }
                else
                    printf("CPF n�o encontrado!!!\n");
            break;

            case 3:
                procuraPrefixoVend(v);
            break;

        }

        printf("Deseja abandonar a consulta?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(vend);
}

void listagemVendedor(FILE *v){
    int sair;
    TVendedor vend;
    vend=novoVendedor();
    fseek(v,0,SEEK_SET);
    do{
        while(fread(vend,sizeof(struct Vendedor),1,v)==1){
            if(vend->id>0){
                printf("Id=%lu\n",vend->id);
                printf("nome=%s\n",vend->nome);
                printf("cpf=%s\n",vend->cpf);
                printf("email=%s\n",vend->email);
                printf("telefone=%s\n",vend->telefone);
            }
        }
        printf("Deseja abandonar a Listagem?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(vend);
}

void exclusaoVendedor(FILE *v){
    int sair,id,pos;
    TVendedor vend;
    vend=novoVendedor();
    fseek(v,0,SEEK_SET);
    do{
        printf("Forne�a o id do vendedor que deseja excluir:\n");
        scanf("%d",&id);
        pos=pesquisaIdVend(id,v);
        if(pos!=-1){
            fseek(v,pos*sizeof(struct Vendedor),SEEK_SET);
            vend->id=0;
            fwrite(vend,sizeof(struct Vendedor),1,v);
        }
        else
            printf("Id n�o encontrado!!!\n");

        printf("Deseja abandonar a Exclus�o?\n1-sim\t2-nao\n");
        scanf("%d",&sair);
    }while(sair!=1);
    free(vend);
}
