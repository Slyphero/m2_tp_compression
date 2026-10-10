#include "matrice.h"
#include "bases.h"
#include "dct.h"

/*
 * La fonction calculant les coefficients de la DCT (et donc de l'inverse)
 * car la matrice de l'inverse DCT est la transposée de la matrice DCT
 *
 * Cette fonction prend beaucoup de temps.
 * il faut que VOUS l'utilisiez le moins possible (UNE SEULE FOIS)
 *
 * FAITES LES CALCULS EN "double"
 *
 * La valeur de Pi est : M_PI
 *
 * Pour ne pas avoir de problèmes dans la suite du TP, indice vos tableau
 * avec [j][i] et non [i][j].
 */

void coef_dct(Matrice *table) {
    int n = table->width;
    double sqrt_n = sqrt((double)n);
    double sqrt_2 = sqrt(2.0);

    for (int i = 0; i < table->width; i++) {
        table->t[0][i] = 1.0 / sqrt_n;
    }

    for (int j = 1; j < table->height; j++) {
        for (int i = 0; i < table->width; i++) {
            table->t[j][i] = (sqrt_2 / sqrt_n) * cos(j * M_PI * ((2.0 * i + 1.0) / (2.0 * n)));
        }
    }
}

/*
 * La fonction calculant la DCT ou son inverse.
 *
 * Cette fonction va être appelée très souvent pour faire
 * la DCT du son ou de l'image (nombreux paquets).
 */

void dct(int inverse,         /* ==0: DCT, !=0 DCT inverse */
         int nbe,             /* Nombre d'échantillons  */
         const float *entree, /* Le son avant transformation (DCT/INVDCT) */
         float *sortie        /* Le son après transformation */
) {
    static Matrice *dct_table, *dct_inverse;

    if (dct_table == NULL) {
        assert(dct_table->width == nbe);
        dct_table = allocation_matrice_float(nbe, nbe);
        coef_dct(dct_table);
        dct_inverse = allocation_matrice_float(nbe, nbe);
        transposition_matrice(dct_table, dct_inverse);
    }

    if (inverse) {
        produit_matrice_vecteur(dct_inverse, entree, sortie);
    } else {
        produit_matrice_vecteur(dct_table, entree, sortie);
    }
}
