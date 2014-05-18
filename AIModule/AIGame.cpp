/**
 * Classe AIGame.
 * @autor Ariel NONO
 */

#include "AIGame.h"

using namespace std;

int AIGame::betMin = 5;
int AIGame::betMax = 100;
bool hasSplit = false;

AIGame::AIGame() :
	previousBets(), listOfCards(), ia(0, 0), com(), bankCard(NaN) {
	int id = this->com.CheckFiles();

	if (id == -1)
		exit(-1);

	this->com.CreateFiles(id);
	this->ia.setId(id);

}

AIGame::~AIGame() {
this->aiInterface.EndGame();
}

void AIGame::runGame() {
	this->com.EnterGame();
	int id = this->ia.getId();
	this->aiInterface.EnterGame(id);

	string str = com.ReadFile();

	int id_message;
	sscanf(str.c_str(), "%d", &id_message);
	if (id_message == 10) // Message PlayerEntered
	{
		int id_player, bet_min, bet_max;
		sscanf(str.c_str(), "%d %d %d %d", &id_message, &id_player, &bet_min,
				&bet_max);
		if (id == id_player) {
			AIGame::betMin = bet_min;
			AIGame::betMax = bet_max;
			com.sendAck();
		}

	} else
		throw runtime_error("Erreur reception message PlayerEntered");

	str = com.ReadFile();

	sscanf(str.c_str(), "%d", &id_message);
	if (id_message == 5) {
		int id_player, balance;
		sscanf(str.c_str(), "%d %d %d", &id_message, &id_player, &balance);
		if (id == id_player) {
			ia.setBalance(balance);
		}
		com.sendAck();
	} else
		throw runtime_error("Message d'initialisation du solde joueur non recu");

	bool quit = false; // variable permettant de quitter le jeu

	while (!quit) {
		this->ia.setInsurance(false);
		this->ia.setBlackjack(false);
		this->ia.setInsurance(false);

		if (this->ia.getHand() != NULL)
			this->ia.setHand(NULL);
		if (this->ia.getHand2() != NULL)
			this->ia.setHand2(NULL);

		this->ia.newHand();

		int bet = this->getBet();
		this->com.Bet(bet);

		this->bankCard.setType(NaN);

		quit = this->runRound();
	}

	this->quitGame();
}

bool AIGame::runRound() {
	int num_joueur, typeCard, typeCard2, argent, main, id_message, idIA;
	bool endRound = false; /* permet de savoir si le tour est achevé */
	bool endGame = false; /* permet de savoir si le jeu est achevé */

	while (!endRound) {
		this->message = this->com.ReadFile();
		sscanf(this->message.c_str(), "%d", &id_message);
		idIA = this->ia.getId();

		switch (id_message) {

		case 1:// AskInsurance received
			this->com.RespondInsurance(0);
			this->aiInterface.insurrance(0);
			break;

		case 2: // EndRound received
			endRound = true;
			this->aiInterface.endRound();
			this->com.sendAck();
			hasSplit = false;
			break;

		case 3: // RoundStart received
			endRound = true;
			this->aiInterface.startRound();

			break;

		case 4: // SendCard received
			sscanf(this->message.c_str(), "%d %d %d %d", &id_message,
					&num_joueur, &typeCard, &main);

			if (num_joueur == idIA) {
				if (!main)
					this->ia.getHand()->addCard(new Card(
							static_cast<EType> (typeCard)));
				else
					this->ia.getHand2()->addCard(new Card(
							static_cast<EType> (typeCard)));

			} else {
				if (num_joueur == 4 && typeCard != 0)/* reception de la carte de la banque */
					this->bankCard.setType(static_cast<EType> (typeCard));
			}

			if (typeCard != NaN)
				this->listOfCards.push_back(Card(static_cast<EType> (typeCard))); // recupere les cartes de tous les joueurs les siennes comprises

			this->com.sendAck();
			break;

		case 5: // SetBalance received
			int balance;

			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,
					&balance);

			if (num_joueur == idIA) {
				this->ia.setBalance(balance);
				this->com.sendAck();
				this->aiInterface.stateBalanceBet(this->ia,
						this->ia.getHand()->getBet());

			}
			com.sendAck();
			break;

		case 6: // SetBet received
			int bet;
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,
					&bet);

			if (num_joueur == idIA) {
				this->ia.getHand()->setBet(bet);
				this->previousBets.push_back(bet);
				this->aiInterface.stateBalanceBet(this->ia, bet);
			}
			com.sendAck();
			break;

		case 7: // ValidStand received
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,
					&main);
			if (num_joueur == idIA) {
				if (!main)
					this->ia.Stand(this->ia.getHand());
				else
					this->ia.Stand(this->ia.getHand2());
				this->com.sendAck();

			}
			break;

		case 8: // ValidSurrender received
			sscanf(this->message.c_str(), "%d %d %d ", &id_message,
					&num_joueur, &main);
			if (num_joueur == idIA) {
				if (!main)
					this->ia.Surrender(this->ia.getHand());
				else
					this->ia.Surrender(this->ia.getHand2());
				this->com.sendAck();

			}
			break;

		case 9: // HasQuit received
			sscanf(this->message.c_str(), "%d %d ", &id_message, &num_joueur);
			if (num_joueur == idIA) {
				endGame = true;
				endRound = true;
				this->aiInterface.choice(this->handValue(this->ia.getHand()),
						false, false, false, false, true, false);
			}
			com.sendAck();
			break;

		case 10: // PlayerEntered received
			sscanf(this->message.c_str(), "%d %d %d %d", &id_message,
					&num_joueur, &betMin, &betMax);

			if (num_joueur == idIA) {
				this->betMin = betMin;
				this->betMax = betMax;
				this->com.sendAck();
			}
			com.sendAck();
			break;

		case 11: // CreditPlayer received
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,
					&argent);
			if (num_joueur == idIA) {
				this->ia.increaseBalance(argent);
				this->aiInterface.balanceState(this->ia);
			}
			break;

		case 12: // DebitPlayer received
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,
					&argent);
			if (num_joueur == idIA) {
				this->ia.decreaseBalance(argent);
				this->aiInterface.balanceState(this->ia);
			}
			break;

		case 13: // SetHand received
			sscanf(this->message.c_str(), "%d %d %d %d %d ", &id_message,
					&num_joueur, &main, &typeCard, &typeCard2);
			if (num_joueur == idIA) {
				/* construction d'une main a partir des cartes recues*/
				Hand hand;

				hand.addCard(new Card(static_cast<EType> (typeCard)));
				hand.addCard(new Card(static_cast<EType> (typeCard2)));

				this->listOfCards.push_back(Card(static_cast<EType> (typeCard)));
				this->listOfCards.push_back(
						Card(static_cast<EType> (typeCard2)));

				if (!main)
					this->ia.getHand()->setHand(hand);
				else
					this->ia.getHand2()->setHand(hand);

				this->com.sendAck();
			}
			break;

		case 14: // ValidSplit received
			sscanf(this->message.c_str(), "%d %d ", &id_message, &num_joueur);
			if (num_joueur == idIA) {
				this->ia.newHand();
				this->com.sendAck();
			}
			com.sendAck();
			break;

		case 15: // AskAction received
			sscanf(this->message.c_str(), "%d %d %d ", &id_message,
					&num_joueur, &main);
			if (num_joueur == idIA) {
				this->aiInterface.stateCards(this->ia);
				if (!main)
					this->chooseAction(this->ia.getHand());
				else
					this->chooseAction(this->ia.getHand2());
			}
			break;
		}
	}
	return endGame;
}

void AIGame::chooseAction(PlayerHand* myhand) // basee sur la "basic strategy"
{
	EType type1;
	EType type2;

	type1 = myhand->getCard(0)->getType();
	type2 = myhand->getCard(1)->getType();

	if (!isSpecial(myhand) && myhand->getValue2() == 21)
		this->strategy_21(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 20)
		this->strategy_20(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 19)
		this->strategy_19(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 18)
		this->strategy_18(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 17)
		this->strategy_17(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 16)
		this->strategy_16(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 15)
		this->strategy_15(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 14)
		this->strategy_14(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 13)
		this->strategy_13(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 12)
		this->strategy_12(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 11)
		this->strategy_11(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 10)
		this->strategy_10(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 9)
		this->strategy_9(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 8)
		this->strategy_8(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 7)
		this->strategy_7(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 6)
		this->strategy_6(this->bankCard.getType(), myhand);

	else if (!isSpecial(myhand) && myhand->getValue2() == 5)
		this->strategy_5(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, AS))
		this->strategy_A_A(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && (isEqual(type1, type2, KING, KING)
			|| isEqual(type1, type2, KING, QUEEN) || isEqual(type1, type2,
			KING, JACK) || isEqual(type1, type2, KING, TEN) || isEqual(type1,
			type2, QUEEN, QUEEN) || isEqual(type1, type2, QUEEN, JACK)
			|| isEqual(type1, type2, QUEEN, TEN) || isEqual(type1, type2, JACK,
			JACK) || isEqual(type1, type2, TEN, TEN)))
		this->strategy_10_10(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, NINE, NINE))
		this->strategy_9_9(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, EIGHT, EIGHT))
		this->strategy_8_8(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, SEVEN, SEVEN))
		this->strategy_7_7(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, SIX, SIX))
		this->strategy_6_6(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, FIVE, FIVE))
		this->strategy_5_5(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, FOUR, FOUR))
		this->strategy_4_4(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, THREE, THREE))
		this->strategy_3_3(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, TWO, TWO))
		this->strategy_2_2(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && (isEqual(type1, type2, AS, KING) || isEqual(
			type1, type2, AS, QUEEN) || isEqual(type1, type2, AS, JACK)
			|| isEqual(type1, type2, AS, TEN)))
		this->strategy_A_10(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, NINE))
		this->strategy_A_9(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, EIGHT))
		this->strategy_A_8(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, SEVEN))
		this->strategy_A_7(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, SIX))
		this->strategy_A_6(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, FIVE))
		this->strategy_A_5(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, FOUR))
		this->strategy_A_4(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, THREE))
		this->strategy_A_3(this->bankCard.getType(), myhand);

	else if (isSpecial(myhand) && isEqual(type1, type2, AS, TWO))
		this->strategy_A_2(this->bankCard.getType(), myhand);

}

void AIGame::quitGame() {
	this->ia.setHand(NULL);
	this->ia.setHand2(NULL);
	this->~AIGame();
	exit(1);
}

void AIGame::strategy_21(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_20(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_19(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_18(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_17(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_16(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	case SEVEN:
	case EIGHT:
	case AS:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_15(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;
	}
}

void AIGame::strategy_14(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;
	}
}

void AIGame::strategy_13(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case AS:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;
	}
}

void AIGame::strategy_12(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case FOUR:
	case FIVE:
	case SIX:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	case TWO:
	case THREE:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case AS:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;
	}
}

void AIGame::strategy_11(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
		if(!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL){
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else {
			this->com.AskToHIt(handValue(myhand));
			this->aiInterface.choice(this->handValue(myhand), true, false,
					false, false, false, false);
		}

		break;

	}
}

void AIGame::strategy_10(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else {
			this->com.AskToHIt(handValue(myhand));
			this->aiInterface.choice(this->handValue(myhand), true, false,
					false, false, false, false);
		}
		break;

	}
}

void AIGame::strategy_9(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else {
			this->com.AskToHIt(handValue(myhand));
			this->aiInterface.choice(this->handValue(myhand), true, false,
					false, false, false, false);
		}
		break;

	}
}

void AIGame::strategy_8(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_7(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_6(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_5(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_A_A(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_10(type, myhand);
		}
		break;

	}
}

void AIGame::strategy_10_10(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_9_9(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case EIGHT:
	case NINE:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_18(type, myhand);
		}
		break;

	case SEVEN:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
	}
}

void AIGame::strategy_8_8(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_16(type, myhand);
		}
		break;

	}
}

void AIGame::strategy_7_7(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_14(type, myhand);
		}
		break;

	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case EIGHT:
	case NINE:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_6_6(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:

		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_14(type, myhand);
		}
		break;

	case SEVEN:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case EIGHT:
	case NINE:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_5_5(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_10(type, myhand);
		break;

	}
}

void AIGame::strategy_4_4(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case FIVE:
	case SIX:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_8(type, myhand);
		}
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_3_3(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->strategy_9(type, myhand);
		}
		break;

	case AS:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_2_2(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
		if (!hasSplit) {
			this->com.Split(this->handValue(myhand));
			hasSplit = true;
			this->aiInterface.choice(this->handValue(myhand), false, false,
					false, true, false, false);
		} else {
			this->com.AskToHIt(this->handValue(myhand));
			this->aiInterface.choice(this->handValue(myhand), true, false,
					false, false, false, false);
		}
		break;

	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
	case AS:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_A_10(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_A_9(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_A_8(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case AS:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_A_7(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case SEVEN:
	case EIGHT:
		this->com.Stand(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), false, true, false,
				false, false, false);
		break;

	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_17(type, myhand);
		break;

	case AS:
	case NINE:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	}
}

void AIGame::strategy_A_6(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_16(type, myhand);
		break;
	}
}

void AIGame::strategy_A_5(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case FOUR:
	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_15(type, myhand);
		break;
	}
}

void AIGame::strategy_A_4(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case FOUR:
	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_14(type, myhand);
		break;
	}
}

void AIGame::strategy_A_3(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {

	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_13(type, myhand);
		break;
	}
}

void AIGame::strategy_A_2(EType type, PlayerHand* myhand) {
	switch (this->bankCard.getType()) {
	case NaN:
		throw runtime_error("carte de la banque non recu ");
		break;

	case TWO:
	case THREE:
	case FOUR:
	case SEVEN:
	case EIGHT:
	case NINE:
	case AS:
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		this->com.AskToHIt(this->handValue(myhand));
		this->aiInterface.choice(this->handValue(myhand), true, false, false,
				false, false, false);
		break;

	case FIVE:
	case SIX:
		if (!hasSplit && myhand->numberOfCards() == 2 && this->ia.getHand2()==NULL) {
			this->com.Double();
			this->aiInterface.choice(this->handValue(myhand), false, false,
					true, false, false, false);
		} else
			strategy_12(type, myhand);

		break;
	}
}

int AIGame::handValue(PlayerHand* myhand) {
	if (myhand == this->ia.getHand())
		return 0;

	return 1;
}

bool AIGame::isSpecial(PlayerHand* myhand) {
	EType type1;
	EType type2;

	type1 = myhand->getCard(0)->getType();
	type2 = myhand->getCard(1)->getType();

	if (myhand->numberOfCards() == 2 && (isEqual(type1, type2, KING, KING)
			|| isEqual(type1, type2, KING, QUEEN) || isEqual(type1, type2,
			KING, JACK) || isEqual(type1, type2, KING, TEN) || isEqual(type1,
			type2, QUEEN, QUEEN) || isEqual(type1, type2, QUEEN, JACK)
			|| isEqual(type1, type2, QUEEN, TEN) || isEqual(type1, type2, JACK,
			JACK) || isEqual(type1, type2, TEN, TEN) || isEqual(type1, type2,
			AS, AS) || isEqual(type1, type2, NINE, NINE) || isEqual(type1,
			type2, EIGHT, EIGHT) || isEqual(type1, type2, SEVEN, SEVEN)
			|| isEqual(type1, type2, SIX, SIX) || isEqual(type1, type2, FIVE,
			FIVE) || isEqual(type1, type2, FOUR, FOUR) || isEqual(type1, type2,
			THREE, THREE) || isEqual(type1, type2, TWO, TWO) || isEqual(type1,
			type2, AS, NINE) || isEqual(type1, type2, AS, EIGHT) || isEqual(
			type1, type2, AS, SEVEN) || isEqual(type1, type2, AS, SIX)
			|| isEqual(type1, type2, AS, FIVE) || isEqual(type1, type2, AS,
			FOUR) || isEqual(type1, type2, AS, THREE) || isEqual(type1, type2,
			AS, TWO) || isEqual(type1, type2, AS, KING) || isEqual(type1,
			type2, AS, QUEEN) || isEqual(type1, type2, AS, JACK) || isEqual(
			type1, type2, AS, TEN)))
		return true;
	return false;
}

bool AIGame::isEqual(EType type1a, EType type1b, EType type2a, EType type2b) {
	if ((type1a == type2a && type1b == type2b) || (type1a == type2b && type1b
			== type2a))
		return true;
	return false;
}

int AIGame::getBet() {

	float bankAdvantage, iaAdvantage, standartDeviation, variance,
			optimalUnitBet;
	int optimalBet;
	int numHand, totalUnit;

	if (this->bankCard.getType() == NaN)
		return this->betMin;

	totalUnit = this->betMax / this->betMin;

	if (this->ia.getHand2() == NULL)
		numHand = 1;
	else
		numHand = 2;

	bankAdvantage = -0.0055 + 0.0063 - 0.0011;
	iaAdvantage = 0.05 * this->trueCountCard() - bankAdvantage;

	standartDeviation = 1.5 * sqrt(numHand);
	variance = pow(standartDeviation, 2);

	optimalUnitBet = (totalUnit * iaAdvantage) / variance;

	optimalBet = (int) (optimalUnitBet * this->betMin);

	if (optimalBet <= this->betMin)
		return this->betMin;

	return optimalBet;
}

int AIGame::pointCard(EType type) {

	int resultat;

	switch (type) {

	case NaN:
	case AS:
	case KING:
	case QUEEN:
	case JACK:
	case TEN:
		resultat = -1;
		break;
	case SEVEN:
	case EIGHT:
	case NINE:
		resultat = 0;
		break;
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
		resultat = 1;
		break;
	}
	return resultat;

}

float AIGame::trueCountCard() {
	float actualCount = 0, trueCount = 0;
	float numConsummeDeck = 0;
	float numRemainDeck = 0;

	for (unsigned int i(0); i < listOfCards.size(); i++) {
		actualCount += this->pointCard(listOfCards[i].getType());
	}

	numConsummeDeck = (float) listOfCards.size() / 6;
	numRemainDeck = 6 - numConsummeDeck;

	trueCount = actualCount / numRemainDeck;

	return trueCount;
}

