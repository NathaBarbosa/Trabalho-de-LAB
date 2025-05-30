
# Enunciado: Fila de Prioridade com Repriorização Dinâmica

## Objetivo
Projetar e implementar uma fila de prioridade concorrente que permita não apenas a inserção e remoção de itens com prioridade, mas também a **repriorização de um item já presente na fila**, de forma segura e eficiente.

## Descrição
Você deve desenvolver uma estrutura de dados que suporte as seguintes operações concorrentes:

- `inserir(item, prioridade)`
- `remover()`
- `repriorizar(item, nova_prioridade)`

A operação de **repriorização** deve localizar o item na estrutura, atualizar seu valor de prioridade e reorganizar a estrutura conforme necessário.

## Tipo de Dado
Cada item representa um **pedido de leitura de sensor de temperatura** e contém:

- `id_dispositivo`
- `timestamp`
- `prioridade`

## Dinâmica de Atualização
Uma thread externa simula mudanças ambientais e chama `repriorizar` aleatoriamente.

## Instruções de Execução
1. Compile com `make`
2. Execute com `./repriorizacao`

## Relatório de Resultados
Documente os seguintes casos de teste:

### Caso 1: Alta concorrência de inserção
- **Variável:** número de produtores
- **Importância:** testar inserções simultâneas

### Caso 2: Alta frequência de repriorização
- **Variável:** frequência de chamadas
- **Importância:** testar integridade sob atualizações concorrentes

### Caso 3: Consumo intenso
- **Variável:** número de consumidores
- **Importância:** testar desempenho sob carga de remoção

Inclua no relatório:
- Tempo de execução
- Número de atualizações
- Observações

## Critérios de Avaliação
- Corretude funcional (40%)
- Sincronização segura (20%)
- Implementação da repriorização (20%)
- Relatório (20%)
