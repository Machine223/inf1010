/*
* Titre : Restaurant.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
#include "Menu.h"
const int INTTABLES = 6;
class Restaurant {
public:
	//constructeurs
	Restaurant();
	Restaurant(const string& fichier, const string& nom,  TypeMenu moment);
	Restaurant(const Restaurant& restaurant);


	//destructeur
	~Restaurant();

	//setters
	void setMoment(TypeMenu moment);
	void setNom(const string& nom);

	//getters
	string getNom() const;
	TypeMenu getMoment() const;

	//Autres methodes
	void lireTable(const string& fichier);
	void libererTable(int id);
	friend ostream& operator<<(ostream& flux, const Restaurant& restaurant); // A MODIFIER
	void commanderPlat(const string& nom, int idTable); 

	void placerClients(int nbClients);
	friend void operator+=(Restaurant& restaurant, Table&  table);
	Restaurant& operator=(const Restaurant& restaurant);
	friend 	bool operator<(const Restaurant& restaurant1, const Restaurant& restaurant2);




private:
	string* nom_;

	double chiffreAffaire_;
	TypeMenu momentJournee_;

	//differents menus en fonction du moment de la journee
	Menu* menuMatin_;
	Menu* menuMidi_;
	Menu* menuSoir_;

	// A MODIFIER

	//liste des tables
	vector<Table*> tables_;
};
void operator+=(Restaurant& restaurant, Table&  table);
ostream& operator<<(ostream& flux, const Restaurant& restaurant);
bool operator<(const Restaurant& restaurant1, const Restaurant& restaurant2);
#endif // !RESTAURANT_H
