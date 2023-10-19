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

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

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

int main(void) {
	jjuggumi_init();
	intro();
	sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	ending();
	return 0;
}