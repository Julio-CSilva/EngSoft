#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    //a partir daqui um novo processo e criado, enquanto o pai vai cair em ELSE, o filho que acabou
    //de ser criado com PID == 0 vai cair em ELSE IF.

    if (pid < 0){
        printf("Erro ao criar o processo!\n");
        return 1;


    } else if (pid == 0) {
        printf("Processo-filho(PID=%d), Pai(PID=%d)\n", getpid(), getppid());

        
    } else {
        //espera o filho terminar para continuar
        wait(NULL);
        printf("Processo-filho finalizou\n");


    }
    return 0;
}