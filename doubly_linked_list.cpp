#include <stdio.h>
#include <stdlib.h>

struct osoba {
	int cislo;
	osoba *dalsi;
};

int main(int argc, char *argv[])
{
	osoba *zakaznici = NULL;
	osoba *os;

	for (int i = 0; i < 10; i++) {
		osoba *novy_zakaznik;
		novy_zakaznik = (struct osoba *)malloc(sizeof(osoba));
		novy_zakaznik->cislo = i;
		novy_zakaznik->dalsi = zakaznici;
		zakaznici = novy_zakaznik;
	}

	for (os = zakaznici; os; os = os->dalsi) {
		printf("cislo: %d\n", os->cislo);
	}

	getchar();

	return 0;
}