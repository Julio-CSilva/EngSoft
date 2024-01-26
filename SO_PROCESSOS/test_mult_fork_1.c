#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int a=0;
void implementacao_filho1(int *a){ //funcao para criacao do filho 1
    *a = *a + 1;
    printf("executando filho 1(PID=%d)\n", getpid());
}

void implementacao_filho2(int *a){ //funcao para criacao do filho 2
    *a = *a + 2;
    printf("executando filho 2(PID=%d)\n", getpid());
}

int main(){

    int filho1, filho2, pid, status;
    printf("Processo-pai(PID=%d)\n", getpid());

    filho1 = fork(); //cria o primeiro filho
    if(!filho1){ //se for o filho 1
        implementacao_filho1(&a);
        exit(0);
    }

    wait(NULL);

    if (filho1>0){
        filho2 = fork(); //cria o segundo filho
        if(!filho2){ //se for o filho 2
            implementacao_filho2(&a);
            exit(0);
        }
    }
    
    pid=wait(NULL); //espera o filho 2 terminar

    printf("Processo-pai(PID=%d), o Processo-finalizado(PID=%d)\n", getppid(), pid);
    printf("Valor final de a: %d\n", a);

    exit(0);
    printf("Processo-pai finalizou\n");

    return 0;
}