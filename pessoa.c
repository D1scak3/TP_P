/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

ppessoa adicionaPessoa(ppessoa pessoas, pessoa temp){
    ppessoa aux, knot;
    
    aux = pessoas;
    
    knot = malloc(sizeof(pessoa));
    if(!knot){
        puts("\n");
        printf("Erro ao alocar memoria para guardar pessoa na lista.\n");
        return 0;
    }
    strcpy(knot->alfanum, temp.alfanum);
    knot->diasInfetado = temp.diasInfetado;
    knot->estado = temp.estado;
    knot->idade = temp.idade;
    knot->idSala = 0;
    knot->prox = NULL;
    
    
    
    if(pessoas == NULL){
        pessoas = knot;
        return pessoas;
    }
    
    
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    
    aux->prox = knot;
    return pessoas;
    
}

ppessoa carregaPessoas(int* quantPessoas){
    FILE* f;
    char nomeFicheiro[20], string[50];
    int quant = 0, flag;
    pessoa temp;
    ppessoa pessoas = NULL;
    
    
    printf("Indique o nome do ficheiro:\t");
    scanf("%s", nomeFicheiro);
   
    
    f = fopen(nomeFicheiro, "r");
    if(!f){
        puts("\n");
        printf("Erro ao abrir o ficheiro para leitura das pessoas.\n");
        return 0;
    }
    
    
    
    while(fscanf(f, "%[^\n]\n", string) != EOF){
        //printf("%s\n", string);
        sscanf(string, "%s %d %c", &temp.alfanum, &temp.idade, &temp.estado);
        
        
        if(string[0] == ' ')//por causa das últimas linha em branco
            return pessoas;
        
        if(temp.estado == 'D'){
            sscanf(string, " %s %d %c %d\n", &temp.alfanum, &temp.idade, &temp.estado, &temp.diasInfetado);
            temp.idSala = 0;
            temp.prox = NULL;
        }else{
            temp.diasInfetado = 0;
            temp.idSala = 0;
            temp.prox = NULL;
        }        

        
        pessoas = adicionaPessoa(pessoas, temp);
        
        if(!pessoas){
            puts("\n");
            printf("Erro ao adicionar a pessoa na lista.\n");
            return 0;
        }else{
            quant++;
        }
    }
    
    (*quantPessoas) = quant;
    
    return pessoas;
}

void mostraPessoas(ppessoa pessoas){
    ppessoa aux = pessoas;
    
    while(aux != NULL){
        printf("Nome: %s\n", aux->alfanum);
        printf("Idade: %d\tEstado: %c", aux->idade, aux->estado);
        if(aux->estado == 'D')
            printf("\tDias infetado: %d", aux->diasInfetado);
        puts("\n");
        aux = aux->prox;
    }
    
}