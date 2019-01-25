#include "Table.h"

Table::Table(): commande_(0), capacite_ (MAXCAP), nbPlats_(0), id_(-1), nbPlaces_(0), occupee_(false){
	commande_ = new Plat*[capacite_];
}

Table::Table(int id, int nbPlaces): commande_(0), capacite_(MAXCAP), nbPlats_(0), id_(id), nbPlaces_(nbPlaces), occupee_(false) {
	commande_ = new Plat*[capacite_];
	/***/
}

int Table::getId() const
{
	return id_;
}

int Table::getNbPlaces() const
{
	return nbPlaces_;
}

bool Table::estOccupee() const
{
	return occupee_;
}

void Table::libererTable()
{
	for (int i = 0; i < nbPlats_; i++)
		commande_[i] = 0;
	occupee_ = false;
}

void Table::placerClient(){
	occupee_ = true;
}

void Table::setId(int id){
	id_ = id;
}

void Table::commander(Plat * plat)
{
	if (nbPlats_ >= capacite_)
	{
		Plat** commande = commande_;
		capacite_ *= 2;
		commande_ = new Plat*[capacite_];
		for (int i = 0; i < nbPlats_; i++)
			commande_[i] = commande[i];
		delete commande;
	}
	commande_[nbPlats_] = plat;
	nbPlats_++;
}

double Table::getChiffreAffaire() const {
	double chiffreAffaire = 0;
	for (int i = 0; i < nbPlats_; i++)
		chiffreAffaire += commande_[i]->getPrix();
	return chiffreAffaire;
}

void Table::afficher() const
{
	std::cout << "La table numero" << id_ << "est occupee. Voici la commande passee par les clients :" << endl;
	for (int i = 0; i < nbPlats_; i++)
		commande_[i]->afficher();
}
