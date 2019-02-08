/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 2
file:    Plat.h
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 11 Fivrier 2019
Ce code contient les déclaration des fonctions implémenté dans Plat.cpp
*/

#ifndef PLAT_H
#define PLAT_H

#include <string>
#include <iostream>

using namespace std;

class Plat {
public:
	/// constructeurs
	Plat();
	Plat(string nom, double prix, double cout);

	///getters
	string getNom() const;
	double getPrix() const;
	double getCout() const;

	///setters
	void setNom(string nom);
	void setPrix(double prix);

	///methodes en plus
	friend ostream& operator<<(ostream& flux, const Plat& plat); // Afficher les caracteristiques  d un plat
	friend bool operator<(const Plat& plat1, const Plat& plat2);

private:
	string nom_;
	double prix_;
	double cout_;

};
ostream& operator<<(ostream& flux, const Plat& plat);
bool operator<(const Plat& plat1, const Plat& plat2) ;

#endif // !PLAT_H
