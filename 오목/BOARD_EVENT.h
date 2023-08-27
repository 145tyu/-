#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BOARD_X 14 // ������ �ִ� X��
#define MAX_BOARD_Y 14 // ������ �ִ� Y��
#define MAX_BOARD 15 // ������ ũ�� 15X15
#define MAX_STONE 255 // �ִ� �� ����

#define NOT_STONE 0 //����
#define BLACK_STONE 1 //�浹
#define WHITE_STONE 2 //�鵹

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

int _3X3(int X, int Y) { //�鵹 ����ó�� ����
	int Count = 0;
	//��
	//��
	//  ����

	//���� ���� �������� �浹�̰� �鵹�� �ֺ��� ���ٸ�
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X - 1] == NOT_STONE) {
		if (BOARD[Y][X + 2] == BLACK_STONE && BOARD[Y][X + 3] == NOT_STONE) {
			Count += 1;
		}
	}
	// ���� ���� ������ �浹�̰� �鵹�� �ֺ��� ���ٸ�
	else {
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X + 1] == NOT_STONE) {
			if (BOARD[Y][X - 2] == BLACK_STONE && BOARD[Y][X - 3] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//���� ���� �Ʒ����� �浹�̰� �鵹�� �ֺ��� ���ٸ�
	if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y - 1][X] == NOT_STONE) {
		if (BOARD[Y + 2][X] == BLACK_STONE && BOARD[Y + 3][X] == NOT_STONE) {
			Count += 1;
		}
	}
	//���� ���� ������ �浹�̰� �鵹�� �ֺ��� ���ٸ�
	else {
		if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y + 1][X] == NOT_STONE) {
			if (BOARD[Y - 2][X] == BLACK_STONE && BOARD[Y - 3][X] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//���� ������ �밢�� �Ʒ����� �浹�̰� �鵹�� �ֺ��� ���ٸ�
	if (BOARD[Y + 1][X + 1] == BLACK_STONE && BOARD[Y - 1][X - 1] == NOT_STONE) {
		if (BOARD[Y + 2][X + 2] == BLACK_STONE && BOARD[Y + 3][X + 3] == NOT_STONE) {
			Count += 1;
		}
	}
	else {
		//���� ������ �밢�� ������ �浹�̰� �鵹�� �ֺ��� ���ٸ�
		if (BOARD[Y - 1][X + 1] == BLACK_STONE && BOARD[Y + 1][X - 1] == NOT_STONE) {
			if (BOARD[Y - 2][X + 2] == BLACK_STONE && BOARD[Y - 3][X + 3] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//���� ���� �밢�� �Ʒ����� �浹�̰� �鵹�� �ֺ��� ���ٸ�
	if (BOARD[Y + 1][X - 1] == BLACK_STONE && BOARD[Y - 1][X + 1] == NOT_STONE) {
		if (BOARD[Y + 2][X - 2] == BLACK_STONE && BOARD[Y + 3][X - 3] == NOT_STONE) {
			Count += 1;
		}
	}
	else {
		//���� ���� �밢�� ������ �浹�̰� �鵹�� �ֺ��� ���ٸ�
		if (BOARD[Y - 1][X - 1] == BLACK_STONE && BOARD[Y + 1][X + 1] == NOT_STONE) {
			if (BOARD[Y - 2][X - 2] == BLACK_STONE && BOARD[Y - 3][X - 3] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	//ī��Ʈ�� 2�̻��̶�� true�� ��ȯ
	if (Count >= 2) return true;
	//�ƴ϶�� false�� ��ȯ
	else return false;
}

int _3X2(int X, int Y) { // �鵹 ����ó�� �Ϸ�
	int Count = 0;
	//     X
	//   �� ��
	//
	//��       ��

	//���� ������ �밢�� �Ʒ����� �浹�̰� ���̻��� �鵹�� ���ٸ�
	if (BOARD[Y + 1][X + 1] == BLACK_STONE && BOARD[Y - 1][X - 1] == NOT_STONE && BOARD[Y + 2][X + 2] == NOT_STONE && BOARD[Y + 4][X + 4] == NOT_STONE) {
		if (BOARD[Y + 3][X + 3] == BLACK_STONE) {
			Count += 1;
		}
	}
	//���� ������ �밢�� ������ �浹�̰� ���̻��� �鵹�� ���ٸ�
	if (BOARD[Y - 1][X + 1] == BLACK_STONE && BOARD[Y + 1][X - 1] == NOT_STONE && BOARD[Y - 2][X + 2] == NOT_STONE && BOARD[Y - 4][X + 4] == NOT_STONE) {
		if (BOARD[Y - 3][X + 3] == BLACK_STONE) {
			Count += 1;
		}
	}
	//���� ���� �밢�� �Ʒ����� �浹�̰� ���̻��� �鵹�� ���ٸ�
	if (BOARD[Y + 1][X - 1] == BLACK_STONE && BOARD[Y - 1][X + 1] == NOT_STONE && BOARD[Y + 2][X - 2] == NOT_STONE && BOARD[Y + 4][X - 4] == NOT_STONE) {
		if (BOARD[Y + 3][X - 3] == BLACK_STONE) {
			Count += 1;
		}
	}
	//���� ���� �밢�� ������ �浹�� ���̻��� �鵹�� ���ٸ�
	if (BOARD[Y - 1][X - 1] == BLACK_STONE && BOARD[Y + 1][X + 1] == NOT_STONE && BOARD[Y - 2][X - 2] == NOT_STONE && BOARD[Y - 4][X - 4] == NOT_STONE) {
		if (BOARD[Y - 3][X - 3] == BLACK_STONE) {
				Count += 1;
		}
	}
	//ī��Ʈ�� 2�̻��̶�� true�� ��ȯ
	if (Count >= 2) return true;
	//�ƴ϶�� false�� ��ȯ
	else return false;
}

int _3Xplus(int X, int Y) { //�鵹 ����ó�� �Ϸ�
	int Count = 0;
	//		��
	//    ��X��
	//		��

	// ���� �������� �浹�̰� �� ������ �鵹�� �ƴ϶��
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X + 2] == NOT_STONE) {
		// ���� ������ �浹�̰� �� ������ �鵹�� �ƴ϶��
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X - 2] == NOT_STONE) {
			// ���� ������ �浹�̰� �� ������ �鵹�� �ƴ϶��
			if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y - 2][X] == NOT_STONE) {
				// ���� �Ʒ����� �浹�̰� �� ������ �鵹�� �ƴ϶��
				if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y + 2][X] == NOT_STONE) {
					Count += 1;
				}
			}
		}
	}
	//ī��Ʈ�� 1�̻��̶�� true�� ��ȯ
	if (Count >= 1) return true;
	//�ƴ϶�� false�� ��ȯ
	else return false;
}

int _3Xplus_(int X, int Y) { //�鵹 ����ó�� �Ϸ�
	int Count = 0;
	//	   ��
	// ��  X��
	//     ��

	//���� ���� �������� �浹�̰� �鵹�� ���ٸ�
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
		//	  ��
		//  ��X  ��
		//    ��
		
		//���� ���� ������ �浹�̰� �鵹�� ���ٸ�
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

	//	   ��
	//
	//   ��X��
	//	   ��

	//���� ���� �Ʒ����� �浹�̰� �鵹�� ���ٸ�
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
		//	  ��
		//  ��X��
		//    
		//    ��

		//���� ���� ������ �浹�̰� �鵹�� ���ٸ�
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
	//ī��Ʈ�� 1�̻��̶�� true�� ��ȯ
	if (Count >= 1) return true;
	//�ƴ϶�� false�� ��ȯ
	else return false;
}

int _4X4(int X, int Y) {
	int Count = 0;

	//���� ���� �������� �浹�̶��
	if (BOARD[Y][X + 1] == BLACK_STONE && BOARD[Y][X - 1] == NOT_STONE) {
		if (BOARD[Y][X + 2] == BLACK_STONE) {
			if (BOARD[Y][X + 3] == BLACK_STONE && BOARD[Y][X + 4] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	else {
		//���� ���� ������ �浹�̶��
		if (BOARD[Y][X - 1] == BLACK_STONE && BOARD[Y][X + 1] == NOT_STONE) {
			if (BOARD[Y][X - 2] == BLACK_STONE) {
				if (BOARD[Y][X - 3] == BLACK_STONE && BOARD[Y][X - 4] == NOT_STONE) {
					Count += 1;
				}
			}
		}
	}
	//���� ���� �Ʒ����� �浹�̶��
	if (BOARD[Y + 1][X] == BLACK_STONE && BOARD[Y - 1][X] == NOT_STONE) {
		if (BOARD[Y + 2][X] == BLACK_STONE) {
			if (BOARD[Y + 3][X] == BLACK_STONE && BOARD[Y][X + 4] == NOT_STONE) {
				Count += 1;
			}
		}
	}
	else {
		//���� ���� ������ �浹�̶��
		if (BOARD[Y - 1][X] == BLACK_STONE && BOARD[Y + 1][X] == NOT_STONE) {
			if (BOARD[Y - 2][X] == BLACK_STONE) {
				if (BOARD[Y - 3][X] == BLACK_STONE && BOARD[Y][X - 4] == NOT_STONE) {
					Count += 1;
				}
			}
		}
	}

	if (BOARD[Y + 1][X - 1] == BLACK_STONE) { //���� ������ �밢�� �Ʒ����� �浹�̶��
		if (BOARD[Y + 2][X - 2] == BLACK_STONE) {
			if (BOARD[Y + 3][X - 3] == BLACK_STONE) {
				Count += 1;
			}
		}
	}
	else {
		if (BOARD[Y - 1][X + 1] == BLACK_STONE) { //���� ������ �밢�� ������ �浹�̶��
			if (BOARD[Y - 2][X + 2] == BLACK_STONE) {
				if (BOARD[Y - 3][X + 3] == BLACK_STONE) {
					Count += 1;
				}
			}
		}
	}

	if (BOARD[Y + 1][X + 1] == BLACK_STONE) { //���� ���� �밢�� �Ʒ����� �浹�̶��
		if (BOARD[Y + 2][X + 2] == BLACK_STONE) {
			if (BOARD[Y + 3][X + 3] == BLACK_STONE) {
				Count += 1;
			}
		}
	}
	else {
		if (BOARD[Y - 1][X - 1] == BLACK_STONE) { //���� ���� �밢�� ������ �浹�̶��
			if (BOARD[Y - 2][X - 2] == BLACK_STONE) {
				if (BOARD[Y - 3][X - 3] == BLACK_STONE) {
					Count += 1;
				}
			}
		}
	}

	//ī��Ʈ�� 2�̻��̶�� true�� ��ȯ
	if (Count >= 2) return true;
	//�ƴ϶�� false�� ��ȯ
	else return false;
}

int _4X2(int X, int Y) { // �� ��X�� ��
	int Count = 0; //�鵹 ����ó�� �Ϸ�

	if (BOARD[Y][X + 1] == BLACK_STONE) { //���� ���� �������� �浹�̶��
		if (BOARD[Y][X + 2] == NOT_STONE && BOARD[Y][X + 3] == BLACK_STONE) {
			Count += 1; //ī��Ʈ
		}
	}
	if (BOARD[Y][X - 1] == 1) { //���� ���� ������ �浹�̶��
		if (BOARD[Y][X - 2] == NOT_STONE && BOARD[Y][X - 3] == BLACK_STONE) {
			Count += 1; //ī��Ʈ
		}
	}

	if (BOARD[Y + 1][X] == 1) { //���� ���� �Ʒ����� �浹�̶��
		if (BOARD[Y + 2][X] == NOT_STONE && BOARD[Y + 3][X] == BLACK_STONE) {
			Count += 1; //ī��Ʈ
		}
	}
	if (BOARD[Y - 1][X] == 1) { //���� ���� ������ �浹�̶��
		if (BOARD[Y - 2][X] == NOT_STONE && BOARD[Y - 3][X] == BLACK_STONE) {
			Count += 1; //ī��Ʈ
		}
	}

	//ī��Ʈ�� 2�̻��̶�� true�� ��ȯ
	if (Count >= 2) return true;
	//�ƴ϶�� false�� ��ȯ
	else return false;
}

int Renju_Rule(int X, int Y) { //���� ����Ʈ : http://omok.mgame.com/help/rule.htm
	// A. 3,3 �ݼ� �Ϸ�
	if (_3X3(X, Y) || _3X2(X, Y) || _3Xplus(X, Y) || _3Xplus_(X, Y)) {
		return true; //true�� ��ȯ
	}
	// B. 4,4 �ݼ� �Ϸ�
	if (_4X4(X, Y) || _4X2(X, Y)) {
		return true; //true�� ��ȯ
	}
	// C. 6,6 �ݼ� ����
	// D. 3,3,4 �ݼ� �Ϸ�
	// E. 3,4,4 �ݼ� �Ϸ�
	else {
		return false; //false�� ��ȯ
	}
}

int BLACK_END() {
	int TEMP = 0, COUNT = 0;
	//���ο� 5���� �����������
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y][X + i] == BLACK_STONE) { //�ش� �ڸ��� �浹�̸�
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
	//���ο� 5���� �����������
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X] == BLACK_STONE) { //�ش� �ڸ��� �浹�̶��
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
	//���� �밢���� 5���� �����������
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X - i] == BLACK_STONE) { //�ش� �ڸ��� �浹�̶��
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
	//������ �밢���� 5���� �����������
	for (int Y = 0; Y <= MAX_BOARD_Y; Y++) {
		for (int X = 0; X <= MAX_BOARD_X; X++) {
			for (int i = 0; i <= 4; i++) {
				if (BOARD[Y + i][X + i] == BLACK_STONE) { //�ش� �ڸ��� �浹�̶��
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
	//���ο� 5���� �����������
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
	//���ο� 5���� �����������
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
	//���� �밢���� 5���� �����������
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
	//������ �밢���� 5���� �����������
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