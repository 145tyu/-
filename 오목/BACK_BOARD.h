#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Console.h"

void SAVE_BACK_BOARD() { //�����ǿ� ������ ����
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			BACK_BOARD[Y][X] = BOARD[Y][X]; //������ == ������
		}
	}
}