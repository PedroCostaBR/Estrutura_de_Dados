# Sistema de Distribuição de Tarefas com Lista Circular

## 1. Identificação

| Campo | Informação |
|---|---|
| Disciplina | Estruturas de Dados |
| Grupo | XMens |
| Integrantes | Kauan, Henri, João Vitor, Rone, Pedro Henrique, Isaac Alves e Victor |
| Linguagem | C |
| Estrutura de dados | Lista simplesmente encadeada circular |
| Data de apresentação | 19/11/2026 |

## 2. Problema e objetivo

Em uma equipe, distribuir tarefas manualmente pode causar desorganização e concentrar atividades em algumas pessoas. O programa organiza essa distribuição em rodízio: permite cadastrar participantes, atribui cada tarefa ao próximo da ordem e mostra as tarefas recebidas por cada pessoa.

O sistema funciona pelo terminal. Os dados permanecem em memória durante a execução e são apagados quando o programa é encerrado.

## 3. Estrutura de dados

Cada participante é representado por um objeto da classe `Participante`. O objeto armazena o nome, uma lista de tarefas e a referência `proximo`, que aponta para o participante seguinte. O último participante aponta de volta para o primeiro, formando um ciclo.

A classe `ListaCircular` mantém a referência `_ultimo`. O próximo participante a receber uma tarefa é `_ultimo.proximo`. Ao distribuir uma tarefa, o programa a registra nesse participante e atualiza `_ultimo`. Assim, quem acabou de receber uma tarefa passa para o fim da ordem.

### Exemplo 1 — Cadastro e formação do ciclo

Ao cadastrar Ana, Bruno e Carla, os nós são ligados em sequência circular:

```C
participantes = ListaCircular()
participantes.adicionar("Ana")
participantes.adicionar("Bruno")
participantes.adicionar("Carla")
```

O encadeamento fica:

```text
Ana → Bruno → Carla
↑               ↓
└───────────────┘
```

Como o último nó é Carla, `_ultimo` aponta para Carla e `_ultimo.proximo` aponta para Ana, que será a próxima a receber uma tarefa.

### Exemplo 2 — Distribuição em rodízio

Com Ana, Bruno e Carla cadastrados, quatro chamadas consecutivas a `distribuir` produzem este resultado:

```C
participantes.distribuir("Tarefa 1")  # Ana
participantes.distribuir("Tarefa 2")  # Bruno
participantes.distribuir("Tarefa 3")  # Carla
participantes.distribuir("Tarefa 4")  # Ana
```

| Participante | Tarefas recebidas |
|---|---|
| Ana | Tarefa 1 e Tarefa 4 |
| Bruno | Tarefa 2 |
| Carla | Tarefa 3 |

Depois da quarta atribuição, Bruno é o próximo da vez. A distribuição continua do ponto em que parou, sem reiniciar a ordem.

### Exemplo 3 — Cadastro durante a distribuição

Com Ana e Bruno cadastrados, a primeira tarefa é atribuída a Ana. Bruno fica como próximo da vez. Ao cadastrar Carla, ela é inserida no fim da ordem atual:

```C
participantes.distribuir("Organizar documentos")  # Ana
participantes.adicionar("Carla")
participantes.distribuir("Preparar materiais")  # Bruno
participantes.distribuir("Conferir equipamentos")  # Carla
```

Depois do cadastro, a ordem de atendimento é Bruno, Carla e Ana, retornando a Bruno ao completar o ciclo. O novo participante passa a fazer parte do rodízio sem apagar as tarefas já atribuídas.

## 4. Funcionalidades

| Funcionalidade | Implementação | Descrição |
|---|---|---|
| Cadastrar participante | `ListaCircular.adicionar(nome)` | Cria o participante e o insere no fim da ordem circular. |
| Distribuir tarefa | `ListaCircular.distribuir(tarefa)` | Atribui a tarefa ao próximo participante e avança o rodízio. |
| Percorrer participantes | `ListaCircular.__iter__()` | Percorre os participantes uma vez, encerrando ao retornar ao primeiro nó. |
| Consultar ordem e tarefas | Opção 3 de `main()` | Exibe quem receberá a próxima tarefa, a ordem atual e as tarefas de cada pessoa. |
| Encerrar o programa | Opção 0 de `main()` | Finaliza a execução. |

O menu também valida entradas: não aceita nome ou descrição de tarefa vazios, informa quando não há participantes para receber uma tarefa e avisa quando a opção escolhida é inválida.

## 5. Complexidade

Considere `n` como o número de participantes e `m` como o número total de tarefas registradas.

| Operação | Complexidade | Justificativa |
|---|---:|---|
| Cadastrar participante | O(1) | Cria um nó e atualiza as referências, sem percorrer a lista. |
| Distribuir tarefa | O(1) amortizado | Acessa diretamente o próximo nó, registra a tarefa e atualiza `_ultimo`. |
| Consultar a ordem | O(n) | Percorre cada participante uma vez. |
| Consultar ordem e tarefas | O(n + m) | Percorre participantes e tarefas para exibi-los. |
| Memória utilizada | O(n + m) | Armazena um nó por participante e uma entrada por tarefa atribuída. |

## 6. Testes e resultados

| Situação testada | Resultado |
|---|---|
| Distribuir tarefa sem participantes | O programa solicita o cadastro de pelo menos um participante. |
| Distribuir quatro tarefas entre Ana, Bruno e Carla | As tarefas são atribuídas a Ana, Bruno, Carla e Ana, nessa ordem. |
| Cadastrar participante durante o rodízio | O novo participante entra no fim da ordem vigente. |
| Consultar participantes e tarefas | O programa mostra o próximo participante, a ordem e as tarefas atribuídas. |
| Informar nome ou tarefa vazia | O programa solicita uma entrada válida e não registra o valor vazio. |
| Cadastrar somente uma pessoa e distribuir tarefas | A mesma pessoa recebe as tarefas, pois seu nó aponta para si mesmo. |

## 7. Conclusão

A lista circular atende à necessidade de distribuir tarefas em sequência contínua. A referência ao último nó permite cadastrar participantes e avançar o rodízio sem percorrer toda a lista em cada operação. A consulta percorre os participantes para apresentar a ordem e o histórico de tarefas. Como os dados ficam apenas na memória, eles não são preservados após o encerramento. Uma melhoria possível é salvar participantes e tarefas em um arquivo para recuperar as informações em outra execução.
