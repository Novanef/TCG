#include <stdio.h>
#include <stdlib.h>
#include "../headers/interface.h"

int main()
{
    printf("\e[1;1H\e[2J");
    int mode = choose_mode();
    if (mode == 0)
    {
        deck_editor();
    }
    else
    {
        card nocard = (card){0, "", 0, 0};
        board plateau = create_board();
        printf("Joueur 1, ");
        char *deck1 = choose_deck();
        swap_deck(&(plateau.player1), deck1);
        printf("Joueur 2, ");
        char *deck2 = choose_deck();
        swap_deck(&(plateau.player2), deck2);
        while (!endGame(plateau))
        {
            printf("\e[1;1H\e[2J");
            draw(&plateau.player1, nbdraw(plateau.player1, plateau));
            show_begin(plateau, 1);
            show_information(plateau, plateau.player1);
            for (int i = 0; i < plateau.player1.Student_Nbr; i++)
            {
                int fisefisa = AskStudent();
                if (fisefisa == 1)
                {
                    addFISECard(&plateau.player1);
                }
                if (fisefisa == 2)
                    addFISACard(&plateau.player1);
            }
            plateau.player1.PE = countPE(plateau.player1, plateau);
            card ask = {0, "", 0, 0};
            card c;
            printf("\e[1;1H\e[2J");
            ask = ask_choosecard(plateau.player1);
            while (ask.ID != nocard.ID)
            {
                c = ask;
                if (allowPlayCard(plateau.player1, c))
                {
                    PlayCard(c, &plateau.player1, &plateau.player2, plateau);
                    printf("\e[1;1H\e[2J");
                    ask = ask_choosecard(plateau.player1);
                }
                else
                {
                    printf("\e[1;1H\e[2J");
                    printf("Pas assez de PE\n");
                    ask = ask_choosecard(plateau.player1);
                }
            }
            printf("\e[1;1H\e[2J");
            draw(&plateau.player2, nbdraw(plateau.player2, plateau));
            show_begin(plateau, 2);
            show_information(plateau, plateau.player2);
            for (int i = 0; i < plateau.player1.Student_Nbr; i++)
            {
                int fisefisa = AskStudent();
                if (fisefisa == 1)
                {
                    addFISECard(&plateau.player2);
                }
                if (fisefisa == 2)
                    addFISACard(&plateau.player2);
            }
            plateau.player2.PE = countPE(plateau.player2, plateau);
            printf("\e[1;1H\e[2J");
            ask = ask_choosecard(plateau.player2);
            while (ask.ID != nocard.ID)
            {
                c = ask;
                if (allowPlayCard(plateau.player2, c))
                {
                    PlayCard(c, &plateau.player2, &plateau.player1, plateau);
                    printf("\e[1;1H\e[2J");
                    ask = ask_choosecard(plateau.player2);
                }
                else
                {
                    printf("\e[1;1H\e[2J");
                    printf("Pas assez de PE\n");
                    ask = ask_choosecard(plateau.player2);
                }
            }
            newturn(&plateau);
            endTurn(&plateau);
        }
        show_winner(endGame(plateau));
        erase_board(&plateau);
        free(deck1);
        free(deck2);
    }
}
