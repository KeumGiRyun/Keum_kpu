#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//���ȣ���� !
void readFile(FILE *stream, char(*data)[14]); //���Ͽ��� �о�� �迭 data �ʱ�ȭ
void startnumber(char(*data)[14], int* row, int* colunm); //���ϴ� ���� ��,�� �Է�
void changeData(char(*data)[14], int row, int column, char check[]); //������ ���� - ���ȣ��
void stepbystep(char step[]); //stepbystep�� �����ٰ���, yes�϶� �ܰ躰 ���
void printAllData(char(*data)[14]); //��ü �迭 ���
void program(char(*data)[14], int row, int column, char check[], char goAgain[]); //��ü�� ���ȣ���ϱ����� �Լ�

int main() {
	char data[4][14]; //�����͸� ���� 2���� �迭
	int row = -1, column = -1; //�� , ��
	char check[10]; //�ܰ躰 ����� ���� ���ϴ� ����
	char goAgain[10] = "yes"; //���α׷��� ��� �������� ���θ� ��� ����
	FILE* stream = NULL;
	readFile(stream, data);
	program(data, row, column, check, goAgain);
	return 0;
}

void readFile(FILE *stream, char(*data)[14]) {
	int i, j; //�ݺ��� ����
	char filename[20]; //file�̸��� ���� ����
	while (stream == NULL) { //data.txt �Է� ������ ����ó��
		printf("Enter the name of the file : ");
		gets_s(filename, 20);
		fopen_s(&stream, filename, "r"); //�б��������� �о��
		if (stream == NULL)
			printf("Error reading database!!\n");
	}
	if (stream == NULL) {
		printf("������ �߻��Ͽ����ϴ�\n");
		//����ó��
	}
	//indata.txt ���� �迭�� ���� �Է�
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
	int r, c;// �ݺ����� ����� ����
	do { //��,���� �ش��ϴ� data ���� '-' �� �ƴҶ� ����ó�� �ݺ���
		while (1) { //0���� �迭�� �ִ� �ຸ�� ���� ���� �Է¹޴´�
			printf("Enter the row number : "); //���ϴ� �� �Է�
			gets_s(buf, 20);
			for (r = 0; r < strlen(buf); r++) { //���ڿ� ��ü �˻��ؼ� 0~9������ �������� Ȯ��
				if (buf[r] < 48 || buf[r]>57) { //0~9������ ���� �ƴҶ�
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
		while (1) { //0���� �迭�� �ִ� �ຸ�� ���� ���� �Է¹޴´�
			printf("Enter the column number : "); //���ϴ� �� �Է�
			gets_s(buf, 20);
			for (c = 0; c< strlen(buf); c++) { //���ڿ� ��ü �˻��ؼ� 0~9������ �������� Ȯ��
				if (buf[c] < 48 || buf[c]>57) { //0~9������ ���� �ƴҶ�
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
		if (data[*row][*colunm] != '-') //���۵����Ͱ� �߸������� ����ó��
			printf("worng number!! data is 'I' or '@'\n\n");
	} while (data[*row][*colunm] != '-');
}

void changeData(char(*data)[14], int row, int column, char check[]) {

	data[row][column] = '@';
	if (strcmp(check, "yes") == 0) { //�ܰ躰 ����� ���Ҷ� ���
		printAllData(data);
		printf("\n");
	}

	// ���� data �� �����ϰ� '-' �϶� ȣ��
	if (row - 1 >= 0 && data[row - 1][column] == '-') changeData(data, row - 1, column, check);
	// ������ data �� �����ϰ� '-' �϶� ȣ��
	if (column - 1 >= 0 && data[row][column - 1] == '-') changeData(data, row, column - 1, check);
	// �Ʒ��� data �� �����ϰ� '-' �϶� ȣ��
	if (row + 1 < 4 && data[row + 1][column] == '-') changeData(data, row + 1, column, check);
	// �������� data �� �����ϰ� '-' �϶� ȣ��
	if (column + 1 < 14 && data[row][column + 1] == '-') changeData(data, row, column + 1, check);
}

void stepbystep(char step[]) {
	fflush(stdin);
	printf("Do you want to print out step by step ? <yes/no> ");
	//yes, no  �� �ƴҶ� ����ó�� �ݺ���
	while (strcmp(step, "yes") != 0 && strcmp(step, "YES") != 0 && strcmp(step, "no") != 0 && strcmp(step, "NO") != 0) {
		gets_s(step, 10);
		if (strcmp(step, "yes") == 0 || strcmp(step, "YES") == 0) { // �ܰ�
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

void printAllData(char(*data)[14]) { //��ü �迭 ���
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

void program(char(*data)[14], int row, int column, char check[], char goAgain[]) { //��ü ���α׷�����
	startnumber(data, &row, &column);
	stepbystep(check);
	changeData(data, row, column, check);
	if (strcmp(check, "no") == 0) printAllData(data); // �ܰ躰 ��� �ƴҽÿ� �ѹ� ���
	printf("Go again? <yes/no>");
	gets_s(goAgain, 10);
	if (strcmp(goAgain, "no") == 0) {
		printf("\nYour final result is\n");
		printAllData(data);
		return;
	}
	else if (strcmp(goAgain, "yes") == 0) {
		strcpy_s(check, 10, "0"); //check �ʱ�ȭ
		program(data, row, column, check, goAgain); //���ȣ��
	}
	else {
		while (strcmp(goAgain, "no") != 0 && strcmp(goAgain, "yes") != 0) { //yes/no �� �ƴ� �� ����ó��
			printf("<yes/no>\n");
			gets_s(goAgain, 10);
		}
		strcpy_s(check, 10, "0"); //check �ʱ�ȭ
		program(data, row, column, check, goAgain);
	}
}
