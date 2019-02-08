/*
* Titre : Menu.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef MENU_H
#define MENU_H

#include "Plat.h"
#include <fstream>
#include <vector>


enum TypeMenu{Matin, Midi, Soir};
const int MAXPLAT = 5;
class Menu {
public:
	// constructeurs
	Menu();
	Menu(string fichier, TypeMenu type);
	Menu(const Menu& table);


	//destructeur
	~Menu();

	//getters
	vector<Plat*> getListePlats() const;

	//affichage
	friend ostream& operator<<(ostream& flux, const Menu& menu); //A MODIFIER

	//methodes en plus
	Plat* trouverPlat(const string& nom) const; // A MODIFIER
	Plat * trouverPlatMoinsCher() const; // Utilise les vecteurs (NE PAS MODIFIER)
	friend void operator+=(Menu& menu, Plat&  plat); // A MODIFIER
	bool lireMenu(const string& fichier);
	Menu& operator=(const Menu& menuSource);



private :
	// A MODIFIER
	vector<Plat*> listePlats_;
	TypeMenu type_;

};
ostream& operator<<(ostream& flux, const Menu& menu);
void operator+=( Menu& menu, Plat&  plat);

#endif // !MENU_H
