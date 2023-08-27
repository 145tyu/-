#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Console.h"

void GotoXY_Draw(int _x, int _y) {
	COORD pos = { _x * 2, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DRAW_BOARD(int MAX_BOARD) {
	GotoXY_Draw(0, 0); //좌표 0, 0으로 이동
	SetColor(6, 0);  // 노란색
	for (int i = 0; i < MAX_BOARD; i++) {
		for (int j = 0; j < MAX_BOARD; j++) {
			GotoXY_Draw(j, i); //좌표를 j, i로 이동
			if (i == 0) { //i가 0이고
				if (j == 0) { //j가 0이라면
					printf("┌─");
				}
				else if (j == MAX_BOARD - 1) //j가 14라면
					printf("┐");
				else
					printf("┬─");
			}
			else if (j == 0) { //j가 0이고
				if (i == MAX_BOARD - 1) //i가 14라면
					printf("└─");
				else
					printf("├─");
			}
			else if (j == MAX_BOARD - 1) { //j가 14이고
				if (i == MAX_BOARD - 1) //i가 14라면
					printf("┘");
				else
					printf("┤");
			}
			else if (i == MAX_BOARD - 1) {
				printf("┴─");
			}
			else
				printf("┼─");
		}
		printf("\n");
	}
}