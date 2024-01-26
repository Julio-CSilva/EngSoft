#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>

void implementacao_filho1(int *a){ //funcao para criacao do filho 1
    *a = *a + 1;
    printf("executando filho 1(PID=%d)\n", getpid());
}

void implementacao_filho2(int *a){ //funcao para criacao do filho 2
    *a = *a * 2;
    printf("executando filho 2(PID=%d)\n", getpid());
}

int main(){

    int filho1, filho2, pid, status;
    int *mem;
    int seg_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); //cria a memoria compartilhada

    mem = shmat(seg_id, NULL, 0); //anexa a memoria compartilhada ao processo-pai
    if(mem < 0 ){
        printf("Erro ao anexar a memoria compartilhada\n");
        return 0;
    }
    *mem = 5;
    printf("Processo-pai(PID=%d), valor do inteiro:%d\n", getpid(), *mem);
    filho1 = fork(); //cria o primeiro filho
    
    if(filho1 > 0){ //se for o pai
        filho2 = fork(); //cria o segundo filho
        
    }
    if(filho1==0){ //se for o filho 1}
        mem = shmat(seg_id, NULL, 0); //anexa a memoria compartilhada ao processo1
        // sleep(1);
        implementacao_filho1(mem);
        printf("Processo-filho1 sendo finalizado(PID=%d), valor do inteiro:%d\n", getpid(), *mem);
        shmdt(mem); //desanexa a memoria compartilhada do processo
        exit(0);
    } else if(filho2==0){ //se for o filho 2
        mem = shmat(seg_id, NULL, 0); //anexa a memoria compartilhada ao processo2
        implementacao_filho2(mem);
        printf("Processo-filho2 sendo finalizado(PID=%d), valor do inteiro:%d\n", getpid(), *mem);
        shmdt(mem); //desanexa a memoria compartilhada do processo
        exit(0);
    }
    for (size_t i = 0; i < 2; i++)
    {
        wait(NULL);
    }

    shmctl(seg_id, IPC_RMID, NULL); //remove a memoria compartilhada
    printf("Valor final do inteiro: %d\n", *mem);
    printf("Processo-finalizado(PID=%d)\n", getpid());
    exit(0);

    return 0;
}