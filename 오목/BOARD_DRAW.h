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
	GotoXY_Draw(0, 0); //��ǥ 0, 0���� �̵�
	SetColor(6, 0);  // �����
	for (int i = 0; i < MAX_BOARD; i++) {
		for (int j = 0; j < MAX_BOARD; j++) {
			GotoXY_Draw(j, i); //��ǥ�� j, i�� �̵�
			if (i == 0) { //i�� 0�̰�
				if (j == 0) { //j�� 0�̶��
					printf("����");
				}
				else if (j == MAX_BOARD - 1) //j�� 14���
					printf("��");
				else
					printf("����");
			}
			else if (j == 0) { //j�� 0�̰�
				if (i == MAX_BOARD - 1) //i�� 14���
					printf("����");
				else
					printf("����");
			}
			else if (j == MAX_BOARD - 1) { //j�� 14�̰�
				if (i == MAX_BOARD - 1) //i�� 14���
					printf("��");
				else
					printf("��");
			}
			else if (i == MAX_BOARD - 1) {
				printf("����");
			}
			else
				printf("����");
		}
		printf("\n");
	}
}