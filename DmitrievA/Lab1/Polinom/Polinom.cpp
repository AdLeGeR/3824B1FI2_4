// Polinom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Polinom.h"

using std::cout;
using std::endl;

int main()
{

    cout << "Choose input format of polinome:" << endl;
    cout << "1. First number N - count of monomes.Next N pairs of numbers - monomes.First number at pair - coefficient.Second - degree(must be between 0 and 999).Example:" << endl;
    cout << "3\n2 111\n3 123\n10 0";
	cout << "2. Human readable format. Example: x^2y^3z^4 + 2*xy4z - 5x - 10x2y3z4 + 1\n";
	int mode;
	cin >> mode;
    while (mode != 1 && mode != 2) {
        cout << "Invalid input. Please enter 1 or 2." << endl;
        cin >> mode;
	}
	Polinom polinom;
    polinom.parseMode = (mode == 1) ? Simple : Human;
	cout << "Enter polinome:" << endl;
	cin >> polinom;
	cout << "You entered: " << polinom << endl;
    int command = -1;
    while(command != 0) {
        cout << "Enter command:" << endl;
        cout << "1. Print polinome" << endl;
		cout << "2. Add another polinome" << endl;
        cout << "3. Multiply by another polinome" << endl;
		cout << "4. Evaluate polinome" << endl;
        cout << "0. Exit" << endl;
        cin >> command;
        if (command == 1) {
            cout << polinom << endl;
        }
        else if (command == 2) {
            Polinom other;
            other.parseMode = polinom.parseMode;
            cout << "Enter another polinome:" << endl;
            cin >> other;
            Polinom result = polinom + other;
            cout << "Result: " << result << endl;
        }
        else if (command != 0) {
            cout << "Invalid command. Please enter 0, 1 or 2." << endl;
        }
	}
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
