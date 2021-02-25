#ifndef _STRUCTURES_H
#define _STRUCTURES_H

/* type d'une carte (FISE/FISA, personnel, action)*/
enum type
{
  Eleve,
  personnel,
  Action
};

/*type général des cartes*/
typedef struct card
{
  int ID;         /*ID de la carte*/
  char name[256]; /*nom de la carte*/
  int cost;       /*coût de la carte*/
  enum type type; /*0=student,1=Personnel,2=Action.  Les cartes Personnels ont un type student dédié pour gérer les effets*/
} card;

extern card collection[31];/*tableau de toutes les cartes différentes du jeu*/

/* structure de cartes en FIFO*/
typedef struct element *queue;

/* structure de chaînon de carte*/
typedef struct element
{
  card value;
  queue next;
} element;

/*structure de cartes en FILO*/
typedef struct element *pile;

/*type des cartes FISE/FISA*/
typedef struct student
{
  int development; /*Nombre de points de développement donné à chaque fin de tour*/
  int durability;  /*Nombre de points de durabilité donné à chaque fin de tour*/
} student;

/*structure de carte FISE/FISA en FILO*/
typedef struct element_student *queue_student;

/*structure de chaînon du type spécifique aux cartes FISE/FISA*/
struct element_student
{
  student value;
  queue_student next;
};

/*type des cartes Personnel, l'ID correspond à la valeur ID du type card*/
typedef struct Personnel
{
  int ID;        /*ID de la carte (même que card)*/
  int number;    /*Nombre d'effets*/
  int effect[8]; /*Tableau des ID des effets*/
  int value[8];  /*tableau des valeurs (numériques) des effets dans le même ordre que effects*/
} Personnel;

/*type joueur/ensiie, contient toutes les informations sur un des deux joueurs*/
typedef struct ensiie
{
  queue hand;           /*contenu de la main du joueur*/
  queue field;          /*cartes personnel en jeu*/
  queue discard;        /*défausse*/
  pile deck;            /*contenu du deck*/
  queue_student FISE;   /*cartes FISE jouées*/
  queue_student FISA;   /*cartes FISA jouées*/
  int Student_Nbr;      /*nombre d'élèves qu'on peut poser au début de chaque tour*/
  int PE;               /*nombre de PE disponible ce tour*/
  int DD;               /*nombre de DD gagné*/
  int bonuscard;        /*nombre de cartes piochées au début de chaque tour*/
  int FISE_Development; /*nombre de points de développement que chaque FISE apporte par défaut en entrant en jeu*/
  int FISE_Durability;  /*nombre de points de durabilité que chaque FISE apporte par défaut en entrant en jeu*/
  int FISA_Development; /*nombre de points de développement que chaque FISA apporte par défaut en entrant en jeu*/
  int FISA_Durability;  /*nombre de points de durabilité que chaque FISA apporte par défaut en entrant en jeu*/
} ensiie;

/*type plateau, contient toutes les informations de la partie en cours */
typedef struct board
{
  ensiie player1; /*joueur 1*/
  ensiie player2; /*joueur 2*/
  int turn;       /*compteur de tour*/
} board;

/*------------------------------------------------------*/

/*donne un nombre aléatoire entre 0 et n*/
int random(int n);

/*affiche les paramètres de c*/
void print_card(card c);

/*ajoute par effet une carte à une pile */
void stack(pile *p, card value);

/*enlève et retourne la dernière carte ajoutée à p*/
card unstack(pile *p);

/*enlève et retourne le premier élève ajouté à q*/
student unstack_student(queue_student *q);

/* ajoute par effet un student à une queue_student */
void stack_student(queue_student *q, student value);

/*supprime les éléments de la queue_student ainsi que les allocations mémoire*/
void free_queue_student(queue_student *q);

/*retourne la longueur de la queue_student q*/
int length_queue_student(queue_student q);

/*supprime les éléments de la pile ainsi que les allocations mémoire*/
void free_pile(pile *p);

/*affiche p*/
void display_pile(pile p);

/*retourne la longueur de la pile p*/
int length_pile(pile p);

/*ajoute value à queue*/
void thread(queue *q, card value);

/*enlève et retourne la première carte ajoutée à queue*/
card unthread(queue *q);

/* enlève et retourne la carte c d'une queue q*/
card pick(queue *q, card c);

/*affiche q*/
void display_queue(queue q);

/*supprime les éléments de la queue ainsi que les allocations mémoire*/
void free_queue(queue *q);

/*retourne la longueur de la queue q*/
int length_queue(queue q);

#endif