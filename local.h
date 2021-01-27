/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#ifndef LOCAL_H
#define LOCAL_H

typedef struct sala local, *plocal;
struct sala{
    int id; // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3]; // id das ligações (-1 nos casos não usados)
};

plocal carregaLocais(int * quantLocais);//devolve array
void mostraLocais(plocal locais, int quantLocais);

#endif /* LOCAL_H */

