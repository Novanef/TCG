#include <stdio.h>
#include "../headers/carte.h"

/*rajouter un type à struct card ?*/
int CardType(card c)
{
    return c.type;
}
/*retourne le cout en PE d'une carte*/
int getPe(card c)
{
    return c.cost;
}

int getdurability(student c)
{
    return c.durability;
}
/*on retourne l'entier decknum indiquant où on est dans le deck 
ou on fait des listes*/
int DeckSize(ensiie e)
{
    return length_pile(e.deck);
}
