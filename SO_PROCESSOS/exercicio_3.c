//3 processos rodando em paralelo
//1 imprime de 1 a 50
//2 imprime de 100 a 199
//3 imprime de 200 a 299

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid[2]={-1,-1};
    pid_t pid_pai = getpid();

    if(getpid() == pid_pai){
        pid[0] = fork(); //criando primeiro filho
    }
    if(getpid() == pid_pai){
        pid[1] = fork(); //criando segundo filho
    }

    if(getpid() == pid_pai){
        for(int i=1; i<=50; i++){
            printf("%d\n", i);
            sleep(2);
        }
        printf("Processo-pai(PID=%d) vai morrer!", getpid());
        exit(0);
    }

    if(pid[1] == 0){
        printf("Filho 1 foi criado!\n");
        for(int i=100; i<=199; i++){
            printf("%d\n", i);
            sleep(1);
        }
        printf("Processo-filho-1(PID=%d, PID_PAI=%d) vai morrer!", getpid(), getppid());
    }
    
    if(pid[0]== 0){
        printf("Filho 2 foi criado!\n");
        for(int i=200; i<=299; i++){
            printf("%d\n", i);
            sleep(1);
        }
        printf("Processo-filho-2(PID=%d, PID_PAI=%d) vai morrer!", getpid(), getppid());
    }

    return 0;
}
