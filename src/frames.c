/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/
#include "frames.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>

void createNFrames(Config* config, Frame frames[]) {
    for (int i = 0; i < config->NUM_FRAMES; i++) {
        frames[i].id = i;
        frames[i].processo_id = -1;
        frames[i].pagina_id = -1;
        frames[i].dados = NULL;
    }
}

void destroyFrame(Frame* frame) {
    if (frame->dados) {
        free(frame->dados);
        frame->dados = NULL;
    }
}

void setProcesso_id(Frame* frame, int processo_id) {
    frame->processo_id = processo_id;
}

void setPagina_id(Frame* frame, int pagina_id) {
    frame->pagina_id = pagina_id;
}

void setDados(Frame* frame, const char* dados) {
    if (frame->dados) {
        free(frame->dados);
    }
    frame->dados = strdup(dados);
}
