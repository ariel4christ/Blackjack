# Blackjack

Quelques infos pour simplifier le travail :

## Documentation

Bien commenter toutes les fonctions/classes (avec la même syntaxe que pour de la javadoc). Comme ça on pourra générer la documentation des modules très facilement (avec [doxygen](http://www.stack.nl/~dimitri/doxygen/)).

## Organisation

Un dossier par module. On aura plus qu'à faire les makefile pour compiler chaque exécutable.

## Messages du module Communication

### Joueur vers Banque
- RespondInsurance (**val** = 0 ou 1) : ***val***
- Split : *1*
- Stand : *2*
- Surrender : *3*
- QuitMessage : *4*
- LeaveGame : *5*
- EnterGame : *6*
- Double : *7*
- AskToHit : *8*
- Bet : *9 **bet***

### Banque vers Joueur

