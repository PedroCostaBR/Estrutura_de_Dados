# Sistema de Distribuição de Tarefas com Lista Circular

## 1. Identificação

| Campo | Informação |
|---|---|
| Disciplina | Estruturas de Dados |
| Grupo | XMens |
| Integrantes | Kauan, Henri, João Vitor, Rone, Pedro Henrique, Isaac Alves e Victor |
| Linguagem | C (padrão C11) |
| Estruturas de dados | Lista circular de participantes e listas encadeadas de tarefas |
| Data de apresentação | 19/11/2026 |

## 2. Problema e objetivo

Em uma equipe, distribuir tarefas manualmente pode causar desorganização e concentrar atividades em algumas pessoas. O programa organiza essa distribuição em rodízio: permite cadastrar participantes, atribui cada tarefa ao próximo da ordem e mostra as tarefas recebidas por cada pessoa.

O sistema funciona pelo terminal. Os dados permanecem em memória durante a execução e são liberados quando o programa é encerrado.

## 3. Estruturas de dados

Cada participante é representado por um nó da estrutura `Participante`, que contém o nome, ponteiros para a primeira e a última tarefa e um ponteiro para o próximo participante. O último participante aponta de volta para o primeiro, formando uma lista circular.

Cada tarefa é um nó da estrutura `Tarefa`, com sua descrição e um ponteiro para a tarefa seguinte. As tarefas de cada participante formam uma lista encadeada separada.

A estrutura `ListaCircular` guarda o ponteiro `ultimo`. O próximo participante a receber uma tarefa é `ultimo->proximo`. Depois da atribuição, `ultimo` passa a apontar para quem acabou de receber a tarefa. Ao cadastrar alguém, o novo participante é inserido no fim da ordem atual. Se houver apenas um participante, seu ponteiro `proximo` aponta para ele mesmo.

### Exemplo 1 — Cadastro e formação do ciclo

Considerando uma lista inicialmente vazia, os cadastros podem ser feitos assim:

```c
ListaCircular lista = {NULL};
adicionar(&lista, "Ana");
adicionar(&lista, "Bruno");
adicionar(&lista, "Carla");
```

O encadeamento circular fica:

```text
Ana → Bruno → Carla
↑               ↓
└───────────────┘
```

O ponteiro `lista.ultimo` aponta para Carla e `lista.ultimo->proximo` aponta para Ana. Portanto, Ana é a próxima participante a receber uma tarefa.

### Exemplo 2 — Distribuição em rodízio

Com Ana, Bruno e Carla cadastrados, quatro chamadas consecutivas a `distribuir` atribuem as tarefas nesta ordem:

```c
distribuir(&lista, "Tarefa 1"); /* Ana */
distribuir(&lista, "Tarefa 2"); /* Bruno */
distribuir(&lista, "Tarefa 3"); /* Carla */
distribuir(&lista, "Tarefa 4"); /* Ana */
```

| Participante | Tarefas recebidas |
|---|---|
| Ana | Tarefa 1 e Tarefa 4 |
| Bruno | Tarefa 2 |
| Carla | Tarefa 3 |

Após a quarta atribuição, Bruno é o próximo da vez. A função acrescenta cada tarefa ao fim da lista de tarefas de seu responsável.

### Exemplo 3 — Cadastro durante a distribuição

Com Ana e Bruno cadastrados, a primeira tarefa é atribuída a Ana. Bruno fica como próximo. Carla é então cadastrada no fim da ordem vigente:

```c
distribuir(&lista, "Organizar documentos"); /* Ana */
adicionar(&lista, "Carla");
distribuir(&lista, "Preparar materiais");   /* Bruno */
distribuir(&lista, "Revisar planilhas");    /* Ana */
distribuir(&lista, "Conferir equipamentos");/* Carla */
```

Depois do cadastro, a ordem de atendimento é Bruno, Ana e Carla, retornando a Bruno ao completar o ciclo. As tarefas anteriores permanecem registradas.

## 4. Funcionalidades

| Funcionalidade | Implementação | Descrição |
|---|---|---|
| Cadastrar participante | `adicionar` | Aloca um nó para o participante e o insere no fim da lista circular. |
| Distribuir tarefa | `distribuir` | Aloca um nó de tarefa, acrescenta-o à lista do próximo participante e avança o rodízio. |
| Mostrar ordem e tarefas | `mostrar` | Percorre os participantes e as tarefas de cada um, exibindo também quem será o próximo. |
| Ler entrada | `ler_linha` | Lê uma linha, remove espaços no início e no fim e verifica o limite de texto. |
| Liberar memória | `liberar` | Libera os nós de tarefas e participantes antes de encerrar. |

O menu permite cadastrar participantes, distribuir tarefas, consultar a ordem e sair. Entradas vazias e opções inválidas são tratadas com mensagens. Nomes e descrições aceitam até 255 bytes. Falhas de alocação de memória são verificadas e informadas.

## 5. Complexidade

Considere `n` como o número de participantes e `m` como o número total de tarefas registradas.

| Operação | Complexidade | Justificativa |
|---|---:|---|
| Cadastrar participante | O(1) | Insere o nó usando o ponteiro para o último participante, sem percorrer a lista. |
| Distribuir tarefa | O(1) | Acessa `ultimo->proximo` e acrescenta a tarefa usando o ponteiro `ultima_tarefa`. |
| Mostrar participantes | O(n) | Percorre cada participante uma vez. |
| Mostrar participantes e tarefas | O(n + m) | Percorre todos os participantes e todos os nós de tarefas. |
| Memória utilizada | O(n + m) | Mantém um nó para cada participante e outro para cada tarefa. |

## 6. Cenários de uso

| Situação | Comportamento do programa |
|---|---|
| Distribuir tarefa sem participantes | O programa informa que é necessário cadastrar pelo menos um participante. |
| Distribuir quatro tarefas entre Ana, Bruno e Carla | As tarefas são atribuídas a Ana, Bruno, Carla e Ana, nessa ordem. |
| Cadastrar participante durante o rodízio | O novo participante entra no fim da ordem vigente e passa a receber tarefas no ciclo. |
| Consultar participantes e tarefas | O programa mostra o próximo participante, a ordem e as tarefas atribuídas. |
| Informar nome ou descrição vazia | O programa solicita um valor válido e não registra o campo vazio. |
| Cadastrar uma pessoa e distribuir várias tarefas | A mesma pessoa recebe as tarefas, pois seu ponteiro para o próximo aponta para si mesma. |
| Encerrar a execução | As tarefas e os participantes alocados são liberados pela função `liberar`. |

## 7. Conclusão

A lista circular organiza a distribuição contínua de tarefas e permite cadastrar participantes sem percorrer todos os nós. As listas encadeadas de tarefas mantêm o histórico de cada pessoa, e os ponteiros para a última tarefa tornam constante o custo de acrescentar uma nova. A consulta percorre os dados para exibi-los, e a memória utilizada é liberada ao encerrar o programa. Como melhoria, os dados poderiam ser salvos em arquivo para que o histórico permanecesse disponível entre execuções.
