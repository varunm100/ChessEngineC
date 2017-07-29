#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

/*-------IMPORTANT DEFINITIONS-------*/
ofstream fout ("ChessGame.log");
char ChessBoard[8][8] = {
	{'r','n','b','k','q','b','n','r'},
	{'p','p','p','p','p','p','p','p'},
	{'#','#','#','#','#','#','#','#'},
	{'#','#','#','#','#','#','#','#'},
	{'#','#','#','#','#','#','#','#'},
	{'#','#','#','#','#','#','#','#'},
	{'p','p','p','p','p','p','p','p'},
	{'r','n','b','k','q','b','n','r'}};

/*------------------------------------*/

void PrintError(string errMessage) {
	cout << "\033[1;31mERROR: \033[0m";
	cout << errMessage << endl;
}

void PrintBoard() {
	cout << "    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |" << endl;
	cout << "------------------------------------" << endl;
	for (int a = 0; a < 8; a++) {
		cout << a << "   ";
		cout << "| ";
		for (int b = 0; b < 8; b++) {
			cout << ChessBoard[a][b] << " | ";
		}
		cout <<  endl;
		cout << "------------------------------------" << endl;
	}
}

void SaveBoardToLog() {
	fout << "    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |" << endl;
	fout << "------------------------------------" << endl;
	for (int a = 0; a < 8; a++) {
		fout << a << "   ";
		fout << "| ";
		for (int b = 0; b < 8; b++) {
			fout << ChessBoard[a][b] << " | ";
		}
		fout <<  endl;
		fout << "------------------------------------" << endl;
	}
	fout << endl;
	fout << endl;
	fout << endl;
	fout << endl;
}

void MovePiece(int StartIndex, int StartIndexY, int EndIndex, int EndIndexY) {
	if (ChessBoard[StartIndex][StartIndexY] == '#') {
		PrintError("The selected location has no containing piece!");
	} else if (ChessBoard[EndIndex][EndIndexY] != '#') {
		PrintError("Could Not Move Piece to location because a piece is already there!");
	} else if (StartIndex < 8 && StartIndexY < 8 && EndIndex < 8 && EndIndexY < 8) {
		ChessBoard[EndIndex][EndIndexY] = ChessBoard[StartIndex][StartIndexY];
		ChessBoard[StartIndex][StartIndexY] = '#';
	} else {
		PrintError("Could Not Move Piece Because Input Location Does Not Exist!");
	}
}

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
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;

	}

	return 0;
}

