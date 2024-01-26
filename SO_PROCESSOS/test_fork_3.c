#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    pid = fork();
    //a partir daqui um novo processo e criado, enquanto o pai vai cair em ELSE, o filho que acabou
    //de ser criado com PID == 0 vai cair em ELSE IF.

    if (pid < 0){
        fprintf(stderr, "Erro ao criar o processo!\n");
        exit(-1); //finaliza o processo com erro


    } else if (pid == 0) {
        printf("Processo-filho(PID=%d), Pai(PID=%d)\n", getpid(), getppid());
        execlp("/bin/ls", "ls", "-l", NULL);//sobreescreve o processo filho com o processo ls
        printf("Teste do execlp\n");
        exit(0);//finaliza o processo

        
    } else {
        //espera o filho terminar para continuar
        wait(NULL);
        printf("Processo-filho finalizou\n");
        exit(0);

    }
    return 0;
}