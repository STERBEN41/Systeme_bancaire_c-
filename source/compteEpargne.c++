#include <iostream>
#include "compteBancaire.h"
#include "compteEpargne.h"
#include "exceptionBancaire.h"
#include "transaction.h"

void CompteEpargne::retirer(double montant)
{ // Implementation de la methode retirer() redefinie pour compte epargne
    if (montant <= 0)
    {
        throw MontantInvalideException(montant);
    }
    else if (solde - montant < 0)
    {
        throw SoldeInsuffisantException(numeroCompte, montant, solde);
    }
    else
    {
        solde -= montant;
        historique.ajouter(Transaction("RETRAIT", montant, numeroCompte));
    }
};

void CompteEpargne::afficherInfos() const
{ // Implementation de la methode afficherInfos() redefinie pour compte epargne
    std::cout << "Compte Epargne n\u00b0" << numeroCompte
              << " | Solde: " << solde
              << " | taux d'interêt: " << tauxInteret
              << " | Date creation: " << dateCreation
              << std::endl;
}

double CompteEpargne::calculerInterets()
{
    double interets = solde * tauxInteret; // calcule le montant des interets
    solde += interets;                     // les ajoute directement au solde
    return interets;                       // retourne le montant calcule, utile pour l'afficher ou le logger
}

// Getter
double CompteEpargne::getTauxInteret() const { return tauxInteret; }