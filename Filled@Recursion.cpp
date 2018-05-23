#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//재귀호출방법 !
void readFile(FILE *stream, char(*data)[14]); //파일에서 읽어와 배열 data 초기화
void startnumber(char(*data)[14], int* row, int* colunm); //원하는 시작 행,열 입력
void changeData(char(*data)[14], int row, int column, char check[]); //데이터 변경 - 재귀호출
void stepbystep(char step[]); //stepbystep을 보여줄건지, yes일때 단계별 출력
void printAllData(char(*data)[14]); //전체 배열 출력
void program(char(*data)[14], int row, int column, char check[], char goAgain[]); //전체를 재귀호출하기위한 함수

int main() {
	char data[4][14]; //데이터를 담을 2차원 배열
	int row = -1, column = -1; //행 , 열
	char check[10]; //단계별 출력을 할지 정하는 변수
	char goAgain[10] = "yes"; //프로그램을 계속 실행할지 여부를 담는 변수
	FILE* stream = NULL;
	readFile(stream, data);
	program(data, row, column, check, goAgain);
	return 0;
}

void readFile(FILE *stream, char(*data)[14]) {
	int i, j; //반복문 변수
	char filename[20]; //file이름을 담을 변수
	while (stream == NULL) { //data.txt 입력 전까지 예외처리
		printf("Enter the name of the file : ");
		gets_s(filename, 20);
		fopen_s(&stream, filename, "r"); //읽기전용으로 읽어옴
		if (stream == NULL)
			printf("Error reading database!!\n");
	}
	if (stream == NULL) {
		printf("에러가 발생하였습니다\n");
		//예외처리
	}
	//indata.txt 에서 배열로 파일 입력
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 15; j++) {
			if (j == 15) {}
			else { fscanf_s(stream, "%c", &data[i][j]); }
		}
	}
	printAllData(data);
	fclose(stream);
}

void startnumber(char(*data)[14], int* row, int* colunm) {
	fflush(stdin);
	char buf[20];
	int r, c;// 반복문에 사용할 변수
	do { //행,열에 해당하는 data 값이 '-' 가 아닐때 예외처리 반복문
		while (1) { //0부터 배열의 최대 행보다 작은 값만 입력받는다
			printf("Enter the row number : "); //원하는 행 입력
			gets_s(buf, 20);
			for (r = 0; r < strlen(buf); r++) { //문자열 전체 검색해서 0~9사이의 숫자인지 확인
				if (buf[r] < 48 || buf[r]>57) { //0~9사이의 값이 아닐때
					printf("input 0~3 number!\n");
					r = -1;
					break;
				}
			}
			if (r != -1) {
				*row = atoi(buf);
				if (*row < 0 || *row>3) {
					printf("input 0~3 number!\n");
				}
				else break;
			}
		}

		fflush(stdin);
		while (1) { //0부터 배열의 최대 행보다 작은 값만 입력받는다
			printf("Enter the column number : "); //원하는 행 입력
			gets_s(buf, 20);
			for (c = 0; c< strlen(buf); c++) { //문자열 전체 검색해서 0~9사이의 숫자인지 확인
				if (buf[c] < 48 || buf[c]>57) { //0~9사이의 값이 아닐때
					printf("input 0~13 number!\n");
					c = -1;
					break;
				}
			}
			if (c != -1) {
				*colunm = atoi(buf);
				if (*colunm < 0 || *colunm>13) {
					printf("input 0~13 number!\n");
				}
				else break;
			}
		}
		fflush(stdin);
		if (data[*row][*colunm] != '-') //시작데이터가 잘못됬을때 예외처리
			printf("worng number!! data is 'I' or '@'\n\n");
	} while (data[*row][*colunm] != '-');
}

void changeData(char(*data)[14], int row, int column, char check[]) {

	data[row][column] = '@';
	if (strcmp(check, "yes") == 0) { //단계별 출력을 원할때 출력
		printAllData(data);
		printf("\n");
	}

	// 위의 data 가 존재하고 '-' 일때 호출
	if (row - 1 >= 0 && data[row - 1][column] == '-') changeData(data, row - 1, column, check);
	// 왼쪽의 data 가 존재하고 '-' 일때 호출
	if (column - 1 >= 0 && data[row][column - 1] == '-') changeData(data, row, column - 1, check);
	// 아래의 data 가 존재하고 '-' 일때 호출
	if (row + 1 < 4 && data[row + 1][column] == '-') changeData(data, row + 1, column, check);
	// 오른쪽의 data 가 존재하고 '-' 일때 호출
	if (column + 1 < 14 && data[row][column + 1] == '-') changeData(data, row, column + 1, check);
}

void stepbystep(char step[]) {
	fflush(stdin);
	printf("Do you want to print out step by step ? <yes/no> ");
	//yes, no  가 아닐때 예외처리 반복문
	while (strcmp(step, "yes") != 0 && strcmp(step, "YES") != 0 && strcmp(step, "no") != 0 && strcmp(step, "NO") != 0) {
		gets_s(step, 10);
		if (strcmp(step, "yes") == 0 || strcmp(step, "YES") == 0) { // 단계
			strcpy_s(step, 4, "yes");
		}
		else if (strcmp(step, "no") == 0 || strcmp(step, "NO") == 0) {
			strcpy_s(step, 3, "no");
		}
		else {
			printf("yes or no\n");
		}
	}
}

void printAllData(char(*data)[14]) { //전체 배열 출력
	int i, j;
	printf("\n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 14; j++) {
			printf("%c ", data[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void program(char(*data)[14], int row, int column, char check[], char goAgain[]) { //전체 프로그램동작
	startnumber(data, &row, &column);
	stepbystep(check);
	changeData(data, row, column, check);
	if (strcmp(check, "no") == 0) printAllData(data); // 단계별 출력 아닐시에 한번 출력
	printf("Go again? <yes/no>");
	gets_s(goAgain, 10);
	if (strcmp(goAgain, "no") == 0) {
		printf("\nYour final result is\n");
		printAllData(data);
		return;
	}
	else if (strcmp(goAgain, "yes") == 0) {
		strcpy_s(check, 10, "0"); //check 초기화
		program(data, row, column, check, goAgain); //재귀호출
	}
	else {
		while (strcmp(goAgain, "no") != 0 && strcmp(goAgain, "yes") != 0) { //yes/no 가 아닐 때 예외처리
			printf("<yes/no>\n");
			gets_s(goAgain, 10);
		}
		strcpy_s(check, 10, "0"); //check 초기화
		program(data, row, column, check, goAgain);
	}
}
