#!/bin/bash

# Acessa o processo do POL
pid=$(pgrep -f "pol")

# Desbloqueia o console do POL
echo "S" | pkill -KILL -P $pid

# Executa o comando 1 para desligar o POL após 6 minutos
echo "1" | pkill -KILL -P $pid

# Compila os scripts
./ecompile.sh -A

# Executa o POL novamente
./pol.sh
