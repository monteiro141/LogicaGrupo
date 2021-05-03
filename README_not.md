# LogicaGrupo
Este trabalho foi realizado no âmbito da cadeira de Lógica Computacional da Universidade da Beira Interior.

Autores : 
- Cristiano Santos, nº43464
- Alexandre Monteiro, nº44149

## Enunciado do trabalho desenvolvido

O objectivo deste trabalho é implementar o algoritmo de Horn. Dada uma fórmula, o
programa deverá verificar se é fórmula de Horn e:
- Se é fórmula de Horn, deverá determinar e indicar se a fórmula é possível ou contraditória.
- Se não é fórmula de Horn, deverá indicar que o algoritmo não é aplicável.
Na secção seguinte são apresentados os detalhes relativos ao input que o programa terá de processar e ao output esperado

### INPUT

O input consistirá em fórmulas na forma normal conjuntiva, uma por linha, onde cada
conectivo é representado da seguinte forma:
- ¬ é representado por ~
- ∧ é representado por &
- ∨ é representado por |

São usados parêntises para delimitar as disjunções e as fórmulas terão no máximo 100 cláusulas.
Os literais, positivos ou negativos, podem estar repetidos numa disjunção. Por exemplo, a
fórmula (¬p ∨ Q ∨ Q) ∧ (¬t) deve ser considerada fórmula de Horn.

O input vai ser introduzido através do standard input. Exemplo de input:
(~p | Q | ~r) & (~t) & (P) & (~T | x | Z) & (F)
(~p | R ) & (~x) & (p) & (~p | x | ~R | x)
(~p | a ) & (p) & (~p | ~R | x) & (~W | P | ~h) & (F) & (~f |~q | e) & (~t |
~k | ~l)

### OUTPUT

O programa deverá produzir como output:
- SAT, se a fórmula é possível
- UNSAT, se a fórmula é contraditória
- NA, se a fórmula não é fórmula de Horn

Cada output tem de ser seguido do caracter de newline (‘\n’), caso contrário, mesmo que
a resposta esteja correcta, será rejeitada.

Output esperado para o exemplo de input anterior:
NA
UNSAT
SAT

### Linguagem de Programação usada e instrução de execução
O programa foi desenvolvido em C(standard C99).
Para compilar use o seguinte comando, (onde main.c é substituído pelo nome do seu ficheiro):
- gcc -o main main.c -Wall -std=c99 -lm