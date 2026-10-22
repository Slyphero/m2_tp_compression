#include "image.h"

/*
 * Lecture d'une ligne du fichier.
 * On saute les lignes commençant par un "#" (commentaire)
 * On simplifie en considérant que les lignes ne dépassent pas MAXLIGNE
 */

void lire_ligne(FILE *f, char *ligne) {
    while (fgets(ligne, MAXLIGNE, f)) {
        if (ligne[0] != '#') {
            return;
        }
    }

    ligne[0] = '\0';
}

/*
 * Allocation d'une image
 */

struct image *allocation_image(int hauteur, int largeur) {
    struct image *img;
    ALLOUER(img, 1);

    img->hauteur = hauteur;
    img->largeur = largeur;

    ALLOUER(img->pixels, hauteur);

    for (int y = 0; y < hauteur; y++) {
        ALLOUER(img->pixels[y], largeur);
    }

    return img;
}

/*
 * Libération image
 */

void liberation_image(struct image *image) {
    for (int y = 0; y < image->hauteur; y++) {
        free(image->pixels[y]);
    }

    free(image->pixels);
    free(image);
}

/*
 * Allocation et lecture d'un image au format PGM.
 * (L'entête commence par "P5\nLargeur Hauteur\n255\n"
 * Avec des lignes de commentaire possibles avant la dernière.
 */

struct image *lecture_image(FILE *f) {
    return 0; /* pour enlever un warning du compilateur */
}

/*
 * Écriture de l'image (toujours au format PGM)
 */

void ecriture_image(FILE *f, const struct image *image) {
}
