#include "TicTacToeServer.h"
#include <iostream>



TicTacToeServer::TicTacToeServer()
{
}


TicTacToeServer::~TicTacToeServer()
{
}
//
//Alternating between the players.
void TicTacToeServer::switchPlayer()
{
}
//
//Create our game board
void TicTacToeServer::createBoard()
{
	//Resize and alocate.
	gameBoard.resize(boardSize);
	for (int i = 0; i < boardSize; ++i) {
		gameBoard[i].resize(boardSize);
	}
	//Fill the board with '*'.
	for (int row = 0; row < gameBoard.size(); row++) {
		for (int col = 0; col < gameBoard[row].size(); col++) {
			gameBoard[row][col] = { '*' };
		}
	}
}
//
//Convert the game board to one dimension.
std::vector<char> TicTacToeServer::toOneDim(std::vector<std::vector<char>> gameBoard)
{
	std::vector<char>oneDimContainer;
	for (int row = 0; row < gameBoard.size(); row++) {
		for (int col = 0; col < gameBoard[row].size(); col++) {
			oneDimContainer.push_back(gameBoard[row][col]);
		}
	}
	return oneDimContainer;
}
//
//Print the game board.
void TicTacToeServer::printBoard(std::vector<std::vector<char>> gameBoardContainer)
{
	for (int row = 0; row < gameBoardContainer.size(); row++) {
		for (int col = 0; col < gameBoardContainer[row].size(); col++) {
			std::cout << gameBoardContainer[row][col];
		}
		std::cout << "\n---\n";
	}
}
//
//Print in one dim.
void TicTacToeServer::printOneDim(std::vector<char> oneDimContainer)
{
	for (size_t i = 0; i < oneDimContainer.size(); i++) {
		std::cout << oneDimContainer[i];
	}
}
//
//Player positioning.
void TicTacToeServer::choosePosition(std::vector<std::vector<char>> gameBoardPosition, char playerChar)
{
	if (newCoordinates.empty()) {
		int Xpos, Ypos;
		//Inserting cordinates of the game player.
		std::cin >> Xpos;
		std::cin >> Ypos;
		std::string XStr = std::to_string(Xpos);
		std::string YStr = std::to_string(Ypos);
		newCoordinates = XStr + YStr;
		//std::cout << "(choosePosition1)coordinates = " << newCoordinates;
		//Check if occupied och legal input.
		while (Xpos > boardSize - 1 || Ypos > boardSize - 1 || Xpos < 0 || Ypos < 0) {
			std::cout << "\nINVALID INPUT!\nCHOOSE A NUMBER BETWEEN 0 AND 2." << std::endl;
			std::cin >> Xpos;
			std::cin >> Ypos;
			if (Xpos <= boardSize - 1 || Ypos <= boardSize - 1 || Xpos >= 0 || Ypos >= 0) {
				std::string XStr = std::to_string(Xpos);
				std::string YStr = std::to_string(Ypos);
				newCoordinates = XStr + YStr;
				std::cout << "(choosePosition2)coordinates = " << newCoordinates;
				break;
			}
		}
		if (gameBoardPosition[Xpos][Ypos] == 'x' || gameBoardPosition[Xpos][Ypos] == 'o') {
			std::cout << "\n(line 94)THE POSITION IS OCCUPIED. CHOOSE ANOTHER COORDINATES!" << std::endl;
			std::cin >> Xpos;
			std::cin >> Ypos;
			std::string XStr = std::to_string(Xpos);
			std::string YStr = std::to_string(Ypos);
			newCoordinates = XStr + YStr;
		}
		gameBoardPosition[Xpos][Ypos] = playerChar;
		std::cout << "PLAYER: " << gameBoardPosition[Xpos][Ypos] << std::endl;
		//Update game board.
		gameBoard = gameBoardPosition;
		printBoard(gameBoard);
	}
	else {
		char XStr = newCoordinates[0];
		char YStr = newCoordinates[1];
		int Xpos = (int)XStr - 48;
		int Ypos = (int)YStr - 48;
		while (Xpos > boardSize - 1 || Ypos > boardSize - 1 || Xpos < 0 || Ypos < 0) {
			std::cout << "\nINVALID INPUT!\nCHOOSE A NUMBER BETWEEN 0 AND 2." << std::endl;
			std::cin >> Xpos;
			std::cin >> Ypos;
			if (Xpos <= boardSize - 1 || Ypos <= boardSize - 1 || Xpos >= 0 || Ypos >= 0) {
				std::string XStr = std::to_string(Xpos);
				std::string YStr = std::to_string(Ypos);
				newCoordinates = XStr + YStr;
				break;
			}
		}
		if (gameBoardPosition[Xpos][Ypos] != '*') {
			std::cout << "\nTHE POSITION IS OCCUPIED. CHOOSE ANOTHER COORDINATES!" << std::endl;
			std::cin >> Xpos;
			std::cin >> Ypos;
			std::string XStr = std::to_string(Xpos);
			std::string YStr = std::to_string(Ypos);
			newCoordinates = XStr + YStr;
		}
		gameBoardPosition[Xpos][Ypos] = playerChar;
		std::cout << "PLAYER: " << gameBoardPosition[Xpos][Ypos] << std::endl;
		//Update game board.
		gameBoard = gameBoardPosition;
		printBoard(gameBoard);
	}
}

//Check if we have a winner!
bool TicTacToeServer::isWinner(std::vector<std::vector<char>> gameBoard, char playerChar)
{
	for (int i = 0; i < boardSize; i++) {
		if ((gameBoard[i][0] == playerChar) && (gameBoard[i][0] == gameBoard[i][1]) && (gameBoard[i][1] == gameBoard[i][2])) {
			std::cout << "CONGRATULATIONS!\n [" << playerChar << "] IS THE WINNER." << std::endl;
			return true; //We won!
		}
	}

	//Check the columns
	for (int i = 0; i < boardSize; i++) {
		if ((gameBoard[0][i] == playerChar) && (gameBoard[0][i] == gameBoard[1][i]) && (gameBoard[1][i] == gameBoard[2][i])) {
			std::cout << "Congratulations!\n [" << playerChar << "] IS THE WINNER." << std::endl;
			return true; //We won!
		}
	}

	//Check top left diagonal
	if ((gameBoard[0][0] == playerChar) && (gameBoard[0][0] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[2][2])) {
		std::cout << "CONGRATULATIONS!\n [" << playerChar << "] is the winner" << std::endl;
		return true; //We won!
	}

	//Check top right diagonal
	if ((gameBoard[2][0] == playerChar) && (gameBoard[2][0] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[0][2])) {
		std::cout << "CONGRATULATIONS!\n [" << playerChar << "] IS THE WINNER." << std::endl;
		return true; //We won!
	}

	return false;
}

void TicTacToeServer::serverConnection() {
	//Initialize winsock.
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOK = WSAStartup(ver, &wsData);

	//If we cant Initialize winsock.
	if (wsOK != 0) {
		std::cerr << "Can't Initialize winsock! Quitting" << std::endl;
		return;
	}

	//Create a socket.
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return;
	}

	//Bind the IP address and port to a socket.
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell winsock the socket is for listening.
	listen(listening, SOMAXCONN);

	//Wait for a connection.
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		//client remote name.
	char service[NI_MAXHOST];	//Service (i.e. port) the client is connected on.

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << host << "CONNECTED ON PORT " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << "CONNECTED ON PORT " << ntohs(client.sin_port) << std::endl;
	}

	//Close listening socket.
	closesocket(listening);

	//
	//While loop: accept and echo massage back to client.
	char buf[12288];
	int iterator = 0;
	while (true) {
		//ZeroMemory(buf, 4096);
		ZeroMemory(buf, 12288);

		//Wait for client to send data.
		int bytesReceived = recv(clientSocket, buf, 12288, 0);
		if (bytesReceived == SOCKET_ERROR) {
			std::cerr << "Error in recv(). Quitting" << std::endl;
			break;
		}
		if (bytesReceived == 0) {
			std::cout << "Client disconnected " << std::endl;
			break;
		}

		//Saving the new coordinates obtained from the client.
		newCoordinates = std::string(buf, 0, bytesReceived);
		//Echo message back to client.
		if (newCoordinates.size() > 0) {
			if (iterator % 2 == 0) {
				choosePosition(gameBoard, player1Char);
				isWinner(gameBoard, player1Char);
				newCoordinates = "";
				choosePosition(gameBoard, player2Char);
				isWinner(gameBoard, player1Char);
				send(clientSocket, newCoordinates.c_str(), newCoordinates.size(), 0);

				iterator++;
			}
			else {
				choosePosition(gameBoard, player1Char);
				isWinner(gameBoard, player1Char);
				newCoordinates = "";
				choosePosition(gameBoard, player2Char);
				isWinner(gameBoard, player1Char);
				send(clientSocket, newCoordinates.c_str(), bytesReceived + 1, 0);
				iterator++;
			}	
		}
	}
	
		//close a socket.
		closesocket(clientSocket);
		//
		//CLean Up or shutdown winsock.
		WSACleanup();
		system("pause");
}