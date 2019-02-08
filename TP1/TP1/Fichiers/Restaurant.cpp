/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    Restaurant.cpp
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les   fonctions déclarées dans Restaurant.h
*/
#include "Restaurant.h"

Restaurant::Restaurant():  momentJournee_(Matin), menuMatin_(0), menuMidi_(0), menuSoir_(0), capaciteTables_(INTTABLES), tables_(0), nbTables_(0)
{// constructeur par defaut
	string nom = "inconnu";
	nom_ = &nom;
}

Restaurant::Restaurant(string & fichier, string & nom, TypeMenu moment): momentJournee_(moment), menuMatin_(0), menuMidi_(0), menuSoir_(0), capaciteTables_(INTTABLES), tables_(0), nbTables_(0)
{ // constructeur par parametre
	nom_ = &nom;
	 menuMatin_ = new Menu(fichier, Matin); // lisons les trois menus
	 menuMidi_ = new Menu(fichier, Midi);
	 menuSoir_ = new Menu(fichier, Soir);
	
	lireTable(fichier);
}


Restaurant::~Restaurant() //Destructor
{
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
	for (unsigned int i = 0; i < nbTables_; i++)
	{
		delete tables_[i]; // le restaurant et ses tables sont en composition, si on delete le restaurant, il faut delete les tables aussi
	}
	delete[] tables_;
}

void Restaurant::setMoment(TypeMenu moment){ // mettons l'attribut  momentJournee_ à la valeur moment
	momentJournee_ = moment;
}

string Restaurant::getNom() const{ // retournos le nom du restaurant
	return *nom_;
}

TypeMenu Restaurant::getMoment() const{ // retournos le moment de journée
	return momentJournee_;
}

void Restaurant::lireTable(string & fichier){ // lisons les tables a partir d'un fichier
	ifstream file(fichier, ios::in);  // on ouvre le fichier en lecture

	tables_ = new Table*[capaciteTables_]; // table vrs des pointeurs des tables
	string ligne = ""; // contient la ligne de debut de chaque partie
	int id = 0; // id de la table
	int  nbPlaces = 0; // nombre de place par table
	if (file)  // si l'ouverture a réussi
	{
		while (!ws(file).eof())
		{
			getline(file, ligne);
			if (ligne == "-TABLES") // on est dans la bonne partie
			{
				while (!ws(file).eof())
				{
					file >> id >> nbPlaces; // reccuerons les données
					ajouterTable(id, nbPlaces); // ajoutons la table a la liste des tables
				}
			}
		}
		file.close();  // on ferme le fichier
	}
}

void Restaurant::ajouterTable(int id, int nbPlaces){ // Ajout d'une table a la liste des tables
	
	if (nbTables_ >= capaciteTables_) //  elargeons le tableau si taille est insuffisante
	{
		Table** tables = tables_; // nouvelle variable qui contient l'ancien tanleau
		capaciteTables_ *= 2; // multiplions la capacité par deux
		tables_ = new Table*[capaciteTables_]; //allounat dynamiquement un nouveau tableau de la nouvelle capacité
		for (int i = 0; i < nbTables_; i++)  // copiant les anciens éléments
			tables_[i] = tables[i];
		delete[] tables; // Supression de l'ancien tableau
	}
	tables_[nbTables_] = new Table(id, nbPlaces);; // Ajoutans le plat au  tableau
	nbTables_++; // incrémentons le nombre de plats

}

void Restaurant::libererTable(int id) // mettre une table disponible
{
	for (int i = 0; i < nbTables_; i++) // bouclons la liste des tables
		if (tables_[i]->getId() == id && tables_[i]->estOccupee()) // table trouvée
		{
			chiffreAffaire_ += tables_[i]->getChiffreAffaire(); // reccuperons le chiffre d'affaire
			tables_[i]->libererTable(); // liberons la table
			break;
		}
}

void Restaurant::commanderPlat(string & nom, int idTable) // commande d'un plat par un client et l ajoutant a la liste de commandes
{

	Plat *plat = nullptr;
	switch (momentJournee_) // on cherche dans le menu correspond au moment de la journée
	{
	case Matin: plat = menuMatin_->trouverPlat(nom);
		break;
	case Midi: plat = menuMidi_->trouverPlat(nom);
		break;
	case Soir: plat = menuSoir_->trouverPlat(nom);
		break;
	default: break;
	}
	if (plat != nullptr) // Plat trouvé
		for (int i = 0; i < nbTables_; i++) // cherchons la table
		{
			if (tables_[i]->getId() == idTable) // table trouvée
			{
				if (tables_[i]->estOccupee()) // si elle est occupée
					tables_[i]->commander(plat);
				else // elle n 'est pas occupée , les clients sont partis !
					cout << "Erreur: table non occupee" << std::endl;
			}
		}
	else
		cout << "Erreur: table non occupee ou le plat introuvable" << std::endl; // Plat non trouvé 
}

void Restaurant::placerClients(int nbClients) // plaçons un nombre de peronnes dans une table intilligement
{
	Table* tableTrouve = nullptr;
	int nbMinPlaces = 100; // contient le nombre de place minimal trouvé dans le restaurant par table
	for (int i = 0; i < nbTables_; i++) // bouclons la table
		if (tables_[i]->estOccupee() == false && nbClients <= tables_[i]->getNbPlaces()) // les clients peuvent s'asseoir dans cette table
		{
			if (nbMinPlaces > tables_[i]->getNbPlaces()) // une table autorisée avec nombre de place plus petit
			{
				tableTrouve = tables_[i]; // tables trouvée
				nbMinPlaces = tableTrouve->getNbPlaces();
			}
		}
	if (tableTrouve == nullptr ) // pas de place correspondante
		std:cout << "Erreur: il n'ya plus/pas de table disponible pour le client" << std::endl;
	else
	{
		tableTrouve->placerClient(); // plaçons les clients si la table est trouvée
	}
}

void Restaurant::afficher() const // Affichage de la restaurant
{
	std::cout << "Le restaurant " << *nom_ ; // Nom du restaurant
	if (chiffreAffaire_ == 0) // pas de chiffre d'affaire
		std::cout << " n'a pas fait de benifice ou le chiffre d'affaire n'est pas encore calcule. " << std::endl << std::endl;
	else // on a fait un chiffre d'affaire $-$
		std::cout << " a  fait un chiffre  d'affaire de : " << chiffreAffaire_ << "$" << std::endl << std::endl ;
	std::cout << "-Voici les tables:" << std::endl; // Affichage des tables
	for (int i = 0; i < nbTables_; i++)
	{
		std::cout << "	";
		tables_[i]->afficher(); // appelons la methose afficher()
	}
	// Affichage des menus
	std::cout << std::endl;
	std::cout << "Voici son menu:" << std::endl;
	menuMatin_->afficher();
	std::cout << std::endl;
	menuMidi_->afficher();
	std::cout << std::endl;
	menuSoir_->afficher();
	std::cout << std::endl;
}
