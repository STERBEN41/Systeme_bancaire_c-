#include "transaction.h"
#include "compteBancaire.h"

// Definition du constructeur
Transaction::Transaction(const std::string &type, double montant, const std::string &numeroCompte)
    : type(type), montant(montant), numeroCompte(numeroCompte)
{
    date = CompteBancaire::obtenirDateActuelle(); // reutilise la fonction statique deja existante
}

// Getters
std::string Transaction::getType() const { return type; }
double Transaction::getMontant() const { return montant; }
std::string Transaction::getDate() const { return date; }
std::string Transaction::getNumeroCompte() const { return numeroCompte; }

// operator<< est une fonction libre, pas de Transaction:: devant
std::ostream &operator<<(std::ostream &os, const Transaction &transaction)
{
    os << "[" << transaction.date << "] " << transaction.type
       << " de " << transaction.montant << " sur le compte " << transaction.numeroCompte;
    return os;
}
