#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define BAZA_SIZE 10
#define MAX_SIZE 20

FILE *fp;
size_t num_of_bytes = 6;

char ime[BAZA_SIZE][MAX_SIZE];
char prezime[BAZA_SIZE][MAX_SIZE];
char brIndexa[BAZA_SIZE][MAX_SIZE];
int brBodova[BAZA_SIZE];

char tmp_ime[MAX_SIZE];
char tmp_prezime[MAX_SIZE];
char tmp_brIndexa[MAX_SIZE];
int tmp_brBodova;

int main ()
{
	int pos=0;
	bool flag=true;
	while(flag)
	{	
		int opcija=0;
		do
		{
			printf("\nIZABERITE OPCIJU: \n");
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
			case 1: 

				printf("Unesite ime: ");
				scanf("%s",ime[pos]);
				printf("\nUnesite prezime: ");
				scanf("%s",prezime[pos]);
				printf("\nUnesite broj indeksa: ");
				scanf("%s",brIndexa[pos]);
				printf("\nUnesite broj bodova: ");
				scanf("%d",&brBodova[pos]);
				printf("\n");
		
				
				fp = fopen ("/dev/baza", "w");
				if(fp==NULL)
				{
					puts("Problem pri otvaranju /dev/baza \n");
					return -1;
				}
		
				fprintf(fp,"%s,%s,%s=%d\n", ime[pos], prezime[pos], brIndexa[pos], brBodova[pos]);
				pos++;

				if(fclose(fp))
				{
					puts("Problem pri zatvaranju /dev/baza\n");
					return -1;
				}
				printf("\nUspesan unos!\n");
		
			break;
				
			case 2: 
					
				printf("Unesite ime: ");
				scanf("%s",tmp_ime);
				printf("\nUnesite prezime: ");
				scanf("%s",tmp_prezime);
				printf("\nUnesite broj indeksa: ");
				scanf("%s",tmp_brIndexa);
				printf("\nUnesite novi broj bodova: ");
				scanf("%d", &tmp_brBodova);
				printf("\n");
		
				
				fp = fopen ("/dev/baza", "a+");
				if(fp==NULL)
				{
					puts("Problem pri otvaranju /dev/baza \n");
					return -1;
				}
					
				for(int i=0; i<BAZA_SIZE; i++)
				{
					while(fscanf(fp,"%s %s %s - %d\n", brIndexa[i], ime[i], prezime[i], &brBodova[i]) != EOF)
					{
						if(strcmp(ime[i],tmp_ime)==0 && strcmp(prezime[i],tmp_prezime)==0 && strcmp(brIndexa[i],tmp_brIndexa)==0 )
						{
							brBodova[i]=tmp_brBodova;
							fprintf(fp,"%s,%s,%s=%d\n", ime[i], prezime[i], brIndexa[i], brBodova[i]);
							printf("Uspesna izmena! \n");
						}
					}
				}

				if(fclose(fp))
				{
					puts("Problem pri zatvaranju /dev/baza\n");
					return -1;
				}
				
			break;

			case 4: 
				       		
				fp = fopen ("/dev/baza", "r");
				if(fp==NULL)
				{
					puts("Problem pri otvaranju /dev/baza \n");
					return -1;
				}
				for(int i=0; i<BAZA_SIZE; i++)
				{
					while(fscanf(fp,"%s %s %s - %d\n", brIndexa[i], ime[i], prezime[i], &brBodova[i]) != EOF)
						printf("%s %s %s - %d\n", brIndexa[i], ime[i], prezime[i], brBodova[i]);
				}

				if(fclose(fp))
				{
					puts("Problem pri zatvaranju /dev/baza\n");
					return -1;
				}
				printf("\nUspesno citanje!\n");

			break;	
			
			case 5: flag=false;
			break;	

			default:
			break;
		}
	}
}

