#ifndef _PLATEAU_H
#define _PLATEAU_H
#include "carte.h"

/*retourne 0 si le tour est pair ou 1 si il est impair */
int ParityTurn(board b);

/*retourne le nb max de Personnel pouvant être présent simultanément sur un coté du terrain*/
int NbMaxPersonnel(board b);

/*retourne le nombre de cartes personnel sur le terrain d'une ensiie*/
int NbPersonnel(ensiie e);

/*change les valeurs du développement (si mode==0) ou de la durabilité (mode==1)
des cartes élèves de la pile d'une ensiie*/
void ChangeStudent(queue_student* eleves,int value,int mode);

/*active l'effet d'une carte*/
void TriggerEffect(card c,ensiie *player,ensiie* opponent);

/*renvoie le personnel correspondant à l'effet d'une carte*/
Personnel FindEffect(card c);

/*Joue la carte personnel c et la pose sur le champ, en enlevant la carte personnel la plus ancienne du plateau si besoin*/
void PlayPersonnel(card c,ensiie* player,ensiie* opponent,board b);

/*mélange une pile*/
void shuffle(pile *p);

/*Joue la carte action c et l'envoie dans la défausse*/
void PlayAction(card c, ensiie* player,ensiie* opponent);

/*Joue la carte c*/
void PlayCard(card c,ensiie* e,ensiie* o,board b);

/* retourne un deck contenant les 31 cartes du jeu dans un ordre aléatoire*/
pile init_deck();

/* création d'un joueur*/
ensiie create_ensiie(void);

/* création d'un plateau vierge */
board create_board(void);

/*suppression d'un joueur à la fin de la partie*/
void erase_ensiie(ensiie* e);

/*suppression d'un plateau à la fin de la partie */
void erase_board(board *b);

/*incrémentation du compteur de tour */
void newturn(board *b);

/*détermine et renvoie le nombre de cartes à piocher au début du tour d'un joueur */
int nbdraw(ensiie e, board b);

/*fait piocher le nombre de cartes défini par nbdraw */
void draw(ensiie *e,int d);

/* ajoute une carte FISE sur le plateau de l'ENSIIE p*/
void addFISECard(ensiie *p);

/* ajoute une carte FISE sur le plateau de l'ENSIIE p*/
void addFISACard(ensiie *p);

/* compte le nombre de PE disponible pour l'ENSIIE P*/
int countPE(ensiie p, board b);

/* permet à l'ENSIIE p de jouer la carte c*/
int allowPlayCard(ensiie p,card c);

/* calcule les DD de chaque joueur*/
void endTurn(board *b);

/* renvoie 1 si le joueur 1 a gagné, 2 si le joueur 2 a gagné, 3 s'il y a égalité, 0 sinon*/
int endGame(board b);

#endif