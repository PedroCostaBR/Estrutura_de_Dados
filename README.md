# Estrutura_de_Dados
Repositório referente ao projeto da matéria de Estrutura de Dados.

## Distribuição de tarefas com lista circular

O programa cadastra participantes e atribui uma tarefa por vez, seguindo a ordem
da lista. Por exemplo, com Ana, Bruno e Carla, as quatro primeiras tarefas vão
para Ana, Bruno, Carla e Ana.

Execute com Python 3.10 ou superior a partir da pasta do projeto.

```bash
python distribuicao.py
```

### Como funciona

Cada participante é um nó com uma referência `proximo`. O último nó aponta
para o primeiro. Se houver um único participante, o nó aponta para si mesmo.

A lista guarda a referência `_ultimo`. O próximo participante a receber uma
tarefa é `_ultimo.proximo`. Depois de atribuir a tarefa, o programa avança
`_ultimo` para o nó que acabou de receber, que passa a ficar no fim da ordem.
Um participante cadastrado durante a distribuição entra no fim da ordem atual.

Cadastro e distribuição levam tempo constante, O(1), considerando o custo
amortizado de registrar uma tarefa. A opção de consulta percorre os
participantes uma vez e exibe as tarefas de cada um. Os dados ficam em memória
durante a execução.
