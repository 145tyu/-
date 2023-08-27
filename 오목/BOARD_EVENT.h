#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BOARD_X 14 // 보드판 최대 X값
#define MAX_BOARD_Y 14 // 보드판 최대 Y값
#define MAX_BOARD 15 // 보드판 크기 15X15
#define MAX_STONE 255 // 최대 돌 개수

#define NOT_STONE 0 //없음
#define BLACK_STONE 1 //흑돌
#define WHITE_STONE 2 //백돌

int BOARD[MAX_BOARD][MAX_BOARD] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

int BACK_BOARD[MAX_BOARD][MAX_BOARD] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

void wait(int SEC) {
	clock_t END;
	END = clock() + SEC * CLOCKS_PER_SEC;
	while (clock() < END) {}
}

int _3X3(int X, int Y) { //백돌 예외처리 진행
	int Count = 0;
	//흑
	//흑
	//  흑흑

	//보드 가로 오른쪽이 흑돌이고 백돌이 주변에 없다면
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X - 1] == NOT_STONE) {
		if (BOARD[Y][X + 2] == BLACK_STONE && BOARD[Y][X + 3] == NOT_STONE) {
			Count += 1;
		}
	}
	// 보드 가로 왼쪽이 흑돌이고 백돌이 주변에 없다면
	else {
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X + 1] == NOT_STONE) {
			if (BOARD[Y][X - 2] == BLACK_STONE && BOARD[Y][X - 3] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//보드 세로 아래쪽이 흑돌이고 백돌이 주변에 없다면
	if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y - 1][X] == NOT_STONE) {
		if (BOARD[Y + 2][X] == BLACK_STONE && BOARD[Y + 3][X] == NOT_STONE) {
			Count += 1;
		}
	}
	//보드 세로 위쪽이 흑돌이고 백돌이 주변에 없다면
	else {
		if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y + 1][X] == NOT_STONE) {
			if (BOARD[Y - 2][X] == BLACK_STONE && BOARD[Y - 3][X] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//보드 오른쪽 대각선 아래쪽이 흑돌이고 백돌이 주변에 없다면
	if (BOARD[Y + 1][X + 1] == BLACK_STONE && BOARD[Y - 1][X - 1] == NOT_STONE) {
		if (BOARD[Y + 2][X + 2] == BLACK_STONE && BOARD[Y + 3][X + 3] == NOT_STONE) {
			Count += 1;
		}
	}
	else {
		//보드 오른쪽 대각선 위쪽이 흑돌이고 백돌이 주변에 없다면
		if (BOARD[Y - 1][X + 1] == BLACK_STONE && BOARD[Y + 1][X - 1] == NOT_STONE) {
			if (BOARD[Y - 2][X + 2] == BLACK_STONE && BOARD[Y - 3][X + 3] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//보드 왼쪽 대각선 아래쪽이 흑돌이고 백돌이 주변에 없다면
	if (BOARD[Y + 1][X - 1] == BLACK_STONE && BOARD[Y - 1][X + 1] == NOT_STONE) {
		if (BOARD[Y + 2][X - 2] == BLACK_STONE && BOARD[Y + 3][X - 3] == NOT_STONE) {
			Count += 1;
		}
	}
	else {
		//보드 왼쪽 대각선 위쪽이 흑돌이고 백돌이 주변에 없다면
		if (BOARD[Y - 1][X - 1] == BLACK_STONE && BOARD[Y + 1][X + 1] == NOT_STONE) {
			if (BOARD[Y - 2][X - 2] == BLACK_STONE && BOARD[Y - 3][X - 3] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//카운트가 2이상이라면 true값 반환
	if (Count >= 2) return true;
	//아니라면 false값 반환
	else return false;
}

int _3X2(int X, int Y) { // 백돌 예외처리 완료
	int Count = 0;
	//     X
	//   흑 흑
	//
	//흑       흑

	//보드 오른쪽 대각선 아래쪽이 흑돌이고 사이사이 백돌이 없다면
	if (BOARD[Y + 1][X + 1] == BLACK_STONE && BOARD[Y - 1][X - 1] == NOT_STONE && BOARD[Y + 2][X + 2] == NOT_STONE && BOARD[Y + 4][X + 4] == NOT_STONE) {
		if (BOARD[Y + 3][X + 3] == BLACK_STONE) {
			Count += 1;
		}
	}
	//보드 오른쪽 대각선 위쪽이 흑돌이고 사이사이 백돌이 없다면
	if (BOARD[Y - 1][X + 1] == BLACK_STONE && BOARD[Y + 1][X - 1] == NOT_STONE && BOARD[Y - 2][X + 2] == NOT_STONE && BOARD[Y - 4][X + 4] == NOT_STONE) {
		if (BOARD[Y - 3][X + 3] == BLACK_STONE) {
			Count += 1;
		}
	}
	//보드 왼쪽 대각선 아래쪽이 흑돌이고 사이사이 백돌이 없다면
	if (BOARD[Y + 1][X - 1] == BLACK_STONE && BOARD[Y - 1][X + 1] == NOT_STONE && BOARD[Y + 2][X - 2] == NOT_STONE && BOARD[Y + 4][X - 4] == NOT_STONE) {
		if (BOARD[Y + 3][X - 3] == BLACK_STONE) {
			Count += 1;
		}
	}
	//보드 왼쪽 대각선 위쪽이 흑돌고 사이사이 백돌이 없다면
	if (BOARD[Y - 1][X - 1] == BLACK_STONE && BOARD[Y + 1][X + 1] == NOT_STONE && BOARD[Y - 2][X - 2] == NOT_STONE && BOARD[Y - 4][X - 4] == NOT_STONE) {
		if (BOARD[Y - 3][X - 3] == BLACK_STONE) {
				Count += 1;
		}
	}
	//카운트가 2이상이라면 true값 반환
	if (Count >= 2) return true;
	//아니라면 false값 반환
	else return false;
}

int _3Xplus(int X, int Y) { //백돌 예외처리 완료
	int Count = 0;
	//		흑
	//    흑X흑
	//		흑

	// 보드 오른쪽이 흑돌이고 그 다음이 백돌이 아니라면
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X + 2] == NOT_STONE) {
		// 보드 왼쪽이 흑돌이고 그 다음이 백돌이 아니라면
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X - 2] == NOT_STONE) {
			// 보드 위쪽이 흑돌이고 그 다음이 백돌이 아니라면
			if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y - 2][X] == NOT_STONE) {
				// 보드 아래쪽이 흑돌이고 그 다음이 백돌이 아니라면
				if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y + 2][X] == NOT_STONE) {
					Count += 1;
				}
			}
		}
	}
	//카운트가 1이상이라면 true값 반환
	if (Count >= 1) return true;
	//아니라면 false값 반환
	else return false;
}

int _3Xplus_(int X, int Y) { //백돌 예외처리 완료
	int Count = 0;
	//	   흑
	// 흑  X흑
	//     흑

	//보드 가로 오른쪽이 흑돌이고 백돌이 없다면
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X + 2] == NOT_STONE && BOARD[Y][X - 1] == NOT_STONE && BOARD[Y][X - 3] == NOT_STONE) {
		if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y - 2][X] == NOT_STONE) {
			if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y + 2][X] == NOT_STONE) {
				if (BOARD[Y][X - 2] == BLACK_STONE) {
					Count += 1;
				}
			}
		}
	}
	else {
		//	  흑
		//  흑X  흑
		//    흑
		
		//보드 가로 왼쪽이 흑돌이고 백돌이 없다면
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X - 2] == NOT_STONE && BOARD[Y][X + 1] == NOT_STONE && BOARD[Y][X + 3] == NOT_STONE) {
			if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y - 2][X] == NOT_STONE) {
				if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y + 2][X] == NOT_STONE) {
					if (BOARD[Y][X + 2] == BLACK_STONE) {
						Count += 1;
					}
				}
			}
		}
	}

	//	   흑
	//
	//   흑X흑
	//	   흑

	//보드 세로 아래쪽이 흑돌이고 백돌이 없다면
	if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y + 2][X] == NOT_STONE && BOARD[Y - 1][X] == NOT_STONE && BOARD[Y - 3][X] == NOT_STONE) {
		if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X + 2] == NOT_STONE) {
			if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X - 2] == NOT_STONE) {
				if (BOARD[Y - 2][X] == BLACK_STONE) {
					Count += 1;
				}
			}
		}
	}
	else {
		//	  흑
		//  흑X흑
		//    
		//    흑

		//보드 세로 위쪽이 흑돌이고 백돌이 없다면
		if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y - 2][X] == NOT_STONE && BOARD[Y + 1][X] == NOT_STONE && BOARD[Y + 3][X] == NOT_STONE) {
			if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X + 2] == NOT_STONE) {
				if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X - 2] == NOT_STONE) {
					if (BOARD[Y + 2][X] == BLACK_STONE) {
						Count += 1;
					}
				}
			}
		}
	}
	//카운트가 1이상이라면 true값 반환
	if (Count >= 1) return true;
	//아니라면 false값 반환
	else return false;
}

int _4X4(int X, int Y) {
	int Count = 0;

	//보드 가로 오른쪽이 흑돌이라면
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X - 1] == NOT_STONE) {
		if (BOARD[Y][X + 2] == BLACK_STONE) {
			if (BOARD[Y][X + 3] == BLACK_STONE && BOARD[Y][X + 4] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	else {
		//보드 가로 왼쪽이 흑돌이라면
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X + 1] == NOT_STONE) {
			if (BOARD[Y][X - 2] == BLACK_STONE) {
				if (BOARD[Y][X - 3] == BLACK_STONE && BOARD[Y][X - 4] == NOT_STONE) {
					Count += 1;
				}
			}
		}
	}
	//보드 세로 아래쪽이 흑돌이라면
	if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y - 1][X] == NOT_STONE) {
		if (BOARD[Y + 2][X] == BLACK_STONE) {
			if (BOARD[Y + 3][X] == BLACK_STONE && BOARD[Y][X + 4] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	else {
		//보드 세로 위쪽이 흑돌이라면
		if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y + 1][X] == NOT_STONE) {
			if (BOARD[Y - 2][X] == BLACK_STONE) {
				if (BOARD[Y - 3][X] == BLACK_STONE && BOARD[Y][X - 4] == NOT_STONE) {
					Count += 1;
				}
			}
		}
	}

	if (BOARD[Y + 1][X - 1] == BLACK_STONE) { //보드 오른쪽 대각선 아래쪽이 흑돌이라면
		if (BOARD[Y + 2][X - 2] == BLACK_STONE) {
			if (BOARD[Y + 3][X - 3] == BLACK_STONE) {
				Count += 1;
			}
		}
	}
	else {
		if (BOARD[Y - 1][X + 1] == BLACK_STONE) { //보드 오른쪽 대각선 위쪽이 흑돌이라면
			if (BOARD[Y - 2][X + 2] == BLACK_STONE) {
				if (BOARD[Y - 3][X + 3] == BLACK_STONE) {
					Count += 1;
				}
			}
		}
	}

	if (BOARD[Y + 1][X + 1] == BLACK_STONE) { //보드 왼쪽 대각선 아래쪽이 흑돌이라면
		if (BOARD[Y + 2][X + 2] == BLACK_STONE) {
			if (BOARD[Y + 3][X + 3] == BLACK_STONE) {
				Count += 1;
			}
		}
	}
	else {
		if (BOARD[Y - 1][X - 1] == BLACK_STONE) { //보드 왼쪽 대각선 위쪽이 흑돌이라면
			if (BOARD[Y - 2][X - 2] == BLACK_STONE) {
				if (BOARD[Y - 3][X - 3] == BLACK_STONE) {
					Count += 1;
				}
			}
		}
	}

	//카운트가 2이상이라면 true값 반환
	if (Count >= 2) return true;
	//아니라면 false값 반환
	else return false;
}

int _4X2(int X, int Y) { // 흑 흑X흑 흑
	int Count = 0; //백돌 예외처리 완료

	if (BOARD[Y][X + 1] == BLACK_STONE) { //보드 가로 오른쪽이 흑돌이라면
		if (BOARD[Y][X + 2] == NOT_STONE && BOARD[Y][X + 3] == BLACK_STONE) {
			Count += 1; //카운트
		}
	}
	if (BOARD[Y][X - 1] == 1) { //보드 가로 왼쪽이 흑돌이라면
		if (BOARD[Y][X - 2] == NOT_STONE && BOARD[Y][X - 3] == BLACK_STONE) {
			Count += 1; //카운트
		}
	}

	if (BOARD[Y + 1][X] == 1) { //보드 세로 아래쪽이 흑돌이라면
		if (BOARD[Y + 2][X] == NOT_STONE && BOARD[Y + 3][X] == BLACK_STONE) {
			Count += 1; //카운트
		}
	}
	if (BOARD[Y - 1][X] == 1) { //보드 세로 위쪽이 흑돌이라면
		if (BOARD[Y - 2][X] == NOT_STONE && BOARD[Y - 3][X] == BLACK_STONE) {
			Count += 1; //카운트
		}
	}

	//카운트가 2이상이라면 true값 반환
	if (Count >= 2) return true;
	//아니라면 false값 반환
	else return false;
}

int Renju_Rule(int X, int Y) { //참고 사이트 : http://omok.mgame.com/help/rule.htm
	// A. 3,3 금수 완료
	if (_3X3(X, Y) || _3X2(X, Y) || _3Xplus(X, Y) || _3Xplus_(X, Y)) {
		return true; //true값 반환
	}
	// B. 4,4 금수 완료
	if (_4X4(X, Y) || _4X2(X, Y)) {
		return true; //true값 반환
	}
	// C. 6,6 금수 진행
	// D. 3,3,4 금수 완료
	// E. 3,4,4 금수 완료
	else {
		return false; //false값 반환
	}
}

int BLACK_END() {
	int TEMP = 0, COUNT = 0;
	//가로에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y][X + i] == BLACK_STONE) { //해당 자리가 흑돌이면
					TEMP += 1;
					if (TEMP == 5) {
						if (BOARD[Y][X + (i + 1)] != BLACK_STONE && BOARD[Y][X - 1] != BLACK_STONE) {
							COUNT += 1;
							break;
						}
						else {
							TEMP = 0;
							break;
						}
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}
	//세로에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X] == BLACK_STONE) { //해당 자리가 흑돌이라면
					TEMP += 1;
					if (TEMP == 5) {
						if (BOARD[Y + (i + 1)][X] != BLACK_STONE && BOARD[Y - 1][X] != BLACK_STONE) {
							COUNT += 1;
							break;
						}
						else {
							TEMP = 0;
							break;
						}
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}
	//왼쪽 대각선에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X - i] == BLACK_STONE) { //해당 자리가 흑돌이라면
					TEMP += 1;
					if (TEMP == 5) {
						if (BOARD[Y + (i + 1)][X - (i + 1)] != BLACK_STONE && BOARD[Y - 1][X + 1] != BLACK_STONE) {
							COUNT += 1;
							break;
						}
						else {
							TEMP = 0;
							break;
						}
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}
	//오른쪽 대각선에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X + i] == BLACK_STONE) { //해당 자리가 흑돌이라면
					TEMP += 1;
					if (TEMP == 5) {
						if (BOARD[Y + (i + 1)][X + (i + 1)] != BLACK_STONE && BOARD[Y - 1][X - 1] != BLACK_STONE) {
							COUNT += 1;
							break;
						}
						else {
							TEMP = 0;
							break;
						}
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}

	return COUNT;
}

int WHITE_END() {
	int TEMP = 0, COUNT = 0;
	//가로에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y][X + i] == 2) {
					TEMP += 1;
					if (TEMP == 5) {
						COUNT += 1;
						break;
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}
	//세로에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X] == 2) {
					TEMP += 1;
					if (TEMP == 5) {
						COUNT += 1;
						break;
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}
	//왼쪽 대각선에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X - i] == 2) {
					TEMP += 1;
					if (TEMP == 5) {
						COUNT += 1;
						break;
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}
	//오른쪽 대각선에 5줄이 만들어졌는지
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X + i] == 2) {
					TEMP += 1;
					if (TEMP == 5) {
						COUNT += 1;
						break;
					}
				}
				else {
					TEMP = 0;
					break;
				}
			}
		}
	}

	return COUNT;
}