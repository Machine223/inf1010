#include "Restaurant.h"

Restaurant::Restaurant():  momentJournee_(Matin), menuMatin_(0), menuMidi_(0), menuSoir_(0), capaciteTables_(INTTABLES), tables_(0), nbTables_(0)
{
	string nom = "inconnu";
	nom_ = &nom;
}

Restaurant::Restaurant(string & fichier, string & nom, TypeMenu moment): momentJournee_(moment), menuMatin_(0), menuMidi_(0), menuSoir_(0), capaciteTables_(INTTABLES), tables_(0), nbTables_(0)
{
	nom_ = &nom;
	 menuMatin_ = new Menu(fichier, Matin);
	 menuMidi_ = new Menu(fichier, Midi);
	 menuSoir_ = new Menu(fichier, Soir);
	
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
	if (file)  // si l'ouverture a réussi
	{
		while (!ws(file).eof())
		{
			getline(file, ligne);
			if (ligne == "-TABLES")
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
	
	if (nbTables_ >= capaciteTables_)
	{
		Table** tables = tables_;
		capaciteTables_ *= 2;
		tables_ = new Table*[capaciteTables_];
		for (int i = 0; i < nbTables_; i++)
			tables_[i] = tables[i];
		delete tables;
	}
	tables_[nbTables_] = new Table(id, nbPlaces);;
	nbTables_++;
}

void Restaurant::libererTable(int id)
{
	for (int i = 0; i < nbTables_; i++)
		if (tables_[i]->getId() == id && tables_[i]->estOccupee())
		{
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
			break;
		}
}

void Restaurant::commanderPlat(string & nom, int idTable)
{
	Plat *plat = nullptr;
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
	if (plat != nullptr)
		for (int i = 0; i < nbTables_; i++)
		{
			if (tables_[i]->getId() == idTable)
			{
				tables_[i]->commander(plat);
			}
		}
	else
		cout << "Erreur: table non occupee ou le plat introuvable" << std::endl;
}

void Restaurant::placerClients(int nbClients)
{
	Table* tableTrouve = nullptr;
	int nbMinPlaces = 100; // contient le nombre de place minimal trouvé dans 
	for (int i = 0; i < nbTables_; i++)
		if (tables_[i]->estOccupee() == false && nbClients <= tables_[i]->getNbPlaces())
		{
			if (nbMinPlaces > tables_[i]->getNbPlaces())
			{
				tableTrouve = tables_[i];
				nbMinPlaces = tableTrouve->getNbPlaces();
			}
		}
	if (tableTrouve == nullptr )
		std:cout << "Erreur: il n'ya plus/pas de table disponible pour le client" << std::endl;
	else
	{
		tableTrouve->placerClient();
	}
}

void Restaurant::afficher() const
{
	std::cout << "Le restaurant " << *nom_ ;
	if (chiffreAffaire_ == 0)
		std::cout << " n'a pas fait de benifice ou le chiffre d'affaire n'est pas encore calcule. " << std::endl << std::endl;
	else
		std::cout << " a  fait un chiffre  d'affaire de : " << chiffreAffaire_ << "$" << std::endl << std::endl ;
	std::cout << "-Voici les tables:" << std::endl;
	for (int i = 0; i < nbTables_; i++)
	{
		std::cout << "	";
		tables_[i]->afficher();
	}
	std::cout << std::endl;
	std::cout << "Voici son menu:" << std::endl;
	menuMatin_->afficher();
	std::cout << std::endl;
	menuMidi_->afficher();
	std::cout << std::endl;
	menuSoir_->afficher();
	std::cout << std::endl;
}
