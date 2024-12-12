/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "frames.h"
#include "processo.h"
#include "pagina.h"
#include "tabela_paginas.h"

FILE* log_file; // Arquivo de log
// Fila circular para implementar FIFO
int* frame_queue;
int queue_start = 0;
int queue_end = 0;
int frames_in_use = 0;

Config config;
// Declarações de funções.
void log_event(const char* evento);
void log_page_fault(int endereco_virtual, int pagina_id);
void substituir_frame(Processo* processo, Frame frames[], int* frame_idx, int pagina_id);
void handle_page_fault(Processo* processo, int pagina_id, Frame frames[], int* frame_idx);
Config readConfiguration(const char* file);

// Função para registrar no log
void log_event(const char* evento) {
    fprintf(log_file, "%s\n", evento);
    fflush(log_file);  // Garante que o log seja gravado imediatamente
}

// Função para registrar um page fault
void log_page_fault(int endereco_virtual, int pagina_id) {
    char mensagem[256];
    sprintf(mensagem, "Page Fault: Endereço virtual %d não mapeado. Criando nova página e alocando frame para a página %d.", endereco_virtual, pagina_id);
    log_event(mensagem);
}

// Função para substituir um frame (FIFO)
void substituir_frame(Processo* processo, Frame frames[], int* frame_idx, int pagina_id) {
    // Remover o frame mais antigo da fila
    int old_frame_id = frame_queue[queue_start];
    Frame* old_frame = &frames[old_frame_id];
    queue_start = (queue_start + 1) % config.NUM_FRAMES;
    frames_in_use--;

    // Remover a página associada ao frame antigo
    int old_pagina_id = old_frame->pagina_id;
    Pagina* old_pagina = processo->tabela->paginas[old_pagina_id];
    if (old_pagina) {
        old_pagina->valido = false;
        old_pagina->frame_id = -1;
    }

    char log_msg[256];
    sprintf(log_msg, "Substituindo página %d do frame %d.", old_pagina_id, old_frame_id);
    log_event(log_msg);

    // Alocar o novo frame
    setPagina_id(old_frame, pagina_id);
    setDados(old_frame, "Dados substituídos");
    old_frame->processo_id = processo->id;

    // Associar o frame à nova página
    Pagina* new_pagina = processo->tabela->paginas[pagina_id];
    new_pagina->valido = true;
    new_pagina->frame_id = old_frame_id;

    // Adicionar o frame atualizado de volta à fila
    frame_queue[queue_end] = old_frame_id;
    queue_end = (queue_end + 1) % config.NUM_FRAMES;
    frames_in_use++;
}

// Função para criar uma nova página e alocar um frame
void handle_page_fault(Processo* processo, int pagina_id, Frame frames[], int* frame_idx) {
    Pagina* pagina = processo->tabela->paginas[pagina_id];

    // Se ainda há frames disponíveis
    if (frames_in_use < config.NUM_FRAMES) {
        Frame* frame = &frames[*frame_idx];
        setProcesso_id(frame, processo->id);
        setPagina_id(frame, pagina_id);
        setDados(frame, "Dados da nova página");

        // Atribuindo o frame à página
        pagina->frame_id = frame->id;
        pagina->valido = true;

        // Adicionando o frame à fila
        frame_queue[queue_end] = frame->id;
        queue_end = (queue_end + 1) % config.NUM_FRAMES;
        frames_in_use++;

        char log_msg[256];
        sprintf(log_msg, "Nova página %d criada e alocada ao frame %d.", pagina_id, frame->id);
        log_event(log_msg);

        (*frame_idx)++;
    } else {
        // Substituir frame usando FIFO
        substituir_frame(processo, frames, frame_idx, pagina_id);
    }
}

int main() {
    config = readConfiguration("config.txt");
    // Abrir o arquivo de log
    log_file = fopen("log.txt", "w");
    if (!log_file) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    // Registrar o início do log
    log_event("Início do simulador. Tempo 0");

    frame_queue = malloc(config.NUM_FRAMES * sizeof(int));

    // Criação de frames
    Frame frames[config.NUM_FRAMES];
    createNFrames(&config, frames);

    // Criação de um processo com páginas
    Processo* processo = createProcesso(1, config.NUM_PAGINAS);
    if (!processo) {
        printf("Falha ao criar o processo.\n");
        fclose(log_file);
        return 1;
    }

    // Inicializando variáveis para controle de frames
    int frame_idx = 0;

    // Inicializando páginas do processo
    for (int i = 0; i < config.NUM_PAGINAS; i++) {
        Pagina* pagina = createPagina();
        if (!pagina) {
            printf("Falha ao criar a página %d.\n", i);
            fclose(log_file);
            return 1;
        }

        setPaginaId(pagina, i);
        setValido(pagina, false);
        addPagina(processo->tabela, pagina, i);
    }

    // Simulando a tradução de endereços (com page fault e substituição)
    for (int tempo = 1; tempo <= config.NUM_ENDERECOS; tempo++) {
        int endereco_virtual = tempo; // Endereço virtual sendo testado

        // Cálculo do número da página e offset
        int pagina_id = endereco_virtual / config.FRAME_SIZE;
        int offset = endereco_virtual % config.FRAME_SIZE;

        // Acessando a tabela de páginas para encontrar a página mapeada
        if (pagina_id < config.NUM_PAGINAS) {
            Pagina* pagina = processo->tabela->paginas[pagina_id];

            if (pagina && pagina->valido) {
                // Página já está mapeada
                char log_msg[256];
                sprintf(log_msg, "Tempo %d: Endereço virtual %d mapeado para o frame %d.", tempo, endereco_virtual, pagina->frame_id);
                log_event(log_msg);
            } else {
                // Page fault: página não encontrada
                log_page_fault(endereco_virtual, pagina_id);
                handle_page_fault(processo, pagina_id, frames, &frame_idx);
            }
        } else {
            // Endereço virtual fora do alcance
            char erro_msg[256];
            sprintf(erro_msg, "Tempo %d: Erro: endereço virtual %d inválido ou página não mapeada.", tempo, endereco_virtual);
            log_event(erro_msg);
        }
    }

    // Finalização e destruição
    log_event("Fim do simulador.");
    destroyProcesso(processo);
    for (int i = 0; i < config.NUM_FRAMES; i++) {
        destroyFrame(&frames[i]);
    }

    fclose(log_file);

    return 0;
}
