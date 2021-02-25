#ifndef _CARTE_H
#define _CARTE_H
#include "structures.h"

/*rajouter un type à struct card ?*/
int CardType(card c);

/*retourne le cout en PE d'une carte*/
int getPe(card c);

/*retourne la durabilité d'un élève*/
int getdurability(student c);

/*retourne la taille du deck du joueur*/
int DeckSize(ensiie e);

#endif