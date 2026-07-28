#include "banque.h"
#include "exceptionBancaire.h"
#include "gestionFichier.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Constructeur
Banque::Banque(const std::string &idBanque, const std::string &nomBanque)
    : idBanque(idBanque), nomBanque(nomBanque)
{
}

// destructeur
Banque::~Banque()
{
    for (Client *client : clients)
    {
        delete client;
    }
}

// Definition de ajouterClient()
void Banque::ajouterClient(Client *client)
{
    clients.push_back(client); // Ajoute le client à la liste des clients de la banque
}

// Definition de supprimerClient()
void Banque::supprimerClient(const std::string &idClient)
{
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if ((*it)->getIdClient() == idClient)
        {
            delete *it;         // libere la memoire du client (et de ses comptes, via ~Client())
            clients.erase(it);  // puis l'enleve de la liste
            return;
        }
    }
    throw ClientInexistantException(idClient);
}

// Definition de modifierClient()
void Banque::modifierClient(const std::string &idClient, const std::string &nouveauNom,
                            const std::string &nouveauPrenom)
{
    Client *client = rechercherClient(idClient); // leve ClientInexistantException si absent
    client->setNom(nouveauNom);
    client->setPrenom(nouveauPrenom);
}

// Definition de rechercherClient() par identifiant
Client *Banque::rechercherClient(const std::string &idClient) const
{
    for (Client *client : clients)
    {
        if (client->getIdClient() == idClient)
        {
            return client;
        }
    }
    throw ClientInexistantException(idClient); // aucun client trouve apres avoir parcouru toute la liste
}

// Surcharge de rechercherClient() avec le même nom, version par position dans la liste
Client *Banque::rechercherClient(int index) const
{
    if (index < 0 || index >= static_cast<int>(clients.size()))
    {
        throw ClientInexistantException("index " + std::to_string(index));
    }
    return clients[index];
}

// Definition de rechercherCompte()
CompteBancaire *Banque::rechercherCompte(const std::string &numero) const
{
    for (Client *client : clients)
    {
        try
        {
            return client->rechercherCompte(numero); // s'arrete ici si il trouve le compte
        }
        catch (const CompteInexistantException &)
        {
            // pas trouve chez ce client, on continue vers le suivant
        }
    }
    throw CompteInexistantException(numero); // pas trouve chez aucun client
}

// Definition de afficherClients()
void Banque::afficherClients() const
{
    if (clients.empty())
    {
        std::cout << "La banque " << nomBanque << " n a aucun client." << std::endl;
    }
    else
    {
        std::cout << "clients de la banque " << nomBanque << ":" << std::endl;
        for (const Client *client : clients)
        {
            std::cout << *client << std::endl; // Utilise l'operateur << surcharge pour afficher les infos du client
        }
    }
}

// Getters
std::string Banque::getIdBanque() const { return idBanque; }
std::string Banque::getNomBanque() const { return nomBanque; }
const std::vector<Client *> &Banque::getClients() const { return clients; }

// Definition de sauvegarder() -- delegue le vrai travail d'ecriture a GestionFichier
void Banque::sauvegarder(const std::string &cheminClients, const std::string &cheminComptes) const
{
    GestionFichier::sauvegarderClients(cheminClients, clients);
    GestionFichier::sauvegarderComptes(cheminComptes, clients);
    std::cout << "Sauvegarde terminee (" << cheminClients << " et " << cheminComptes << ")." << std::endl;
}

// Definition de charger() -- ATTENTION : il faut charger les clients AVANT les comptes,
// car chaque compte a besoin de retrouver son proprietaire deja en memoire.
void Banque::charger(const std::string &cheminClients, const std::string &cheminComptes)
{
    GestionFichier::chargerClients(cheminClients, clients);
    GestionFichier::chargerComptes(cheminComptes, clients);
    std::cout << "Chargement termine (" << cheminClients << " et " << cheminComptes << ")." << std::endl;
}