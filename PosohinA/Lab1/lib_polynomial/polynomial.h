#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H

#include"../lib_list/list.h"
#include<string>

class Polynomial {
	List view;

public:
	Polynomial();
	Polynomial(const List);
	~Polynomial();

	Polynomial& operator = (const Polynomial&);
	Polynomial operator + (const Polynomial&) const;
	Polynomial operator - (const Polynomial&) const;
	Polynomial operator * (double) const;
	Polynomial operator * (const Polynomial&) const;
	bool operator == (const Polynomial&) const;
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
	void record();
};

const Polynomial operator * (double, const Polynomial&) ;

int entering_degree(const char);
bool chek_deg(int, int);
#endif // !POLYNOMIAL_POLYNOMIAL_H
