// Projekt.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>

FILE *v() {
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

void o(FILE *p_file) {
	int datum_a, datum;
	scanf("%d", &datum_a);
	int poc = 1;
	char riadok[50], ch;
	while (!feof(p_file)) {
		ch = fgetc(p_file);
		if (ch == '\n') {
			poc++;
		}
	}
	poc = poc / 5;
	fseek(p_file, 0L, SEEK_SET);
	int i = 1, j=0, poz=1;
	int *pozicie = (int *)malloc(sizeof(int)*(poc));
	while (!feof(p_file)) {
		fgets(riadok, sizeof(riadok), p_file);
		if (i == 5) {
			i = 0;
			datum = atoi(riadok);
			if ((datum_a - datum) > 10000) {			//pokial to je nad 10000 znamen· to ze tam pracuje viac ako rok
				pozicie[j] = poz;
				j++;
			}
		}
		i++;
		poz++;
	}													//zisùovanie kto ma narok na odmenu
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

char** n(FILE *p_file) {
	int poc = 1, i = 1, j = 0, l, k=0;
	char ch;
	while (!feof(p_file)) {
		ch = fgetc(p_file);
		if (ch == '\n') {
			poc++;
		}
	}
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

void s(char **p_spz, FILE *p_file) {
	char ch;
	int poc = 1;
	while (!feof(p_file)) {
		ch = fgetc(p_file);
		if (ch == '\n') {
			poc++;
		}
	}
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

void p(char **p_spz, FILE *p_file)
{
	char ch;
	int poc = 1;
	while (!feof(p_file)) {
		ch = fgetc(p_file);
		if (ch == '\n') {
			poc++;
		}
	}
	int i, z, j;
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

void z(char **p_spz, FILE *p_file)
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

int main()
{
	char funkcia, **p_spz = NULL;
	FILE *p_file = NULL;
	while ((funkcia = getchar()) != 'k') {
		if (funkcia == 'v')
		{
			p_file = v();
		}
		else if ((p_file != NULL) && (p_spz == NULL) && (funkcia == 'n'))
		{
			p_spz = n(p_file);
		}
		else if ((p_file != NULL) && (p_spz != NULL) && (funkcia == 'n'))
		{
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
			p_spz = n(p_file);
		}
		else if ((p_file != NULL) && (funkcia == 'o'))
		{
			o(p_file);
		}
		else if ((p_file != NULL) && (p_spz != NULL) && (funkcia == 's'))
		{
			s(p_spz, p_file);
		}
		else if ((p_file != NULL) && (p_spz != NULL) && (funkcia == 'p'))
		{
			p(p_spz, p_file);
		}
		else if ((p_file != NULL) && (p_spz != NULL) && (funkcia == 'z'))
		{
			z(p_spz, p_file);
		}
		else if (((p_spz == NULL) && (funkcia == 's')) ||  (p_spz == NULL) && (funkcia == 'p'))
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