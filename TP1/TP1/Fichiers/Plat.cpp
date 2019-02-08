/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Plat.cpp
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les   fonctions déclarées dans Plat.h
*/

#include "Plat.h"

Plat::Plat() :nom_("inconnu"), prix_(0), cout_(0)  // constructeur par defaut
{
}

Plat::Plat(string& nom, double prix, double cout) : nom_(nom), prix_(prix), cout_(cout) // constructeur par parametre
{
}

string Plat::getNom() const // retourne le nom de plat
{
	return nom_;
}

double Plat::getPrix() const // retourne le  prix de plat
{
	return prix_;
}

double Plat::getCout() const // retourne le  cout de plat
{
	return cout_;
}

void Plat::setNom(string nom) // mettre l'attribut nom_ a la valeur nom
{
	nom_ = nom;
}

void Plat::setPrix(double prix) // mettre l'attribut prix_ a la valeur prix
{
	prix_ = prix;
}

void Plat::afficher() const // Affiche un plat
{
	std::cout << "	" << nom_ << "		" << prix_ <<"$	(" << cout_ << "$	pour le restaurant)" << std::endl;
}
