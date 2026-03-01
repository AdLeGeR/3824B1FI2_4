#pragma once
#include <iostream>;
#include "List.h"
#include <string>

using std::ostream;
using std::endl;
using std::istream;
using std::cout;
using std::cin;
using std::to_string;

enum ParseMode {
	Simple,
	Human
};

class Polinom
{
	List<Monome> monomes = List<Monome>();

public:
	ParseMode parseMode = Simple;
	Polinom() {}
	Polinom(int num) {
		monomes.push_back(Monome(num, 0));
	}

	Polinom operator+ (Polinom& other){
		Polinom result= Polinom();
		for(List<Monome>::iterator it = monomes.begin(), it2 = other.monomes.begin(); it != monomes.end() && it2 != other.monomes.end(); it++, it2++) {
			if (it->degree == it2->degree) {
				int coeff = it->coeff + it2->coeff;
				if(coeff != 0) result.monomes.push_back(Monome(coeff, it->degree));
			}
			else if (*it < *it2) {
				result.monomes.push_back(*it2);
			}
			else {
				result.monomes.push_back(*it);
			}
		}
	}
	/*void addMonome(Monome monome) {
		for( List<Monome>::iterator it = monomes.begin(); it != monomes.end(); it++) {
			if (it->degree == monome.degree) {
				int coeff = it->coeff + monome.coeff;
				if (coeff != 0) {
					*it = Monome(coeff, it->degree);
				}
				else {
					monomes.erase(it);
				}
				return;
			}
			else if (*it < monome) {
				monomes.insert(it, monome);
				return;
			}
		}
		monomes.push_back(monome);
	}*/
	Polinom operator* (const Polinom& other) {
		Polinom result;
		for (const auto& monome1 : this->monomes) {
			for (const auto& monome2 : other.monomes) {
				result.monomes.push_back(monome1 * monome2);
			}
		}
		result.monomes.sort();
		for(List<Monome>::iterator it = result.monomes.begin(); it != result.monomes.end();) {
			List<Monome>::iterator next = it;
			next++;
			while (next != result.monomes.end() && it->degree == next->degree) {
				it->coeff += next->coeff;
				result.monomes.erase(next);
				next++;
			}
			if (it->coeff == 0) {
				result.monomes.erase(it);
				it = next;
			}
			else {
				it++;
			}
		}
		return result;
	}

	friend istream& operator >> (istream& in, Polinom& polinom) {
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
			polinom.monomes.sort();
			return in;
		}
		else {
			//x^2y^3z^4 + 2*xyz + 5x
			// x2y3z4 + 2xyz + 5x
			std::string line;
			in >> line;
			Monome monome;
			bool x, y, z, coeff, deg;
			int ix, iy, iz, icoeff, sign = 1;
			enum variable { X, Y, Z, COEFF };
			variable cur_var;
			for (size_t i = 0; i < line.size(); i++)
			{
				if (line[i] == ' ') continue;
				if (line[i] == '+') {
					polinom.monomes.push_back(Monome(sign*coeff,x*100+y*10+z));
					x = y = z = coeff = false;
					ix = iy = iz = icoeff = 0;
					sign = 1;
					continue;
				}
				if (line[i] == '-') {
					polinom.monomes.push_back(Monome(sign * coeff, x * 100 + y * 10 + z));
					x = y = z = coeff = false;
					ix = iy = iz = icoeff = 0;
					sign = -1;
					continue;
				}
				else if (line[i] == '*') continue;
				if (line[i] == '^') {
					if (deg) { throw "Double ^ at position " + to_string(i); return in; }
					deg = true;
				}
				else if (line[i] >= '0' && line[i] <= '9') {
					if(!coeff) {
						cur_var = COEFF;
						coeff = true;
						icoeff = icoeff * 10 + (line[i] - '0');
					}
					else {
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
						else {
							throw "Invalid character in input";
							return in;
						}
					}
				}
				else if (line[i] == 'x') {
					if (x) { throw "Double x at position " + to_string(i); return in; }
					x = true;
					cur_var = X;
				}
				else if (line[i] == 'y') {
					if (y) { throw "Double y at position " + to_string(i); return in; }
					y = true;
					cur_var = Y;
				}
				else if (line[i] == 'z') {
					if (z) { throw "Double z at position " + to_string(i); return in; }
					z = true;
					cur_var = Z;
				}
				else {
					throw "Invalid character in input";
					return in;
				}
			}
		}
		
	}

	friend ostream& operator << (ostream& out, const Polinom& polinom) {
		for (const auto& monome : polinom.monomes) {
			out << monome << " + ";
		}
		return out;
	}

};


class Monome
{
	int coeff;
	int degree;
	friend class Polinom;
	int degree_sum() const {
		return (degree / 100) + (degree % 100 / 10) + (degree % 10);
	}
public:

	bool operator> (const Monome& other) const {
		if(this->degree_sum() == other.degree_sum()) {
			if (this->degree == other.degree) return this->coeff > other.coeff;
			return this->degree > other.degree;
		}
		return this->degree_sum() > other.degree_sum();
	}
	bool operator < (const Monome& other) const {
		if (this->degree_sum() == other.degree_sum()) {
			if (this->degree == other.degree) return this->coeff < other.coeff;
			return this->degree < other.degree;
		}
		return this->degree_sum() < other.degree_sum();
	}

	Monome() {
		coeff = 0;
		degree = 0;
	}

	Monome(int coeff, int degree) {
		if (degree < 0 || degree > 999) {
			throw "Degree of monome must be between 0 and 999";
		}
		if (coeff == 0) {
			throw "Coefficient of monome must be non-zero";
		}
		this->coeff = coeff;
		this->degree = degree;
	}
	Monome operator* (const Monome& other) const {
		int new_coeff = this->coeff * other.coeff;
		if(this->degree%10 + other.degree%10 > 9 || this->degree%100/10 + other.degree%100/10 > 9 || this->degree/100 + other.degree/100 > 9) {
			throw "Degree of someone variable more than 9";
		}
		int new_degree = this->degree + other.degree;
		return Monome(new_coeff, new_degree);
	}
	friend istream& operator>> (istream& in, Monome& monome) {
		cin >> monome.coeff >> monome.degree;
		if (monome.degree < 0 || monome.degree > 999) {
			throw "Degree of monome must be between 0 and 999";
		}
		if( monome.coeff == 0) {
			throw "Coefficient of monome must be non-zero";
		}
		return in;
	}
	friend ostream& operator<< (ostream& out, const Monome& monome) {
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
};