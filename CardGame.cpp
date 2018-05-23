// FindCard.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
void gotoxy(int x, int y); //좌표로 이동
void initMap(char(*Map)[7]); //맵 ? 표로 초기화
void initBehind(char(*Map)[7], char alpha[49]); //알파벳이 들어있는 맵
void printMap(char(*Map)[7]); //맵 출력
void initAlpha(char alpha[49]); //알파벳 초기화
void makeMap(char *front, char *behind); //맵 변화
int main()
{
	int i = 0;
	char answer[4];
	int trycount = 1;
	int entercount = 1;
	int key = 0;
	char alpha[49];
	char MapBehind[7][7]; // 정답을 가진 맵
	char Mapfront[7][7]; // ? 를 가짐
	int x = 0, y = 0; // 좌표
	int x1, y1;
	int score = 1000; //점수
	initMap(Mapfront);
	initAlpha(alpha);
	initBehind(MapBehind, alpha);
	printMap(Mapfront);
	gotoxy(15, 2);
	printf("점수 = %4d", score);
	gotoxy(15, 3);
	printf("정답 = %c %c %c", alpha[0], alpha[1], alpha[2]);
	gotoxy(0, 10);
	printf("정답을 입력하려면 ? 키를 누르세요");
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	gotoxy(x, y);
	printf("?");
	while (score>0) {
			key = _getch();
			if (key == 224 || key == 0) {
				key = _getch();
				switch (key) {
				case 72: //상
					if (y > 0) {
						gotoxy(x, y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf("?");
						y--;
						gotoxy(0, 0);
						printMap(Mapfront);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
						gotoxy(x, y);
						printf("?");
					}
					break;
				case 75: //좌
					if (x > 0) {
						gotoxy(x, y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf("?");
						x--;
						gotoxy(0, 0);
						printMap(Mapfront);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
						gotoxy(x, y);
						printf("?");
					}
					break;
				case 77: //우
					if (x < 6) {
						gotoxy(x, y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf("?");
						x++;
						gotoxy(0, 0);
						printMap(Mapfront);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
						gotoxy(x, y);
						printf("?");
					}
					break;
				case 80: //하
					if (y < 6) { 
						gotoxy(x, y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf("?");
						y++;
						gotoxy(0, 0);
						printMap(Mapfront);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
						gotoxy(x, y);
						printf("?");
					}
					break;
				}
			}
			else if (key == 63) {
				gotoxy(0, 11);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("정답은 ? (연속으로 세글자 입력) :  ");
				scanf_s(" %c", &answer[1]);
				scanf_s(" %c", &answer[2]);
				scanf_s(" %c", &answer[3]);
				if (answer[1] == alpha[0] || answer[1] == alpha[1] || answer[1] == alpha[2]){
					if (answer[2] == alpha[0] || answer[2] == alpha[1] || answer[2] == alpha[2]) {
						if (answer[3] == alpha[0] || answer[3] == alpha[1] || answer[3] == alpha[2]) {
							gotoxy(0, 13);
							printf("정답입니다 !!!!");
							return 0;
						}
						else {
							gotoxy(0, 13);
							printf("오답입니다");
							score -= trycount * 10;
							trycount++;
							gotoxy(0, 11);
							printf("                                           ");
							gotoxy(15, 2);
							printf("점수 = %4d", score);
							gotoxy(x, y);
						}
					}
					else {
						gotoxy(0, 13);
						printf("오답입니다");
						score -= trycount * 10;
						trycount++;
						gotoxy(0, 11);
						printf("                                           ");
						gotoxy(15, 2);
						printf("점수 = %4d", score);
						gotoxy(x, y);
					}
				}
				else {
					gotoxy(0, 13);
					printf("오답입니다");
					score -= trycount * 10;
					trycount++;
					gotoxy(0, 11);
					printf("                                           ");
					gotoxy(15, 2);
					printf("점수 = %4d", score);
					gotoxy(x, y);
				}
			}
			else {
				if (key == 13) {
					if (entercount == 1) {
						x1 = x;
						y1 = y;
						Mapfront[y][x] = MapBehind[y][x];
						gotoxy(0, 0);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printMap(Mapfront);
						entercount++;
					}
					else if (entercount == 2) {
						score -= 5;
						gotoxy(15, 2);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						printf("점수 = %4d", score);
						if (MapBehind[y][x] == MapBehind[y1][x1]) {
							Mapfront[y][x] = MapBehind[y][x];
							gotoxy(0, 0);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							printMap(Mapfront);
						}
						else {
							Mapfront[y][x] = MapBehind[y][x];
							gotoxy(0, 0);
							printMap(Mapfront);
							Sleep(1000);
							Mapfront[y1][x1] = '?';
							Mapfront[y][x] = '?';
							gotoxy(0, 0);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							printMap(Mapfront);
						}
						entercount = 1;
						gotoxy(x, y);
					}
				}
			}
	}
	gotoxy(0, 13);
	printf("ㅠㅠㅠ 실패하였습니다\n");
	return 0;
}
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void initMap(char(*Map)[7]) {
	int i, j;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			Map[i][j] = '?';
		}
	}
}
void initBehind(char(*Map)[7], char alpha[49]) {
	int answer[49];
	int check;
	int i, j, index = 0;
	srand(time(NULL));
	for (i = 0; i < 49; i++) {
		while (1) {
			answer[i] = rand() % 49;
			check = 0;
			for (j = 0; j < i; j++) { //같은값이 있는지 확인한다
				if (answer[j] == answer[i]) {
					check = 1;
					break;
				}
			}
			if (!check)
				break;
		}
	}

	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			Map[i][j] = alpha[answer[index]];
			index++;
		}
	}
}

void printMap(char(*Map)[7]) {
	int i, j;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			printf("%c", Map[i][j]);
		}
		printf("\n");
	}
}

void initAlpha(char alpha[49]) { // A = 65, Z = 90
	//abcde fghij klmno pqrst uvwxy z 26개
	int i, j = 0;
	srand(time(NULL));
	alpha[0] = rand() % 25 + 65; //정답 만들기
	do {
		alpha[1] = rand() % 25 + 65;
	} while (alpha[1] == alpha[0]);

	do {
		alpha[2] = rand() % 25 + 65;
	} while (alpha[2] == alpha[0] || alpha[2] == alpha[1]);

	for (i = 3; i < 49; i++) {
		alpha[i] = 'A' + j;
		while (alpha[i] == alpha[0] || alpha[i] == alpha[1] || alpha[i] == alpha[2]) {
			alpha[i] += 1;
			j++;
		}
		j++;
		if (alpha[i] == 'Z') j = 0;
	}
}
void makeMap(char *front, char *behind){ //맵 변화
	*front = *behind;
}
