// 2023-2 ������α׷��� ����: �޲ٹ� ����
// ������ ������ �� ������ ascii art�� �����ϴ�
// intro() �ۼ� (5�� ���� ������)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

void intro()
{
	printf("======================================\n");
	printf(" �޲ٹ� ���ӿ� ���� ���� ȯ���մϴ�!\n");
	printf("======================================\n");
}


int jjuggumi_init(void);


// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("\n�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

int main(void) {
	jjuggumi_init();
	intro();
	sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}
