#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    pid_t pid[5]={-1,-1,-1,-1,-1};
    int status;

    pid[0] = fork();
    if(pid[0] < 0){ //erro ao criar o novo processo
        printf("Erro ao criar o processo!\n");
        return 1;
    }

    if (pid[0] > 0) { //se for o pai
        printf("Processo-pai: cria primeiro filho\n");
        pid[1] = fork();
        if(pid[1] < 0){ //erro ao criar o novo processo
            printf("Erro ao criar o processo!\n");
        return 1;
        }
    }
    
    //criando os filhos

    if(pid[0] == 0){ //filho do filho1 do processo-pai
        printf("filho1 do processo-pai(PID=%d), criando um filho...\n",getpid());
        pid[2] = fork();
    }

    if(pid[1] == 0){ //filho do filho2 do processo-pai
        printf("filho2 do processo-pai(PID=%d), criando um filho...\n",getpid());
        pid[3] = fork();
    }

    if((pid[0]==0) || (pid[1]==0)){
        for(;;);
    } else {
        status = wait(NULL);
        printf("Processo-filho(PID=%d) finalizou\n", status);
    }

    return 0;
}