#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "plateau.h"

int map(int abscisse, int ordonnee, int cote) {
    if (abscisse < 0 || abscisse >= cote || ordonnee < 0 || ordonnee >= cote) {
        return -1;
    }
    return cote * ordonnee + abscisse;
}

int chercheOrdonnee(Monde *monde, int indice) {
    return indice / monde->plateau->cote;
}

int chercheAbscisse(Monde *monde, int indice) {
    return indice % monde->plateau->cote;
}

int estLibre(Monde *monde, int indice) {
    int nombrecases = monde->plateau->nombrecases;

    if (indice < 0 || indice > nombrecases - 1) return -1;

    if (monde->plateau->cases[indice].fourmi != NULL) {
        return 0;
    }
    return 1;
}

void affichePlateau(Plateau *plateau) {
    int largeur, hauteur;
    int couleur;

    for (largeur = 0; largeur < plateau->cote; largeur++) {
        printf(" %d   ", largeur);
    }

    printf("\n");
    for (hauteur = 0; hauteur < plateau->cote; hauteur++) {
        for (largeur = 0; largeur < plateau->cote; largeur++) {

            if (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi == NULL) {
                printf("    ");
            } else {
                couleur = (int) plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi->couleur;
                switch (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi->type) {
                    case FOURMILIERE:
                        if (!couleur) printf(" Fr ");
                        else printf(" Fn ");
                        break;
                    case SOLDAT:
                        if (!couleur) printf(" Sr ");
                        else printf(" Sn ");
                        break;
                    case OUVRIERE:
                        if (!couleur) printf(" Or ");
                        else printf(" On ");
                        break;
                    case REINE:
                        if (!couleur) printf(" Rr ");
                        else printf(" Rn ");
                        break;
                    default:
                        break;
                }
            }
            printf("|");
        }
        printf(" %d\n\n", hauteur);
    }
}

int chercheLibre(Monde *monde, int centre) {

    int cote = monde->plateau->cote;
    int rayon;
    int haut, droite, bas, gauche, ligne;
    int ordonnee = chercheOrdonnee(monde, centre);
    int abscisse = chercheAbscisse(monde, centre);

    for (rayon = 1; rayon < cote; rayon++) {

        //haut
        for (haut = centre - rayon * cote + rayon; haut >= centre - rayon * cote - rayon; haut--) {
            ligne = ordonnee - rayon;
            if (haut < ligne * cote || haut >= (ligne + 1) * cote || !ordonnee) continue;
            if (estLibre(monde, haut)) {
                return haut;
            }
        }

        //gauche
        for (gauche = centre - (rayon - 1) * cote - rayon; gauche <= centre + (rayon - 1) * cote - rayon; gauche += cote) {
            if (!abscisse) continue;
            if (estLibre(monde, gauche)) {
                return gauche;
            }
        }

        //bas
        for (bas = centre + rayon * cote - rayon; bas <= centre + rayon * cote + rayon; bas++) {
            ligne = ordonnee + rayon;
            if (bas < ligne * cote || bas >= (ligne + 1) * cote || ordonnee == cote) continue;
            if (estLibre(monde, bas)) {
                return bas;
            }
        }

        //droite
        for (droite = centre + rayon * cote + rayon; droite >= centre - (rayon - 1) * cote + rayon; droite -= cote) {
            if (abscisse == cote - 1) continue;
            if (estLibre(monde, droite)) {
                return droite;
            }
        }
    }
    return -1;
}

