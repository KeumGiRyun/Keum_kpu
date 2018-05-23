#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Stack {
	int row;
	int column;
}Stack;

void readFile(FILE *stream, char(*data)[14]); //���Ͽ��� �о�� �迭 data �ʱ�ȭ
void startnumber(char(*data)[14], int* row, int* colunm); //���ϴ� ���� ��,�� �Է�
void changeData(char(*data)[14], int row, int column, char check[]); //������ ���� - ���ȣ��
void stepbystep(char step[]); //stepbystep�� �����ٰ���, yes�϶� �ܰ躰 ���
void printAllData(char(*data)[14]); //��ü �迭 ���
void program(char(*data)[14], int row, int column, char check[], char goAgain[]); //��ü���α׷� ����
void initStack(Stack *stack) { //stack �ʱ�ȭ
	int i = 0;
	for (i; i < 48; i++) {
		stack[i].row = -1;
		stack[i].column = -1;
	}
}
int isFull(int index) { //��ã���� Ȯ��
	if (index != 0) return 1;
	else return 0;
}
int isEmpty(int index) { //����ִ��� Ȯ��
	if (index == 0) return 0;
	else return 1;
}
void push(Stack *stack, char(*data)[14], int row, int column, int *index) { //stack�� �ϳ� �Է�
	if (*index == 48) {
		printf("FULL!\n");
		return;
	}
	else {
		(*index)++;
		stack[*index].row = row;
		stack[*index].column = column;
		data[row][column] = '@';
	}
}

void pop(Stack *stack,int *index,int *row,int *column) { //stack���� ������

	if ((*index) == 0) {
		printf("EMPTY!\n");
		return;
	}
	else {
		(*index)--;
		*row = stack[*index].row;
		*column = stack[*index].column;
	}
}


int main() {
	char data[4][14]; //�����͸� ���� 2���� �迭
	int row = -1, column = -1; //�� , ��
	char check[10] ; //�ܰ躰 ����� ���� ���ϴ� ����
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
	Stack stack[48];
	int index = -1; //stack �迭�� �ε���
	int before_row , before_column; //�����ܰ�
	initStack(stack);
	push(stack, data, row, column, &index);

	do{
		if (data[row - 1][column] == '-' && row > 0) {
			push(stack, data, row-1, column, &index);
			before_row = row;
			row--;
			if (strcmp(check, "yes") == 0) { //�ܰ躰 ����� ���Ҷ� ���
				printAllData(data);
				printf("\n");
			}
		}
		else if (data[row][column - 1] == '-' && column > 0) {
			push(stack, data, row, column-1, &index);
			before_column = column;
			column--;
			if (strcmp(check, "yes") == 0) { //�ܰ躰 ����� ���Ҷ� ���
				printAllData(data);
				printf("\n");
			}
		}
		else if (data[row + 1][column] == '-' && row < 3) {
			push(stack, data, row+1, column, &index);
			before_row = row;
			row++;
			if (strcmp(check, "yes") == 0) { //�ܰ躰 ����� ���Ҷ� ���
				printAllData(data);
				printf("\n");
			}
		}
		else if (data[row][column + 1] == '-' && column < 13) {
			push(stack, data, row, column+1, &index);
			before_column = column;
			column++;
			if (strcmp(check, "yes") == 0) { //�ܰ躰 ����� ���Ҷ� ���
				printAllData(data);
				printf("\n");
			}
		}
		else {
			pop(stack, &index,&row,&column);
		}
	} while (index != 0);
	
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
	while (strcmp(goAgain, "no") != 0) {
		startnumber(data, &row, &column);
		stepbystep(check);
		changeData(data, row, column, check);
		if (strcmp(check, "no") == 0) printAllData(data); // �ܰ躰 ��� �ƴҽÿ� �ѹ� ���
		printf("Go again? <yes/no>");
		gets_s(goAgain, 10);
		if (strcmp(goAgain, "no") == 0) { //no �϶� ���α׷� ����
			printf("\nYour final result is\n");
			printAllData(data);
			return;
		}
		else if (strcmp(goAgain, "yes") == 0) { //yes�϶� �ѹ��� ����
			strcpy_s(check, 10, "0"); //check �ʱ�ȭ
		}
		else {
			while (strcmp(goAgain, "no") != 0 && strcmp(goAgain, "yes") != 0) { //yes/no �� �ƴ� �� ����ó��
				printf("<yes/no>\n");
				gets_s(goAgain, 10);
			}
			strcpy_s(check, 10, "0"); //check �ʱ�ȭ
		}
	}
}

void Push(Stack *stack, char(*data)[14], int row, int column) {
	
}