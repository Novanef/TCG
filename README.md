# Durableverse - Groupe Sobre

Commandes du makefile:
make : génère l'éxécutable ./main ainsi que les fichiers objets dans le fichier bin
make clean : supprime les fichiers objets stockés dans bin
make rmproper : supprime l'éxécutable
make run : lance l'éxécutable

Après avoir effectué la commande make run, on demande à l'utilisateur s'il veut utiliser l'éditeur de deck ou faire une partie.
Si l'utilisateur choisit l'éditeur de deck, il peut créer et sauvegarder des decks ou supprimer des decks existants.
Les decks sont stockés dans ./bin/decks au format txt, chaque ligne contient l'ID d'une carte du deck.
Le programme s'arrête quand l'utilisateur entre la commande quit

Si l'utilisateur choisit de jouer, le programme demande aux deux joueurs de choisir un deck parmi ceux enregistrés puis une partie se lance.
A chaque début de tour il sera demandé de rentrer FISE OU FISA pour ajouter la carte élève correspondate à la pile. Tout autre input sera compté comme un refus de mettre une nouvelle carte étudiant.
Le joueur peut ensuite choisir de rentrer l'une des commandes affichées pour obtenir des informations relatives au plateau, poser une carte ou bien mettre fin à son tour.

La partie prend fin et le programme se ferme lorsque un ou plusieurs joueurs remplit les conditions de victoire.