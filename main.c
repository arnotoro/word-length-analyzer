#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SANAT_MAX 300
#define MAX 50

typedef struct sanat {
    char sana[SANAT_MAX];
    int sanaluokka;
    struct sanat *pSeuraava;
} SANAT;

typedef struct tilastot {
    int sanatLkm;
    int kumulPituus;
    char lyhinSana[SANAT_MAX];
    char pisinSana[SANAT_MAX];
    char ensimmainenSana[SANAT_MAX];
    char viimeinenSana[SANAT_MAX];
} TILASTOT;

typedef struct sanaluokka {
    int luokkaNro;
    int sanatLkm;
} SANALUOKKA;

// luokkien alustus ja alustetaan ensimmäinen alkio nollaksi, jotta
// sanaluokka voidaan hakea suoraan indeksiä hyödyntäen
SANALUOKKA sanaluokat[] = {
    {0, 0}, // ei tietoa
    {1, 0}, // substantiivi
    {2, 0}, // verbi
    {3, 0}, // adjektiivi
    {4, 0}, // adverbi
    {5, 0}, // prepositio
    {6, 0}, // numero
    {7, 0}, // tarkenne
    {8, 0}, // pronomini
    {9, 0}, // konjunktio
    {10, 0}, // huudahdus
};

int valikko(void);
void kysyTiedostonNimi(char *tiedostonNimi);
SANAT *lueTiedosto(SANAT *pAlku, char *tiedostonNimi);
SANAT *lisaaListaan(SANAT *pAlku, char *rivi);
TILASTOT *analysoiTiedot(SANAT *pAlkuS, TILASTOT *pALkuT);
void tulostaTiedot(FILE *tietoVirta, TILASTOT *ptr);
void kirjoitaTiedosto(char *tiedostonNimi, TILASTOT *ptr);

int main (void) {
    int valinta = 1;
    char tiedostonNimi[MAX];
    SANAT *pAlku = NULL;
    TILASTOT *ptr = NULL;



    do {
        valinta = valikko();

        if (valinta == 1) {
            kysyTiedostonNimi(tiedostonNimi);
            pAlku = lueTiedosto(pAlku, tiedostonNimi);
        } 
        else if (valinta == 2) {
            ptr = analysoiTiedot(pAlku, ptr);
        } 
        else if (valinta == 3) {
            kysyTiedostonNimi(tiedostonNimi);
            kirjoitaTiedosto(tiedostonNimi, ptr);
        }
        else if (valinta == 0) {
            printf("Lopetetaan. \n");
        } 
        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }

        printf("\n");
    } while (valinta != 0);


    printf("Kiitos ohjelman käytöstä!\n");
    return 0;
}

int valikko(void) {
    int valinta;

    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("0) Lopeta\n");

    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    getchar();

    return valinta;
}

void kysyTiedostonNimi(char *tiedostonNimi) {
    printf("Anna tiedoston nimi: ");
    scanf("%s", tiedostonNimi);
}

SANAT *lueTiedosto(SANAT *pAlku, char *tiedostonNimi) {
    FILE *tiedosto;
    char otsikkoRivi[SANAT_MAX], rivi[SANAT_MAX];

    // jos lista jo olemassa, tyhjennetään
    if (pAlku != NULL) {

    }

    if ((tiedosto = fopen(tiedostonNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopeteaan");
        exit(0);
    } 
    else {
        // luetaan otsikkorivi ensin pois
        fgets(otsikkoRivi, SANAT_MAX, tiedosto);

        // käydään lopputiedosto lävitse ja tallennetaan tiedot linkitettyyn listaan
        while (fgets(rivi, SANAT_MAX, tiedosto) != NULL) {
            pAlku = lisaaListaan(pAlku, rivi);
        }

        printf("Tiedosto '%s' luettu.\n", tiedostonNimi);
        fclose(tiedosto);
    }

    return pAlku;
}

SANAT *lisaaListaan(SANAT *pAlku, char *tietoRivi) {
    SANAT *pUusi = NULL;
    SANAT *ptr = NULL;
    char *sana;
    int sanaluokka;

    // varataan muistia uudelle alkiolle
    if ((pUusi = (SANAT*)malloc(sizeof(SANAT))) == NULL) {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }

    sana = strtok(tietoRivi, ";");
    sanaluokka = atoi(strtok(NULL, ";"));



    strcpy(pUusi->sana, sana);
    pUusi->sanaluokka = sanaluokka;
    pUusi->pSeuraava = NULL;

    // jos lista tyhjä, lisätään alkio listan alkuun
    if (pAlku == NULL) {
        pAlku = pUusi;
    } 
    else {
        ptr = pAlku;
        while (ptr->pSeuraava != NULL) {
            ptr = ptr->pSeuraava;
        }
        ptr->pSeuraava = pUusi;
    }

    return pAlku;
}


TILASTOT *analysoiTiedot(SANAT *pAlkuS, TILASTOT *pAlkuT) {
    int sanatLKM = 0;
    int vikaSanaArvo = 0, ekaSanaArvo = 0;
    int kumulPituus = 0;
    char lyhinSana[SANAT_MAX], pisinSana[SANAT_MAX];
    char ekaSana[SANAT_MAX], vikaSana[SANAT_MAX];
    char nykSana[SANAT_MAX];
    SANAT *ptr = pAlkuS;

    if (pAlkuT != NULL) {
        // tyhjennetään lista
    }



    while (ptr != NULL) {
        if((pAlkuT = (TILASTOT*)malloc(sizeof(TILASTOT))) == NULL) {
            perror("Muistinvaraus epäonnistui, lopetetaan");
            exit(0);
        }

        // alustetaan muuttujat
        if (sanatLKM == 0) {
            strcpy(ekaSana, ptr->sana);
            strcpy(vikaSana, ptr->sana);
            strcpy(lyhinSana, ptr->sana);
            strcpy(pisinSana, ptr->sana);
        }


        // käsiteltävä sana
        strcpy(nykSana, ptr->sana);
        
        // ensimmäinen sana aakkosissa
        ekaSanaArvo = strcmp(ekaSana, nykSana);
        if (ekaSanaArvo > 0) {
            strcpy(ekaSana, nykSana);
        } 

        // viimeinen sana aakkosissa
        vikaSanaArvo = strcmp(vikaSana, nykSana);
        if (vikaSanaArvo < 0) {
            strcpy(vikaSana, nykSana);
        }

        // kumulatiivinen pituus
        kumulPituus += strlen(nykSana);

        // lyhin sana
        if (strlen(nykSana) < strlen(lyhinSana)) {
            strcpy(lyhinSana, nykSana);
        }

        // pisin sana
        if (strlen(nykSana) > strlen(pisinSana)) {
            strcpy(pisinSana, nykSana);
        }

        sanatLKM++; // sanojen määrä


        // sanaluokkien lukumäärä

        sanaluokat[ptr->sanaluokka].sanatLkm++;

        ptr = ptr->pSeuraava;
    }



    // tallennetaan tilastotiedot
    pAlkuT->sanatLkm = sanatLKM;
    pAlkuT->kumulPituus = kumulPituus;
    strcpy(pAlkuT->lyhinSana, lyhinSana);
    strcpy(pAlkuT->pisinSana, pisinSana);
    strcpy(pAlkuT->ensimmainenSana, ekaSana);
    strcpy(pAlkuT->viimeinenSana, vikaSana);

    return pAlkuT;
}


void kirjoitaTiedosto(char *tiedostonNimi, TILASTOT *ptr) {
    FILE *tiedosto;

    if ((tiedosto = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    
    // kirjoitetaan tiedot tiedostoon
    tulostaTiedot(tiedosto, ptr);

    fclose(tiedosto);

    // kirjoitetaan tiedot näytölle
    tulostaTiedot(stdout, ptr);
}

void tulostaTiedot(FILE *tietoVirta, TILASTOT *ptr) {
    if (tietoVirta == stdout) {
        printf("Tilastotiedot %d sanasta:\n", ptr->sanatLkm);
        printf("Keskimääräinen sanan pituus on %.1f merkkiä.\n", (float)ptr->kumulPituus/ptr->sanatLkm);
        printf("Pisin sana '%s' on %lu merkkiä pitkä.\n", ptr->pisinSana, strlen(ptr->pisinSana));
        printf("Lyhin sana '%s' on %lu merkkiä pitkä.\n", ptr->lyhinSana, strlen(ptr->lyhinSana));
        printf("Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", ptr->ensimmainenSana);
        printf("Aakkosjärjestyksessä viimeinen sana on '%s'.\n", ptr->viimeinenSana);

        printf("\n");
        
        printf("Sanaluokka;Lkm\n");

        for (int i = 0; i < 10; i++) {
            printf("Luokka %d;%d\n", i, sanaluokat[i].sanatLkm);
        }
    } 
    else {
        fprintf(tietoVirta, "Tilastotiedot %d sanasta:\n", ptr->sanatLkm);
        fprintf(tietoVirta, "Keskimääräinen sanan pituus on %.1f merkkiä.\n", (float)ptr->kumulPituus/ptr->sanatLkm);
        fprintf(tietoVirta, "Pisin sana '%s' on %lu merkkiä pitkä.\n", ptr->pisinSana, strlen(ptr->pisinSana));
        fprintf(tietoVirta, "Lyhin sana '%s' on %lu merkkiä pitkä.\n", ptr->lyhinSana, strlen(ptr->lyhinSana));
        fprintf(tietoVirta, "Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", ptr->ensimmainenSana);
        fprintf(tietoVirta, "Aakkosjärjestyksessä viimeinen sana on '%s'.\n", ptr->viimeinenSana);

        fprintf(tietoVirta, "\n");

        fprintf(tietoVirta, "Sanaluokka;Lkm\n");

        for (int i = 1; i <= 10; i++) {
            fprintf(tietoVirta, "Luokka %d;%d\n", i, sanaluokat[i].sanatLkm);
        }
    }
}