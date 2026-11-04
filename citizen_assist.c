#include <stdio.h>
#include <stdlib.h>

typedef struct ServicoSaude {
    int id;                       //Identificador único
    char titulo[50];              //Ex: "Posto Central de Vacinacao"
    char categoria[30];           //Ex: "Vacinacao", "Urgencia", "Exames"
    char descricao[100];          //Breve descrição
    char requisitos[100];         //Ex: "RG, CPF e Cartao do SUS"
    char local[50];               //Ex: "Zona Norte"
    struct ServicoSaude* proX;    //Ponteiro para o próximo nó
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
//Função para criar um novo nó
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
//Verifica se um ID já existe na lista
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
    while(getchar() != '\n'); //Limpa buffer

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

    //Inserção no início da lista
    novo->proX = *inicio;
    *inicio = novo;

    printf("Servico cadastrado com sucesso!\n");
}
//Exibir um único registro 
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

void listar(ServicoSaude* inicio) {
    if (inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }
    printf("\n--- LISTA DE SERVICOS CADASTRADOS ---\n");
    ServicoSaude* atual = inicio;
    int total = 0;
    while (atual != NULL) {
        exibirRegistro(atual);
        total++;
        atual = atual->proX;
    }
    printf("Total de registros: %d\n", total);
}

//Consulta por ID
void consultar(ServicoSaude* inicio) {
    if (inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }
    int opcao;
    printf("\n--- CONSULTA E PESQUISA ---\n");
    printf("1. Consultar por ID\n");
    printf("2. Pesquisar por Categoria ou Titulo\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    while(getchar() != '\n');

    if (opcao == 1) {
        int idBuscado;
        printf("Digite o ID que deseja consultar: ");
        scanf("%d", &idBuscado);
        while(getchar() != '\n');

        ServicoSaude* atual = inicio;
        int encontrado = 0;
        
        while (atual != NULL) {
            if (atual->id == idBuscado) {
                printf("\nServico encontrado:\n");
                exibirRegistro(atual);
                encontrado = 1;
                break;
            }
            atual = atual->proX;
        }
        if (!encontrado) {
            printf("Consulta sem resultado: Nenhum servico encontrado com o ID %d.\n", idBuscado);
        }
    } else if (opcao == 2) {
        char termo[50];
        printf("Digite parte do titulo ou categoria: ");
        fgets(termo, sizeof(termo), stdin);
        removerNovaLinha(termo);

        ServicoSaude* atual = inicio;
        int encontrados = 0;
        printf("\nResultados da pesquisa por '%s':\n", termo);
        while (atual != NULL) {
            if (contemSubstring(atual->titulo, termo) || contemSubstring(atual->categoria, termo)) {
                exibirRegistro(atual);
                encontrados++;
            }
            atual = atual->proX;
        }
        if (encontrados == 0) {
            printf("Pesquisa sem resultado: Nenhum registro corresponde ao termo '%s'.\n", termo);
        } else {
            printf("Total de registros encontrados: %d\n", encontrados);
        }
    } else {
        printf("Opcao invalida!\n");
    }
}

//Ordenação
void ordenar(ServicoSaude** inicio) {
    if (*inicio == NULL || (*inicio)->proX == NULL) {
        printf("\nLista vazia ou com apenas um elemento. Nao e necessario ordenar.\n");
        return;
    }

    ServicoSaude* ordenado = NULL;
    ServicoSaude* atual = *inicio;

    while (atual != NULL) {
        ServicoSaude* proximo = atual->proX;

        if (ordenado == NULL || ordenado->id >= atual->id) {
            atual->proX = ordenado;
            ordenado = atual;
        } else {
            ServicoSaude* temp = ordenado;
            while (temp->proX != NULL && temp->proX->id < atual->id) {
                temp = temp->proX;
            }
            atual->proX = temp->proX;
            temp->proX = atual;
        }
        atual = proximo;
    }
    *inicio = ordenado;
    printf("\nLista ordenada com sucesso por ID (Insertion Sort)!\n");
}

//Atualização de registros
void atualizar(ServicoSaude* inicio) {
    if (inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }
    int idBuscado;
    printf("\n--- ATUALIZAR SERVICO ---\n");
    printf("Digite o ID do servico que deseja atualizar: ");
    scanf("%d", &idBuscado);
    while(getchar() != '\n');

    ServicoSaude* atual = inicio;
    while (atual != NULL && atual->id != idBuscado) {
        atual = atual->proX;
    }

    if (atual == NULL) {
        printf("Erro: Servico com ID %d nao encontrado.\n", idBuscado);
        return;
    }

    printf("Servico atual:\n");
    exibirRegistro(atual);

    printf("Digite o novo Titulo: ");
    fgets(atual->titulo, sizeof(atual->titulo), stdin);
    removerNovaLinha(atual->titulo);

    printf("Digite a nova Categoria: ");
    fgets(atual->categoria, sizeof(atual->categoria), stdin);
    removerNovaLinha(atual->categoria);

    printf("Digite a nova Descricao: ");
    fgets(atual->descricao, sizeof(atual->descricao), stdin);
    removerNovaLinha(atual->descricao);

    printf("Digite os novos Requisitos: ");
    fgets(atual->requisitos, sizeof(atual->requisitos), stdin);
    removerNovaLinha(atual->requisitos);

    printf("Digite o novo Local: ");
    fgets(atual->local, sizeof(atual->local), stdin);
    removerNovaLinha(atual->local);

    printf("Servico atualizado com sucesso!\n");
}

void excluir(ServicoSaude** inicio) {
    if (*inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }
    int idBuscado;
    printf("\n--- EXCLUIR SERVICO ---\n");
    printf("Digite o ID do servico que deseja excluir: ");
    scanf("%d", &idBuscado);
    while(getchar() != '\n');

    ServicoSaude* atual = *inicio;
    ServicoSaude* anterior = NULL;

    while (atual != NULL && atual->id != idBuscado) {
        anterior = atual;
        atual = atual->proX;
    }

    if (atual == NULL) {
        printf("Erro: Servico com ID %d nao encontrado.\n", idBuscado);
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->proX;
    } else {
        anterior->proX = atual->proX;
    }

    free(atual);
    printf("Servico excluido com sucesso!\n");
}

//Indicadores
void analise(ServicoSaude* inicio) {
    if (inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }
    int total = 0;
    ServicoSaude* atual = inicio;
    while (atual != NULL) {
        total++;
        atual = atual->proX;
    }
    printf("\n--- ANALISE E INDICADORES ---\n");
    printf("Total de servicos de saude cadastrados: %d\n", total);
    printf("Status da base de dados: Operante e integra.\n");
}

// Função para liberar memória ao sair
void liberarLista(ServicoSaude* inicio) {
    ServicoSaude* atual = inicio;
    while (atual != NULL) {
        ServicoSaude* proximo = atual->proX;
        free(atual);
        atual = proximo;
    }
}
// Função Principal
int main() {
    ServicoSaude* inicio = NULL;
    int opcao;

    do {
        printf("-------------------------------------------\n");
        printf("    CITIZEN ASSIST AI - SAUDE             \n");
        printf("-------------------------------------------\n");
        printf("1. Cadastrar servico\n");
        printf("2. Listar todos os servicos\n");
        printf("3. Consultar / Pesquisar servico\n");
        printf("4. Ordenar servicos (Insertion Sort)\n");
        printf("5. Atualizar servico\n");
        printf("6. Excluir servico\n");
        printf("7. Analise e indicadores\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida! Digite um numero.\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        switch (opcao) {
            case 1:
                cadastrar(&inicio);
                break;
            case 2:
                listar(inicio);
                break;
            case 3:
                consultar(inicio);
                break;
            case 4:
                ordenar(&inicio);
                listar(inicio);
                break;
            case 5:
                atualizar(inicio);
                break;
            case 6:
                excluir(&inicio);
                break;
            case 7:
                analise(inicio);
                break;
            case 8:
                printf("\nEncerrando o sistema e liberando memoria...\n");
                liberarLista(inicio);
                printf("Sistema encerrado com sucesso.\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha um numero de 1 a 8.\n");
        }
    } while (opcao != 8);

    return 0;
}
