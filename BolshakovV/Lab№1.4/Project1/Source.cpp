#include "Header.h"
double correct_coeff() {

	bool flag_error = 1;
	std::string coeff;
	int count_dot;
	while (true) {

		std::cout << "Your coeff: ";
		std::getline(std::cin, coeff);
		count_dot = 0;
		size_t i;
		for (i = 0; i < coeff.size(); ++i) {

			if (coeff.size() > 1 && coeff[0] == '0') {
				std::cout << "Incorrect data. Please try again" << '\n';
				break;
			}

			if (coeff.size() == 1 && coeff[0] == '-') {
				std::cout << "Incorrect data. Please try again" << '\n';
				break;
			}

			if (coeff[i] >= '0' && coeff[i] <= '9') {

			}
			else if (coeff[i] == '-' && i != 0) {
				std::cout << "Incorrect data. Please try again" << '\n';
				break;
			}
			else if (coeff[i] == '.') {
				++count_dot;
				if (count_dot > 1) {
					std::cout << "Incorrect data. Please try again" << '\n';
					break;
				}
			}
			else {
				std::cout << "Incorrect data. Please try again" << '\n';
				break;
			}
		}

		if (i == coeff.size()) {
			break;
		}
	}

	double val = std::stod(coeff);
	return val;
};

unsigned int correct_deg() {
	std::string deg;

	bool flag_error = 0;
	while (true) {

		std::cout << "Your degree: ";
		std::getline(std::cin, deg);

		for (size_t i = 0; i < deg.size(); ++i) {
			if (deg[i] < '0' || deg[i]>'9') {
				std::cout << "Incorrect data. Please try again" << '\n';
				flag_error = 1;
				break;
			}
		}
		if (!flag_error) {


			if (deg.size() > 1 && deg[0] == '0') {
				std::cout << "Error. The degree cannot start from zero" << '\n';
			}
			else if (deg.size() > 3) {
				std::cout << "The monom degree must contain no more than 3 digits. Please try again" << '\n';
			}
			else {
				break;
			}
		}
		flag_error = 0;
	}

	unsigned int val = std::stoi(deg);
	return val;
}

void input_polinom(Polinom& pol) {
	bool flag_not_correct = 1;
	while (flag_not_correct) {
		try {
			std::cout << "Input: ";
			std::cin >> pol;
			flag_not_correct = 0;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << ". Please try again.\n";
		}
	}
}

void add_m(double& coeff, unsigned int& deg) {

	coeff = correct_coeff();

	std::cout << "\nEnter the degree of the monomial (Integer. No more than 3 digits, minimum value: 0).\n";
	std::cout << "The number of hundreds is the degree of the variable x, the number of tens is the degree of the variable y,";
	std::cout << " and the number of units is the degree of the variable z.\n";
	std::cout << "Example:" << '\n';
	std::cout << "123 -> x^1, y^2, z^2;" << '\n';
	std::cout << "10 -> x^0, y^1, z^0;" << '\n';
	std::cout << "2 -> x^0, y^0, z^2" << '\n';


	deg = correct_deg();
	std::cout << '\n';
}

void rules_add_monom() {
	std::cout << "\nInput rules: the first number is the coefficient, followed by a colon, and the second number is the power.\n";
	std::cout << "Enter the monomials separated by commas (spaces are not allowed!).\n";
	std::cout << "Example: 12:123,5:11,4:789 -> polynomial: 4x7y8z9 + 12x1y2z3 + 5x0y1z1.\n";
}


void main_job(Polinom& pol1, Polinom& pol2) {

	Polinom result;

	bool  flag_stop = 0;
	std::string ch;
	do {

		std::cout << "\nAvailable operations:" << '\n';
		std::cout << "1 - Add monom to polinom_1;" << '\n';
		std::cout << "2 - Add monom to polinom_2;" << '\n';
		std::cout << "3 - Add polinom_1 and polinom_2 (sum);" << '\n';
		std::cout << "4 - Subtract from polinom_1 polinom_2;" << '\n';
		std::cout << "5 - Subtract from polinom_2 polinom_1;" << '\n';
		std::cout << "6 - Multiply polinom_1 by a constant;" << '\n';
		std::cout << "7 - Multiply polinom_2 by a constant;" << '\n';
		std::cout << "8 - Multiply polinom_1 and polinom_2;" << '\n';
		std::cout << "9 - Output polinom_1" << '\n';
		std::cout << "10 - Output polinom_2" << '\n';
		std::cout << "0 - Stop the program" << '\n';

		std::cout << "\nSelect an operation: ";
		bool flag_correct = 0;
		while (!flag_correct) {

			std::getline(std::cin, ch);

			if ((ch.size() == 1 && ch[0] >= '0' && ch[0] <= '9') || ch == "10") {
				flag_correct = 1;

			}
			else {
				std::cout << "Incorrect data. Please try again" << '\n';
			}
		}

		double coeff;
		unsigned int deg;
		int operation = std::stoi(ch);
		try {
			switch (operation) {
			case 1:
				std::cout << "\nEnter a coefficient (a real number). Note: If you enter 0, the monomial will not be added to polinom_1\n";

				add_m(coeff, deg);

				pol1.add_monom(coeff, deg);

				std::cout << "Monom is added to polinom_1\n";
				break;
			case 2:
				std::cout << "\nEnter a coefficient (a real number). Note: If you enter 0, the monomial will not be added to polinom_2\n";

				add_m(coeff, deg);

				pol2.add_monom(coeff, deg);

				std::cout << '\n';
				std::cout << "Monom is added to polinom_1\n";

				break;
			case 3:

				result = pol1 + pol2;
				std::cout << "\nThe result of the operation: " << result << '\n';

				break;
			case 4:

				result = pol1 - pol2;
				std::cout << "\nThe result of the operation: " << result << '\n';

				break;
			case 5:

				result = pol2 - pol1;
				std::cout << "\nThe result of the operation: " << result << '\n';

				break;
			case 6:

				std::cout << "\nAttention: when you multiply a polynomial by a constant, the polynomial itself will be changed.\n (If you don't want to change anything, multiply it by 1)\n";

				double constant1;
				constant1 = correct_coeff();
				pol1 = pol1 * constant1;
				std::cout << "Polinom_1: " << pol1 << '\n';

				break;
			case 7:

				std::cout << "\nAttention: when you multiply a polynomial by a constant, the polynomial itself will be changed.\n (If you don't want to change anything, multiply it by 1)\n";

				double constant2;
				constant2 = correct_coeff();
				pol2 = pol2 * constant2;

				std::cout << "Polinom_2: " << pol2 << '\n';

				break;
			case 8:

				result = pol1 * pol2;
				std::cout << "\nThe result of the operation: " << result << '\n';

				break;
			case 9:

				std::cout << "\nPolinom_1: " << pol1 << '\n';

				break;
			case 10:

				std::cout << "\nPolinom_2: " << pol2 << '\n';
				break;

			case 0:
				flag_stop = 1;
				break;
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what() << '\n';
		}



	} while (!flag_stop);
}


int main() {


	bool flag_stop = 0;

	std::cout << "Hello. You need to create two polynomials: polinom_1 and polinom_2. Please select the mode:" << '\n';
	std::cout << "Polinom is empty - monoms can be added later, polinom is not empty - you will need to enter several monoms" << '\n';
	std::cout << "1 - polinom_1 is empty, polinom_2 is empty;" << '\n';
	std::cout << "2 - polinom_1 is not empty, polinom_2 is empty;" << '\n';
	std::cout << "3 - polinom_1 is empty, polinom_2 is not empty" << '\n';
	std::cout << "4 - polinom_1 is not empty, polinom_2 is not empty" << '\n';
	std::cout << "0 - Stop the program" << '\n';
	std::string ch;
	while (flag_stop != 1) {
		std::cout << "Your choice: ";

		std::getline(std::cin, ch);
		if (ch.size() == 1 && ch[0] >= '0' && ch[0] <= '4') {
			flag_stop = 1;

		}
		else {
			std::cout << "Incorrect data. Please try again" << '\n';
			flag_stop = 0;
		}
	}

	int m = std::stoi(ch);
	switch (m) {
	case 1:
	{
		Polinom pol1;
		Polinom pol2;
		std::cout << "Polynomials: polinom_1 and polinom_2 are created" << '\n';
		main_job(pol1, pol2);
	}
	break;
	case 2:
	{
		Polinom pol1;
		std::cout << "\nTo create polinom_1, you will need to enter several monomials.\n";
		rules_add_monom();

		input_polinom(pol1);

		std::cout << "Polinom_1 has been created\n";
		Polinom pol2;
		std::cout << "Polinom_2 has been created\n";

		main_job(pol1, pol2);

	}
	break;
	case 3:
	{
		Polinom pol1;
		std::cout << "Polinom_1 has been created\n";

		Polinom pol2;
		std::cout << "To create polinom_2, you will need to enter several monomials.\n";
		rules_add_monom();
		input_polinom(pol2);
		std::cout << "Polinom_2 has been created\n";

		main_job(pol1, pol2);
	}
	break;
	case 4:
	{
		Polinom pol1;
		std::cout << "\nTo create polinom_1, you will need to enter several monomials.\n";
		rules_add_monom();

		input_polinom(pol1);
		Polinom pol2;
		std::cout << "\nNow polinom_2\n";
		input_polinom(pol2);

		std::cout << "Polynomials: polinom_1 and polinom_2 are created" << '\n';

		main_job(pol1, pol2);

	}
	break;
	case 0:

		break;
	}

}