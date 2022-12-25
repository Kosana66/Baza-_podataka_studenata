#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BAZA_SIZE 10
#define MAX_SIZE 20

FILE *fp;
size_t num_of_bytes = 6;

char ime[BAZA_SIZE][MAX_SIZE];
char prezime[BAZA_SIZE][MAX_SIZE];
char brIndexa[BAZA_SIZE][MAX_SIZE];
int brBodova[BAZA_SIZE];

void pokupiStudenta(int pos)
{
	printf("Unesite ime: \t");
	scanf("%s",ime[pos]);
	printf("\nUnesite prezime: \t");
	scanf("%s",prezime[pos]);
	printf("\nUnesite broj indeksa: \t");
	scanf("%s",brIndexa[pos]);
	printf("\nUnesite broj bodova: \t");
	scanf("%d",&brBodova[pos]);
	printf("\n");
}

int unos(int *pos)
{
		fp = fopen ("/dev/baza", "a");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/baza \n");
			return -1;
		}
		
		pokupiStudenta(*pos);
		fprintf(fp,"%s,%s,%s=%d\n", ime[*pos], prezime[*pos], brIndexa[*pos], brBodova[*pos]);
		printf("ime: %s", ime[*pos]);
			printf("prezime: %s",prezime[*pos]);
	
		(*pos)++;

		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/switch");
			return -1;
		}
		printf("Uspesan unos!\n");
}		

int citanje(int *pos)
{
		fp = fopen ("/dev/baza", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/baza \n");
			return -1;
		}
		
		for(int i=0; i<(*pos); i++)
		{
			fscanf(fp,"%s,%s,%s=%d\n",ime[i], prezime[i], brIndexa[i], &brBodova[i]);
			printf("%s %s %s - %d\n", brIndexa[i], ime[i], prezime[i], brBodova[i]);
		}

		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/switch");
			return -1;
		}
		printf("Uspesno citanje!\n");
}


int main ()
{
	int pos=0;
	bool flag=true;
	while(flag)
	{	
		int opcija=0;
		do
		{
			printf("IZABERITE OPCIJU: \n");
			printf("1. Unos novog studenta \n");
			printf("2. Izmena broja bodova studenta \n");
			printf("3. Brisanje studenta \n");
			printf("4. Citanje liste \n");
			printf("5. Izlaz \n ");	
			scanf("%d",&opcija);
			if(opcija<0 || opcija>5)
				printf("Ne postoji opcija pod tim brojem! \n");
		}while(opcija<0 || opcija>5);

		switch(opcija)
		{
			case 1: unos(&pos); 
			break;

			case 4: citanje(&pos); 
			break;	
			
			case 5: flag=false;
			break;	

			default:
			break;
		}
	}
}

