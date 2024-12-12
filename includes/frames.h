/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/

#ifndef FRAMES_H
#define FRAMES_H

#include <stdbool.h>
#include "config.h"

typedef struct {
    int id;           // ID do frame
    int processo_id;  // ID do processo associado
    int pagina_id;    // ID da página associada
    char* dados;      // Dados armazenados no frame
} Frame;

// Função para criar múltiplos frames
void createNFrames(Config* config, Frame frames[]);

// Função para liberar memória associada a um frame
void destroyFrame(Frame* frame);

// Funções utilitárias para manipular atributos do frame
void setProcesso_id(Frame* frame, int processo_id);
void setPagina_id(Frame* frame, int pagina_id);
void setDados(Frame* frame, const char* dados);

#endif
