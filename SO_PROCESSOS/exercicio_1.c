//imprime primeiro o valor PID do filho
//em seguida imprime o valor PID do pai
//na pespectiva do filho imprime primeiro o PID proprio que e 0
//em seguida imprime o seu PID atualizado pelo sistema

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid, pid1;
    pid = fork();

    //a partir daqui um novo processo e criado, enquanto o pai vai cair em ELSE, o filho que acabou
    //de ser criado com PID == 0 vai cair em ELSE IF.

    if (pid < 0){
        printf("Erro ao criar o processo!\n");
        return 1;


    } else if (pid == 0) {
        pid1 = getpid();
        printf("Processo filho pid(PID=%d)\n", pid);
        printf("Processo filho pid1(PID=%d)\n", pid1);

        
    } else {
        pid1 = getpid();
        printf("Processo-pai pid(PID=%d)\n", pid);
        printf("Processo-pai pid1(PID=%d)\n", pid1);
        wait(NULL);

    }
    return 0;
}