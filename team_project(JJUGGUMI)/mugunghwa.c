#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

#define DIALOG_DURATION_SEC		2

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int hwa_map_x = 14, hwa_map_y = 40;
int young = 3;
int hwa_switch = 0;
int btn[10] = { 0 };
int goal_switch[10] = { 0 };
int dead_s[10] = { 0 };
int nswitch[10] = { 0 };

void goal(int, int, int);
void mugunghwa(void);

//맵 위치 생성
void hwamap_init(int n_row, int n_col) {
	// 두 버퍼를를 완전히 비우기
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

//플레이어 위치 생성
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

void move_manual_hwa(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)

	switch (key) {
	case K_UP: dir = DIR_UP;
		break;
	case K_DOWN: dir = DIR_DOWN;
		break;
	case K_LEFT: dir = DIR_LEFT;
		break;
	case K_RIGHT: dir = DIR_RIGHT;
		break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}
	goal(nx, ny, 0);

	move_tail(0, nx, ny);
}

//플레이어 움직임
void move_random_hwa(int player_hwa, int dir) {
	int p = player_hwa;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리
	int rand_num;

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	do {
		rand_num = randint(0, 8);
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
		ny = py[p] + randint(-1, 0);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

void goal(int nx, int ny, int p) {
	if (nx == 5 && ny == 1) {
		player[p] = true;
		goal_switch[p] = 1;
	}
	if (nx == 6 && ny == 2) {
		player[p] = true;
		goal_switch[p] = 1;
	}
	if (nx == 7 && ny == 2) {
		player[p] = true;
		goal_switch[p] = 1;
	}
	if (nx == 8 && ny == 2) {
		player[p] = true;
		goal_switch[p] = 1;
	}
	if (nx == 9 && ny == 1) {
		player[p] = true;
		goal_switch[p] = 1;
	}
}

void dialog_hwa(int player, char message[]) {
	for (int i = 0; i < DIALOG_DURATION_SEC; i++) {
		gotoxy(4, 5); printf("********************");
		gotoxy(5, 5); printf("%d 플레이어 %d %s", 2 - i, player, message);
		gotoxy(6, 5); printf("********************");
		Sleep(1000);
	}
	gotoxy(4, 5);  printf("                          ");
	gotoxy(5, 5);  printf("                          ");
	gotoxy(6, 5);  printf("                          ");
}

void mugunghwa(void) {
	int t = 0;
	int c = 0;
	int plus = 0;
	int young_x = (hwa_map_x / 2) - (young / 2);

	mugunghwa_init();
	system("cls");
	display();
	dialog("무궁화꽃이피었습니다");
	/*for (int i = 0; i < n_player; i++) {
		if (btn[i] == 1) {
			dialog_hwa(i, " 컷!");
		}
	}*/
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			if (btn[0] != 1) {
				if (goal_switch[0] != 1) {
					if (hwa_switch == 1) {
						btn[0] = 1;
					}
					move_manual_hwa(key);
				}
			}
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				if (btn[i] != 1) {
					if (goal_switch[i] != 1) {
						move_random_hwa(i, -1);
					}
				}
			}
		}

		if (c <= 10) {
			if (tick % 1000 == 0 && c < 6) {
				gotoxy(15, 0);
				for (int i = 0; i < c; i++) {
					if (i == 0) {
						printf("무 ");
					}
					if (i == 1) {
						printf("궁 ");
					}
					if (i == 2) {
						printf("화 ");
					}
					if (i == 3) {
						printf("꽃 ");
					}
					if (i == 4) {
						printf("이 ");
					}
				}
				c++;
			}
			if (tick % 200 == 0 && c > 5) {
				gotoxy(15, 15);
				for (int j = 4; j < c; j++) {
					if (j == 5) {
						printf("피 ");
					}
					if (j == 6) {
						printf("었 ");
					}
					if (j == 7) {
						printf("습 ");
					}
					if (j == 8) {
						printf("니 ");
					}
					if (j == 9) {
						printf("다 ");

					}
				}
				c++;
			}
		}
		if (c > 10) {
			hwa_switch = 1;
			for (int i = 6; i < 9; i++) {
				gotoxy(i, 1);
				printf("@");
			}
			if (tick % 4000 == 0) {
				gotoxy(15, 0);
				printf("                                                             ");
				c = 0;
				hwa_switch = 0;
			}
			for (int i = 0; i < 10; i++) {
				if (btn[i] == 1 && nswitch[i] != 1) {
					player[i] = false;
					dead_s[i] = 1;
				}
			}
			for (int i = 0; i < n_player; i++) {
				if (btn[i] == 1 && dead_s[i] == 1) {
					dialog_hwa(i, "플레이어 죽음");
					dead_s[i] = 0;
					nswitch[i] = 1;
				}
			}
		}
		if (hwa_switch != 1) {
			for (int i = 6; i < 9; i++) {
				gotoxy(i, 1);
				printf("#");
			}
		}

		display();
		Sleep(10);
		tick += 10;
		int j;
		j = 0;
		for (int i = 0; i < n_player; i++) {
			if (player[i] == true) {
				j++;
			}
		}
		if (j == 1) {
			break;
		}
	}
}