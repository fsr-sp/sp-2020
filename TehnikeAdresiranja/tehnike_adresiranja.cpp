#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Struktura
typedef struct {
	int sifra;
	char naziv[51 + 1];
	float cijena;
}zapis;

#define MAX 100

//Parametri
#define MAXZAPIS 100
#define BLOK 512
#define C (int)(BLOK/sizeof(zapis))
#define M (int) ((MAXZAPIS/C) * 1.3)

int adresa(int sifra) {
	return sifra % M;
}

int upis(FILE *f, int adr, zapis pom)
{
	zapis pretinac[C];

	int poc = adr;
	int i;
	i = poc;

	do {
		fseek(f, i * BLOK, SEEK_SET);
		fread(pretinac, sizeof(pretinac), 1, f);
		for (int j = 0; j < C; j++) {
			if (pretinac[j].sifra == pom.sifra) {
				return 0;
			}if (pretinac[j].sifra == 0) {
				pretinac[j] = pom;
				fseek(f, i * BLOK, SEEK_SET);
				fwrite(pretinac, sizeof(pretinac), 1, f);
				if (i == poc)
					return 1;
				else
					return 2;
			}
		}
		i = (i + 1) % M;
	} while (i != poc);
	return 0;
}

FILE *prepisi(char *izlaz, char *ulaz)
{
	FILE *fizlaz, *fulaz;
	if ((fizlaz = fopen(izlaz, "wb+")) == NULL)
		return NULL;
	if ((fulaz = fopen(ulaz, "r")) == NULL)
		return NULL;

	//Format
	zapis pret[C];
	fseek(fizlaz, 0, SEEK_SET);
	for (int i = 0; i < C; i++)
		pret[i].sifra = 0;

	for (int i = 0; i < M; i++) {
		fseek(fizlaz, i*BLOK, SEEK_SET);
		fwrite(pret, sizeof(pret), 1, fizlaz);
	}

	zapis pom;
	int adr;
	while (fscanf(fulaz, "%d,%[^,],%f", &pom.sifra, &pom.naziv, &pom.cijena) != EOF)
	{
		adr = adresa(pom.sifra);
		int r = upis(fizlaz, adr, pom);
		if (r == 1)
			printf("\n%d %d %s %.2f", adr, pom.sifra, pom.naziv, pom.cijena);
		else
			printf("\nPreljev %d %d %s %.2f", adr, pom.sifra, pom.naziv, pom.cijena);
		
	}

	fclose(fizlaz);
	fclose(fulaz);
	return NULL;
}

void parametri() {
	printf("\nM = %d", M);
	printf("\nC = %d", C);
	printf("\nzapis = %d", sizeof(zapis));
}

int print(FILE *f)
{
	zapis pretinac[C];
	int br = 0;
	printf("\nDatoteka\n");
	for (int i = 0; i < M; i++)
	{
		fseek(f, i*BLOK, SEEK_SET);
		fread(pretinac, sizeof(pretinac), 1, f);
		for (int j = 0; j < C; j++)
		{
			printf("%03d ", pretinac[j].sifra);
		}
		printf("\n");
	}
	return br;
}


int brojZapisa(FILE *f)
{
	zapis pretinac[C];
	int br = 0;
	fseek(f, 0, SEEK_SET);
	for (int i = 0; i < M; i++) {
		fseek(f, i * BLOK, SEEK_SET);
		fread(pretinac, sizeof(pretinac), 1, f);
		for (int j = 0; j < C; j++) 
			if (pretinac[j].sifra != 0)
				br++;
	}
	return br;
}

int pronadji(FILE *f, int sifra) {
	return 0;
}

float gustoca(const char *ime_datoteke)
{
	return 0.0;
}

void format(FILE *f)
{
	zapis pretinac[C];
	for (int i = 0; i < M; i++) {
		fseek(f, i * BLOK, SEEK_SET);
		fread(pretinac, sizeof(pretinac), 1, f);
		for (int j = 0; j < C; j++)
			pretinac[j].sifra = 0;
		fseek(f, i * BLOK, SEEK_SET);
		fwrite(pretinac, sizeof(pretinac), 1, f);
	}
}

// Tablica
zapis tablica[MAX];
int upis(int adresa, zapis pom)
{
	tablica[adresa] = pom;
	return -1;
}

int pronadji(int adresa, int sifra, char *naziv)
{
	return -1;
}

int main()
{
	char fin[] = "artikli.txt";
	char fout[] = "artikli.dat";

	prepisi(fout, fin);

	FILE *f = fopen(fout, "rb+");
	if (f == NULL)
		return -1;

	parametri();
	print(f);

	format(f);
	int br = brojZapisa(f);
	zapis pom = { 10, "Naziv1", 34.4 };

	_getch();
	return 1;
}