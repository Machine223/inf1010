/*
* Titre : Table.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Table.h"

//constructeurs
Table::Table(){

	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

Table::Table(int id, int nbPlaces) {
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}
//
//Table::Table(const Table & table): commande_(table.commande_), nbPlaces_(table.nbPlaces_), id_(table.id_)
//{
//}

//destructeur
Table::~Table() {
	//A MODIFIER
	commande_.clear();
}

//getters
int Table::getId() const {
	return id_;
}

int Table::getNbPlaces() const {
	return nbPlaces_;
}

int Table::getnbClientATable() const
{
	return nbClientsATable_;
}

bool Table::estPleine() const {
	return nbPlaces_==0;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

//setters
void Table::setId(int id) {
	id_ = id;
}

void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	//A MODIFIER
	commande_.clear(); // a confirmer
}

void Table::placerClient(int nbClients) {
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
}

//autres methodes
void Table::commander(Plat* plat) {
	// A MODIFIER
	commande_.push_back(plat);
}

double Table::getChiffreAffaire() const {
	double chiffre = 0;
	for (int i = 0; i < commande_.size(); i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
	}
	return chiffre;
}
/*
Table&  Table::operator=(const Table & tableSource)
{
	commande_ = tableSource.commande_;
	id_ = tableSource.id_;
	nbPlaces_ = tableSource.nbPlaces_;
	nbClientsATable_ = tableSource.nbClientsATable_;
	return *this;
}*/

//affichage
ostream& operator<<(ostream& flux, const Table& table){
	flux << "La table numero " << table.id_;
	if (table.nbClientsATable_ >0) {
		flux << " est occupee. ";
		if (table.commande_.size() != 0) {
			flux << "Voici la commande passee par les clients : " << endl;
			for (int i = 0; i < table.commande_.size(); i++) {
				flux << "\t";
				flux << *table.commande_[i];
			}
		}
		else
			cout << "Mais ils n'ont rien conmmande pour l'instant. " << endl;
	}
	else {
		cout << " est libre. " << endl;
	}
	return flux;
}
