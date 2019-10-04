//Client

#include "TicTacToeClient.h"

//
//Main loop
std::vector<std::vector<char>> gameBoard;
void main() {
	TicTacToeClient T;
	T.createBoard();
	T.printBoard(gameBoard);
	T.clientConnection();
	system("pause");
}