#include "Header.h"  
using namespace std;

void print_menu() {
    cout << "\nAvailable commands:\n";
    cout << "1 - Enter a polynomial (You have to stick to the following format: C1 D1 C2 D2 ...)\n where C1 - coefficient and D1 determines the degrees it's a 3-digit number\n(first digit is a degree of X, second one is a degree of Y, and the last one is for Z.\n Polinomial gets an ID (1, 2, 3...). Current ID is to be displayed.\n";
    cout << "2 - Print a polynomial. Enter its ID.\n";
    cout << "3 - Sum two polynomials. Enter two polynomial IDs.\n";
    cout << "4 - Subtract second polynomial from the first. Enter two polynomial IDs.\n";
    cout << "5 - Multiply two polynomials. Enter two polynomial IDs.\n";
    cout << "    (You may also enter the same exact polynomial IDs for commands 3, 4, 5)\n";
    cout << "6 - Multiply a polynomial by a constant. Enter polynomial ID and then the constant.\n";
    cout << "7 - Print all the entered polynomials as well as their IDs.\n";
    cout << "8 - Exit.\n";
    cout << "Enter command: ";
}

int main() {
    vector<Polinomial> Data;
    double command;
    print_menu();
    int Num1, Num2;
    do {
        cin >> command;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        if (command == 1) {
            Polinomial M;
            cout << "Enter polynomial for example (12 111 3.7 234) = 12xyz + 3.7x^2 y^3 z^4:\n ";
            cin >> M;
            Data.emplace_back(M);
            cout << "Polynomial added, its ID is " << Data.size() << ".\n";
        }
        else if (command >= 2 && command <= 6) {
            if (Data.empty()) {
                cout << "No polynomials have been entered yet, please add a polynomial first (command 1).\n";
                continue;
            }

            int Num1 = 0, Num2 = 0;
            if (command != 7) {
                if (command == 2 || command == 6) {
                    cout << "Enter the polinomial's ID\n";
                    cin >> Num1;
                }
                else {
                    cout << "Enter the polinomials' IDs\n";
                    cin >> Num1 >> Num2;
                }
            }


            if (command == 2) {
                cout << "Polynomial " << Num1 << ": " << Data[Num1 - 1] << "\n";
            }
            else if (command == 3) {
                Polinomial res = Data[Num1 - 1] + Data[Num2 - 1];
                cout << "Result of addition: " << res << "\n";
            }
            else if (command == 4) {
                Polinomial res = Data[Num1 - 1] - Data[Num2 - 1];
                cout << "Result of subtraction: " << res << "\n";
            }
            else if (command == 5) {
                Polinomial res = Data[Num1 - 1] * Data[Num2 - 1];
                cout << "Result of multiplication: " << res << "\n";
            }
            else if (command == 6) {
                double constant;// = get_input();
                cin >> constant;
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                Polinomial res = Data[Num1 - 1] * constant;
                cout << "Result of multiplication by constant: " << res << "\n";
            }
        }
        else if (command == 7) {
            if (Data.empty()) {
                cout << "No polynomials entered yet.\n";
            }
            else {
                cout << " Stored Polynomials \n";
                for (size_t i = 0; i < Data.size(); ++i) {
                    cout << "ID " << (i + 1) << ": " << Data[i] << "\n";
                }
                cout << "\n";
            }
        }
        else if (command != 8) {
            cout << "You've entered an incorrect command, please try again.\n";
        }
        if(command!=8) cout << "Enter command: ";
    } while (command != 8);

    cout << "Turned off\n";
    return 0;
}