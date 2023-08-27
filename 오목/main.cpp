#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <process.h>
#include "Console.h"
#include "BOARD_DRAW.h"
#include "BOARD_EVENT.h"

#define MAX_BOARD 15 //보드판 크기 15X15
#define MAX_BOARD_X 14 //보드판 최대 X값
#define MAX_BOARD_Y 14 //보드판 최대 Y값
#define MAX_PLAYER_X 28 //플레이어 X 최대
#define MAX_PLAYER_Y 14 //플레이어 Y 최대

#define NOT_STONE 0 //없음
#define BLACK_STONE 1 //흑돌
#define WHITE_STONE 2 //백돌

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

////////////// 데이터 초기화 /////////////
void RESET_DATA() {
	///////////// 플레이어 초기화 /////////////
	PLAYER.X = 14; //플레이어 중앙으로 위치값 초기화
	PLAYER.Y = 7; //플레이어 중앙으로 위치값 초기화
	PLAYER.Active = true; //플레이어 활성화

	/////////////// 흑돌 초기화 //////////////
	BLACK_STONE_STATE.Total = 0; //총 개수
	BLACK_STONE_STATE.Life = 3; //목숨
	BLACK_STONE_STATE.Win = false; //이겼는지
	BLACK_STONE_STATE.Active = true; //활성화
	BLACK_STONE_STATE.Draw_Actice = true; //표시 활성화
	BLACK_STONE_STATE.TIMER_30 = false; //타이머 비활성화
	BLACK_STONE_STATE.TIMER_10 = false; //타이머 비활성화

	/////////////// 백돌 초기화 //////////////
	WHITE_STONE_STATE.Total = 0; //총 개수
	WHITE_STONE_STATE.Life = 3; //목숨
	WHITE_STONE_STATE.Win = false; //이겼는지
	WHITE_STONE_STATE.Active = true; //활성화
	WHITE_STONE_STATE.Draw_Actice = true; //표시 활성화
	WHITE_STONE_STATE.TIMER_30 = false; //타이머 비활성화
	WHITE_STONE_STATE.TIMER_10 = false; //타이머 비활성화

	TOTAL_STONE = 0; //전체돌 초기화
	TIMER_COUNT = 30; //타이머 초기화
	PRE_STONE_COUNT = 0; //무르기 초기화
	Breaking_Rules_State = false; //렌주룰 상태 초기화

	////////////// 바둑판 초기화 /////////////
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			BOARD[Y][X] = 0; //메인 바둑판
			BACK_BOARD[Y][X] = 0; //이전 바둑판
		}
	}
}
/////////////// 타이머 종료 //////////////
void STOP_TIMER() {
	BLACK_STONE_STATE.TIMER_30 = false; //타이머 비활성화
	BLACK_STONE_STATE.TIMER_10 = false; //타이머 비활성화
	WHITE_STONE_STATE.TIMER_30 = false; //타이머 비활성화
	WHITE_STONE_STATE.TIMER_10 = false; //타이머 비활성화
}

///////////// 플레이어 그리기 ////////////
void DRAW_PLAYER() {
	if (GAME_PLAY_S) { //게임이 진행 중이라면
		GotoXY(PLAYER.X, PLAYER.Y);
		if (TOTAL_STONE % 2 == 0) { //흑돌 차례일때
			SetColor(6, 8); //주황색, 회색
			printf("◎");

			GotoXY(0, 16);
			SetColor(0, 15); //0,15 하얀색
			printf("도움말 : 흑돌 차례입니다."); //하단에 도움말 표시
		}
		else if (TOTAL_STONE % 2 != 0) { //백돌 차례일때
			SetColor(6, 15); //주황색, 하얀색
			printf("◎");

			GotoXY(0, 16);
			SetColor(0, 15); //하얀색
			printf("도움말 : 백돌 차례입니다."); //하단에 도움말 표시
		}
	}
}

//////////////// 돌 그리기 ///////////////
void DRAW_STONE() {
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			if (BOARD[Y][X] == BLACK_STONE) { //흑돌
				if (BLACK_STONE_STATE.Draw_Actice) {
					GotoXY(X * 2, Y); //좌표 이동
					SetColor(6, 0); //주황색, 검은색
					printf("●");
				}
			}
			if (BOARD[Y][X] == WHITE_STONE) { //백돌
				if (WHITE_STONE_STATE.Draw_Actice) {
					GotoXY(X * 2, Y); //좌표 이동
					SetColor(6, 15); //주황색, 하얀색
					printf("●");
				}
			}
		}
	}
}

//////////// 렌주룰 위반 표시 ////////////
void Breaking_Rules() {
	GotoXY(0, 16); //좌표 이동
	SetColor(0, 15); //하얀색
	printf("도움말 : 렌주 규칙에 어긋납니다.");
	Breaking_Rules_State = false; //렌주룰 위반 비활성화
}

////////////// 게임 정보 표시 ////////////
void GAME_INFO() {
	if (GAME_PLAY_S) { //게임이 진행 중이라면
		SetColor(0, 15); //하얀색

		GotoXY(31, 3); //좌표 이동
		printf("선택기 : X:%d Y:%d", PLAYER.X / 2, PLAYER.Y);

		GotoXY(31, 5); //좌표 이동
		printf("흑돌 목숨 : %d", BLACK_STONE_STATE.Life);

		GotoXY(31, 7); //좌표 이동
		printf("백돌 목숨 : %d", WHITE_STONE_STATE.Life);

		GotoXY(31, 9); //좌표 이동
		printf("전체돌 : %d", TOTAL_STONE);

		GotoXY(31, 11); //좌표 이동
		printf("타이머 : %d", TIMER_COUNT);
	}
	if (GAME_REPLAY_S) { //게임이 종료된 상태라면
		SetColor(0, 15); //하얀색

		GotoXY(31, 9); //좌표 이동
		printf("전체돌 : %d", TOTAL_STONE);

		GotoXY(0, 16); //좌표 이동
		printf("도움말 : 메인화면으로 가려면 Enter 게임을 종료하려면 Esc를 눌러주세요.");
	}
}

///////////// 게임 시작 표시 /////////////
void GAME_START() {
	Clear(); //창 초기화
	SetColor(0, 15); //하얀색

	GotoXY(11, 5); //좌표 이동
	printf("오목 게임");

	GotoXY(8, 10); //좌표 이동
	printf("ENTER | 게임시작");

	GotoXY(8, 12); //좌표 이동
	printf("ESC | 게임종료");

	GotoXY(4, 18);
	printf("마지막 빌드 : 2022년12월16일");
}

///////////// 게임 진행 표시 /////////////
void GAME_PLAY() {
	Clear(); //창 초기화
	DRAW_BOARD(MAX_BOARD); //보드 표시
	DRAW_STONE(); //돌 표시
	DRAW_PLAYER(); //플레이어 표시
	GAME_INFO(); //게임 상태 표시
	if (Breaking_Rules_State == true) { //렌주룰 위반이 감지되면
		Breaking_Rules(); //위반경고 표시
	}
}

///////////// 게임 종료 표시 /////////////
void GAME_END() {
	if (BLACK_STONE_STATE.Win) { //흑돌이 이겼다면
		Sleep(2000);
		Clear(); //창 초기화
		SetColor(0, 15); //하얀색

		GotoXY(8, 5); //좌표 이동
		printf("흑돌이 승리했습니다.");

		GotoXY(8, 10); //좌표 이동
		printf("V | 기물보기");

		GotoXY(8, 12); //좌표 이동
		printf("ENTER | 처음으로");

		GotoXY(8, 14); //좌표 이동
		printf("ESC | 게임종료");
	}
	if (WHITE_STONE_STATE.Win) { //백돌이 이겼다면
		Sleep(2000);
		Clear(); //창 초기화
		SetColor(0, 15); //하얀색

		GotoXY(8, 5); //좌표 이동
		printf("백돌이 승리했습니다.");

		GotoXY(8, 10); //좌표 이동
		printf("V | 기물보기");

		GotoXY(8, 12); //좌표 이동
		printf("ENTER | 처음으로");

		GotoXY(8, 14); //좌표 이동
		printf("ESC | 게임종료");
	}
}

/////////// 게임 리플레이 표시 ///////////
void GAME_REPLAY() {
	Clear(); //창 초기화
	DRAW_BOARD(MAX_BOARD); //보드 표시
	DRAW_STONE(); //돌 표시
	GAME_INFO(); //게임 상태 표시
}

///////////// 게임 끄기 표시 /////////////
void GAME_SHUTDOWN() {
	Clear();
	SetColor(0, 15); //하얀색

	GotoXY(8, 10); //좌표 이동
	printf("게임을 종료합니다...");

	GotoXY(48, 18);
	printf(" ");
}

////////////// 화면 업데이트//////////////
void UPDATE() {
	if (GAME_READY_S) {
		RESET_DATA(); //데이터 초기화
		GAME_START(); //게임 시작 표시
	}

	if (GAME_PLAY_S) {
		GAME_PLAY(); //게임 플레이 표시
	}

	if (GAME_END_S) {
		GAME_END(); //게임 종료 표시
	}

	if (GAME_REPLAY_S) {
		GAME_REPLAY(); //게임 리플레이 표시
	}
}

/////////////// 승패 처리기 //////////////
void GAME_END_Processing() {
	if (BLACK_END() != 0) { //0이 아니면
		GAME_PLAY_S = false; //게임 진행 비활성화
		GAME_END_S = true; //게임 종료 활성화
		BLACK_STONE_STATE.Win = true; //승리 활성화
		STOP_TIMER(); //모든 타이머 중지
	}
	if (WHITE_END() != 0) { //0이 아니면
		GAME_PLAY_S = false; //게임 진행 비활성화
		GAME_END_S = true; //게임 종료 활성화
		WHITE_STONE_STATE.Win = true; //승리 활성화
		STOP_TIMER(); //모든 타이머 중지
	}
}

unsigned _stdcall B_TIMER_SATRT_10(void* arg) { //흑돌용
	for (int i = 0; i < 2; i++) { //3번 반복 
		TIMER_COUNT = 10; //타이머 10초로 초기화

		for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //10초
			if (BLACK_STONE_STATE.TIMER_30 == false) { //30초 타이머가 비활성화라면
				return 0; //쓰레드 종료
			}
			wait(1); //1초 기다리기
			if (TIMER_COUNT == 9) { //9일때 화면 초기화
				UPDATE(); //화면 업데이트
			}
			else {
				GAME_INFO(); //정보 업데이트
			}
		}
		BLACK_STONE_STATE.Life--; //생명 하나 삭제
		if (BLACK_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //게임 진행 비활성화
			GAME_END_S = true; //게임 종료 활성화
			WHITE_STONE_STATE.Win = true; //승리 활성화
			UPDATE(); //화면 업데이트
			return 0; //쓰레드 종료
		}
	}
	return 0; //쓰레드 종료
}

unsigned _stdcall B_TIMER_SATRT_30(void* arg) { //흑돌용
	TIMER_COUNT = 30; //타이머 30초로 초기화

	for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //30초
		if (BLACK_STONE_STATE.TIMER_30 == false) { //30초 타이머가 비활성화라면
			return 0; //쓰레드 종료
		}
		wait(1); //1초 기다리기
		if (TIMER_COUNT == 9) { //9일때 화면 초기화
			UPDATE(); //화면 업데이트
		}
		else {
			GAME_INFO(); //정보 업데이트
		}
	}

	if (TIMER_COUNT == 0) { //타이머가 0이라면
		BLACK_STONE_STATE.Life--; //생명 하나 삭제
		if (BLACK_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //게임 진행 비활성화
			GAME_END_S = true; //게임 종료 활성화
			WHITE_STONE_STATE.Win = true; //승리 활성화
			UPDATE(); //화면 업데이트
			return 0; //쓰레드 종료
		}
		if (!BLACK_STONE_STATE.TIMER_10) { //10초 타이머가 비활성화라면
			BLACK_STONE_STATE.TIMER_10 = true; //10초 타이머 활성화
			_beginthreadex(NULL, 0, B_TIMER_SATRT_10, 0, 0, NULL); //10초 타이머 쓰레드 활성화
		}
	}
	return 0; //쓰레드 종료
}

unsigned _stdcall W_TIMER_SATRT_10(void* arg) { //백돌용
	for (int i = 0; i < 2; i++) { //3번 반복 
		TIMER_COUNT = 10; //타이머 10초로 초기화

		for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //10초
			if (WHITE_STONE_STATE.TIMER_30 == false) { //30초 타이머가 비활성화라면
				return 0; //쓰레드 종료
			}
			wait(1); //1초 기다리기
			if (TIMER_COUNT == 9) { //9일때 화면 초기화
				UPDATE(); //화면 업데이트
			}
			else {
				GAME_INFO(); //정보 업데이트
			}
		}

		WHITE_STONE_STATE.Life--; //생명 하나 삭제
		if (WHITE_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //게임 진행 비활성화
			GAME_END_S = true; //게임 종료 활성화
			BLACK_STONE_STATE.Win = true; //승리 활성화
			UPDATE(); //화면 업데이트
			return 0; //쓰레드 종료
		}
	}
	return 0; //쓰레드 종료
}

unsigned _stdcall W_TIMER_SATRT_30(void* arg) { //백돌용
	TIMER_COUNT = 30; //타이머 30초로 초기화

	for (TIMER_COUNT; TIMER_COUNT > 0; TIMER_COUNT--) { //30초
		if (WHITE_STONE_STATE.TIMER_30 == false) { //30초 타이머가 비활성화라면
			return 0; //쓰레드 종료
		}
		wait(1); //1초 기다리기
		if (TIMER_COUNT == 9) { //9일때 화면 초기화
			UPDATE(); //화면 업데이트
		}
		else {
			GAME_INFO(); //정보 업데이트
		}
	}

	if (TIMER_COUNT == 0) { //타이머가 0이라면
		WHITE_STONE_STATE.Life--; //생명 하나 삭제
		if (WHITE_STONE_STATE.Life == 0) {
			GAME_PLAY_S = false; //게임 진행 비활성화
			GAME_END_S = true; //게임 종료 활성화
			BLACK_STONE_STATE.Win = true; //승리 활성화
			UPDATE(); //화면 업데이트
			return 0; //쓰레드 종료
		}
		if (!WHITE_STONE_STATE.TIMER_10) { //10초 타이머가 비활성화라면
			WHITE_STONE_STATE.TIMER_10 = true; //10초 타이머 활성화
			_beginthreadex(NULL, 0, W_TIMER_SATRT_10, 0, 0, NULL); //10초 타이머 쓰레드 활성화
		}
	}
	return 0; //쓰레드 종료
}

///////////// 타이머 이벤트 //////////////
void TIMER_EVENT() {
	if (GAME_PLAY_S) { //게임이 진행 중이라면
		if (TOTAL_STONE % 2 == 0) { //흑돌 차례라면
			if (!BLACK_STONE_STATE.TIMER_30) { //30초 타이머가 비활성화 상태라면
				BLACK_STONE_STATE.TIMER_30 = true; //30초 타이머 활성화
				_beginthreadex(NULL, 0, B_TIMER_SATRT_30, 0, 0, NULL); //타이머 쓰레드 시작
			}
		}
		else if (TOTAL_STONE % 2 != 0) { //백돌 차례라면
			if (!WHITE_STONE_STATE.TIMER_30) { //30초 타이머가 비활성화 상태라면
				WHITE_STONE_STATE.TIMER_30 = true; //30초 타이머 활성화
				_beginthreadex(NULL, 0, W_TIMER_SATRT_30, 0, 0, NULL); //타이머 쓰레드 시작
			}
		}
	}
}

///////// 이전판에 현재판을 저장 /////////
void SAVE_BACK_BOARD() {
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			BACK_BOARD[Y][X] = BOARD[Y][X]; //이전판 == 현재판
		}
	}
}

////////////// 키보드 이벤트 /////////////
void ARROW_EVENT() {
	Sleep(100);
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		PLAYER.X -= 2;
		if (PLAYER.X < 0) PLAYER.X = 0; //보드 넘기 금지
		UPDATE(); //화면 업데이트
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
		PLAYER.X += 2;
		if (PLAYER.X > MAX_PLAYER_X) PLAYER.X = MAX_PLAYER_X; //보드 넘기 금지
		UPDATE(); //화면 업데이트
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위쪽
		PLAYER.Y -= 1;
		if (PLAYER.Y < 0) PLAYER.Y = 0; //보드 넘기 금지
		UPDATE(); //화면 업데이트
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래쪽
		PLAYER.Y += 1;
		if (PLAYER.Y > MAX_PLAYER_Y) PLAYER.Y = MAX_PLAYER_Y; //보드 넘기 금지
		UPDATE(); //화면 업데이트
	}
}

////////////// 키보드 이벤트 /////////////
void INPUT_EVENT() {
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) { //엔터키
		if (GAME_READY_S) { //게임 준비가 활성화라면
			GAME_READY_S = false; //게임 준비상태 비활성화
			GAME_PLAY_S = true; //게임 시작
			UPDATE(); //화면 업데이트
		}
		if (GAME_END_S) { //게임 종료가 활성화라면
			GAME_END_S = false; //게임 끝 비활성화
			GAME_READY_S = true; //게임 준비상태 활성화
			UPDATE(); //화면 업데이트
		}
		if (GAME_REPLAY_S) { //게임 리플레이가 활성화라면
			GAME_REPLAY_S = false; //게임 리플레이 비활성화
			GAME_READY_S = true; //게임 준비상태 활성화
			UPDATE(); //화면 업데이트
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //ESC키
		if (GAME_READY_S || GAME_END_S || GAME_REPLAY_S) {
			GAME_SHUTDOWN(); //게임 끄기 표시
			exit(0); //종료
		}
	}

	if (GetAsyncKeyState(0x56) & 0x8000) { //V키
		if (GAME_END_S) { //게임 종료가 활성화라면
			GAME_END_S = false; //게임 종료 비활성화
			GAME_REPLAY_S = true; //게임 리플레이 활성화
			UPDATE(); //화면 업데이트
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { //스페이스바
		if (GAME_PLAY_S) {
			if (BLACK_STONE_STATE.Active == true && WHITE_STONE_STATE.Active == true) { //흑돌, 백돌이 활성화 상태라면
				if (BOARD[PLAYER.Y][PLAYER.X / 2] == NOT_STONE) { //들어온 값 자리에 아무것도 없다면
					if (TOTAL_STONE % 2 == 0) { //흑돌 차례라면
						if (Renju_Rule(PLAYER.X / 2, PLAYER.Y)) { //렌주룰에 위반이 되는지 확인
							Breaking_Rules_State = true; //렌주룰 위반
						}
						else {
							SAVE_BACK_BOARD(); //이전 판에 현재판 저장
							BOARD[PLAYER.Y][PLAYER.X / 2] = BLACK_STONE; //바둑판을 흑돌로 변경
							BLACK_STONE_STATE.Total++; //흑돌 개수 올림
							TOTAL_STONE += 1; //총 돌 개수 올림
							BLACK_STONE_STATE.TIMER_30 = false; //타이머 비활성화
							BLACK_STONE_STATE.TIMER_10 = false; //타이머 비활성화
						}
					}
					else if (TOTAL_STONE % 2 != 0) { //백돌 차례라면
						SAVE_BACK_BOARD(); //이전 판에 현재판 저장
						BOARD[PLAYER.Y][PLAYER.X / 2] = WHITE_STONE; //바둑판을 백돌로 변경
						WHITE_STONE_STATE.Total++; //흑돌 개수 올림
						TOTAL_STONE += 1; //총 돌 개수 올림
						WHITE_STONE_STATE.TIMER_30 = false; //타이머 비활성화
						WHITE_STONE_STATE.TIMER_10 = false; //타이머 비활성화
					}
					PRE_STONE_COUNT = 0; //무르기 카운트 취소
					GAME_END_Processing(); //게임 종료 결정
					UPDATE(); //화면 업데이트
				}
			}
		}
	}

	if (GetAsyncKeyState(0x43) & 0x8000) { //C키
		if (PRE_STONE_COUNT == 0) {
			for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
				for (int X = 0; X <= MAX_BOARD_X; X++) {
					BOARD[Y][X] = BACK_BOARD[Y][X]; //이전 보드판을 현재 보드판에 덮어쓰기
				}
			}

			if (TOTAL_STONE != 0) { //카운트가 0이 아니라면
				TOTAL_STONE -= 1; //총 개수에서 1을 빼서 이전돌로 변경
			}
			PRE_STONE_COUNT = 1; //무르기 카운트
			UPDATE(); //화면 업데이트
		}
		else {
			SetColor(0, 15); //하얀색
			GotoXY(0, 16); //좌표 이동
			printf("도움말 : 무르기를 이미 사용했습니다.");
		}
	}
}

////////////////// 메인 //////////////////
int main() {
	system("mode con cols=50 lines=20"); //창 크기 조절 (윈도우11 22H2의 최신 빌드 또는 최신 터미널에서는 창 조절 불가)
	SetTitle("오목"); //CMD창 제목 변경
	UPDATE(); //화면 업데이트
	while (1) {
		ARROW_EVENT(); //방향키 키보드 이벤트
		INPUT_EVENT(); //키보드 이벤트
		TIMER_EVENT(); //타이머 이벤트
		GAME_END_Processing(); //게임 종료 결정
	}
}