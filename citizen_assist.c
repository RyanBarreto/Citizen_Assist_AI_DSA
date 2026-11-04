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

void removerNovaLinha(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int contemSubstring(const char* texto, const char* termo) {
    if (termo[0] == '\0') return 1;
    int i = 0;
    while (texto[i] != '\0') {
        int j = 0;
        while (texto[i + j] != '\0' && termo[j] != '\0' && texto[i + j] == termo[j]) {
            j++;
        }
        if (termo[j] == '\0') return 1;
        i++;
    }
    return 0;
}
// Função para criar um novo nó
ServicoSaude* criarServico(int id, char* titulo, char* categoria, char* descricao, char* requisitos, char* local) {
    ServicoSaude* novo = (ServicoSaude*) malloc(sizeof(ServicoSaude));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novo->id = id;
    copiarString(novo->titulo, titulo, sizeof(novo->titulo));
    copiarString(novo->categoria, categoria, sizeof(novo->categoria));
    copiarString(novo->descricao, descricao, sizeof(novo->descricao));
    copiarString(novo->requisitos, requisitos, sizeof(novo->requisitos));
    copiarString(novo->local, local, sizeof(novo->local));
    novo->proX = NULL;
    return novo;
}
// Verifica se um ID já existe na lista
int existeId(ServicoSaude* inicio, int id) {
    ServicoSaude* atual = inicio;
    while (atual != NULL) {
        if (atual->id == id) return 1;
        atual = atual->proX;
    }
    return 0;
}

void cadastrar(ServicoSaude** inicio) {
    int id;
    char titulo[50], categoria[30], descricao[100], requisitos[100], local[50];

    printf("\n--- CADASTRAR NOVO SERVICO ---\n");
    printf("Digite o ID unico (inteiro): ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada invalida!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n'); // Limpa buffer

    if (existeId(*inicio, id)) {
        printf("Erro: Ja existe um servico com o ID %d!\n", id);
        return;
    }

    printf("Titulo do servico: ");
    fgets(titulo, sizeof(titulo), stdin);
    removerNovaLinha(titulo);

    printf("Categoria (ex: Vacinacao, Urgencia): ");
    fgets(categoria, sizeof(categoria), stdin);
    removerNovaLinha(categoria);

    printf("Descricao: ");
    fgets(descricao, sizeof(descricao), stdin);
    removerNovaLinha(descricao);

    printf("Requisitos: ");
    fgets(requisitos, sizeof(requisitos), stdin);
    removerNovaLinha(requisitos);

    printf("Local / Regiao: ");
    fgets(local, sizeof(local), stdin);
    removerNovaLinha(local);

    ServicoSaude* novo = criarServico(id, titulo, categoria, descricao, requisitos, local);

    // Inserção no início da lista
    novo->proX = *inicio;
    *inicio = novo;

    printf("Servico cadastrado com sucesso!\n");
}
// Exibir um único registro 
void exibirRegistro(ServicoSaude* s) {
    printf("----------------------------------------\n");
    printf("ID: %d\n", s->id);
    printf("Titulo: %s\n", s->titulo);
    printf("Categoria: %s\n", s->categoria);
    printf("Descricao: %s\n", s->descricao);
    printf("Requisitos: %s\n", s->requisitos);
    printf("Local: %s\n", s->local);
    printf("----------------------------------------\n");
}
