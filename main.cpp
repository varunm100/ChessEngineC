#include "ChessBoard.h"

using namespace std;

char ChessBoardef[8][8] = {
	{'r','n','b','k','q','b','n','r'},
	{'p','p','p','p','p','p','p','p'},
	{'#','#','#','#','#','#','#','#'},
	{'#','#','#','#','#','#','#','#'},
	{'#','#','#','#','#','#','#','#'},
	{'#','#','#','#','#','#','#','#'},
	{'p','p','p','p','p','p','p','p'},
	{'r','n','b','k','q','b','n','r'}};
int ChessBoardBoolCdef[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2}};

int main() {
	ChessBoardDef MainChessBoard(ChessBoardef, ChessBoardBoolCdef);
	while(true) {
		MainChessBoard.PrintBoard();
		MainChessBoard.SaveBoardToLog();
		MainChessBoard.Update();
		int StartX = 0;
		int StartY = 0;
		int UsrMoveX = 0;
		int UsrMoveY = 0;
		cout << "Which Piece Would You Like To Move?: ";
		cin >> StartX >> StartY;
		cout << "Where Should The Piece Move To?: ";
		cin >> UsrMoveX >> UsrMoveY;
		MainChessBoard.MovePiece(StartX, StartY, UsrMoveX, UsrMoveY);
 		//Best number found is 38 endl's
		cout << "King State: " << MainChessBoard.KingThreatQ(1) << endl;
		cout << "King State: " << MainChessBoard.KingThreatQ(2) << endl;
	}
	return 0;
}

