#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct element {
    int val;
    struct element *suivant;
} Element;


Element* creerElement(int val);
Element* ajouterFin(Element* L, int val);
Element* remplirListe(Element* L);
void afficherListe(Element* L);
Element* RotationDroite(Element* L, int k);
Element* RotationGauche(Element* L, int k);
int length(Element* L);
Element* RotationBloc(Element* L, int rot, int div);
Element* init(Element* L1, Element* L2);
void vider(Element* L2);

Element* creerElement(int val) {
    Element* nv = malloc(sizeof(Element));
    nv->val = val;
    nv->suivant = NULL;
    return nv;
}

Element* ajouterFin(Element* L, int val) {
    Element* nv = creerElement(val);
    if (L == NULL)
        L = nv;
    else {
        Element* tmp = L;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = nv;
    }
    return L;
}

Element* remplirListe(Element* L) {
    int stop = 999;
    int temp;
    int i = 1;
    printf("*************************SAISIE DE LA LISTE *************************\n");
    printf("Pour arreter la saisie, entrez 999\n");
    while (temp != stop) {
        printf("Element %i: ", i++);
        scanf("%i", &temp);
        if (temp != stop)
            L = ajouterFin(L, temp);
        else
            break;
    }
    return L;
}

void afficherListe(Element* L) {
    while (L->suivant != NULL) {
        printf("%i -> ", L->val);
        L = L->suivant;
    }
    printf("%i", L->val);
}

Element* RotationDroite(Element* L, int k) {
    Element* tmp = L;
    Element* precedant = NULL;
    for (int i = 0; i < k; i++) {
        while (tmp->suivant != NULL) {
            precedant = tmp;
            tmp = tmp->suivant;
        }
        precedant->suivant = NULL;
        tmp->suivant = L;
        L = tmp;
    }
    return L;
}

Element* RotationGauche(Element* L, int k) {
    for (int i = 0; i < k; i++) {
        Element* tmp = L;
        Element* sv = L->suivant;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = L;
        L->suivant = NULL;
        L = sv;
    }
    return L;
}

int length(Element* L) {
    int taille = 0;
    while (L != NULL) {
        taille++;
        L = L->suivant;
    }
    return taille;
}

Element* RotationBloc(Element* L, int rot, int div) {
    int t = length(L);
    if (t < div)
        return L;
    int NB_Listes;
    if (t % div == 0)
        NB_Listes = t / div;
    else
        NB_Listes = (t / div) + 1;

    Element* T[NB_Listes];

    for (int i = 0; i < NB_Listes; i++) {
        T[i] = NULL;
    }
    Element* tmp = L;

    for (int i = 0; i < NB_Listes && tmp != NULL; i++) {
        for (int j = 0; j < div && tmp != NULL; j++) {
            T[i] = ajouterFin(T[i], tmp->val);
            tmp = tmp->suivant;
        }
    }

    for (int i = 0; i < NB_Listes; i++) {
        if (rot > 0)
            T[i] = RotationDroite(T[i], rot);
        else
            T[i] = RotationGauche(T[i], -rot);
    }

    Element* nv = NULL;
    for (int i = 0; i < NB_Listes; i++) {
        Element* tmp = T[i];
        while (tmp != NULL) {
            nv = ajouterFin(nv, tmp->val);
            tmp = tmp->suivant;
        }
    }

    return nv;
}

Element* init(Element* L1, Element* L2) {
    Element* tmp1 = L1;
    Element* tmp2 = L2;

    while (tmp1 != NULL) {
        L2 = ajouterFin(L2, tmp1->val);
        tmp1 = tmp1->suivant;
    }
    return L2;
}

void vider(Element* L2) {
    Element* tmp = NULL;
    while (L2 != NULL) {
        tmp = L2;
        L2 = L2->suivant;
        free(tmp);
    }
}

int main() {
    Element* L = NULL;
    Element* L2 = NULL;
    Element* originalList = NULL;
    int rep1;
    int rep2;
    int k1, k2, k3, D;
    do {
        L = remplirListe(L);
        if (L == NULL) {
            printf("La liste que vous avez saisie est vide, resaisir (0/1) :  ");
            scanf("%i", &rep1);
            if (rep1 == 0) {
                printf("A la prochaine\n");
                exit(0);
            }
        }
        system("cls");
    } while (L == NULL && rep1 == 1);

    originalList = init(L, originalList);

    do {
        system("cls");
        printf("Votre liste initial: ");
        afficherListe(originalList);
        printf("\n");
        printf("Pour la rotation a droite, TAPEZ '1'\nPour la rotation a gauche, TAPEZ '2'\nPour la rotation par blocs, TAPEZ '3'\nPour quitter, TAPEZ '0'\n");
        printf("Votre choix: ");
        do {
            scanf("%i", &rep2);
            if (rep2 != 1 && rep2 != 2 && rep2 != 3 && rep2 != 0)
                printf("Choix incorrect, resaisir :");
        } while (rep2 != 1 && rep2 != 2 && rep2 != 3 && rep2 != 0);
        system("cls");
        switch (rep2) {
            case 0:  printf("A la prochaine\n");
                        exit(0);
            case 1:
                printf("Votre liste initial: ");
                afficherListe(originalList);
                printf("\n");
                printf("Entrer K: ");
                scanf("%i", &k1);
                printf("La liste obtenue: ");
                afficherListe(RotationDroite(init(originalList, L2), abs(k1)));
                printf("\n");
                printf("Voulez vous revenir a la page d'acceuil (1) ou Quitter (2): \n");
                printf("Votre choix : ");
                do {
                    scanf("%i", &k1);
                    if (k1 == 2){
                        system("cls");
                        printf("A la prochaine\n");
                        exit(0);
                    }

                    else if (k1 == 1)
                        break;
                    else
                        printf("Choix incorrect, resaisir :");
                } while (k1 != 1 && k1 != 2);
                break;
            case 2:
                printf("Votre liste initial: ");
                afficherListe(originalList);
                printf("\n");
                printf("Entrer K: ");
                scanf("%i", &k2);
                printf("La liste obtenue: ");
                afficherListe(RotationGauche(init(originalList, L2), abs(k2)));
                printf("\n");
                printf("Voulez vous revenir a la page d'acceuil (1) ou Quitter (2): \n");
                printf("Votre choix : ");
                do {
                    scanf("%i", &k2);
                    if (k2 == 2){
                        system("cls");
                        printf("A la prochaine\n");
                        exit(0);
                        }
                    else if (k2 == 1)
                        break;
                    else
                        printf("Choix incorrect, resaisir :");
                } while (k2 != 1 && k2 != 2);
                break;
            case 3:
                printf("Votre liste initial: ");
                afficherListe(originalList);
                printf("\n");
                printf("Entrer K: ");
                scanf("%i", &k3);
                printf("Entrer D: ");
                scanf("%i", &D);
                printf("La liste obtenue: ");
                afficherListe(RotationBloc(init(originalList, L2), k3, D));
                printf("\n");
                printf("Voulez vous revenir a la page d'acceuil (1) ou Quitter (2): \n");
                printf("Votre choix : ");
                do {
                    scanf("%i", &k3);
                    if (k3 == 2){
                        system("cls");
                        printf("A la prochaine\n");
                        exit(0);
                        }
                    else if (k3 == 1)
                        break ;
                    else
                        printf("Choix incorrect, resaisir :");

                } while (k3 != 1 && k3 != 2);


        }
    } while (k1 == 1 || k2 == 1 || k3 == 1);
    vider(L);
    vider(L2);
    vider(originalList);
    return 0;
}
