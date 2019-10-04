#include "TicTacToeClient.h"
#include <iostream>

TicTacToeClient::TicTacToeClient()
{
}


TicTacToeClient::~TicTacToeClient()
{
}
//
//Alternating between the players.
void TicTacToeClient::switchPlayer()
{
	if (iterator % 2 == 0) {
		Player1 = false;
		Player2 = true;
		iterator++;
	}
	else {
		Player1 = true;
		Player2 = false;
		iterator++;
	}
}
//
//Create our game board
void TicTacToeClient::createBoard()
{
	//Resize and alocate.
	gameBoard.resize(boardSize);
	for (int i = 0; i < boardSize; ++i) {
		gameBoard[i].resize(boardSize);
	}
	//Fill the board with '*'.
	for (unsigned int row = 0; row < gameBoard.size(); row++) {
		for (unsigned int col = 0; col < gameBoard[row].size(); col++) {
			gameBoard[row][col] = { '*' };
		}
	}
}
//
//Convert the game board to one dimension.
std::vector<char> TicTacToeClient::toOneDim(std::vector<std::vector<char>> gameBoard)
{
	std::vector<char>oneDimContainer;
	for (unsigned int row = 0; row < gameBoard.size(); row++) {
		for (unsigned int col = 0; col < gameBoard[row].size(); col++) {
			oneDimContainer.push_back(gameBoard[row][col]);
		}
	}
	return oneDimContainer;
}
//
//Print the game board.
void TicTacToeClient::printBoard(std::vector<std::vector<char>> gameBoardContainer)
{
	for (unsigned int row = 0; row < gameBoardContainer.size(); row++) {
		for (unsigned int col = 0; col < gameBoardContainer[row].size(); col++) {
			std::cout << gameBoardContainer[row][col];
		}
		std::cout << "\n---\n";
	}
}
//
//Print in one dim.
void TicTacToeClient::printOneDim(std::vector<char> oneDimContainer)
{
	for (size_t i = 0; i < oneDimContainer.size(); i++) {
		std::cout << oneDimContainer[i];
	}
}
//
//Player positioning.
void TicTacToeClient::choosePosition(std::vector<std::vector<char>> gameBoardPosition, char playerChar)
{///////////////////////////////////////////////////
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
		if (gameBoardPosition[Xpos][Ypos] == 'x' || gameBoardPosition[Xpos][Ypos] == 'o') {
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

//
//Check if we have a winner!
bool TicTacToeClient::isWinner(std::vector<std::vector<char>> gameBoard, char playerChar)
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
			std::cout << "CONGRATULATIONS!\n [" << playerChar << "] IS THE WINNER." << std::endl;
			return true; //We won!
		}
	}

	//Check top left diagonal
	if ((gameBoard[0][0] == playerChar) && (gameBoard[0][0] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[2][2])) {
		std::cout << "CONGRATULATIONS!\n [" << playerChar << "] IS THE WINNER." << std::endl;
		return true; //We won!
	}

	//Check top right diagonal
	if ((gameBoard[2][0] == playerChar) && (gameBoard[2][0] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[0][2])) {
		std::cout << "CONGRATULATIONS!\n [" << playerChar << "] IS THE WINNER." << std::endl;
		return true; //We won!
	}

	return false;
}


void TicTacToeClient::clientConnection() {
	//Connecting to the local machine.
	std::string ipAddress = "127.0.0.1";
	//
	//Listening port number on the server.
	int port = 54000;
	//
	//Intítialize WinSock.
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		std::cerr << "CAN'T START WINSOCK, ERROR # " << wsResult << std::endl;
		return;
	}
	//
	//Create socket.
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "CAN'T CREATE SOCKET, ERR # " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	//
	//Fill in a hint structure.(tells what server and what port i need to connect to.)
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	//
	//Connect to server.
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint)); //if zero then success!
	if (connResult == SOCKET_ERROR) {
		std::cerr << "CAN'T CONNECT TO THE SERVER, ERR #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	//
	//Do-while loop to send and receive data.
   //char buf[4096];
	char buf[12288];

	do {
		//For the first play.
		if (newCoordinates.empty()) {
			int Xpos, Ypos;
			//Inserting cordinates of the game player.
			std::cin >> Xpos;
			std::cin >> Ypos;
			std::string XStr = std::to_string(Xpos);
			std::string YStr = std::to_string(Ypos);
			newCoordinates = XStr + YStr;
			choosePosition(gameBoard, player1Char);
		}
		//////////////////////////////////////////

		//
		//Send the text.
		//Chech if user typed something!
		if (newCoordinates.size() > 0) {
			//Sending to the server.
			int sendResult = send(sock, newCoordinates.c_str(), newCoordinates.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				//Wait for response.
				//ZeroMemory(buf, 4096);
				ZeroMemory(buf, 12288);
				//int bytesReceived = recv(sock, buf, 4096, 0);//Returns positive integers if sucess!
				int bytesReceived = recv(sock, buf, 12288, 0);
				if (bytesReceived > 0) {
					//Response from the SERVER.
					newCoordinates = std::string(buf, 0, bytesReceived);
					if (newCoordinates.size() > 0) {
						iterator++;
						if (iterator % 2 == 0) {
							choosePosition(gameBoard, player1Char);
							isWinner(gameBoard, player1Char);
							newCoordinates = "";
							choosePosition(gameBoard, player2Char);
							isWinner(gameBoard, player1Char);
							send(sock, newCoordinates.c_str(), bytesReceived + 1, 0);
							iterator++;
						}
						else {
							choosePosition(gameBoard, player2Char);
							isWinner(gameBoard, player2Char);
							newCoordinates = "";
							choosePosition(gameBoard, player1Char);
							isWinner(gameBoard, player2Char);
							send(sock, newCoordinates.c_str(), bytesReceived + 1, 0);
							iterator++;
						}
					}
				}
			}
		}
	} while (newCoordinates.size() > 0);
	//
	//Close down everything.
	closesocket(sock);
	WSACleanup();
	system("pause");
}