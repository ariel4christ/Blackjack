# Blackjack

Quelques infos pour simplifier le travail :

## Documentation

Bien commenter toutes les fonctions/classes (avec la même syntaxe que pour de la javadoc). Comme ça on pourra générer la documentation des modules très facilement (avec [doxygen](http://www.stack.nl/~dimitri/doxygen/)).

## Organisation

Un dossier par module. On aura plus qu'à faire les makefile pour compiler chaque exécutable.

## Messages du module Communication

Pour lire tous les messages on pourra utiliser sscanf() pour récupérer les infos de la même façon qu'elles sont envoyées :
```cpp
string str; // Stocke le message reçu
int id_message;

//On regarde le premier entier du message pour savoir quel type de message c'est
sscanf(str.c_str(), "%d", &id_message)

// Dans un switch en fonction de id_message, on sait ce qu'on doit recevoir en paramètres, donc on peut refaire un sscanf
sscanf(str, "%d ...", &id_message, ...);
```

### Joueur vers Banque
- RespondInsurance (**val** = 0 ou 1) : ***val***
- Split : **1 *secondHand***
- Stand : **2 *secondHand***
- Surrender : **3 *secondHand***
- QuitMessage : **4**
- LeaveGame : **5**
- EnterGame : **6**
- Double : **7**
- AskToHit : **8 *secondHand***
- Bet : **9 *bet***
- Accusé de reception : **10**

### Banque vers Joueur

- AskInsurance : **1**
- EndRound : **2**
- RoundStart : **3**
- SendCard : **4 *id_joueur* *type_carte* *secondHand***
- SetBalance : **5 *id_joueur* *balance***
- SetBet : **6 *id_joueur* *bet***
- ValidStand : **7 *id_joueur* *secondHand***
- ValidSurrender : **8 *id_joueur* *secondHand***
- HasQuit : **9 *id_joueur***
- PlayerEntered : **10 *id_joueur* *miseMin* *miseMax***
- CreditPlayer : **11 *id_joueur* *argent***
- DebitPlayer : **12 *id_joueur* *argent***
- SetHand : **13 *id_joueur* *secondHand* *carte1* *carte2* ...**
- ValidSplit : **14 *id_joueur***
- AskAction : **15 *id_joueur* *secondHand***

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
