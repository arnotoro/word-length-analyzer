/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Tekijä: Arno Törö
 * Opiskelijanumero: 0570180
 * Päivämäärä: 12.3.2023
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
 * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla: -

 * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
 * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
 * vaikuttaneet siihen yllä mainituilla tavoilla.
 */
/*************************************************************************/
/* Tehtävä perustason harkkatyö, tiedoston nimi funktiot.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funktiot.h"

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

    return;
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

    return;
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

    return;
}

/* eof */