#include <iostream>
#include "compteBancaire.h"
#include "exceptionBancaire.h"
#include "transaction.h"
#include <ctime> 
#include <sstream> 
#include <iomanip> 

int CompteBancaire::nbrComptes = 0; // initialisation du membre statique

std::string CompteBancaire::obtenirDateActuelle() // Fonction pour obtenir la date actuelle sous forme de chaine
{
    time_t maintenant = time(nullptr);       // récupère le temps système actuel
    tm *dateLocale = localtime(&maintenant); // convertit en structure lisible (jour, mois, année...)

    std::ostringstream oss;
    oss << std::put_time(dateLocale, "%d/%m/%Y"); // formate en JJ/MM/AAAA
    return oss.str();
}

// Définition du constructeur
CompteBancaire::CompteBancaire(const std::string &numero, double montantInitial, const std::string &type, Client *client, const std::string &dateCreation)
    : numeroCompte(numero), typeCompte(type), solde(montantInitial), proprietaire(client)
{
    if (montantInitial < 0 && type == "Epargne")
    {
        throw MontantInvalideException(montantInitial);
    }
    ++nbrComptes;
    this->dateCreation = dateCreation.empty() ? obtenirDateActuelle() : dateCreation;
}

// Définition de deposer()
void CompteBancaire::deposer(double montant)
{
    if (montant <= 0)
    {
        throw MontantInvalideException(montant);
    }
    solde += montant;
    historique.ajouter(Transaction("DEPOT", montant, numeroCompte)); // enregistre l'operation
}

// Getters
std::string CompteBancaire::getNumeroCompte() const { return numeroCompte; }
double CompteBancaire::getSolde() const { return solde; }
std::string CompteBancaire::getDateCreation() const { return dateCreation; }
Client *CompteBancaire::getProprietaire() const { return proprietaire; }
std::string CompteBancaire::getTypeCompte() const { return typeCompte; }
int CompteBancaire::getNbrComptes() { return nbrComptes; }
HistoriqueTransaction &CompteBancaire::getHistorique() { return historique; }

// Setter
void CompteBancaire::setNbrComptes(int valeur) { nbrComptes = valeur; }

// operator<< est une fonction libre, pas de CompteBancaire:: devant
std::ostream &operator<<(std::ostream &os, const CompteBancaire &compte)
{
    os << "Compte " << compte.typeCompte << " n\u00b0" << compte.numeroCompte
       << " | Solde: " << compte.solde
       << " | Date creation: " << compte.dateCreation;
    return os;
}