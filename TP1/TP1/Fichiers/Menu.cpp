#include "Menu.h"
#include <fstream>
#include <string>

Menu::Menu() : capacite_(MAXPLAT), listePlats_(nullptr), nbPlats_(0), type_(Matin)
{
	listePlats_ = new Plat*[capacite_];
}

Menu::Menu(string fichier, TypeMenu type) : capacite_(MAXPLAT), listePlats_(nullptr), nbPlats_(0), type_(type)
{
	listePlats_ = new Plat*[capacite_];
	lireMenu(fichier);
}

Menu::~Menu()
{
	for (int i = 0; i < nbPlats_; i++)
	{
		delete listePlats_[i];
	}
	delete listePlats_;
}

int Menu::getNbPlats() const
{

		return nbPlats_;

}

void Menu::afficher()
{
	std::cout << type_ << " :" << std::endl;
	for (int i = 0; i < nbPlats_; i++)
		listePlats_[i]->afficher();
}

Plat* Menu::trouverPlat(string & nom)
{
	string nomPlat = "";
	for (int i = 0; i < nbPlats_; i++)
	{
		nomPlat = listePlats_[i]->getNom(); 
			if (nom == nomPlat)
				return listePlats_[i];
	}		
	return nullptr;
}

void Menu::ajouterPlat(Plat & plat)
{
	if(nbPlats_>=capacite_)
	{
		Plat** listePlats = listePlats_;
		capacite_ *= 2;
		listePlats_ = new Plat*[capacite_];
		for (int i = 0; i< nbPlats_; i++)
			listePlats_[i] = listePlats[i];
		delete listePlats;
	}
	listePlats_[nbPlats_] = new Plat(plat);
}

void Menu::ajouterPlat(string& nom, double montant, double cout)
{
	Plat plat = Plat(nom, montant, cout);
	ajouterPlat(plat);
	nbPlats_++;
}

bool Menu::lireMenu(string & fichier)
{
	ifstream file(fichier, ios::in);  // on ouvre le fichier en lecture
	string mot = "";
	double prix = 0.0;
	double cout = 0.0;
	bool menuLu = false;
	TypeMenu type;
	if (file)  // si l'ouverture a réussi
	{
		while (!menuLu)
		{
			getline(file, mot);
			if (mot == "-MATIN")
				type = Matin;
			if (mot == "-MIDI")
				type = Midi;
			if (mot == "-SOIR")
				type = Soir;
			if (type == type_)
			{
				while (!ws(file).eof())
				{
					file >> mot;
					if (mot[0] != '-')
					{
						file >> prix >> cout;
						ajouterPlat(mot, prix, cout);
					}
					else
					{
						menuLu = true;
						break;
					}
				}
			}
		}
		file.close();  // on ferme le fichier
	}
	else
	{
		std::cout << "fichier ne s'ouvre pas" << std::endl;
	}
		
	if (nbPlats_ == 0)
		return false;
	return true;
}

std::ostream &operator<<(std::ostream &flux, TypeMenu const& type)
{
	if (type == 0)
		flux << "Matin";
	if (type == 1)
		flux << "Midi";
	if (type == 2)
		flux << "Soir";
	return flux;
}