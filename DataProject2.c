#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct theInventory {
	char FullName[100];
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
void displayInventory(theInventory Inventory[]); //출력
void displayoneInventory(theInventory Inventory); //한작가의 정렬된 출력
void displayAuthorsWork(theInventory *Inventory); //특정 작가 작품 제목순으로 출력
void addBook(theInventory *Inventory);// 새로운 서적 정보 입력
void changePrice(theInventory *Inventory); //특정 서적의 가격 정보 변경
void changeQty(theInventory *Inventory); //특성 서적의 재고숫자 변경
void whatPrice(char price[25]); //변경 가격 입력, 예외처리
void whatQty(char qty[25]); //변경 재고수량 입력, 예외처리
void totalQty(theInventory *Inventory); //재고에 있는 전체 서적의 재고 숫자 출력
void calculateTotalAmount(theInventory *Inventory); //재고의 서적들에 대한 전체 가격 출력
Book* initBook(char file[], int fileindex); //토큰화
void createBook(Book* book, char *title, char* qty, char* price); //책 정보를 주었을때 하나 생성
Book* findLast(Book *b); //해당 작가의 마지막 책을 반환
int searchPerson(theInventory *Inventory, char* name, int index); //원하는 작가 검색
Book* findBook(theInventory Inventory, char *bookname); //특정 서적이 존재하는지 여부
int findPerson(theInventory *Inventory, char *name); //해당 작가가 존재하는지, 안하면 -1 반환, 하면 해당 index 반환
void makeFullname(char* lastname, char* firstname, char* fullname); //대소문자 생성 및 풀네임 생성
void makeTitle(char *title); //제목의 대소문자 변경
Book bookcopy(Book* book);

int main()
{
	int flag;
	char* choice;
	theInventory Inventory[30];
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
	char name[100];
	int i; //반복문변수
	int index = 0; //inventory index
	int findindex = -1; //같은 이름의 작가를 찾을때 해당 작가의 index를 표현할 변수
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
	for (i = 0; i < 30; i++) Inventory[i].link = NULL; //link 초기화
	while (feof(stream) == 0) { //파일에서 입력이 없을때까지
		fileindex = 0;
		arrayindex = 0;
		fgets(file, 250, stream); //한줄 전체를 file 배열에 받아옴
		while (1) { // , 를 만날때까지 한글자씩 lastname에 넣어주는 loop
			if (file[fileindex] == ',') {
				name[arrayindex] = ' ';
				fileindex++;
				arrayindex++;
				break;
			} //, 만나면 name 에 공백삽입
			else {
				name[arrayindex] = file[fileindex];
				fileindex++; //다음 글자를 읽기위해 ++
				arrayindex++; //다음 인덱스에 글자를 저장하기위해 ++
			}
		}

		while (1) {  // , 를 만날때까지 한글자씩 firstname에 넣어주는 loop
			if (file[fileindex] == ',') {
				fileindex++;
				name[arrayindex] = '\0'; //이름의 끝을 만나면 널문자
				break;
			} //, 만나면 fileindex만 증가하여 ,가 fullname에는 안들어오게
			else {
				name[arrayindex] = file[fileindex];
				fileindex++; //다음 글자를 읽기위해 ++
				arrayindex++; //다음 인덱스에 글자를 저장하기위해 ++
			}
		}

		//앞으로 - initBook 함수를통해 Book의 멤버함수에도 같은 테크닉으로 저장
		if (index > 0) {
			findindex = searchPerson(Inventory, name, index - 1); //사람 있는지확인 있으면 인덱스 반환}
		}
		Book *book = (Book *)malloc(sizeof(Book)); //책한권 동적할당
		book = initBook(file, fileindex); //책 정보 초기화


		if (findindex == -1) { //사람없음
			strcpy_s(Inventory[index].FullName, strlen(name) + 1, name);
			(Inventory + index)->link = book; //해당 사람의 link = book
			index++; //inventory[index]++
		}
		else { //작가가 있음
			Book *Last = findLast((Inventory + findindex)->link); //작가의 마지막 book 을 찾아서 last에 저장
			Last->next = book; //맨뒤에 삽입
		}
	}
	fclose(stream);
}

char* printMenu() { //메뉴출력
	char* choice = (char *)malloc(sizeof(char) * 10);
	printf("\nEnter 1 to display the inventory\n");
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
	int i;
	int pointindex = -1;
	printf("displayInventory\n");
	while (Inventory[index].link != NULL) { //inventory 배열의 index를 증가시키며 Inventory->link의 값이 NULL일때 출력 종료
		printf("\nThe author is : %s\n", Inventory[index].FullName);
		Book* p = (Inventory + index)->link; //작가의 첫번째 book을 가리키는 p
		while (p != NULL) { //p 가 끝이 아닐때까지 이동하며 출력
			printf("The title is : %s\n", p->title);
			printf("The qty is: %s\n", p->qty);
			printf("The price is : ");
			for (i = 0; i < 25; i++) {
				if (p->price[i] == '.') { pointindex = i; break; }
			}
			for (i = 0; i < pointindex + 3; i++) {
				printf("%c", p->price[i]);
			}
			printf("\n\n----\n");
			p = p->next;
		}
		index++;
	}
}

void displayAuthorsWork(theInventory *Inventory) {//특정 작가 작품 제목순으로 출력
	char lastname[50];
	char firstname[50];
	char fullname[100];
	Book* onebook;
	Book book[20];
	Book temp;
	int personindex = -1; //작가의 index
	int index;
	int i, j; //반복문 변수
	int pointindex = -1;
	printf("displayAuthorWork\n");
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //이름 입력
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //성 입력
	makeFullname(lastname, firstname, fullname); //대소문자 구분

	personindex = findPerson(Inventory, fullname); //작가 검색
	if (personindex == -1) {
		printf("No such author in your database.\n");
		return; //작가가 없을때
	}
	else { //있을 때
		onebook = Inventory[personindex].link;
		index = 0;
		//strcmp(str1,str2) str1이 크면 양수, str2가 크면 음수, 같으면 양수반환
		while (1) {
			book[index] = bookcopy(onebook);
			index++;
			if (onebook->next == NULL) break;
			onebook = onebook->next;
		}

		for (i = 0; i < index; i++) {
			for (j = 0; j < (index - 1 - i); j++) {
				if (strcmp(book[j].title, book[j + 1].title) > 0) {
					temp = bookcopy(&book[j]);
					book[j] = bookcopy(&book[j + 1]);
					book[j + 1] = bookcopy(&temp);
				}
			}
		}
		//출력
		printf("\nThe author is : %s\n", Inventory[personindex].FullName);
		for (i = 0; i < index; i++) {
			printf("The title is : %s\n", book[i].title);
			printf("The qty is: %s\n", book[i].qty);
			printf("The price is : ");
			for (j = 0; j < 25; j++) {
				if (book[i].price[j] == '.') { pointindex = j; break; }
			}
			for (j = 0; j < pointindex + 3; j++) {
				printf("%c", book[i].price[j]);
			}
			printf("\n\n----\n");
		}
	}

}

void addBook(theInventory *Inventory) {
	int index = 0;
	int personindex = -1;
	char lastname[50];
	char firstname[50];
	char fullname[100];
	char title[100];
	char qty[25];
	char price[25];
	Book* book = NULL;
	Book* lastbook = NULL;
	printf("addBook\n");
	while (Inventory[index].link != NULL) {
		index++;
	}
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //이름 입력
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //성 입력
	makeFullname(lastname, firstname, fullname); //대소문자 구분
	personindex = findPerson(Inventory, fullname); //작가 검색
	if (personindex == -1) {  //작가가 없을때
		printf("Enter the title : ");
		gets_s(title, 100);
		makeTitle(title);
		whatQty(qty);
		whatPrice(price);
		book = (Book *)malloc(sizeof(Book)); //책한권 동적할당
		createBook(book, title, qty, price);
		strcpy_s(Inventory[index].FullName, strlen(fullname) + 1, fullname);
		Inventory[index].link = book;
		index++;
	}
	else { //있을 때
		printf("Find author! Enter the title : ");
		gets_s(title, 100);
		makeTitle(title);
		book = findBook(Inventory[personindex], title);
		if (book == NULL) { //새로운 책일때
			whatQty(qty);
			whatPrice(price);
			book = (Book *)malloc(sizeof(Book)); //책한권 동적할당
			createBook(book, title, qty, price);
			lastbook = findLast((Inventory + personindex)->link);
			lastbook->next = book;
		}
		else { //이미 존재하는 책일때
			printf("This book is already in the Inventory and cannot be added again");
		}
	}
	printf("\n\n");
}

void changePrice(theInventory *Inventory) {
	char lastname[50];
	char firstname[50];
	char fullname[100];
	char title[100];
	char price[25];
	Book* book; //가격변경을 원하는 책
	int personindex = -1; //작가의 index
	int i; //반복문 변수
	printf("changePrice\n");
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //이름 입력
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //성 입력
	makeFullname(lastname, firstname, fullname); //대소문자 구분

	personindex = findPerson(Inventory, fullname); //작가 검색
	if (personindex == -1) {
		printf("No such author in your database. So you cannot chancge the price\n");
		return; //작가가 없을때
	}
	else { //있을 때
		printf("Enter the title:");
		gets_s(title, 100); //책제목 입력
		makeTitle(title); //대소문자 구분

		book = findBook(Inventory[personindex], title);
		if (book == NULL) {
			printf("No book with the title %s by %s,%s\n", title, lastname, firstname);
			return; //책이 없을때
		}
		else {
			whatPrice(price);
			printf("Price will be updated from %s to %s\n", book->price, price);
			strcpy_s(book->price, 25, price);
		}
	}
}

void changeQty(theInventory *Inventory) {
	char lastname[50];
	char firstname[50];
	char fullname[100];
	char title[100];
	char qty[25];
	Book* book; //가격변경을 원하는 책
	int personindex = -1; //작가의 index
	int i; //반복문 변수
	printf("changeQty\n");
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //이름 입력
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //성 입력
	makeFullname(lastname, firstname, fullname); //대소문자 구분

	personindex = findPerson(Inventory, fullname); //작가 검색
	if (personindex == -1) {
		printf("No such author in your database. So you cannot chancge the price\n");
		return; //작가가 없을때
	}
	else { //있을 때
		printf("Enter the title:");
		gets_s(title, 100); //책제목 입력
		makeTitle(title); //대소문자 구분

		book = findBook(Inventory[personindex], title);
		if (book == NULL) {
			printf("No book with the title %s by %s,%s\n", title, lastname, firstname);
			return; //책이 없을때
		}
		else {
			whatQty(qty);
			printf("Qty will be updated from %s to %s\n", book->qty, qty);
			strcpy_s(book->qty, 25, qty);
		}
	}
}

void totalQty(theInventory *Inventory) {//재고에 있는 전체 서적의 재고 숫자 출력
	int totalqty = 0; //총수량
	int qty; //한권의 수량
	int index = 0;
	while (Inventory[index].link != NULL) {
		Book* p = (Inventory + index)->link; //작가의 첫번째 book을 가리키는 p
		while (p != NULL) { //p 가 끝이 아닐때까지 이동하며 출력
			qty = atoi(p->qty);
			totalqty += qty;
			p = p->next;
		}
		index++;
	}
	printf("The total number of books is : %d\n", totalqty);
}

void calculateTotalAmount(theInventory *Inventory) {
	double totalprice = 0; //총 가격
	double price; //책 한권의 가격
	int index = 0;
	while (Inventory[index].link != NULL) {
		Book* p = (Inventory + index)->link; //작가의 첫번째 book을 가리키는 p
		while (p != NULL) { //p 가 끝이 아닐때까지 이동하며 출력
			price = atof(p->price);
			totalprice += price;
			p = p->next;
		}
		index++;
	}
	printf("The total value of the inventory is : $%.2f\n", totalprice);
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

void createBook(Book* book, char *title, char* qty, char* price) {
	strcpy_s(book->title, strlen(title) + 1, title);
	strcpy_s(book->qty, strlen(qty) + 1, qty);
	strcpy_s(book->price, strlen(price) + 1, price);
	book->next = NULL;
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
int searchPerson(theInventory *Inventory, char *name, int index) {
	theInventory *p = NULL;
	while (index >= 0) {
		if (strcmp(Inventory[index].FullName, name) == 0) {
			p = &Inventory[index];
			return index;
		}
		index--;
	}
	return index;
}

Book* findBook(theInventory Inventory, char *bookname) {
	Book* p = NULL;
	p = Inventory.link; //작가의 첫번째 책
	while (1) {
		if (strcmp(p->title, bookname) == 0) { //책 제목을 발견하면
			return p;
		}
		else {
			p = p->next; // 다음 책
		}

		if (p == NULL) //책을 발견 못했을때
			return NULL;//발견못하면 NULL 반환
	}
}

int findPerson(theInventory *Inventory, char *name) {
	int index = 0;
	while (Inventory[index].link != NULL) {
		if (strcmp(Inventory[index].FullName, name) == 0) {
			return index;
		}
		index++;
	}
	return -1;
}

void whatPrice(char price[25]) {
	int i;
	int pointindex;
	char check[25];
	while (1) {
		pointindex = -1;
		for (i = 0; i < 25; i++) check[i] = '\0'; //확인을 위해 모두 -1로 초기화

		printf("Enter the price:");
		gets_s(price, 25);

		for (i = 0; i < strlen(price); i++) check[i] = price[i]; //price의 값을 check에 복사

		for (i = 0; i < strlen(price); i++) { //. 이 있는 index 저장
			if (price[i] == '.' && pointindex == -1) {
				pointindex = i;
			}
			else { //.을 제외한 숫자가 아닐때 예외처리
				if (price[i] < '0' || price[i] > '9') {
					pointindex = -1;
					strcpy_s(price, 25, "\0");
					break;
				}
			}
		}
		//소수점 두자리가 아닐때
		if (pointindex == -1 || check[pointindex + 1] == '\0' || check[pointindex + 2] == '\0' || check[pointindex + 3] != '\0') {
			strcpy_s(price, 25, "\0");
		}
		else {
			return;
		}
		printf("Invalid input for the new price.\n");
	}
}

void whatQty(char qty[25]) {
	int i;
	int check; // 예외처리 성공여부
	while (1) {
		check = 1; //1 에서 변경 없으면 예외없음
		printf("Enter the qty:");
		gets_s(qty, 25);
		for (i = 0; i < strlen(qty); i++) { //하나하나 예외 확인
			if (qty[i] <'0' || qty[i] > '9') {
				check = 0;
			}
		}
		if (check == 1) return;
		printf("Invalid input for the new qty.\n");
	}

}

void makeFullname(char* lastname, char* firstname, char* fullname) {
	int i;
	if (firstname[0] >= 'a' && firstname[0] <= 'z') firstname[0] -= 32; //첫자는 대문자로
	for (i = 1; i < strlen(firstname) + 1; i++) { //소문자로 치환
		if (firstname[i] >= 'A' && firstname[i] <= 'Z')
			firstname[i] += 32;
	}

	if (lastname[0] >= 'a' && lastname[0] <= 'z') lastname[0] -= 32; //첫자는 대문자로
	for (i = 1; i < strlen(lastname) + 1; i++) { //소문자로 치환
		if (lastname[i] >= 'A' && lastname[i] <= 'Z')
			lastname[i] += 32;
	}
	strcpy_s(fullname, strlen(lastname) + 1, lastname); //작가의 이름을 fullname 으로
	strcat_s(fullname, 100, " ");
	strcat_s(fullname, 100, firstname);

}
void makeTitle(char *title) {
	int i;
	if (title[0] >= 'a' && title[0] <= 'z') title[0] -= 32; //첫자는 대문자로}
	for (i = 1; i < strlen(title) + 1; i++) { //소문자로 치환
		if (title[i] == ' ') { //공백을 만나면 다음글자를 대문자로
			if (title[i + 1] >= 'a' && title[i + 1] <= 'z') title[i + 1] -= 32;
			i++;
		}
		else if (title[i] >= 'A' && title[i] <= 'Z') //다른 글자들은 모두 소문자로
			title[i] += 32;
	}
}

Book bookcopy(Book* book) {
	Book b;
	b.next = book->next;
	strcpy_s(b.title, 100, book->title);
	strcpy_s(b.price, 25, book->price);
	strcpy_s(b.qty, 25, book->qty);
	return b;
}