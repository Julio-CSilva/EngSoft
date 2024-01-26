#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>

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
    char *mem;
    printf("Processo-pai(PID=%d)\n", getpid());

    int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666); //cria a memoria compartilhada

    filho1 = fork(); //cria o primeiro filho
    if(!filho1){ //se for o filho 1
        implementacao_filho1(&a);
        mem = shmat(seg_id, NULL, 0); //anexa a memoria compartilhada ao processo1
        sprintf(mem, "escrevendo o valor do teste");
        printf("Valor da memoria compartilhada: %s (PID=%d)\n", mem, getpid());
        shmdt(mem); //desanexa a memoria compartilhada do processo
        exit(0);
    }

    status = wait(NULL);

    if (filho1>0){
        filho2 = fork(); //cria o segundo filho
        if(!filho2){ //se for o filho 2
            implementacao_filho2(&a);
            mem = shmat(seg_id, NULL, 0); //anexa a memoria compartilhada ao processo2
            printf("Valor da memoria compartilhada: %s (PID=%d)\n", mem, getpid());
            shmdt(mem); //desanexa a memoria compartilhada do processo
            exit(0);
        }
    }
    
    status = wait(NULL); //espera o filho 2 terminar

    printf("Processo-finalizado(PID=%d)\n", getpid());
    printf("Valor final de a: %d\n", a);
    shmctl(seg_id, IPC_RMID, NULL); //remove a memoria compartilhada
    exit(0);
    printf("Processo-pai finalizou\n");

    return 0;
}