#ifndef INFIJAAPOSTFIJA_H
#define INFIJAAPOSTFIJA_H

#define max 100

struct nodo
{
    char oper;
   struct nodo *sgte;
};

typedef struct nodo Nodo;
typedef Nodo *Ptrpila; //definimos estructura tipo pila


void inAPost(char *, char *);
void push(Ptrpila *,char);
char pop(Ptrpila *);
int  InfijaMayorAPila(char, char);
int  correcto(char *);
void destruir(Ptrpila *);
float resulPostfija(char *);

#endif
