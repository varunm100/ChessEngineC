#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

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

int ChessBoardBoolC[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2}};

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
			if (ChessBoardBoolC[a][b] == 1) {
				cout << BOLDRED << ChessBoard[a][b] << RESET << " | ";
			} else if (ChessBoardBoolC[a][b] == 2) {
				cout << BOLDBLACK << ChessBoard[a][b] << RESET << " | ";
			} else {
				cout << ChessBoard[a][b] << " | ";
			}
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
		ChessBoardBoolC[EndIndex][EndIndexY] = ChessBoardBoolC[StartIndex][StartIndexY];
		ChessBoardBoolC[StartIndex][StartIndexY] = 0;
		
		ChessBoard[EndIndex][EndIndexY] = ChessBoard[StartIndex][StartIndexY];
		ChessBoard[StartIndex][StartIndexY] = '#';
	} else {
		PrintError("Could Not Move Piece Because Input Location Does Not Exist!");
	}
}

vector<int> GetMovePossFromXY(int _Row, int _Col) {

	vector<int> _PieceCombinationV;
	if(ChessBoard[_Col][_Row] == '#') {
		PrintError("Selected Location Does Not Contain Piece!");
		return _PieceCombinationV;
	}
	bool _IsRed = false;
	bool _IsBlack = false;
	if (ChessBoardBoolC[_Row][_Col] == 1) {
		_IsRed = true;
	} else if (ChessBoardBoolC[_Row][_Col] == 2){
		_IsBlack = true;
	} else {
		PrintError("ERROR!");
	}
	switch(ChessBoard[_Row][_Col]) {
		case 'p':
			if (_IsRed) {
				if(_Row == 1 && ChessBoard[_Row+1][_Col] == '#') {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col);
					if (ChessBoard[_Row+2][_Col] == '#') {
						_PieceCombinationV.push_back(_Row+2);
						_PieceCombinationV.push_back(_Col);
					}
				} else if (_Row+1 < 8 && ChessBoard[_Row+1][_Col] == '#') {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col);
				}
			} else if (_IsBlack) {
				if(_Row == 6 && ChessBoard[_Row-1][_Col] == '#') {
					_PieceCombinationV.push_back(_Row-1);
					_PieceCombinationV.push_back(_Col);
					if (ChessBoard[_Row-2][_Col] == '#') {
						_PieceCombinationV.push_back(_Row-2);
						_PieceCombinationV.push_back(_Col);
					}
				} else if (_Row-1 > -1 && ChessBoard[_Row-1][_Col] == '#') {
					_PieceCombinationV.push_back(_Row-1);
					_PieceCombinationV.push_back(_Col);
				}
			}
			break;
		case 'r':
			break;
		case 'n':
			break;
		case 'b':
			break;
		case 'k':
			break;
		case 'q':
			break;
	}

	return _PieceCombinationV;
}

int main() {
	/*while(true) {
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

	}*/
	PrintBoard();
	vector<int> Combinations = GetMovePossFromXY(3,1);

	for (int i = 0; i < Combinations.size(); i++) {
		cout << Combinations[i] << "   ";
	}
	cout <<  endl;
	return 0;
}

