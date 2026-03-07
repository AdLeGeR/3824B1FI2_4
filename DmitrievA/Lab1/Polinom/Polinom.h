#pragma once
#include <iostream>
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

class Monome;

class Polinom
{
	List<Monome> monomes = List<Monome>();
public:
	ParseMode parseMode = Simple;
	Polinom();
	Polinom(double num);
	Polinom operator+ (const Polinom& other) const;
	Polinom operator- (const Polinom& other) const;
	/*void addMonome(const Monome& monome) {
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
	Polinom operator* (double num);
	Polinom operator* (const Polinom& other);
	friend istream& operator >> (istream& in, Polinom& polinom);
	friend ostream& operator << (ostream& out, const Polinom& polinom);
};


class Monome
{
	double coeff;
	int degree;
	friend class Polinom;
	int degree_sum() const;
public:
	bool operator> (const Monome& other) const;
	bool operator< (const Monome& other) const;
	Monome();
	Monome(double coeff, int degree);
	Monome operator-() const;
	Monome operator* (double num) const;
	Monome operator* (const Monome& other) const;
	bool operator== (const Monome& other) const;
	friend istream& operator>> (istream& in, Monome& monome);
	friend ostream& operator<< (ostream& out, const Monome& monome);
};