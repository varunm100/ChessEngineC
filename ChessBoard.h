#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <cstring>

using namespace std;

extern char ChessBoard[8][8];
extern int ChessBoardBoolC[8][8];
void PrintError(string errMessage);
void PrintBoard();
void SaveBoardToLog();
bool CheckLimitFoo(int _LimitRowMax, int _LimitColMax);
vector<int> GetMovePossFromXY(int _Row, int _Col);
int combine(int a, int b);
bool ValidMoveQ(int _StartX, int _StartY, int _EndX, int _EndY);
void MovePiece(int StartIndex, int StartIndexY, int EndIndex, int EndIndexY);
bool KingThreatQ();