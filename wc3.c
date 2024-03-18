#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_TOKENS 1000
#define MAX_LINE_LENGTH 1024

typedef struct {
    long int id;
    char token[MAX_LINE_LENGTH];
    int count;
} Token;

Token tokens[MAX_TOKENS];
int num_tokens = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *process_word(void *arg) {
    char *word = (char *)arg;

    pthread_mutex_lock(&mutex);

    for (int i = 0; i < num_tokens; ++i) {
        if (strcmp(tokens[i].token, word) == 0) {
            tokens[i].count++;
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
    }

    strcpy(tokens[num_tokens].token, word);
    tokens[num_tokens].id = num_tokens + 1;
    tokens[num_tokens].count = 1;
    num_tokens++;

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void read_and_process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *word = strtok(line, " \t\n");
        while (word != NULL) {
            pthread_t tid;
            pthread_create(&tid, NULL, process_word, (void *)word);
            pthread_join(tid, NULL);
            word = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
}

int compare_tokens(const void *a, const void *b) {
    const Token *token_a = (const Token *)a;
    const Token *token_b = (const Token *)b;
    return token_b->count - token_a->count;
}

void write_results(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    fprintf(file, "token_id,token_string,count\n");
    for (int i = 0; i < num_tokens; ++i) {
        fprintf(file, "%ld,%s,%d\n", tokens[i].id, tokens[i].token, tokens[i].count);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 5 || strcmp(argv[1], "-f") != 0 || strcmp(argv[3], "-o") != 0) {
        fprintf(stderr, "Uso: %s -f arquivo.txt -o saida.csv\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[2];
    const char *output_filename = argv[4];

    read_and_process_file(input_filename);

    qsort(tokens, num_tokens, sizeof(Token), compare_tokens);

    write_results(output_filename);

    return 0;
}
