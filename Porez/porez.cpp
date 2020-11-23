#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct element {
	char	JMBG[13 + 1];
	char	ImePrezime[40 + 1];
	float	Prihod;
	float	PlatitiPorez;
};
typedef struct element zapis;

// služi samo da bi se dobili podaci za testiranje
int prepisi(char *filenameIn, char *filenameOut) {
	FILE *fin, *fout;
	zapis z;
	int Br;

	fin = fopen(filenameIn, "r");
	fout = fopen(filenameOut, "w");

	if (fin == NULL || fout == NULL) {
		printf("pogreška prilikom prepisivanja podataka");
		return 0;
	}

	fscanf(fin, "%d\n", &Br);
	fwrite(&Br, sizeof(Br), 1, fout);

	while (fscanf(fin, "%s %[^\n] %f %f", z.JMBG, z.ImePrezime, &(z.Prihod), &(z.PlatitiPorez)) > 0) {
		fwrite(&z, sizeof(z), 1, fout);
	}

	fclose(fin);
	fclose(fout);
	return 1;
}

//1. Zadatak
zapis* Ucitaj(char *FileName, int *BrElem) {
	int		i; //lokalne varijable
	int	Br = 0;
	FILE 	*fp;
	zapis	*Polje = NULL;
	zapis	Elem;
	// Ovdje napisati kod
	fp = fopen(FileName, "r");
	if (fp == NULL)
		return NULL;
	fread(&Br, sizeof(int), 1, fp);
	Polje = (zapis *)malloc(Br * sizeof(zapis));
	for (int i = 0; i < Br; i++)
		fread(&Polje[i], sizeof(zapis), 1, fp);
	*BrElem = Br;
	return Polje;
}

//2. Zadatak
int	MaxPorez(zapis *Polje, int BrElem) {
	int	i, MaxInd;
	float Max;
	Max = Polje[0].PlatitiPorez;
	MaxInd = 0;
	for (int i=1; i< BrElem; i++)
		if (Polje[i].PlatitiPorez > Max) {
			MaxInd = i;
			Max = Polje[i].PlatitiPorez;
		}
	return MaxInd;
}

int IzbrisiZadnjeg(zapis *Polje, int *brElem) {
	return 1;
}

int main() {
	int	BrElem, MaxInd; //lokalne varijable
	char fout[40] = "podaci.dat";
	char fin[40] = "podaci.txt";
	zapis *Polje;
	prepisi(fin, fout);
	Polje = Ucitaj(fout, &BrElem);
	if (Polje != NULL) {
		MaxInd = MaxPorez(Polje, BrElem);
		printf("Najvise poreza treba platiti %s, u iznosu od %.0f", Polje[MaxInd].ImePrezime,
			Polje[MaxInd].PlatitiPorez);
	}
	free(Polje);
	_getch();
	return 0;
}
