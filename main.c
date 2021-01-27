/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "local.h"
#include "simulation.h"
#include "utils.h"

/*
 * 
 */
void main() {

    int val, quantPessoas, quantLocais, flag = 0;
    ppessoa pessoas = NULL;
    plocal locais = NULL;
    
    initRandom();
    
    printf("Bem vindo ao simulador de contágio.\n");
    
    while(flag == 0){
        printf("Opcoes do simulador:\n");
        printf("\t1- Carregar local\n");
        printf("\t2- Carregar pessoas\n");
        printf("\t3- Mostrar local\n");
        printf("\t4- Mostrar pessoas\n");
        printf("\t5- Iniciar simulacao\n");
        printf("\t6- Sair do simulador\n");
        printf("\nIndique a opcao:");
        scanf("%d", &val);
        //puts("\n");
        switch(val){
            case 1:
                locais = carregaLocais(&quantLocais);
                if(!locais)
                    printf("Erro ao ler o ficheiro designado.\n");
                else
                    printf("Local carregado com sucesso.\n");
                puts("\n");
                break;
            case 2:
                pessoas = carregaPessoas(&quantPessoas);
                if(!pessoas)
                    printf("Erro ao ler o ficheiro designado.\n");
                else
                    printf("Pessoas carregadas com sucesso.\n");
                puts("\n");
                break;
            case 3:
                if(locais)
                    mostraLocais(locais, quantLocais);
                else
                    printf("Nao ha nenhum local carregado.\n");
                puts("\n");
                break;
            case 4:
                if(pessoas)
                    mostraPessoas(pessoas);
                else
                    printf("Nao ha pessoas carregadas.\n");
                puts("\n");
                break;
            case 5:
                initSimulation(pessoas, quantPessoas, locais, quantLocais);
                puts("\n");
                break;
            case 6:
                flag = 1;
                break;
        }
        val = 0;
        puts("\n");
   }
    
    free(locais);
    
    while(pessoas != NULL){
        printf("while------\n");
        ppessoa aux1 = pessoas, aux2;
        while(aux1->prox != NULL){
            aux2 = aux1;
            aux1 = aux1->prox;
            printf("ola\n");
        }
        aux2->prox = NULL;
        free(aux1);
        if(pessoas->prox == NULL){
            free(pessoas);
            break;
        }
    }
    
    return;
}


