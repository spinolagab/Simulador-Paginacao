/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/
#include "tabela_paginas.h"
#include <stdlib.h>

TabelaPaginas* createTabelaPaginas(int num_paginas) {
    TabelaPaginas* tabela = (TabelaPaginas*)malloc(sizeof(TabelaPaginas));
    if (tabela) {
        tabela->paginas = (Pagina**)malloc(num_paginas * sizeof(Pagina*));
        tabela->num_paginas = num_paginas;

        for (int i = 0; i < num_paginas; i++) {
            tabela->paginas[i] = NULL;
        }
    }
    return tabela;
}

void destroyTabelaPaginas(TabelaPaginas* tabela) {
    if (tabela) {
        for (int i = 0; i < tabela->num_paginas; i++) {
            if (tabela->paginas[i]) {
                destroyPagina(tabela->paginas[i]);
            }
        }
        free(tabela->paginas);
        free(tabela);
    }
}

void addPagina(TabelaPaginas* tabela, Pagina* pagina, int index) {
    if (index >= 0 && index < tabela->num_paginas) {
        tabela->paginas[index] = pagina;
    }
}
