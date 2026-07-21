#include "menu.h"
#include "compteCourant.h"
#include "compteEpargne.h"
#include "exceptionBancaire.h"
#include <iostream>
#include <limits>

namespace
{
    // Vide le buffer de saisie apres une entree invalide (evite les boucles infinies)
    void viderBuffer()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Menu::Menu(Banque &banque) : banque(banque) {}

void Menu::afficherOptions() const
{
    std::cout << "\n===== " << banque.getNomBanque() << " =====\n";
    std::cout << " 1. Ajouter un client\n";
    std::cout << " 2. Ajouter un compte a un client\n";
    std::cout << " 3. Modifier un client (nom/prenom)\n";
    std::cout << " 4. Supprimer un client\n";
    std::cout << " 5. Supprimer un compte\n";
    std::cout << " 6. Deposer de l'argent\n";
    std::cout << " 7. Retirer de l'argent\n";
    std::cout << " 8. Rechercher un client\n";
    std::cout << " 9. Afficher tous les clients\n";
    std::cout << "10. Afficher les comptes d'un client\n";
    std::cout << "11. Afficher l'historique d'un compte\n";
    std::cout << "12. Calculer les interets d'un compte epargne\n";
    std::cout << "13. Sauvegarder les donnees\n";
    std::cout << "14. Charger les donnees\n";
    std::cout << "15. Statistiques (membres statiques)\n";
    std::cout << " 0. Quitter\n";
    std::cout << "Choix : ";
}

void Menu::lancer()
{
    int choix;
    do
    {
        afficherOptions();
        std::cin >> choix;

        if (std::cin.fail())
        {
            viderBuffer();
            std::cout << "Entree invalide, veuillez taper un nombre.\n";
            continue;
        }

        try
        {
            switch (choix)
            {
                case 1: ajouterClient(); break;
                case 2: ajouterCompte(); break;
                case 3: modifierClient(); break;
                case 4: supprimerClient(); break;
                case 5: supprimerCompte(); break;
                case 6: deposer(); break;
                case 7: retirer(); break;
                case 8: rechercherClient(); break;
                case 9: afficherTousLesClients(); break;
                case 10: afficherComptesClient(); break;
                case 11: afficherHistoriqueCompte(); break;
                case 12: calculerInterets(); break;
                case 13: sauvegarder(); break;
                case 14: charger(); break;
                case 15: afficherStatistiques(); break;
                case 0: std::cout << "Au revoir !\n"; break;
                default: std::cout << "Choix invalide.\n";
            }
        }
        catch (const ExceptionBancaire &e)
        {
            // Toutes les exceptions du projet heritent de ExceptionBancaire,
            // donc ce seul catch suffit a toutes les attraper.
            std::cout << "Erreur : " << e.what() << "\n";
        }

    } while (choix != 0);
}

void Menu::ajouterClient()
{
    std::string nom, prenom;
    std::cout << "Nom : "; std::cin >> nom;
    std::cout << "Prenom : "; std::cin >> prenom;

    std::string id = "CL" + std::to_string(Client::getNbrClients() + 1); // ID genere automatiquement
    banque.ajouterClient(new Client(id, nom, prenom));
    std::cout << "Client ajoute avec l'identifiant " << id << ".\n";
}

void Menu::ajouterCompte()
{
    std::string idClient;
    std::cout << "Identifiant du client : "; std::cin >> idClient;
    Client *client = banque.rechercherClient(idClient);

    int typeCompte;
    std::cout << "Type de compte (1=Courant, 2=Epargne) : "; std::cin >> typeCompte;

    double soldeInitial;
    std::cout << "Solde initial : "; std::cin >> soldeInitial;

    std::string numero = "CPT" + std::to_string(CompteBancaire::getNbrComptes() + 1); // numero genere automatiquement

    if (typeCompte == 1)
    {
        double decouvert;
        std::cout << "Decouvert autorise : "; std::cin >> decouvert;
        client->ajouterCompte(new CompteCourant(numero, soldeInitial, client, decouvert));
    }
    else if (typeCompte == 2)
    {
        double taux;
        std::cout << "Taux d'interet (ex 0.03 pour 3%) : "; std::cin >> taux;
        client->ajouterCompte(new CompteEpargne(numero, soldeInitial, client, taux));
    }
    else
    {
        std::cout << "Type de compte invalide.\n";
        return;
    }
    std::cout << "Compte " << numero << " ajoute.\n";
}

void Menu::modifierClient()
{
    std::string idClient, nouveauNom, nouveauPrenom;
    std::cout << "Identifiant du client : "; std::cin >> idClient;
    std::cout << "Nouveau nom : "; std::cin >> nouveauNom;
    std::cout << "Nouveau prenom : "; std::cin >> nouveauPrenom;
    banque.modifierClient(idClient, nouveauNom, nouveauPrenom);
    std::cout << "Client modifie.\n";
}

void Menu::supprimerClient()
{
    std::string idClient;
    std::cout << "Identifiant du client a supprimer : "; std::cin >> idClient;
    banque.supprimerClient(idClient);
    std::cout << "Client supprime.\n";
}

void Menu::supprimerCompte()
{
    std::string idClient, numero;
    std::cout << "Identifiant du client : "; std::cin >> idClient;
    std::cout << "Numero du compte a supprimer : "; std::cin >> numero;
    Client *client = banque.rechercherClient(idClient);
    client->supprimerCompte(numero);
    std::cout << "Compte supprime.\n";
}

void Menu::deposer()
{
    std::string numero;
    double montant;
    std::cout << "Numero de compte : "; std::cin >> numero;
    std::cout << "Montant a deposer : "; std::cin >> montant;
    CompteBancaire *compte = banque.rechercherCompte(numero);
    compte->deposer(montant);
    std::cout << "Depot effectue. Nouveau solde : " << compte->getSolde() << "\n";
}

void Menu::retirer()
{
    std::string numero;
    double montant;
    std::cout << "Numero de compte : "; std::cin >> numero;
    std::cout << "Montant a retirer : "; std::cin >> montant;
    CompteBancaire *compte = banque.rechercherCompte(numero);
    compte->retirer(montant); // polymorphisme : bonne version selon CompteCourant ou CompteEpargne
    std::cout << "Retrait effectue. Nouveau solde : " << compte->getSolde() << "\n";
}

void Menu::rechercherClient()
{
    std::string idClient;
    std::cout << "Identifiant du client : "; std::cin >> idClient;
    Client *client = banque.rechercherClient(idClient);
    std::cout << *client << "\n"; // utilise l'operator<< surcharge de Client
}

void Menu::afficherTousLesClients()
{
    banque.afficherClients();
}

void Menu::afficherComptesClient()
{
    std::string idClient;
    std::cout << "Identifiant du client : "; std::cin >> idClient;
    Client *client = banque.rechercherClient(idClient);

    std::string numero;
    std::cout << "Numero de compte precis (laisser vide + Entree pour voir TOUS les comptes) : ";
    std::cin.ignore();
    std::getline(std::cin, numero);

    if (numero.empty())
    {
        client->afficherComptes(); // version sans parametre : tous les comptes
    }
    else
    {
        client->afficherComptes(numero); // surcharge : un seul compte
    }
}

void Menu::afficherHistoriqueCompte()
{
    std::string numero;
    std::cout << "Numero de compte : "; std::cin >> numero;
    CompteBancaire *compte = banque.rechercherCompte(numero);
    compte->getHistorique().afficherHistorique();
}

void Menu::calculerInterets()
{
    std::string numero;
    std::cout << "Numero de compte epargne : "; std::cin >> numero;
    CompteBancaire *compte = banque.rechercherCompte(numero);

    CompteEpargne *ce = dynamic_cast<CompteEpargne *>(compte);
    if (ce == nullptr)
    {
        std::cout << "Ce compte n'est pas un compte epargne.\n";
        return;
    }
    double interets = ce->calculerInterets();
    std::cout << "Interets ajoutes : " << interets << " | Nouveau solde : " << ce->getSolde() << "\n";
}

void Menu::sauvegarder()
{
    banque.sauvegarder("data/clients.txt", "data/comptes.txt");
}

void Menu::charger()
{
    banque.charger("data/clients.txt", "data/comptes.txt");
}

void Menu::afficherStatistiques()
{
    std::cout << "Nombre total de clients crees : " << Client::getNbrClients() << "\n";
    std::cout << "Nombre total de comptes crees : " << CompteBancaire::getNbrComptes() << "\n";
    std::cout << "Nombre de clients actuellement dans la banque : " << banque.getClients().size() << "\n";

    if (!banque.getClients().empty())
    {
        Client *premier = banque.rechercherClient(0); // surcharge de rechercherClient() : version par index
        std::cout << "Premier client enregistre : " << *premier << "\n";
    }
}
