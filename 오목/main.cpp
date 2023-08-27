#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <process.h>
#include "Console.h"
#include "BOARD_DRAW.h"
#include "BOARD_EVENT.h"

#define MAX_BOARD 15 //������ ũ�� 15X15
#define MAX_BOARD_X 14 //������ �ִ� X��
#define MAX_BOARD_Y 14 //������ �ִ� Y��
#define MAX_PLAYER_X 28 //�÷��̾� X �ִ�
#define MAX_PLAYER_Y 14 //�÷��̾� Y �ִ�

#define NOT_STONE 0 //����
#define BLACK_STONE 1 //�浹
#define WHITE_STONE 2 //�鵹

struct ST_PLAYER {
	int X = 0;
	int Y = 0;
	bool Active = false;
};
ST_PLAYER PLAYER;

struct ST_STONE {
	int Total = 0;
	int Life = 3;
	bool TIMER_30 = false, TIMER_10 = false;
	bool Win = false, Lose = false; //X
	bool Active = false, Draw_Actice = false;
};
ST_STONE WHITE_STONE_STATE;
ST_STONE BLACK_STONE_STATE;

int TOTAL_STONE = 0;
int TIMER_COUNT = 30;
int PRE_STONE_COUNT = 0;
bool Breaking_Rules_State = false;
bool GAME_PLAY_S = false, GAME_READY_S = true, GAME_END_S = false, GAME_REPLAY_S = false;

////////////// ������ �ʱ�ȭ /////////////
void RESET_DATA() {
	///////////// �÷��̾� �ʱ�ȭ /////////////
	PLAYER.X = 14; //�÷��̾� �߾����� ��ġ�� �ʱ�ȭ
	PLAYER.Y = 7; //�÷��̾� �߾����� ��ġ�� �ʱ�ȭ
	PLAYER.Active = true; //�÷��̾� Ȱ��ȭ

	/////////////// �浹 �ʱ�ȭ //////////////
	BLACK_STONE_STATE.Total = 0; //�� ����
	BLACK_STONE_STATE.Life = 3; //���
	BLACK_STONE_STATE.Win = false; //�̰����
	BLACK_STONE_STATE.Active = true; //Ȱ��ȭ
	BLACK_STONE_STATE.Draw_Actice = true; //ǥ�� Ȱ��ȭ
	BLACK_STONE_STATE.TIMER_30 = false; //Ÿ�̸� ��Ȱ��ȭ
	BLACK_STONE_STATE.TIMER_10 = false; //Ÿ�̸� ��Ȱ��ȭ

	/////////////// �鵹 �ʱ�ȭ //////////////
	WHITE_STONE_STATE.Total = 0; //�� ����
	WHITE_STONE_STATE.Life = 3; //���
	WHITE_STONE_STATE.Win = false; //�̰����
	WHITE_STONE_STATE.Active = true; //Ȱ��ȭ
	WHITE_STONE_STATE.Draw_Actice = true; //ǥ�� Ȱ��ȭ
	WHITE_STONE_STATE.TIMER_30 = false; //Ÿ�̸� ��Ȱ��ȭ
	WHITE_STONE_STATE.TIMER_10 = false; //Ÿ�̸� ��Ȱ��ȭ

	TOTAL_STONE = 0; //��ü�� �ʱ�ȭ
	TIMER_COUNT = 30; //Ÿ�̸� �ʱ�ȭ
	PRE_STONE_COUNT = 0; //������ �ʱ�ȭ
	Breaking_Rules_State = false; //���ַ� ���� �ʱ�ȭ

	////////////// �ٵ��� �ʱ�ȭ /////////////
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			BOARD[Y][X] = 0; //���� �ٵ���
			BACK_BOARD[Y][X] = 0; //���� �ٵ���
		}
	}
}
/////////////// Ÿ�̸� ���� //////////////
void STOP_TIMER() {
	BLACK_STONE_STATE.TIMER_30 = false; //Ÿ�̸� ��Ȱ��ȭ
	BLACK_STONE_STATE.TIMER_10 = false; //Ÿ�̸� ��Ȱ��ȭ
	WHITE_STONE_STATE.TIMER_30 = false; //Ÿ�̸� ��Ȱ��ȭ
	WHITE_STONE_STATE.TIMER_10 = false; //Ÿ�̸� ��Ȱ��ȭ
}

///////////// �÷��̾� �׸��� ////////////
void DRAW_PLAYER() {
	if (GAME_PLAY_S) { //������ ���� ���̶��
		GotoXY(PLAYER.X, PLAYER.Y);
		if (TOTAL_STONE % 2 == 0) { //�浹 �����϶�
			SetColor(6, 8); //��Ȳ��, ȸ��
			printf("��");

			GotoXY(0, 16);
			SetColor(0, 15); //0,15 �Ͼ��
			printf("���� : �浹 �����Դϴ�."); //�ϴܿ� ���� ǥ��
		}
		else if (TOTAL_STONE % 2 != 0) { //�鵹 �����϶�
			SetColor(6, 15); //��Ȳ��, �Ͼ��
			printf("��");

			GotoXY(0, 16);
			SetColor(0, 15); //�Ͼ��
			printf("���� : �鵹 �����Դϴ�."); //�ϴܿ� ���� ǥ��
		}
	}
}

//////////////// �� �׸��� ///////////////
void DRAW_STONE() {
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			if (BOARD[Y][X] == BLACK_STONE) { //�浹
				if (BLACK_STONE_STATE.Draw_Actice) {
					GotoXY(X * 2, Y); //��ǥ �̵�
					SetColor(6, 0); //��Ȳ��, ������
					printf("��");
				}
			}
			if (BOARD[Y][X] == WHITE_STONE) { //�鵹
				if (WHITE_STONE_STATE.Draw_Actice) {
					GotoXY(X * 2, Y); //��ǥ �̵�
					SetColor(6, 15); //��Ȳ��, �Ͼ��
					printf("��");
				}
			}
		}
	}
}

//////////// ���ַ� ���� ǥ�� ////////////
void Breaking_Rules() {
	GotoXY(0, 16); //��ǥ �̵�
	SetColor(0, 15); //�Ͼ��
	printf("���� : ���� ��Ģ�� ��߳��ϴ�.");
	Breaking_Rules_State = false; //���ַ� ���� ��Ȱ��ȭ
}

////////////// ���� ���� ǥ�� ////////////
void GAME_INFO() {
	if (GAME_PLAY_S) { //������ ���� ���̶��
		SetColor(0, 15); //�Ͼ��

		GotoXY(31, 3); //��ǥ �̵�
		printf("���ñ� : X:%d Y:%d", PLAYER.X / 2, PLAYER.Y);

		GotoXY(31, 5); //��ǥ �̵�
		printf("�浹 ��� : %d", BLACK_STONE_STATE.Life);

		GotoXY(31, 7); //��ǥ �̵�
		printf("�鵹 ��� : %d", WHITE_STONE_STATE.Life);

		GotoXY(31, 9); //��ǥ �̵�
		printf("��ü�� : %d", TOTAL_STONE);

		GotoXY(31, 11); //��ǥ �̵�
		printf("Ÿ�̸� : %d", TIMER_COUNT);
	}
	if (GAME_REPLAY_S) { //������ ����� ���¶��
		SetColor(0, 15); //�Ͼ��

		GotoXY(31, 9); //��ǥ �̵�
		printf("��ü�� : %d", TOTAL_STONE);

		GotoXY(0, 16); //��ǥ �̵�
		printf("���� : ����ȭ������ ������ Enter ������ �����Ϸ��� Esc�� �����ּ���.");
	}
}

///////////// ���� ���� ǥ�� /////////////
void GAME_START() {
	Clear(); //â �ʱ�ȭ
	SetColor(0, 15); //�Ͼ��

	GotoXY(11, 5); //��ǥ �̵�
	printf("���� ����");

	GotoXY(8, 10); //��ǥ �̵�
	printf("ENTER | ���ӽ���");

	GotoXY(8, 12); //��ǥ �̵�
	printf("ESC | ��������");

	GotoXY(4, 18);
	printf("������ ���� : 2022��12��16��");
}

///////////// ���� ���� ǥ�� /////////////
void GAME_PLAY() {
	Clear(); //â �ʱ�ȭ
	DRAW_BOARD(MAX_BOARD); //���� ǥ��
	DRAW_STONE(); //�� ǥ��
	DRAW_PLAYER(); //�÷��̾� ǥ��
	GAME_INFO(); //���� ���� ǥ��
	if (Breaking_Rules_State == true) { //���ַ� ������ �����Ǹ�
		Breaking_Rules(); //���ݰ�� ǥ��
	}
}

///////////// ���� ���� ǥ�� /////////////
void GAME_END() {
	if (BLACK_STONE_STATE.Win) { //�浹�� �̰�ٸ�
		Sleep(2000);
		Clear(); //â �ʱ�ȭ
		SetColor(0, 15); //�Ͼ��

		GotoXY(8, 5); //��ǥ �̵�
		printf("�浹�� �¸��߽��ϴ�.");

		GotoXY(8, 10); //��ǥ �̵�
		printf("V | �⹰����");

		GotoXY(8, 12); //��ǥ �̵�
		printf("ENTER | ó������");

		GotoXY(8, 14); //��ǥ �̵�
		printf("ESC | ��������");
	}
	if (WHITE_STONE_STATE.Win) { //�鵹�� �̰�ٸ�
		Sleep(2000);
		Clear(); //â �ʱ�ȭ
		SetColor(0, 15); //�Ͼ��

		GotoXY(8, 5); //��ǥ �̵�
		printf("�鵹�� �¸��߽��ϴ�.");

		GotoXY(8, 10); //��ǥ �̵�
		printf("V | �⹰����");

		GotoXY(8, 12); //��ǥ �̵�
		printf("ENTER | ó������");

		GotoXY(8, 14); //��ǥ �̵�
		printf("ESC | ��������");
	}
}

/////////// ���� ���÷��� ǥ�� ///////////
void GAME_REPLAY() {
	Clear(); //â �ʱ�ȭ
	DRAW_BOARD(MAX_BOARD); //���� ǥ��
	DRAW_STONE(); //�� ǥ��
	GAME_INFO(); //���� ���� ǥ��
}

///////////// ���� ���� ǥ�� /////////////
void GAME_SHUTDOWN() {
	Clear();
	SetColor(0, 15); //�Ͼ��

	GotoXY(8, 10); //��ǥ �̵�
	printf("������ �����մϴ�...");

	GotoXY(48, 18);
	printf(" ");
}

////////////// ȭ�� ������Ʈ//////////////
void UPDATE() {
	if (GAME_READY_S) {
		RESET_DATA(); //������ �ʱ�ȭ
		GAME_START(); //���� ���� ǥ��
	}

	if (GAME_PLAY_S) {
		GAME_PLAY(); //���� �÷��� ǥ��
	}

	if (GAME_END_S) {
		GAME_END(); //���� ���� ǥ��
	}

	if (GAME_REPLAY_S) {
		GAME_REPLAY(); //���� ���÷��� ǥ��
	}
}

/////////////// ���� ó���� //////////////
void GAME_END_Processing() {
	if (BLACK_END() != 0) { //0�� �ƴϸ�
		GAME_PLAY_S = false; //���� ���� ��Ȱ��ȭ
		GAME_END_S = true; //���� ���� Ȱ��ȭ
		BLACK_STONE_STATE.Win = true; //�¸� Ȱ��ȭ
		STOP_TIMER(); //��� Ÿ�̸� ����
	}
	if (WHITE_END() != 0) { //0�� �ƴϸ�
		GAME_PLAY_S = false; //���� ���� ��Ȱ��ȭ
		GAME_END_S = true; //���� ���� Ȱ��ȭ
		WHITE_STONE_STATE.Win = true; //�¸� Ȱ��ȭ
		STOP_TIMER(); //��� Ÿ�̸� ����
	}
}

unsigned _stdcall B_TIMER_SATRT_10(void* arg) { //�浹��
	for (int i = 0; i < 2; i++) { //3�� �ݺ� 
		TIMER_COUNT = 10; //Ÿ�̸� 10�ʷ� �ʱ�ȭ

		for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //10��
			if (BLACK_STONE_STATE.TIMER_30 == false) { //30�� Ÿ�̸Ӱ� ��Ȱ��ȭ���
				return 0; //������ ����
			}
			wait(1); //1�� ��ٸ���
			if (TIMER_COUNT == 9) { //9�϶� ȭ�� �ʱ�ȭ
				UPDATE(); //ȭ�� ������Ʈ
			}
			else {
				GAME_INFO(); //���� ������Ʈ
			}
		}
		BLACK_STONE_STATE.Life--; //���� �ϳ� ����
		if (BLACK_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //���� ���� ��Ȱ��ȭ
			GAME_END_S = true; //���� ���� Ȱ��ȭ
			WHITE_STONE_STATE.Win = true; //�¸� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
			return 0; //������ ����
		}
	}
	return 0; //������ ����
}

unsigned _stdcall B_TIMER_SATRT_30(void* arg) { //�浹��
	TIMER_COUNT = 30; //Ÿ�̸� 30�ʷ� �ʱ�ȭ

	for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //30��
		if (BLACK_STONE_STATE.TIMER_30 == false) { //30�� Ÿ�̸Ӱ� ��Ȱ��ȭ���
			return 0; //������ ����
		}
		wait(1); //1�� ��ٸ���
		if (TIMER_COUNT == 9) { //9�϶� ȭ�� �ʱ�ȭ
			UPDATE(); //ȭ�� ������Ʈ
		}
		else {
			GAME_INFO(); //���� ������Ʈ
		}
	}

	if (TIMER_COUNT == 0) { //Ÿ�̸Ӱ� 0�̶��
		BLACK_STONE_STATE.Life--; //���� �ϳ� ����
		if (BLACK_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //���� ���� ��Ȱ��ȭ
			GAME_END_S = true; //���� ���� Ȱ��ȭ
			WHITE_STONE_STATE.Win = true; //�¸� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
			return 0; //������ ����
		}
		if (!BLACK_STONE_STATE.TIMER_10) { //10�� Ÿ�̸Ӱ� ��Ȱ��ȭ���
			BLACK_STONE_STATE.TIMER_10 = true; //10�� Ÿ�̸� Ȱ��ȭ
			_beginthreadex(NULL, 0, B_TIMER_SATRT_10, 0, 0, NULL); //10�� Ÿ�̸� ������ Ȱ��ȭ
		}
	}
	return 0; //������ ����
}

unsigned _stdcall W_TIMER_SATRT_10(void* arg) { //�鵹��
	for (int i = 0; i < 2; i++) { //3�� �ݺ� 
		TIMER_COUNT = 10; //Ÿ�̸� 10�ʷ� �ʱ�ȭ

		for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //10��
			if (WHITE_STONE_STATE.TIMER_30 == false) { //30�� Ÿ�̸Ӱ� ��Ȱ��ȭ���
				return 0; //������ ����
			}
			wait(1); //1�� ��ٸ���
			if (TIMER_COUNT == 9) { //9�϶� ȭ�� �ʱ�ȭ
				UPDATE(); //ȭ�� ������Ʈ
			}
			else {
				GAME_INFO(); //���� ������Ʈ
			}
		}

		WHITE_STONE_STATE.Life--; //���� �ϳ� ����
		if (WHITE_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //���� ���� ��Ȱ��ȭ
			GAME_END_S = true; //���� ���� Ȱ��ȭ
			BLACK_STONE_STATE.Win = true; //�¸� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
			return 0; //������ ����
		}
	}
	return 0; //������ ����
}

unsigned _stdcall W_TIMER_SATRT_30(void* arg) { //�鵹��
	TIMER_COUNT = 30; //Ÿ�̸� 30�ʷ� �ʱ�ȭ

	for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //30��
		if (WHITE_STONE_STATE.TIMER_30 == false) { //30�� Ÿ�̸Ӱ� ��Ȱ��ȭ���
			return 0; //������ ����
		}
		wait(1); //1�� ��ٸ���
		if (TIMER_COUNT == 9) { //9�϶� ȭ�� �ʱ�ȭ
			UPDATE(); //ȭ�� ������Ʈ
		}
		else {
			GAME_INFO(); //���� ������Ʈ
		}
	}

	if (TIMER_COUNT == 0) { //Ÿ�̸Ӱ� 0�̶��
		WHITE_STONE_STATE.Life--; //���� �ϳ� ����
		if (WHITE_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //���� ���� ��Ȱ��ȭ
			GAME_END_S = true; //���� ���� Ȱ��ȭ
			BLACK_STONE_STATE.Win = true; //�¸� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
			return 0; //������ ����
		}
		if (!WHITE_STONE_STATE.TIMER_10) { //10�� Ÿ�̸Ӱ� ��Ȱ��ȭ���
			WHITE_STONE_STATE.TIMER_10 = true; //10�� Ÿ�̸� Ȱ��ȭ
			_beginthreadex(NULL, 0, W_TIMER_SATRT_10, 0, 0, NULL); //10�� Ÿ�̸� ������ Ȱ��ȭ
		}
	}
	return 0; //������ ����
}

///////////// Ÿ�̸� �̺�Ʈ //////////////
void TIMER_EVENT() {
	if (GAME_PLAY_S) { //������ ���� ���̶��
		if (TOTAL_STONE % 2 == 0) { //�浹 ���ʶ��
			if (!BLACK_STONE_STATE.TIMER_30) { //30�� Ÿ�̸Ӱ� ��Ȱ��ȭ ���¶��
				BLACK_STONE_STATE.TIMER_30 = true; //30�� Ÿ�̸� Ȱ��ȭ
				_beginthreadex(NULL, 0, B_TIMER_SATRT_30, 0, 0, NULL); //Ÿ�̸� ������ ����
			}
		}
		else if (TOTAL_STONE % 2 != 0) { //�鵹 ���ʶ��
			if (!WHITE_STONE_STATE.TIMER_30) { //30�� Ÿ�̸Ӱ� ��Ȱ��ȭ ���¶��
				WHITE_STONE_STATE.TIMER_30 = true; //30�� Ÿ�̸� Ȱ��ȭ
				_beginthreadex(NULL, 0, W_TIMER_SATRT_30, 0, 0, NULL); //Ÿ�̸� ������ ����
			}
		}
	}
}

///////// �����ǿ� �������� ���� /////////
void SAVE_BACK_BOARD() {
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			BACK_BOARD[Y][X] = BOARD[Y][X]; //������ == ������
		}
	}
}

////////////// Ű���� �̺�Ʈ /////////////
void ARROW_EVENT() {
	Sleep(100);
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //����
		PLAYER.X -= 2;
		if (PLAYER.X < 0) PLAYER.X = 0; //���� �ѱ� ����
		UPDATE(); //ȭ�� ������Ʈ
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //������
		PLAYER.X += 2;
		if (PLAYER.X > MAX_PLAYER_X) PLAYER.X = MAX_PLAYER_X; //���� �ѱ� ����
		UPDATE(); //ȭ�� ������Ʈ
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //����
		PLAYER.Y -= 1;
		if (PLAYER.Y < 0) PLAYER.Y = 0; //���� �ѱ� ����
		UPDATE(); //ȭ�� ������Ʈ
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //�Ʒ���
		PLAYER.Y += 1;
		if (PLAYER.Y > MAX_PLAYER_Y) PLAYER.Y = MAX_PLAYER_Y; //���� �ѱ� ����
		UPDATE(); //ȭ�� ������Ʈ
	}
}

////////////// Ű���� �̺�Ʈ /////////////
void INPUT_EVENT() {
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) { //����Ű
		if (GAME_READY_S) { //���� �غ� Ȱ��ȭ���
			GAME_READY_S = false; //���� �غ���� ��Ȱ��ȭ
			GAME_PLAY_S = true; //���� ����
			UPDATE(); //ȭ�� ������Ʈ
		}
		if (GAME_END_S) { //���� ���ᰡ Ȱ��ȭ���
			GAME_END_S = false; //���� �� ��Ȱ��ȭ
			GAME_READY_S = true; //���� �غ���� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
		}
		if (GAME_REPLAY_S) { //���� ���÷��̰� Ȱ��ȭ���
			GAME_REPLAY_S = false; //���� ���÷��� ��Ȱ��ȭ
			GAME_READY_S = true; //���� �غ���� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //ESCŰ
		if (GAME_READY_S || GAME_END_S || GAME_REPLAY_S) {
			GAME_SHUTDOWN(); //���� ���� ǥ��
			exit(0); //����
		}
	}

	if (GetAsyncKeyState(0x56) & 0x8000) { //VŰ
		if (GAME_END_S) { //���� ���ᰡ Ȱ��ȭ���
			GAME_END_S = false; //���� ���� ��Ȱ��ȭ
			GAME_REPLAY_S = true; //���� ���÷��� Ȱ��ȭ
			UPDATE(); //ȭ�� ������Ʈ
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { //�����̽���
		if (GAME_PLAY_S) {
			if (BLACK_STONE_STATE.Active == true && WHITE_STONE_STATE.Active == true) { //�浹, �鵹�� Ȱ��ȭ ���¶��
				if (BOARD[PLAYER.Y][PLAYER.X / 2] == NOT_STONE) { //���� �� �ڸ��� �ƹ��͵� ���ٸ�
					if (TOTAL_STONE % 2 == 0) { //�浹 ���ʶ��
						if (Renju_Rule(PLAYER.X / 2, PLAYER.Y)) { //���ַ꿡 ������ �Ǵ��� Ȯ��
							Breaking_Rules_State = true; //���ַ� ����
						}
						else {
							SAVE_BACK_BOARD(); //���� �ǿ� ������ ����
							BOARD[PLAYER.Y][PLAYER.X / 2] = BLACK_STONE; //�ٵ����� �浹�� ����
							BLACK_STONE_STATE.Total++; //�浹 ���� �ø�
							TOTAL_STONE += 1; //�� �� ���� �ø�
							BLACK_STONE_STATE.TIMER_30 = false; //Ÿ�̸� ��Ȱ��ȭ
							BLACK_STONE_STATE.TIMER_10 = false; //Ÿ�̸� ��Ȱ��ȭ
						}
					}
					else if (TOTAL_STONE % 2 != 0) { //�鵹 ���ʶ��
						SAVE_BACK_BOARD(); //���� �ǿ� ������ ����
						BOARD[PLAYER.Y][PLAYER.X / 2] = WHITE_STONE; //�ٵ����� �鵹�� ����
						WHITE_STONE_STATE.Total++; //�浹 ���� �ø�
						TOTAL_STONE += 1; //�� �� ���� �ø�
						WHITE_STONE_STATE.TIMER_30 = false; //Ÿ�̸� ��Ȱ��ȭ
						WHITE_STONE_STATE.TIMER_10 = false; //Ÿ�̸� ��Ȱ��ȭ
					}
					PRE_STONE_COUNT = 0; //������ ī��Ʈ ���
					GAME_END_Processing(); //���� ���� ����
					UPDATE(); //ȭ�� ������Ʈ
				}
			}
		}
	}

	if (GetAsyncKeyState(0x43) & 0x8000) { //CŰ
		if (PRE_STONE_COUNT == 0) {
			for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
				for (int X = 0; X <= MAX_BOARD_X; X++) {
					BOARD[Y][X] = BACK_BOARD[Y][X]; //���� �������� ���� �����ǿ� �����
				}
			}

			if (TOTAL_STONE != 0) { //ī��Ʈ�� 0�� �ƴ϶��
				TOTAL_STONE -= 1; //�� �������� 1�� ���� �������� ����
			}
			PRE_STONE_COUNT = 1; //������ ī��Ʈ
			UPDATE(); //ȭ�� ������Ʈ
		}
		else {
			SetColor(0, 15); //�Ͼ��
			GotoXY(0, 16); //��ǥ �̵�
			printf("���� : �����⸦ �̹� ����߽��ϴ�.");
		}
	}
}

////////////////// ���� //////////////////
int main() {
	system("mode con cols=50 lines=20"); //â ũ�� ���� (������11 22H2�� �ֽ� ���� �Ǵ� �ֽ� �͹̳ο����� â ���� �Ұ�)
	SetTitle("����"); //CMDâ ���� ����
	UPDATE(); //ȭ�� ������Ʈ
	while (1) {
		ARROW_EVENT(); //����Ű Ű���� �̺�Ʈ
		INPUT_EVENT(); //Ű���� �̺�Ʈ
		TIMER_EVENT(); //Ÿ�̸� �̺�Ʈ
		GAME_END_Processing(); //���� ���� ����
	}
}