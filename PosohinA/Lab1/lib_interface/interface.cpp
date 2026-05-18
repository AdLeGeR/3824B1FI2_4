#include "../lib_interface/interface.h"

Interface::Interface() : Pol1(), Pol2() {}

Interface::~Interface() {}

Polynomial Interface::sum() const {
	return Pol1 + Pol2;
}

Polynomial Interface::sub() const {
	return Pol1 - Pol2;
}

Polynomial Interface::mul() const {
	return Pol1 * Pol2;
}

Polynomial Interface::sum2() const {
	return Pol2 + Pol1;
}

Polynomial Interface::sub2() const {
	return Pol2 - Pol1;
}

Polynomial Interface::mul_val1() const {
	int val;
	while (true) {
		std::cout << "Entering the val" << std::endl;
		std::cin >> val;

		if (std::cin.fail()) {
			std::cout << "Error: Invalid input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
	return Pol1 * val;
}

Polynomial Interface::mul_val2() const {
	int val;
	while (true) {
		std::cout << "Entering the val" << std::endl;
		std::cin >> val;

		if (std::cin.fail()) {
			std::cout << "Error: Invalid input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
	return Pol2 * val;
}

void Interface::input_polyn() {
	std::cout << "Entering the polynomial number 1" << std::endl;
	Pol1.record();
	std::cout << "Entering the polynomial number 2" << std::endl;
	Pol2.record();
}

void Interface::actions(){
	bool flage = true;
	int a;
	Polynomial rez;
	while (flage) {
		while (true) {
			std::cout << "What to do with polynomials?\n1 - Pol1 + Pol2\n2 - Pol1 - Pol2\n3 - Pol1 * Pol2\n4 - Pol2 + Pol1\n5 - Pol2 - Pol1\n6 - Pol1 * val\n6 - Pol2 * val\n0 - Exit\nEnter the number indicating the action: ";
			std::cin >> a;

			if (std::cin.fail()) {
				std::cout << "Error: Invalid input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}

		switch (a) {
		case 1:
			rez = sum();
			flage = false;
			break;

		case 2:
			rez = sub();
			flage = false;
			break;

		case 3:
			rez = mul();
			flage = false;
			break;

		case 4:
			rez = sum2();
			flage = false;
			break;

		case 5:
			rez = sub2();
			flage = false;
			break;

		case 6:
			rez = mul_val1();
			flage = false;
			break;

		case 7:
			rez = mul_val2();
			flage = false;
			break;

		case 0:
			std::cout << "\nGoodbye!";
			return;
		
		default:
			std::cout << "\nincorrect value\n";
		}
		
		std::cout << rez << std::endl;
	
		while (true) {
			std::cout << "\ndo you want to continue with the same polynomials?\n1 - yes\n2 - no\n3 - Exit\n";
			std::cin >> a;

			if (std::cin.fail()) {
				std::cout << "Error: Invalid input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		switch (a) {
		case 1:
			flage = true;
			break;

		case 2:
			input_polyn();
			actions();
			flage = true;
			break;

		case 3:
			break;

		default:
			std::cout << "incorrect value\n";
		}

	}
}
