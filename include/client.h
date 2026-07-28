#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <vector>
#include "compteBancaire.h"

class Client
{
private:
    std::string idClient;
    std::string nom;
    std::string prenom;
    std::vector<CompteBancaire *> comptes;
    std::string dateInscription;
    static int nbrClients; // Compteur de clients
public:
    Client(const std::string &idClient, const std::string &nom, const std::string &prenom, const std::string &dateInscription = "");
    ~Client(); // Destructeur pour liberer la memoire des comptes associes au client

    // Getters
    std::string getIdClient() const;
    std::string getNom() const;
    std::string getPrenom() const;
    const std::vector<CompteBancaire*>& getComptes() const;
    std::string getDateInscription() const;
    static int getNbrClients();

    // Setter
    void setNom(const std::string &nouveauNom);       // pour l'operation "Modifier"
    void setPrenom(const std::string &nouveauPrenom);  // pour l'operation "Modifier"

    // Methodes 
    void ajouterCompte(CompteBancaire *compte);
    void supprimerCompte(const std::string &numero); // pour l'operation "Supprimer"
    CompteBancaire* rechercherCompte(const std::string &numero) const;
    void afficherComptes() const;                              // affiche tous les comptes du client
    void afficherComptes(const std::string &numero) const;      // surcharge : affiche un compte
    friend std::ostream &operator<<(std::ostream &os, const Client &client);
};
#endif