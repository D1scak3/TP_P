/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "local.h"


plocal carregaLocais(int* quantLocais){
    
    int flag = 0, quant = 0;
    plocal locais;
    local localTemp;
    char nomeFicheiro[20];
    FILE* f;
    
    printf("Indique o nome do ficheiro:\t");
    scanf("%s", nomeFicheiro);
    
    
    f = fopen(nomeFicheiro, "rb");
    if(!f){
        puts("\n");
        printf("Erro ao abrir o ficheiro para leitura dos locais.\n");
        return 0;
    }
    
    locais = malloc(sizeof(local));
    if(!locais){
        puts("\n");
        printf("Erro ao alocar memoria para gaurdar os locais.\n");
        return 0;
    }
    
    //printf("VOU COMEÇAR A LER\n");
    while(fread(&localTemp, sizeof(local), 1, f) == 1){
        
        //confirma se há valores errados nas ligações
        for(int i = 0;i < 3; i++){
            if(localTemp.liga[i] < 0 && localTemp.liga[i] != (-1))
                flag = 1;
        }
        if(flag == 1){
            fclose(f);
            free(locais);
            return 0;
        }
        
        
            
        //realoca memoria e adiciona local ao array
        quant++;
        locais = realloc(locais, (sizeof(local) * quant));
        if(!locais){
            puts("\n");
            printf("Erro ao alocar memoria para guardar os locais.\n");
            return 0;
        }
        locais[quant-1] = localTemp;
    }
    
    //pra confirmar valores
    //printf("Quantidade de salas no local: %d", quantLocais);
    
    *quantLocais = quant;
    fclose(f);
    return locais;
}

void mostraLocais(plocal locais, int quantLocais){
    printf("INFORMACAO SOBRE O LOCAL\n");
    for(int i = 0; i < quantLocais; i++){
        printf("ID da sala: <%d>\n", locais[i].id);
        printf("Capacidade: <%d>\n", locais[i].capacidade);
        printf("Faz ligacoes com as salas:\t");
        for(int j = 0; j < 3; j++){
            if(locais[i].liga[j] != (-1))
                printf("<%d>\t", locais[i].liga[j]);
        }
    }
    puts("\n");
    return;
}
