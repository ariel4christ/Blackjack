all: Bank.o Card.o Hand.o Participant.o Player.o PlayerHand.o


Bank.o : GameModule/Bank.h GameModule/Bank.cpp
	g++ -c -o GameModule/Bank.o GameModule/Bank.cpp

Card.o : GameModule/Card.h GameModule/Card.cpp
	g++ -c -o GameModule/Card.o GameModule/Card.cpp

Hand.o : GameModule/Hand.h GameModule/Hand.cpp
	g++ -c -o GameModule/Hand.o GameModule/Hand.cpp

Participant.o : GameModule/Participant.h GameModule/Participant.cpp
	g++ -c -o GameModule/Participant.o GameModule/Participant.cpp

Player.o : GameModule/Player.h GameModule/Player.cpp
	g++ -c -o GameModule/Player.o GameModule/Player.cpp

PlayerHand.o : GameModule/PlayerHand.h GameModule/PlayerHand.cpp
	g++ -c -o GameModule/PlayerHand.o GameModule/PlayerHand.cpp