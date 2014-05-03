all: Bank.o Card.o Hand.o Participant.o Player.o PlayerHand.o BankCommunication.o PlayerCommunication.o AI.o BankInterface.o HMI.o Interface.o BankGame.o IAGame.o UserGame.o


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


BankCommunication.o : CommunicationModule/BankCommunication.h CommunicationModule/BankCommunication.cpp
	g++ -c -o CommunicationModule/BankCommunication.o CommunicationModule/BankCommunication.cpp

PlayerCommunication.o : CommunicationModule/PlayerCommunication.h CommunicationModule/PlayerCommunication.cpp
	g++ -c -o CommunicationModule/PlayerCommunication.o CommunicationModule/PlayerCommunication.cpp


AI.o : InterfaceModule/AI.h InterfaceModule/AI.cpp
	g++ -c -o InterfaceModule/AI.o InterfaceModule/AI.cpp

BankInterface.o : InterfaceModule/BankInterface.h InterfaceModule/BankInterface.cpp
	g++ -c -o InterfaceModule/BankInterface.o InterfaceModule/BankInterface.cpp

HMI.o : InterfaceModule/HMI.h InterfaceModule/HMI.cpp
	g++ -c -o InterfaceModule/HMI.o InterfaceModule/HMI.cpp

Interface.o : InterfaceModule/Interface.h InterfaceModule/Interface.cpp
	g++ -c -o InterfaceModule/Interface.o InterfaceModule/Interface.cpp


UserGame.o : UserModule/UserGame.h UserModule/UserGame.cpp
	g++ -c -o UserModule/UserGame.o UserModule/UserGame.cpp

BankGame.o : BankModule/BankGame.h BankModule/BankGame.cpp
	g++ -c -o BankModule/BankGame.o BankModule/BankGame.cpp

IAGame.o : IAModule/IAGame.h IAModule/IAGame.cpp
	g++ -c -o IAModule/IAGame.o IAModule/IAGame.cpp
