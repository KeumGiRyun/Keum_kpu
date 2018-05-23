// Homework3.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct theInventory {
	char lastname[50];
	char firstname[50];
	struct Book *link;
}theInventory;

typedef struct Book {
	char title[100];
	char qty[25];
	char price[25];
	struct Book *next;
}Book;

void greeting(); //�λ�
void readDatabase(theInventory Inventory[]); //inventory ����
char* printMenu(); //�޴� ���
void displayInventory(theInventory Inventory[]);
void displayAuthorsWork(theInventory *Inventory);
void addBook(theInventory *Inventory);
void changePrice(theInventory *Inventory);
void changeQty(theInventory *Inventory);
void totalQty(theInventory *Inventory);
void calculateTotalAmount(theInventory *Inventory);
Book* initBook(char file[], int fileindex); //��ūȭ
Book* findLast(Book *b);
int searchPerson(theInventory *Inventory, char* Lastname, char* Fristname, int index);

int main()
{
	int flag;
	char* choice;
	theInventory Inventory[20];

	greeting(); //�λ縻
	readDatabase(Inventory); //Inventory �ʱ�ȭ �� ����
	flag = 1;
	while (flag) { //�Է��Ѽ����� �޴��� ����
		choice = printMenu();
		if (strcmp(choice, "1") == 0)
			displayInventory(Inventory);
		else if (strcmp(choice, "2") == 0)
			displayAuthorsWork(Inventory);
		else if (strcmp(choice, "3") == 0)
			addBook(Inventory);
		else if (strcmp(choice, "4") == 0)
			changePrice(Inventory);
		else if (strcmp(choice, "5") == 0)
			changeQty(Inventory);
		else if (strcmp(choice, "6") == 0)
			totalQty(Inventory);
		else if (strcmp(choice, "7") == 0)
			calculateTotalAmount(Inventory);
		else if (strcmp(choice, "8") == 0) {
			printf("Thank you for using this program\n");
			flag = 0;
		}
		else
			printf("Invalid choice\n");

	}
	return 0;
}

void greeting() {
	printf("Welcome to the bookstore program!\n");
}

void readDatabase(theInventory Inventory[]) {
	FILE* stream = NULL; //���� �������� ����
	int findindex = -1; //���� �̸��� �۰��� ã���� �ش� �۰��� index�� ǥ���� ����
	int index = 0; //Inventory�� index
	int fileindex = 0, arrayindex = 0; //���Ͽ��� char ������ �ѱ��ھ� �޾ƿ��� ���� �ε���
	char filename[20]; //���� �̸��� ���� �迭
	char file[250]; //���Ͽ��� ���پ� �Է¹��� �迭
	while (stream == NULL) { //data.txt �Է� ������ ����ó��
		printf("Enter the name of the file : ");
		gets_s(filename, 20);
		fopen_s(&stream, filename, "r"); //�б��������� �о��
		if (stream == NULL)
			printf("Error reading database!!\n");
	}
	printf("%s open\n", filename);
	while (feof(stream) == NULL) { //���Ͽ��� �Է��� ����������
		fileindex = 0;
		arrayindex = 0;
		fgets(file, 250, stream); //���� ��ü�� file �迭�� �޾ƿ�
		while (file[fileindex] != ',') { // , �� ���������� �ѱ��ھ� lastname�� �־��ִ� loop
			Inventory[index].lastname[arrayindex] = file[fileindex];
			fileindex++; //���� ���ڸ� �б����� ++
			arrayindex++; //���� �ε����� ���ڸ� �����ϱ����� ++
			if (file[fileindex] == ',') {
				Inventory[index].lastname[arrayindex] = '\0'; // , �������� lastname�� ���� �˷��ִ� \0�� �Է�
			}
		}
		fileindex++; //������ �ε����� ��� ����
		arrayindex = 0; //���ο� �迭�� �����ؾ� �ǹǷ� 0���� �ʱ�ȭ
		while (file[fileindex] != ',') {  // , �� ���������� �ѱ��ھ� firstname�� �־��ִ� loop
			Inventory[index].firstname[arrayindex] = file[fileindex];
			fileindex++; //���� ���ڸ� �б����� ++
			arrayindex++; //���� �ε����� ���ڸ� �����ϱ����� ++
			if (file[fileindex] == ',') {
				Inventory[index].firstname[arrayindex] = '\0'; // , �������� lastname�� ���� �˷��ִ� \0�� �Է�
			}
		}
		fileindex++; //������ �ε����� ��� ����
		//�Ŀ� initBook �Լ������� Book�� ����Լ����� ���� ��ũ������ ����

		findindex = searchPerson(Inventory, Inventory[index].lastname, Inventory[index].firstname, index - 1); //��� �ִ���Ȯ�� ������ �ε��� ��ȯ
		Book *book = (Book *)malloc(sizeof(Book)); //å�ѱ� �����Ҵ�
		book = initBook(file, fileindex); //å ���� �ʱ�ȭ

		if (findindex == -1) { //�������
			(Inventory + index)->link = book; //�ش� ����� link = book
			index++; //inventory[index]++
		}
		else { //�۰��� ����
			Book *Last = findLast((Inventory + findindex)->link); //�۰��� ������ book �� ã�Ƽ� last�� ����
			Last->next = book; //�ǵڿ� ����
		}

		Inventory[index] = { '\0' , }; //�ش� �۰��� �����ÿ� inventory[index]�� ������ ���Ƿ� �ʱ�ȭ
		//puts(file);
	}
}

char* printMenu() { //�޴����
	char* choice = (char *)malloc(sizeof(char) * 10);
	printf("Enter 1 to display the inventory\n");
	printf("Enter 2 to display the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to change the price\n");
	printf("Enter 5 to change the qty on hand\n");
	printf("Enter 6 to view the total number of books in the inventory\n");
	printf("Enter 7 to see the total amount of the entire inventory\n");
	printf("Enter 8 to exit\n");
	printf("Enter your choice : ");
	gets_s(choice, 10);
	return choice;
}

void displayInventory(theInventory Inventory[]) { //inventory ���� ���
	int index = 0;
	printf("displayInventory\n");
	while ((Inventory + index)->link != NULL) { //inventory �迭�� index�� ������Ű�� Inventory->link�� ���� NULL�϶� ��� ����
		printf("\nThe author is : %s %s\n\n", Inventory[index].lastname, Inventory[index].firstname);
		Book* p = (Inventory + index)->link; //�۰��� ù��° book�� ����Ű�� p
		while (p != NULL) { //p �� ���� �ƴҶ����� �̵��ϸ� ���
			printf("The title is : %s\n", p->title);
			printf("The qty is: %s\n", p->qty);
			printf("The price is : %.4s\n", p->price);
			printf("\n----\n");
			p = p->next;
		}
		index++;
	}
}

void displayAuthorsWork(theInventory *Inventory) {
	printf("displayAuthorWork\n");
}

void addBook(theInventory *Inventory) {
	printf("addBook\n");
}

void changePrice(theInventory *Inventory) {
	printf("changePrice\n");
}

void changeQty(theInventory *Inventory) {
	printf("changeQty\n");
}

void totalQty(theInventory *Inventory) {
	printf("totalQty\n");
}

void calculateTotalAmount(theInventory *Inventory) {
	printf("calculateTotalAmount\n");
}

Book* initBook(char file[], int fileindex) { //Book ���� �ʱ�ȭ �̸��� ������ fileindex�� �޾ƿ� �� �ĺ��� char�� �ϳ��� �Է�
	Book *_new = (Book *)malloc(sizeof(Book)); //Book* �� ���� �ʱ�ȭ
	_new->next = NULL;
	int index = 0;
	while (file[fileindex] != ',') {  // , �� ���������� �ѱ��ھ� title�� �־��ִ� loop
		_new->title[index] = file[fileindex];
		fileindex++;
		index++;
		if (file[fileindex] == ',') { // , �������� lastname�� ���� �˷��ִ� \0�� �Է�
			_new->title[index] = '\0';
		}
	}
	fileindex++;
	index = 0;
	while (file[fileindex] != ',') { // , �� ���������� �ѱ��ھ� qty�� �־��ִ� loop
		_new->qty[index] = file[fileindex];
		fileindex++;
		index++;
		if (file[fileindex] == ',') { // , �������� lastname�� ���� �˷��ִ� \0�� �Է�
			_new->qty[index] = '\0';
		}
	}
	fileindex++;
	index = 0;
	while (file[fileindex] != '\n') {// , �� ���������� �ѱ��ھ� price�� �־��ִ� loop
		_new->price[index] = file[fileindex];
		fileindex++;
		index++;
		if (file[fileindex] == '\n') { // , �������� lastname�� ���� �˷��ִ� \0�� �Է�
			_new->price[index] = '\0';
		}
	}
	return _new;
}

Book *findLast(Book *b) { //�ش� �۰��� ������ Book* �� ��ȯ���ִ� �Լ�
	if (b == NULL) {}
	else {
		while (b->next != NULL) {
			b = b->next;
		}
	}
	return b;
}

//Lastname �� Fristname�� �ԷµǾ����� Inventory�� �ε����� (�����ε��� - 1)���� 1�� ���ҽ�Ű��
//Lastname �� Fristname�� ��� ������ index�� ��ȯ�ϴ� �Լ�
//�����ÿ� -1 ��ȯ
int searchPerson(theInventory *Inventory, char *Lastname, char* Fristname, int index) {
	theInventory *p = NULL;
	while (index >= 0) {
		if (strcmp(Inventory[index].lastname, Lastname) == 0 && strcmp(Inventory[index].firstname, Fristname) == 0) {
			p = &Inventory[index];
			return index;
		}
		index--;
	}
	return index;
}