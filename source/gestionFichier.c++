#include "gestionFichier.h"
#include "compteCourant.h"
#include "compteEpargne.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Format du fichier clients : idClient|nom|prenom|dateInscription
void GestionFichier::sauvegarderClients(const std::string &chemin, const std::vector<Client *> &clients)
{
    std::ofstream fichier(chemin);
    if (!fichier.is_open())
    {
        std::cout << "Impossible d'ouvrir " << chemin << " pour la sauvegarde des clients." << std::endl;
        return;
    }
    for (Client *client : clients)
    {
        fichier << client->getIdClient() << "|" << client->getNom() << "|" << client->getPrenom()
                << "|" << client->getDateInscription() << "\n";
    }
    fichier.close();
}

// Format du fichier comptes : numeroCompte|type|solde|decouvertOuTaux|idClientProprietaire|dateCreation
// (le type "Courant" ou "Epargne" permet de recreer le bon objet au chargement)
void GestionFichier::sauvegarderComptes(const std::string &chemin, const std::vector<Client *> &clients)
{
    std::ofstream fichier(chemin);
    if (!fichier.is_open())
    {
        std::cout << "Impossible d'ouvrir " << chemin << " pour la sauvegarde des comptes." << std::endl;
        return;
    }
    for (Client *client : clients)
    {
        for (CompteBancaire *compte : client->getComptes())
        {
            if (CompteCourant *cc = dynamic_cast<CompteCourant *>(compte))
            {
                fichier << cc->getNumeroCompte() << "|Courant|" << cc->getSolde()
                        << "|" << cc->getDecouvertAutorise() << "|" << client->getIdClient()
                        << "|" << cc->getDateCreation() << "\n";
            }
            else if (CompteEpargne *ce = dynamic_cast<CompteEpargne *>(compte))
            {
                fichier << ce->getNumeroCompte() << "|Epargne|" << ce->getSolde()
                        << "|" << ce->getTauxInteret() << "|" << client->getIdClient()
                        << "|" << ce->getDateCreation() << "\n";
            }
        }
    }
    fichier.close();
}

void GestionFichier::chargerClients(const std::string &chemin, std::vector<Client *> &clients)
{
    std::ifstream fichier(chemin);
    if (!fichier.is_open())
    {
        std::cout << "Impossible d'ouvrir " << chemin << " pour le chargement des clients." << std::endl;
        return;
    }

    // On repart de zero : les clients actuellement en memoire sont liberes avant de recharger
    for (Client *c : clients)
    {
        delete c;
    }
    clients.clear();

    std::string ligne;
    while (std::getline(fichier, ligne))
    {
        std::stringstream ss(ligne);
        std::string idClient, nom, prenom, dateInscription;
        std::getline(ss, idClient, '|');
        std::getline(ss, nom, '|');
        std::getline(ss, prenom, '|');
        std::getline(ss, dateInscription, '|');
        if (idClient.empty())
        {
            continue;
        }
        clients.push_back(new Client(idClient, nom, prenom, dateInscription));
    }
    fichier.close();
}

void GestionFichier::chargerComptes(const std::string &chemin, std::vector<Client *> &clients)
{
    std::ifstream fichier(chemin);
    if (!fichier.is_open())
    {
        std::cout << "Impossible d'ouvrir " << chemin << " pour le chargement des comptes." << std::endl;
        return;
    }

    std::string ligne;
    while (std::getline(fichier, ligne))
    {
        std::stringstream ss(ligne);
        std::string numero, type, soldeStr, extraStr, idClient, dateCreation;
        std::getline(ss, numero, '|');
        std::getline(ss, type, '|');
        std::getline(ss, soldeStr, '|');
        std::getline(ss, extraStr, '|');
        std::getline(ss, idClient, '|');
        std::getline(ss, dateCreation, '|');
        if (numero.empty())
        {
            continue;
        }

        double solde = std::stod(soldeStr);
        double extra = std::stod(extraStr);

        // Retrouve le client proprietaire parmi ceux deja charges (clients.txt doit etre charge avant comptes.txt)
        Client *proprietaire = nullptr;
        for (Client *c : clients)
        {
            if (c->getIdClient() == idClient)
            {
                proprietaire = c;
                break;
            }
        }
        if (proprietaire == nullptr)
        {
            continue; // client introuvable, on ignore ce compte
        }

        if (type == "Courant")
        {
            proprietaire->ajouterCompte(new CompteCourant(numero, solde, proprietaire, extra, dateCreation));
        }
        else if (type == "Epargne")
        {
            proprietaire->ajouterCompte(new CompteEpargne(numero, solde, proprietaire, extra, dateCreation));
        }
    }
    fichier.close();
}
