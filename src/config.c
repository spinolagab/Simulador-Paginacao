/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

Config readConfiguration(const char* file){
  Config config = {0};
  FILE *innerFile = fopen(file, "r");

  if (!innerFile){
    perror("Erro ao abrir o arquivo de configuração.\n");
    exit(EXIT_FAILURE);
  }

  char buffer[128];
  while (fgets(buffer, sizeof(buffer), innerFile)) {
    char key[64];
    int value;

    if (sscanf(buffer, "%63[^=]=%d", key, &value) == 2){
      if(strcmp(key, "NUM_FRAMES") == 0){
        config.NUM_FRAMES = value;
      } else if (strcmp(key, "NUM_PAGINAS") == 0){
         config.NUM_PAGINAS = value;
      } else if(strcmp(key, "FRAME_SIZE") == 0){
        config.FRAME_SIZE = value;
      } else if (strcmp(key, "NUM_ENDERECOS") == 0){
        config.NUM_ENDERECOS = value;
      }
    }
  } 

  fclose(innerFile);
  return config;
}
