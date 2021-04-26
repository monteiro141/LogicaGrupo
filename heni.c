#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct IMPLICA
{
    char expressao[1000];
    char negativos[100];
    char positivos[100];
    int verificado;
}IMPLICA;

/*ASCII -> A to Z: 65 a 90
        -> a to z: 97 a 122*/
/*
TOP = + 
BOT = - 
*/

/**
 * Esta função vai pegar na expressão inicial e dividila em varias estruturas do tipo IMPLICA
 * @param expressao Expressão inicial que é passada do stdin
 * @param A[][300] Estrutura para o qual se vai aplicar a expressão e dividir em varias sub expressões mais pequenas ( ... ) 
*/
void separarExpressaoGrande(char * expressao, IMPLICA A[][300],int * numeroExp)
{
    //printf("Entrou no for\n");~
    for(int i = 0;i < strlen(expressao);i++)
    {
        if(expressao[i] == '(')
        {
            (*numeroExp)++;
        }else
        {
            strncat((*A)[(*numeroExp)-1].expressao,&expressao[i],1);
        }
    }
}
/**
 * Esta função vai devolver um tipo IMPLICA com os varios literais negativos e positivos já divididos
 * @param expressao Expressão a avaliar, pelo qual a estrutura IMPLICA se vai basear de forma a construir os literais positivos e negativos
 * @return Estrutura IMPLICA já avaliada nos literais
*/
IMPLICA separarExpressaoInicial(char * expressao)
{
    int i,u;
    IMPLICA A;
    strcpy(A.negativos,"");
    strcpy(A.positivos,"");
    bool temNegativo=false;
    bool temPositivo=false;
    for(i = 0;i < strlen(expressao);i++)
    {
        if(expressao[i] == '~')
        {
            for(u=0;u < strlen(A.negativos);u++)
            {  
                if(A.negativos[u]==expressao[i+1])
                    temNegativo=true;
            }
            if(temNegativo == false)
            {
                //A.negativos += expressao[i+1];
                strncat(A.negativos,&expressao[i+1],1);
            }
                
            i++;
            temNegativo=false;
            continue;
        }else if((expressao[i]>= 65 && expressao[i] <=90) || (expressao[i]>= 97 && expressao[i] <=122))
        {
            for(u=0;u < strlen(A.positivos);u++)
            {
                if(A.positivos[u]==expressao[i])
                    temPositivo=true;
            }
            if(temPositivo==false)
            {
                //A.positivos += expressao[i];
                strncat(A.positivos,&expressao[i],1);
            }
               temPositivo=false; 
        }
    }
    return A;
}
/**
 * Função que apenas conta se a expressão tem mais do que um literal positivo
 * @param expressao Expressão a analisar
 * @return -1 se tem dois ou mais literais e 1 se tem o contrario
*/
int contarLiteralPositivo(char * expressao)
{
    if(strlen(expressao) >=2)
        return -1;
    return 1;
}

/**
 * Função que vai adicionar ao Conjunto dos literais comparados os literais positivos que passaram a verificação
 * @param grupo Conjunto inicial com o top ( + )
 * @param positivos Conjunto de literais positivos a serem adicionados
*/
void adicionarAoGrupo(char  grupo[][300], char * positivos)// +,Q,P     P       Q
{
    int i,u;
    bool existe=false;
    for(i=0;i<strlen(positivos);i++)
    {
        for(u=0;u<strlen(*grupo);u++)
        {
            if((*grupo)[u] == positivos[i])
                existe=true;
        }
        if(existe==false)
        {
            strncat((*grupo),&positivos[i],1);
            existe=false;
        }
    }
}
/**
 * Função que vai adicionar ao Conjunto dos literais, caso passem a verificação dos literais negativos, então, vai adicionar os positivos ao Conjunto
 * @param grupo Conjunto do top e outros literais que foram adicionados
 * @param negativos Conjunto de literais da expressão negativos
 * @param positivos Conjunto de literais da expressão positivos
 * @return -1 se não foi adicionado nenhum literal ao Conjunto e 1 se foi possivel adicionar algum literal ao Conjunto
*/
int compararGrupo(char  grupo[][300],char * negativos,char * positivos)//  +,Q,P     P Q R -> A
{
    bool existe=false;
    int i,u;
    for(i=0;i<strlen(negativos);i++)
    {
        for(u=0;u<strlen(*grupo);u++)
        {
            if((*grupo)[u] == negativos[i])
                existe=true;
        }
        if(existe==true)
        {
            existe=false;
            continue;
        }else
        {
            return -1;
        }
    }
    adicionarAoGrupo(grupo,positivos);
    return 1;
}

/**
 * Função que verifica o Conjunto dos literais, caso haja o mesmo numero de literais aos negativos então a função pode ter um bottom e sair UNSAT
 * @param grupo Conjuto dos literais que ja sofreram modificação
 * @param negativos Conjunto de negativos a serem comparados
 * @return -1 se nao for possivel adicionar o bottom e 1 se for possivel por o bottom 
*/

int verBottom(char  grupo[][300],char * negativos)// +,p,q ... q p  -> -
{
    bool existe=false;
    int i,u;
    for(i=0;i<strlen(negativos);i++)
    {
        existe=false;
        for(u=0;u<strlen(*grupo);u++)
        {
            if((*grupo)[u] == negativos[i])
            {
                
                existe=true;
            }
        }
        if(!existe)
        {
            return -1;
        }
    }
    return 1;
}

/**
 * Função que verifica se a expressão é sat ou unsat
 * @param A Array de expressões a serem avaliadas
 * @param grupo Conjunto inicial dos literais, começa sempre com o top ( + )
 * @param numeroExpressoes Numero das expressoes que foram separadas para as estruturas do tipo IMPLICA
 * @param temBot temBot é usado como variavel de controlo no main para imprimir unsat ou sat
*/
void satOrUnsat(IMPLICA * A, char  grupo[][300],int numeroExpressoes,bool * temBot) //grupo = "+"
{
    int i;
    for(i=0;i<numeroExpressoes;i++)
    {
        if(A[i].verificado == 0)
        {
            if(strlen(A[i].negativos)==0)
            {
                adicionarAoGrupo(grupo,A[i].positivos);
                A[i].verificado=1;
                i=-1;
            }else if(strlen(A[i].positivos)==0)
            {
                    if(verBottom(grupo,A[i].negativos)==1)//1 -> pode adicionar bottom, -1-> nao adicionou
                    {
                        (*temBot)=true;
                        return;
                    }
            }else
            {
                if(compararGrupo(grupo,A[i].negativos,A[i].positivos) == 1)
                {
                    A[i].verificado=1;
                    i=-1;
                }else
                {
                    continue;
                }
            }
        }else
        {
            continue;
        }
    }
}

int main(void)
{
    //Numero de expressões pelo qual vai ser usado para controlar noutras funções
    int numeroExp=0,i; 
    //Buffer para o qual se vai passar a expressão inicial passada pelo stdin
    char buffer[60000];
    //Buffer do conjunto de literais
    char grupo[300];
    //Arrays de sub expressões divididas
    //IMPLICA Arr[300];
    //IMPLICA ArrFinal[300];
    IMPLICA Decoy; //Variavel apenas usada para "limpar" os arrays
    strcpy(Decoy.expressao,"");
    strcpy(Decoy.negativos,"");
    strcpy(Decoy.positivos,"");
    Decoy.verificado=0;
    //variaveis de controlo para printar NA,SAT ou UNSAT
    bool NA=false,temBot=false;
    //ler expressão a expressão
    while(fgets(buffer,60000,stdin))
    {
        /*for(i=0;i < 300;i++)
        {
            Arr[i] = Decoy;
            ArrFinal[i] = Decoy;
        }*/
        IMPLICA Arr[300]={};
        IMPLICA ArrFinal[300]={};
        NA=false;
        temBot=false;
        strcpy(grupo,"+");
        numeroExp=0;
        separarExpressaoGrande(buffer,&Arr,&numeroExp);
        for(i = 0;i < numeroExp;i++)
        {
            ArrFinal[i] = separarExpressaoInicial(Arr[i].expressao);
            ArrFinal[i].verificado=0;
            if(contarLiteralPositivo(ArrFinal[i].positivos)==-1)
            {
                NA=true;
            }
                
        }
        if(NA)
            printf("NA\n");
        else
        {
            satOrUnsat(ArrFinal,&grupo,numeroExp,&temBot);
            if(temBot==false)
            {
                printf("SAT\n");
            }else
                printf("UNSAT\n");
        }
    }
    
    return 0;
}