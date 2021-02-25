#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../headers/deck.h"
#include <dirent.h>
#include <ctype.h>

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

/* affiche toutes les cartes du jeu*/
void print_collection()
{

    printf("Cartes disponibles : \n");
    printf("Coût    Nom\n");
    for (int i = 0; i < 31; i++)
    {
        printf("%i    %s\n", collection[i].cost, collection[i].name);
    }
}

/*affiche toutes les cartes du jeu et un deck*/
void print_collection_and_deck(pile deck)
{
    int lendeck = length_pile(deck);
    int len = (lendeck > 30) ? lendeck : 30;
    printf("Cartes disponibles :%-90sDeck :\n", "");
    printf("ID    Coût    Nom%-93sID    Coût    Nom\n", "");
    for (int i = 0; i < len; i++)
    {
        if (i < 31 && i < lendeck)
        {
            printf("%-5d%-5d%-100s%-5d%-5d%s\n", collection[i].ID, collection[i].cost, collection[i].name, deck->value.ID, deck->value.cost, deck->value.name);
            deck = deck->next;
        }
        if (i >= 31 && i < lendeck)
        {
            printf("%-110s%-5d%-5d%s\n", "", deck->value.ID, deck->value.cost, deck->value.name);
            deck = deck->next;
        }
        if (i < 31 && i >= lendeck)
        {
            printf("%-5d%-5d%s\n", collection[i].ID, collection[i].cost, collection[i].name);
        }
    }
}

void list_deck()
{
    struct dirent *de;
    DIR *dr = NULL;
    dr = opendir("./bin/decks");
    if (dr == NULL)
    {
        printf("Could not open deck directory\n");
        exit(EXIT_FAILURE);
    }
    printf("voici la liste des decks disponibles :\n");
    while ((de = readdir(dr)) != NULL)
    {
        if (strlen(de->d_name) >= 4)
        {
            printf("-%.*s\n", (int)strlen(de->d_name) - 4, de->d_name);
        }
    }
    printf("\n");
    closedir(dr);
}

char *choose_deck()
{
    list_deck();
    struct dirent *de;
    DIR *dr = opendir("./bin/decks");
    if (dr == NULL)
    {
        printf("Could not open deck directory");
    }
    printf("entrez le nom du deck que vous souhaitez utiliser\n");
    char choice[256] = "";
    while (1)
    {
        fgets(choice, 256, stdin);
        while ((de = readdir(dr)) != NULL)
        {
            if (strncmp(choice, de->d_name, (int)strlen(de->d_name) - 4) == 0)
            {
                char *name = malloc(260 * sizeof(char));
                strcpy(name, de->d_name);
                closedir(dr);
                return name;
            }
        }
        printf("Nom inconnu : %s\n", choice);
        closedir(dr);
        dr = opendir("./bin/decks");
    }
    closedir(dr);
    return "";
}

void confirm_deck(pile deck, char *nom_deck)
{
    char filename[128];
    char *extension = ".txt";
    if (sizeof(filename) < strlen(nom_deck) + 1)
    {
        fprintf(stderr, "'%s' est un nom trop long\n", nom_deck);
        exit(EXIT_FAILURE);
    }
    strncpy(filename, nom_deck, sizeof(filename));

    if (sizeof(filename) < (strlen(filename) + strlen(extension) + 1))
    {
        fprintf(stderr, "'%s' est un nom trop long\n", nom_deck);
        exit(EXIT_FAILURE);
    }
    strncat(filename, extension, (sizeof(filename) - strlen(filename)));
    char *path = "./bin/decks/";
    char complete_path[256];
    strcpy(complete_path, path);
    strcat(complete_path, filename);
    FILE *file = fopen(complete_path, "w+");
    if (file != NULL)
    {
        while (deck != NULL)
        {
            fprintf(file, "%i\n", deck->value.ID);
            deck = deck->next;
        }
    }
    fclose(file);
}

void delete_deck(char *nom_deck)
{
    char *extension = ".txt";
    char *path = "./bin/decks/";
    char complete_path[256];
    strcpy(complete_path, path);
    strcat(complete_path, nom_deck);
    strcat(complete_path, extension);
    if (remove(complete_path) == 0)
    {
        printf(" Deck %s supprimé\n", nom_deck);
    }
    else
    {
        printf("Deck introuvable \n");
    }
}
pile create_deck()
{

    char choice[256] = "";
    pile deck = NULL;

    int id = 1;
    while (strncmp(choice, "end", 3) != 0)
    {
        printf("\e[1;1H\e[2J");
        print_collection_and_deck(deck);
        printf("Entrez l'ID des cartes que vous souhaitez ajouter au deck\n");
        printf("Entrez \"end\" pour terminer le deck\n");
        fgets(choice, 256, stdin);
        id = (int)strtol(choice, NULL, 10);
        if (id <= 31 && id > 0)
        {
            stack(&deck, collection[strtol(choice, NULL, 10) - 1]);
        }
    }
    return deck;
}

void swap_deck(ensiie *e, char *filename)
{
    char *path = "./bin/decks/";
    char complete_path[128];
    strcpy(complete_path, path);
    strcat(complete_path, filename);
    FILE *file = fopen(complete_path, "r");
    if (file != NULL)
    {
        int id = 0;
        free_pile(&(e->deck));
        while (fscanf(file, "%i\n", &id) != EOF)
        {
            if (id <= 31)
            {
                stack(&(e->deck), collection[id - 1]);
            }
        }
        shuffle(&(e->deck));
        fclose(file);
    }
}
