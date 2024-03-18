#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Erro ao criar o processo filho
        perror("Erro ao criar o processo filho");
        return 1;
    } else if (pid == 0) {
        // Processo filho
        printf("Processo filho\n");
    } else {
        // Processo pai
        printf("Processo pai\n");
    }

    return 0;
}

/*
A função fork() é uma chamada de sistema em sistemas Unix e sistemas operacionais baseados em Unix, como Linux e macOS. Essa função é usada para criar um novo processo, que é uma cópia exata do processo que a chamou. Aqui está uma explicação básica de como ela funciona:

    Quando você chama fork() em um programa C, o sistema operacional faz uma cópia completa do processo atual, incluindo o código, dados, pilha e contexto do processo.

    Após a chamada para fork(), dois processos são executados simultaneamente. Um é o processo pai (o processo original que chamou fork()) e o outro é o processo filho (a cópia exata).

    O valor de retorno da função fork() é diferente para cada processo. Para o processo pai, fork() retorna o PID (identificador de processo) do processo filho recém-criado. Para o processo filho, fork() retorna 0.

    Assim, após a chamada para fork(), o programa tem dois fluxos de execução paralelos: um no processo pai e outro no processo filho.

    A partir do ponto da chamada para fork(), as operações feitas em cada processo são independentes. Isso significa que as alterações feitas em variáveis, manipulação de arquivos e outros recursos não afetam o outro processo.

    Normalmente, o processo filho é usado para executar uma tarefa separada do processo pai. O processo pai frequentemente monitora e controla o processo filho.

É importante notar que, enquanto a função fork() cria uma cópia do processo atual, essa cópia é feita pelo sistema operacional e não pelo próprio programa. Isso significa que, a partir do momento em que a chamada para fork() é feita, o processo pai e o processo filho são totalmente independentes e podem continuar a execução de forma independente um do outro.
*/
