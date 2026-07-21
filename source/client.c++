#include "client.h"
#include "compteBancaire.h"
#include "exceptionBancaire.h"
#include <iostream>
#include <vector>

int Client::nbrClients = 0; // initialisation du membre statique

// Constructeur
Client::Client(const std::string &idClient, const std::string &nom, const std::string &prenom, const std::string &dateInscription)
    : idClient(idClient), nom(nom), prenom(prenom)
{
    this->dateInscription = dateInscription.empty() ? CompteBancaire::obtenirDateActuelle() : dateInscription;
    nbrClients++;
}

// Destructeur
Client::~Client()
{
    for (CompteBancaire *compte : comptes)
    {
        delete compte;
    }
}

// Definition de ajouterCompte()
void Client::ajouterCompte(CompteBancaire *compte)
{
    comptes.push_back(compte); // Ajoute le compte à la liste des comptes du client
}

// Definition de supprimerCompte()
void Client::supprimerCompte(const std::string &numero)
{
    for (auto it = comptes.begin(); it != comptes.end(); ++it)
    {
        if ((*it)->getNumeroCompte() == numero)
        {
            delete *it;          // libere la memoire du compte
            comptes.erase(it);   // puis l'enleve de la liste
            return;
        }
    }
    throw CompteInexistantException(numero); // aucun compte trouve avec ce numero
}

// Definition de rechercherCompte()
CompteBancaire *Client::rechercherCompte(const std::string &numero) const
{
    for (CompteBancaire *compte : comptes)
    {
        if (compte->getNumeroCompte() == numero)
        {
            return compte;
        }
    }
    throw CompteInexistantException(numero); // aucun compte trouve apres avoir tout parcouru
}

// Definition de afficherComptes()
void Client::afficherComptes() const
{
    if (comptes.empty())
    {
        std::cout << "Le client " << nom << " " << prenom << " n'a aucun compte." << std::endl;
    }
    else
    {
        std::cout << "Comptes du client " << nom << " " << prenom << ":" << std::endl;
        for (const CompteBancaire *compte : comptes)
        {
            std::cout << *compte << std::endl; // Utilise l'operateur << surcharge pour afficher les infos du compte
        }
    }
}

// Surcharge de afficherComptes() -- meme nom, version qui affiche un seul compte precis
void Client::afficherComptes(const std::string &numero) const
{
    CompteBancaire *compte = rechercherCompte(numero); // leve CompteInexistantException si absent
    std::cout << *compte << std::endl;
}

// Definition de l'operateur << surcharge pour afficher les infos du client
std::ostream &operator<<(std::ostream &os, const Client &client)
{
    os << "Client " << client.nom << " " << client.prenom << " (ID: " << client.idClient << ")";
    return os;
}

// Getters
std::string Client::getIdClient() const { return idClient; }
std::string Client::getNom() const { return nom; }
std::string Client::getPrenom() const { return prenom; }
std::string Client::getDateInscription() const { return dateInscription; }
const std::vector<CompteBancaire *> &Client::getComptes() const { return comptes; }
int Client::getNbrClients() { return nbrClients; }

// Setter
void Client::setNbrClients(int valeur) { nbrClients = valeur; }
void Client::setNom(const std::string &nouveauNom) { nom = nouveauNom; }
void Client::setPrenom(const std::string &nouveauPrenom) { prenom = nouveauPrenom; }