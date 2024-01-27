#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 5

pthread_t threads[NTHREADS];
int status, i;
void *thread_return;

int soma=0;

void* hello_world(void *arg) {
    printf("Inicio da Thread %d. soma = %d\n", (int) (size_t)arg, soma);

    if((int) (size_t)arg == 1) { //se for a segunda thread
        soma = soma*3;
    } else { //se for a primeira thread
        soma = soma + 1;
    }
    printf("Fim da Thread %d. soma = %d\n", (int) (size_t)arg, soma);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    for(i=0; i<NTHREADS; i++) {
    printf("Processo-pai criando thread #%d\n", i);
    status = pthread_create(&threads[i], NULL, hello_world, (void *) (size_t) i); 
    
        if(status != 0) {
            printf("Erro na criação da thread. Codigo de erro: %d\n", status);
            return 1;
        }
    }

    for(i=0; i<NTHREADS; i++) {
        printf("Processo-pai esperando thread #%d terminar...\n", i);
        pthread_join(threads[i], &thread_return);
        printf("Thread #%d finalizada\n", i);
    }

    printf("Processo-pai vai finalizar\n");
    return 0;
}