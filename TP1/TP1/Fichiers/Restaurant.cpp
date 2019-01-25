#include "Restaurant.h"

Restaurant::Restaurant(): nom_(0), momentJournee_(Matin), menuMatin_(0), menuMidi_(0), menuSoir_(0), capaciteTables_(INTTABLES), tables_(0), nbTables_(0)
{
	string nom = "inconnu";
	nom_ = &nom;
}

Restaurant::Restaurant(string & fichier, string & nom, TypeMenu moment):nom_(0), momentJournee_(Matin), menuMatin_(0), menuMidi_(0), menuSoir_(0), capaciteTables_(INTTABLES), tables_(0), nbTables_(0)
{
	nom_ = &nom;
	switch (moment)
	{
	case Matin: menuMatin_ = new Menu(fichier, Matin);
		break;
	case Midi: menuMidi_ = new Menu(fichier, Midi);
		break;
	case Soir: menuSoir_ = new Menu(fichier, Soir);
		break;
	default: break;
	}
	lireTable(fichier);
}

void Restaurant::setMoment(TypeMenu moment){
	momentJournee_ = moment;
}

string Restaurant::getNom() const{
	return *nom_;
}

TypeMenu Restaurant::getMoment() const{
	return momentJournee_;
}

void Restaurant::lireTable(string & fichier){
	ifstream file(fichier, ios::in);  // on ouvre le fichier en lecture

	tables_ = new Table*[capaciteTables_];
	string ligne = "";
	int id = 0;
	int  nbPlaces = 0;
	TypeMenu type;
	if (file)  // si l'ouverture a réussi
	{
		while (!ws(file).eof())
		{
			getline(file, ligne);
			if (ligne == "TABLES_")
			{
				while (!ws(file).eof())
				{
					file >> id >> nbPlaces;
					ajouterTable(id, nbPlaces);
				}
			}
		}
		file.close();  // on ferme le fichier
	}
}

void Restaurant::ajouterTable(int id, int nbPlaces){
	Table table(id, nbPlaces);
	if (nbTables_ >= capaciteTables_)
	{
		Table** tables = tables_;
		capaciteTables_ *= 2;
		tables_ = new Table*[capaciteTables_];
		for (int i = 0; i < nbTables_; i++)
			tables_[i] = tables[i];
		delete tables;
	}
	tables_[nbTables_] = &table;
	nbTables_++;
}

void Restaurant::libererTable(int id)
{
	for (int i = 0; i < nbTables_; i++)
		if (tables_[i]->getId() == id && tables_[i]->estOccupee())
		{
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
			nbTables_--;
		}
		
}

void Restaurant::commanderPlat(string & nom, int idTable)
{
	Plat *plat;
	switch (momentJournee_)
	{
	case Matin: plat = menuMatin_->trouverPlat(nom);
		break;
	case Midi: plat = menuMidi_->trouverPlat(nom);
		break;
	case Soir: plat = menuSoir_->trouverPlat(nom);
		break;
	default: break;
	}
	for (int i = 0; i < nbTables_; i++)
		if (tables_[i]->getId() == idTable )
		{
			tables_[i]->commander(plat);
		}
}

void Restaurant::placerClients(int nbClients)
{
	Table* tableTrouve = nullptr;
	for (int i = 0; i < nbTables_; i++)
		if (tables_[i]->estOccupee() == false && nbClients >= tables_[i]->getNbPlaces())
		{
			if (tableTrouve->getNbPlaces() < tables_[i]->getNbPlaces() || tableTrouve == nullptr)
				tableTrouve = tables_[i];
		}
	if (tableTrouve == nullptr )
		std:cout << "aucune table libéré trouvé" << endl;
}

void Restaurant::afficher() const
{
	std::cout << "Le restaurant" << nom_;
	if (chiffreAffaire_ != 0)
		std::cout << "n'a pas fait de benifice ou le chiffre d'affaire n'est pas encore calcule." << endl;
	else
		std::cout << "a  fait un chiffre  d'affaire de " << chiffreAffaire_ << "$" << endl;
	std::cout << "Voici les tables:" << endl;
	for (int i = 0; i < nbTables_; i++)
	{
		std::cout << "		-";
		tables_[i]->afficher();
	}
	std::cout << "Voici son menu:" << endl;
	std::cout << "Matin:" << endl;
	menuMatin_->afficher();
	std::cout << "Midi:" << endl;
	menuMidi_->afficher();
	std::cout << "Soir:" << endl;
	menuSoir_->afficher();
}
