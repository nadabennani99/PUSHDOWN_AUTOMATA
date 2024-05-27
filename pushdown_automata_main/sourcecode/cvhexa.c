#include "cvhexa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 1000



int height(FILE* fichier){
    int car, Line;
    Line = 0;
    while (( car = getc(fichier)) != EOF){
         if (car == '\n'){
              ++Line;
          }
    }
    return Line+1;
}

/*The code for the two following functions was inspired from https://codeforwin.org/2018/02/c-program-remove-empty-lines-from-file.html
*/


int isLineEmpty(const char *str)
{
    char c;
    do
    {
        c = *(str++);
        if(c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '\0')
            return 0;

    } while (c != '\0');

    return 1;
}

void removeEmptyLines(FILE *fread, FILE *fwrite)
{
    char temp[SIZE];
    while ((fgets(temp, SIZE, fread)) != NULL)
    {
        if(!isLineEmpty(temp))
          {//if line is not empty then we write it on the new file fwrite
            fputs(temp, fwrite);
          }

        }
}

//Inspired from the code proposed in GeeksforGeeks
void InsertendNode(Node** head,int data,char* name)
{
Node* newNode=malloc(sizeof(Node));
Node* temp=*head;
strcpy(newNode->name,name);
newNode->address=data;
newNode->next=NULL;
if (*head==NULL)
{
*head=newNode;
return;

}
while (temp->next!=NULL)
{
temp=temp->next;

}

temp->next=newNode;
return;
}

int verifyinstruction(char* s)
{
int i=0;
if (!(strcmp(s,"push")))
{
i=1;
}
else if (!(strcmp(s,"pop")))
{
i=1;
}
else if (!(strcmp(s,"iPop")))
{
i=1;
}
else if (!(strcmp(s,"iPush")))
{
i=1;
}
else if (!(strcmp(s,"push#")))
{
i=1;
}
else if (!(strcmp(s,"call")))
{
i=1;
}
else if (!(strcmp(s,"ret")))
{
i=1;
}
else if (!(strcmp(s,"jmp")))
{
i=1;
}

else if (!(strcmp(s,"jpc")))
{
i=1;
}
else if (!(strcmp(s,"write")))
{
i=1;
}

else if (!(strcmp(s,"read")))
{
i=1;
}
else if (!(strcmp(s,"rnd")))
{
i=1;
}
else if (!(strcmp(s,"dup")))
{
i=1;
}
else if (!(strcmp(s,"op")))
{
i=1;
}
else if (!(strcmp(s,"halt")))
{
i=1;
}
return i;
}

int hexavalue(char* s)
{
	int i=-1;
if (!(strcmp(s,"push")))
{
i=1;
return i;
}
else if (!(strcmp(s,"pop")))
{
i=0;
return i;
}
else if (!(strcmp(s,"iPop")))
{
i=2;
return i;
}
else if (!(strcmp(s,"iPush")))
{
i=3;
return i;
}
else if (!(strcmp(s,"push#")))
{
i=4;
return i;
}
else if (!(strcmp(s,"call")))
{
i=5;
return i;
}
else if (!(strcmp(s,"ret")))
{
i=6;
return i;
}
else if (!(strcmp(s,"jmp")))
{
i=7;
return i;
}

else if (!(strcmp(s,"jpc")))
{
i=8;
return i;
}
else if (!(strcmp(s,"write")))
{
i=9;
return i;
}

else if (!(strcmp(s,"read")))
{
i=10;
return i;
}
else if (!(strcmp(s,"rnd")))
{
i=11;
return i;
}
else if (!(strcmp(s,"dup")))
{
i=12;
return i;
}
else if (!(strcmp(s,"op")))
{
i=13;
return i;
}
else if (!(strcmp(s,"halt")))
{
i=99;
return i;
}
return -1;
}

int hasdata(char* s)
{
int i=0;
if (!(strcmp(s,"push")))
{
i=1;
}
else if (!(strcmp(s,"pop")))
{
i=1;
}
else if (!(strcmp(s,"push#")))
{
i=1;
}
else if (!(strcmp(s,"call")))
{
i=2;
}

else if (!(strcmp(s,"jmp")))
{
i=2;
}

else if (!(strcmp(s,"jpc")))
{
i=2;
}
else if (!(strcmp(s,"write")))
{
i=1;
}

else if (!(strcmp(s,"read")))
{
i=1;
}
else if (!(strcmp(s,"rnd")))
{
i=1;
}
else if (!(strcmp(s,"op")))
{
i=1;
}

return i;
}

int findetiquettevalue (char* s,Node* head)
{
	Node* temp=head;
	while (temp!=NULL)
	{
		if (!(strcmp(s,temp->name)))
		{
			return temp->address;

		}
		else
		{
		temp=temp->next;
		}


	}
	return -1;
}

Node* DownWeGo(FILE* f,int fileheight)
{
char buf[50];
Node* list=NULL;
char* s;
int nblines=0;
while (nblines!=fileheight&& f!=NULL)
{
fgets(buf,50,f);
s=strtok(buf," ");
if (!verifyinstruction(s))
{
s[strlen(s)-1]='\0';
InsertendNode(&list,nblines,s);
}
nblines++;
}
rewind(f);
return list;
}

int checkSyntax(FILE* f)
{
	rewind(f);
	char buf[200];
	char* s;
	int i=1;
	int cpt=0;
	while (fgets(buf,200,f)!=NULL)
	{	s=strtok(buf," \t\n\r");
			if (verifyinstruction(s)) //instruction
			{

				if (hasdata(s))
				{
				s=strtok(NULL," \t\n\r");
				if (s==NULL)
				{
				printf("Syntax error. Please input another program\n");
				printf("%s in first if",s);
				i=0;
				break;}
				}
				continue;
			}
			else if (s[strlen(s)-1]==':')
			{
				s=strtok(NULL," \t\n\r");
				if (!verifyinstruction(s))
				{
				printf("Syntax error. Please input another program\n");
				printf("%s in 2 if",s);
				i=0;
				break;
				}
				else
				{
				if (hasdata(s))
				{
				s=strtok(NULL," \t\n\r");
				if (s==NULL)
				{
				printf("Syntax error. Please input another program\n");
				printf("%s in 3 if",s);
				i=0;
				break;}
				}
				}continue;

			}
			else
			{
				printf("%d\n",strcmp(s,"halt"));
				printf("Syntax error. Pease input another program\n");

				i=0;
				break;

			}
		cpt++;
		printf("cpt:%d\n",cpt);
		}
    return i;

}

void translatetohexa(FILE* f)
{
	FILE* hexafile=fopen("hexafile.txt","w");
	char s[100];
	int nblines=1;
	int fileheight=height(f);
  rewind(f);
	Node* list=DownWeGo(f,fileheight);
	int i=0;
	int j=0;
	int adr=0;
	while (nblines!=fileheight+1 && f!=NULL)
	{
	fscanf(f,"%s ",s);
	if (verifyinstruction(s))
	{	j=hexavalue(s);
		fprintf(hexafile,"%.2x ",j);

		if (hasdata(s))
		{
			if (hasdata(s)==2)
			{
			fscanf(f,"%s",s);
			adr=findetiquettevalue(s,list)-nblines;
        if (adr<0)
        {
			       fprintf(hexafile,"%.04hx\n",(short)adr);
        }else{
              fprintf(hexafile,"%.4x\n",adr);
        }
			}
			else
			{
			fscanf(f,"%d\n",&i);
        if (i<0)
        {
           fprintf(hexafile,"%.04hx\n",(short)i);
         }else{
            fprintf(hexafile,"%.4x\n",i);
        }
			}

			nblines++;
			continue;
		}
		else
		{
			i=0;
			fprintf(hexafile,"%.4x\n",i);
		}

	}
	else if (s[strlen(s)-1]==':')
	{	//Skipping the etiquette
		//Going through the rest of the line

		fscanf(f,"%s ",s);
		j=hexavalue(s);
		fprintf(hexafile,"%.2x ",hexavalue(s));

		if (hasdata(s))
		{
			fscanf(f,"%d\n",&i);
      if (hasdata(s)==2)
			{
			fscanf(f,"%s",s);
			adr=findetiquettevalue(s,list)-nblines;
        if (adr<0)
        {
			       fprintf(hexafile,"%.04hx\n",(short)adr);
        }else{
              fprintf(hexafile,"%.4x\n",adr);
        }
			}
			else
			{
			fscanf(f,"%d\n",&i);
        if (i<0)
        {
           fprintf(hexafile,"%.04hx\n",(short)i);
         }else{
            fprintf(hexafile,"%.4x\n",i);
        }
			}
			nblines++;
			continue;
		}
		else
		{
			i=0;
			fprintf(hexafile,"%.4x\n",i);
		}
	}
	else
	{
		printf("Syntax Error. Please review your code\n");
		fprintf(hexafile,"The process has been stopped because of a syntax error\n");
		break;

	}
	fscanf(f,"\n");
	nblines++;
	}
	fclose(hexafile);
  Node* temp;
  while (list!=NULL)
  {
    temp=list;
    list=list->next;
    free(temp);
  }
  return;
}
