/*
INF1010 � PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Table.h
Th�me: Allocation dynamique, composition et agr�gation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les d�claration des fonctions impl�ment� dans Table.cpp
*/

#ifndef TABLE_H
#define TABLE_H

#include "Menu.h"
const  int MAXCAP = 5;
class Table {
public: 
	//constructeurs 
	Table();  // constructeur par defaut
	Table(int id, int nbPlaces); // constructeur par parametre

	//Destructeur
	~Table();

	//getters 
	int getId() const;   // retourne l'identifiant  de la table
	int getNbPlaces() const;  // retourne le nombre de places  de la table
	bool estOccupee() const;   // retourne l'�tat de la table est ce qu'lle est occup�e ou libre

	//setters 
	void libererTable(); // mettre une table non occup�e 
	void placerClient(); // mettre une table occup�e
	void setId(int id);  // mettre le id_ a la valeur id

	//autres methodes 
	void commander(Plat* plat); // ajouter une commande a la liste des commandes 
	double getChiffreAffaire() const;  // retournons le chiffre d'affaire gagn� par cette table

	//affichage
	void afficher() const; // affichage de commande de la table
private : 
	Plat** commande_; // liste qui contient la liste des plats commandes par les clients d'une table (sont des pointeurs)
	unsigned int capacite_; // taille maximale d'un tableau
	unsigned int nbPlats_; // nombre de plat command�s par table

	int id_;  // Identifiant de la table
	unsigned int nbPlaces_;  // nombe de place de la table
	bool occupee_;  // etat de la table
};
#endif // !TABLE_H
