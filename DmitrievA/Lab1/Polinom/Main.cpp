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
    cout << "3\n2 111\n3 123\n10 0\n";
	cout << "2. Human readable format. Example: x^2y^3z^4 + 2*xy4z - 5x - 10x2y3z4 + 1\n";
	int mode;
	cin >> mode;
    while (mode != 1 && mode != 2) {
        cout << "Invalid input. Please enter 1 or 2." << endl;
        cin >> mode;
	}
    cin.clear();
    
	Polinom polinom;
    ParseMode parse_mode = (mode == 1) ? Simple : Human;
    polinom.parseMode = parse_mode;
	cout << "Enter polinome:" << endl;
	cin >> polinom;
	cout << "You entered: " << polinom << endl;
    int command = -1;
    while(command != 0) {
        cout << "Enter command:" << endl;
        cout << "1. Print polinome" << endl;
		cout << "2. Add another polinome" << endl;
        cout << "3. Sub another polinome" << endl;
        cout << "4. Multiply by another polinome" << endl;
		cout << "5. Evaluate polinome" << endl;
        cout << "0. Exit" << endl;
        cin >> command;
        if (command == 1) {
            cout << polinom << endl;
        }
        else if (command == 2) {
            Polinom other;
            other.parseMode = polinom.parseMode;
            cout << "Enter another polinome to add:" << endl;
            try {
                cin >> other;
            }
            catch (const char* e) {
                cout << "Input error: " << e << endl;
                // clear failbit and skip to next loop
                cin.clear();
                continue;
            }
            try {
                polinom = polinom + other;
                polinom.parseMode = parse_mode;
                cout << "Result: " << polinom << endl;
            }
            catch (const char* e) {
                cout << "Operation error: " << e << endl;
            }
        }
        else if (command == 3) {
            Polinom other;
            other.parseMode = polinom.parseMode;
            cout << "Enter another polinome to subtract:" << endl;
            try {
                cin >> other;
            }
            catch (const char* e) {
                cout << "Input error: " << e << endl;
                cin.clear();
                continue;
            }
            try {
                polinom = polinom - other;
                polinom.parseMode = parse_mode;
                cout << "Result: " << polinom << endl;
            }
            catch (const char* e) {
                cout << "Operation error: " << e << endl;
            }
        }
        else if (command == 4) {
            Polinom other;
            other.parseMode = polinom.parseMode;
            cout << "Enter another polinome to multiply:" << endl;
            try {
                cin >> other;
            }
            catch (const char* e) {
                cout << "Input error: " << e << endl;
                cin.clear();
                continue;
            }
            try {
                polinom = polinom * other;
                polinom.parseMode = parse_mode;
                cout << "Result: " << polinom << endl;
            }
            catch (const char* e) {
                cout << "Operation error: " << e << endl;
            }
        }
        else if (command == 5) {
            double x = 0.0, y = 0.0, z = 0.0;
            cout << "Enter values for x y z (separated by spaces): ";
            if (!(cin >> x >> y >> z)) {
                cout << "Invalid input for x, y, z. Aborting evaluation." << endl;
                cin.clear();
                // discard rest of line
                std::string tmp; std::getline(cin, tmp);
                continue;
            }
            try {
                double value = polinom.evaluate(x, y, z);
                cout << "Value: " << value << endl;
            }
            catch (const char* e) {
                cout << "Evaluation error: " << e << endl;
            }
            catch (...) {
                cout << "Unknown evaluation error." << endl;
            }
        }
        else if (command != 0) {
            cout << "Invalid command. Please enter 0, 1, 2, 3 or 4." << endl;
        }
	}
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
