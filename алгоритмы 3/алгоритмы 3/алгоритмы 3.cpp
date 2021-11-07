#include <iostream>
using namespace std;    

int main()
{
	string email_address;
	bool flag = false;
	setlocale(LC_ALL, "Russian");
	cout << "Введите адрес почты: ";
	cin >> email_address;
	int size = email_address.size();
	for (int i=0; i<size; i++)
	{
		if (email_address[i] == '@') flag = true;
		if (email_address[i+1] == '.' && flag)
		{
			if (email_address[i] == '-') {
				cout << "Некоректный ввод";
				return 0;
			}
		}
	}
	cout << "Корректный ввод";
	return 0;
}
