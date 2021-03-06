// Projekt.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>

int pocet_riadkov(FILE *p_file)
{
	char ch;
	int poc = 1;
	while (!feof(p_file)) {
		ch = fgetc(p_file);
		if (ch == '\n') {
			poc++;
		}
	}
	return poc;
}

FILE *vypis_suboru() {
	FILE *p_file = fopen("predaj.txt", "r");;

	if (p_file == NULL) {
		printf("Neotvoreny subor\n");
		return NULL;
	}
	char riadok[50];
	int i = 1;
	while ((fgets(riadok, sizeof(riadok), p_file))) {
		switch (i) {
			case 1:
				printf("meno priezvisko: %s", riadok);
				break;
			case 2:
				printf("SPZ: %s", riadok);
				break;
			case 3:
				printf("typ auta: %s", riadok);
				break;
			case 4:
				printf("cena: %s", riadok);
				break;
			case 5:
				printf("datum: %s", riadok);
				i = 0;
				printf("\n");
				break;
		}
		i++;
	}
	fseek(p_file, 0L, SEEK_SET);
	return p_file;
}

void odmeny(FILE *p_file) {
	int datum_zadany, datum_subor;
	scanf("%d", &datum_zadany);
	int poc = pocet_riadkov(p_file);
	char riadok[50];
	poc = poc / 5;
	fseek(p_file, 0L, SEEK_SET);
	int i = 1, j=0, pozicia=1;
	int *pozicie = (int *)malloc(sizeof(int)*(poc));
	while (!feof(p_file)) {
		fgets(riadok, sizeof(riadok), p_file);
		if (i == 5) {
			i = 0;
			datum_subor = atoi(riadok);
			if ((datum_zadany - datum_subor) > 10000) {			//pokial to je nad 10000 znamená to ze tam pracuje viac ako rok
				pozicie[j] = pozicia;
				j++;
			}
		}
		i++;
		pozicia++;
	}													//zisťovanie kto ma narok na odmenu
	fseek(p_file, 0L, SEEK_SET);
	i = 1;
	j = 0;
	int typ, k;
	double suma;
	while (!feof(p_file)) {
		fgets(riadok, sizeof(riadok), p_file);
		if (i == (pozicie[j] - 4)) {
			for (k = 0; k <= sizeof(riadok); k++) {
				if (riadok[k] == '\n') {
					riadok[k] = 0;
				}
			}
			printf("%s ", riadok);
		}
		else if (i == (pozicie[j] - 3)) {
			for (k = 1; k <= sizeof(riadok); k++) {
				if (riadok[k] == '\n') {
					riadok[k] = 0;
				}
			}
			printf("%s ", riadok);
		}
		else if (i == (pozicie[j] - 2)) {
			typ = atoi(riadok);
		}
		else if (i == (pozicie[j] - 1)) {
			suma = atoi(riadok);
			if (typ == 0) {
				suma = suma / 100 * 2.2;
			}
			else {
				suma = suma / 100 * 1.5;
			}
			printf("%.2lf\n", suma);
			j++;
		}
		i++;
	}												//vypis osob ktore maju odmenu a vypocet odmeny
	fseek(p_file, 0L, SEEK_SET);
	free(pozicie);
}

char** vytvorenie_pola_SPZ(FILE *p_file) {
	int poc = pocet_riadkov(p_file), i = 1, j = 0, l, k=0;
	poc = poc / 5;
	fseek(p_file, 0L, SEEK_SET);
	char **p_spz = (char **)malloc(poc * sizeof(char*));
	char riadok[50];
	while (fgets(riadok, sizeof(riadok), p_file)) {
		if (i == 2) {
			p_spz[k] = (char *)malloc(sizeof(char) * 8);			//alokacia 2D pola
			for (l = 0; l < 7; l++) {
				p_spz[k][l] = riadok[l];							//zapisanie SPZ po znakoch do pola
			}
			p_spz[k][7] = '\0';
			k++;
		}
		else if (i == 5) {
			i = 0;
		}
		i++;
	}
	fseek(p_file, 0L, SEEK_SET);
	return p_spz;
}

void vypis_SPZ(char **p_spz, FILE *p_file) {
	int poc;
	poc = pocet_riadkov(p_file);
	for (int i = 0; i < (poc/5); i++) {
		for (int j = 0; j < 7; j++) {
			printf("%c", p_spz[i][j]);
			if (j == 1) {
				printf(" ");
			}
			else if (j == 4) {
				printf(" ");
			}
		}
		printf("\n");
	}
	fseek(p_file, 0L, SEEK_SET);
}

void palindrom(char **p_spz, FILE *p_file)
{
	int poc = pocet_riadkov(p_file), i, z, j;
	char *b;
	for (i = 0; i < (poc/5); i++)
	{
		int poc_p = 0;
		z = 1;
		b = (char *)malloc(sizeof(char) * 8);
		strcpy(b, p_spz[i]);
		for (j=0; j< 7;j++)
		{
			if (b[j] == b[(6-z+1)])
			{
				poc_p++;
			}
			z++;
		}
		if (poc_p == 7)
		{
			for (j=0;j<2;j++)
			{
				printf("%c", b[j]);
			}
			printf("\n");
		}
	}
	fseek(p_file, 0L, SEEK_SET);
}

void predajnost(char **p_spz, FILE *p_file)
{
	char ch;
	int poc = 1, i, j, pomoc, poc_spz = 1, max = -1, poz = 0;
	while (!feof(p_file)) {
		ch = fgetc(p_file);
		if (ch == '\n') {
			poc++;
		}
	}
	poc = poc / 5;
	for (i=0;i<poc;i++)
	{
		for (j=0;j<poc;j++)
		{
			if ((i<j) && (p_spz[i][0] == p_spz[j][0]) && (p_spz[i][1] == p_spz[j][1]))
			{
				poc_spz++;
			}
		}
		if (poc_spz >=2)
		{
			printf("%c%c %d\n", p_spz[i][0],p_spz[i][1],poc_spz);
		}
		poc_spz=1;
	}
	fseek(p_file, 0L, SEEK_SET);
}

void histogram (char **p_spz, FILE *p_file)
{
	int poc = pocet_riadkov(p_file);
	poc = poc / 5;
	int i, j, k = 0, poc_b, cislo;
	char l = 48;
	char *p_pomoc = (char*)malloc(sizeof(char)*(poc*3)), *p_histogram = (char*)malloc(sizeof(char)*10);
	for (i=0;i<poc;i++)
		for (j=0;j<7;j++)
			if ((j==2) || (j==3) || (j==4))
			{
				p_pomoc[k] = p_spz[i][j];
				k++;
			}

	for (i=0;i<10;i++)
	{
		p_histogram[i] = l;
		l++;
	}
	for (i=0;i<10;i++)
	{
		poc_b = 0;
		for (j=0;j<(poc*3);j++)
			if (p_histogram[i] == p_pomoc[j])
				poc_b++;
		if (poc_b !=0)
			printf("%c:%d\n", p_histogram[i], poc_b);
	}
	free(p_pomoc);
	free(p_histogram);
}

int main()
{
	char funkcia, **p_spz = NULL;
	FILE *p_file = NULL;
	while ((funkcia = getchar()) != 'k') {
		if (funkcia == 'v')
		{
			p_file = vypis_suboru();
		}
		else if ((p_file != NULL) && (p_spz == NULL) && (funkcia == 'n'))
		{
			p_spz = vytvorenie_pola_SPZ(p_file);
		}
		if ((p_file != NULL) && (p_spz != NULL))
		{
			switch(funkcia)
			{
				case 'o':
					odmeny(p_file);
					break;
				case 's':
					vypis_SPZ(p_spz, p_file);
					break;
				case 'p':
					palindrom(p_spz, p_file);
					break;
				case 'z':
					predajnost(p_spz, p_file);
					break;
				case 'b':
					histogram(p_spz, p_file);
				case 'n': 
					char ch;
					int poc = 1, i;
					while (!feof(p_file)) {
						ch = fgetc(p_file);
						if (ch == '\n') {
							poc++;
						}
					}
					fseek(p_file, 0L, SEEK_SET);
					for (i=0;i<(poc/5);i++)
					{
						free(p_spz[i]);
					}
					free(p_spz);
					p_spz = vytvorenie_pola_SPZ(p_file);
					break;
			}
		}
		else if (((p_spz == NULL) && ((funkcia == 's')) || (funkcia == 'p')))
		{
			printf("Pole nie je vytvorene\n");
		}

	}
	if (p_file != NULL)
	{
		fclose(p_file);
	}
	return 0;
}