
# Tabela Hash em C

Este é um código em C que implementa uma tabela hash utilizando listas encadeadas para tratar colisões. A tabela hash é usada para armazenar nomes em uma estrutura de dados eficiente para busca e inserção.

## Compilação e execução

Para compilar o código, certifique-se de ter um compilador C instalado em sua máquina. Em seguida, siga as etapas abaixo:

1. Salve o código em um arquivo com a extensão ".c", por exemplo, "tabela_hash.c".
2. Abra um terminal ou prompt de comando e navegue até o diretório onde o arquivo está localizado.
3. Execute o seguinte comando para compilar o código:

```
gcc tabela_hash.c -o tabela_hash
```

4. Após a compilação bem-sucedida, execute o programa com o seguinte comando:

```
./tabela_hash
```

## Funcionalidades

O programa oferece as seguintes funcionalidades:

1. Inserir nome: Permite inserir um nome na tabela hash.
2. Remover Nome: Permite remover um nome da tabela hash.
3. Buscar nome: Permite pesquisar um nome na tabela hash.
4. Imprimir listas: Exibe todos os nomes presentes na tabela hash, separados por lista.
5. Ordenar listas: Ordena os nomes em cada lista da tabela hash.
6. Exibir histograma: Mostra um histograma do número de elementos em cada lista da tabela hash.
7. Exportar Tamanho das tabelas para arquivo .csv: Exportação do tamanho de todas as listas para uma tabela .csv
8. Exibir tabela de contagem por letra do alfabeto: Exibe quantas nomes existem na tabela Hash por letra do alfabeto.
9. Sair: Encerra o programa.

## Arquivos de entrada

O programa lê os nomes a serem inseridos na tabela hash a partir de um arquivo chamado "nomes.txt". Certifique-se de que esse arquivo esteja presente no mesmo diretório do código-fonte. Cada nome deve estar em uma linha separada no arquivo.

## Arquivo de saída

O programa também gera um arquivo chamado "tamanhos_tabelas.csv" que contém o tamanho de cada lista da tabela hash. Esse arquivo é gerado ao final da execução do programa.

## Observações

- A tabela hash possui um tamanho fixo de 53.
- As colisões são tratadas utilizando listas encadeadas.
- O código utiliza a função de hash djb2 para calcular a posição de inserção na tabela.
- Os nomes inseridos na tabela não devem exceder 50 caracteres.

Esse é um exemplo simples de implementação de uma tabela hash em C. É possível aprimorar e expandir as funcionalidades de acordo com as necessidades específicas do seu projeto.
