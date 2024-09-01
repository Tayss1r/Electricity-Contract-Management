
# Gestion des contrats d'électricité

## Description

Ce projet est une application en langage C qui vise à gérer efficacement les centres de production d'énergie, les régions de distribution ainsi que les abonnements des clients. Le programme est conçu pour gérer plusieurs centres de production répartis sur différentes régions, chaque centre de production ayant un type d'énergie spécifique, et une capacité annuelle. Les clients peuvent s'abonner à différents types de contrats avec des puissances souscrites et des durées variées.

### Objectifs du projet :
- Faciliter la gestion des centres de production d'énergie
- Assurer une distribution optimale dans les différentes régions
- Gérer efficacement les abonnements des clients pour chaque centre de production

## Fonctionnalités

1. **Gestion des Centres de Production** :
    - Créer, mettre à jour et supprimer des centres de production.
    - Associer chaque centre à un ou plusieurs types de sources d'énergie.
    - Suivre la charge annuelle de chaque centre et les régions qu’il dessert.

2. **Gestion des Régions de Distribution** :
    - Définir des régions et assigner des centres de production à ces régions.
    - Suivre les régions distribuées par chaque centre de production.

3. **Gestion des Abonnements des Clients** :
    - Enregistrer les abonnements clients en fonction du type d’abonnement, de la puissance souscrite, de la durée du contrat, et du prix par kWh.
    - Suivre et calculer les coûts liés à la consommation d'énergie.

4. **Gestion des Clients** :
    - Ajouter, modifier et supprimer des clients.
    - Associer chaque client à un abonnement spécifique.

## Installation

Pour installer et exécuter ce projet, suivez les étapes ci-dessous :

1. **Clonez le dépôt GitHub** :
    ```bash
    git clone https://github.com/votre_nom_utilisateur/nom_du_projet.git
    ```

2. **Accédez au répertoire du projet** :
    ```bash
    cd nom_du_projet
    ```

3. **Compilez le programme avec GCC** :
    ```bash
    gcc -o gestion_energie newprojet.c
    ```

4. **Exécutez le programme** :
    ```bash
    ./gestion_energie
    ```

## Utilisation

Une fois le programme compilé, vous pouvez l'exécuter pour gérer les données suivantes :
- Ajout et suppression de centres de production
- Mise à jour des informations de distribution
- Gestion des clients et abonnements

### Exemple de commandes :

- **Ajouter un centre de production** :
    Entrez le nom du centre, sa région et le type d'énergie qu'il utilise.
  
- **Ajouter un abonnement client** :
    Entrez le type d'abonnement, la durée et la puissance souscrite pour le client.

## Structure du Code

Le programme est divisé en plusieurs structures :

1. **RegionDistribution** : 
    - Représente une région de distribution avec un nom unique.

2. **CentreProduction** :
    - Contient des informations sur chaque centre de production, y compris son code, son nom, sa région et les types d'énergie qu'il produit.

3. **Abonnement** :
    - Représente les détails des abonnements clients (puissance souscrite, durée, prix).

4. **Client** :
    - Stocke les informations relatives aux clients, y compris leur abonnement et leurs données personnelles.

## Contribuer

Les contributions au projet sont les bienvenues. Si vous souhaitez contribuer :
1. Forkez le projet
2. Créez une branche pour vos modifications (`git checkout -b ma-nouvelle-fonctionnalité`)
3. Effectuez vos modifications et validez-les (`git commit -m 'Ajout d'une nouvelle fonctionnalité'`)
4. Poussez la branche (`git push origin ma-nouvelle-fonctionnalité`)
5. Créez une Pull Request sur GitHub


