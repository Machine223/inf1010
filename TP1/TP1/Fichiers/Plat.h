/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Plat.h
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les déclaration des fonctions implémenté dans Plat.cpp
*/

#ifndef PLAT_H
#define PLAT_H

#include <string>
#include <iostream>

using namespace std; 

class Plat {
public: 
	// constructeurs
	Plat();  // constructeur par defaut
	Plat(string& nom, double prix, double cout); // constructeur par parametres

	//getters 
	string getNom() const;  // retourne le nom de plat
	double getPrix() const; // retourne le  prix de plat
	double getCout() const; // retourne le cout de plat

	//setters 
	void setNom(string nom);  // mettre l'attribut nom_ a la valeur nom
	void setPrix(double prix);  // mettre l'attribut prix_ a la valeur nom
	
	//affichage
	void afficher() const;  // Affiche un plat

private: 
	string nom_;  // nom du plat
	double prix_;  // prix de plat
	double cout_;  // cout de plat

};

#endif // !PLAT_H
