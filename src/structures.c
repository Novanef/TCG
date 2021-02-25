#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/structures.h"

/*affiche les paramètres de c*/
void print_card(card c)
{
    printf("| Id = %i, nom = %s, cost = %i, type = %i |", c.ID, c.name, c.cost, c.type);
}

/* ajoute par effet une carte à une pile */
void stack(pile *p, card value)
{
    pile h = (pile)malloc(sizeof(struct element)); /* Nouvel element */
    h->value = value;                              /* valeur du nouvel element */
    h->next = *p;                                  /* Le element suivant est p */
    *p = h;
}

/*enlève et retourne la dernière carte ajoutée à p*/
card unstack(pile *p)
{
    if (*p == NULL)
    {
        exit(EXIT_FAILURE);
    }
    pile next_card = (*p)->next;
    card ret = (*p)->value;
    free(*p);
    *p = next_card;
    return ret;
}

/*enlève et retourne le premier élève ajouté à q*/
student unstack_student(queue_student *q)
{
    if (*q == NULL)
    {
        return ((student){0, 0});
    }
    queue_student next_student = (*q)->next;
    student ret = (*q)->value;
    free(*q);
    *q = next_student;
    return ret;
}

/* ajoute par effet un student à une queue_student */
void stack_student(queue_student *q, student value)
{
    queue_student h = (queue_student)malloc(sizeof(struct element_student)); /* Nouvel element */
    h->value = value;                                                        /* valeur du nouvel element */
    h->next = *q;                                                            /* L'element suivant est p */
    *q = h;
}

/*supprime les éléments de la queue_student ainsi que les allocations mémoire*/
void free_queue_student(queue_student *q)
{
    while (*q != NULL)
    {
        unstack_student(q);
    }
    *q = NULL;
}

/*retourne la longueur de la queue_student q*/
int length_queue_student(queue_student q)
{
    int i = 0;
    while (q != NULL)
    {
        i++;
        q = q->next;
    }
    return i;
}

/*supprime les éléments de la pile ainsi que les allocations mémoire*/
void free_pile(pile *p)
{
    while (*p != NULL)
    {
        unstack(p);
    }
    *p = NULL;
}

/*affiche p*/
void display_pile(pile p)
{
    if (p == NULL)
    {
        printf("|______________________|");
    }
    else
    {
        while (p != NULL)
        {
            printf("|");
            print_card(p->value);
            printf("|\n");
            p = p->next;
        }
        printf("|______________________|");
    }
}

/*retourne la longueur de la pile p*/
int length_pile(pile p)
{
    int i = 0;
    while (p != NULL)
    {
        i++;
        p = p->next;
    }
    return i;
}

/*ajoute value à queue*/
void thread(queue *q, card value)
{
    queue new = malloc(sizeof(struct element));
    new->value = value;
    new->next = NULL;
    if (*q != NULL)
    {
        queue temp = *q;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
    else
    {
        *q = new;
    }
}

/*enlève et retourne la première carte ajoutée à queue*/
card unthread(queue *q)
{
    if (*q == NULL)
    {
        exit(EXIT_FAILURE);
    }
    queue next_card = (*q)->next;
    card ret = (*q)->value;
    free(*q);
    *q = next_card;
    return ret;
}

/* enlève et retourne la carte c d"une queue q*/
card pick(queue *q, card c)
{
    if (q == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if ((*q)->value.ID == c.ID)
    {
        return (unthread(q));
    }
    queue temp = *q;
    while (temp->next != NULL)
    {
        if (temp->next->value.ID == c.ID)
        {
            card ret = temp->next->value;
            printf("Carte pick de la main : %s\n", ret.name);
            queue freed = temp->next;
            temp->next = temp->next->next;
            free(freed);
            return ret;
        }
        temp = temp->next;
    }
    exit(EXIT_FAILURE);
}

/* enlève la carte c d"une queue q*/
void display_queue(queue q)
{
    if (q == NULL)
    {
        printf("[]");
    }
    else
    {
        printf("[");
        while (q->next != NULL)
        {
            print_card(q->value);
            printf(", ");
            q = q->next;
        }
        printf("]");
    }
}

/*supprime les éléments de la queue ainsi que les allocations mémoire*/
void free_queue(queue *q)
{
    while (*q != NULL)
    {
        unthread(q);
    }
    *q = NULL;
}

/*retourne la longueur de la queue q*/
int length_queue(queue q)
{
    int i = 0;
    while (q != NULL)
    {
        i++;
        q = q->next;
    }
    return i;
}

/*donne un nombre aléatoire entre 0 et n*/
int random(int n)
{
    static int tab[100];
    static int first = 0;
    int index;
    double rn;
    if (first == 0)
    {
        int i;
        srand(time(NULL));
        for (i = 0; i < 100; i++)
            tab[i] = rand();
        first = 1;
    }
    index = rand() / RAND_MAX * 99;
    rn = tab[index];
    tab[index] = rand();
    return ((int)(rn / RAND_MAX * n));
}