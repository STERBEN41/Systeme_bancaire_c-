#ifndef MENU_H
#define MENU_H

#include "banque.h"

// Regroupe toute l'interaction avec l'utilisateur (affichage du menu, lecture du choix,
// appel des bonnes methodes de Banque). Garde main.c++ tres court.
class Menu
{
private:
    Banque &banque; // reference vers LA banque geree pendant toute l'execution

public:
    explicit Menu(Banque &banque);

    void afficherOptions() const;
    void lancer(); // boucle principale : affiche, lit le choix, execute, recommence

private:
    // Une methode privee par option du menu, pour rester lisible
    void ajouterClient();
    void ajouterCompte();
    void modifierClient();
    void supprimerClient();
    void supprimerCompte();
    void deposer();
    void retirer();
    void rechercherClient();
    void afficherTousLesClients();
    void afficherComptesClient();
    void afficherHistoriqueCompte();
    void calculerInterets();
    void sauvegarder();
    void charger();
    void afficherStatistiques();
};
#endif
