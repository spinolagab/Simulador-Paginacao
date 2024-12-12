#!/bin/bash

# Diretórios
INCLUDE_DIR="includes"
SRC_DIR="src"
OUTPUT="simulacao"
CONFIG_FILE="config.txt"

# Compilação
gcc -g -I "$INCLUDE_DIR" "$SRC_DIR"/*c -o "$OUTPUT"

if [ $? -eq 0 ]; then
  echo "Compilação bem sucedida. Executando simulação..."  
    ./"$OUTPUT"
else
  echo "Falha na compilação."
fi
