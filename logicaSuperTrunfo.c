#include <stdio.h>
#include <string.h>

// Estrutura da carta
typedef struct {
    char codigo[4];
    char nome[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
} Carta;

void calcularAtributos(Carta *c) {
    c->densidade = c->area > 0 ? (float)c->populacao / c->area : 0;
    c->pibPerCapita = c->populacao > 0 ? c->pib / c->populacao : 0;
}

void exibirMenu(int ignorar) {
    printf("\nEscolha um atributo para comparar:\n");
    if (ignorar != 1) printf("1 - População\n");
    if (ignorar != 2) printf("2 - Área\n");
    if (ignorar != 3) printf("3 - PIB\n");
    if (ignorar != 4) printf("4 - Pontos Turísticos\n");
    if (ignorar != 5) printf("5 - Densidade Populacional\n");
    if (ignorar != 6) printf("6 - PIB per Capita\n");
    printf("Escolha: ");
}

float obterValor(Carta c, int opcao) {
    switch(opcao) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.densidade;
        case 6: return c.pibPerCapita;
        default: return -1;
    }
}

void nomeAtributo(int opcao) {
    switch(opcao) {
        case 1: printf("População"); break;
        case 2: printf("Área"); break;
        case 3: printf("PIB"); break;
        case 4: printf("Pontos Turísticos"); break;
        case 5: printf("Densidade Populacional"); break;
        case 6: printf("PIB per Capita"); break;
    }
}

void cadastrarCarta(Carta *c, int num) {
    printf("\n--- Cadastro da Carta %d ---\n", num);
    printf("Código (ex: A01): ");
    scanf(" %3s", c->codigo);
    printf("Nome do país: ");
    scanf(" %[^\n]", c->nome);
    printf("População (apenas números): ");
    scanf("%lu", &c->populacao);
    printf("Área em km²: ");
    scanf("%f", &c->area);
    printf("PIB em trilhões USD: ");
    scanf("%f", &c->pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &c->pontosTuristicos);
    calcularAtributos(c);
}

int main() {
    Carta c1, c2;
    int escolha1, escolha2;

    // Cadastro das cartas
    cadastrarCarta(&c1, 1);
    cadastrarCarta(&c2, 2);

    // Escolha dos atributos
    exibirMenu(0);
    scanf("%d", &escolha1);

    do {
        exibirMenu(escolha1);
        scanf("%d", &escolha2);
        if (escolha2 == escolha1)
            printf("Você já escolheu esse atributo. Escolha outro.\n");
    } while (escolha2 == escolha1);

    // Obtenção de valores
    float valor1_c1 = obterValor(c1, escolha1);
    float valor1_c2 = obterValor(c2, escolha1);
    float valor2_c1 = obterValor(c1, escolha2);
    float valor2_c2 = obterValor(c2, escolha2);

    // Verificação de vencedores
    int v1 = (escolha1 == 5) ? (valor1_c1 < valor1_c2) : (valor1_c1 > valor1_c2);
    int v2 = (escolha2 == 5) ? (valor2_c1 < valor2_c2) : (valor2_c1 > valor2_c2);

    float soma1 = valor1_c1 + valor2_c1;
    float soma2 = valor1_c2 + valor2_c2;

    // Resultado
    printf("\n--- RESULTADO FINAL ---\n");
    printf("Carta 1: %s\n", c1.nome);
    printf("Carta 2: %s\n\n", c2.nome);

    printf("Atributo 1: ");
    nomeAtributo(escolha1);
    printf("\n  %s: %.2f\n  %s: %.2f\n", c1.nome, valor1_c1, c2.nome, valor1_c2);
    printf("Vencedor: %s\n\n", v1 ? c1.nome : c2.nome);

    printf("Atributo 2: ");
    nomeAtributo(escolha2);
    printf("\n  %s: %.2f\n  %s: %.2f\n", c1.nome, valor2_c1, c2.nome, valor2_c2);
    printf("Vencedor: %s\n\n", v2 ? c1.nome : c2.nome);

    printf("Soma dos atributos:\n");
    printf("  %s: %.2f\n", c1.nome, soma1);
    printf("  %s: %.2f\n", c2.nome, soma2);

    if (soma1 == soma2)
        printf("Resultado final: Empate!\n");
    else
        printf("Resultado final: %s venceu a rodada!\n", (soma1 > soma2) ? c1.nome : c2.nome);

    return 0;
}
