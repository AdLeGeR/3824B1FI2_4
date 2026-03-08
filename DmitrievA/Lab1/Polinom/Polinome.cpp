#pragma once
#include <iostream>
#include "List.h"
#include <string>
#include "Polinom.h"
#include <limits>
#include <functional>

using std::ostream;
using std::endl;
using std::istream;
using std::cout;
using std::cin;
using std::to_string;
using std::greater;

const double EPS = 1e-12;

Polinom::Polinom() {}

Polinom::Polinom(const Polinom& other) {
	this->parseMode = other.parseMode;
	for (List<Monome>::const_iterator it = other.monomes.cbegin(); it != other.monomes.cend(); ++it) {
		this->monomes.push_back(*it);
	}
}

Polinom::Polinom(double num) {
	monomes.push_back(Monome(num, 0));
}

void Polinom::normalize() {
	for (List<Monome>::iterator it = monomes.begin(); it != monomes.end();) {
		List<Monome>::iterator next = it;
		next++;
		while (next != monomes.end() && it->degree == next->degree) {
			it->coeff += next->coeff;
			auto temp = next;
			next++;
			monomes.erase(temp);
		}
		if (abs(it->coeff) < EPS) {
			monomes.erase(it);
			it = next;
		}
		else {
			it++;
		}
	}
}
Polinom Polinom::operator+ (const Polinom& other) const{
	Polinom result= Polinom();
	List<Monome>::const_iterator it = monomes.cbegin(), 
		it2 = other.monomes.cbegin();
	for(; it != monomes.cend() && it2 != other.monomes.cend();) {
		if (it->degree == it2->degree) {
			double coeff = it->coeff + it2->coeff;
			if(abs(coeff) > EPS) result.monomes.push_back(Monome(coeff, it->degree));
			it++; it2++;
		}
		else if (*it < *it2) {
			result.monomes.push_back(*it2);
			it2++;
		}
		else {
			result.monomes.push_back(*it);
			it++;
		}
	}
	for (; it != monomes.cend(); it++) result.monomes.push_back(*it);
	for (; it2 != monomes.cend(); it2++) result.monomes.push_back(*it2);
	return result;
}
	
Polinom Polinom::operator- (const Polinom& other) const {
	Polinom result = Polinom();
	List<Monome>::const_iterator it = monomes.cbegin(), it2 = other.monomes.cbegin();
	for (; it != monomes.cend() && it2 != other.monomes.cend(); ) {
		if (it->degree == it2->degree) {
			double coeff = it->coeff - it2->coeff;
			if (abs(coeff) > EPS) result.monomes.push_back(Monome(coeff, it->degree));
			it++; it2++;
		}
		else if (*it < *it2) {
			result.monomes.push_back(-(*it2));
			it2++;
		}
		else {
			result.monomes.push_back(*it);
			it++;
		}

	}
	for (; it != monomes.cend(); it++) result.monomes.push_back(*it);
	for (; it2 != monomes.cend(); it2++) result.monomes.push_back(-(*it2));
	return result;
}

Polinom Polinom::operator* (double num) {
	Polinom result;
	for (const auto& monome1 : this->monomes) {
		result.monomes.push_back(monome1 * num);
	}
	return result;
}
Polinom Polinom::operator* (const Polinom& other) {
	Polinom result;
	for (const auto& monome1 : this->monomes) {
		for (const auto& monome2 : other.monomes) {
			result.monomes.push_back(monome1 * monome2);
		}
	}
	result.monomes.sort(greater<Monome>{});
	result.normalize();
	return result;
}

Polinom& Polinom::operator= (const Polinom& other) {
	if (this == &other) return *this; // самоприсвоение

	// очистка текущего списка (удаление узлов)
	while (monomes.getSize() > 0) {
		monomes.erase(monomes.begin());
	}

	// копирование из other
	for (List<Monome>::const_iterator it = other.monomes.cbegin(); it != other.monomes.cend(); ++it) {
		monomes.push_back(*it);
	}

	this->parseMode = other.parseMode;
	return *this;
}

double Polinom::evaluate(double x, double y, double z) const {
	double result = 0;
	for (const auto& monome : this->monomes) {
		double monome_value = monome.coeff;
		int deg = monome.degree;
		int deg_x = deg / 100;
		int deg_y = deg % 100 / 10;
		int deg_z = deg % 10;
		monome_value *= pow(x, deg_x);
		monome_value *= pow(y, deg_y);
		monome_value *= pow(z, deg_z);
		result += monome_value;
	}
	return result;
}

istream& operator >> (istream& in, Polinom& polinom) {
	if (polinom.parseMode == Simple) {
		int n;
		cin >> n;
		if (n < 0) {
			throw "Number of monomes must be non-negative";
			return in;
		}
		for (int i = 0; i < n; i++) {
			Monome monome;
			cin >> monome;
			polinom.monomes.push_back(monome);
		}
		polinom.monomes.sort(greater<Monome>{});
		polinom.normalize();
		return in;
	}
	else {
		//x^2y^3z^4 + 2*xyz + 5x
		// x2y3z4 + 2xyz + 5x
		std::string line;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(in, line);
		bool x, y, z, coeff, deg;
		// deg - появился ли символ ^ для текущей переменной
		// x, y, z - появились ли символы x, y, z для текущего монома
		//coeff - появился ли коэффициент для текущего монома
		x = y = z = coeff = deg = false;
		int ix, iy, iz, icoeff, sign = 1;
		ix = iy = iz = icoeff =0;
		enum variable { X, Y, Z, COEFF };
		variable cur_var = COEFF;
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ') continue;
			if (line[i] == '+') {
				polinom.monomes.push_back(Monome(sign* (1 > icoeff ? 1 : icoeff),ix*100+iy*10+iz));
				x = y = z = coeff = false;
				ix = iy = iz = icoeff = 0;
				sign = 1;
				cur_var = COEFF;
				continue;
			}
			if (line[i] == '-' && polinom.monomes.getSize() > 0) {
				polinom.monomes.push_back(Monome(sign * (1 > icoeff ? 1 : icoeff), ix * 100 + iy * 10 + iz));
				x = y = z = coeff = false;
				ix = iy = iz = icoeff = 0;
				sign = -1;
				cur_var = COEFF;
				continue;
			}
			else if (line[i] == '-' && polinom.monomes.getSize() == 0) {
				sign = -1;
				continue;
			}
			else if (line[i] == '*') continue;
			if (line[i] == '^') {
				if (deg) { throw "Double ^ at position " + to_string(i); return in; }
				deg = true;
			}
			else if (line[i] >= '0' && line[i] <= '9') {
				/*if(!coeff && cur_var == COEFF) {
					coeff = true;
					icoeff = icoeff * 10 + (line[i] - '0');
				}
				else {*/
					if (cur_var == X) {
						ix = (line[i] - '0');
						deg = false;
					}
					else if (cur_var == Y) {
						iy = (line[i] - '0');
						deg = false;
					}
					else if (cur_var == Z) {
						iz = (line[i] - '0');
						deg = false;
					}
					else if (cur_var == COEFF) {
						icoeff = icoeff * 10 + (line[i] - '0');
					}
				//}
			}
			else if (line[i] == 'x') {
				if (x) { throw "Double x at position " + to_string(i); return in; }
				x = true;
				ix = 1;
				cur_var = X;
			}
			else if (line[i] == 'y') {
				if (y) { throw "Double y at position " + to_string(i); return in; }
				y = true;
				iy = 1;
				cur_var = Y;
			}
			else if (line[i] == 'z') {
				if (z) { throw "Double z at position " + to_string(i); return in; }
				z = true;
				iz = 1;
				cur_var = Z;
			}
			else {
				throw "Invalid character in input";
				return in;
			}
		}
		polinom.monomes.push_back(Monome(sign* (1 > icoeff ? 1 : icoeff), ix * 100 + iy * 10 + iz));
		polinom.monomes.sort(greater<Monome>{});
		polinom.normalize();
	}
		
}

ostream& operator << (ostream& out, const Polinom& polinom) {
	for (const auto& monome : polinom.monomes) {
		out << monome << " + ";
	}
	return out;
}




int Monome::degree_sum() const {
	return (degree / 100) + (degree % 100 / 10) + (degree % 10);
}


bool Monome::operator> (const Monome& other) const {
	if(this->degree_sum() == other.degree_sum()) {
		if (this->degree == other.degree) return this->coeff > other.coeff;
		return this->degree > other.degree;
	}
	return this->degree_sum() > other.degree_sum();
}
bool Monome::operator < (const Monome& other) const {
	if (this->degree_sum() == other.degree_sum()) {
		if (this->degree == other.degree) return this->coeff < other.coeff;
		return this->degree < other.degree;
	}
	return this->degree_sum() < other.degree_sum();
}

Monome::Monome() {
	coeff = 0;
	degree = 0;
}

Monome::Monome(double coeff, int degree) {
	if (degree < 0 || degree > 999) {
		throw "Degree of monome must be between 0 and 999";
	}
	if (coeff == 0) {
		throw "Coefficient of monome must be non-zero";
	}
	this->coeff = coeff;
	this->degree = degree;
}

Monome Monome::operator-() const {
	return Monome(-coeff, degree);
}

Monome Monome::operator* (double num) const {
	return Monome(coeff * num, degree);
}
Monome Monome::operator* (const Monome& other) const {
	double new_coeff = this->coeff * other.coeff;
	if(this->degree%10 + other.degree%10 > 9 || this->degree%100/10 + other.degree%100/10 > 9 || this->degree/100 + other.degree/100 > 9) {
		throw "Degree of someone variable more than 9";
	}
	int new_degree = this->degree + other.degree;
	return Monome(new_coeff, new_degree);
}

bool Monome::operator== (const Monome& other) const {
	return this->degree == other.degree && this->coeff == other.coeff;
}

istream& operator>> (istream& in, Monome& monome) {
	cin >> monome.coeff >> monome.degree;
	if (monome.degree < 0 || monome.degree > 999) {
		throw "Degree of monome must be between 0 and 999";
	}
	if( monome.coeff == 0) {
		throw "Coefficient of monome must be non-zero";
	}
	return in;
}
ostream& operator<< (ostream& out, const Monome& monome) {
	out << monome.coeff;
	if (monome.degree / 100 != 0) {
		out << "x^" << monome.degree / 100;
	}
	if(monome.degree % 100 / 10!= 0) {
		out << "y^" << monome.degree % 100 / 10;
	}
	if (monome.degree % 10 != 0) {
		out << "z^" << monome.degree % 10;
	}
	return out;
}
