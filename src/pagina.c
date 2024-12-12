/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/
#include "pagina.h"
#include <stdlib.h>

Pagina* createPagina() {
    Pagina* pagina = (Pagina*)malloc(sizeof(Pagina));
    if (pagina) {
        pagina->id = -1;
        pagina->frame_id = -1;
        pagina->valido = false;
    }
    return pagina;
}

void destroyPagina(Pagina* pagina) {
    if (pagina) {
        free(pagina);
    }
}

void setPaginaId(Pagina* pagina, int id) {
    pagina->id = id;
}

void setValido(Pagina* pagina, bool valido) {
    pagina->valido = valido;
}
