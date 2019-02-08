/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Table.cpp
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les   fonctions déclarées dans Table.h
*/

#include "Table.h"

Table::Table(): commande_(0), capacite_ (MAXCAP), nbPlats_(0), id_(-1), nbPlaces_(0), occupee_(false) // constructeur par defaut
{
	commande_ = new Plat*[capacite_];
}

Table::Table(int id, int nbPlaces): commande_(0), capacite_(MAXCAP), nbPlats_(0), id_(id), nbPlaces_(nbPlaces), occupee_(false) // constructeur par parametre
{
	commande_ = new Plat*[capacite_];
}

Table::~Table() // Destructeur
{
	delete[] commande_; // les plats vont etre detruits par la classe Menu.
}

int Table::getId() const   // retourne l'identifiant  de la table
{
	return id_;
}

int Table::getNbPlaces() const // retourne le nombre de places  de la table
{
	return nbPlaces_;
}

bool Table::estOccupee() const // retourne l'état de la table est ce qu'lle est occupée ou libre
{
	return occupee_;
}

void Table::libererTable() // mettre une table non occupée 
{
	for (int i = 0; i < nbPlats_; i++)  // annulons les commandes
		commande_[i] = 0;
	occupee_ = false; // liberons la table
}

void Table::placerClient(){  // mettre une table occupée
	occupee_ = true;
}

void Table::setId(int id){  // mettre le id_ a la valeur id
	id_ = id;
}

void Table::commander(Plat * plat)  // ajouter une commande a la liste des commandes 
{
	if (nbPlats_ >= capacite_) // elargeons le tableau si taille est insuffisante
	{
		Plat** commande = commande_; // nouvelle variable qui contient l'ancien tanleau
		capacite_ *= 2; // multiplions la capacité par deux
		commande_ = new Plat*[capacite_]; //allounat dynamiquement un nouveau tableau de la nouvelle capacité
		for (int i = 0; i < nbPlats_; i++) // copiant les anciens éléments
			commande_[i] = commande[i];
		delete[] commande; // Supression de l'ancien tableau
	} 
	commande_[nbPlats_] = plat; // Ajoutans le plat au  tableau
	nbPlats_++; // incrémentons le nombre de plats
}

double Table::getChiffreAffaire() const { // calculons le chiffre d'affaire que le restaurant gagne
	double chiffreAffaire = 0;
	for (int i = 0; i < nbPlats_; i++)
		chiffreAffaire += (commande_[i]->getPrix() - commande_[i]->getCout()); // le chiffre d'affaire est le prix - le cout
	return chiffreAffaire;
}

void Table::afficher() const // affichage de la table
{
	std::cout << "La table numero " << id_ << " est"; 
	if (occupee_) // table occupée
	{
		std::cout << " occupee. ";
		if (nbPlats_ > 0) //  ils ont déja commandé
		{
			std::cout << " Voici la commande passee par les clients : " << std::endl;
		for (int i = 0; i < nbPlats_; i++)
			commande_[i]->afficher();
		std::cout << std::endl;
		}
		else //  ils n'ont pas encore commandé
			std::cout << " Mais ils n'ont rien commande pour l'instant." << std::endl << std::endl;

	}
	else // libre
		std::cout << " libre" << std::endl;


}
