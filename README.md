# Estrutura_de_Dados
Repositório referente ao projeto da matéria de Estrutura de Dados.

## Distribuição de tarefas com lista circular

O programa em C cadastra participantes e atribui uma tarefa por vez, seguindo a ordem
da lista. Por exemplo, com Ana, Bruno e Carla, as quatro primeiras tarefas vão
para Ana, Bruno, Carla e Ana.

Compile com GCC a partir da pasta do projeto e execute no PowerShell.

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic distribuicao.c -o distribuicao.exe
.\distribuicao.exe
```

No Linux, use `-o distribuicao` e execute `./distribuicao`.
Nomes e descrições aceitam até 255 bytes cada.

### Como funciona

Cada participante é um nó com uma referência `proximo`. O último nó aponta
para o primeiro. Se houver um único participante, o nó aponta para si mesmo.

A lista guarda o ponteiro `ultimo`. O próximo participante a receber uma
tarefa é `ultimo->proximo`. Depois de atribuir a tarefa, o programa avança
`ultimo` para o nó que acabou de receber, que passa a ficar no fim da ordem.
Um participante cadastrado durante a distribuição entra no fim da ordem atual.

Cadastro e distribuição levam tempo constante, O(1), pois a lista guarda o
último participante e cada participante guarda a última tarefa atribuída.
A opção de consulta percorre os participantes uma vez e exibe as tarefas de
cada um. Os dados ficam em memória durante a execução.
