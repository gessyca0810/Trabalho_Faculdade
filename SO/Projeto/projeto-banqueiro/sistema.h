#ifndef SISTEMA_H_INCLUDED   /* Include guard */
#define SISTEMA_H_INCLUDED

void Recdisp();
void Usodisp();
void Faldisp();
void reqlibdisp(int vec[]);
int SeMaiorQueNec(int pID,int requisicao[]);
int SuficienteParaAlocar(int requisicao[]);
int modoseguro();
int semreclib(int pID,int liberacao[]);


#endif // SISTEMA_H_INCLUDED