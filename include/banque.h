#ifndef BANQUE_H
#define BANQUE_H

#include <iostream>
#include <vector>
#include "client.h"
#include "compteBancaire.h"

class Banque
{
private:
    std::string idBanque;
    std::vector<Client *> clients; // Liste des clients de la banque
    std::string nomBanque;

public:
    Banque(const std::string &idBanque, const std::string &nomBanque);
    ~Banque(); // Destructeur

    // Methodes de gestion des clients
    void ajouterClient(Client *client);
    void supprimerClient(const std::string &idClient);   // pour l'operation "Supprimer"
    void modifierClient(const std::string &idClient, const std::string &nouveauNom,
                         const std::string &nouveauPrenom); // pour l'operation "Modifier"
    Client *rechercherClient(const std::string &idClient) const;
    Client *rechercherClient(int index) const; // surcharge : recherche par position dans la liste
    CompteBancaire *rechercherCompte(const std::string &numero) const;
    void afficherClients() const;

    // Methodes de persistance
    void sauvegarder(const std::string &cheminClients, const std::string &cheminComptes) const;
    void charger(const std::string &cheminClients, const std::string &cheminComptes);

    // Getters
    std::string getIdBanque() const;
    std::string getNomBanque() const;
    const std::vector<Client *> &getClients() const;
};
#endif