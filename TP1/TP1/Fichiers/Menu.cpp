/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Menu.cpp
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les implémentations des fonctions définies dans Menu.h
*/


#include "Menu.h"
#include <fstream>
#include <string>

Menu::Menu() : capacite_(MAXPLAT), listePlats_(nullptr), nbPlats_(0), type_(Matin) // constructeur par defaut
{
	listePlats_ = new Plat*[capacite_]; // allocation dynamique de tableau qui contients des pointeurs vers des plats
}

Menu::Menu(string fichier, TypeMenu type) : capacite_(MAXPLAT), listePlats_(nullptr), nbPlats_(0), type_(type) // constructeur par parametre
{
	listePlats_ = new Plat*[capacite_]; //  allocation dynamique de tableau de pointeurs de plat
	lireMenu(fichier); // lecture des plats a partir d'un fichier "polyFood.txt"
}

Menu::~Menu() // Destructeur
{
	for (int i = 0; i < nbPlats_; i++) // Supression des objets Plat
	{
		delete listePlats_[i];
	}
	delete[] listePlats_ ; // Supression du tableau
}

int Menu::getNbPlats() const // une méthode constante qui retourne le nombre de plats
{
		return nbPlats_;
}

void Menu::afficher() const // Méthode d'affichage 
{
	std::cout << type_ << " :" << std::endl;
	for (int i = 0; i < nbPlats_; i++)
		listePlats_[i]->afficher();
}

Plat* Menu::trouverPlat(string & nom) const // Cherchons un plat par nom et on recupere le pointeur vers ce point nullptr si il n'existe pas
{
	string nomPlat = "";
	for (int i = 0; i < nbPlats_; i++) // Bouclons tous le tableau qui contient des pointeurs vers des plats
	{
		nomPlat = listePlats_[i]->getNom();  
			if (nom == nomPlat) // comparons les deux strings
				return listePlats_[i];
	}		
	return nullptr; // s'il n'existe pas
}

void Menu::ajouterPlat(Plat & plat) // Ajout d'un plat dans une liste de plat
{
	if(nbPlats_>=capacite_) // verifions si le tableau est rempli
	{ // elargeons le tableau 
		Plat** listePlats = listePlats_; // nouvelle variable qui contient l'ancien tanleau
		capacite_ *= 2; // multiplions la capacité par deux
		listePlats_ = new Plat*[capacite_]; //allounat dynamiquement un nouveau tableau de la nouvelle capacité
		for (int i = 0; i< nbPlats_; i++) // copiant les anciens éléments
			listePlats_[i] = listePlats[i];
		delete[] listePlats; // Supression de l'ancien tableau
	}
	listePlats_[nbPlats_] = new Plat(plat); // Ajoutans le plat au  tableau
}

void Menu::ajouterPlat(string& nom, double montant, double cout)
{
	Plat plat = Plat(nom, montant, cout); // creons une variable qui contieny notre plat
	ajouterPlat(plat); // ajoutons - le dans un tableau
	nbPlats_++; // incrémentant le nombre de plat dans le tableau
}

bool Menu::lireMenu(string & fichier) // lire les données présentes dans le fichier
{
	ifstream file(fichier, ios::in);  // on ouvre le fichier en lecture
	string mot = ""; // va contenir le moment et le nom du plat
	double prix = 0.0; // le prix du plat
	double cout = 0.0; // le cout payé par le restaurant
	bool menuLu = false; // verifier si le menu a été lu
	TypeMenu type; // contient le type de chaque menu dans le fichier
	if (file)  // si l'ouverture a réussi
	{
		while (!menuLu) // si le menu n'est pas encore lu
		{
			getline(file, mot); // lisons la premiere ligne
			if (mot == "-MATIN") // si c'est matin
				type = Matin; 
			if (mot == "-MIDI") // si c'est midi
				type = Midi;
			if (mot == "-SOIR") // si c'set soir
				type = Soir;
			if (type == type_) // si le type lu correspond au moment de la journée
			{
				while (!ws(file).eof()) // commen_ons a lire les données
				{
					file >> mot; // nom du plat
					if (mot[0] != '-') // si on aest pas encore arrivé a la fin du Menu
					{
						file >> prix >> cout; // lisons le prix et le cout
						ajouterPlat(mot, prix, cout);
					}
					else // si on est arivé a la fin du menu
					{
						menuLu = true; // on sort du premier while
						break; // on sort  du deuxieme while
					}
				}
			}
		}
		file.close();  // on ferme le fichier
	}
	else
	{
		std::cout << "fichier ne s'ouvre pas" << std::endl; // Lecture échouée
	}
		
	if (nbPlats_ == 0) // Lecture n'est pas réussie
		return false;
	return true;
}

std::ostream &operator<<(std::ostream &flux, TypeMenu const& type) // pour l'affichage du string a partir d'un type enum
{
	if (type == 0)
		flux << "Matin";
	if (type == 1)
		flux << "Midi";
	if (type == 2)
		flux << "Soir";
	return flux;
}