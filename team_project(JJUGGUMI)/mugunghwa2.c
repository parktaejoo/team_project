#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int hwa_map_x = 14, hwa_map_y = 40;
int young = 3;
int hwa_switch = 0;
int btn[10] = { 1 };

void goal(int, int, int);
void mugunghwa(void);

//�� ��ġ ����
void hwamap_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

//�÷��̾� ��ġ ����
void mugunghwa_init(void) {
	hwamap_init(hwa_map_x, hwa_map_y);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		x = (hwa_map_x / 2) - (n_player / 2) + i;
		y = hwa_map_y - 2;

		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}

//�÷��̾� ������
void move_random_hwa(int player_hwa, int dir) {
	int p = player_hwa;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�
	int rand_num;

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

	do {
		rand_num = randint(0, 10);
		switch (rand_num) {
		case 0:
			nx = px[p];
			ny = py[p] - 1;
			if (hwa_switch == 1) {
				btn[p] = 1;
			}
			goal(nx, ny, p);
			break;
		case 1:
			nx = px[p] - 1;
			ny = py[p];
			if (hwa_switch == 1) {
				btn[p] = 1;
			}
			goal(nx, ny, p);
			break;
		case 2:
			nx = px[p] + 1;
			ny = py[p];
			if (hwa_switch == 1) {
				btn[p] = 1;
			}
			goal(nx, ny, p);
			break;
		case 3:
			nx = px[p];
			ny = py[p] - 1;
			if (hwa_switch == 1) {
				btn[p] = 1;
			}
			goal(nx, ny, p);
			break;
		default:
			break;
		}
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

void goal(int nx, int ny, int p) {
	if (nx == 5 && ny == 1) {
		player[p] = true;
	}
	if (nx == 6 && ny == 2) {
		player[p] = true;
	}
	if (nx == 7 && ny == 2) {
		player[p] = true;
	}
	if (nx == 8 && ny == 2) {
		player[p] = true;
	}
	if (nx == 9 && ny == 1) {
		player[p] = true;
	}
}

void mugunghwa(void) {
	int t = 0;
	int c = 0;
	int young_x = (hwa_map_x / 2) - (young / 2);

	mugunghwa_init();

	system("cls");
	display();
	dialog("����ȭ ���� �Ǿ����ϴ�.");
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				move_random_hwa(i, -1);
			}
		}

		if (tick % 200 == 0 && c < 6) {
			gotoxy(15, 0);
			for (int i = 0; i < c; i++) {
				if (i == 0) {
					hwa_switch = 0;
					printf("�� ");
				}
				if (i == 1) {
					printf("�� ");
				}
				if (i == 2) {
					printf("ȭ ");
				}
				if (i == 3) {
					printf("�� ");
				}
				if (i == 4) {
					printf("�� ");
				}
			}
			c++;
		}
		if (tick % 100 == 0 && c > 5) {
			gotoxy(15, 15);
			for (int j = 4; j < c; j++) {
				if (j == 5) {
					printf("�� ");
				}
				if (j == 6) {
					printf("�� ");
				}
				if (j == 7) {
					printf("�� ");
				}
				if (j == 8) {
					printf("�� ");
				}
				if (j == 9) {
					printf("�� ");
				}
			}
			c++;
		}
		if (c > 10) {
			hwa_switch = 1;
			if (hwa_switch == 1) {
				/*for (int i = 0; i < young; i++) {
					gotoxy(young_x + i, 1);
					printf("@");
				}*/
				for (int i = 6; i < 9; i++) {
					gotoxy(i, 1);
					printf("@");
				}
				for (int i = 0; i < 10; i++) {
					if (btn[i] == 1) {
						player[i] = false;
					}
				}
			}
			if (tick % 3000 == 0) {
				gotoxy(15, 0);
				printf("                                                             ");
				c = 0;
			}
		}
		if (hwa_switch != 1) {
			for (int i = 6; i < 9; i++) {
				//gotoxy(young_x + i, 1);
				gotoxy(i, 1);
				printf("#");
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}