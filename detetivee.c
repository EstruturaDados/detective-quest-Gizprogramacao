#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a estrutura de cada cômodo (nó da árvore)
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/**
 * @brief Cria dinamicamente uma nova sala (nó da árvore).
 * * Aloca memória para uma nova sala, define seu nome e inicializa
 * os caminhos (filhos) como nulos.
 *
 * @param nome O nome da sala a ser criada.
 * @return Um ponteiro para a Sala recém-criada.
 */
Sala* criarSala(const char* nome) {
    // 1. Alocar memória para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // 2. Verificar se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        printf("Erro de alocacao de memoria! Nao foi possivel criar a sala.\n");
        exit(1); // Encerra o programa se a memória falhar
    }
    
    // 3. Definir os atributos da sala
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite ao jogador navegar interativamente pela mansão.
 *
 * Começando pela sala atual (raiz na primeira chamada), o jogador
 * escolhe entre esquerda (e), direita (d) ou sair (s). O programa
 * exibe a sala atual e continua até que o jogador saia ou
 * chegue a um cômodo sem saída (nó-folha).
 *
 * @param salaAtual O ponto de partida da exploração (inicialmente, o Hall).
 */
void explorarSalas(Sala* salaAtual) {
    char escolha;

    // O loop continua enquanto estivermos em uma sala válida
    while (salaAtual != NULL) {
        printf("\n========================================\n");
        printf("Voce esta em: %s\n", salaAtual->nome);

        // 1. Verificar se é um nó-folha (sem saídas)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este e um comodo sem saida. Fim da exploracao neste caminho.\n");
            break; // Encerra o loop de exploração
        }

        // 2. Apresentar as opções de caminho
        printf("Escolha seu caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf(" (e) Ir para a Esquerda (%s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf(" (d) Ir para a Direita (%s)\n", salaAtual->direita->nome);
        }
        printf(" (s) Sair da mansao\n");
        printf("Opcao: ");

        // 3. Ler a escolha do jogador (o espaço antes de %c ignora quebras de linha)
        scanf(" %c", &escolha);

        // 4. Processar a escolha
        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda; // Move o jogador para a esquerda
                } else {
                    printf("Caminho bloqueado. Nao ha nada a esquerda.\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita; // Move o jogador para a direita
                } else {
                    printf("Caminho bloqueado. Nao ha nada a direita.\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("Voce decidiu sair da mansao... Ate a proxima, detetive.\n");
                return; // Encerra a função (e o loop)

            default:
                printf("Opcao invalida. Por favor, escolha 'e', 'd' ou 's'.\n");
                break;
        }
    }
}

/**
 * @brief Libera toda a memória alocada para a árvore (mapa).
 * * Utiliza um percurso em pós-ordem para garantir que os filhos
 * sejam liberados antes dos pais.
 *
 * @param raiz O nó raiz da árvore a ser liberada.
 */
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvore(raiz->esquerda); // Libera sub-árvore esquerda
    liberarArvore(raiz->direita);  // Libera sub-árvore direita
    free(raiz);                   // Libera o nó atual
}

/**
 * @brief Ponto de entrada principal do programa.
 *
 * Monta a estrutura estática do mapa da mansão (a árvore binária)
 * e, em seguida, inicia o loop de exploração do jogador.
 */
int main() {
    // --- Montagem do Mapa da Mansão ---
    // A estrutura é criada aqui, usando alocação dinâmica.
    
    // Nível 0 (Raiz)
    Sala* raiz = criarSala("Hall de Entrada");

    // Nível 1
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Sala de Jantar");

    // Nível 2
    raiz->esquerda->esquerda = criarSala("Biblioteca");
    raiz->esquerda->direita = criarSala("Jardim de Inverno"); // Nó-folha

    raiz->direita->direita = criarSala("Cozinha");
    // raiz->direita->esquerda fica NULL (Corredor Vazio)

    // Nível 3
    raiz->esquerda->esquerda->esquerda = criarSala("Escritorio Secreto"); // Nó-folha
    raiz->direita->direita->esquerda = criarSala("Despensa"); // Nó-folha

    // --- Início do Jogo ---
    printf("--- Bem-vindo ao Detective Quest ---\n");
    printf("Voce esta na entrada da mansao. Explore os comodos para encontrar o culpado.\n");

    // Chama a função de exploração começando pela raiz (Hall)
    explorarSalas(raiz);

    // --- Limpeza ---
    // Libera toda a memória alocada para o mapa antes de sair
    liberarArvore(raiz);

    printf("\nJogo encerrado.\n");
    
    return 0;
}
