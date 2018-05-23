// Homework.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Menu(int *menu, FILE *stream, int randomnumber[], int *num, int *check); //메뉴 생성 함수
void readData(FILE *stream, int randomnumber[], int *num, int *check);//난수를 발생시켜 data.dat에 저장하기 위한 함수
void searchNumber(FILE *stream, int randomnumber[], int *num, int rank); //오름차순 순번의 숫자를 찾기 위한 함수

int main()
{
	int menu = 0, num, check = 0; // menu = 사용자의 메뉴선택에따라 값 변경, 함수 호출 //num=난수의 갯수를 담을 변수
	//check = 난수의 생성을 확인하는 변수
	int *randomnumber = NULL; //난수를 저장할 배열
	FILE *stream;
	fopen_s(&stream, "data.dat", "w"); //stream 파일을 쓰기전용으로 생성
	if (stream == NULL) {
		printf("에러가 발생하였습니다\n");
		//예외처리
	}
	else {
		while (menu != 3) {
			//메뉴 출력
			printf("메뉴\n1. 난수 생성\n2. 오름차순 순번 숫자 찾기\n3. 프로그램 종료");
			scanf_s("%d", &menu); //메뉴 선택
			if (menu == 1 || menu == 2 || menu == 3) //1,2,3 외의 숫자가 왔을때 예외처리
				Menu(&menu, stream, randomnumber, &num, &check); //메뉴 출력 함수 호출
			else {
				printf("1,2,3 중에 선택해주세요\n");
			}
		}
		fclose(stream);
	}
	return 0; //프로그램 종료
}


void Menu(int *menu, FILE *stream, int randomnumber[], int *num, int *check) {
	int rank; //몇번째 큰수를 찾을지 저장하는 변수 check = 난수가 생성되었는지 확인하는 변수
	switch (*menu) {
	case 1://난수생성
		char choice;
		getchar(); //버퍼에 남은 enter 제거
		printf("난수를 생성하시겠습니까 <y/n>");
		scanf_s("%c", &choice);
		if (choice == 'y' || choice == 'Y') { // 'y' 나 'Y'가 들어왔을때만 실행
			readData(stream, randomnumber, num, check); //난수생성
		}
		else if (choice == 'n' || choice == 'N') { //'n' 이나 'N'이 들어왔을때만 실행
		}
		else {
			printf("y,n 중에 선택하세요\n"); // 예외처리
		}
		break;
	case 2://슷자 찾기
		if (*check == 0) {
			printf("난수가 생성되지 않았습니다\n");
		}
		else {
			printf("몇 번째로 작은 숫자를 찾고 싶으신가요?");
			scanf_s("%d", &rank);
			searchNumber(stream, randomnumber, num, rank);
		}
		break;
	case 3://종료
		printf("프로그램을 종료하겠습니다\n");
		break;
	default:
		printf("1,2,3 중 선택해주세요\n"); //1,2,3 외의 숫자가 들어왔을때 예외처리
		break;
	}
}

void readData(FILE *stream, int randomnumber[], int *num, int *check)//난수를 발생시켜 data.dat에 저장하기 위한 함수
{
	int  i, random; // i = for문에서 사용
						//randomnumber = num 에 따라 동적할당을 위한 배열
	printf("몇 개의 난수를 생성하고 싶은신가요 ?");
	scanf_s("%d", num);//동적할당 갯수 사용자지정
	randomnumber = (int *)malloc(sizeof(int) * (*num)); //num에 따라 동적할당
	srand(time(NULL)); //rand()에 매번다른 seed값을 주기위한 함수

	for (i = 0; i < *num; i++) { // stream 파일에 난수생성을 위한 for loop
		random = rand(); //난수 저장을 위해 random 변수에 매번 다른 수를 넣음
		fprintf_s(stream, "%d ", random); //난수를 저장, 수와 수 사이엔 blank
		if (i - 10 == -1) fprintf_s(stream, "\n"); //난수 10개마다 행넘김
	}
	fclose(stream); //쓰기전용으로 열었던 stream을 닫음
	printf("%d개의 난수가 생성되었습니다\n", *num);
	*check = 1;
}


void searchNumber(FILE *stream, int randomnumber[], int *num, int rank) {
	int count, index, i, j;//count = 숫자의 등수, index = 숫자의 위치, i,j = for loop
	fopen_s(&stream, "data.dat", "r"); //stream 파일을 읽기전용으로 가져옴
	if (stream == NULL) {
		//예외처리
	}
	else {
		for (i = 0; i < *num; i++) { //stream 파일에서 난수를 불러와 randomnumber 배열에 저장하기위한 for loop
			fscanf_s(stream, "%d", &randomnumber[i]);
		}

		for (i = 0; i < *num; i++) {
			count = 1;
			for (j = 0; j < *num; j++) {
				if (randomnumber[i] < randomnumber[j]) {
					count++;
				}

				if (count == rank) {
					index = i;
					printf("%d번째로 작은 숫자는 %d이고, 데이터 %d번째에 위치해 있습니다.", rank, randomnumber[i], index);
				}
			}
		}
	}
}