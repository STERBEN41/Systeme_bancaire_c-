#ifndef COMPTECOURANT_H
#define COMPTECOURANT_H

#include "compteBancaire.h"

class CompteCourant : public CompteBancaire // Classe représentant un compte courant herite de CompteBancaire
{
private:
    double decouvertAutorise ; // Initialisation du decouvert

public:
    CompteCourant(const std::string &numero, double montantInitial, Client *client, double decouvert, const std::string &dateCreation = "")
        : CompteBancaire(numero, montantInitial, "Courant", client, dateCreation), decouvertAutorise(decouvert) {} // Constructeur par defaut

    void retirer(double montant) override; // Implementation de la methode retirer() redefinie pour compte courant
    void afficherInfos() const override; // Implementation de la methode afficherInfos() redefinie pour compte courant


    // Getters
    double getDecouvertAutorise() const;
};
#endif