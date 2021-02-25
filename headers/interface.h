#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "deck.h"

/*demande au joueur s'il veut jouer une carte FISE ou FISA,
 renvoie 1 pour FISE, 2 pour FISA et 0 pour RIEN*/
int AskStudent();

/*retourne la position de la carte que le joueur souhaite jouer depuis sa main 
ou bien 0 pour finir la phase du joueur*/
int AskAction(ensiie *e);

/*afficher toutes les informations*/
void show_information(board b, ensiie e);

/*afficher qu'une nouvelle phase commence pour le joueur i*/
void show_begin(board b, int i);

/*afficher le plateau*/
void show_board(board b);

/*demander à un joueur qui reçoit une nouvelle carte Elève s’il souhaite ajouter une carte FISE ou FISA*/
int ask_fisefisa(ensiie e);

/*demande à un joueur de choisir une carte de sa main, renvoie l'adresse de la carte ou une carte nulle {0,"",0,0} si le joueur choisit de finir sa phase*/
card ask_choosecard(ensiie e);

/*afficher le gagnant du jeu ou egalite le cas echeant*/
void show_winner(int i);

/*Affiche les cartes contenues dans une structure*/
void print_deck(ensiie e);

/*Affiche les cartes contenues dans une structure*/
void print_discard(ensiie e);

/*Affiche les cartes contenues dans une structure*/
void print_hand(ensiie e);

/*Affiche les cartes contenues dans une structure*/
void print_field(ensiie e);

/*Permet à l'utilisateur de choisir parmi les différentes  fonctionnalités de l'éditeur de deck*/
void deck_editor();

/*Permet à l'utilisateur de choisir s'il veut jouer ou aller dans l'éditeur de deck, renvoie 1 pour la partie et 0 pour le deck editor*/
int choose_mode();

#endif