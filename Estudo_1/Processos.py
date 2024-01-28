import numpy as np
import multiprocessing as mp
import time

# Função para calcular o produto de duas matrizes usando a biblioteca np
def mult_matrizes(A, B, C, start, end):
    C[start:end, :] = np.dot(A[start:end, :], B)

if __name__ == '__main__':
    mp.freeze_support()


    tamanho = int(input())
    processos = int(input())
    matriz_A = np.random.randint(1, 100, size=(tamanho, tamanho))
    matriz_B = np.random.randint(1, 100, size=(tamanho, tamanho))
    matriz_resultado = np.zeros((tamanho, tamanho))

    processes = []
    tempo_inicial = time.time()
    for i in range(0, tamanho, processos):
        start = i
        end = min(i + processos, tamanho)
        p = mp.Process(target=mult_matrizes, args=(matriz_A, matriz_B, matriz_resultado, start, end))
        p.start()
        processes.append(p)

    for p in processes:
        p.join()

    tempo_final = time.time()
    tempo_total = tempo_final - tempo_inicial

    print(tempo_total)