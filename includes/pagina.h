/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/

#ifndef PAGINA_H
#define PAGINA_H

#include <stdbool.h>

typedef struct {
    int id;       // ID da página
    int frame_id; // ID do frame associado
    bool valido;  // Se a página está mapeada em um frame
} Pagina;

// Funções para criar e destruir páginas
Pagina* createPagina();
void destroyPagina(Pagina* pagina);

// Funções utilitárias para manipular atributos da página
void setPaginaId(Pagina* pagina, int id);
void setValido(Pagina* pagina, bool valido);

#endif
