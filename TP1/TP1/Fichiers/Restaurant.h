/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Restaurant.h
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les   fonctions déclarées dans Restaurant.cpp
*/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
const int INTTABLES = 6;
class Restaurant {
public: 
	//constructeurs 
	Restaurant();  // constructeur par defaut
	Restaurant(string& fichier, string& nom,  TypeMenu moment);  // constructeur par parametres
	//Destructor
	~Restaurant();
	//setters 
	void setMoment(TypeMenu moment);  // mettons l'attribut  momentJournee_ à la valeur moment

	//getters 
	string getNom() const;   // retournos le nom du restaurant
	TypeMenu getMoment() const;   // retournos le moment de journée

	//Autres methodes 
	void lireTable(string& fichier);  // lecture des information des tables a partir d'un fichier
	void ajouterTable(int id, int nbPlaces); // Ajout d'une table a la liste des tables
	void libererTable(int id);  // mettre une table disponible
	void commanderPlat(string& nom, int idTable);  // commande d'un plat par un client et l ajoutant a la liste de commandes
	void placerClients(int nbClients);  // placement d'un nombre de peronnes dans une table intilligement

	//affichage 
	void afficher() const; // Affichage des informations de le restaurant

private: 
	string* nom_;  // nom de le restaurant

	double chiffreAffaire_;  // chiffre d'afaire de le restaurant
	TypeMenu momentJournee_; 

	//differents menus en fonction du moment de la journee
	Menu* menuMatin_;  
	Menu* menuMidi_; 
	Menu* menuSoir_; 

	//liste des tables 
	unsigned int capaciteTables_;
	Table** tables_; 
	unsigned int nbTables_; 

};
#endif // !RESTAURANT_H
