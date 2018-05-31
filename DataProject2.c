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

void greeting(); //�λ�
void readDatabase(theInventory Inventory[]); //inventory ����
char* printMenu(); //�޴� ���
void displayInventory(theInventory Inventory[]); //���
void displayoneInventory(theInventory Inventory); //���۰��� ���ĵ� ���
void displayAuthorsWork(theInventory *Inventory); //Ư�� �۰� ��ǰ ��������� ���
void addBook(theInventory *Inventory);// ���ο� ���� ���� �Է�
void changePrice(theInventory *Inventory); //Ư�� ������ ���� ���� ����
void changeQty(theInventory *Inventory); //Ư�� ������ ������ ����
void whatPrice(char price[25]); //���� ���� �Է�, ����ó��
void whatQty(char qty[25]); //���� ������ �Է�, ����ó��
void totalQty(theInventory *Inventory); //��� �ִ� ��ü ������ ��� ���� ���
void calculateTotalAmount(theInventory *Inventory); //����� �����鿡 ���� ��ü ���� ���
Book* initBook(char file[], int fileindex); //��ūȭ
void createBook(Book* book, char *title, char* qty, char* price); //å ������ �־����� �ϳ� ����
Book* findLast(Book *b); //�ش� �۰��� ������ å�� ��ȯ
int searchPerson(theInventory *Inventory, char* name, int index); //���ϴ� �۰� �˻�
Book* findBook(theInventory Inventory, char *bookname); //Ư�� ������ �����ϴ��� ����
int findPerson(theInventory *Inventory, char *name); //�ش� �۰��� �����ϴ���, ���ϸ� -1 ��ȯ, �ϸ� �ش� index ��ȯ
void makeFullname(char* lastname, char* firstname, char* fullname); //��ҹ��� ���� �� Ǯ���� ����
void makeTitle(char *title); //������ ��ҹ��� ����
Book bookcopy(Book* book);

int main()
{
	int flag;
	char* choice;
	theInventory Inventory[30];
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
	char name[100];
	int i; //�ݺ�������
	int index = 0; //inventory index
	int findindex = -1; //���� �̸��� �۰��� ã���� �ش� �۰��� index�� ǥ���� ����
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
	for (i = 0; i < 30; i++) Inventory[i].link = NULL; //link �ʱ�ȭ
	while (feof(stream) == 0) { //���Ͽ��� �Է��� ����������
		fileindex = 0;
		arrayindex = 0;
		fgets(file, 250, stream); //���� ��ü�� file �迭�� �޾ƿ�
		while (1) { // , �� ���������� �ѱ��ھ� lastname�� �־��ִ� loop
			if (file[fileindex] == ',') {
				name[arrayindex] = ' ';
				fileindex++;
				arrayindex++;
				break;
			} //, ������ name �� �������
			else {
				name[arrayindex] = file[fileindex];
				fileindex++; //���� ���ڸ� �б����� ++
				arrayindex++; //���� �ε����� ���ڸ� �����ϱ����� ++
			}
		}

		while (1) {  // , �� ���������� �ѱ��ھ� firstname�� �־��ִ� loop
			if (file[fileindex] == ',') {
				fileindex++;
				name[arrayindex] = '\0'; //�̸��� ���� ������ �ι���
				break;
			} //, ������ fileindex�� �����Ͽ� ,�� fullname���� �ȵ�����
			else {
				name[arrayindex] = file[fileindex];
				fileindex++; //���� ���ڸ� �б����� ++
				arrayindex++; //���� �ε����� ���ڸ� �����ϱ����� ++
			}
		}

		//������ - initBook �Լ������� Book�� ����Լ����� ���� ��ũ������ ����
		if (index > 0) {
			findindex = searchPerson(Inventory, name, index - 1); //��� �ִ���Ȯ�� ������ �ε��� ��ȯ}
		}
		Book *book = (Book *)malloc(sizeof(Book)); //å�ѱ� �����Ҵ�
		book = initBook(file, fileindex); //å ���� �ʱ�ȭ


		if (findindex == -1) { //�������
			strcpy_s(Inventory[index].FullName, strlen(name) + 1, name);
			(Inventory + index)->link = book; //�ش� ����� link = book
			index++; //inventory[index]++
		}
		else { //�۰��� ����
			Book *Last = findLast((Inventory + findindex)->link); //�۰��� ������ book �� ã�Ƽ� last�� ����
			Last->next = book; //�ǵڿ� ����
		}
	}
	fclose(stream);
}

char* printMenu() { //�޴����
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

void displayInventory(theInventory Inventory[]) { //inventory ���� ���
	int index = 0;
	int i;
	int pointindex = -1;
	printf("displayInventory\n");
	while (Inventory[index].link != NULL) { //inventory �迭�� index�� ������Ű�� Inventory->link�� ���� NULL�϶� ��� ����
		printf("\nThe author is : %s\n", Inventory[index].FullName);
		Book* p = (Inventory + index)->link; //�۰��� ù��° book�� ����Ű�� p
		while (p != NULL) { //p �� ���� �ƴҶ����� �̵��ϸ� ���
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

void displayAuthorsWork(theInventory *Inventory) {//Ư�� �۰� ��ǰ ��������� ���
	char lastname[50];
	char firstname[50];
	char fullname[100];
	Book* onebook;
	Book book[20];
	Book temp;
	int personindex = -1; //�۰��� index
	int index;
	int i, j; //�ݺ��� ����
	int pointindex = -1;
	printf("displayAuthorWork\n");
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //�̸� �Է�
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //�� �Է�
	makeFullname(lastname, firstname, fullname); //��ҹ��� ����

	personindex = findPerson(Inventory, fullname); //�۰� �˻�
	if (personindex == -1) {
		printf("No such author in your database.\n");
		return; //�۰��� ������
	}
	else { //���� ��
		onebook = Inventory[personindex].link;
		index = 0;
		//strcmp(str1,str2) str1�� ũ�� ���, str2�� ũ�� ����, ������ �����ȯ
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
		//���
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
	gets_s(firstname, 50); //�̸� �Է�
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //�� �Է�
	makeFullname(lastname, firstname, fullname); //��ҹ��� ����
	personindex = findPerson(Inventory, fullname); //�۰� �˻�
	if (personindex == -1) {  //�۰��� ������
		printf("Enter the title : ");
		gets_s(title, 100);
		makeTitle(title);
		whatQty(qty);
		whatPrice(price);
		book = (Book *)malloc(sizeof(Book)); //å�ѱ� �����Ҵ�
		createBook(book, title, qty, price);
		strcpy_s(Inventory[index].FullName, strlen(fullname) + 1, fullname);
		Inventory[index].link = book;
		index++;
	}
	else { //���� ��
		printf("Find author! Enter the title : ");
		gets_s(title, 100);
		makeTitle(title);
		book = findBook(Inventory[personindex], title);
		if (book == NULL) { //���ο� å�϶�
			whatQty(qty);
			whatPrice(price);
			book = (Book *)malloc(sizeof(Book)); //å�ѱ� �����Ҵ�
			createBook(book, title, qty, price);
			lastbook = findLast((Inventory + personindex)->link);
			lastbook->next = book;
		}
		else { //�̹� �����ϴ� å�϶�
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
	Book* book; //���ݺ����� ���ϴ� å
	int personindex = -1; //�۰��� index
	int i; //�ݺ��� ����
	printf("changePrice\n");
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //�̸� �Է�
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //�� �Է�
	makeFullname(lastname, firstname, fullname); //��ҹ��� ����

	personindex = findPerson(Inventory, fullname); //�۰� �˻�
	if (personindex == -1) {
		printf("No such author in your database. So you cannot chancge the price\n");
		return; //�۰��� ������
	}
	else { //���� ��
		printf("Enter the title:");
		gets_s(title, 100); //å���� �Է�
		makeTitle(title); //��ҹ��� ����

		book = findBook(Inventory[personindex], title);
		if (book == NULL) {
			printf("No book with the title %s by %s,%s\n", title, lastname, firstname);
			return; //å�� ������
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
	Book* book; //���ݺ����� ���ϴ� å
	int personindex = -1; //�۰��� index
	int i; //�ݺ��� ����
	printf("changeQty\n");
	printf("Enter the author's first name:");
	gets_s(firstname, 50); //�̸� �Է�
	printf("Enter the author's last name:");
	gets_s(lastname, 50); //�� �Է�
	makeFullname(lastname, firstname, fullname); //��ҹ��� ����

	personindex = findPerson(Inventory, fullname); //�۰� �˻�
	if (personindex == -1) {
		printf("No such author in your database. So you cannot chancge the price\n");
		return; //�۰��� ������
	}
	else { //���� ��
		printf("Enter the title:");
		gets_s(title, 100); //å���� �Է�
		makeTitle(title); //��ҹ��� ����

		book = findBook(Inventory[personindex], title);
		if (book == NULL) {
			printf("No book with the title %s by %s,%s\n", title, lastname, firstname);
			return; //å�� ������
		}
		else {
			whatQty(qty);
			printf("Qty will be updated from %s to %s\n", book->qty, qty);
			strcpy_s(book->qty, 25, qty);
		}
	}
}

void totalQty(theInventory *Inventory) {//��� �ִ� ��ü ������ ��� ���� ���
	int totalqty = 0; //�Ѽ���
	int qty; //�ѱ��� ����
	int index = 0;
	while (Inventory[index].link != NULL) {
		Book* p = (Inventory + index)->link; //�۰��� ù��° book�� ����Ű�� p
		while (p != NULL) { //p �� ���� �ƴҶ����� �̵��ϸ� ���
			qty = atoi(p->qty);
			totalqty += qty;
			p = p->next;
		}
		index++;
	}
	printf("The total number of books is : %d\n", totalqty);
}

void calculateTotalAmount(theInventory *Inventory) {
	double totalprice = 0; //�� ����
	double price; //å �ѱ��� ����
	int index = 0;
	while (Inventory[index].link != NULL) {
		Book* p = (Inventory + index)->link; //�۰��� ù��° book�� ����Ű�� p
		while (p != NULL) { //p �� ���� �ƴҶ����� �̵��ϸ� ���
			price = atof(p->price);
			totalprice += price;
			p = p->next;
		}
		index++;
	}
	printf("The total value of the inventory is : $%.2f\n", totalprice);
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

void createBook(Book* book, char *title, char* qty, char* price) {
	strcpy_s(book->title, strlen(title) + 1, title);
	strcpy_s(book->qty, strlen(qty) + 1, qty);
	strcpy_s(book->price, strlen(price) + 1, price);
	book->next = NULL;
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
	p = Inventory.link; //�۰��� ù��° å
	while (1) {
		if (strcmp(p->title, bookname) == 0) { //å ������ �߰��ϸ�
			return p;
		}
		else {
			p = p->next; // ���� å
		}

		if (p == NULL) //å�� �߰� ��������
			return NULL;//�߰߸��ϸ� NULL ��ȯ
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
		for (i = 0; i < 25; i++) check[i] = '\0'; //Ȯ���� ���� ��� -1�� �ʱ�ȭ

		printf("Enter the price:");
		gets_s(price, 25);

		for (i = 0; i < strlen(price); i++) check[i] = price[i]; //price�� ���� check�� ����

		for (i = 0; i < strlen(price); i++) { //. �� �ִ� index ����
			if (price[i] == '.' && pointindex == -1) {
				pointindex = i;
			}
			else { //.�� ������ ���ڰ� �ƴҶ� ����ó��
				if (price[i] < '0' || price[i] > '9') {
					pointindex = -1;
					strcpy_s(price, 25, "\0");
					break;
				}
			}
		}
		//�Ҽ��� ���ڸ��� �ƴҶ�
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
	int check; // ����ó�� ��������
	while (1) {
		check = 1; //1 ���� ���� ������ ���ܾ���
		printf("Enter the qty:");
		gets_s(qty, 25);
		for (i = 0; i < strlen(qty); i++) { //�ϳ��ϳ� ���� Ȯ��
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
	if (firstname[0] >= 'a' && firstname[0] <= 'z') firstname[0] -= 32; //ù�ڴ� �빮�ڷ�
	for (i = 1; i < strlen(firstname) + 1; i++) { //�ҹ��ڷ� ġȯ
		if (firstname[i] >= 'A' && firstname[i] <= 'Z')
			firstname[i] += 32;
	}

	if (lastname[0] >= 'a' && lastname[0] <= 'z') lastname[0] -= 32; //ù�ڴ� �빮�ڷ�
	for (i = 1; i < strlen(lastname) + 1; i++) { //�ҹ��ڷ� ġȯ
		if (lastname[i] >= 'A' && lastname[i] <= 'Z')
			lastname[i] += 32;
	}
	strcpy_s(fullname, strlen(lastname) + 1, lastname); //�۰��� �̸��� fullname ����
	strcat_s(fullname, 100, " ");
	strcat_s(fullname, 100, firstname);

}
void makeTitle(char *title) {
	int i;
	if (title[0] >= 'a' && title[0] <= 'z') title[0] -= 32; //ù�ڴ� �빮�ڷ�}
	for (i = 1; i < strlen(title) + 1; i++) { //�ҹ��ڷ� ġȯ
		if (title[i] == ' ') { //������ ������ �������ڸ� �빮�ڷ�
			if (title[i + 1] >= 'a' && title[i + 1] <= 'z') title[i + 1] -= 32;
			i++;
		}
		else if (title[i] >= 'A' && title[i] <= 'Z') //�ٸ� ���ڵ��� ��� �ҹ��ڷ�
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