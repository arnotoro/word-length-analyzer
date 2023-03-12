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
/* Tehtävä perustason harkkatyö, tiedoston nimi funktiot.h */
#ifndef FUNKTIOT_H_
#define FUNKTIOT_H_
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

int valikko(void);
void kysyTiedostonNimi(char *tiedostonNimi);
SANAT *lueTiedosto(SANAT *pAlku, char *tiedostonNimi);
SANAT *lisaaListaan(SANAT *pAlku, char *rivi);
TILASTOT *analysoiTiedot(SANAT *pAlkuS, TILASTOT *pALkuT);
void kirjoitaTiedosto(char *tiedostonNimi, TILASTOT *ptr);
void tulostaTiedot(FILE *tietoVirta, TILASTOT *ptr);

#endif

/* eof */