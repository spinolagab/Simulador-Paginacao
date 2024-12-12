/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/
#include "processo.h"
#include <stdlib.h>

Processo* createProcesso(int id, int num_paginas) {
    Processo* processo = (Processo*)malloc(sizeof(Processo));
    if (processo) {
        processo->id = id;
        processo->tabela = createTabelaPaginas(num_paginas);
    }
    return processo;
}

void destroyProcesso(Processo* processo) {
    if (processo) {
        if (processo->tabela) {
            destroyTabelaPaginas(processo->tabela);
        }
        free(processo);
    }
}
