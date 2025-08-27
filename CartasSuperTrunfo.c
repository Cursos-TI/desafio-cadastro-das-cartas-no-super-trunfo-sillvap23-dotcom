#include <stdio.h>



int main() {
  //variáveis da carta1
    char estado1[30];      // Estado (ex"Ceará)
    char codigo1[10];       //Código ("C01")
    char nomeCidade1[50];   // Nome da Cidade
    int populacao1;         // População Total
    float area1;            // Área em km²
    float pib1;             // PIB em Bilhões
    int pontosTuristicos1;  //Número de pontos turísticos

    //variáveis da carta2
    char estado2[30];      // Estado (ex"Ceará)
    char codigo2[10];       //Código ("C01")
    char nomeCidade2[50];   // Nome da Cidade
    int populacao2;         // População Total
    float area2;            // Área em km²
    float pib2;             // PIB em Bilhões
    int pontosTuristicos2;  //Número de pontos turísticos

    //As variavéis servem para armazenar as informações que o programa precisar manipular e mostrar.

    //Entrada dos dados da carta1
    printf("== Carta 1 ==\n");
    printf("Digite o estado da carta:");
    scanf("%s", estado1);

    printf("Digite o código da carta: ");
    scanf("%s", codigo1);

    printf("Digite o nome da cidade: ");
    scanf("%s", nomeCidade1);

    printf("Digite a população: ");
    scanf("%d", &populacao1);

    printf("Digite a área em km²: ");
    scanf("%f", &area1);
    
    printf("Digite o PIB (em bilões de reais): ");
    scanf("%f", &pib1);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &pontosTuristicos1);

     //Entrada dos dados da carta2
    printf("== Carta 2 ==\n");
    printf("Digite o estado da carta:");
    scanf("%s", estado2);

    printf("Digite o código da carta: ");
    scanf("%s", codigo2);

    printf("Digite o nome da cidade: ");
    scanf("%s", nomeCidade2);

    printf("Digite a população: ");
    scanf("%d", &populacao2);

    printf("Digite a área em km²: ");
    scanf("%f", &area2);
    
    printf("Digite o PIB (em bilões de reais): ");
    scanf("%f", &pib2);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &pontosTuristicos2);
    //O "pintf" é usado para mostrar as mensagens e resultados.
    //o "scanf" é usado para ler os dados digitados pelo usuário.
    
    //Exibição da carta1
    printf("\n=== Carta 1 ===\n");
    printf("Estado: %s\n", estado1);
    printf("Código: %s\n", codigo1);
    printf("CIdade: %s\n", nomeCidade1);
    printf("População: %d\n", populacao1);
    printf("Área: %.2f km²\n", area1);
    printf("PIB: %.2f bilhões de reais\n", pib1);
    printf("Pontos Turísticos: %d\n", pontosTuristicos1);

    //Exibição da carta2
    printf("\n=== Carta 2 ===\n");
    printf("Estado: %s\n", estado2);
    printf("Código: %s\n", codigo2);
    printf("CIdade: %s\n", nomeCidade2);
    printf("População: %d\n", populacao2);
    printf("Área: %.2f km²\n", area2);
    printf("PIB: %.2f bilhões de reais\n", pib2);
    printf("Pontos Turísticos: %d\n", pontosTuristicos2);


    return 0;
}
