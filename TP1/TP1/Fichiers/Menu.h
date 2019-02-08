/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Menu.h
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les déclaration des fonctions implémenté dans Menu.cpp
*/

#ifndef MENU_H
#define MENU_H 

#include "Plat.h"
#include <fstream>

enum TypeMenu{Matin, Midi, Soir};
const int MAXPLAT = 5;
class Menu {
public: 
	// constructeurs
	Menu(); // constructeur par defaut 
	Menu(string fichier, TypeMenu type);  // constructeur par parametre
	~Menu(); // Destructeur


	//getters
	int getNbPlats() const;  // retourne le nombre de plats
	
	//affichage 
	void afficher() const; // Affiche le menu

	//methodes en plus
	Plat* trouverPlat(string& nom) const; // recherche un plat dans le menu
	void ajouterPlat(Plat& plat);  // ajoute un plat dans une liste de plat
	void ajouterPlat(string& nom, double montant, double cout);  // ajoute un plat dans une liste de plat
	bool lireMenu(string& fichier) ; //lire un menu à partir d'un fichier
private : 
	unsigned int capacite_; // la capacité maximale d'un tableau de plats
	Plat** listePlats_;   // tableau qui contient des pointeurs vers des plats
	unsigned int nbPlats_;  // nombre de plat
	TypeMenu type_;  // attribut qui contient le type de Menu "Matin, Midi ou Soir"

};
std::ostream &operator<<(std::ostream &flux, TypeMenu const& type) ; //affiche un string a partir d'un type enum




#endif // !MENU_H
