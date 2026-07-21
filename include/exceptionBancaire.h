#ifndef EXCEPTIONSBANCAIRES_H // empeche les inclusions multiples
#define EXCEPTIONSBANCAIRES_H

#include <exception>
#include <string>

//  Classe de base pour toutes les exceptions
class ExceptionBancaire : public std::exception
{
protected:
    std::string message;

public:
    explicit ExceptionBancaire(const std::string &msg) : message(msg) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

//  Exceptions dérivées

class SoldeInsuffisantException : public ExceptionBancaire
{
public:
    SoldeInsuffisantException(const std::string &numeroCompte, double montant, double solde)
        : ExceptionBancaire("Solde insuffisant sur le compte " + numeroCompte +
                            " : tentative de retrait de " + std::to_string(montant) +
                            " alors que le solde est de " + std::to_string(solde)) {}
};

class MontantInvalideException : public ExceptionBancaire
{
public:
    MontantInvalideException(double montant)
        : ExceptionBancaire("Montant invalide : " + std::to_string(montant) +
                            " (le montant doit etre strictement positif)") {}
};

class CompteInexistantException : public ExceptionBancaire
{
public:
    CompteInexistantException(const std::string &numeroCompte)
        : ExceptionBancaire("Aucun compte trouve avec le numero " + numeroCompte) {}
};

class ClientInexistantException : public ExceptionBancaire
{
public:
    ClientInexistantException(const std::string &idClient)
        : ExceptionBancaire("Aucun client trouve avec l'identifiant " + idClient) {}
};

#endif