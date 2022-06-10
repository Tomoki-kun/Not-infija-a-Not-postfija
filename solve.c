#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solve.h"

float resulPostfija(char *postfija)
{
    int contOp = 0, contNum = 0;
    float ret = 0, num1, num2;
    char *chr;
    pNodoPost pila = NULL;

    chr = strtok(postfija," ");
    while(chr)
    {
        if(esOperador(chr))
        {
            contOp++;
            if(contOp==contNum)
            {
                pdestruir(&pila);
                printf("\n-->ERROR DE SINTAXIS\n\n");
                exit(-2);
            }
            ppop(&pila,&num1,&num2);
            if(strcmp(chr, "/") == 0)
            {
                if(num1==0)
                {
                    pdestruir(&pila);
                    printf("\tMATH ERROR! Division por cero\n\n\n");
                    exit((-1));
                }
                ret = num2 / num1;
            }
            else if(strcmp(chr, "+") == 0)
                ret = num1 + num2;
            else if(strcmp(chr, "-") == 0)
                ret = num2 - num1;
            else if(strcmp(chr, "*") == 0)
                ret = num1 * num2;
            ppush(&pila, ret);
        }
        else
        {
            ppush(&pila, atof(chr));
            contNum++;
        }
        chr = strtok(NULL," ");
    }
    pdestruir(&pila);
    return ret;
}

void ppush(pNodoPost *pila,float numero)
{
    pNodoPost nuevo = (pNodoPost) malloc(sizeof (NodoPost));

    if(nuevo)
    {
        nuevo->num = numero;
        nuevo->pSig = *pila;
        *pila = nuevo;
    }
    else
    {
        printf("ERROR! memoria insuficiente");
    }
}

void ppop(pNodoPost *pila,float * num1,float *num2)
{
    pNodoPost aux;

    *num1 = (*pila)->num;
    aux = *pila;
    *pila = (*pila)->pSig;
    free(aux);

    *num2 = (*pila)->num;
    aux = *pila;
    *pila = (*pila)->pSig;
    free(aux);
}

unsigned char esOperador(char *chr)
{
    int i = 0;
    int ret = 1;
    char *operadores[4] = {"+", "-", "*", "/"};

    do
    {
        ret = strcmp(chr, operadores[i]);
        i++;
    }while((i < 4) && ret != 0);
    return !ret;
}

void pdestruir(pNodoPost *pila)
{
    pNodoPost aux;
    aux = *pila;

    while(aux!=NULL)
    {
        *pila = (*pila)->pSig;
        free(aux);
        aux = *pila;
    }
}
