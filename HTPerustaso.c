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
/* Tehtävä perustason harkkatyö, tiedoston nimi HTPerustaso.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HTPerusKirjasto.h"

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
            if (pAlku == NULL) {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            } else {
                ptr = analysoiTiedot(pAlku, ptr);
            }
        } 
        else if (valinta == 3) {
            if (ptr == NULL) {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            } else {
                kysyTiedostonNimi(tiedostonNimi);
                kirjoitaTiedosto(tiedostonNimi, ptr);
            }
        }
        else if (valinta == 0) {
            pAlku = tyhjennaSanat(pAlku);
            free(ptr);
            printf("Lopetetaan.\n");
        } 
        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }

        printf("\n");
    } while (valinta != 0);


    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

/* eof */