#ifndef COMPTEBANCAIRE_H
#define COMPTEBANCAIRE_H

#include <string>
#include <iostream>
#include "exceptionBancaire.h"
#include "historiqueTransaction.h"

class Client; // Forward declaration de la classe Client pour eviter d'inclure le client.h ici

class CompteBancaire // Classe abstraite représentant un compte bancaire
{
protected:
    std::string numeroCompte;
    std::string typeCompte;
    double solde;
    std::string dateCreation;
    Client *proprietaire;  // Pointeur vers le proprietaire du compte
    HistoriqueTransaction historique; // garde la trace de tous les depots/retraits de ce compte
    static int nbrComptes; // Compteur de comptes pour generer des numeros de compte uniques

public:
    CompteBancaire(const std::string &numero, double montantInitial, const std::string &type, Client *client, const std::string &dateCreation = "");
    virtual ~CompteBancaire() = default; // destructeur virtuel pour permettre la destruction correcte des objets

    // Methodes
    virtual void deposer(double montant);     // virtual non pure, car on peut avoir une implementation par defaut
    virtual void retirer(double montant) = 0; // virtual pure, car chaque type de compte peut avoir des regles differentes pour le retrait
    virtual void afficherInfos() const = 0;

    // Getters
    double getSolde() const;
    std::string getNumeroCompte() const;
    std::string getDateCreation() const;
    std::string getTypeCompte() const;
    Client *getProprietaire() const;
    static int getNbrComptes();
    HistoriqueTransaction &getHistorique(); // acces a l'historique (pour ajouter/consulter les transactions)

    // Setter
    static void setNbrComptes(int valeur);

    friend std::ostream &operator<<(std::ostream &os, const CompteBancaire &compte); // Surcharge de l'operateur << pour afficher les infos du compte
    static std::string obtenirDateActuelle();
};
#endif