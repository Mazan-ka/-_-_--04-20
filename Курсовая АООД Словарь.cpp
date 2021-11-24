#include <iostream>
#include <fstream>

using namespace std;

struct Glossary {
    Glossary(int key, string FIO, string passport_data) {
        this->key = key;
        this->FIO = FIO;
        this->passport_data = passport_data;
    }
    Glossary () {}
    int key;
    string FIO;
    string passport_data;
};

typedef Glossary *P_glossary;

P_glossary* add_item(P_glossary *arr, int size) {
    P_glossary* new_arr = new P_glossary[size+1];
    for (int i = 0; i < size + 1; i++) {
        if (i < size) {
            new_arr[i] = arr[i];
        }
        if (i == size) {
            P_glossary temp = new Glossary(0, "q", "e");
            new_arr[i] = temp;
        } 
    }

    cout << "Enter number of item \n";
    cin >> new_arr[size]->key;
    cout << "Enter FIO of item \n";
    cin >> new_arr[size]->FIO;
    cout << "Enter passport data of item \n";
    cin >> new_arr[size]->passport_data;
    return new_arr;
}

P_glossary* delete_item(P_glossary* arr, int size) {
    int key;
    cout << "Enter the position of item, which is you want to delete: \n";
    cin >> key;

    P_glossary* new_arr = new P_glossary[size - 1];
    arr[key] = NULL;
    for (int i = key; i < size-1; i++) {
        arr[i] = arr[i + 1];
    }
    for (int i = 0; i < size-1; i++) {
        new_arr[i] = arr[i];
    }
    return new_arr;
}

int find(P_glossary* arr, int size) {
    int key;
    cout << "Enter the key: \n";
    cin >> key;

    int k = 0;
    bool is_find = false;
    for (int i=0; i<size; i++) {
        if (arr[i]->key == key) {
            is_find = true;
            k = i;
        }
    }
    if (is_find) return k;
    else {
        cout << "Wrong key! \n";
        return find(arr, size);
    }
}

P_glossary* edit(P_glossary* arr) {
    int key;
    char change;

    cout << "Enter the position of item, which is you want to edit: \n";
    cin >> key;
    cout << "Enter what you want to edit('k' -- edit key; 'f' -- edit FIO; 'p' -- edit passport_data): \n";
    cin >> change;
    switch (change) {
    case('k'):
        cout << "Enter: \n";
        cin >> arr[key]->key;
        break;
    case('f'):
        cout << "Enter: \n";
        cin >> arr[key]->FIO;
        break;
    case('p'):
        cout << "Enter: \n";
        cin >> arr[key]->passport_data;
        break;
    default:
        cout << "Wrong key! \n";
        break;
    }
    return arr;
}

void output_in_ascending(P_glossary* arr, int size) {
    char key;
    cout << "Enter the parameter by which you want to sort the data('k' -- key; 'f' -- FIO; 'p' -- passport_data): \n";
    cin >> key;
    switch (key) {
    case('k'):
        for (int i=0; i<size; i++) {
            for (int j=0; j<size-1; j++) {
                if (arr[j]->key > arr[j + 1]->key) {
                    P_glossary b = arr[j]; 
                    arr[j] = arr[j + 1]; 
                    arr[j + 1] = b;
                }
            }
        }
        break;
    case('f'):
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (arr[j]->FIO[0] > arr[j + 1]->FIO[0]) {
                    P_glossary b = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = b;
                }
            }
        }
        break;
    case('p'):
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (arr[j]->passport_data[0] > arr[j + 1]->passport_data[0]) {
                    P_glossary b = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = b;
                }
            }
        }
        break;
    default:
        cout << "Wrong key! \n";
        break;
    }
    for (int i = 0; i < size; i++) cout << arr[i]->key << "   " << arr[i]->FIO << "   " << arr[i]->passport_data << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Write the size of the glossary " << endl;
    int size;
    string str;
    cin >> size;

    P_glossary *arr = new P_glossary[size];
    ifstream f_input;
    f_input.open("input.txt");
    if (f_input.is_open()) {
        for (int i = 0; i < size; i++) {
            P_glossary p = new Glossary;
            arr[i] = p;
            f_input >> arr[i]->key;
            f_input >> arr[i]->FIO;
            f_input >> arr[i]->passport_data;
        }
    }
    f_input.close();

    bool f_exit = true;
    char ch;
    while (f_exit) {
        cout << "\n\nWhat do you want to do? \n ('a' -- add item; 'd' -- delete item; 'f' -- find item by key; 'e' -- change value of item; \n 'o' -- output glossary in ascending of keys) \n If you want to exit enter any key \n";
        cin >> ch;
        switch (ch) {
            case ('a'):
                arr = add_item(arr, size);
                size++;
                break;
            case ('d'):
                arr = delete_item(arr, size);
                size--;
                break;
            case ('f'):
                int num;
                num = find(arr, size);
                cout << "Number of this item is " << num << endl;
                break;
            case ('e'):
                edit(arr);
                cout << "Data has been changes \n";
                break;
            case ('o'):
                output_in_ascending(arr, size);
                break;
            default:
                f_exit = false;
                break;
        }
    }

    ofstream f_output;
    
    f_output.open("output.txt");
    if (f_output.is_open()) {
        for (int i = 0; i < size; i++) {
            f_output << arr[i]->key << " ";
            f_output << arr[i]->FIO << " ";
            f_output << arr[i]->passport_data << endl;
        }
    }
    f_output.close();
    delete[] arr;
}
