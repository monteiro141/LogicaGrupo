### Input
Inicialmente trabalhamos o input singularmente, onde cada expressão é trabalhada antes da entrada da próxima.
### Expressão para sub-expressões
Passo a passo, ao receber a expressão do input vamos separar em cada sub-expressão (por parêntesis). Pegando nessa sub-expressão, vamos calcular os literais negativos e positivos para mais tarde serem trabalhados em "grupo".
### NA
A primeira verificação é o NA, essa verificação consistem em contar quantos literais positivos existem numa sub-expressão, caso seja maior ou igual a dois, então a expressão inicial é NA sem necessitar de verificar UNSAT ou SAT.
### UNSAT ou SAT
A próxima verificação, caso não seja NA, consiste em pegar cada sub-expressão e "tentar" adicionar os literais positivos das sub-expressões a um "grupo" com um TOP ( + ) inicial.
### UNSAT
Aplicando o algoritmo de horn e adicionando os literais positivos, chega-se a uma conclusão, caso por ventura se consiga adicionar um BOT ( - ) ao nosso "grupo", então a expressão é UNSAT e um boolean "temBot" é true e o output final é UNSAT.
### SAT
Caso o algoritmo de horn chegue ao final e todas as sub-expressões estejam verificadas, então o output final é SAT.
