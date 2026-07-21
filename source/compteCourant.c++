#include <iostream>
#include "compteBancaire.h"
#include "compteCourant.h"
#include "exceptionBancaire.h"
#include "transaction.h"

void CompteCourant::retirer(double montant)
    { // Implementation de la methode retirer() redefinie pour compte courant
        if (montant <= 0)
        {
            throw MontantInvalideException(montant);
        }
        else if (solde - montant < -decouvertAutorise)
        {
            throw SoldeInsuffisantException(numeroCompte, montant, solde);
        }
        else
        {
            solde -= montant;
            historique.ajouter(Transaction("RETRAIT", montant, numeroCompte));
        }
    }

void CompteCourant::afficherInfos() const 
{ // Implementation de la methode afficherInfos() redefinie pour compte courant
        std::cout << "Compte Courant n\u00b0" << numeroCompte
                  << " | Solde: " << solde
                  << " | Decouvert autorise: " << decouvertAutorise
                  << " | Date creation: " << dateCreation
                  << std::endl;
}

// Getters
double CompteCourant::getDecouvertAutorise() const { return decouvertAutorise;}