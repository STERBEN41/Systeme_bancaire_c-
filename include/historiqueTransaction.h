#ifndef HISTORIQUETRANSACTION_H
#define HISTORIQUETRANSACTION_H

#include <vector>
#include "transaction.h"

class HistoriqueTransaction // Regroupe toutes les transactions effectuees sur un compte
{
private:
    std::vector<Transaction> transaction; // liste des transactions

public:
    void ajouter(const Transaction &t);
    void afficherHistorique() const;
    const std::vector<Transaction> &getTransactions() const;
};
#endif
