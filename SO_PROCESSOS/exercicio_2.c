//cria uma filho e espera sua rotina ser finalizada
//o filho soma 5 + 15 e finaliza sua rotina
//o pai imprime o valor da variavel value, sem alteracao pois a variavel do filho vem de ambientes diferentes

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int value = 5;

int main(){
    pid_t pid;
    pid = fork(); //criacao do processo filho

    if(pid == 0){ //se for o filho
        value += 15;
        return 0;

    } else if (pid > 0) { //se for o pai
        wait(NULL);
        printf("PAI: value = %d\n", value);
        return 0;
    }
}