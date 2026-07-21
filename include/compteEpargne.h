#ifndef COMPTEEPARGNE_H
#define COMPTEEPARGNE_H

#include "compteBancaire.h"

class CompteEpargne : public CompteBancaire // Classe représentant un compte epargne herite de compteBancaire
{
private:
    double tauxInteret;

public:
    CompteEpargne(const std::string &numero, double montantInitial, Client *client, double taux, const std::string &dateCreation = "")
        : CompteBancaire(numero, montantInitial, "Epargne", client, dateCreation), tauxInteret(taux) {} // Constructeur par defaut

    void retirer(double montant) override; // Implementation de la methode retirer() redefinie pour compte epargne
    void afficherInfos() const override;   // Implementation de la methode afficherInfos() redefinie pour compte epargne
    double calculerInterets() ;

    // Getter
    double getTauxInteret() const;
};
#endif