#include <stdio.h>
#include <time.h>
typedef
struct location_data { //0,1,2,3,4번 위치 저장 구조체
    int x, y;
}location;

char map[11][40], front[11][40];

int tick = 0;

void mugunghwa(void) {
    system("cls");
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 0 };
    int nx = 0, ny = 0;
    int pass[5] = { 0,0,0,0,0 }, dir[5] = { 3,3,3,3,3 };
    int c = 0, t = 200;
    int tick2 = 1, tick_s = 0;
    int move_check = 0;
    int heart[5] = { 1,1,1,1,1 }, speed[5] = { 0, 300,300,300,300 };
    location coord[5] = { {3,38},{4,38},{5,38},{6,38},{7,38} };
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            if (i == 0 || i == 10 || j == 0 || j == 39)
                map[i][j] = '*';
            else
                map[i][j] = ' ';
        }
    }
    map[4][1] = '#';
    map[5][1] = '#';
    map[6][1] = '#';
    map[3][38] = '0';
    map[4][38] = '1';
    map[5][38] = '2';
    map[6][38] = '3';
    map[7][38] = '4';
    srand((unsigned int)time(NULL));
    int per;

 while (1) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
            case 72: dir[0] = 0; break; // up (x-1, y+0)
            case 80: dir[0] = 1; break; // down (x+1, y+0)
            case 75: dir[0] = 2; break; // left (x+0, y-1)
            case 77: dir[0] = 3; break; // right (x+0, y+1)
            case 'q': return 0;
            }
        }
        if (tick % 100 == 0 && heart[0] == 1) {
            player_location(nx, ny, move_check, dir, dx, dy, heart, pass, map, coord);
            dir[0] = 3;
        }
        if (tick % speed[1] == 0 && heart[1] == 1) {
            per = rand() % 100;
            computer_location(1, nx, ny, dir, dx, dy, per, coord, map, heart, move_check, pass);
        }
        if (tick % speed[2] == 0 && heart[2] == 1) {
            per = rand() % 100;
            computer_location(2, nx, ny, dir, dx, dy, per, coord, map, heart, move_check, pass);
        }
        if (tick % speed[3] == 0 && heart[3] == 1) {
            per = rand() % 100;
            computer_location(3, nx, ny, dir, dx, dy, per, coord, map, heart, move_check, pass);
        }
        if (tick % speed[4] == 0 && heart[4] == 1) {
            per = rand() % 100;
            computer_location(4, nx, ny, dir, dx, dy, per, coord, map, heart, move_check, pass);
        }

        if (tick % t == 0 && c < 6) {
            gotoxy(12, 0);
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
        if (tick % t == 0 && c > 5) {
            gotoxy(12, 15);
            for (int j = 4; j < c; j++) {
                if (j == 4) {
                    printf("피 ");
                }
                if (j == 5) {
                    printf("었 ");
                }
                if (j == 6) {
                    printf("습 ");
                }
                if (j == 7) {
                    printf("니 ");
                }
                if (j == 8) {
                    printf("다 ");
                }
            }
            c++;
        }
        if (c > 10) {
            map[4][1] = '@', map[5][1] = '@', map[6][1] = '@';
            move_check = 1;
            tick_s = 10;
            dir[1] = 3, dir[2] = 3; dir[3] = 3, dir[4] = 3;
            if (tick2 % 3001 == 0) {
                gotoxy(12, 0);
                printf("                                                                                        ");
                c = 0;
                tick2 = 1;
                tick_s = 0;
                move_check = 0;
                map[4][1] = '#', map[5][1] = '#', map[6][1] = '#';
            }
        }
        draw();
        Sleep(10);
        tick += 10;
        tick2 += tick_s;
    }
}