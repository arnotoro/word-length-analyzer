/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Tekijä: Arno Törö
 * Opiskelijanumero: 
 * Päivämäärä: 12.3.2023
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
 * lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla: -

 * Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
 * tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
 * vaikuttaneet siihen yllä mainituilla tavoilla.
 */
/*************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HTPerusKirjasto.h"

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
        pAlku = tyhjennaSanat(pAlku);
    }

    if ((tiedosto = fopen(tiedostonNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
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


TILASTOT *analysoiTiedot(SANAT *pAlkuS, TILASTOT *pAlkuT, SANALUOKKA sanaluokat[]) {
    int sanatLKM = 0;
    int vikaSanaArvo = 0, ekaSanaArvo = 0;
    int kumulPituus = 0;
    char lyhinSana[SANAT_MAX], pisinSana[SANAT_MAX];
    char ekaSana[SANAT_MAX], vikaSana[SANAT_MAX];
    char nykSana[SANAT_MAX];
    SANAT *ptr = pAlkuS;
    TILASTOT *ptrT = pAlkuT;

    // jos analyysitulokset jo olemassa, tyhjennetään ja alustetaan uudestaan
    if (ptrT != NULL) {
        for (int i = 1; i <= 10; i++) {
            sanaluokat[i].sanatLkm = 0;
        }
        free(ptrT);
    }

    if ((ptrT = (TILASTOT*)malloc(sizeof(TILASTOT))) == NULL) {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }

    while (ptr != NULL) {

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
    ptrT->sanatLkm = sanatLKM;
    ptrT->kumulPituus = kumulPituus;
    strcpy(ptrT->lyhinSana, lyhinSana);
    strcpy(ptrT->pisinSana, pisinSana);
    strcpy(ptrT->ensimmainenSana, ekaSana);
    strcpy(ptrT->viimeinenSana, vikaSana);

    printf("Analysoitu %d sanaa.\n", sanatLKM);
    printf("Sanaluokittaiset lukumäärät analysoitu.\n");
    free(ptr);

    return ptrT;
}


void kirjoitaTiedosto(char *tiedostonNimi, TILASTOT *ptr, SANALUOKKA sanaluokat[]) {
    FILE *tiedosto;
    
    // kirjoitetaan tiedot näytölle
    tulostaTiedot(stdout, ptr, sanaluokat);


    if ((tiedosto = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // kirjoitetaan tiedot tiedostoon
    tulostaTiedot(tiedosto, ptr, sanaluokat);

    printf("Tiedosto '%s' kirjoitettu.\n", tiedostonNimi);
    fclose(tiedosto);

    return;
}

void tulostaTiedot(FILE *tietoVirta, TILASTOT *ptr, SANALUOKKA sanaluokat[]) {
    // korjaus: fprintf tietovirta voidaan asettaa myös stdout:ksi, jolloin tulostus näytölle
    
    fprintf(tietoVirta, "Tilastotiedot %d sanasta:\n", ptr->sanatLkm);
    fprintf(tietoVirta, "Keskimääräinen sanan pituus on %.1f merkkiä.\n", (float)ptr->kumulPituus/ptr->sanatLkm);
    fprintf(tietoVirta, "Pisin sana '%s' on %lu merkkiä pitkä.\n", ptr->pisinSana, strlen(ptr->pisinSana));
    fprintf(tietoVirta, "Lyhyin sana '%s' on %lu merkkiä pitkä.\n", ptr->lyhinSana, strlen(ptr->lyhinSana));
    fprintf(tietoVirta, "Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", ptr->ensimmainenSana);
    fprintf(tietoVirta, "Aakkosjärjestyksessä viimeinen sana on '%s'.\n", ptr->viimeinenSana);

    fprintf(tietoVirta, "\n");

    fprintf(tietoVirta, "Sanaluokka;Lkm\n");

    for (int i = 1; i <= 10; i++) {
        fprintf(tietoVirta, "Luokka %d;%d\n", i, sanaluokat[i].sanatLkm);
    }

    return;
}

SANAT *tyhjennaSanat(SANAT *pAlku) {
    SANAT *ptr = pAlku;
    
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }

    return NULL;
}


/* eof */