# Blackjack

Quelques infos pour simplifier le travail :

## Documentation

Bien commenter toutes les fonctions/classes (avec la même syntaxe que pour de la javadoc). Comme ça on pourra générer la documentation des modules très facilement (avec [doxygen](http://www.stack.nl/~dimitri/doxygen/)).

## Organisation

Un dossier par module. On aura plus qu'à faire les makefile pour compiler chaque exécutable.

## Messages du module Communication

### Joueur vers Banque
- RespondInsurance (**val** = 0 ou 1) : ***val***
- Split : **1**
- Stand : **2**
- Surrender : **3**
- QuitMessage : **4**
- LeaveGame : **5**
- EnterGame : **6**
- Double : **7**
- AskToHit : **8 *secondHand***
- Bet : **9 *bet***

### Banque vers Joueur

- AskInsurance : **1**
- EndRound : **2**
- RoundStart : **3**
- SendCard : **4 *id_joueur* *type_carte* *secondHand***
- SetBalance : **5 *id_joueur* *balance***
- SetBet : **6 *id_joueur* *bet***
- ValidStand : **7 *id_joueur***
- ValidSurrender : **8 *id_joueur***
- HasQuit : **9 *id_joueur***
- PlayerEntered : **10 *id_joueur***
- CreditPlayer : **11 *id_joueur* *argent***
- DebitPlayer : **12 *id_joueur* *argent***

## Suivi du nombre de joueurs :

On va utiliser un entier pour stocker les places utilisées dans le jeu. Ses 4 derniers bits vont définir chacun si un joueur existe ou non. (La fonction CheckFiles() de BankCommunication retourne cet entier).

Exemple :
```cpp
int b = 0; // L'entier en question
int player = l'id d'un joueur (0, 1, 2 ou 3)

// Ajouter le joueur ayant l'id *player* à la liste des joueurs
b |= (1 << player)

// Supprimer le joueur ayant l'id *player* de la liste des joueurs
b ^= (1 << player)

// Savoir si le joueur ayant l'id *player* existe
if (b & (1 << player))
    // player existe
```