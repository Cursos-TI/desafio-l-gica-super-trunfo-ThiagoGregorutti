#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para system("cls") ou system("clear")

// Definição da estrutura para a carta de país
typedef struct {
    char nome[50];
    int populacao; // Em milhões
    float area;    // Em km²
    float pib;     // Em trilhões de USD
    int pontosTuristicos; // Número de pontos turísticos
    float densidadeDemografica; // População / Área
} Pais;

// Enumeração para facilitar a manipulação dos atributos
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE_DEMOGRAFICA
} Atributo;

// Protótipos de funções
void exibirCarta(const Pais *carta);
void exibirMenuAtributos(int atributo_ja_escolhido);
float obterValorAtributo(const Pais *carta, Atributo atributo);
const char* obterNomeAtributo(Atributo atributo);
int compararAtributo(float val1, float val2, Atributo atributo); // Retorna 1 se carta1 vence, 2 se carta2 vence, 0 se empate

int main() {
    // Cartas pré-cadastradas (exemplo, você pode adicionar mais)
    Pais carta1 = {"Brasil", 215, 8.51, 1.9, 10, 25.26}; // Dados fictícios
    Pais carta2 = {"Canada", 38, 9.98, 2.0, 8, 3.81};    // Dados fictícios

    int escolha1, escolha2;
    int atributo1_ok = 0;
    int atributo2_ok = 0;

    printf("=== BEM-VINDO AO SUPER TRUNFO DE PAISES (NIVEL MESTRE)! ===\n");

    // Exibe as cartas que serão comparadas
    printf("\n--- Cartas em Jogo ---\n");
    printf("\nCarta 1:\n");
    exibirCarta(&carta1);
    printf("\nCarta 2:\n");
    exibirCarta(&carta2);
    printf("\n");

    // Loop para escolher o primeiro atributo
    while (!atributo1_ok) {
        exibirMenuAtributos(0); // 0 indica que nenhum atributo foi escolhido ainda
        printf("Escolha o PRIMEIRO atributo para comparar (1-5): ");
        scanf("%d", &escolha1);

        if (escolha1 >= 1 && escolha1 <= 5) {
            atributo1_ok = 1;
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
        // Limpar o buffer de entrada
        while (getchar() != '\n');
    }

    // Loop para escolher o segundo atributo
    while (!atributo2_ok) {
        exibirMenuAtributos(escolha1); // Passa o primeiro atributo escolhido
        printf("Escolha o SEGUNDO atributo para comparar (1-5): ");
        scanf("%d", &escolha2);

        if (escolha2 >= 1 && escolha2 <= 5) {
            if (escolha2 == escolha1) {
                printf("Voce nao pode escolher o mesmo atributo duas vezes! Tente novamente.\n");
            } else {
                atributo2_ok = 1;
            }
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
        // Limpar o buffer de entrada
        while (getchar() != '\n');
    }

    // Convertendo as escolhas para o tipo Atributo
    Atributo attr1 = (Atributo)escolha1;
    Atributo attr2 = (Atributo)escolha2;

    printf("\n--- RESULTADO DA RODADA ---\n");
    printf("Atributos escolhidos: %s e %s\n", obterNomeAtributo(attr1), obterNomeAtributo(attr2));

    float valor1_attr1 = obterValorAtributo(&carta1, attr1);
    float valor2_attr1 = obterValor2Atributo(&carta2, attr1); // Correção do erro de digitação
    float valor1_attr2 = obterValorAtributo(&carta1, attr2);
    float valor2_attr2 = obterValor2Atributo(&carta2, attr2); // Correção do erro de digitação

    printf("\n%s (%s: %.2f | %s: %.2f)\n", carta1.nome, obterNomeAtributo(attr1), valor1_attr1, obterNomeAtributo(attr2), valor1_attr2);
    printf("%s (%s: %.2f | %s: %.2f)\n", carta2.nome, obterNomeAtributo(attr1), valor2_attr1, obterNomeAtributo(attr2), valor2_attr2);

    // Comparação do primeiro atributo
    int vencedor_attr1 = compararAtributo(valor1_attr1, valor2_attr1, attr1);
    // Comparação do segundo atributo
    int vencedor_attr2 = compararAtributo(valor1_attr2, valor2_attr2, attr2);

    // Soma dos atributos
    float soma_carta1 = valor1_attr1 + valor1_attr2;
    float soma_carta2 = valor2_attr1 + valor2_attr2;

    printf("\nSoma dos atributos para %s: %.2f\n", carta1.nome, soma_carta1);
    printf("Soma dos atributos para %s: %.2f\n", carta2.nome, soma_carta2);

    // Determina o vencedor final
    if (soma_carta1 > soma_carta2) {
        printf("\n%s vence a rodada com a maior soma de atributos!\n", carta1.nome);
    } else if (soma_carta2 > soma_carta1) {
        printf("\n%s vence a rodada com a maior soma de atributos!\n", carta2.nome);
    } else {
        printf("\nEmpate!\n");
    }

    return 0;
}

// Implementação das funções
void exibirCarta(const Pais *carta) {
    printf("Nome: %s\n", carta->nome);
    printf("Populacao: %d milhoes\n", carta->populacao);
    printf("Area: %.2f km^2\n", carta->area);
    printf("PIB: %.2f trilhoes USD\n", carta->pib);
    printf("Pontos Turisticos: %d\n", carta->pontosTuristicos);
    printf("Densidade Demografica: %.2f hab/km^2\n", carta->densidadeDemografica);
}

void exibirMenuAtributos(int atributo_ja_escolhido) {
    printf("\n--- Escolha um Atributo ---\n");
    if (atributo_ja_escolhido != POPULACAO) printf("1. Populacao\n");
    if (atributo_ja_escolhido != AREA) printf("2. Area\n");
    if (atributo_ja_escolhido != PIB) printf("3. PIB\n");
    if (atributo_ja_escolhido != PONTOS_TURISTICOS) printf("4. Pontos Turisticos\n");
    if (atributo_ja_escolhido != DENSIDADE_DEMOGRAFICA) printf("5. Densidade Demografica\n");
}

float obterValorAtributo(const Pais *carta, Atributo atributo) {
    switch (atributo) {
        case POPULACAO:
            return (float)carta->populacao;
        case AREA:
            return carta->area;
        case PIB:
            return carta->pib;
        case PONTOS_TURISTICOS:
            return (float)carta->pontosTuristicos;
        case DENSIDADE_DEMOGRAFICA:
            return carta->densidadeDemografica