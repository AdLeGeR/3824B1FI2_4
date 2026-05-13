#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "list.h"



class Polynom {
private:
	void remove_zeros();

public:
	List poly;
	void push_back(double co, int pow);
	void read();
	void print();
	Polynom operator+ (const Polynom& other);
	Polynom operator* (double c);
	Polynom operator- (const Polynom& other);
	Polynom operator* (const Polynom& other);
};

void Polynom::push_back(double co, int pow) {
	this->poly.push_back(co, pow);
}

void Polynom::remove_zeros() {
			Node* a = this->poly.head;
			while (a) {
				Node* next = a->next;
				if (a->coeff == 0)
					poly.deleteNode(a);
				a = next;
			}
		}

void Polynom::read() {
	std::cout << "Enter the monomials in the format: <coefficient> <degree>. An empty line is the end of the input.\n";

	std::string line;
	while (true) {
		std::getline(std::cin, line);
		if (line.empty()) break;

		std::stringstream ss(line);
		double coeff;
		int power;

		if (ss >> coeff >> power)
			poly.push_back(coeff, power);
		else
			std::cout << "Incorrect format. Try again.\n";
	}
}

void Polynom::print() { poly.print(); }

Polynom Polynom::operator+ (const Polynom& other) {
	Polynom res;
	Node* a = poly.head;
	Node* b = other.poly.head;

	while (a && b) {
		if (a->power == b->power) {
			double sum = a->coeff + b->coeff;
			res.poly.simple_push_back(sum, a->power);
			a = a->next;
			b = b->next;
			continue;
		}
		if (*a > *b) {
			res.poly.simple_push_back(a->coeff, a->power);
			a = a->next;
			continue;
		}
		else {
			res.poly.simple_push_back(b->coeff, b->power);
			b = b->next;
			continue;
		}
	}

	while (a) {
		res.poly.simple_push_back(a->coeff, a->power);
		a = a->next;
	}
	while (b) {
		res.poly.simple_push_back(b->coeff, b->power);
		b = b->next;
	}
	res.remove_zeros();
	return res;
}

Polynom Polynom::operator* (double c) {
	Polynom res;
	Node* a = this->poly.head;
	while (a != 0) {
		res.poly.simple_push_back(a->coeff * c, a->power);
		a = a->next;
	}
	res.remove_zeros();
	return res;
}

Polynom Polynom::operator- (const Polynom& other) {
	Polynom negative = other;
	negative = negative * (-1);
	return (*this) + negative;
}

Polynom Polynom::operator* (const Polynom& other) {
	Polynom res;
	Node* a = this->poly.head;
	Node* b = other.poly.head;
	while (b != 0) {
		while (a != 0) {
			if ((*a).can_multiply(b)) res.poly.push_back(a->coeff * b->coeff, a->power + b->power);
			else throw std::runtime_error("degree overflow");
			a = a->next;
		}
		b = b->next;
		a = this->poly.head;
	}

	res.remove_zeros();

	return res;
}