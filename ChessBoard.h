#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <cstring>

using namespace std;


class ChessBoardDef {
public:
	ChessBoardDef(char _ChessBoard[8][8], int _ChessBoardBoolC[8][8]);
	~ChessBoardDef(){};
	char ChessBoard[8][8];
	int ChessBoardBoolC[8][8];
	void PrintError(string errMessage);
	bool BlackMate;
	bool WhiteMate;
	void PrintBoard();
	void SaveBoardToLog();
	bool CheckLimitFoo(int _LimitRowMax, int _LimitColMax);
	vector<int> GetMovePossFromXY(int _Row, int _Col);
	int combine(int a, int b);
	bool ValidMoveQ(int _StartX, int _StartY, int _EndX, int _EndY);
	void MovePiece(int StartIndex, int StartIndexY, int EndIndex, int EndIndexY);
	bool KingThreatQ(int BorW);
	/*int EvalPosition()*/
};