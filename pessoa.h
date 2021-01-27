/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#ifndef PESSOA_H
#define PESSOA_H

typedef struct pessoa pessoa, *ppessoa;
struct pessoa{
    char alfanum[20];//nome
    char estado;//representado por um char
    int idade;
    int diasInfetado;
    int idSala;
    ppessoa prox;
};

ppessoa carregaPessoas(int* quantPessoas);
ppessoa adicionaPessoa(ppessoa pessoas, pessoa temp);
void mostraPessoas(ppessoa pessoas);

#endif /* PESSOA_H */

