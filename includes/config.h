/*
Integrantes
1. Bruno Antico Galin - RA: 10417318
2. Enzo Benedetto Proença - RA: 10418579
3. Gabriel Alves de Freitas Spinola Sucupira - RA: 10418133
4. Ismael de Sousa Silva - RA: 10410870
*/

#ifndef CONFIG_H
#define CONFIG_H

typedef struct  {
  int NUM_FRAMES;
  int NUM_PAGINAS;
  int FRAME_SIZE;
  int NUM_ENDERECOS;
} Config;

Config readConfiguration(const char* filename);

#endif // !CONFIG_H
