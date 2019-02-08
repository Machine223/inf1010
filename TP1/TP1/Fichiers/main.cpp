/*
INF1010 – PROGRAMMATION ORIENTEE OBJET
Travail pratique No. 1
file:    main.cpp
Thème: Allocation dynamique, composition et agrégation
Auteur: ABDELKADER ZOBIRI 1891451 - Abderrahim Ammour 1924705
Date: 04 Fivrier 2019
Ce code contient les tests de pour toutes les fonctions crées ainsi que la lecture de fichier et les gérer
*/

#include "Restaurant.h"

using namespace std; 

int main() {

	//creation du restaurant - avec le fichier donne - le nom : PolyFood - moment de la journee : soir. 
	TypeMenu typeMenu = Soir;
	string fichier = "polyFood.txt", nomRestaurant = "PolyFood";
	Restaurant restaurant(fichier, nomRestaurant, typeMenu);
	//creer plusieurs clients -- des entiers 

	int client1 = 1; 
	int client2 = 5; 
	int client3 = 15; 
	int client4 = 3; 
	int client5 = 2; 

	//placer les clients 
	restaurant.placerClients(client1);
	restaurant.placerClients(client2);
	restaurant.placerClients(client3);
	restaurant.placerClients(client4);
	restaurant.placerClients(client5);

	// commander des plats
	//Poisson - Table 1 
	//Poulet - Table 2 
	//Pizza - Table 2 
	//Poulet - Table 4
	//Muffin - Table 4 
	//Oeud - Table 4 
	string plat = "Poisson";
	restaurant.commanderPlat(plat, 1);
	plat = "Poulet";
	restaurant.commanderPlat(plat, 2);
	plat = "Pizza";
	restaurant.commanderPlat(plat, 2);
	plat = "Poulet";
	restaurant.commanderPlat(plat, 4);	
	plat = "Muffin";
	restaurant.commanderPlat(plat, 4);
	plat = "Oeuf";
	restaurant.commanderPlat(plat, 4);
	//afficher le restaurant
	restaurant.afficher(); 
	cout << "-------------------------------------------------" << std::endl;

	//liberer les tables 
	restaurant.libererTable(1);
	restaurant.libererTable(2);
	restaurant.libererTable(3);
	restaurant.libererTable(4);
	//afficher le restaurant 
	
	restaurant.afficher(); 
	return 0;

}