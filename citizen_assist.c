#include <stdio.h>
#include <stdlib.h>

typedef struct ServicoSaude {
    int id;                       // Identificador único
    char titulo[50];              // Ex: "Posto Central de Vacinacao"
    char categoria[30];           // Ex: "Vacinacao", "Urgencia", "Exames"
    char descricao[100];          // Breve descrição
    char requisitos[100];         // Ex: "RG, CPF e Cartao do SUS"
    char local[50];               // Ex: "Zona Norte"
    struct ServicoSaude* proX;    // Ponteiro para o próximo nó
} ServicoSaude;

void copiarString(char* destino, const char* origem, int tamanhoMaximo) {
    int i = 0;
    while (origem[i] != '\0' && i < tamanhoMaximo - 1) {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}
