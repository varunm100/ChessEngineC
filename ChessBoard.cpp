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

/*-------IMPORTANT DEFINITIONS-------*/
ofstream fout ("ChessGame.log");
//Other are included in ChessBoard.h file.
/*------------------------------------*/

ChessBoardDef::ChessBoardDef(char _ChessBoard[8][8], int _ChessBoardBoolC[8][8]) {
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			ChessBoard[a][b] = _ChessBoard[a][b];
			ChessBoardBoolC[a][b] = _ChessBoardBoolC[a][b];
		}
	}

}

void ChessBoardDef::PrintError(string errMessage) {
	cout << "\033[1;31mERROR: \033[0m";
	cout << errMessage << endl;
}

void ChessBoardDef::PrintBoard() {
	cout << "    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |" << endl;
	cout << "------------------------------------" << endl;
	for (int a = 0; a < 8; a++) {
		cout << a << "   ";
		cout << "| ";
		for (int b = 0; b < 8; b++) {
			if (ChessBoardBoolC[a][b] == 1) {
				cout << BOLDRED << ChessBoard[a][b] << RESET << " | ";
			} else if (ChessBoardBoolC[a][b] == 2) {
				cout << BOLDGREEN << ChessBoard[a][b] << RESET << " | ";
			} else {
				cout << ChessBoard[a][b] << " | ";
			}
		}
		cout <<  endl;
		cout << "------------------------------------" << endl;
	}
}

void ChessBoardDef::SaveBoardToLog() {
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

bool ChessBoardDef::CheckLimitFoo(int _LimitRowMax, int _LimitColMax) {
	if (_LimitRowMax <= 7 && _LimitRowMax >= 0 && _LimitColMax >= 0 && _LimitColMax <= 7) {
		return true;
	} else {
		return false;
	}
}

vector<int> ChessBoardDef::GetMovePossFromXY(int _Row, int _Col) {
	vector<int> _PieceCombinationV;
	if(ChessBoard[_Row][_Col] == '#') {
		PrintError("Selected Location Does Not Contain Piece!");
		cout << ChessBoard[_Col][_Row] << endl;
		return _PieceCombinationV;
	}
	bool _IsRed = false;
	bool _IsBlack = false;
	if (ChessBoardBoolC[_Row][_Col] == 1) {
		_IsRed = true;
	} else if (ChessBoardBoolC[_Row][_Col] == 2){
		_IsBlack = true;
	} else {
		cout << ChessBoardBoolC[_Row][_Col] << endl;
		PrintError("ERROR!");
	}
	int _ChessCheckLimits[8][8];
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			_ChessCheckLimits[x][y] = _ChessCheckLimits[x][y];
		}
	}
	fill(_ChessCheckLimits[0], _ChessCheckLimits[0] + 8 * 8, std::numeric_limits<double>::quiet_NaN());
	//Some important Stuff
	int BoolToNum = ChessBoardBoolC[_Row][_Col];
	int BoolToNumOpp = 0;
	if (BoolToNum == 1){BoolToNumOpp = 2;} else if (BoolToNum == 2) {BoolToNumOpp = 1;}
	//Ending to important stuff
	switch(ChessBoard[_Row][_Col]) {
		case 'p':
			if (_IsRed) {
				if (!isnan(_ChessCheckLimits[_Row+1][_Col+1]) && ChessBoardBoolC[_Row+1][_Col+1] == 2) {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col+1);
				}
				if (!isnan(_ChessCheckLimits[_Row+1][_Col-1]) && ChessBoardBoolC[_Row+1][_Col-1] == 2) {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col-1);
				}
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
			if(_IsRed) {
				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row+i][_Col] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row+i,_Col) && ChessBoardBoolC[_Row+i][_Col] != 1) {
						_PieceCombinationV.push_back(_Row+i);
						_PieceCombinationV.push_back(_Col);
						if(ChessBoardBoolC[_Row+i][_Col] == 2) {
							cout << "YO" << endl;
							break;
						}
					}
				}
				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row-i][_Col] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row-i, _Col) && ChessBoardBoolC[_Row-i][_Col] != 1) {
						_PieceCombinationV.push_back(_Row-i);
						_PieceCombinationV.push_back(_Col); 
						if(ChessBoardBoolC[_Row-i][_Col] == 2) {
							break;
						}
					}
				}

				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row][_Col+i] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col+i) && ChessBoardBoolC[_Row][_Col+i] != 1) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col+i);
						if(ChessBoardBoolC[_Row][_Col+i] == 2) {
							break;
						}
					}
				}
				for (int i = 1; i < 8;i++) {
					if (ChessBoardBoolC[_Row][_Col-i] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col-i) && ChessBoardBoolC[_Row][_Col-i] != 1) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col-i);
						if(ChessBoardBoolC[_Row][_Col-i] == 2) {
							break;
						}
					}
				}
			} else if (_IsBlack) {
				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row+i][_Col] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row+i,_Col) && ChessBoardBoolC[_Row+i][_Col] != 2) {
						_PieceCombinationV.push_back(_Row+i);
						_PieceCombinationV.push_back(_Col);
						if(ChessBoardBoolC[_Row+i][_Col] == 1) {
							break;
						}
					}

				}

				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row-i][_Col] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row-i, _Col) && ChessBoardBoolC[_Row-i][_Col] != 2) {
						_PieceCombinationV.push_back(_Row-i);
						_PieceCombinationV.push_back(_Col); 
						if(ChessBoardBoolC[_Row-i][_Col] == 1) {
							break;
						}
					}
				}

				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row][_Col+i] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col+i) && ChessBoardBoolC[_Row][_Col+i] != 2) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col+i);
						if(ChessBoardBoolC[_Row][_Col+i] == 1) {
							break;
						}
					}
				}
				for (int i = 1; i < 8;i++) {
					if (ChessBoardBoolC[_Row][_Col-i] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col-i) && ChessBoardBoolC[_Row][_Col-i] != 2) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col-i);
						if(ChessBoardBoolC[_Row][_Col-i] == 1) {
							break;
						}
					}
				}
			} else {
				PrintError("ERROR while proccessing rook piece");
			}
			break;
		case 'n':
			if (_IsRed) {
				//Up and Down
				if (CheckLimitFoo(_Row+2,_Col+1) && ChessBoardBoolC[_Row+2][_Col+1] != 1) {
					_PieceCombinationV.push_back(_Row+2);
					_PieceCombinationV.push_back(_Col+1);
				}
				if (CheckLimitFoo(_Row+2,_Col-1) && ChessBoardBoolC[_Row+2][_Col-1] != 1) {
					_PieceCombinationV.push_back(_Row+2);
					_PieceCombinationV.push_back(_Col-1);
				}
				if (CheckLimitFoo(_Row-2,_Col+1) && ChessBoardBoolC[_Row-2][_Col+1] != 1) {
					_PieceCombinationV.push_back(_Row-2);
					_PieceCombinationV.push_back(_Col+1);
				}
				if (CheckLimitFoo(_Row-2,_Col-1) && ChessBoardBoolC[_Row-2][_Col-1] != 1) {
					_PieceCombinationV.push_back(_Row-2);
					_PieceCombinationV.push_back(_Col-1);
				}


				if (CheckLimitFoo(_Row+1,_Col+2) && ChessBoardBoolC[_Row+1][_Col+2] != 1) {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col+2);
				}
				if (CheckLimitFoo(_Row+1,_Col-2) && ChessBoardBoolC[_Row+1][_Col-2] != 1) {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col-2);
				}
				if (CheckLimitFoo(_Row-1,_Col+2) && ChessBoardBoolC[_Row-1][_Col+2] != 1) {
					_PieceCombinationV.push_back(_Row-1);
					_PieceCombinationV.push_back(_Col+2);
				}
				if (CheckLimitFoo(_Row-1,_Col-2) && ChessBoardBoolC[_Row-1][_Col-2] != 1) {
					_PieceCombinationV.push_back(_Row-1);
					_PieceCombinationV.push_back(_Col-2);
				}
			} else if (_IsBlack) {
				
				if (CheckLimitFoo(_Row+2,_Col+1) && ChessBoardBoolC[_Row+2][_Col+1] != 2) {
					_PieceCombinationV.push_back(_Row+2);
					_PieceCombinationV.push_back(_Col+1);
				}
				if (CheckLimitFoo(_Row+2,_Col-1) && ChessBoardBoolC[_Row+2][_Col-1] != 2) {
					_PieceCombinationV.push_back(_Row+2);
					_PieceCombinationV.push_back(_Col-1);
				}
				if (CheckLimitFoo(_Row-2,_Col+1) && ChessBoardBoolC[_Row-2][_Col+1] != 2) {
					_PieceCombinationV.push_back(_Row-2);
					_PieceCombinationV.push_back(_Col+1);
				}
				if (CheckLimitFoo(_Row-2,_Col-1) && ChessBoardBoolC[_Row-2][_Col-1] != 2) {
					_PieceCombinationV.push_back(_Row-2);
					_PieceCombinationV.push_back(_Col-1);
				}
				

				if (CheckLimitFoo(_Row+1,_Col+2) && ChessBoardBoolC[_Row+1][_Col+2] != 2) {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col+2);
				}
				if (CheckLimitFoo(_Row+1,_Col-2) && ChessBoardBoolC[_Row+1][_Col-2] != 2) {
					_PieceCombinationV.push_back(_Row+1);
					_PieceCombinationV.push_back(_Col-2);
				}
				if (CheckLimitFoo(_Row-1,_Col+2) && ChessBoardBoolC[_Row-1][_Col+2] != 2) {
					_PieceCombinationV.push_back(_Row-1);
					_PieceCombinationV.push_back(_Col+2);
				}
				if (CheckLimitFoo(_Row-1,_Col-2) && ChessBoardBoolC[_Row-1][_Col-2] != 2) {
					_PieceCombinationV.push_back(_Row-1);
					_PieceCombinationV.push_back(_Col-2);
				}
			} else {
				PrintError("ERROR while proccessing knight piece");
			}
			break;
		case 'b':
			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row+i][_Col+i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row+i,_Col+i) && ChessBoardBoolC[_Row+i][_Col+i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row+i);
					_PieceCombinationV.push_back(_Col+i);
					if (ChessBoardBoolC[_Row+i][_Col+i] == BoolToNumOpp) {
						break;
					}
				}
			}
			
			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row+i][_Col-i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row+i,_Col-i) && ChessBoardBoolC[_Row+i][_Col-i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row+i);
					_PieceCombinationV.push_back(_Col-i);
					if (ChessBoardBoolC[_Row+i][_Col-i] == BoolToNumOpp) {
						break;
					}
				}
			}

			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row-i][_Col+i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row-i,_Col+i) && ChessBoardBoolC[_Row-i][_Col+i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row-i);
					_PieceCombinationV.push_back(_Col+i);
					if (ChessBoardBoolC[_Row-i][_Col+i] == BoolToNumOpp) {
						break;
					}
				}
			}

			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row-i][_Col-i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row-i,_Col-i) && ChessBoardBoolC[_Row-i][_Col-i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row-i);
					_PieceCombinationV.push_back(_Col-i);
					if (ChessBoardBoolC[_Row-i][_Col-i] == BoolToNumOpp) {
						break;
					}
				}
			}
			break;
		case 'k':
			if (CheckLimitFoo(_Row+1,_Col+1) && ChessBoardBoolC[_Row+1][_Col+1] != BoolToNum) {
				_PieceCombinationV.push_back(_Row+1);
				_PieceCombinationV.push_back(_Col+1);
			}
			if (CheckLimitFoo(_Row-1,_Col+1) && ChessBoardBoolC[_Row-1][_Col+1] != BoolToNum) {
				_PieceCombinationV.push_back(_Row-1);
				_PieceCombinationV.push_back(_Col+1);	
			}
			if (CheckLimitFoo(_Row+1,_Col-1) && ChessBoardBoolC[_Row+1][_Col-1] != BoolToNum) {
				_PieceCombinationV.push_back(_Row+1);
				_PieceCombinationV.push_back(_Col-1);
			}
			if (CheckLimitFoo(_Row-1,_Col-1) && ChessBoardBoolC[_Row-1][_Col-1] != BoolToNum) {
				_PieceCombinationV.push_back(_Row-1);
				_PieceCombinationV.push_back(_Col-1);
			}

			if (CheckLimitFoo(_Row-1,_Col) && ChessBoardBoolC[_Row-1][_Col] != BoolToNum) {
				_PieceCombinationV.push_back(_Row-1);
				_PieceCombinationV.push_back(_Col);
			}
			if (CheckLimitFoo(_Row+1,_Col) && ChessBoardBoolC[_Row+1][_Col] != BoolToNum) {
				_PieceCombinationV.push_back(_Row+1);
				_PieceCombinationV.push_back(_Col);
			}
			if (CheckLimitFoo(_Row,_Col-1) && ChessBoardBoolC[_Row][_Col-1] != BoolToNum) {
				_PieceCombinationV.push_back(_Row);
				_PieceCombinationV.push_back(_Col-1);
			}
			if (CheckLimitFoo(_Row,_Col+1) && ChessBoardBoolC[_Row][_Col+1] != BoolToNum) {
				_PieceCombinationV.push_back(_Row);
				_PieceCombinationV.push_back(_Col+1);
			}
			break;
		case 'q':
			if(_IsRed) {
				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row+i][_Col] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row+i,_Col) && ChessBoardBoolC[_Row+i][_Col] != 1) {
						_PieceCombinationV.push_back(_Row+i);
						_PieceCombinationV.push_back(_Col);
						if(ChessBoardBoolC[_Row+i][_Col] == 2) {
							cout << "YO" << endl;
							break;
						}
					}
				}
				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row-i][_Col] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row-i, _Col) && ChessBoardBoolC[_Row-i][_Col] != 1) {
						_PieceCombinationV.push_back(_Row-i);
						_PieceCombinationV.push_back(_Col); 
						if(ChessBoardBoolC[_Row-i][_Col] == 2) {
							break;
						}
					}
				}

				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row][_Col+i] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col+i) && ChessBoardBoolC[_Row][_Col+i] != 1) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col+i);
						if(ChessBoardBoolC[_Row][_Col+i] == 2) {
							break;
						}
					}
				}
				for (int i = 1; i < 8;i++) {
					if (ChessBoardBoolC[_Row][_Col-i] == 1) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col-i) && ChessBoardBoolC[_Row][_Col-i] != 1) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col-i);
						if(ChessBoardBoolC[_Row][_Col-i] == 2) {
							break;
						}
					}
				}
			} else if (_IsBlack) {
				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row+i][_Col] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row+i,_Col) && ChessBoardBoolC[_Row+i][_Col] != 2) {
						_PieceCombinationV.push_back(_Row+i);
						_PieceCombinationV.push_back(_Col);
						if(ChessBoardBoolC[_Row+i][_Col] == 1) {
							break;
						}
					}

				}

				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row-i][_Col] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row-i, _Col) && ChessBoardBoolC[_Row-i][_Col] != 2) {
						_PieceCombinationV.push_back(_Row-i);
						_PieceCombinationV.push_back(_Col); 
						if(ChessBoardBoolC[_Row-i][_Col] == 1) {
							break;
						}
					}
				}

				for (int i = 1; i < 8;i++) {
					if(ChessBoardBoolC[_Row][_Col+i] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col+i) && ChessBoardBoolC[_Row][_Col+i] != 2) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col+i);
						if(ChessBoardBoolC[_Row][_Col+i] == 1) {
							break;
						}
					}
				}
				for (int i = 1; i < 8;i++) {
					if (ChessBoardBoolC[_Row][_Col-i] == 2) {
						break;
					}
					if (CheckLimitFoo(_Row, _Col-i) && ChessBoardBoolC[_Row][_Col-i] != 2) {
						_PieceCombinationV.push_back(_Row);
						_PieceCombinationV.push_back(_Col-i);
						if(ChessBoardBoolC[_Row][_Col-i] == 1) {
							break;
						}
					}
				}
			} else {
				PrintError("ERROR while proccessing rook piece");
			}
			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row+i][_Col+i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row+i,_Col+i) && ChessBoardBoolC[_Row+i][_Col+i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row+i);
					_PieceCombinationV.push_back(_Col+i);
					if (ChessBoardBoolC[_Row+i][_Col+i] == BoolToNumOpp) {
						break;
					}
				}
			}
			
			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row+i][_Col-i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row+i,_Col-i) && ChessBoardBoolC[_Row+i][_Col-i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row+i);
					_PieceCombinationV.push_back(_Col-i);
					if (ChessBoardBoolC[_Row+i][_Col-i] == BoolToNumOpp) {
						break;
					}
				}
			}

			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row-i][_Col+i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row-i,_Col+i) && ChessBoardBoolC[_Row-i][_Col+i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row-i);
					_PieceCombinationV.push_back(_Col+i);
					if (ChessBoardBoolC[_Row-i][_Col+i] == BoolToNumOpp) {
						break;
					}
				}
			}

			for (int i = 1; i < 8; i++) {
				if (ChessBoardBoolC[_Row-i][_Col-i] == BoolToNum) {
					break;
				}
				if (CheckLimitFoo(_Row-i,_Col-i) && ChessBoardBoolC[_Row-i][_Col-i] != BoolToNum) {
					_PieceCombinationV.push_back(_Row-i);
					_PieceCombinationV.push_back(_Col-i);
					if (ChessBoardBoolC[_Row-i][_Col-i] == BoolToNumOpp) {
						break;
					}
				}
			}
			break;
	}
	return _PieceCombinationV;
}

int ChessBoardDef::combine(int a, int b) {
	int times = 1;
	while (times <= b){
		times *= 10;
	}
	return a*times + b;
} 

bool ChessBoardDef::ValidMoveQ(int _StartX, int _StartY, int _EndX, int _EndY) {
	vector<int> _MoveCombinations = GetMovePossFromXY(_StartX, _StartY);
	int _counter1 = 0;
	if (_MoveCombinations.size() == 0) {
		return false;
	}
	int _FinalNum = combine(_EndX+1,_EndY+1);
	while(!_MoveCombinations.empty()) {
		int _YCounter = _MoveCombinations.back()+1;
		_MoveCombinations.pop_back();
		int _XCounter = _MoveCombinations.back()+1;
		_MoveCombinations.pop_back();
		int _conCate = combine(_XCounter,_YCounter);
		if (_conCate == _FinalNum) {
			return true;
		}
	}
	return false;
}

void ChessBoardDef::MovePiece(int StartIndex, int StartIndexY, int EndIndex, int EndIndexY) {
	int BlackWhiteQ = ChessBoardBoolC[StartIndex][StartIndexY];
	
	if (ChessBoard[StartIndex][StartIndexY] == '#') {
		PrintError("The selected location has no containing piece!");
	} else if (ChessBoard[EndIndex][EndIndexY] == 'k') {
		PrintError("You CANNOT eleiminate the King, you can only CAPTURE it!");
	} else if (StartIndex < 8 && StartIndexY < 8 && EndIndex < 8 && EndIndexY < 8 && ValidMoveQ(StartIndex, StartIndexY, EndIndex, EndIndexY)) {
		ChessBoardBoolC[EndIndex][EndIndexY] = ChessBoardBoolC[StartIndex][StartIndexY];
		ChessBoardBoolC[StartIndex][StartIndexY] = 0;
		
		ChessBoard[EndIndex][EndIndexY] = ChessBoard[StartIndex][StartIndexY];
		ChessBoard[StartIndex][StartIndexY] = '#';
	} else {
		PrintError("Not A Valid Move!");
	}
}

bool ChessBoardDef::KingThreatQ(int BorW) {
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			if (ChessBoard[a][b] != '#') {
				vector<int> Poss = GetMovePossFromXY(a,b);
				while(!Poss.empty()) {
					int _YCounter = Poss.back()+1;
					Poss.pop_back();
					int _XCounter = Poss.back()+1;
					Poss.pop_back();
					if (ChessBoard[_XCounter][_YCounter] == 'k' && ChessBoardBoolC[_XCounter][_YCounter] == BorW) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void UpdatePawns() {
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			if (ChessBoard[a][b] == 'p' && (a == 0 || a == 7)) {
				ChessBoard[a][b] = 'q';
			}
		}
	}
}

void Update() {
	if (KingThreatQ(1)) {
		BlackMate = true;
	} else if (KingThreatQ(2)) {
		WhiteMate = true;
	} else {
		BlackMate = false;
		WhiteMate = false;
	}
	UpdatePawns();
}