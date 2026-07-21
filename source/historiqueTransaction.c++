#include "historiqueTransaction.h"
#include <iostream>

void HistoriqueTransaction::ajouter(const Transaction &t)
{
    transaction.push_back(t);
}

void HistoriqueTransaction::afficherHistorique() const
{
    if (transaction.empty())
    {
        std::cout << "Aucune transaction pour l'instant." << std::endl;
        return;
    }
    for (const Transaction &t : transaction)
    {
        std::cout << t << std::endl; // utilise l'operator<< surcharge de Transaction
    }
}

const std::vector<Transaction> &HistoriqueTransaction::getTransactions() const
{
    return transaction;
}
