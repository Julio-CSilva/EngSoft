#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char * argv[]){

    int vetor_pipe[2], TAM; //0 - leitura, 1 - escrita
    pid_t pid;
    TAM = strlen(argv[1])+1;
    char buffer[TAM];


    pipe(vetor_pipe); //cria o pipe
    pid = fork(); //cria o processo-filho

    if(pid==0){ //se for o processo-filho
        close(vetor_pipe[1]); //fecha a porta de escrita nao sera utilizada
        while(read(vetor_pipe[0], &buffer, TAM) > 0) //le do pipe ate que algo seja escrito
        close(vetor_pipe[0]); //fecha a porta de leitura
        printf("Processo-filho(PID=%d) leu: %s\n", getpid(), buffer);
        exit(EXIT_SUCCESS);

    } else { //se for o processo-pai
        close(vetor_pipe[0]); //fecha a porta de leitura pois nao sera utilizado
        sleep(2);
        write(vetor_pipe[1], argv[1], strlen(argv[1])+1); //envia o argumento para o pipe
        close(vetor_pipe[1]); //fecha a porta de escrita
        printf("Processo-pai(PID=%d) escreveu: %s\n", getpid(), argv[1]);
        wait(NULL); //espera o filho terminar
        printf("Processo-filho terminou\n");
        exit(EXIT_SUCCESS);
    }
    return 0;
}