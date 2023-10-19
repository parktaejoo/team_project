// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);
void intro(void);
void ending(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("�÷��̾� ��: ");
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
				gotoxy(6, 5); printf("|�����ڴ� %d���Դϴ�!|", i);
				gotoxy(7, 5); printf("---------------------");
			}
		}
		else {
			gotoxy(5, 5); printf(" ---------------------");
			gotoxy(6, 5); printf("| ����ڰ� �����ϴ�! |");
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