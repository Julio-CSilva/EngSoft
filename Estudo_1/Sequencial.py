# script utilizando pipe para rodar 10x e salvar no arquivo de saida
# o tempo de execução
# for i in {1..10}; do echo 100 | python3 Sequencial.py >> saida.txt; done

import numpy as np
import time

tamanho = int(input())
matriz_A = np.random.randint(1, 100, size=(tamanho, tamanho))
matriz_B = np.random.randint(1, 100, size=(tamanho, tamanho))
matriz_resultado = np.zeros((tamanho, tamanho))


tempo_inicial = time.time() #inicio da contagem do tempo
matriz_resultado = np.dot(matriz_A, matriz_B)

tempo_final = time.time() #fim da contagem do tempo
tempo_total = tempo_final - tempo_inicial

print(tempo_total)