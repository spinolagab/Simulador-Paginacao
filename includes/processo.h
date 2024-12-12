/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/

#ifndef PROCESSO_H
#define PROCESSO_H

#include "tabela_paginas.h"

typedef struct {
    int id;               // ID do processo
    TabelaPaginas* tabela; // Tabela de páginas do processo
} Processo;

// Funções para criar e destruir processos
Processo* createProcesso(int id, int num_paginas);
void destroyProcesso(Processo* processo);

#endif
