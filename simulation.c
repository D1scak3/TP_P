/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "local.h"
#include "pessoa.h"
#include "utils.h"
#include "relatorio.h"

#define DISSEMINACAO 0.70
#define IMUNIDADE 0.2

static int diasPassados = 0;

//------------------INICIA DADOS LOCAIS--------------------
void initDadosLocais(plocal locais, int quantLocais, int dadosLocais[quantLocais][3]){
    
    //0 = id
    //1 = capacidade
    //2 = quant de pessoas presentes
    for(int i = 0; i < quantLocais; i++){
        dadosLocais[i][0] = locais[i].id;
        dadosLocais[i][1] = locais[i].capacidade;
        dadosLocais[i][2] = 0;
    }
    
    return;
}


//------------------DISTRIBUI PESSOAS----------------------
void distribui(ppessoa pessoas, int quantLocais, int dadosLocais[quantLocais][3]){
    ppessoa aux = pessoas;
    int rnd;
    
    while(aux != NULL){
        
        rnd = intUniformRnd(0, quantLocais-1);
        for(int i = 0; i < quantLocais; i++){
            if(rnd == i && dadosLocais[i][1] >= dadosLocais[i][2]){
                aux->idSala = dadosLocais[i][0];
                dadosLocais[i][2] += 1;
                aux = aux->prox;
            }
        }
    }
    
}


//------------------MOSTRA ESTATISTICAS---------------------
void mostraStats(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais, int dadosLocais[quantLocais][3]){
    
    ppessoa aux = pessoas;
    float percentS, percentD, percentI;
    int quantS = 0, quantD = 0, quantI = 0;
    
    while(aux != NULL){
        
        if(aux->estado == 'S')
            quantS++;
        else if(aux->estado == 'D')
            quantD++;
        else if(aux->estado == 'I')
            quantI++;
        
        printf("A pessoa <%s> esta na sala com ID <%d>\n", aux->alfanum, aux->idSala);
        aux = aux->prox;
    }
    
    puts("\n");
    printf("No total:\n");
    for(int i = 0; i < quantLocais; i++){
        printf("Ha <%d> pessoas na sala com ID<%d>.\n", dadosLocais[i][2], dadosLocais[i][0]);
    }
    
    percentS = (float)((float)quantS / quantPessoas);
    percentD = (float)((float)quantD / quantPessoas);
    percentI = (float)((float)quantI / quantPessoas);
    puts("\n");
    printf("Percengatens:\n");
    printf("Saudaveis:<%f>\tDoentes:<%f>\tImunes:<%f>\n", percentS, percentD, percentI);
    
}


//------------------ADICIONA DOENTE--------------------------
void addDoente(ppessoa pessoas, int* quantPessoas, int quantLocais, int dadosLocais[quantLocais][3]){
    int flag = 0, destino;
    for(int i = 0; i < quantLocais; i++){
        if(dadosLocais[i][2] == dadosLocais[i][1])
            flag++;//conta quant de locais cheios
    }
    if(flag == quantLocais){//se quant de locais cheios == quantLocais, sai da função
        printf("Nao ha locais disponiveis para adicionar doentes.\n");
        return;
    }
    
    ppessoa aux,  novo = malloc(sizeof(pessoa));
    if(!novo){
        printf("Erro ao alocar memoria para o novo doente.\n");
        return;
    }
    
    printf("Indique o nome do novo doente:\t");
    scanf("%s", novo->alfanum);
    printf("\nIndique a idade:\t");
    int valor;
    scanf("%d", &valor);
    novo->idade = valor;
    printf("\nIndique a quantos dias esta doente:\t");
    scanf("%d", &valor);
    novo->diasInfetado = valor;
    
    novo->estado = 'D';
    novo->prox = NULL;
    
  
    do{
        flag = 0;
        printf("\nOnde deseja colocar o doente?\n");
        printf("Salas disponiveis:\n");
        for(int i = 0; i < quantLocais; i++){
            if(dadosLocais[i][2] < dadosLocais[i][1])//mostra salas disponiveis
                printf("Sala com ID<%d>\n", dadosLocais[i][0]);
        }
        scanf("%d", &destino);
        for(int i = 0; i < quantLocais; i++){
            if(dadosLocais[i][0] == destino){//compara id
                if(dadosLocais[i][2] >= dadosLocais[i][1])//se n tiver espaço
                    flag = 1;
                else//se tiver espaço
                    dadosLocais[i][2] = dadosLocais[i][2] + 1;
            }
        }    
    }while(flag == 1);
    novo->idSala = destino;
    
    
    //printf("VOU ADICIONAR A NOVA PESSOA A LISTA\n");
    aux = pessoas;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
    
    int val;
    val = (*quantPessoas);
    val++;
    (*quantPessoas) = val;
        
}


//------------------RECUPERACAO E MAX INFEÇAO----------------
void calcRecup(ppessoa pessoas, int quantPessoas, float recup[quantPessoas]){
    ppessoa aux = pessoas;
    int i = 0;
    
    while(aux != NULL){
        float prob = (1.0)/(aux->idade);
        recup[i++] = prob;
        aux = aux->prox;
    }
    
}
void calcMaxInfect(ppessoa pessoas, int quantPessoas, int maxInfect[quantPessoas]){
    ppessoa aux = pessoas;
    int i = 0;
    
    while(aux != NULL){
        float val = ((float)(aux->idade))/10.0;
        maxInfect[i++] = trunc(val) + 5;
        aux = aux->prox;
    }
}


//------------------AVANCA ITERACAO-------------------------
void avancaIt(ppessoa pessoas, int quantPessoas, int quantLocais, int dadosLocais[quantLocais][3]){
    //calcular recuperação e infeção
    float recup[quantPessoas];
    int maxInfect[quantPessoas], i = 0, j = 0, prob;
    
    calcRecup(pessoas, quantPessoas, recup);
    calcMaxInfect(pessoas, quantPessoas, maxInfect);
    
    ppessoa aux = pessoas;
    
    while(aux != NULL){
        
        //verifica dias infetado
        //so entra aqui se tiver diasInfetado > 0
        if(aux->diasInfetado == maxInfect[i]){
            prob = probEvento(IMUNIDADE);
            if(prob == 1){
                aux->estado = 'I';
                aux->diasInfetado = 0;
            }else{
                aux->estado = 'S';
                aux->diasInfetado = 0;
            }
        }
        
        
        //verifica recuperação
        if(aux->estado == 'D'){
            prob = probEvento(recup[i]);
            if(prob == 1){
                prob = probEvento(IMUNIDADE);
                if(prob == 1){
                    aux->estado = 'I';
                    aux->diasInfetado = 0;
                }
                else{
                    aux->estado = 'S';
                    aux->diasInfetado = 0;
                }
            }else{
                aux->diasInfetado += 1;
            }
        }
        
        i++;
        aux = aux->prox;
        
    }
    //printf("VERIFIQUEI DIAS MAX E RECUPERACAO\n");
    //system("pause");
    
    //INFETA PESSOAS
    /*
     *PEGAR EM TODAS AS PESSOAS DA MESMA SALA
     *SELECIONAR AO CALHAS QUEM É INFETADO, DAS PESSOAS NA MESMA SALA 
     */
    
    for(int i = 0; i < quantLocais; i++){
        int id = dadosLocais[i][0], quantSala = dadosLocais[i][2], j = 0, rnd, flag = 0, count = 0;
        float a = ((float)quantSala) * DISSEMINACAO;
        int parcela = trunc(a);
        if(parcela != 0){//só atua se tiver quantidade suficiente na sala

            int usados[quantSala];//para guardar o índice dos que já foram enfetados
            for(int k = 0; k < quantSala; k++){
                usados[k] = -1;//inicia a -1 por causa do índice 0
            }
            aux = pessoas;
            ppessoa pessoasNaSala = malloc(sizeof(pessoa) * quantSala);
            if(!pessoasNaSala){
                printf("Erro ao alocar memoria para as pessoas na sala.\n");
                return;
            }


            while(aux != NULL){//copia pessoas numa mesma sala para um array à parte
                if(aux->idSala == id){
                    strcpy(pessoasNaSala[j].alfanum, aux->alfanum);
                    pessoasNaSala[j].estado = aux->estado;
                    //printf("PESSOA COPIADA: %s %c %d\n", pessoasNaSala[j].alfanum, pessoasNaSala[j].estado, pessoasNaSala[j].idSala);
                    j++;
                }
                aux = aux->prox;
            }    
            //system("pause");

            for(int k = 0; k < quantSala; k++){//infeta as pessoas(atualiza a info obtida)

                do{//escolhe pessoa ao calhas
                    rnd = intUniformRnd(0, quantSala-1);
                    for(int h = 0; h < quantSala; h++){
                        if(usados[h] == rnd)
                            flag = 1;
                    }
                }while(flag == 1);

                if(count < parcela){//só entra aqui se ainda n infetou a quantidade de pessoas(parcela) intendida
                    //printf("PESSOA ANTES: %s %c\n", pessoasNaSala[rnd].alfanum, pessoasNaSala[rnd].estado);
                    if(pessoasNaSala[rnd].estado != 'I')
                        pessoasNaSala[rnd].estado = 'D';
                    //printf("PESSOA Depois: %s %c\n", pessoasNaSala[rnd].alfanum, pessoasNaSala[rnd].estado);
                    count++;
                }

            }
            //system("pause");
            
            //devolve a informação alterada à lista
            aux = pessoas;
            while(aux != NULL){
                if(strcmp(aux->alfanum, pessoasNaSala[j].alfanum) == 0){
                    aux->estado = pessoasNaSala[j].estado;
                    j++;
                }
                aux = aux->prox;
            }

        }
    }
    
    return;
    
}


//------------------MOVE PESSOAS-----------------------------
void move(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais, int dadosLocais[quantLocais][3]){
    
    int origem = 0, destino = 0, aMover = 0, flag = 0;
    
    for(int i = 0; i < quantLocais; i++){
        if(dadosLocais[i][2] > 0)
            printf("A sala com ID<%d> tem <%d> pessoas.\n", dadosLocais[i][0], dadosLocais[i][2]);
    }
    
    printf("\n");
    
    do{//get origem
        flag = 0;
        printf("Indique de onde(ID da sala) quer mover a(s) pessoa(s)(0 se mudou de ideias):\t");
        scanf("%d", &origem);
        
        if(origem == 0)
            return;
        
        for(int j = 0; j < quantLocais; j++){
            if(origem == dadosLocais[j][0])
                flag = 1;
        }
        
    }while(flag == 0);//só avança quando a flag for ativada
    
    printf("\n");
    
    do{//get quantidade a mover
        flag = 0;
        printf("Indique quantas pessoas quer mover(0 se mudou de ideias):\t");
        scanf("%d", &aMover);
        
        if(aMover == 0)
            return;
        
        for(int j = 0; j < quantLocais; j++){
            if(aMover <= dadosLocais[j][2])
                flag = 1;
        }
        
    }while(flag == 0);//só avança quando a flag for ativada
    
    printf("\n");
    



//^^^^^^^^^^^^^^^^TUDO BEM ATÉ AQUI^^^^^^^^^^^^



    int k = 0;
    ppessoa aux = pessoas, pessoasAMover = malloc(sizeof(pessoa) * aMover);
    if(!pessoasAMover){
        printf("Erro ao alocar memoria para as pessoas a mover.\n");
        return;
    }
    
    while(aux != NULL){
        if(aux->idSala == origem){
            strcpy(pessoasAMover[k].alfanum, aux->alfanum);
            pessoasAMover[k].idSala = aux->idSala;
            k++;
        }
        aux = aux->prox;
    }
    
    
//    printf("ARRAY DE PESSOAS\n");
//    printf("k: %d\n", k);
//    for(int j = 0; j < k ; j++){
//        printf("%s %d\n", pessoasAMover[j].alfanum, pessoasAMover[j].idSala);
//    }
    //system("pause");




    //^^^^^^^^^^^^^^TUDO BEM
    
    printf("Pode mover para as salas com ID:\t");
    for(int i = 0; i < quantLocais; i++){
        if(dadosLocais[i][0] == origem){
            for(int j = 0; j < 3; j++)
                if(locais[i].liga[j] != (-1))
                    printf("%d\t", locais[i].liga[j]);
        }
    }
    
    printf("\n");
    
    do{
        flag = 0;
        printf("Para que sala deseja mover a(s) pessoa(s):\t");
        scanf("%d", &destino);
        
        for(int j = 0; j < quantLocais; j++){
            if(dadosLocais[j][0] == origem)
                for(int g = 0; g < 3; g++)
                    if(destino == locais[j].liga[g])
                        flag = 1;
        }
        
        
    }while(flag == 0);//só avança se a flag for ativada
    
//    printf("A SALA EXISTE.\n");
//
//    printf("ANTES DE MOVER\n");
//    printf("k: %d\n", k);
//    for(int j = 0; j < k ; j++){
//        printf("%s %d\n", pessoasAMover[j].alfanum, pessoasAMover[j].idSala);
//    }
    //system("pause");

    for(int j = 0; j < k; j++){
        //printf("%d", pessoasAMover[j].idSala);
        pessoasAMover[j].idSala = destino;
        //printf("%d\n", pessoasAMover[j].idSala);
    }

//    printf("DEPOIS DE MOVER\n");
//    printf("k: %d\n", k);
//    for(int j = 0; j < k ; j++){
//        printf("%s %d\n", pessoasAMover[j].alfanum, pessoasAMover[j].idSala);
//    }
//    system("pause");
    
    aux = pessoas;
    int m = 0;
    while(aux != NULL){
        if(strcmp(aux->alfanum, pessoasAMover[m].alfanum) == 0){
            aux->idSala = pessoasAMover[m].idSala;
            m++;
        }
        aux = aux->prox;
    }
    
    
//    for(int j = 0; j < quantLocais; j++){
//        printf("ID %d       QUANT %d\n", dadosLocais[j][0], dadosLocais[j][2]);
//    }
    
    //printf("aMover: %d\n", aMover);
    
    for(int j = 0; j < quantLocais; j++){
        int x = dadosLocais[j][2];
        int res;
        //printf("X: %d\n", x);
        if(origem == dadosLocais[j][0]){
            res = x - aMover;
            dadosLocais[j][2] = res;
        }
        if(destino == dadosLocais[j][0]){
            res = x + aMover;
            dadosLocais[j][2] = res;
        }
    }
    
    
    free(pessoasAMover);
//    for(int j = 0; j < quantLocais; j++){
//        printf("ID %d       QUANT %d\n", dadosLocais[j][0], dadosLocais[j][2]);
//    }
    
}


void initSimulation(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais){
    int flag = 0, val = 0;
    int dadosLocais[quantLocais][3];//guarda dados de cada local
    
    initDadosLocais(locais, quantLocais, dadosLocais);
    distribui(pessoas, quantLocais, dadosLocais);
    
    while(flag == 0){
        printf("Opcoes do simulador:\n");
        printf("1- Mostrar estatisticas\n");
        printf("2- Adicionar doente\n");
        printf("3- Avancar uma iteracao\n");
        printf("4- Mover doente(s)\n");
        printf("5- Retroceder iteracao(oes)(POR IMPLEMENTAR)\n");
        printf("0- Voltar ao carregamento de dados\n");
        puts("\n");
        printf("Introduza uma opcao:\t");
        scanf("%d", &val);
        printf("\n");
        
        //ISTO ÀS VEZES DÁ ERRO AO MOSTRAR OS STATS
        //DEPOIS DE AVANÇAR 2-3 ITERAÇÕES
        //COM O PESSOASC.TXT
        
        switch(val){
            case 1:
                mostraStats(pessoas, quantPessoas, locais, quantLocais, dadosLocais);
                break;
            case 2:
                addDoente(pessoas, &quantPessoas, quantLocais, dadosLocais);
                break;
            case 3:
                avancaIt(pessoas, quantPessoas, quantLocais, dadosLocais);
                break;
            case 4:
                move(pessoas, quantPessoas, locais, quantLocais, dadosLocais);
                break;
            case 5:
                //ainda falta pensar nisto
                break;
            case 0:
                 makeRelatorio(pessoas, quantPessoas, locais, quantLocais, dadosLocais);
                return;
                break;
        }
        
        
    }
    
}