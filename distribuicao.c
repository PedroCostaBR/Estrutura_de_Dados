#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { LIMITE_TEXTO = 255 };

typedef struct Tarefa {
    char descricao[LIMITE_TEXTO + 1];
    struct Tarefa *proxima;
} Tarefa;

typedef struct Participante {
    char nome[LIMITE_TEXTO + 1];
    Tarefa *primeira_tarefa;
    Tarefa *ultima_tarefa;
    struct Participante *proximo;
} Participante;

typedef struct {
    Participante *ultimo;
} ListaCircular;

static int adicionar(ListaCircular *lista, const char *nome)
{
    Participante *novo = malloc(sizeof *novo);
    if (novo == NULL) {
        return 0;
    }

    strcpy(novo->nome, nome);
    novo->primeira_tarefa = NULL;
    novo->ultima_tarefa = NULL;
    novo->proximo = novo;
    if (lista->ultimo != NULL) {
        novo->proximo = lista->ultimo->proximo;
        lista->ultimo->proximo = novo;
    }
    lista->ultimo = novo;
    return 1;
}

static const char *distribuir(ListaCircular *lista, const char *descricao)
{
    Tarefa *tarefa = malloc(sizeof *tarefa);
    if (tarefa == NULL) {
        return NULL;
    }

    Participante *responsavel = lista->ultimo->proximo;
    strcpy(tarefa->descricao, descricao);
    tarefa->proxima = NULL;
    if (responsavel->ultima_tarefa == NULL) {
        responsavel->primeira_tarefa = tarefa;
    } else {
        responsavel->ultima_tarefa->proxima = tarefa;
    }
    responsavel->ultima_tarefa = tarefa;

    /* Quem recebeu a tarefa passa para o fim da vez. */
    lista->ultimo = responsavel;
    return responsavel->nome;
}

static void mostrar(const ListaCircular *lista)
{
    if (lista->ultimo == NULL) {
        puts("Nenhum participante cadastrado.");
        return;
    }

    const Participante *primeiro = lista->ultimo->proximo;
    const Participante *atual = primeiro;
    printf("Próximo a receber uma tarefa: %s\n", primeiro->nome);
    puts("Participantes na ordem de distribuição:");
    do {
        printf("- %s\n", atual->nome);
        for (const Tarefa *tarefa = atual->primeira_tarefa;
             tarefa != NULL; tarefa = tarefa->proxima) {
            printf("  - %s\n", tarefa->descricao);
        }
        atual = atual->proximo;
    } while (atual != primeiro);
}

static void liberar(ListaCircular *lista)
{
    if (lista->ultimo == NULL) {
        return;
    }

    Participante *atual = lista->ultimo->proximo;
    lista->ultimo->proximo = NULL;
    while (atual != NULL) {
        Tarefa *tarefa = atual->primeira_tarefa;
        while (tarefa != NULL) {
            Tarefa *proxima = tarefa->proxima;
            free(tarefa);
            tarefa = proxima;
        }

        Participante *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->ultimo = NULL;
}

/* Retorna 1 para uma linha lida, 0 no fim da entrada e -1 se exceder o limite. */
static int ler_linha(const char *mensagem, char *texto)
{
    fputs(mensagem, stdout);
    fflush(stdout);
    if (fgets(texto, LIMITE_TEXTO + 2, stdin) == NULL) {
        return 0;
    }

    size_t tamanho = strcspn(texto, "\n");
    if (tamanho > LIMITE_TEXTO) {
        int caractere;
        do {
            caractere = getchar();
        } while (caractere != '\n' && caractere != EOF);
        printf("Digite até %d bytes de texto.\n", LIMITE_TEXTO);
        return -1;
    }

    size_t inicio = 0;
    while (inicio < tamanho && isspace((unsigned char)texto[inicio])) {
        inicio++;
    }
    while (tamanho > inicio && isspace((unsigned char)texto[tamanho - 1])) {
        tamanho--;
    }
    memmove(texto, texto + inicio, tamanho - inicio);
    texto[tamanho - inicio] = '\0';
    return 1;
}

int main(void)
{
    ListaCircular lista = {NULL};
    char texto[LIMITE_TEXTO + 2];

    while (1) {
        puts("\nDistribuição de tarefas");
        puts("1. Cadastrar participante");
        puts("2. Distribuir tarefa");
        puts("3. Mostrar ordem e tarefas atribuídas");
        puts("0. Sair");
        int leitura = ler_linha("Escolha uma opção: ", texto);
        if (leitura == 0) {
            break;
        }
        if (leitura < 0) {
            continue;
        }

        if (strcmp(texto, "1") == 0) {
            leitura = ler_linha("Nome do participante: ", texto);
            if (leitura == 0) {
                break;
            }
            if (leitura < 0) {
                continue;
            }
            if (texto[0] == '\0') {
                puts("Informe um nome.");
            } else if (adicionar(&lista, texto)) {
                printf("%s entrou no fim da ordem de distribuição.\n", texto);
            } else {
                puts("Memória insuficiente para cadastrar o participante.");
            }
        } else if (strcmp(texto, "2") == 0) {
            leitura = ler_linha("Descrição da tarefa: ", texto);
            if (leitura == 0) {
                break;
            }
            if (leitura < 0) {
                continue;
            }
            if (texto[0] == '\0') {
                puts("Informe uma tarefa.");
            } else if (lista.ultimo == NULL) {
                puts("Cadastre pelo menos um participante antes de distribuir tarefas.");
            } else {
                const char *responsavel = distribuir(&lista, texto);
                if (responsavel != NULL) {
                    printf("Tarefa atribuída a %s.\n", responsavel);
                } else {
                    puts("Memória insuficiente para registrar a tarefa.");
                }
            }
        } else if (strcmp(texto, "3") == 0) {
            mostrar(&lista);
        } else if (strcmp(texto, "0") == 0) {
            break;
        } else {
            puts("Opção inválida.");
        }
    }

    liberar(&lista);
    return 0;
}
