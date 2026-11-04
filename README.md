# Documentação Técnica

### Recorte Escolhido: Serviços de Saúde Pública Municipais (postos de vacinação, hospitais de urgência, exames).

### Modelo dos Registros (struct):
Cada nó da lista encadeada armazena os seguintes campos:

id: Identificador único (inteiro).

titulo: Nome do serviço.

categoria: Área de atuação (ex: Vacinação, Urgência).

descricao: Breve explicação da utilidade do serviço.

requisitos: Documentos ou condições necessárias para o cidadão.

local: Região ou endereço de atendimento.

proX: Ponteiro para o próximo elemento da lista.

### Lista Encadeada: Implementação dinâmica utilizando alocação de memória (malloc e free), com inserção direta no início, percurso linear para listagem, e ajuste de ponteiros para exclusão segura.

### Menu Interativo: Interface via terminal baseada em um loop de controle (do-while com switch-case) e validação de opções inválidas.

# Análise de Algoritmos (Notacao Big-O)
- Insercao (cadastrar): O(1) — Os novos nós são inseridos diretamente no início da lista encadeada, exigindo tempo constante independentemente da quantidade de registros armazenados.
- Busca e Consulta (consultar): O(n) — Como a lista encadeada não permite acesso indexado direto, a busca linear exige percorrer sequencialmente os nós até encontrar o identificador ou termo desejado.
- Remocao (excluir): O(n) — No pior caso, é necessário percorrer toda a lista para localizar o elemento anterior e ajustar os ponteiros de encadeamento antes de liberar a memória com free.
- Ordenacao (ordenar - Insertion Sort): O(n^2) — O algoritmo reorganiza iterativamente os nós com base no ID por meio de remapeamento manual de ponteiros.

# Evidencias de Testes
Abaixo estão os testes realizados cobrindo cenários normais, limites e entradas inválidas:

| Caso de Teste | Entrada Simulada | Resultado Esperado | Resultado Observado | Status |
| :--- | :--- | :--- | :--- | :--- |
| **Lista Vazia** | Executar a opcao "Listar" ao iniciar | Mensagem informando que a base esta vazia | "A lista esta vazia!" | **Passou** |
| **Cadastro Normal** | ID: 101, Titulo: "Posto Central", Categoria: "Vacina" | Registro inserido com sucesso | "Servico cadastrado com sucesso!" | **Passou** |
| **ID Duplicado** | Inserir novo servico com ID: 101 | Bloquear insercao e avisar duplicidade | "Erro: Ja existe um servico com o ID 101!" | **Passou** |
| **Consulta Inexistente** | Buscar ID: 999 | Aviso amigavel de ausencia de resultado | "Consulta sem resultado: Nenhum servico encontrado..." | **Passou** |
| **Opcao Invalida** | Digitar 9 no menu principal | Exibir erro e reexibir o menu | "Opcao invalida! Escolha um numero de 1 a 8." | **Passou** |
