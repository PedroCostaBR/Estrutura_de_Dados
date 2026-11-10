# Estrutura_de_Dados
Repositório do projeto da disciplina de Estruturas de Dados.

## Distribuição de tarefas com lista circular

O programa em C cadastra participantes e distribui tarefas em sequência por meio
de uma lista circular simplesmente encadeada. Considerando o grupo formado por
Kauan, Henri, João Vitor, Rone, Pedro Henrique, Isaac Alves e Victor, as tarefas
são atribuídas nessa ordem; após Victor, o percorrimento volta a Kauan.

Compile com GCC a partir da pasta do projeto e execute no PowerShell.

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic distribuicao.c -o distribuicao.exe
.\distribuicao.exe
```

No Linux, use `-o distribuicao` e execute `./distribuicao`.
Nomes e descrições aceitam até 255 bytes cada.

### Como funciona

Cada participante é representado por um nó de lista encadeada (`Participante`),
que contém o nome, os ponteiros para a primeira e a última tarefa e o ponteiro
de encadeamento `proximo`. O último participante aponta para o primeiro; quando
há apenas um participante, seu ponteiro `proximo` aponta para o próprio nó.

A estrutura da lista mantém o ponteiro de cauda/último (`ultimo`). Assim, o
próximo participante é acessado diretamente por `ultimo->proximo`. Depois da
atribuição, `ultimo` passa a apontar para o participante que recebeu a tarefa,
mantendo a ordem de distribuição. Um novo participante é ligado entre o último
e o primeiro, passando a ocupar o fim da ordem.

Tanto o cadastro quanto a distribuição têm complexidade O(1): o cadastro
atualiza os ponteiros de encadeamento do último e do novo nó sem percorrer a
lista, e a distribuição acessa o próximo participante e acrescenta a tarefa
usando `ultima_tarefa`, sem percorrer a lista de tarefas desse participante.

Participantes e tarefas são criados com alocação dinâmica na Heap via
`malloc()`. Na consulta, o programa faz o percorrimento da lista circular e
percorre também as tarefas vinculadas a cada participante. Para n participantes
e m tarefas no total, essa operação tem complexidade O(n + m), pois cada nó de
participante e cada nó de tarefa é visitado uma vez.

Ao encerrar, a função `liberar` desfaz a circularidade da lista e usa iteração
no desalocador para percorrer os nós e chamar `free()` em cada tarefa e
participante. Esse processo tem complexidade O(n + m) e evita vazamento de
memória (memory leak). Os dados permanecem em memória apenas durante a execução
do programa.


..