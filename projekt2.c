#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

struct Obraz {
    char P2[3];
    int szerokosc;
    int wysokosc;
    int szarosc;
    int** piksele;    
    char nazwa[100];
};

void zwolnij(struct Obraz* obraz) 
{
    if (obraz->piksele != NULL) {
        for (int i = 0; i < obraz->wysokosc; i++) {
            free(obraz->piksele[i]);
        }
        free(obraz->piksele);
        obraz->piksele = NULL;
    }
}

void pomin_komentarze(FILE* plik) 
{
    int znak;
    while ((znak = fgetc(plik)) != EOF) 
    {
        if (znak == '#') 
        {
            while ((znak = fgetc(plik)) != EOF && znak != '\n');
        }
        else if (znak == ' ' || znak == '\n' || znak == '\t' || znak == '\r') {
            continue; 
        }
        else 
        {
            ungetc(znak, plik); 
            break;
        }
    }
}

int wczytaj_int() {
    int liczba;
    while (1) {
        if (scanf("%d", &liczba) == 1) {
            return liczba;
        }
        else {
            printf("To nie jest liczba. Sprobuj ponownie: ");
            while (getchar() != '\n'); 
        }
    }
}

int wczytaj(char nazwa_pliku[], struct Obraz* obraz) 
{
    FILE* plik = fopen(nazwa_pliku, "r");

    if (plik == NULL) {
        printf("Blad! Nie mozna otworzyc pliku: %s\n", nazwa_pliku);
        return 0;
    }

    strcpy(obraz->nazwa, nazwa_pliku);

    pomin_komentarze(plik);
    fscanf(plik, "%s", obraz->P2);

    pomin_komentarze(plik);
    fscanf(plik, "%d", &obraz->szerokosc);

    pomin_komentarze(plik);
    fscanf(plik, "%d", &obraz->wysokosc);

    pomin_komentarze(plik);
    fscanf(plik, "%d", &obraz->szarosc);

    obraz->piksele = malloc(obraz->wysokosc * sizeof(int*));
    for (int i = 0; i < obraz->wysokosc; i++) {
        obraz->piksele[i] = malloc(obraz->szerokosc * sizeof(int));
    }

    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            pomin_komentarze(plik);
            fscanf(plik, "%d", &obraz->piksele[i][j]);
        }
    }

    fclose(plik);
    printf("Wczytano obraz: %s (%dx%d)\n", obraz->nazwa, obraz->szerokosc, obraz->wysokosc);
    return 1;
}

void zapisz(char nazwa_pliku[], struct Obraz* obraz) 
{
    FILE* plik = fopen(nazwa_pliku, "w");

    if (plik == NULL) {
        printf("Blad tworzenia pliku: %s\n", nazwa_pliku);
        return;
    }

    fprintf(plik, "%s\n%d %d\n%d\n", obraz->P2, obraz->szerokosc, obraz->wysokosc, obraz->szarosc);

    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            fprintf(plik, "%d ", obraz->piksele[i][j]);
        }
        fprintf(plik, "\n");
    }
    fclose(plik);
    printf("Zapisano plik jako: %s\n", nazwa_pliku);
}

void obroc(struct Obraz* obraz) {
    int nowa_szer = obraz->wysokosc;
    int nowa_wys = obraz->szerokosc;

    int** temp = malloc(nowa_wys * sizeof(int*));
    for (int i = 0; i < nowa_wys; i++) {
        temp[i] = malloc(nowa_szer * sizeof(int));
    }

    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            temp[j][obraz->wysokosc - 1 - i] = obraz->piksele[i][j];
        }
    }

    zwolnij(obraz);
    obraz->piksele = temp;
    obraz->szerokosc = nowa_szer;
    obraz->wysokosc = nowa_wys;
}

void negatyw(struct Obraz* obraz) {
    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            obraz->piksele[i][j] = obraz->szarosc - obraz->piksele[i][j];
        }
    }
    printf("Zastosowano filtr: Negatyw.\n");
}

void generuj_histogram(struct Obraz* obraz) {
    int* hist = calloc(obraz->szarosc + 1, sizeof(int));

    if (hist == NULL) {
        printf("Blad alokacji pamieci dla histogramu!\n");
        return;
    }

    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            int wartosc = obraz->piksele[i][j];
            if (wartosc <= obraz->szarosc) hist[wartosc]++;
        }
    }

    FILE* plik = fopen("histogram.csv", "w");
    if (plik == NULL) {
        printf("Blad zapisu histogramu!\n");
        free(hist);
        return;
    }
    fprintf(plik, "Wartosc;Liczba\n");
    for (int i = 0; i <= obraz->szarosc; i++) {
        fprintf(plik, "%d;%d\n", i, hist[i]);
    }
    fclose(plik);
    free(hist);
    printf("Histogram zapisano do pliku 'histogram.csv'.\n");
}

void statystyki(struct Obraz* obraz) {
    int min = obraz->szarosc;
    int max = 0;
    long long suma = 0;
    long long liczba_pikseli = (long long)obraz->szerokosc * obraz->wysokosc;

    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            int wartosc = obraz->piksele[i][j];
            if (wartosc < min) min = wartosc;
            if (wartosc > max) max = wartosc;
            suma += wartosc;
        }
    }
    float srednia = (float)suma / liczba_pikseli;

    printf("\n STATYSTYKI \n");
    printf("Rozmiar: %dx%d\n", obraz->szerokosc, obraz->wysokosc);
    printf("Jasnosc MIN: %d\n", min);
    printf("Jasnosc MAX: %d\n", max);
    printf("Jasnosc SREDNIA: %.2f\n", srednia);
}

void odbicie_lustrzane(struct Obraz* obraz, int tryb) {
    int temp;
    if (tryb == 1) { // Os PIONOWA (zamiana Lewo-Prawo)
        for (int i = 0; i < obraz->wysokosc; i++) {
            for (int j = 0; j < obraz->szerokosc / 2; j++) {
                temp = obraz->piksele[i][j];
                obraz->piksele[i][j] = obraz->piksele[i][obraz->szerokosc - 1 - j];
                obraz->piksele[i][obraz->szerokosc - 1 - j] = temp;
            }
        }
        printf("Odbito wzgledem osi pionowej.\n");
    }
    else if (tryb == 2) { 
        for (int i = 0; i < obraz->wysokosc / 2; i++) {
            int* tempRow = obraz->piksele[i];
            obraz->piksele[i] = obraz->piksele[obraz->wysokosc - 1 - i];
            obraz->piksele[obraz->wysokosc - 1 - i] = tempRow;
        }
        printf("Odbito wzgledem osi poziomej.\n");
    }
}

void szum_pieprz_sol(struct Obraz* obraz, int szansa) {
    for (int i = 0; i < obraz->wysokosc; i++) {
        for (int j = 0; j < obraz->szerokosc; j++) {
            if ((rand() % 100) < szansa) {
                obraz->piksele[i][j] = (rand() % 2 == 0) ? 0 : obraz->szarosc;
            }
        }
    }
    printf("Dodano szum 'Pieprz i Sol' (%d%%).\n", szansa);
}

void filtr_medianowy(struct Obraz* obraz) 
{
    int** temp = malloc(obraz->wysokosc * sizeof(int*));
    for (int i = 0; i < obraz->wysokosc; i++) {
        temp[i] = malloc(obraz->szerokosc * sizeof(int));
        for (int j = 0; j < obraz->szerokosc; j++) {
            temp[i][j] = obraz->piksele[i][j];
        }
    }
    int okno[9]; 
    for (int i = 1; i < obraz->wysokosc - 1; i++) {
        for (int j = 1; j < obraz->szerokosc - 1; j++) {
            int k = 0;
           
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    okno[k++] = obraz->piksele[i + x][j + y];
                }
            }
            qsort(okno, 9, sizeof(int), porownaj);
            temp[i][j] = okno[4];
        }
    }

    zwolnij(obraz);
    obraz->piksele = temp;
    printf("Zastosowano Filtr Medianowy (odszumianie).\n");
}

int porownaj(void* a, void* b)
{
    return (*(int*)a - *(int*)b);
}

void filtr_gaussa(struct Obraz* obraz) {
    int** temp = malloc(obraz->wysokosc * sizeof(int*));
    for (int i = 0; i < obraz->wysokosc; i++) {
        temp[i] = malloc(obraz->szerokosc * sizeof(int));
        for (int j = 0; j < obraz->szerokosc; j++) {
            temp[i][j] = obraz->piksele[i][j];
        }
    }

    int maska[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
    int suma_wag = 16;

    for (int i = 1; i < obraz->wysokosc - 1; i++) {
        for (int j = 1; j < obraz->szerokosc - 1; j++) {
            int suma = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    suma += obraz->piksele[i + k][j + l] * maska[k + 1][l + 1];
                }
            }
            temp[i][j] = suma / suma_wag;
        }
    }

    zwolnij(obraz);
    obraz->piksele = temp;
    printf("Zastosowano Filtr Gaussa (wygladzanie).\n");
}

int main() 
{
    srand(time(NULL)); 
    struct Obraz mojObraz;
    mojObraz.piksele = NULL; 
    int opcja = -1;
    char nazwa[100];

    while (opcja != 0) 
    {
        printf("\MENU\n");
        printf("1. Wczytaj obraz\n");
        printf("2. Zapisz obraz\n");
        printf("3. Obroc obraz (90/180/270)\n");
        printf("4. Negatyw\n");
        printf("5. Generuj histogram (CSV)\n");
        printf("6. Statystyki obrazu\n");
        printf("7. Odbicie lustrzane (pion/poziom)\n");
        printf("8. Szum Pieprz i Sol\n");
        printf("9. Filtr Medianowy (usuwa szum)\n");
        printf("10. Filtr Gaussa (wygladzanie)\n");
        printf("0. Wyjscie\n");
        printf("Wybierz opcje: ");

        opcja = wczytaj_int();

        switch (opcja) {
        case 1:
            printf("Podaj nazwe pliku do odczytu: ");
            scanf("%s", nazwa);
            if (mojObraz.piksele != NULL) zwolnij(&mojObraz);
            wczytaj(nazwa, &mojObraz);
            break;
        case 2:
            if (mojObraz.piksele != NULL) {
                printf("Podaj nazwe pliku do zapisu: ");
                scanf("%s", nazwa);
                zapisz(nazwa, &mojObraz);
            }
            else printf("Blad: Brak wczytanego obrazu!\n");
            break;
        case 3:
            if (mojObraz.piksele != NULL) {
                printf("Ile obrotow 90st w prawo? (1-3): ");
                int ile = wczytaj_int();
                if (ile >= 1 && ile <= 3) {
                    for (int k = 0; k < ile; k++) obroc(&mojObraz);
                    printf("Gotowe!\n");
                }
                else printf("Blad: Podaj 1, 2 lub 3.\n");
            }
            else printf("Blad: Brak wczytanego obrazu!\n");
            break;
        case 4:
            if (mojObraz.piksele != NULL)
                negatyw(&mojObraz);
            else printf("Blad: Brak wczytanego obrazu!\n");
            break;
        case 5:
            if (mojObraz.piksele != NULL)
                generuj_histogram(&mojObraz);
            else printf("Blad: Brak wczytanego obrazu!\n");
            break;
        case 6:
            if (mojObraz.piksele != NULL)
                statystyki(&mojObraz);
            else printf("Blad: Brak wczytanego obrazu!\n");
            break;
        case 7:
            if (mojObraz.piksele != NULL) {
                printf("Os: 1.Pionowa 2.Pozioma: ");
                int os = wczytaj_int();
                if (os == 1 || os == 2) odbicie_lustrzane(&mojObraz, os);
                else printf("Nieznana os.\n");
            }
            else printf(" Brak wczytanego obrazu!\n");
            break;
        case 8:
            if (mojObraz.piksele != NULL) {
                printf("Moc szumu (0-100): ");
                int pr = wczytaj_int();
                if (pr >= 0 && pr <= 100) szum_pieprz_sol(&mojObraz, pr);
                else printf("Blad: 0-100.\n");
            }
            else printf(" Brak wczytanego obrazu!\n");
            break;
        case 9:
            if (mojObraz.piksele != NULL)
                filtr_medianowy(&mojObraz);
            else printf(" Brak wczytanego obrazu!\n");
            break;
        case 10:
            if (mojObraz.piksele != NULL)
                filtr_gaussa(&mojObraz);
            else printf("Brak wczytanego obrazu!\n");
            break;
        case 0:
            zwolnij(&mojObraz);
            printf("Konciec\n");
            break;
        default:
            printf("Nieznana opcja.\n");
        }
    }

    return 0;
}