#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#define MAX_SIZE 4

int main(int argc, char * argv[]){

    int vetor_pipe_ida[2], vetor_pipe_volta[2]; //0 - leitura, 1 - escrita
    pid_t pid;
    char buffer[MAX_SIZE];
    int num, resposta;

    pipe(vetor_pipe_ida); //cria o pipe de ida
    pipe(vetor_pipe_volta); //cria o pipe de volta
    pid = fork(); //cria o processo-filho
    
    if (pid==0){
        close(vetor_pipe_ida[1]); //fecha a porta de escrita do pipe de ida
        while (read(vetor_pipe_ida[0], buffer, MAX_SIZE) > 0) //le do pipe de ida ate que algo seja escrito
        
        sscanf(buffer, "%d", &num); //converte o buffer para inteiro
        close(vetor_pipe_ida[0]); //fecha a porta de leitura do pipe de ida
        printf("Processo-filho(PID=%d) leu: %d\n", getpid(), num);

        //resposta ao processo-pai
        num = num+1;
        sprintf(buffer, "%d", num);

        close(vetor_pipe_volta[0]); //fecha a porta de leitura do pipe de volta
        write(vetor_pipe_volta[1], buffer, MAX_SIZE); //escreve no pipe de volta
        close(vetor_pipe_volta[1]); //fecha a porta de escrita do pipe de volta

        printf("Processo-filho(PID=%d) escreveu: %d\n", getpid(), num);
        printf("Processo-filho terminou\n");

        exit(EXIT_SUCCESS);
        
    } else { //processo-pai
        num = atoi(argv[1]); //converte o argumento para inteiro
        sprintf(buffer, "%d", num); //converte o inteiro para string
        close(vetor_pipe_ida[0]); //fecha a porta de leitura do pipe de ida
        write(vetor_pipe_ida[1], buffer, MAX_SIZE); //escreve no pipe de ida
        close(vetor_pipe_ida[1]); //fecha a porta de escrita do pipe de ida
        printf("Processo-pai(PID=%d) escreveu: %s\n", getpid(), buffer);

        //leitura da resposta do processo-filho
        close(vetor_pipe_volta[1]); //fecha a porta de escrita do pipe de volta
        while (read(vetor_pipe_volta[0], buffer, MAX_SIZE) > 0) //le do pipe de volta ate que algo seja escrito
        close(vetor_pipe_volta[0]); //fecha a porta de leitura do pipe de volta

        sscanf(buffer, "%d", &num); //converte o buffer para inteiro
        printf("Processo-pai(PID=%d) leu: %d\n", getpid(), num);

        wait(NULL); //espera o filho terminar
        printf("Processo-filho terminou\n");
        printf("Processo-pai terminou\n");

        exit(EXIT_SUCCESS);
        
    }
    return 0;
}