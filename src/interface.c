#include "../headers/interface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*demande au joueur s'il veut jouer une carte FISE ou FISA,
 renvoie 1 pour FISE, 2 pour FISA et 0 pour RIEN*/
int AskStudent()
{
    char choice[256] = "";
    printf(" FISE OU FISA OU RIEN?\n");
    printf("-FISE   -FISA   -RIEN\n");
    while (strncmp(choice, "FISE", 4) != 0 || strncmp(choice, "FISA", 4) != 0 || strncmp(choice, "RIEN", 4) != 0)
    {
        fgets(choice, 256, stdin);
        if (strncmp(choice, "FISE", 4) == 0)
        {
            return 1;
        }
        if (strncmp(choice, "FISA", 4) == 0)
        {
            return 2;
        }
        if (strncmp(choice, "RIEN", 4) == 0)
        {
            return 0;
        }
    }
    return 0;
}

/*demande à un joueur de choisir une carte de sa main, renvoie l'adresse de la carte ou une carte nulle {0,"",0,0} si le joueur choisit de finir sa phase*/
card ask_choosecard(ensiie e)
{
    char ask[256] = "";
    printf("Choisissez une action à mener :\n");
    printf("-play x : joue la carte à la position x de votre main\n");
    printf("-DD : affiche vos DD actuels\n");
    printf("-discard: montre les cartes de votre de defausse\n");
    printf("-eleve: donne le nombre d'eleves dans les piles\n");
    printf("-end : mets fin à votre tour\n");
    printf("PE : %i\n", e.PE);
    print_hand(e);
    print_field(e);
    while (strncmp(ask, "end", 3) != 0)
    {
        fgets(ask, 256, stdin);
        if (!strncmp(ask, "play", 4) && strlen(ask) >= 6)
        {
            int position = 0;
            char askbis[256];
            sscanf(ask, "%s %d", askbis, &position);
            if (position <= length_pile(e.hand))
            {
                queue *temp = &e.hand;
                for (int i = 0; i < position - 1; i++)
                {
                    *temp = (*temp)->next;
                }
                return ((*temp)->value);
            }
        }
        if (strncmp(ask, "DD", 2) == 0)
        {
            printf("DD du joueur:%i\n", e.DD);
        }
        if (strncmp(ask, "discard", 7) == 0)
        {
            print_discard(e);
        }
        if (strncmp(ask, "eleve", 5) == 0)
        {
            printf("la queue FISE comporte %i eleves et la queue FISA %i\n", length_queue_student((&e)->FISE), length_queue_student((&e)->FISA));
        }
        else
        {
            printf("Entrez une nouvelle commande\n");
        }
    }
    card nocard = (card){0, "", 0, 0};
    return nocard;
}

/*afficher toutes les informations*/
void show_information(board b, ensiie e)
{
    print_hand(e);
    printf("PE : %i\n", e.PE);
    printf("DD joueur 1 : %i\n", b.player1.DD);
    printf("DD joueur 2 : %i\n", b.player2.DD);
    print_field(b.player1);
    print_field(b.player2);
}
void show_board(board b)
{
    printf("Player1 DD:%i   Player2 DD:%i\n", b.player1.DD, b.player2.DD);
    printf("Player1 PE:%i Player2 PE:%i\n", b.player1.PE, b.player2.PE);
    if (length_queue_student(b.player1.FISE) != 0 && length_queue_student(b.player2.FISE) != 0)
    {
        printf("Player1 student durability :%i Player 2:%i", b.player1.FISE->value.durability, b.player2.FISE->value.durability);
    }
    if (length_queue_student(b.player1.FISA) != 0 && length_queue_student(b.player2.FISA) != 0)
    {
        printf("Player1 student durability :%i Player 2:%i", b.player1.FISE->value.durability, b.player2.FISE->value.durability);
    }
    if (length_queue_student(b.player1.FISE) != 0 && length_queue_student(b.player2.FISE) != 0)
    {
        printf("Player1 student development :%i Player 2:%i", b.player1.FISE->value.development, b.player2.FISE->value.development);
    }
    if (length_queue_student(b.player1.FISA) != 0 && length_queue_student(b.player2.FISA) != 0)
    {
        printf("Player1 student development :%i Player 2:%i", b.player1.FISE->value.development, b.player2.FISE->value.development);
    }
}
/*afficher qu'une nouvelle phase commence*/
void show_begin(board b, int i)
{
    printf("Nouvelle phase, tour %i\n", b.turn);
    if (i == 1)
    {
        printf("au tour de Player 1 de jouer !\n");
    }
    else
    {
        printf("au tour de Player 2 de jouer !\n");
    }
}

/*afficher le gagnant du jeu ou egalite le cas echeant*/
void show_winner(int i)
{
    if (i == 1)
        printf("Le joueur 1 a gagné !\n");
    if (i == 2)
        printf("Le joueur 2 a gagné !\n");
    if (i == 3)
        printf("Égalité !");
}

/*Affiche les cartes contenues dans une structure*/
void print_deck(ensiie e)
{
    printf("Deck : | ");
    while (e.deck != NULL)
    {
        printf(" %s : %i |", e.deck->value.name, e.deck->value.cost);
        e.deck = e.deck->next;
    }
    printf("\n");
}

/*Affiche les cartes contenues dans une structure*/
void print_discard(ensiie e)
{
    printf("Discard : | ");
    while (e.discard != NULL)
    {
        printf(" %s : %i |", e.discard->value.name, e.discard->value.cost);
        e.discard = e.discard->next;
    }
    printf("\n");
}

/*Affiche les cartes contenues dans une structure*/
void print_hand(ensiie e)
{
    printf("Hand : | ");
    while (e.hand != NULL)
    {
        printf(" %s : %i |", e.hand->value.name, e.hand->value.cost);
        e.hand = e.hand->next;
    }
    printf("\n");
}

/*Affiche les cartes contenues dans une structure*/
void print_field(ensiie e)
{
    printf("Field : | ");
    while (e.field != NULL)
    {
        printf(" %s |", e.field->value.name);
        e.field = e.field->next;
    }
    printf("\n");
}

void deck_editor()
{
    char choice[256] = "";
    char choicebis[256] = "";
    char name[256] = "";
    while (strncmp(choice, "quit", 4) != 0)
    {
        printf("\e[1;1H\e[2J");
        printf("Vous êtes dans l'éditeur de deck\n");
        list_deck();
        printf("new: créer un nouveau deck\n");
        printf("del : supprimer un deck existant\n");
        printf("quit : sortir de l'application\n");
        fgets(choice, 256, stdin);
        if (strncmp(choice, "new", 3) == 0)
        {
            printf("\e[1;1H\e[2J");
            printf("Entrez le nom du nouveau deck :\n");
            fgets(choicebis, 256, stdin);
            pile deck = create_deck();
            printf("Voulez-vous enregister ce deck ?\nO   N\n");
            fgets(choice, 256, stdin);
            if (strncmp(choice, "O", 1) == 0)
            {
                strncpy(name, choicebis, strlen(choicebis) - 1);
                confirm_deck(deck, name);
            }
            free_pile(&deck);
        }
        if (strncmp(choice, "del", 3) == 0)
        {
            printf("Entrez le nom du deck à supprimer :\n");
            fgets(choicebis, 256, stdin);
            strncpy(name, choicebis, strlen(choicebis) - 1);
            delete_deck(name);
        }
    }
}

/*Permet à l'utilisateur de choisir s'il veut jouer un aller dans l'éditeur de deck, renvoie 1 pour la partie et 0 pour le deck editor*/
int choose_mode()
{
    printf("play: lancer une partie\n");
    printf("deck : entrer dans l'éditeur de decks\n");
    char choice[256] = "";
    while (strncmp(choice, "deck", 4) || strncmp(choice, "play", 4))
    {
        fgets(choice, 256, stdin);
        if (strncmp(choice, "play", 4) == 0)
        {
            return 1;
        }
        if (strncmp(choice, "deck", 4) == 0)
        {
            return 0;
        }
        printf("Commande inconnue\n");
    }
    return 0;
}
