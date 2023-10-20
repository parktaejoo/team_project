// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);
void intro(void);
void ending(void);

void gotoxy(int row, int col);
void draw(void);


void gotoxy(int row, int col) {
	COORD pos = { col, row }; // 행, 열 반대로 전달
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef
struct location_data { //0,1,2,3,4번 위치 저장 구조체
	int x, y;
}location;

// low 이상 high 이하 난수를 발생시키는 함수
// low와 high 사이의 임의의 정수를 반환하는 역할을 함

int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum; 
}

// 게임 초기화 담당
// 플레이어 수를 입력 받고, 모든 플레이어가 살아있음으로 설정

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

// 게임 시작 시 나타나는 인트로(소개 화면)를 출력하는 역할을 함

void intro(void) {
	system("cls");
	printf(" _____  _   _ ______  _   _  _____  _   _  _____ \n");
	printf("/  ___|| | | || ___ \\| | | ||_   _|| | | ||  ___|\n");
	printf("\\ `--. | | | || |_/ /| | | |  | |  | | | || |__  \n");
	printf(" `--. \\| | | ||    / | | | |  | |  | | | ||  __| \n");
	printf("/\\__/ /| |_| || |\\ \\ \\ \\_/ / _| |_ \\ \\_/ /| |___ \n");
	printf("\\____/  \\___/ \\_| \\_| \\___/  \\___/  \\___/ \\____/ \n");
	for (int i = 0; i < 3; i++) {
		gotoxy(0, 50 + (i * 4)); printf(" _ ");
		gotoxy(1, 50 + (i * 4)); printf("| |");
		gotoxy(2, 50 + (i * 4)); printf("| |");
		gotoxy(3, 50 + (i * 4)); printf("| |");
		gotoxy(4, 50 + (i * 4)); printf("|_|");
		gotoxy(5, 50 + (i * 4)); printf("(_)");
		Sleep(1000);
	}
}

// 게임 종료 시 화면에 나타나는 엔딩을 출력하는 역할을 함

void ending(void) {
	int count = 0;
	for (int i = 0; i < n_player; i++) {
		if (player[i]) {
			count++;
		}
	}
	for (int i = 0; i < n_player; i++) {
		if (count == 1) {
			if (player[i]) {
				gotoxy(5, 5); printf("---------------------");
				gotoxy(6, 5); printf("|생존자는 %d번입니다!|", i);
				gotoxy(7, 5); printf("---------------------");
			}
		}
		else {
			gotoxy(5, 5); printf(" ---------------------");
			gotoxy(6, 5); printf("| 우승자가 없습니다! |");
			gotoxy(7, 5); printf(" ---------------------");
		}
	}
	for (int i = 0; i < 13 + n_player; i++) {
		printf("\n");
	}
}

int player_location(int nx, int ny, int move_check, int dir[], int dx[], int dy[], int pass[], int heart[], char map[11][40], location coord[]) {
	if (move_check == 1 && dir[0] != 3) {
		if (dir[0] == 2) {
			for (int j = 1; j < coord[0].y; j++) {
				if (map[coord[0].x][j] != ' ' && map[coord[0].x][j] != '@') {
					heart[0] = 1;
				}
			}
			if (heart[0] == 0) {
				map[coord[0].x][coord[0].y] = ' ';
				return 0;
			}
		}
		else {
			map[coord[0].x][coord[0].y] = ' ';
			heart[0] = 0;
			return 0;
		}
	}
	nx = coord[0].x + dx[dir[0]];
	ny = coord[0].y + dy[dir[0]];
	if ((nx == 4 && ny == 2) || (nx == 5 && ny == 2) || (nx == 6 && ny == 2) || (nx == 3 && ny == 1) || (nx == 7 && ny == 1)) {
		pass[0] = 1;
	}
	if (nx > 0 && nx < 10 && ny > 0 && ny < 39 && map[nx][ny] == ' ') {
		map[coord[0].x][coord[0].y] = ' ';
		coord[0].x = nx; coord[0].y = ny;
		map[coord[0].x][coord[0].y] = '0';
	}
	return 1;
}

int computer_location(int a, int nx, int ny, int dir[], int dx[], int dy[], int per, location coord[], char map[11][40], int heart[], int move_check, int pass[]) {
	if (move_check == 0) {
		dir[a] = rand() % 10;
		if (dir[a] < 7) {
			dir[a] = 2;
		}
		else if (dir[a] < 8) {
			dir[a] = 0;
		}
		else if (dir[a] < 9) {
			dir[a] = 1;
		}
		else if (dir[a] < 10) {
			dir[a] = 3;
		}
	}
	else {
		if (per < 10) {
			dir[a] = rand() % 3;
			if (dir[a] == 2) {
				for (int j = 1; j < coord[a].y; j++) {
					if (map[coord[a].x][j] != ' ' && map[coord[a].x][j] != '@') {
						heart[a] = 1;
					}
				}
				if (heart[a] == 0) {
					map[coord[a].x][coord[a].y] = ' ';
					return 0;
				}
			}
			else {
				map[coord[a].x][coord[a].y] = ' ';
				heart[a] = 0;
				return 0;
			}
		}
	}
	nx = coord[a].x + dx[dir[a]];
	ny = coord[a].y + dy[dir[a]];
	if ((nx == 4 && ny == 2) || (nx == 5 && ny == 2) || (nx == 6 && ny == 2) || (nx == 3 && ny == 1) || (nx == 7 && ny == 1)) {
		pass[a] = 1;
	}
	if (nx > 0 && nx < 10 && ny > 0 && ny < 39 && map[nx][ny] == ' ') {
		map[coord[a].x][coord[a].y] = ' ';
		coord[a].x = nx; coord[a].y = ny;
		map[coord[a].x][coord[a].y] = a + '0';
	}
	heart[a] = 1;
}

// 초기화, 인트로, 미니게임들(sample(); ,mugunghwa();, nightgame();, juldarigi();, jebi();
// 그리고 엔딩 순서로 진행됨
int main(void) {
	jjuggumi_init();
	intro();
	mugunghwa();   // 여기서 '무궁화 꽃이 피었습니다' 게임을 실행합니다.
	ending();
	return 0;
}