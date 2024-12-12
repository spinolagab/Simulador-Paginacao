/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/

#ifndef TABELA_PAGINAS_H
#define TABELA_PAGINAS_H

#include "pagina.h"

typedef struct {
    Pagina** paginas; // Vetor de páginas
    int num_paginas;  // Número total de páginas
} TabelaPaginas;

// Funções para criar e destruir tabelas de páginas
TabelaPaginas* createTabelaPaginas(int num_paginas);
void destroyTabelaPaginas(TabelaPaginas* tabela);

// Função para adicionar uma página à tabela
void addPagina(TabelaPaginas* tabela, Pagina* pagina, int index);

#endif
