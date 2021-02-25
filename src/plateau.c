#include "../headers/plateau.h"
#include <stdio.h>
#include <stdlib.h>

/*retourne 0 si le tour est pair ou 1 si il est impair */
int ParityTurn(board b)
{
    return (b.turn % 2);
}

/*retourne le nb max de Personnel pouvant être présent simultanément sur un coté du terrain*/
int NbMaxPersonnel(board b)
{
    if (b.turn < 6)
    {
        return 1;
    }
    if (b.turn < 11)
    {
        return 2;
    }
    return 3;
}
/*retourne le nombre de cartes personnel sur le terrain d'une ensiie*/
int NbPersonnel(ensiie e)
{
    return length_queue(e.field);
}
/*change les valeurs du développement (si mode==0) ou de la durabilité (mode==1)
des cartes élèves de la pile d'une ensiie*/
void ChangeStudent(queue_student *eleves, int value, int mode)
{
    queue_student temp = *eleves;
    if (mode == 0)
    {
        while (temp != NULL)
        {
            if (temp->value.development + value >= 0)
                (temp->value).development += value;
            temp = temp->next;
        }
    }
    if (mode == 1)
    {
        while (temp != NULL)
        {
            if (temp->value.durability + value >= 0)
                (temp->value).durability += value;
            temp = temp->next;
        }
    }
}

/*renvoie l'entier correspondant à l'effet d'une carte*/
Personnel FindEffect(card c)
{
    if (c.type == 1)
    {
        Personnel EffetsPerso[20] = {
            (Personnel){1, 1, {1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {2, 1, {2, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {3, 1, {3, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {4, 1, {4, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {5, 1, {5, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {6, 1, {6, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {7, 1, {7, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {8, 1, {8, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}},
            {9, 2, {1, 3, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0}},
            {10, 2, {2, 4, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0}},
            {11, 2, {5, 7, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0}},
            {12, 2, {6, 8, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0}},
            {13, 1, {11, 0, 0, 0, 0, 0, 0, 0}, {2, 0, 0, 0, 0, 0, 0, 0}},
            {14, 3, {9, 10, 11, 0, 0, 0, 0, 0}, {2, 1, 1, 0, 0, 0, 0, 0}},
            {15, 3, {10, 11, 12, 0, 0, 0, 0, 0}, {2, 1, 1, 0, 0, 0, 0, 0}},
            {16, 4, {1, 2, 6, 10, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}},
            {17, 4, {3, 4, 8, 10, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}},
            {18, 3, {1, 2, 12, 0, 0, 0, 0, 0}, {2, 2, 1, 0, 0, 0, 0, 0}},
            {19, 3, {3, 4, 12, 0, 0, 0, 0, 0}, {2, 2, 1, 0, 0, 0, 0, 0}},
            {20, 8, {1, 2, 3, 4, 9, 10, 11, 12}, {2, 2, 2, 2, 1, 1, 1, 2}},
        };
        for (int i = 0; i < 20; i++)
        {
            if (c.ID == EffetsPerso[i].ID)
            {
                return EffetsPerso[i];
            }
        }
    }
    return ((Personnel){0, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}});
}

/*active l'effet d'une carte*/
void TriggerEffect(card c, ensiie *player, ensiie *opponent)
{
    if (c.type == 1)
    {
        Personnel Played = FindEffect(c);
        for (int i = 0; i < Played.number; i++)
        {

            switch (Played.effect[i])
            {
            case 1:
                ChangeStudent(&(player->FISE), Played.value[i], 0);
                break;
            case 2:
                ChangeStudent(&(player->FISE), Played.value[i], 1);
                break;
            case 3:
                ChangeStudent(&(player->FISA), Played.value[i], 0);
                break;
            case 4:
                ChangeStudent(&(player->FISA), Played.value[i], 1);
                break;
            case 5:
                ChangeStudent(&(opponent->FISE), -Played.value[i], 0);
                break;
            case 6:
                ChangeStudent(&(opponent->FISE), -Played.value[i], 1);
                break;
            case 7:
                ChangeStudent(&(opponent->FISA), -Played.value[i], 0);
                break;
            case 8:
                ChangeStudent(&(opponent->FISA), -Played.value[i], 1);
                break;
            case 9:
                player->DD += Played.value[i];
                break;
            case 10:
                opponent->DD -= Played.value[i];
                if (opponent->DD < 0)
                    opponent->DD = 0;
                break;
            case 11:
                player->bonuscard += Played.value[i];
                break;
            case 12:
                player->Student_Nbr += Played.value[i];
            }
        }
    }
}

/*Joue la carte personnel c et la pose sur le champ, en enlevant la carte personnel la plus ancienne du plateau si besoin*/
void PlayPersonnel(card c, ensiie *player, ensiie *opponent, board b)
{
    if (NbPersonnel(*player) == NbMaxPersonnel(b))
    {
        thread(&player->discard, unthread(&player->field));
        thread(&player->field, pick(&player->hand, c));
    }
    else
    {
        card picked = pick(&player->hand, c);
        thread(&player->field, picked);
    }
    TriggerEffect(c, player, opponent);
}

/*mélange une pile*/
void shuffle(pile *p)
{
    int n = length_pile(*p);
    card *temp = malloc(n * sizeof(card));
    card nocard = (card){0, "", 0, 0};
    int i;
    for (i = 0; i < n; i++)
    {
        temp[i] = unstack(p);
    }
    while (length_pile(*p) < n)
    {
        i = random(n - 1);
        while (i < n - 1)
        {
            if (temp[i].ID != nocard.ID)
            {
                break;
            }
            i = i + 1;
        }
        while (i > 0)
        {
            if (temp[i].ID != nocard.ID)
            {
                break;
            }
            i = i - 1;
        }
        stack(p, temp[i]);
        temp[i] = nocard;
    }
    free(temp);
}

/*Joue la carte action c et l'envoie dans la défausse*/
void PlayAction(card c, ensiie *player, ensiie *opponent)
{
    switch (c.ID)
    {
    case 21:
        player->DD += 6;
        break;
    case 22:
        draw(player, 1);
        break;
    case 23:
        addFISECard(player);
        break;
    case 24:
        addFISACard(player);
        break;
    case 25:
        player->PE += 6;
        break;
    case 26:
        unstack_student(&opponent->FISE);
        unstack_student(&opponent->FISA);
        break;
    case 27:
        if (opponent->field != NULL)
            thread(&opponent->discard, unthread(&opponent->field));
        break;
    case 28:
        while (player->discard != NULL)
        {
            stack(&player->deck, unthread(&player->discard));
        }
        card recyclage = {28, "Recyclage", 10, 2};
        stack(&player->deck, recyclage);
        shuffle(&player->deck);
        break;
    case 29:
        player->FISE_Development += 1;
        player->FISA_Development += 1;
        break;
    case 30:
        player->FISE_Durability += 1;
        player->FISA_Durability += 1;
        break;
    case 31:
        free_queue_student(&player->FISE);
        free_queue_student(&player->FISA);
        free_queue_student(&opponent->FISE);
        free_queue_student(&opponent->FISA);
        break;
    }
    if (c.ID != 28)
        stack(&player->discard, pick(&player->hand, c));
}

/*Joue la carte c*/
void PlayCard(card c, ensiie *e, ensiie *o, board b)
{
    if (c.type == 1)
    {
        PlayPersonnel(c, e, o, b);
    }
    if (c.type == 2)
    {
        PlayAction(c, e, o);
    }
    e->PE -= c.cost;
}

/* retourne un deck contenant les 31 cartes du jeu dans un ordre aléatoire*/
pile init_deck()
{
    card collection[31] = {/*tableau de toutes les cartes différentes du jeu*/
                           {1, "Tomas Lim", 3, 1},
                           {2, "Marie Szafranski", 3, 1},
                           {3, "Alain Faye", 3, 1},
                           {4, "Christophe Mouilleron", 3, 1},
                           {5, "Stefania Dumbrava", 3, 1},
                           {6, "Julien Forest", 3, 1},
                           {7, "Nicolas Brunel", 3, 1},
                           {8, "Laurence Bourard", 3, 1},
                           {9, "Dimitri Watel", 5, 1},
                           {10, "Vitera Y", 5, 1},
                           {11, "Kevin Goilard", 5, 1},
                           {12, "Vincent Jeannas", 5, 1},
                           {13, "Massinissa Merabet", 7, 1},
                           {14, "Anne-Laure Ligozat", 8, 1},
                           {15, "Catherine Dubois", 8, 1},
                           {16, "Eric Lejeune", 10, 1},
                           {17, "Christine Mathias", 10, 1},
                           {18, "Katrin Salhab", 15, 1},
                           {19, "Abass Sagna", 15, 1},
                           {20, "Laurent Prével", 20, 1},
                           {21, "Cours Développement durable", 2, 2},
                           {22, "Recrutement", 2, 2},
                           {23, "Rentrée FISE", 3, 2},
                           {24, "Rentrée FISA", 3, 2},
                           {25, "Energie Verte", 4, 2},
                           {26, "Diplomation", 5, 2},
                           {27, "Décharge", 5, 2},
                           {28, "Recyclage", 10, 2},
                           {29, "Zero papier", 10, 2},
                           {30, "Repas végétarien", 10, 2},
                           {31, "Fermeture annuelle", 10, 2}};
    card test = {0, "", 0, 0};
    pile deck = NULL;
    int i;
    while (length_pile(deck) < 31)
    {
        i = random(30);
        while (collection[i].ID == test.ID && i < 30)
        {
            i = i + 1;
        }
        while (collection[i].ID == test.ID && i > 0)
        {
            i = i - 1;
        }
        stack(&deck, collection[i]);
        collection[i] = test;
    }
    return deck;
}

/*création d"un joueur*/
ensiie create_ensiie()
{
    ensiie player;
    player.deck = init_deck();
    player.discard = NULL;
    player.hand = NULL;
    player.field = NULL;
    player.Student_Nbr = 1;
    player.PE = 0;
    player.DD = 0;
    player.bonuscard = 0;
    player.FISE = NULL;
    player.FISA = NULL;
    player.FISE_Development = 1;
    player.FISA_Development = 1;
    player.FISE_Durability = 1;
    player.FISA_Durability = 1;
    return player;
}

/* création d"un plateau vierge */
board create_board()
{
    ensiie player1 = create_ensiie();
    ensiie player2 = create_ensiie();
    board b;
    b.player1 = player1;
    b.player2 = player2;
    b.turn = 0;
    return b;
}

/*suppression d'un joueur à la fin de la partie*/
void erase_ensiie(ensiie *e)
{
    free_queue(&e->hand);
    free_queue(&e->field);
    free_queue(&e->discard);
    free_pile(&e->deck);
    free_queue_student(&e->FISA);
    free_queue_student(&e->FISE);
}

/*suppression d"un plateau à la fin de la partie */
void erase_board(board *b)
{
    erase_ensiie(&b->player1);
    erase_ensiie(&b->player2);
}

/*incrémentation du compteur de tour */
void newturn(board *b)
{
    b->turn = b->turn + 1;
}

/*détermine et renvoie le nombre de cartes à piocher au début du tour d"un joueur */
int nbdraw(ensiie e, board b)
{
    if (b.turn == 0)
    {
        return 3;
    }
    else
    {
        return 1 + e.bonuscard;
    }
}

/*fait piocher le nombre de cartes défini par nbdraw */
void draw(ensiie *e, int d)
{
    for (int i = 0; i < d; i++)
    {
        if (e->deck != NULL)
            stack(&e->hand, unstack(&e->deck));
    }
}

/* ajoute une carte FISE sur le plateau de l"ENSIIE p*/
void addFISECard(ensiie *e)
{
    stack_student(&e->FISE, (student){1, 1});
}

/* ajoute une carte FISA sur le plateau de l"ENSIIE p*/
void addFISACard(ensiie *e)
{
    stack_student(&e->FISA, (student){1, 1});
}

/* compte le nombre de PE disponible pour l"ENSIIE P*/
int countPE(ensiie e, board b)
{
    if (b.turn % 2 == 0)
        return length_queue_student(e.FISE);
    else
        return length_queue_student(e.FISE) + length_queue_student(e.FISA) * 2;
}

/* permet à l"ENSIIE e de jouer la carte c*/
int allowPlayCard(ensiie e, card c)
{
    if (e.PE >= c.cost)
        return 1;
    return 0;
}

/* calcule les DD de chaque joueur après un tour*/
void endTurn(board *b)
{
    int Dev_player1 = 0;
    queue_student FISE1 = b->player1.FISE;
    while (FISE1 != NULL)
    {
        Dev_player1 += FISE1->value.development + b->player1.FISE_Development;
        FISE1 = FISE1->next;
    }
    int Dev_player2 = 0;
    queue_student FISE2 = b->player2.FISE;
    while (FISE2 != NULL)
    {
        Dev_player2 += FISE2->value.development + b->player2.FISE_Development;
        FISE2 = FISE2->next;
    }
    if (b->turn % 2 == 1)
    {
        queue_student FISA1 = b->player1.FISA;
        while (FISA1 != NULL)
        {
            Dev_player1 += FISA1->value.development + b->player1.FISA_Development;
            FISA1 = FISA1->next;
        }
        queue_student FISA2 = b->player2.FISA;
        while (FISA2 != NULL)
        {
            Dev_player2 += FISA2->value.development + b->player2.FISA_Development;
            FISA2 = FISA2->next;
        }
    }
    int Dur_player1 = 0;
    FISE1 = b->player1.FISE;
    while (FISE1 != NULL)
    {
        Dur_player1 += FISE1->value.development + b->player1.FISE_Durability;
        FISE1 = FISE1->next;
    }
    int Dur_player2 = 0;
    FISE2 = b->player2.FISE;
    while (FISE2 != NULL)
    {
        Dur_player2 += FISE2->value.development + b->player2.FISE_Durability;
        FISE2 = FISE2->next;
    }
    if (b->turn % 2 == 1)
    {
        queue_student FISA1 = b->player1.FISA;
        while (FISA1 != NULL)
        {
            Dur_player1 += FISA1->value.development + b->player1.FISA_Durability;
            FISA1 = FISA1->next;
        }
        queue_student FISA2 = b->player2.FISA;
        while (FISA2 != NULL)
        {
            Dur_player2 += FISA2->value.development + b->player2.FISA_Durability;
            FISA2 = FISA2->next;
        }
    }
    if (Dev_player1 >= Dur_player2)
    {
        b->player1.DD += Dev_player1 - Dur_player2;
        if (b->player1.DD < 0)
            b->player1.DD = 0;
    }
    if (Dev_player2 >= Dur_player1)
    {
        b->player2.DD += Dev_player2 - Dur_player1;
        if (b->player2.DD < 0)
            b->player2.DD = 0;
    }
}

/* renvoie 1 si le joueur 1 a gagné, 2 si le joueur 2 a gagné, 3 s"il y a égalité, 0 sinon*/
int endGame(board b)
{
    if (b.player1.DD > 20)
    {
        if (b.player1.DD > b.player2.DD)
            return 1;
        else
        {
            if (b.player1.DD < b.player2.DD)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (b.player2.DD > 20)
            return 2;
        else
        {
            if (b.turn == 30)
            {
                if (b.player1.DD > b.player2.DD)
                    return 1;
                else
                {
                    if (b.player1.DD < b.player2.DD)
                        return 2;
                    else
                        return 3;
                }
            }
            else
                return 0;
        }
    }
}