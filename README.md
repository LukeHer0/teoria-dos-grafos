
# Implementação de algoritmos Minimum spanning tree e Shortest path

Projeto de implementação de algoritmos de Minimum spanning tree e Shortest path para a disciplina Teoria de Grafos.

## Estrutura

Algoritmos implementados:

* Dijkstra
* Prim
* Kruskal
* Bellman-Ford (escolhido)

Cada algoritmo contém uma pasta com o código em `c++` e um arquivo `makefile` auxiliando na compilação.

As entradas criadas estão presentes na pasta `/Bellman-Ford/entradas`.

## Comandos

Os algoritmos implementados utilizam os seguintes argumentos:

```
-h : mostra o help
-o <arquivo> : redireciona a saida para o ‘‘arquivo’’
-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada
-s : mostra a solução
-i : vértice inicial (com exceção do algoritmo de Kruskal)
```

Cada algoritmo contém uma pasta com o código em `c++` e um arquivo `makefile` para compilação.

As entradas criadas estão presentes na pasta `/Bellman-Ford/Entradas`.


## Autores

- [@LukeHer0](https://www.github.com/LukeHer0) - Lucas Heron Santos Anchieta
- [@ruantmelo](https://www.github.com/ruantmelo) - Ruan Tenório de Melo


## Executando localmente

Clone o repositório

```bash
  git clone https://github.com/LukeHer0/teoria-dos-grafos.git
```

Acesse a pasta do projeto

```bash
  cd teoria-dos-grafos
```

Compile todos os scripts

```bash
  make all
```

Cada pasta terá agora os algoritmos compilados que podem ser utilizados
