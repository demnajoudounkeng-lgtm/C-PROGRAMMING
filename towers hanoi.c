#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int N;
int piles[3][10];
int hauteurs[3];
int nb_mouvements;

void afficher_piles() {
    int niveau, p, i, disque;

    system(CLEAR);
    printf("\n========== TOURS DE HANOI ==========\n\n");

    for (niveau = N - 1; niveau >= 0; niveau--) {
        for (p = 0; p < 3; p++) {
            if (niveau < hauteurs[p])
                disque = piles[p][niveau];
            else
                disque = 0;

            if (disque > 0) {
                for (i = 0; i < N - disque; i++) printf(" ");
                for (i = 0; i < 2 * disque - 1; i++) printf("=");
                for (i = 0; i < N - disque; i++) printf(" ");
            } else {
                for (i = 0; i < N - 1; i++) printf(" ");
                printf("|");
                for (i = 0; i < N - 1; i++) printf(" ");
            }
            printf("     ");
        }
        printf("\n");
    }

    /* Base */
    for (p = 0; p < 3; p++) {
        for (i = 0; i < 2 * N + 1; i++) printf("-");
        printf("     ");
    }
    printf("\n");

    /* Noms piquets */
    for (p = 0; p < 3; p++) {
        for (i = 0; i < N - 1; i++) printf(" ");
        printf("P%d", p + 1);
        for (i = 0; i < N - 1; i++) printf(" ");
        printf("     ");
    }
    printf("\n\n");
    printf("  Mouvements effectues : %d\n", nb_mouvements);
}

int est_gagne() {
    return hauteurs[2] == N;
}

int mouvement_valide(int from, int to) {
    int disque_source, disque_dest;

    if (from < 0 || from > 2 || to < 0 || to > 2) {
        printf("  ERREUR : numero de piquet invalide !\n");
        return 0;
    }
    if (from == to) {
        printf("  ERREUR : source et destination identiques !\n");
        return 0;
    }
    if (hauteurs[from] == 0) {
        printf("  ERREUR : le piquet %d est vide !\n", from + 1);
        return 0;
    }

    disque_source = piles[from][hauteurs[from] - 1];

    if (hauteurs[to] > 0) {
        disque_dest = piles[to][hauteurs[to] - 1];
        if (disque_source > disque_dest) {
            printf("  ERREUR : impossible de poser un grand disque sur un petit !\n");
            return 0;
        }
    }
    return 1;
}

void deplacer(int from, int to) {
    int disque;
    disque = piles[from][hauteurs[from] - 1];
    hauteurs[from]--;
    piles[to][hauteurs[to]] = disque;
    hauteurs[to]++;
    nb_mouvements++;
}

int main() {
    int i, from, to;
    int optimal;

    printf("Entrez le nombre de disques (2 a 7) : ");
    scanf("%d", &N);

    /* Initialisation */
    hauteurs[0] = hauteurs[1] = hauteurs[2] = 0;
    nb_mouvements = 0;
    optimal = (1 << N) - 1;

    for (i = N; i >= 1; i--) {
        piles[0][hauteurs[0]] = i;
        hauteurs[0]++;
    }

    /* Boucle principale */
    while (!est_gagne()) {
        afficher_piles();
        printf("  Objectif : deplacer tous les disques sur P3\n");
        printf("  Mouvements optimaux : %d\n\n", optimal);

        printf("  De quel piquet ? (1, 2 ou 3) : ");
        scanf("%d", &from);
        from--;

        printf("  Vers quel piquet ? (1, 2 ou 3) : ");
        scanf("%d", &to);
        to--;

        if (!mouvement_valide(from, to)) {
            printf("  Appuyez sur ENTREE pour continuer...");
            getchar(); getchar();
        } else {
            deplacer(from, to);
        }
    }

    /* Victoire */
    afficher_piles();
    printf("\n  FELICITATIONS Emma ! Vous avez resolu le puzzle !\n");
    printf("  Vous avez utilise %d mouvements", nb_mouvements);
    if (nb_mouvements == optimal)
        printf(" (OPTIMAL !) \n");
    else
        printf(" (optimal = %d)\n", optimal);

    return 0;
}
   
