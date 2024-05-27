#include "simulation.h"
#include "cvhexa.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int pop (int x)
{
if (x<0|| x>3999)
{
	printf("Process stopped. The address is beyond memory range in pop.\n");
	return 0;
}
if (SP<=0)
{
printf("SP cannot be decremented. Process killed\n");
return 0;
}
tab[x]=tab[SP-1];
SP--;
return 1;
}

int push (int x)
{
if (x<0|| x>3999)
{
	printf("Process stopped. The address is beyond memory range in push.\n");
	return 0;
}
tab[SP]=tab[x];
SP++;
return 1;
}

int iPop()
{
	if (SP<=1)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
	tab[tab[SP-1]]=tab[SP-2];
	SP=SP-2;
	return 1;
}

int iPush()
{
	if (SP<=0)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
	else if (tab[SP-1]<0 || tab[SP-1]>3999)
	{
	printf("Cannot access this address of memory via iPush. Process stopped\n");
	}
	tab[SP-1]=tab[tab[SP-1]];
	SP++;
  return 1;
}

int pushi(int i)
{
	tab[SP]=i;
	SP++;
	return 1;
}

int call(int adr,int h)
{

	if (PC+adr<0||PC+adr>h)
	{
		printf("Adress beyond file range. The process is thus stopped\n");
		return 0;
	}
	tab[SP]=PC;
	PC=PC+adr;
	SP++;
	return 1;
}

int retu()
{
	if (SP<0||SP>3999)
	{
		printf("No address value in SP. Process stopped\n");
		return 0;
	}
	SP--;
	PC=tab[SP];
	return 1;
}
// check le cas de la boucle infinie
int jmp(int adr,int h){
if(adr==-1)
{
	printf("Infinite loop. Process is then stopped\n");
	return 0;
}
else if (PC+adr<0||PC+adr>h)
	{
		printf("Adress beyond file range. The process is thus stopped\n");
		return 0;
	}
else
{
	PC=PC+adr;
}
return 1;
}

int jpc(int adr,int h)
{

if(adr==-1)
{
	printf("Infinite loop. Process is then stopped\n");
	return 0;
}
else if (PC+adr<0||PC+adr>h)
	{
		printf("Adress beyond file range. The process is thus stopped\n");
		printf("adr value: %d\n",adr);
		printf("PC value: %d\n",PC);
		return 0;
	}
SP--;
int var=tab[SP];
if(var!=0)
{
	PC=PC+adr;
}
return 1;
}

int write(int x )
{
	if (x<0|| x>3999)
{
	printf("Process stopped. The address is beyond memory range in write.\n");
	return 0;
}
	printf("La variable a l'adresse %d correspond a : %d\n",x ,tab[x]);
	return 1;
}

int read(int x)
{
	if (x<0|| x>3999)
{
	printf("Process stopped. The address is beyond memory range in read.\n");
	return 0;
}
	int var;
	printf("Vous devez rentrer une valeur qui sera mise dans la variable a l'adresse %d : \n",x);
	scanf("%d",&var);
	tab[x]=var;
  return 1;
}

int rnd(int x)
{
	srand(time(NULL));
	tab[SP]=rand() % x;
	SP++;
	return 1;
}

int dup(){
	tab[SP]=tab[SP-1];
	SP++;
  return 1;
}

int op(int i){
if (SP<=0)
{
	printf("SP is not full enough. Process stopped\n");
	return 0;
}
int ret=1;
	switch (i)
	{
		case 0:
		//test egalite
		SP-=1;
		if (SP<=0)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
		if (tab[SP-1]==tab[SP])
		{
			tab[SP-1]=1;
		}
		else
		{
			tab[SP-1]=0;
		}
		break;

		case 1:
		SP-=1;
		if (SP<=0)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
		if(tab[SP-1]!=tab[SP]){
			tab[SP-1]=1;
		}else{
			tab[SP-1]=0;
		}
		break;

		case 2:
		//test superieur
		SP-=1;
		if (SP<=0)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
		if(tab[SP-1]>tab[SP]){
			tab[SP-1]=1;
		}else{
			tab[SP-1]=0;
		}
		break;

		case 3:
		if (SP<=0)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
		SP--;
		if(tab[SP-1]>=tab[SP]){
			tab[SP-1]=1;
		}else{
			tab[SP-1]=0;
		}
		break;

		case 4:
		SP-=1;
		if (SP<=0)
	{
	printf("SP is not full enough. Process stopped\n");
	return 0;
	}
		if(tab[SP-1]<tab[SP]){
			tab[SP-1]=1;
		}else{
			tab[SP-1]=0;
		}
		break;

		case 5:
		//test inferieur ou egal
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		if(tab[SP-1]<=tab[SP])
		{
			tab[SP-1]=1;
		}else{
			tab[SP-1]=0;
		}
		break;

		case 6:
		//et logique bit a bit
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=(tab[SP-1]&tab[SP]);

		break;

		case 7:
		//ou logique bit a bit
		SP--;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=(tab[SP-1]|tab[SP]);
		break;

		case 8:
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=(tab[SP-1]^tab[SP]);

		break;

		case 9:
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=~tab[SP-1];

		break;

		case 10:
		if (SP<=0)
		{
	printf("SP is not full enough. Process stopped\n");
	return 0;
		}
		tab[SP-1] = -1 * tab[SP-1];
		break;

		case 11:
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=(tab[SP-1] + tab[SP]);
		break;

		case 12:
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=(tab[SP-1] -tab[SP]);
		break;

		case 13:
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=tab[SP-1] * tab[SP];
		break;

		case 14:
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=tab[SP-1] / tab[SP];

		break;

		case 15:
		SP-=1;
		if (SP<=0)
		{
		printf("SP is not full enough. Process stopped\n");
		return 0;
		}
		tab[SP-1]=tab[SP-1] % tab[SP];


		break;
		default:
			ret=0;

			}
			if (!ret)
			{
			printf("Instruction number beyond range\n");
			}
			return ret;
}

int halt()
{
	printf("End of simulation\n");
	return 1;
}


void filltab(int datatab[],int instructiontab[],FILE* f,int h)
{
rewind(f);
	for (int i=0;i<h;i++)
	{
	fscanf(f,"%x ",&instructiontab[i]);
	fscanf(f,"%x\n",&datatab[i]);
	if (datatab[i]>32768)
	{
	datatab[i]=datatab[i]-65536;
	}

	}
}
int execute(int instruction, int data, int* tab,int h)
{
int ret=0;
	switch (instruction)
	{
		case 0:
			ret=pop(data);
			break;
		case 1:
			ret=push(data);
			break;
		case 2:
			ret=iPop();
			break;
		case 3:
			ret=iPush();
			break;
		case 4:
			ret=pushi(data);
			break;
		case 5:
			ret=call(data,h);
			break;
		case 6:
			ret=retu();
			break;
		case 7:
			ret=jmp(data,h);
			break;
		case 8:
			ret=jpc(data,h);
			break;
		case 9:
			ret=write(data);
			break;
		case 10:
			ret=read(data);
			break;
		case 11:
			ret=rnd(data);
			break;
		case 12:
			ret=dup();
			break;
		case 13:
			ret=op(data);
			break;
		case 99:
			ret=halt();
			break;
		default:
			ret=0;
	}
	return ret;
}
