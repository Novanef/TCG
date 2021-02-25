#ifndef _DECK_H
#define _DECK_H
#include "plateau.h"

/* affiche toutes les cartes du jeu*/
void print_collection();

/*affiche toutes les cartes du jeu et un deck*/
void print_collection_and_deck(pile deck);

/*sauvegarde le deck créé*/
void confirm_deck(pile deck,char* nom_deck);

/*supprime un deck enregistré*/
void delete_deck(char* nom_deck);

/* affiche le nom des decks enregistrés*/
void list_deck();

/* demande à l'utilisateur quel deck il veut jouer parmi les decks enregistrés*/
char* choose_deck();

/*Permet au joueur de créer un nouveau deck*/
pile create_deck();

/* change le deck d'un jouer par le deck en argument*/
void swap_deck(ensiie* e, char* nom_deck);

#endif