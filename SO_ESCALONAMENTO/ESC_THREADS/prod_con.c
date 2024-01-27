//problema do produtor consumidor com threads
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define BUFFER_SAFRA 3

int buffer_index = 0;

void *producer(int *buffer){
    int count = 0;
    while(count < BUFFER_SAFRA){
        while(buffer_index == BUFFER_SIZE){
            //buffer cheio
            printf("Producer: Buffer cheio. Indo dormir...\n");
            sleep(3);
        }
        //produzindo
        buffer[buffer_index] = buffer_index;
        printf("Producer(SAFRA=%d): Produzindo item %d\n", count, buffer_index);
        buffer_index++;
        if(buffer_index == BUFFER_SIZE){
            count++;
        }
    }

    pthread_exit(NULL);
}

void* consumer(int *buffer){
    int tmp, count = 0;
    while(count < BUFFER_SAFRA){
        while(buffer_index == 0){
            //buffer vazio
            printf("Consumer: Buffer vazio. Indo dormir...\n");
            sleep(3);
        }
        //consumindo
        tmp = buffer[buffer_index-1];
        printf("Consumer(SAFRA=%d): Consumindo item %d\n", count, tmp);
        buffer_index--;
        if(buffer_index == 0){
            count++;
        }
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t prod, cons;
    int status, i;
    int *buffer = malloc(sizeof(int) * BUFFER_SIZE);
    status = pthread_create(&prod, NULL, (void*) producer, (void*) buffer);
    status = pthread_create(&cons, NULL, (void*) consumer, (void*) buffer);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    printf("Produtor e consumidor finalizados\n");
    printf("POSICAO | VALOR\n");
    for(i=0; i<BUFFER_SIZE; i++){
        printf("BUFFER[%d] | %d\n", i, buffer[i]);
    }

    exit(EXIT_SUCCESS);
}