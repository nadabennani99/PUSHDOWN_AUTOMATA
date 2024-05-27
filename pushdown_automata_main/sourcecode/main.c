#include "global.h"
#include "cvhexa.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc , char* argv[])
{

FILE* f=fopen(argv[1],"r");
FILE* final=fopen("fichierfinal.txt","w");
removeEmptyLines(f,final);
fclose(final);
fclose(f);
final=fopen("fichierfinal.txt","r");
int j=checkSyntax(final);
if (!j)
{
  printf("Program has been stopped\n");
  return 0;
}
else
{
rewind(final);
translatetohexa(final);
}
fclose(final);
FILE* fichier=fopen("hexafile.txt","r");
int h=height(fichier);
int instructiontab[h];
int datatab[h];
int ref=0;
filltab(datatab,instructiontab,fichier,h);
rewind(fichier);
PC++;
//convertir pour chaque taleau les nombres hexa en int
do
{
	ref=execute(instructiontab[PC-1],datatab[PC-1],tab,h);
	PC++;
	if (!ref)
	{
	printf("The simulation has been stopped because of an error in the code\n");
	printf("Value of PC in the error %d\n",PC-1);
	break;
	}


}while (instructiontab[PC-1]!=99);
printf("Simulation is over ! Thank you for using our pushdowmn automata !\n");
fclose(fichier);
return 0;

}
