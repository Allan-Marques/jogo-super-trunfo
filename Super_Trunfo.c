#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARTAS 10
#define TAM_NOME 50

typedef struct {
    char estado[3];
    char codigo[4];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

// Protótipos das funções
void lerNomesJogadores(char jogador1[], char jogador2[], int tamanho);
int sorteiaJogadorInicial(const char jogador1[], const char jogador2[]);
void embaralharCartas(Carta cartas[], int n);
Carta removeTopCard(Carta deck[], int *count);
void addCardToBottom(Carta deck[], int *count, Carta card);
void exibirCartaComOpcoes(Carta carta);
int lerEscolhaAtributo(const char *jogador);
void pausa(void);
void exibirTutorial(void);

int main() {
    char jogador1[TAM_NOME], jogador2[TAM_NOME];
    int jogadorAtual; // 0 para jogador1, 1 para jogador2

    // Exibir tutorial inicial
    exibirTutorial();
    pausa();
    system("clear");  // Se estiver no Windows, use system("cls")

    // Ler nomes dos jogadores
    lerNomesJogadores(jogador1, jogador2, TAM_NOME);

    // Sorteio de quem começa
    srand(time(NULL));
    jogadorAtual = sorteiaJogadorInicial(jogador1, jogador2);

    // Definição das cartas com dados reais do Brasil
    Carta cartas[NUM_CARTAS] = {
        {"SP", "SP01", "São Paulo", 12396372, 1521.00, 699.28, 50},
        {"RJ", "RJ02", "Rio de Janeiro", 6775561, 1200.00, 364.68, 40},
        {"DF", "DF03", "Brasília", 3094325, 5802.00, 254.46, 35},
        {"MG", "MG04", "Belo Horizonte", 2530701, 331.00, 104.36, 25},
        {"AM", "AM05", "Manaus", 2255903, 11401.00, 102.78, 20},
        {"PR", "PR06", "Curitiba", 1948626, 435.00, 98.02, 30},
        {"RS", "RS07", "Porto Alegre", 1492530, 496.00, 81.53, 28},
        {"PE", "PE08", "Recife", 1661017, 218.00, 65.36, 22},
        {"CE", "CE09", "Fortaleza", 2703391, 314.00, 67.01, 26},
        {"BA", "BA10", "Salvador", 2900319, 693.00, 63.36, 27}
    };

    // Embaralhar as cartas
    embaralharCartas(cartas, NUM_CARTAS);

    // Distribuir as cartas entre os jogadores
    Carta deckJogador1[NUM_CARTAS];
    Carta deckJogador2[NUM_CARTAS];
    int count1 = NUM_CARTAS / 2;
    int count2 = NUM_CARTAS / 2;
    for (int i = 0; i < NUM_CARTAS; i++) {
        if (i % 2 == 0)
            deckJogador1[i / 2] = cartas[i];
        else
            deckJogador2[i / 2] = cartas[i];
    }

    int round = 1;
    // Loop do jogo: enquanto ambos os jogadores tiverem cartas
    while (count1 > 0 && count2 > 0) {
        printf("=== Rodada %d ===\n", round);
        printf("Neste turno, o jogador ativo verá sua carta e as opções para escolher o atributo.\n");

        // Identificar o deck do jogador ativo e do oponente
        Carta *deckAtivo, *deckOponente;
        int *countAtivo, *countOponente;
        const char *nomeAtivo, *nomeOponente;
        if (jogadorAtual == 0) {
            deckAtivo = deckJogador1;
            countAtivo = &count1;
            deckOponente = deckJogador2;
            countOponente = &count2;
            nomeAtivo = jogador1;
            nomeOponente = jogador2;
        } else {
            deckAtivo = deckJogador2;
            countAtivo = &count2;
            deckOponente = deckJogador1;
            countOponente = &count1;
            nomeAtivo = jogador2;
            nomeOponente = jogador1;
        }
        
        // Mostrar a carta do jogador ativo com as opções de atributo
        printf("\n%s, sua carta é:\n", nomeAtivo);
        exibirCartaComOpcoes(deckAtivo[0]);
        
        // O jogador ativo escolhe o atributo para comparar
        int escolha = lerEscolhaAtributo(nomeAtivo);
        
        // Revelar as cartas e comparar o atributo escolhido
        printf("\nRevelando as cartas...\n");
        printf("\nCarta de %s:\n", nomeAtivo);
        exibirCartaComOpcoes(deckAtivo[0]);
        printf("\nCarta de %s:\n", nomeOponente);
        exibirCartaComOpcoes(deckOponente[0]);
        
        // Obter os valores para o atributo escolhido
        float valorAtivo = 0, valorOponente = 0;
        switch (escolha) {
            case 1: // População
                valorAtivo = (float) deckAtivo[0].populacao;
                valorOponente = (float) deckOponente[0].populacao;
                break;
            case 2: // Área
                valorAtivo = deckAtivo[0].area;
                valorOponente = deckOponente[0].area;
                break;
            case 3: // PIB
                valorAtivo = deckAtivo[0].pib;
                valorOponente = deckOponente[0].pib;
                break;
            case 4: // Pontos Turísticos
                valorAtivo = (float) deckAtivo[0].pontosTuristicos;
                valorOponente = (float) deckOponente[0].pontosTuristicos;
                break;
            default: break;
        }
        
        // Comparar os valores e determinar o vencedor da rodada
        if (valorAtivo > valorOponente) {
            printf("\n%s venceu a rodada!\n", nomeAtivo);
            // Jogador ativo ganha ambas as cartas
            Carta cartaAtivo = removeTopCard(deckAtivo, countAtivo);
            Carta cartaOponente = removeTopCard(deckOponente, countOponente);
            addCardToBottom(deckAtivo, countAtivo, cartaAtivo);
            addCardToBottom(deckAtivo, countAtivo, cartaOponente);
            printf("%s ganhou a carta de %s!\n", nomeAtivo, nomeOponente);
        } else if (valorAtivo < valorOponente) {
            printf("\n%s venceu a rodada!\n", nomeOponente);
            // O oponente ganha ambas as cartas
            Carta cartaAtivo = removeTopCard(deckAtivo, countAtivo);
            Carta cartaOponente = removeTopCard(deckOponente, countOponente);
            addCardToBottom(deckOponente, countOponente, cartaAtivo);
            addCardToBottom(deckOponente, countOponente, cartaOponente);
            printf("%s ganhou a carta de %s!\n", nomeOponente, nomeAtivo);
            // Troca o jogador ativo
            jogadorAtual = (jogadorAtual == 0 ? 1 : 0);
        } else {
            // Empate: cada jogador recoloca sua carta no final
            printf("\nEmpate na rodada! Cada jogador recoloca sua carta.\n");
            Carta cartaAtivo = removeTopCard(deckAtivo, countAtivo);
            Carta cartaOponente = removeTopCard(deckOponente, countOponente);
            addCardToBottom(deckAtivo, countAtivo, cartaAtivo);
            addCardToBottom(deckOponente, countOponente, cartaOponente);
        }
        
        printf("\nCartas restantes: %s: %d, %s: %d\n", jogador1, count1, jogador2, count2);
        
        // Pedir para o próximo jogador pressionar Enter
        printf("\nPressione Enter para o próximo jogador...\n");
        pausa();
        system("clear");
        
        round++;
    }
    
    // Exibir o vencedor
    if (count1 == 0) {
        printf("%s venceu o jogo!\n", jogador2);
    } else {
        printf("%s venceu o jogo!\n", jogador1);
    }
    
    return 0;
}

// Implementação das funções

void lerNomesJogadores(char jogador1[], char jogador2[], int tamanho) {
    printf("Digite o nome do Jogador 1: ");
    fgets(jogador1, tamanho, stdin);
    jogador1[strcspn(jogador1, "\n")] = '\0';
    
    printf("Digite o nome do Jogador 2: ");
    fgets(jogador2, tamanho, stdin);
    jogador2[strcspn(jogador2, "\n")] = '\0';
}

int sorteiaJogadorInicial(const char jogador1[], const char jogador2[]) {
    int jAtual = rand() % 2; // 0 para jogador1, 1 para jogador2
    printf("\n%s começa o jogo!\n", jAtual == 0 ? jogador1 : jogador2);
    return jAtual;
}

void embaralharCartas(Carta cartas[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}

Carta removeTopCard(Carta deck[], int *count) {
    Carta top = deck[0];
    for (int i = 1; i < *count; i++) {
        deck[i - 1] = deck[i];
    }
    (*count)--; 
    return top;
}

void addCardToBottom(Carta deck[], int *count, Carta card) {
    deck[*count] = card;
    (*count)++;
}

void exibirCartaComOpcoes(Carta carta) {
    printf("Estado: %s\n", carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("Nome da Cidade: %s\n", carta.nomeCidade);
    printf("População: %d\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões de reais\n", carta.pib);
    printf("Número de Pontos Turísticos: %d\n", carta.pontosTuristicos);
    printf("\nEscolha um atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Número de Pontos Turísticos\n");
}

int lerEscolhaAtributo(const char *jogador) {
    int escolha;
    do {
        printf("\n%s, escolha um atributo (1-4): ", jogador);
        if (scanf(" %d", &escolha) != 1) {
            while(getchar() != '\n');
            escolha = 0;
        }
    } while (escolha < 1 || escolha > 4);
    return escolha;
}

void pausa(void) {
    printf("\nPressione Enter para continuar...");
    while(getchar() != '\n');
}

void exibirTutorial(void) {
    printf("===== Bem-vindo ao Super Trunfo Brasileiro! =====\n\n");
    printf("Neste jogo, cada jogador receberá um deck de cartas representando cidades brasileiras reais.\n");
    printf("Cada carta contém informações como:\n");
    printf(" - Estado e Código\n");
    printf(" - Nome da Cidade\n");
    printf(" - População\n");
    printf(" - Área\n");
    printf(" - PIB\n");
    printf(" - Número de Pontos Turísticos\n\n");
    printf("Como jogar:\n");
    printf("1. Cada jogador recebe metade do deck de cartas.\n");
    printf("2. Em cada rodada, apenas o jogador ativo verá sua carta.\n");
    printf("3. O jogador ativo escolherá um atributo para comparar com a carta do oponente.\n");
    printf("4. As duas cartas serão reveladas e o atributo escolhido será comparado.\n");
    printf("   - A carta com o maior valor vence a rodada e o vencedor leva ambas as cartas.\n");
    printf("   - Em caso de empate, cada jogador recoloca sua carta no final do deck.\n");
    printf("5. O jogo continua até que um dos jogadores fique sem cartas.\n");
    printf("6. O vencedor é o jogador que ficar com todas as cartas ou o último a ter cartas restantes.\n\n");
    printf("Boa sorte e divirta-se!\n");
}
