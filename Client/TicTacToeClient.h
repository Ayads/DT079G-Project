#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#pragma comment(lib, "ws2_32.lib")
class TicTacToeClient
{
public:
	TicTacToeClient();
	~TicTacToeClient();
	void switchPlayer();
	void createBoard();
	std::vector<char> toOneDim(std::vector<std::vector<char>> gameBoard);
	void printBoard(std::vector<std::vector<char>> gameBoardContainer);
	void printOneDim(std::vector<char> oneDimContainer);
	bool isWinner(std::vector<std::vector<char>> gameBoard, char playerChar);
	void choosePosition(std::vector<std::vector<char>> gameBoardPosition, char playerChar);
	void clientConnection();
	bool Player1 = true;
	bool Player2 = true;
	char player1Char = 'x';
	char player2Char = 'o';
	std::string newCoordinates;
	std::vector<std::vector<char>> gameBoard;
private:
	const int boardSize = 3;
	int iterator = 0;
};