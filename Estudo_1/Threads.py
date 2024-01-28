import numpy as np
import threading
import time

# Função para calcular o produto de duas matrizes usando a biblioteca np
def mult_matrizes(A, B, C, start, end):
    C[start:end, :] = np.dot(A[start:end, :], B)

if __name__ == '__main__':

    tam = int(500)
    num_threads = int(90)
    matriz_A = np.random.randint(1, 100, size=(tam, tam))
    matriz_B = np.random.randint(1, 100, size=(tam, tam))
    matriz_resultado = np.zeros((tam, tam))
    
    threads = []
    tempo_inicial = time.time()
    for i in range(0, tam, num_threads):
        start = i
        end = min(i + num_threads, tam)
        t = threading.Thread(target=mult_matrizes, args=(matriz_A, matriz_B, matriz_resultado, start, end))
        t.start()
        
        threads.append(t)

    for t in threads:
        t.join()

    tempo_final = time.time()
    tempo_total = tempo_final - tempo_inicial

    print(tempo_total)
