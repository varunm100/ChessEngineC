#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <cstring>
#include "ChessBoard.h"

using namespace std;

const int PownTable[64];
const int RookTable]64];
const int BishopTable[64];
const int QueenTable[64];
const int KingTable[64];

int evaluate(ChessBoardDef _ChessBoardInstance);