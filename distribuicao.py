from __future__ import annotations

from collections.abc import Iterator


class Participante:
    def __init__(self, nome: str) -> None:
        self.nome = nome
        self.tarefas: list[str] = []
        self.proximo = self


class ListaCircular:
    def __init__(self) -> None:
        self._ultimo: Participante | None = None

    def adicionar(self, nome: str) -> None:
        novo = Participante(nome)
        if self._ultimo is not None:
            novo.proximo = self._ultimo.proximo
            self._ultimo.proximo = novo
        self._ultimo = novo

    def distribuir(self, tarefa: str) -> str | None:
        if self._ultimo is None:
            return None

        participante = self._ultimo.proximo
        participante.tarefas.append(tarefa)
        # Quem acabou de receber uma tarefa passa para o fim da vez.
        self._ultimo = participante
        return participante.nome

    def __iter__(self) -> Iterator[Participante]:
        if self._ultimo is None:
            return

        primeiro = self._ultimo.proximo
        atual = primeiro
        while True:
            yield atual
            atual = atual.proximo
            if atual is primeiro:
                break


def main() -> None:
    participantes = ListaCircular()

    while True:
        print("\nDistribuição de tarefas")
        print("1. Cadastrar participante")
        print("2. Distribuir tarefa")
        print("3. Mostrar ordem e tarefas atribuídas")
        print("0. Sair")
        opcao = input("Escolha uma opção: ").strip()

        if opcao == "1":
            nome = input("Nome do participante: ").strip()
            if nome:
                participantes.adicionar(nome)
                print(f"{nome} entrou no fim da ordem de distribuição.")
            else:
                print("Informe um nome.")
        elif opcao == "2":
            tarefa = input("Descrição da tarefa: ").strip()
            if not tarefa:
                print("Informe uma tarefa.")
                continue

            responsavel = participantes.distribuir(tarefa)
            if responsavel is None:
                print("Cadastre pelo menos um participante antes de distribuir tarefas.")
            else:
                print(f"Tarefa atribuída a {responsavel}.")
        elif opcao == "3":
            primeiro = next(iter(participantes), None)
            if primeiro is None:
                print("Nenhum participante cadastrado.")
            else:
                print(f"Próximo a receber uma tarefa: {primeiro.nome}")
                print("Participantes na ordem de distribuição:")
                for participante in participantes:
                    print(f"- {participante.nome}")
                    for tarefa in participante.tarefas:
                        print(f"  • {tarefa}")
        elif opcao == "0":
            return
        else:
            print("Opção inválida.")


if __name__ == "__main__":
    main()
