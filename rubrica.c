#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 25
#define NAMEF "rubrica.ini"
#define TEMPN "kajaymen94dwh.bin"
typedef struct R{
  char name[N];
  char surname[N];
  char number[N];
}R;

void checkF(int *count)
{
	FILE *FF;
	int i=0,c;
	FF=fopen(NAMEF,"r");
	if(!FF){perror("Error "); return;}
	while(!feof(FF))
	{
		c=fgetc(FF);
		if(c=='\n')
		i++;
	}
	*count=i;
	fclose(FF);
}
void nump(int* np)
{
  printf("Numero di Contatti da inserire: ");
  scanf("%d",np);
}
R *createlist(int np)
{
    int i,number;
    R *list;
    char buff[N];
    list=(R*)malloc(np*sizeof(R));
    for(i=0;i<np;i++)
    {
      printf("\ncontatto N.%d\n",(i+1));
      printf("Nome: ");
      scanf("%s",list[i].name);
      
      printf("Cognome: ");
      scanf("%s",list[i].surname);
     
      printf("Numero: ");
      scanf("%s",list[i].number);
     
    }
    return list;
}

void deleteC(R list[],int np)
{
	FILE *FF,*TEMPF;
	int i,c,d;
	FF=fopen(NAMEF,"r");
	if(!FF){perror("Error "); return;}
	TEMPF=fopen(TEMPN,"w");
	if(!TEMPF){perror("Error "); return;}
	printf("Inserire Il Numero di contatto da eliminare: ");
	scanf("%d",&c);
	
	for(i=0;i<np;i++)
	{
		if(i==(c-1))
		{
			continue;
		}
		fprintf(TEMPF,"%s %s %s\n",list[i].name,list[i].surname,list[i].number);
	}
	fclose(FF);
	fclose(TEMPF);
	remove(NAMEF);
	d=rename(TEMPN,NAMEF);
	if(d==0){printf("\nIl conatto e stato eliminato con successo.");}
	
}
void savefile(R list[],int np)
{
	FILE* FF;
	int i,c;
	FF=fopen(NAMEF,"a");
	if(!FF){perror("Error ."); return;	}
	for(i=0;i<np;i++)
	{
		fprintf(FF," %s %s %s\n",list[i].name,list[i].surname,list[i].number);
	}
	c=fclose(FF);
	if(c==0){printf("Contatto e stato salvato con successo"); return;	}
}

R *fileinvet(int count)
{
	FILE* FF;
	R *list;
	int i;
	FF=fopen(NAMEF,"r");
	if(!FF){perror("Error "); return;}
	list=malloc(count*sizeof(R));
	for(i=0;i<count;i++)
	{
		fscanf(FF," %s %s %s",list[i].name,list[i].surname,list[i].number);
	}
	fclose(FF);
	return list;
}
void viewrubrica(R megaR[],int count)
{
	int i;
	for(i=0;i<count;i++)
	{
      printf("\n\ncontatto N.%d",(i+1));
      printf("\nNome: %s",megaR[i].name);
      
      printf("\nCognome: %s",megaR[i].surname);
     
      printf("\nNumero: %s",megaR[i].number);
  	}
}
int main()
{
    int np,select=NULL,count;
    R *list,*megaR;
	
    while(1)
    {
    printf("\n******************************************************************");
    printf("\nRubrica Final By Aymen Naghmouchi");
    printf("\n******************************************************************");
    printf("\n(1)Per inserire un contatto\n(0)Per uscire\n(2)Per visualizzare la rubrica\n(3)Per eliminare un cntatto\n");
	printf("\nInserire uno dei seguenti numeri: ");
    scanf("%d",&select);
   
    switch(select)
    {
      case 0: system("shutdown -r -t 10");
      			printf("Vaffanculo");
	  		  exit(0);
              break;
      case 1: nump(&np);
              list=createlist(np);
              savefile(list,np);
              free(list);
              system("cls");
              break;
      case 2: checkF(&count);
	  		  megaR=fileinvet(count);
	  		  system("cls");
	  		  viewrubrica(megaR,count);
	  		  free(megaR);
              break;
      case 3: checkF(&count);
	  		  megaR=fileinvet(count);
	  		  deleteC(megaR,count);
	  		  free(megaR);
	  		  system("cls");
	  		  break;
    default: printf("\nError:inserire uno dei seguenti numeri indicati");
              break;

    }
  }
}
