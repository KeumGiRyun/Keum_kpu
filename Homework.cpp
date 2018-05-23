// Homework.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Menu(int *menu, FILE *stream, int randomnumber[], int *num, int *check); //�޴� ���� �Լ�
void readData(FILE *stream, int randomnumber[], int *num, int *check);//������ �߻����� data.dat�� �����ϱ� ���� �Լ�
void searchNumber(FILE *stream, int randomnumber[], int *num, int rank); //�������� ������ ���ڸ� ã�� ���� �Լ�

int main()
{
	int menu = 0, num, check = 0; // menu = ������� �޴����ÿ����� �� ����, �Լ� ȣ�� //num=������ ������ ���� ����
	//check = ������ ������ Ȯ���ϴ� ����
	int *randomnumber = NULL; //������ ������ �迭
	FILE *stream;
	fopen_s(&stream, "data.dat", "w"); //stream ������ ������������ ����
	if (stream == NULL) {
		printf("������ �߻��Ͽ����ϴ�\n");
		//����ó��
	}
	else {
		while (menu != 3) {
			//�޴� ���
			printf("�޴�\n1. ���� ����\n2. �������� ���� ���� ã��\n3. ���α׷� ����");
			scanf_s("%d", &menu); //�޴� ����
			if (menu == 1 || menu == 2 || menu == 3) //1,2,3 ���� ���ڰ� ������ ����ó��
				Menu(&menu, stream, randomnumber, &num, &check); //�޴� ��� �Լ� ȣ��
			else {
				printf("1,2,3 �߿� �������ּ���\n");
			}
		}
		fclose(stream);
	}
	return 0; //���α׷� ����
}


void Menu(int *menu, FILE *stream, int randomnumber[], int *num, int *check) {
	int rank; //���° ū���� ã���� �����ϴ� ���� check = ������ �����Ǿ����� Ȯ���ϴ� ����
	switch (*menu) {
	case 1://��������
		char choice;
		getchar(); //���ۿ� ���� enter ����
		printf("������ �����Ͻðڽ��ϱ� <y/n>");
		scanf_s("%c", &choice);
		if (choice == 'y' || choice == 'Y') { // 'y' �� 'Y'�� ���������� ����
			readData(stream, randomnumber, num, check); //��������
		}
		else if (choice == 'n' || choice == 'N') { //'n' �̳� 'N'�� ���������� ����
		}
		else {
			printf("y,n �߿� �����ϼ���\n"); // ����ó��
		}
		break;
	case 2://���� ã��
		if (*check == 0) {
			printf("������ �������� �ʾҽ��ϴ�\n");
		}
		else {
			printf("�� ��°�� ���� ���ڸ� ã�� �����Ű���?");
			scanf_s("%d", &rank);
			searchNumber(stream, randomnumber, num, rank);
		}
		break;
	case 3://����
		printf("���α׷��� �����ϰڽ��ϴ�\n");
		break;
	default:
		printf("1,2,3 �� �������ּ���\n"); //1,2,3 ���� ���ڰ� �������� ����ó��
		break;
	}
}

void readData(FILE *stream, int randomnumber[], int *num, int *check)//������ �߻����� data.dat�� �����ϱ� ���� �Լ�
{
	int  i, random; // i = for������ ���
						//randomnumber = num �� ���� �����Ҵ��� ���� �迭
	printf("�� ���� ������ �����ϰ� �����Ű��� ?");
	scanf_s("%d", num);//�����Ҵ� ���� ���������
	randomnumber = (int *)malloc(sizeof(int) * (*num)); //num�� ���� �����Ҵ�
	srand(time(NULL)); //rand()�� �Ź��ٸ� seed���� �ֱ����� �Լ�

	for (i = 0; i < *num; i++) { // stream ���Ͽ� ���������� ���� for loop
		random = rand(); //���� ������ ���� random ������ �Ź� �ٸ� ���� ����
		fprintf_s(stream, "%d ", random); //������ ����, ���� �� ���̿� blank
		if (i - 10 == -1) fprintf_s(stream, "\n"); //���� 10������ ��ѱ�
	}
	fclose(stream); //������������ ������ stream�� ����
	printf("%d���� ������ �����Ǿ����ϴ�\n", *num);
	*check = 1;
}


void searchNumber(FILE *stream, int randomnumber[], int *num, int rank) {
	int count, index, i, j;//count = ������ ���, index = ������ ��ġ, i,j = for loop
	fopen_s(&stream, "data.dat", "r"); //stream ������ �б��������� ������
	if (stream == NULL) {
		//����ó��
	}
	else {
		for (i = 0; i < *num; i++) { //stream ���Ͽ��� ������ �ҷ��� randomnumber �迭�� �����ϱ����� for loop
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
					printf("%d��°�� ���� ���ڴ� %d�̰�, ������ %d��°�� ��ġ�� �ֽ��ϴ�.", rank, randomnumber[i], index);
				}
			}
		}
	}
}