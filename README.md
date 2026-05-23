# Árvore AVL em C

Implementação uma árvore AVL em C feita para estudo de algoritmos e estruturas de dados.

## Arquivos

- `avl.c` → implementação da árvore AVL com inserção, remoção e balanceamento.
- `avl_bfs.c` → implementação da AVL com percurso em largura (Breadth-First Search) usando fila encadeada.

## Funcionalidades

- Inserção balanceada
- Remoção balanceada
- Busca
- Percurso em ordem
- Percurso em largura (BFS)
- Rotações simples e duplas
- Atualização automática de alturas

## Conceitos utilizados

- Árvore Binária de Busca (BST)
- Balanceamento AVL
- Recursão
- Ponteiros em C
- Fila encadeada
- BFS (Breadth-First Search)
- Alocação dinâmica de memória

## Compilação

Para compilar a implementação principal:
```bash
gcc avl.c -o avl
```
Para compilar a implementação com percurso BFS:
```bash
gcc avl_bfs.c -o avlBFS
```

## Execução

Implementação principal:
```bash
./avl
```
Implementação com BFS:
```bash
./avlBFS
```

## Autor
Gabriel Ulhoa
