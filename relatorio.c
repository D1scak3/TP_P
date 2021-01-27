/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorio.h"
#include "pessoa.h"
#include "local.h"

void makeRelatorio(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais, int dadosLocais[quantLocais][3]){
    
    float percentS, percentD, percentI;
    int quantS = 0, quantD = 0, quantI = 0;
    ppessoa aux = pessoas;
    FILE* f;
    f = fopen("relatorio_final.txt", "wt");
    if(!f){
        printf("Erro ao criar relatorio final.\n");
        return;
    }
    
    fprintf(f, "-------------------PESSOAS-------------------\n");
    while(aux != NULL){
        if(aux->estado == 'D'){
            fprintf(f, "Nome: %s\t Idade: %d\t Estado: %c\t Dias doente: %d\n", aux->alfanum, aux->idade, aux->estado, aux->diasInfetado);
            fprintf(f, "Esta na sala com ID: %d\n", aux->idSala);
        }
        else{
            fprintf(f, "Nome: %s\t Idade: %d\t Estado: %c\n", aux->alfanum, aux->idade, aux->estado);
            fprintf(f, "Esta na sala com ID: %d\n", aux->idSala);
        }
        fprintf(f, "\n");
        aux = aux->prox;
    }
    
    
    fprintf(f, "-------------------LOCAIS-------------------\n");
    for(int i = 0; i < quantLocais; i++){
        fprintf(f, "ID: %d\t Capacidade maxima: %d\t Pessoas presentes na sala: %d\n", dadosLocais[i][0], dadosLocais[i][1], dadosLocais[i][2]);
    }
    fprintf(f, "\n");
    
    
    fprintf(f, "-------------------PERCENTAGENS-------------------\n");
    aux = pessoas;
    while(aux != NULL){
        if(aux->estado == 'S')
            quantS++;
        else if(aux->estado == 'D')
            quantD++;
        else if(aux->estado == 'I')
            quantI++;
       aux = aux->prox;
    }
    
    percentS = (float)((float)quantS / quantPessoas);
    percentD = (float)((float)quantD / quantPessoas);
    percentI = (float)((float)quantI / quantPessoas);
    fprintf(f, "Saudaveis: %f\t Doentes: %f\t Imunes: %f\n", percentS, percentD, percentI);
    
    
    int idLocal = 0, quantPessoasSala, quantPessoasDoente;
    int somaIdade;
    for(int i = 0; i < quantLocais; i++){
        
        aux = pessoas;
        idLocal = locais[i].id;
        quantPessoasSala = 0;
        quantPessoasDoente = 0;
        somaIdade = 0;
        
        while(aux != NULL){
            if(aux->idSala == idLocal){
                quantPessoasSala++;
                if(aux->estado == 'D'){
                    quantPessoasDoente++;
                    somaIdade = somaIdade + aux->idade;
                }
            }
            aux = aux->prox;
        }

        float media = ((float)somaIdade)/((float)quantPessoasDoente);
        
        
        fprintf(f, "Na sala com ID<%d>, a media da idade das pessoas doentes e: %f.\n", idLocal, media);
        
    }
    
    
    
    
    return;
}