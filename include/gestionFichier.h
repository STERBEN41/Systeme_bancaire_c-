#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include <string>
#include <vector>
#include "client.h"

// Classe utilitaire : regroupe toute la lecture/ecriture de fichiers,
// pour garder Banque concentree sur la logique metier plutot que sur le format du texte.
// Toutes les methodes sont statiques : pas besoin de creer un objet GestionFichier.
class GestionFichier
{
public:
    static void sauvegarderClients(const std::string &chemin, const std::vector<Client *> &clients);
    static void sauvegarderComptes(const std::string &chemin, const std::vector<Client *> &clients);

    static void chargerClients(const std::string &chemin, std::vector<Client *> &clients);
    static void chargerComptes(const std::string &chemin, std::vector<Client *> &clients);
};
#endif
