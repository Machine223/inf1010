#include "Menu.h"
#include "fstream"
Menu::Menu() : capacite_(MAXPLAT), listePlats_(0), nbPlats_(0), type_(Matin)
{
	listePlats_ = new Plat*[capacite_];
}

Menu::Menu(string fichier, TypeMenu type) : capacite_(MAXPLAT), listePlats_(0), nbPlats_(0), type_(type)
{
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
	std::cout << type_ << " :";
	for (int i = 0; i < nbPlats_; i++)
		listePlats_[i]->afficher();
}

Plat * Menu::trouverPlat(string & nom)
{
	for (int i = 0; i< nbPlats_; i++)
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i];
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
	listePlats_[nbPlats_] = &plat;
	nbPlats_++;
}

void Menu::ajouterPlat(string & nom, double montant, double cout)
{
	Plat plat(nom, montant, cout);
	ajouterPlat(plat);
}

bool Menu::lireMenu(string & fichier)
{
	ifstream file(fichier, ios::in);  // on ouvre le fichier en lecture

	listePlats_ = new Plat*[capacite_];
	string mot = "";
	double prix = 0;
	double cout = 0;
	TypeMenu type;
	if (file)  // si l'ouverture a réussi
	{
		while (!ws(file).eof())
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
						break;
					}
				}
			}
		}
		file.close();  // on ferme le fichier
	}
	if (nbPlats_ = 0)
		return false;
	return true;
}
