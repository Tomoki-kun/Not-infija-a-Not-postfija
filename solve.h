#ifndef SOLVE_H
#define SOLVE_H

struct nodoPost
{
    float num;
    struct nodoPost *pSig;
};

typedef struct nodoPost NodoPost;
typedef NodoPost * pNodoPost; 

float resulPostfija(char *);
void ppush(pNodoPost *,float);
void ppop(pNodoPost *,float *,float *);
unsigned char esOperador(char *);
void pdestruir(pNodoPost *pila);

#endif
