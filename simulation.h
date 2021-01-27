/*
 *Feito por Miguel Fazenda
 *Nº 2018019166 
 *Turma P8
 */

#ifndef SIMULATION_H
#define SIMULATION_H

void initSimulation(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais);

void initDadosLocais(plocal locais, int quantLocais, int dadosLocais[quantLocais][3]);
void distribui(ppessoa pesssoas, int quantLocais, int dadosLocais[quantLocais][3]);

void mostraStats(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais, int dadosLocais[quantLocais][3]);
void addDoente(ppessoa pessoas, int* quantPessoas, int quantLocais, int dadosLocais[quantLocais][3]);
void avancaIt(ppessoa pessoas, int quantPessoas, int quantLocais, int dadosLocais[quantLocais][3]);
void move(ppessoa pessoas, int quantPessoas, plocal locais, int quantLocais, int dadosLocais[quantLocais][3]);

void calcRecup(ppessoa pessoas, int quantPessoas, float recup[quantPessoas]);
void calcMaxInfect(ppessoa pessoas, int quantPessoas, int maxInfect[quantPessoas]);

#endif /* SIMULATION_H */

