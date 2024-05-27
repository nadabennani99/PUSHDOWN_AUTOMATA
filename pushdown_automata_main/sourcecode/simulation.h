#ifndef _SIMULATION_
#define _SIMULATION_
#include <stdlib.h>
#include <stdio.h>


int pop (int x);
int push (int x);
int iPop();
int iPush();
int pushi(int i);
int call(int adr,int h);
int retu();
int jmp(int adr,int h);
int jpc(int adr,int h);
int write(int x );
int read(int x);
int rnd(int x);
int dup();
int op(int i);
int halt();
void filltab(int datatab[],int instructiontab[],FILE* f,int h);
int execute(int instruction, int data, int* tab,int h);



#endif
