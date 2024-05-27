
#ifndef _CVHEXA_
#define _CVHEXA_
#include <stdlib.h>
#include <stdio.h>



typedef struct Node{
int address;
char name[20];
struct Node* next;
struct Node* prev;}Node;


int height(FILE* fichier);
int isLineEmpty(const char *str);
void removeEmptyLines(FILE *fread, FILE *fwrite);
void InsertendNode(Node** head,int data,char* name);
int verifyinstruction(char* s);
int hexavalue(char* s);
int hasdata(char* s);
int findetiquettevalue (char* s,Node* head);
Node* DownWeGo(FILE* f,int fileheight);
int checkSyntax(FILE* f);
void translatetohexa(FILE* f);

#endif
