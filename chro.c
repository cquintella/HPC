#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        return 1;
    }

    // Inicia o relógio
    clock_t start = clock();

    // Executa o comando fornecido na linha de comando
    int status = system(argv[1]);

    // Verifica se houve erro na execução do comando
    if (status == -1) {
        perror("Erro ao executar o comando");
        return 1;
    }

    // Calcula o tempo de execução
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    // Imprime o tempo de execução
    printf("Tempo de execução: %.6f segundos\n", duration);

    return 0;
}
