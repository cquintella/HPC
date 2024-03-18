#include <stdio.h>
#include <pthread.h>

void *child_thread_function(void *arg) {
    printf("Processo filho\n");
    return NULL;
}

int main() {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, child_thread_function, NULL);
    if (ret != 0) {
        perror("Erro ao criar a thread");
        return 1;
    }

    printf("Processo pai\n");

    // Espera pela thread filho terminar
    pthread_join(tid, NULL);

    return 0;
}


/*

O tipo pthread_t é usado para representar um identificador de thread em sistemas que suportam a biblioteca de threads POSIX (Portable Operating System Interface). Este tipo é uma estrutura opaca definida pela biblioteca pthread.h e é usado para identificar threads individuais em um programa.
A estrutura real por trás de pthread_t é geralmente específica de cada implementação da biblioteca de threads, e geralmente não é necessário (ou possível) acessar diretamente seus membros. Em vez disso, você usa funções fornecidas pela biblioteca pthread.h para manipular threads.

A função pthread_create() é usada para criar uma nova thread em um programa que utiliza a biblioteca de threads POSIX. 

    thread: Um ponteiro para uma variável do tipo pthread_t, na qual o identificador da nova thread será armazenado.
    attr: Um ponteiro para um objeto pthread_attr_t que contém atributos para a nova thread. Normalmente, é passado como NULL para usar os atributos padrão.
    start_routine: Um ponteiro para a função que será executada pela nova thread. Esta função deve receber um ponteiro void e retornar um ponteiro void.
    arg: Um ponteiro para os argumentos que serão passados para a função start_routine.

A função pthread_create() cria uma nova thread que executa a função start_routine. Ela recebe um único argumento, arg, que é passado para start_routine como um argumento. O identificador da nova thread é armazenado na variável thread.

Se a criação da thread for bem-sucedida, pthread_create() retorna 0. Caso contrário, retorna um código de erro que indica o tipo de falha. Após a criação da thread, o novo thread começa a execução na função start_routine.

*/
