#include <fstream>
#include <iostream>

using namespace std;

struct Book
{
	int registration_number;
	int id;
	char author[25];
	char title[15];
	int publication_year;
};

Book* input_file(int quantity) //создание файла
{
	Book* InformationOfBooks = new Book[quantity]{};
	ifstream f;
	f.open("tukva.txt"); //открытие файла
	if (f.is_open()) {
		for (int i = 0; i < quantity; i++) {
			f >> InformationOfBooks[i].registration_number;
			f >> InformationOfBooks[i].id;
			f >> InformationOfBooks[i].author;
			f >> InformationOfBooks[i].title;
			f >> InformationOfBooks[i].publication_year;
		}
	}
	f.close(); //закрытие файла
	return InformationOfBooks;
}

Book* sort(Book* InformationOfBooks, int quantity)
{
	for (int i = 0; i < quantity; i++) {
		for (int j = 0; j < quantity - 1; j++) {
			if (InformationOfBooks[j].registration_number > InformationOfBooks[j + 1].registration_number) {
				int temp = InformationOfBooks[j].registration_number;
				InformationOfBooks[j].registration_number = InformationOfBooks[j + 1].registration_number;
				InformationOfBooks[j + 1].registration_number = temp;
			}
		}
	}
	return InformationOfBooks;
}

void output_console(Book* InformationOfBooks, int quantity)
{
	for (int i = 0; i < quantity; i++) {
		cout << "registration_number: " << InformationOfBooks[i].registration_number << " | id: "
		<< InformationOfBooks[i].id << " | author: " << InformationOfBooks[i].author << " | title: "
		<< InformationOfBooks[i].title << " | publication_year: " << InformationOfBooks[i].publication_year << endl;
	}
}

int Search_Binary(Book* InformationOfBooks, int left, int right, int key)
{
	int midd = 0;
	while (true) {
		midd = (left + right) / 2;
		if (key < InformationOfBooks[midd].registration_number) right = midd - 1; //смещаем правую границу поиска
		else if (key > InformationOfBooks[midd].registration_number) left = midd + 1; //смещаем левую границу поиска
		else return midd;
		if (left > right) return -1; //если границы сомкнулись 
	}
}

void binary_output_file(Book* InformationOfBooks, int quantity)
{
	ofstream f("tukva.bin", ios::out | ios::binary);

	//FILE *f;
	//f = fopen( "D:\\Уник, учебники и важная фегня\\3 семестр\\Алгоритмические основы обработки данных\\Алгоритмы 4\\Алгоритмы 4\\tukva.dat", "w+" );

	f.write((char*)&quantity, sizeof(int));
	if (f.is_open()) {
		for (int i = 0; i < quantity; i++) {
			f.write((char*)&(InformationOfBooks[i].registration_number), sizeof(int));
			f.write((char*)&(InformationOfBooks[i].id), sizeof(int));
			int author_size = strlen(InformationOfBooks[i].author) + 1;
			f.write((char*)&(author_size), sizeof(int));
			char* cstr1 = new char[author_size];
			strcpy_s(cstr1, author_size, InformationOfBooks[i].author);
			f.write(cstr1, author_size);
			int title_size = strlen(InformationOfBooks[i].title) + 1;
			f.write((char*)&(title_size), sizeof(int));
			char* cstr = new char[title_size];
			strcpy_s(cstr, title_size, InformationOfBooks[i].title);
			f.write(cstr, title_size);
			f.write((char*)&(InformationOfBooks[i].publication_year), sizeof(int));
		}
	}
	f.close();
}

void binary_input_file(Book* sub_InformationOfBooks, int quantity)
{
	Book* InformationOfBooks = new Book[quantity];
	ifstream f2("tukva.bin", ios::in | ios::binary);
	f2.read((char*)&quantity, sizeof(int));
	if (f2.is_open()) {
		for (int i = 0; i < quantity; i++) {
			f2.read((char*)&(InformationOfBooks[i].registration_number), sizeof(int));
			f2.read((char*)&(InformationOfBooks[i].id), sizeof(int));
			int author_size = strlen(sub_InformationOfBooks[i].author) + 1;
			f2.read((char*)&(author_size), sizeof(int));
			char* cstr1 = new char[author_size];
			f2.read(cstr1, author_size);
			strcpy_s(InformationOfBooks[i].author, author_size, cstr1);
			int title_size = strlen(sub_InformationOfBooks[i].title) + 1;
			f2.read((char*)&(title_size), sizeof(int));
			char* cstr = new char[title_size];
			f2.read(cstr, title_size);
			strcpy_s(InformationOfBooks[i].title, title_size, cstr);
			f2.read((char*)&(InformationOfBooks[i].publication_year), sizeof(int));
			InformationOfBooks[i].publication_year = 0;
		}
	}
	f2.close();
	for (int i = 0; i < quantity; i++) {
		cout << "registration_number: " << InformationOfBooks[i].registration_number << " | id: "
		<< InformationOfBooks[i].id << " | author: " << InformationOfBooks[i].author << " | title: "
		<< InformationOfBooks[i].title << " | publication_year: " << InformationOfBooks[i].publication_year << endl;
	}
}

int main()
{
	cout << "Quantity of structs? " << endl;
	int quantity;
	cin >> quantity;
	Book* pointer = input_file(quantity);
	//Book* pointer_for_binary_out;
	pointer = sort(pointer, quantity);
	output_console(pointer, quantity);
	int key = 0;
	cout << "What key? " << endl;
	cin >> key;
	const int result_binary_search = Search_Binary(pointer, 0, quantity, key);
	if (result_binary_search != -1) cout << "Index of this key: " << result_binary_search << endl;
	else cout << "This key is Not found! " << endl;
	binary_output_file(pointer, quantity);
	binary_input_file(pointer, quantity);
	return 0;
}