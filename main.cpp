#include "ChessBoard.h"

using namespace std;

int main() {
	while(true) {
		PrintBoard();
		SaveBoardToLog();
		int StartX = 0;
		int StartY = 0;
		int UsrMoveX = 0;
		int UsrMoveY = 0;
		cout << "Which Piece Would You Like To Move?: ";
		cin >> StartX >> StartY;
		cout << "Where Should The Piece Move To?: ";
		cin >> UsrMoveX >> UsrMoveY;
		MovePiece(StartX, StartY, UsrMoveX, UsrMoveY);
		for (int i = 0; i < 38;i++) {
			cout <<  endl;
		}
	}
	return 0;
}

