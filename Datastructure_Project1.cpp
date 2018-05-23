// Homework3.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

void greeting(); //인사
void readDatabase(theInventory Inventory[]); //inventory 생성
char* printMenu(); //메뉴 출력
void displayInventory(theInventory Inventory[]);
void displayAuthorsWork(theInventory *Inventory);
void addBook(theInventory *Inventory);
void changePrice(theInventory *Inventory);
void changeQty(theInventory *Inventory);
void totalQty(theInventory *Inventory);
void calculateTotalAmount(theInventory *Inventory);
Book* initBook(char file[], int fileindex); //토큰화
Book* findLast(Book *b);
int searchPerson(theInventory *Inventory, char* Lastname, char* Fristname, int index);

int main()
{
	int flag;
	char* choice;
	theInventory Inventory[20];

	greeting(); //인사말
	readDatabase(Inventory); //Inventory 초기화 및 생성
	flag = 1;
	while (flag) { //입력한숫자의 메뉴를 실행
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
	FILE* stream = NULL; //파일 열기위한 변수
	int findindex = -1; //같은 이름의 작가를 찾을때 해당 작가의 index를 표현할 변수
	int index = 0; //Inventory의 index
	int fileindex = 0, arrayindex = 0; //파일에서 char 형으로 한글자씩 받아오기 위한 인덱스
	char filename[20]; //파일 이름을 받을 배열
	char file[250]; //파일에서 한줄씩 입력받을 배열
	while (stream == NULL) { //data.txt 입력 전까지 예외처리
		printf("Enter the name of the file : ");
		gets_s(filename, 20);
		fopen_s(&stream, filename, "r"); //읽기전용으로 읽어옴
		if (stream == NULL)
			printf("Error reading database!!\n");
	}
	printf("%s open\n", filename);
	while (feof(stream) == NULL) { //파일에서 입력이 없을때까지
		fileindex = 0;
		arrayindex = 0;
		fgets(file, 250, stream); //한줄 전체를 file 배열에 받아옴
		while (file[fileindex] != ',') { // , 를 만날때까지 한글자씩 lastname에 넣어주는 loop
			Inventory[index].lastname[arrayindex] = file[fileindex];
			fileindex++; //다음 글자를 읽기위해 ++
			arrayindex++; //다음 인덱스에 글자를 저장하기위해 ++
			if (file[fileindex] == ',') {
				Inventory[index].lastname[arrayindex] = '\0'; // , 만났을때 lastname의 끝을 알려주는 \0를 입력
			}
		}
		fileindex++; //파일의 인덱스는 계속 증가
		arrayindex = 0; //새로운 배열에 저장해야 되므로 0으로 초기화
		while (file[fileindex] != ',') {  // , 를 만날때까지 한글자씩 firstname에 넣어주는 loop
			Inventory[index].firstname[arrayindex] = file[fileindex];
			fileindex++; //다음 글자를 읽기위해 ++
			arrayindex++; //다음 인덱스에 글자를 저장하기위해 ++
			if (file[fileindex] == ',') {
				Inventory[index].firstname[arrayindex] = '\0'; // , 만났을때 lastname의 끝을 알려주는 \0를 입력
			}
		}
		fileindex++; //파일의 인덱스는 계속 증가
		//후에 initBook 함수를통해 Book의 멤버함수에도 같은 테크닉으로 저장

		findindex = searchPerson(Inventory, Inventory[index].lastname, Inventory[index].firstname, index - 1); //사람 있는지확인 있으면 인덱스 반환
		Book *book = (Book *)malloc(sizeof(Book)); //책한권 동적할당
		book = initBook(file, fileindex); //책 정보 초기화

		if (findindex == -1) { //사람없음
			(Inventory + index)->link = book; //해당 사람의 link = book
			index++; //inventory[index]++
		}
		else { //작가가 있음
			Book *Last = findLast((Inventory + findindex)->link); //작가의 마지막 book 을 찾아서 last에 저장
			Last->next = book; //맨뒤에 삽입
		}

		Inventory[index] = { '\0' , }; //해당 작가가 있을시에 inventory[index]에 정보가 들어가므로 초기화
		//puts(file);
	}
}

char* printMenu() { //메뉴출력
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

void displayInventory(theInventory Inventory[]) { //inventory 정보 출력
	int index = 0;
	printf("displayInventory\n");
	while ((Inventory + index)->link != NULL) { //inventory 배열의 index를 증가시키며 Inventory->link의 값이 NULL일때 출력 종료
		printf("\nThe author is : %s %s\n\n", Inventory[index].lastname, Inventory[index].firstname);
		Book* p = (Inventory + index)->link; //작가의 첫번째 book을 가리키는 p
		while (p != NULL) { //p 가 끝이 아닐때까지 이동하며 출력
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

Book* initBook(char file[], int fileindex) { //Book 정보 초기화 이름을 넣은후 fileindex를 받아와 그 후부터 char형 하나씩 입력
	Book *_new = (Book *)malloc(sizeof(Book)); //Book* 형 변수 초기화
	_new->next = NULL;
	int index = 0;
	while (file[fileindex] != ',') {  // , 를 만날때까지 한글자씩 title에 넣어주는 loop
		_new->title[index] = file[fileindex];
		fileindex++;
		index++;
		if (file[fileindex] == ',') { // , 만났을때 lastname의 끝을 알려주는 \0를 입력
			_new->title[index] = '\0';
		}
	}
	fileindex++;
	index = 0;
	while (file[fileindex] != ',') { // , 를 만날때까지 한글자씩 qty에 넣어주는 loop
		_new->qty[index] = file[fileindex];
		fileindex++;
		index++;
		if (file[fileindex] == ',') { // , 만났을때 lastname의 끝을 알려주는 \0를 입력
			_new->qty[index] = '\0';
		}
	}
	fileindex++;
	index = 0;
	while (file[fileindex] != '\n') {// , 를 만날때까지 한글자씩 price에 넣어주는 loop
		_new->price[index] = file[fileindex];
		fileindex++;
		index++;
		if (file[fileindex] == '\n') { // , 만났을때 lastname의 끝을 알려주는 \0를 입력
			_new->price[index] = '\0';
		}
	}
	return _new;
}

Book *findLast(Book *b) { //해당 작가의 마지막 Book* 를 반환해주는 함수
	if (b == NULL) {}
	else {
		while (b->next != NULL) {
			b = b->next;
		}
	}
	return b;
}

//Lastname 과 Fristname이 입력되었을때 Inventory의 인덱스를 (현재인덱스 - 1)부터 1씩 감소시키며
//Lastname 과 Fristname이 모두 같으면 index를 반환하는 함수
//없을시에 -1 반환
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