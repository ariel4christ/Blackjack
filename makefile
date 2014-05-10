all: Bank Player Ia

objDir = obj

Bank : $(objDir)/BankMain.o $(objDir)/Bank.o $(objDir)/Card.o $(objDir)/Hand.o $(objDir)/Participant.o $(objDir)/Player.o $(objDir)/PlayerHand.o $(objDir)/BankCommunication.o $(objDir)/BankInterface.o $(objDir)/BankGame.o
	g++ -g -o Bank $(objDir)/BankMain.o $(objDir)/Bank.o $(objDir)/Card.o $(objDir)/Hand.o $(objDir)/Participant.o $(objDir)/Player.o $(objDir)/PlayerHand.o $(objDir)/BankCommunication.o $(objDir)/BankInterface.o $(objDir)/BankGame.o

Player : $(objDir)/PlayerMain.o $(objDir)/Bank.o $(objDir)/Card.o $(objDir)/Hand.o $(objDir)/Participant.o $(objDir)/Player.o $(objDir)/PlayerHand.o $(objDir)/PlayerCommunication.o $(objDir)/HMI.o $(objDir)/UserGame.o
	g++ -g -o Player $(objDir)/PlayerMain.o $(objDir)/Bank.o $(objDir)/Card.o $(objDir)/Hand.o $(objDir)/Participant.o $(objDir)/Player.o $(objDir)/PlayerHand.o $(objDir)/PlayerCommunication.o $(objDir)/HMI.o $(objDir)/UserGame.o
	
Ia: $(objDir)/IaMain.o $(objDir)/Bank.o $(objDir)/Card.o $(objDir)/Hand.o $(objDir)/Participant.o $(objDir)/Player.o $(objDir)/PlayerHand.o $(objDir)/PlayerCommunication.o $(objDir)/AIGame.o
	g++ -g -o Ia $(objDir)/IaMain.o $(objDir)/Bank.o $(objDir)/Card.o $(objDir)/Hand.o $(objDir)/Participant.o $(objDir)/Player.o $(objDir)/PlayerHand.o $(objDir)/PlayerCommunication.o $(objDir)/AIGame.o




$(objDir)/BankMain.o : BankMain.cpp
	g++ -g -c -o $(objDir)/BankMain.o BankMain.cpp

$(objDir)/PlayerMain.o : PlayerMain.cpp
	g++ -g -c -o $(objDir)/PlayerMain.o PlayerMain.cpp
	
$(objDir)/IaMain.o : IaMain.cpp
	g++ -g -c -o $(objDir)/IaMain.o IaMain.cpp

$(objDir)/Bank.o : GameModule/Bank.h GameModule/Bank.cpp
	g++ -g -c -o $(objDir)/Bank.o GameModule/Bank.cpp

$(objDir)/Card.o : GameModule/Card.h GameModule/Card.cpp
	g++ -g -c -o $(objDir)/Card.o GameModule/Card.cpp

$(objDir)/Hand.o : GameModule/Hand.h GameModule/Hand.cpp
	g++ -g -c -o $(objDir)/Hand.o GameModule/Hand.cpp

$(objDir)/Participant.o : GameModule/Participant.h GameModule/Participant.cpp
	g++ -g -c -o $(objDir)/Participant.o GameModule/Participant.cpp

$(objDir)/Player.o : GameModule/Player.h GameModule/Player.cpp
	g++ -g -c -o $(objDir)/Player.o GameModule/Player.cpp

$(objDir)/PlayerHand.o : GameModule/PlayerHand.h GameModule/PlayerHand.cpp
	g++ -g -c -o $(objDir)/PlayerHand.o GameModule/PlayerHand.cpp


$(objDir)/BankCommunication.o : CommunicationModule/BankCommunication.h CommunicationModule/BankCommunication.cpp
	g++ -g -c -o $(objDir)/BankCommunication.o CommunicationModule/BankCommunication.cpp

$(objDir)/PlayerCommunication.o : CommunicationModule/PlayerCommunication.h CommunicationModule/PlayerCommunication.cpp
	g++ -g -c -o $(objDir)/PlayerCommunication.o CommunicationModule/PlayerCommunication.cpp


$(objDir)/AI.o : InterfaceModule/AI.h InterfaceModule/AI.cpp
	g++ -g -c -o $(objDir)/AI.o InterfaceModule/AI.cpp

$(objDir)/BankInterface.o : InterfaceModule/BankInterface.h InterfaceModule/BankInterface.cpp
	g++ -g -c -o $(objDir)/BankInterface.o InterfaceModule/BankInterface.cpp

$(objDir)/HMI.o : InterfaceModule/HMI.h InterfaceModule/HMI.cpp
	g++ -g -c -o $(objDir)/HMI.o InterfaceModule/HMI.cpp


$(objDir)/UserGame.o : UserModule/UserGame.h UserModule/UserGame.cpp
	g++ -g -c -o $(objDir)/UserGame.o UserModule/UserGame.cpp

$(objDir)/BankGame.o : BankModule/BankGame.h BankModule/BankGame.cpp
	g++ -g -c -o $(objDir)/BankGame.o BankModule/BankGame.cpp

$(objDir)/AIGame.o : AIModule/AIGame.h AIModule/AIGame.cpp
	g++ -g -c -o $(objDir)/AIGame.o AIModule/AIGame.cpp
