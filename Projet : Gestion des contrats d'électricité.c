#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_FOURNISSEURS 100
#define MAX_CENTRES_PRODUCTION 100
#define MAX_REGIONS_DISTRIBUTION 10

#define MAX_REGIONS 5
#define MAX_REGION_DISTRIBUTION 3
#define MAX_SOURCES_ENERGIE 5
#define MAX_NOM_LENGTH 30
#define MAX_CLIENTS 100

// Structure pour les regions de distribution
typedef struct {
    char nom[MAX_NOM_LENGTH + 1];
} RegionDistribution;

// Structure pour les centres de production
typedef struct {
    char code[10];
    char nom[MAX_NOM_LENGTH + 1];
    char region[MAX_NOM_LENGTH + 1];
    RegionDistribution regionsDistribution[MAX_REGIONS_DISTRIBUTION];
    int nombreRegionsDistribution;
    float chargeAnnuelle;
    char typeEnergie[MAX_NOM_LENGTH + 1];
} CentreProduction;

// Structure pour les abonnements
typedef struct {
    char typeAbonnement[10]; 
    float puissanceSouscrite;
    int duree;
    float prixKwhHT;
} Abonnement;

// Structure pour les clients
typedef struct {
    char nom[MAX_NOM_LENGTH + 1];
    char code[10];
    char region[MAX_NOM_LENGTH + 1];
    float consommationAnuelle;
    int dureeContrat;
} Client;

// Structure pour les fournisseurs
typedef struct {
    char nom[MAX_NOM_LENGTH + 1];
    char code[10];
    CentreProduction centresProduction[MAX_CENTRES_PRODUCTION];
    int nombreCentresProduction;
    Abonnement abonnement; 
    Client clients[MAX_CLIENTS];
    int nombreClients;
} Fournisseur;

// Tableau pour stocker les fournisseurs
Fournisseur fournisseurs[MAX_FOURNISSEURS];
int nombreFournisseurs = 0;
Client clients[MAX_CLIENTS];
int nombreClients = 0;


// Tableaux predefinis des regions et des regions de distribution
char regions[MAX_REGIONS][MAX_NOM_LENGTH + 1] = {"Zerzis", "Ain Draham", "Mahdia", "Bizerte", "Kasserine"};
char regionsDistribution[MAX_REGIONS][MAX_REGION_DISTRIBUTION][MAX_NOM_LENGTH + 1] = {
    {"Jerba", "Medenine", "Gabes"},
    {"Beja", "Kef", "Siliana"},
    {"Monastir", "Sousse", "Sfax"},
    {"Tunis", "Ben Arous", "Manouba"},
    {"Gafsa", "Sidi-Bouzid", "Hajeb el Ayoun"}
};

// Tableaux predefinis des sources d'energie
char sourcesEnergie[MAX_SOURCES_ENERGIE][MAX_NOM_LENGTH + 1] = {"Hydrolique", "Solaire", "Eolienne", "Nucleaire", "Fossile"};

// Verifie si une chaine est alphabetique et ne depasse pas 30 caracteres
int nomValide(char nom[]) {
    if (strlen(nom) > MAX_NOM_LENGTH) {
        return 0;
    }
    for (int i = 0; i < strlen(nom); ++i) {
        if (!isalpha(nom[i])) {
            return 0;
        }
    }
    return 1;
}

// Verifie si le code du fournisseur existe deja
int codeExiste(char code[]) {
    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (strcmp(fournisseurs[i].code, code) == 0) {
            return 1;
        }
    }
    return 0;
}

// Ajouter un centre de production a un fournisseur existant
void ajouterCentreProduction(Fournisseur *fournisseur) {
    if (fournisseur->nombreCentresProduction >= MAX_CENTRES_PRODUCTION) {
        printf("Erreur : Nombre maximal de centres de production atteint.\n");
        return;
    }

    CentreProduction *nouveauCentre = &fournisseur->centresProduction[fournisseur->nombreCentresProduction];

    printf("Ajout d'un nouveau centre de production pour le fournisseur %s\n", fournisseur->nom);
    printf("  - Entrez le nom du centre de production (30 caracteres alphabetiques au maximum) : ");
    scanf("%s", nouveauCentre->nom);
    if (!nomValide(nouveauCentre->nom)) {
        printf("Erreur : Le nom doit etre alphabetique et contenir au maximum 30 caracteres.\n");
        return;
    }
    nouveauCentre->nombreRegionsDistribution = 0;

    printf("  - Entrez le code du centre de production (unique) : ");
    scanf("%s", nouveauCentre->code);

    printf("  - Choisissez la region du centre de production parmi les options suivantes :\n");
    for (int i = 0; i < MAX_REGIONS; ++i) {
        printf("    %d. %s\n", i + 1, regions[i]);
    }
    int choixRegion;
    printf("  - Entrez le numero de la region : ");
    scanf("%d", &choixRegion);

    if (choixRegion < 1 || choixRegion > MAX_REGIONS) {
        printf("Erreur : Region invalide.\n");
        return;
    }
    strcpy(nouveauCentre->region, regions[choixRegion - 1]);

    printf("  - Entrez la charge annuelle du centre de production : ");
    scanf("%f", &nouveauCentre->chargeAnnuelle);

    printf("  - Choisissez le type d'energie parmi les options suivantes :\n");
    for (int m = 0; m < MAX_SOURCES_ENERGIE; ++m) {
        printf("    %d. %s\n", m + 1, sourcesEnergie[m]);
    }
    int choixEnergie;
    printf("  - Entrez le numero du type d'energie : ");
    scanf("%d", &choixEnergie);

    if (choixEnergie < 1 || choixEnergie > MAX_SOURCES_ENERGIE) {
        printf("Erreur : Type d'energie invalide.\n");
        return;
    }
    strcpy(nouveauCentre->typeEnergie, sourcesEnergie[choixEnergie - 1]);

    printf("Combien de regions de distribution voulez-vous ajouter pour ce centre de production ? (maximum %d): ", MAX_REGIONS_DISTRIBUTION);
    int nbRegions;
    scanf("%d", &nbRegions);

    if (nbRegions > 0 && nbRegions <= MAX_REGIONS_DISTRIBUTION) {
        for (int k = 0; k < nbRegions; ++k) {
            printf("Choisissez la region de distribution %d parmi les options suivantes :\n", k + 1);
            for (int j = 0; j < MAX_REGION_DISTRIBUTION; ++j) {
                printf("    %d. %s\n", j + 1, regionsDistribution[choixRegion - 1][j]);
            }
            int choixRegionDist;
            printf("  - Entrez le numero de la region de distribution : ");
            scanf("%d", &choixRegionDist);

            if (choixRegionDist < 1 || choixRegionDist > MAX_REGION_DISTRIBUTION) {
                printf("Erreur : Region de distribution invalide.\n");
                return;
            }
            strcpy(nouveauCentre->regionsDistribution[k].nom, regionsDistribution[choixRegion - 1][choixRegionDist - 1]);
            nouveauCentre->nombreRegionsDistribution++;
        }
    } else {
        printf("Erreur : Le nombre de regions de distribution doit etre compris entre 1 et %d.\n", MAX_REGIONS_DISTRIBUTION);
        return;
    }

    fournisseur->nombreCentresProduction++;
}


// Afficher les options de r�gion de production pour la modification
void afficherOptionsRegionsProductionModification() {
    printf("Choisissez la nouvelle region du centre de production parmi les options suivantes :\n");
    for (int i = 0; i < MAX_REGIONS; ++i) {
        printf("    %d. %s\n", i + 1, regions[i]);
    }
}

// R�cup�rer la s�lection de l'utilisateur pour la r�gion de production lors de la modification
int choisirRegionProductionModification() {
    int choixRegion;
    afficherOptionsRegionsProductionModification();
    printf("Entrez le numero de la nouvelle region : ");
    scanf("%d", &choixRegion);
    return choixRegion;
}

// Afficher les options de r�gion de distribution pour la modification
void afficherOptionsRegionsDistributionModification(int regionProduction) {
    printf("Choisissez la nouvelle region de distribution parmi les options suivantes :\n");
    for (int i = 0; i < MAX_REGION_DISTRIBUTION; ++i) {
        printf("    %d. %s\n", i + 1, regionsDistribution[regionProduction - 1][i]);
    }
}

// R�cup�rer la s�lection de l'utilisateur pour la r�gion de distribution lors de la modification
int choisirRegionDistributionModification(int regionProduction) {
    int choixRegionDist;
    afficherOptionsRegionsDistributionModification(regionProduction);
    printf("Entrez le numero de la nouvelle region de distribution : ");
    scanf("%d", &choixRegionDist);
    return choixRegionDist;
}

// Afficher les options de types d'�nergie pour la modification
void afficherOptionsTypesEnergieModification() {
    printf("Choisissez le nouveau type d'energie parmi les options suivantes :\n");
    for (int i = 0; i < MAX_SOURCES_ENERGIE; ++i) {
        printf("    %d. %s\n", i + 1, sourcesEnergie[i]);
    }
}

// R�cup�rer la s�lection de l'utilisateur pour le type d'�nergie lors de la modification
int choisirTypeEnergieModification() {
    int choixEnergie;
    afficherOptionsTypesEnergieModification();
    printf("Entrez le numero du nouveau type d'energie : ");
    scanf("%d", &choixEnergie);
    return choixEnergie;
}



void modifierCentreProduction() {
    char codeCentre[10];
    printf("Entrez le code du centre de production a modifier : ");
    scanf("%s", codeCentre);

    int found = 0;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        for (int j = 0; j < fournisseurs[i].nombreCentresProduction; ++j) {
            if (strcmp(fournisseurs[i].centresProduction[j].code, codeCentre) == 0) {
                CentreProduction *centre = &fournisseurs[i].centresProduction[j];

                printf("Entrez le nouveau nom du centre de production : ");
                scanf("%s", centre->nom);

                printf("Choisissez la nouvelle region du centre de production :\n");
                int choixRegionProductionModification = choisirRegionProductionModification();
                strcpy(centre->region, regions[choixRegionProductionModification - 1]);

                printf("Combien de regions de distribution voulez-vous ajouter pour ce centre de production ? (maximum %d): ", MAX_REGIONS_DISTRIBUTION);
                int nbRegions;
                scanf("%d", &nbRegions);

                if (nbRegions > 0 && nbRegions <= MAX_REGIONS_DISTRIBUTION) {
                    for (int k = 0; k < nbRegions; ++k) {
                        printf("Choisissez la nouvelle region de distribution %d :\n", k + 1);
                        int choixRegionDistModification = choisirRegionDistributionModification(choixRegionProductionModification);
                        strcpy(centre->regionsDistribution[k].nom, regionsDistribution[choixRegionProductionModification - 1][choixRegionDistModification - 1]);
                        centre->nombreRegionsDistribution++;
                    }
                } else {
                    printf("Erreur : Le nombre de regions de distribution doit etre compris entre 1 et %d.\n", MAX_REGIONS_DISTRIBUTION);
                    return;
                }


                printf("Entrez la nouvelle charge annuelle du centre de production : ");
                scanf("%f", &centre->chargeAnnuelle);

                printf("Choisissez le nouveau type d'energie :\n");
                int choixEnergieModification = choisirTypeEnergieModification();
                strcpy(centre->typeEnergie, sourcesEnergie[choixEnergieModification - 1]);

                printf("Centre de production modifie avec succes.\n");
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("Erreur : Aucun centre de production avec ce code.\n");
    }
}

// Supprimer un centre de production pour un fournisseur donn�
void supprimerCentreProduction() {

    char codeCentre[10];
    printf("Entrez le code du centre de production a supprimer : ");
    scanf("%s", codeCentre);

    int found = 0;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        for (int j = 0; j < fournisseurs[i].nombreCentresProduction; ++j) {
            if (strcmp(fournisseurs[i].centresProduction[j].code, codeCentre) == 0) {
                for (int k = j; k < fournisseurs[i].nombreCentresProduction - 1; ++k) {
                    fournisseurs[i].centresProduction[k] = fournisseurs[i].centresProduction[k + 1];
                }
                fournisseurs[i].nombreCentresProduction--;
                printf("Centre de production supprime avec succes.\n");
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("Erreur : Aucun centre de production avec ce code.\n");
    }
}




// Ajouter un fournisseur
void ajouterFournisseur() {
    Fournisseur nouveauFournisseur;
    nouveauFournisseur.nombreCentresProduction = 0;
    printf("Entrez le nom du fournisseur (30 caracteres alphabetiques au maximum) : ");
    scanf("%s", nouveauFournisseur.nom);
    if (!nomValide(nouveauFournisseur.nom)) {
        printf("Erreur : Le nom doit etre alphabetique et contenir au maximum 30 caracteres.\n");
        return;
    }

    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (strcmp(fournisseurs[i].nom, nouveauFournisseur.nom) == 0) {
            printf("Erreur : Le nom du fournisseur existe deja.\n");
            return;
        }
    }

    printf("Entrez le code du fournisseur (unique) : ");
    scanf("%s", nouveauFournisseur.code);

    // Verifier l'unicite du code
    if (codeExiste(nouveauFournisseur.code)) {
        printf("Erreur : Le code du fournisseur existe deja.\n");
        return;
    }

    printf("Combien de centres de production voulez-vous ajouter pour ce fournisseur ? : ");
    int nbCentres;
    scanf("%d", &nbCentres);

    if (nbCentres > 0 && nbCentres <= MAX_CENTRES_PRODUCTION) {
        for (int j = 0; j < nbCentres; ++j) {
            CentreProduction nouveauCentre;
            printf("Centre de production %d :\n", j + 1);
            printf("  - Entrez le nom du centre de production (30 caracteres alphabetiques au maximum) : ");
            scanf("%s", nouveauCentre.nom);
            if (!nomValide(nouveauCentre.nom)) {
                printf("Erreur : Le nom doit etre alphabetique et contenir au maximum 30 caracteres.\n");
                return;
            }

            printf("  - Entrez le code du centre de production (unique) : ");
            scanf("%s", nouveauCentre.code);

            printf("  - Choisissez la region du centre de production parmi les options suivantes :\n");
            for (int k = 0; k < MAX_REGIONS; ++k) {
                printf("    %d. %s\n", k + 1, regions[k]);
            }
            int choixRegion;
            printf("  - Entrez le numero de la region : ");
            scanf("%d", &choixRegion);

            if (choixRegion < 1 || choixRegion > MAX_REGIONS) {
                printf("Erreur : Region invalide.\n");
                return;
            }
            strcpy(nouveauCentre.region, regions[choixRegion - 1]);

            printf("  - Entrez la charge annuelle maximal du centre de production : ");
            scanf("%f", &nouveauCentre.chargeAnnuelle);

            printf("  - Choisissez le type d'energie parmi les options suivantes :\n");
            for (int l = 0; l < MAX_SOURCES_ENERGIE; ++l) {
                printf("    %d. %s\n", l + 1, sourcesEnergie[l]);
            }
            int choixEnergie;
            printf("  - Entrez le numero du type d'energie : ");
            scanf("%d", &choixEnergie);

            if (choixEnergie < 1 || choixEnergie > MAX_SOURCES_ENERGIE) {
                printf("Erreur : Type d'energie invalide.\n");
                return;
            }
            strcpy(nouveauCentre.typeEnergie, sourcesEnergie[choixEnergie - 1]);

            printf("Combien de regions de distribution voulez-vous ajouter pour ce centre de production ? (maximum %d): ", MAX_REGIONS_DISTRIBUTION);
            int nbRegions;
            scanf("%d", &nbRegions);

            if (nbRegions > 0 && nbRegions <= MAX_REGIONS_DISTRIBUTION) {
                for (int m = 0; m < nbRegions; ++m) {
                    printf("Choisissez la region de distribution %d parmi les options suivantes :\n", m + 1);
                    for (int n = 0; n < MAX_REGION_DISTRIBUTION; ++n) {
                        printf("    %d. %s\n", n + 1, regionsDistribution[choixRegion - 1][n]);
                    }
                    int choixRegionDist;
                    printf("  - Entrez le numero de la region de distribution : ");
                    scanf("%d", &choixRegionDist);

                    if (choixRegionDist < 1 || choixRegionDist > MAX_REGION_DISTRIBUTION) {
                        printf("Erreur : Region de distribution invalide.\n");
                        return;
                    }
                    strcpy(nouveauCentre.regionsDistribution[m].nom, regionsDistribution[choixRegion - 1][choixRegionDist - 1]);
                    nouveauCentre.nombreRegionsDistribution++;
                }
                printf("Entrez le type d'abonnement : ");
                scanf("%s", nouveauFournisseur.abonnement.typeAbonnement);

                printf("Entrez la puissance souscrite (kVA) : ");
                scanf("%f", &nouveauFournisseur.abonnement.puissanceSouscrite);

                printf("Entrez la duree de l'abonnement (en annees) : ");
                scanf("%d", &nouveauFournisseur.abonnement.duree);

                printf("Entrez le prix du kWh HT : ");
                scanf("%f", &nouveauFournisseur.abonnement.prixKwhHT);
            } else {
                printf("Erreur : Le nombre de regions de distribution doit etre compris entre 1 et %d.\n", MAX_REGIONS_DISTRIBUTION);
                return;
            }

            for (int y = 0; y < nombreFournisseurs; ++y) {
                for (int x = 0; x < fournisseurs[x].nombreCentresProduction; ++x) {
                    if (strcmp(nouveauCentre.code, fournisseurs[y].centresProduction[x].code) == 0) {
                        printf("Erreur : Le code du centre de production existe deja pour un autre fournisseur.\n");
                        return;
                    }
                }
            }

            nouveauFournisseur.centresProduction[j] = nouveauCentre;
            nouveauFournisseur.nombreCentresProduction++;
        }
    } else {
        printf("Erreur : Le nombre de centres de production doit etre compris entre 1 et %d.\n", MAX_CENTRES_PRODUCTION);
        return;
    }

    fournisseurs[nombreFournisseurs++] = nouveauFournisseur;
    printf("Fournisseur ajoute avec succes.\n");
}

void modifierAbonnement() {
    if (nombreFournisseurs == 0) {
        printf("Aucun fournisseur disponible.\n");
        return;
    }

    char code[10];
    printf("Entrez le code du fournisseur pour modifier l'abonnement : ");
    scanf("%s", code);

    int index = -1;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (strcmp(fournisseurs[i].code, code) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Erreur : Aucun fournisseur avec ce code.\n");
        return;
    }

    Fournisseur *fournisseur = &fournisseurs[index];

    printf("Entrez le nouveau type d'abonnement : ");
    scanf("%s", fournisseur->abonnement.typeAbonnement);

    printf("Entrez la nouvelle puissance souscrite (kVA) : ");
    scanf("%f", &fournisseur->abonnement.puissanceSouscrite);

    printf("Entrez la nouvelle duree de l'abonnement (en annee) : ");
    scanf("%d", &fournisseur->abonnement.duree);

    printf("Entrez le nouveau prix du kWh HT : ");
    scanf("%f", &fournisseur->abonnement.prixKwhHT);

    printf("Abonnement modifie avec succes.\n");
}

void supprimerAbonnement() {
    if (nombreFournisseurs == 0) {
        printf("Aucun fournisseur disponible.\n");
        return;
    }

    char code[10];
    printf("Entrez le code du fournisseur pour supprimer l'abonnement : ");
    scanf("%s", code);

    int index = -1;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (strcmp(fournisseurs[i].code, code) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Erreur : Aucun fournisseur avec ce code.\n");
        return;
    }

    Fournisseur *fournisseur = &fournisseurs[index];

    strcpy(fournisseur->abonnement.typeAbonnement, "");
    fournisseur->abonnement.puissanceSouscrite = 0.0;
    fournisseur->abonnement.duree = 0;
    fournisseur->abonnement.prixKwhHT = 0.0;

    printf("Abonnement supprime avec succes.\n");
}


// Supprimer un fournisseur
void supprimerFournisseur() {
    if (nombreFournisseurs == 0) {
        printf("Aucun fournisseur disponible.\n");
        return;
    }
    char code[10];
    printf("Entrez le code du fournisseur a supprimer : ");
    scanf("%s", code);

    int index = -1;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (strcmp(fournisseurs[i].code, code) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Erreur : Aucun fournisseur avec ce code.\n");
        return;
    }

    for (int i = index; i < nombreFournisseurs - 1; ++i) {
        fournisseurs[i] = fournisseurs[i + 1];
    }

    nombreFournisseurs--;
    printf("Fournisseur supprime avec succes.\n");
}

// Afficher la liste des fournisseurs
void afficherFournisseurs() {
    if (nombreFournisseurs == 0) {
        printf("Aucun fournisseur disponible.\n");
        return;
    }

    for (int i = 0; i < nombreFournisseurs; ++i) {
        printf("Fournisseur %d :\n", i + 1);
        printf("- Nom : %s\n", fournisseurs[i].nom);
        printf("- Code : %s\n", fournisseurs[i].code);
        printf("Nombre de centres de production : %d\n", fournisseurs[i].nombreCentresProduction);
        for (int j = 0; j < fournisseurs[i].nombreCentresProduction; ++j) {
            CentreProduction *cp = &fournisseurs[i].centresProduction[j];
            printf("Centre de production %d :\n", j + 1);
            printf("- Nom : %s\n", cp->nom);
            printf("- Code : %s\n", cp->code);
            printf("- Region : %s\n", cp->region);
            printf("- Charge annuelle : %.2f\n", cp->chargeAnnuelle);
            printf("- Type d'energie : %s\n", cp->typeEnergie);
            printf("- Nombre de regions de distribution : %d\n", cp->nombreRegionsDistribution);
            for (int k = 0; k < cp->nombreRegionsDistribution; ++k) {
                if (strlen(cp->regionsDistribution[k].nom) > 0) {
                    printf("- Region de distribution %d : %s\n", k + 1, cp->regionsDistribution[k].nom);
                }
            }
        }


    }
}


// Fonction pour v�rifier si le code client est unique
int estCodeClientUnique(char *code) {
    for (int i = 0; i < nombreClients; i++) {
        if (strcmp(clients[i].code, code) == 0) {
            return 0;
        }
    }
    return 1;
}



// Fonction pour afficher les d�tails de tous les abonnements des fournisseurs
void afficherAbonnementsTousFournisseurs() {
    printf("\nD�tails des abonnements de tous les fournisseurs:\n");
    for (int i = 0; i < nombreFournisseurs; i++) {
        printf("Fournisseur: %s\n", fournisseurs[i].nom);
        printf("  Code: %s\n", fournisseurs[i].code);
        printf("  Type d'abonnement: %s\n", fournisseurs[i].abonnement.typeAbonnement);
        printf("  Puissance souscrite: %.2f kVA\n", fournisseurs[i].abonnement.puissanceSouscrite);
        printf("  Dur�e de l'abonnement: %d mois\n", fournisseurs[i].abonnement.duree);
        printf("  Prix du kWh HT: %.2f\n", fournisseurs[i].abonnement.prixKwhHT);
        printf("\n");
    }
}

int estRegionValide(const char* region) {
    for (int i = 0; i < nombreFournisseurs; i++) {
        for (int j = 0; j < fournisseurs[i].nombreCentresProduction; j++) {
            for (int k = 0; k < fournisseurs[i].centresProduction[j].nombreRegionsDistribution; k++) {
                if (strcmp(fournisseurs[i].centresProduction[j].regionsDistribution[k].nom, region) == 0) {
                    return 1; // La r�gion est valide
                }
            }
        }
    }
    return 0;
}

// Fonctions d'affichage des fournisseurs dans une r�gion
void afficherFournisseursDansRegion(const char* region) {
    int found = 0;
    printf("Fournisseurs dans la region %s:\n", region);
    for (int i = 0; i < nombreFournisseurs; i++) {
        for (int j = 0; j < fournisseurs[i].nombreCentresProduction; j++) {
            for (int k = 0; k < fournisseurs[i].centresProduction[j].nombreRegionsDistribution; k++) {
                if (strcmp(fournisseurs[i].centresProduction[j].regionsDistribution[k].nom, region) == 0) {
                    printf("  - %s (Code: %s)\n", fournisseurs[i].nom, fournisseurs[i].code);
                    found = 1;
                    break;
                }
            }
        }
    }
    if (!found) {
        printf("Aucun fournisseur trouve dans cette region.\n");
    }
}


// Fonction pour v�rifier si un code client existe d�j�
int codeClientExiste(char code[]) {
    for (int i = 0; i < nombreClients; ++i) {
        if (strcmp(clients[i].code, code) == 0) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour v�rifier si un fournisseur a un centre de production dans la r�gion donn�e
int fournisseurACentreDansRegion(Fournisseur *fournisseur, char region[]) {
    for (int i = 0; i < fournisseur->nombreCentresProduction; ++i) {
        for (int j = 0; j < fournisseur->centresProduction[i].nombreRegionsDistribution; ++j) {
            if (strcmp(fournisseur->centresProduction[i].regionsDistribution[j].nom, region) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void ajouterClient() {
    if (nombreFournisseurs == 0) {
        printf("Aucun client disponible.\n");
        return;
    }
    if (nombreClients >= MAX_CLIENTS) {
        printf("Erreur : Nombre maximal de clients atteint.\n");
        return;
    }

    Client nouveauClient;
    printf("Entrez le nom du client (30 caracteres alphabetiques au maximum) : ");
    scanf("%s", nouveauClient.nom);
    if (!nomValide(nouveauClient.nom)) {
        printf("Erreur : Le nom doit etre alphabetique et contenir au maximum 30 caracteres.\n");
        return;
    }

    printf("Entrez le code unique du client : ");
    scanf("%s", nouveauClient.code);
    if (codeClientExiste(nouveauClient.code)) {
        printf("Erreur : Un client avec ce code existe deja.\n");
        return;
    }

    printf("Entrez la region du client : ");
    scanf("%s", nouveauClient.region);

    // Affichage de la liste des fournisseurs qui ont un centre de production dans la r�gion du client
    printf("Liste des fournisseurs dans la region %s et leurs abonnements :\n", nouveauClient.region);
    int fournisseurTrouve = 0;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (fournisseurACentreDansRegion(&fournisseurs[i], nouveauClient.region)) {
            fournisseurTrouve = 1;
            printf("Fournisseur %d : %s, (code : %s)\n", i + 1, fournisseurs[i].nom, fournisseurs[i].code);
            printf("  - Type d'abonnement : %s\n", fournisseurs[i].abonnement.typeAbonnement);
            printf("  - Puissance souscrite : %.2f kVA\n", fournisseurs[i].abonnement.puissanceSouscrite);
            printf("  - Duree : %d annees\n", fournisseurs[i].abonnement.duree);
            printf("  - Prix du kWh HT : %.2f\n", fournisseurs[i].abonnement.prixKwhHT);
        }
    }

    if (!fournisseurTrouve) {
        printf("Aucun fournisseur trouve dans la region %s.\n", nouveauClient.region);
        return;
    }

    printf("Entrez la consommation Anuelle (kWh) du client : ");
    scanf("%f", &nouveauClient.consommationAnuelle);

    char typeAbonnement[30];
    printf("Entrez le type d'abonnement choisi : ");
    scanf("%s", typeAbonnement);

    int fournisseurChoisiIndex = -1;
    for (int i = 0; i < nombreFournisseurs; ++i) {
        if (fournisseurACentreDansRegion(&fournisseurs[i], nouveauClient.region) &&
            strcmp(fournisseurs[i].abonnement.typeAbonnement, typeAbonnement) == 0) {
            fournisseurChoisiIndex = i;
            break;
        }
    }

    if (fournisseurChoisiIndex == -1) {
        printf("Erreur : Aucun fournisseur avec le type d'abonnement '%s' trouve dans la region %s.\n", typeAbonnement, nouveauClient.region);
        return;
    }

    clients[nombreClients] = nouveauClient;
    nombreClients++;

    printf("Client ajoute avec succes.\n");
}






void afficherClient() {
    if (nombreFournisseurs == 0) {
        printf("Aucun client disponible.\n");
        return;
    }
    if (nombreClients == 0) {
        printf("Aucun client disponible.\n");
        return;
    }

    char codeClient[10];
    printf("Entrez le code du client a afficher : ");
    scanf("%s", codeClient);

    for (int i = 0; i < nombreClients; ++i) {
        if (strcmp(clients[i].code, codeClient) == 0) {
            Client client = clients[i];
            printf("Details du client:\n");
            printf("  Nom: %s\n", client.nom);
            printf("  Code: %s\n", client.code);
            printf("  Region: %s\n", client.region);
            printf("  Consommation anuelle: %.2f kWh\n", client.consommationAnuelle);
            //l'estimation : estimation = nombre d'annees dans l'abonnement  * Prix du kWh HT * consomation anuelle

            for (int j = 0; j < nombreFournisseurs; ++j) {
                for (int k = 0; k < fournisseurs[j].nombreClients; ++k) {
                        Fournisseur fournisseur = fournisseurs[j];
                        Abonnement abonnement = fournisseur.abonnement;
                        printf("Details de l'abonnement : \n");
                        printf("  Fournisseur : (%s)\n", fournisseur.nom);
                        printf("  Type d'abonnement: %s\n", abonnement.typeAbonnement);
                        printf("    Puissance souscrite: %.2f kVA\n", abonnement.puissanceSouscrite);
                        printf("    Duree de l'abonnement: %d annees\n", abonnement.duree);
                        printf("    Prix du kWh HT: %.2f\n", abonnement.prixKwhHT);
                        double estimation = abonnement.duree * abonnement.prixKwhHT * client.consommationAnuelle;
                        printf("  Estimation du cout annuel en Dinars: %.2f\n", estimation);
                        return;
                    }
                }

            printf("Erreur: Fournisseur associe non trouve.\n");
            return;
        }
    }
    printf("Erreur: Client non trouve.\n");
}








// Fonction principale
int main() {
    int choix;
    do {
        printf("\nMenu :\n");
        printf("1. Ajouter un fournisseur\n");
        printf("2. Supprimer un fournisseur\n");
        printf("3. Afficher la liste des fournisseurs\n");
        printf("4. Ajouter un centre de production pour un fournisseur existant\n");
        printf("5. Modifier un centre de production\n");
        printf("6. Supprimer un centre de production\n");
        printf("7. Modifier un abonnement pour un fournisseur\n");
        printf("8. Supprimer un abonnement pour un fournisseur\n");
        printf("9. Ajouter un client\n");
        printf("10. Afficher un client\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajouterFournisseur();
                break;
            case 2:
                supprimerFournisseur();
                break;
            case 3:
                afficherFournisseurs();
                break;
            case 4:
                {
                char codeFournisseur[10];
                printf("Entrez le code du fournisseur : ");
                scanf("%s", codeFournisseur);

                int found = 0;
                for (int i = 0; i < nombreFournisseurs; ++i) {
                    if (strcmp(fournisseurs[i].code, codeFournisseur) == 0) {
                        ajouterCentreProduction(&fournisseurs[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Erreur : Fournisseur non trouv�.\n");
                }
                break;}
            case 5:
                modifierCentreProduction();
                break;
            case 6:
                supprimerCentreProduction();
                break;
            case 7:
                modifierAbonnement();
                break;
            case 8:
                supprimerAbonnement();
                break;
            case 9:
                ajouterClient();
                break;
            case 10:
                afficherClient();
                break;
            case 0:
                printf("Programme termin�.\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choix != 0);
    return 0;
}
