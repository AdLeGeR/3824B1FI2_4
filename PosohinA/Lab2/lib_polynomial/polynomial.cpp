#include"../lib_polynomial/polynomial.h"
#include <iomanip>

int entering_degree(const char a) {
	int deg;
	while (true) {
		while (true) {
			std::cout << "degree l" << a << " = ";
			std::cin >> deg;

			if (std::cin.fail()) {
				std::cout << "Error: Invalid input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		if (0 <= deg && deg <= 9)
			break;
		else
			std::cout << "Erorr\n";
	}
	return deg;
}

bool chek_deg(int A, int B) {
	while (B != 0) {
		if (A % 10 + B % 10 > 9)
			return false;
		A /= 10;
		B /= 10;
	}
	return true;
}


Polynomial::Polynomial() : view() {}

Polynomial::Polynomial(const List A) : view(A) {}

Polynomial::~Polynomial() { view.clear(); }

void Polynomial::record() {
	std::cout << "enter the monomials step by step. General view of the monome K * x^l1 * y^l2 * z^l3\nl1,l2,l3 - (0 - 9), k - the real coefficient" << "To stop typing, write K = 0" << std::endl;
	int i = 1;
	int sum_deg;
	double rat;
	int l1, l2, l3, degree;

	while (true) {

		while (true) {
			std::cout << "Enter " << i << " monom" << std::endl;
			std::cout << "Ratio K = \n";
			std::cin >> rat;

			if (std::cin.fail()) {
				std::cout << "Error: Invalid input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		if (rat == 0) {
			if (i == 1) {
				std::cout << "Polynomial cannot be empty" << std::endl;
				continue;
			}
			break;
		}
		i++;
		l1 = entering_degree('1');
		l2 = entering_degree('2');
		l3 = entering_degree('3');
		sum_deg = l1 + l2 + l3;
		degree = 100 * l1 + 10 * l2 + l3;

		std::pair<double, int> monome = { rat, degree };

		if (view.is_empty()) {
			view.push_back(monome);
			std::cout << "Monom recorded\n";
			continue;
		}
		bool flage = false;

		auto it = view.begin();

		if (sum_numb(monome.second) > sum_numb((*it).second)) {
			view.push_front(monome);
			flage = true;
		}

		if (!flage) {
			for (auto it = view.begin(); it != view.end(); ++it) {
				Node* curr = it.get_current();

				if (monome.second == curr->_val.second) {
					curr->_val.first += monome.first;
					flage = true;
					break;
				}

				if (curr->_next == nullptr) {
					view.push_back(monome);
					flage = true;
					break;
				}

				else {
					Node* nextcur = curr->_next;

					if (sum_numb(monome.second) > sum_numb(nextcur->_val.second) && sum_numb(monome.second) < sum_numb(curr->_val.second)) {
						view.insert(curr, monome);
						flage = true;
						break;
					}
				}
			}
		}
	}
	std::cout << "your polynomial: " << (*this) << std::endl;
}


Polynomial Polynomial::operator + (const Polynomial& A) const {
	Polynomial new_Polynomial;
	auto it1 = view.begin();
	auto it2 = A.view.begin();

	while (it1 != view.end() && it2 != view.end()) {
		int sum1 = sum_numb((*it1).second);
		int sum2 = sum_numb((*it2).second);

		if ((*it1).second == (*it2).second) {
			double sum = (*it1).first + (*it2).first;
			if (sum != 0.0) {
				std::pair<double, int> monome = { sum, (*it1).second };
				new_Polynomial.view.push_back(monome);
			}
			++it1;
			++it2;
		}

		else if (sum1 > sum2) {
			new_Polynomial.view.push_back(*it1);
			it1++;
		}

		else if (sum1 <= sum2) {
			new_Polynomial.view.push_back(*it2);
			it2++;
		}
	}

	for (it1; it1 != view.end(); it1++)
		new_Polynomial.view.push_back((*it1));

	for (it2; it2 != view.end(); it2++)
		new_Polynomial.view.push_back((*it2));

	return new_Polynomial;
}

Polynomial Polynomial::operator - (const Polynomial& A) const {
	Polynomial new_Polynomial;
	new_Polynomial = (*this) + (A * (-1.0));
	return new_Polynomial;
}

Polynomial& Polynomial::operator = (const Polynomial& A) {
	if (this != &A)
		view = A.view;
	return (*this);
}

Polynomial Polynomial::operator * (double A) const {
	Polynomial new_Polynomial;
	new_Polynomial.view.push_back(std::pair<double, int>(A, 0));
	return (*this) * new_Polynomial;
}

Polynomial Polynomial::operator * (const Polynomial& A) const {
	Polynomial new_Polynomial;

	for (auto it1 = view.begin(); it1 != view.end(); it1++) {
		for (auto it2 = A.view.begin(); it2 != A.view.end(); it2++) {

			if (!chek_deg((*it1).second, (*it2).second))
				throw std::logic_error("overflou");

			double coef = (*it1).first * (*it2).first;
			if (coef == 0.0)
				continue;
			int deg = (*it1).second + (*it2).second;
			std::pair<double, int> new_pair = { coef, deg };

			Node* prev = nullptr;
			bool found = false;

			for (auto resIt = new_Polynomial.view.begin(); resIt != new_Polynomial.view.end(); ++resIt) {
				Node* curr = resIt.get_current();

				if (curr->_val.second == deg) {
					curr->_val.first += coef;
					found = true;
					break;
				}

				if (sum_numb(deg) > sum_numb(curr->_val.second)) {
					if (prev == nullptr)
						new_Polynomial.view.push_front(new_pair);

					else
						new_Polynomial.view.insert(prev, new_pair);

					found = true;
					break;
				}

				prev = curr;
			}

			if (!found)
				new_Polynomial.view.push_back(new_pair);
		}
	}
	return new_Polynomial;
}

const Polynomial operator * (double val, const Polynomial& A) {
	return A * val;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	for (auto it = p.view.begin(); it != p.view.end(); ++it) {
		if ((*it).first == 0.0)
			continue;

		if ((*it).first > 0)
			os << " + ";

		else
			os << " - ";

		if (std::abs((*it).first) != 1.0 || (*it).second == 0)
			os << std::abs((*it).first);

		if ((*it).second > 0) {
			int l1 = (*it).second / 100;
			int l2 = ((*it).second / 10) % 10;
			int l3 = (*it).second % 10;

			if (l1 > 0)
				os << "x^" << l1;

			if (l2 > 0)
				os << " * y^" << l2;

			if (l3 > 0)
				os << " * z^" << l3;
		}
	}
	return os;
}

bool Polynomial::operator == (const Polynomial& A) const {
	bool flage = true;
	auto it1 = view.begin();
	auto it2 = A.view.begin();

	while (it1 != view.end() && it2 != A.view.end()) {
		if ((*it1) != (*it2))
			return false;

		it1++;
		it2++;
	}
	return (it1 == view.end() && it2 == A.view.end());
}