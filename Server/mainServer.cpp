//SERVER
#include "TicTacToeServer.h"

//
//Main loop
std::vector<std::vector<char>> gameBoard;
void main() {
	TicTacToeServer T;
	T.createBoard();
	T.printBoard(gameBoard);
	T.serverConnection();
	system("pause");
}