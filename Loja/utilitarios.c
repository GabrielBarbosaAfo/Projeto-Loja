#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utilitarios.h"

void retiraEnter(char *variavel){
    int tamanho=strlen(variavel);
    if(variavel[tamanho-1]=='\n')
      variavel[tamanho-1]='\0';
}

void maiusculo(char *s1, char *s2){
    int i;
    for(i=0;i<strlen(s1);i++){
        switch(s1[i]){
            case 'á':
            case 'Á':
            case 'à':
            case 'À':
            case 'â':
            case 'Â':
            case 'ã':
            case 'Ã':
            s2[i]='A';
            break;

            case 'é':
            case 'É':
            case 'ê':
            case 'Ê':
            s2[i]='E';
            break;

            case 'í':
            case 'Í':
            case 'Ì':
            case 'ì':
            case 'Î':
            case 'î':
            s2[i]='I';
            break;

            case 'ó':
            case 'Ó':
            case 'ò':
            case 'Ò':
            case 'ô':
            case 'Ô':
            case 'õ':
            case 'Õ':
            s2[i]='O';
            break;

            case 'ú':
            case 'Ú':
            case 'ù':
            case 'Ù':
            case 'û':
            case 'Û':
            s2[i]='U';
            break;
        }

        if(s1[i]>'Z')
            s2[i]=s1[i]-32;
    }
}

//validando cpf
int validarCpf(char *cpf){
//valida o CPF retornando 0 caso seja invalido e 1 caso seja valido
    int soma=0;
    int i;
//verifica se tem todos os numeros e faz a soma dos digitos caso descubra um valor valido retorna 0
    if(cpf[10] != '\0'){
        for (i=0;cpf[i]!='\0';i++)
        soma = soma+(cpf[i]-48);



        switch (soma) {
            case 10:
            case 11:
            case 12:
            case 21:
            case 22:
            case 23:
            case 32:
            case 33:
            case 34:
            case 43:
            case 44:
            case 45:
            case 54:
            case 55:
            case 56:
            case 65:
            case 66:
            case 67:
            case 76:
            case 77:
            case 78:
            case 87:
            case 88:

                return 1;
            default:
                return 0;

        }

    }else
        return 0;

}

void dataAtual(char *data){
    struct tm tempo;
    time_t meuTempo;
    int dia,mes,ano;

    time(&meuTempo);
    tempo = *localtime(&meuTempo);
    dia = tempo.tm_mday;
    mes = tempo.tm_mon + 1;
    ano = tempo.tm_year + 1900;

    sprintf(data,"%.2d/%.2d/%.4d",dia,mes,ano);
    data[10]='\0';

}

int validaData(int dia,int mes,int ano){
    if(ano>2100 || ano<1900){
        return -1;
    }
    switch(mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(dia>31 || dia<1)
                return -1;
    }
    switch(mes){
        case 4:
        case 6:
        case 9:
        case 11:
            if(dia>30 || dia<1)
                return -1;

    }
    if(((ano%4==0) && (ano%100!=0)) || (ano%400==0)){
    switch(mes){
        case 2:
            if(dia>29 || dia<1)
                return -1;
    }
    }
    else{
        switch(mes){
            case 2:
                if(dia>28 || dia<1)
                    return -1;
        }
    }
    return 0;
}
