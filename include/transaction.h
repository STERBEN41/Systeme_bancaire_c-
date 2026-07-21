#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

class Transaction // Represente une operation (depot ou retrait) effectuee sur un compte
{
private:
    std::string type;         // "DEPOT" ou "RETRAIT"
    double montant;
    std::string date;
    std::string numeroCompte; // numero du compte concerne par cette transaction

public:
    Transaction(const std::string &type, double montant, const std::string &numeroCompte);

    // Getters
    std::string getType() const;
    double getMontant() const;
    std::string getDate() const;
    std::string getNumeroCompte() const;

    friend std::ostream &operator<<(std::ostream &os, const Transaction &transaction);
};
#endif
