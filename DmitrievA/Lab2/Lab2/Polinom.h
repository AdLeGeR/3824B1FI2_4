"Copyright 2026 Alexey Dmitriev"
#pragma once
#include <iostream>
#include <string>

#include "List.h"

    using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::to_string;

enum ParseMode { Simple, Human };

class Monome;

class Polinom {
  List<Monome> monomes = List<Monome>();
  void normalize();

 public:
  ParseMode parseMode = Simple;
  Polinom();
  Polinom(const Polinom& other);
  explicit Polinom(double num);
  Polinom operator+(const Polinom& other) const;
  Polinom operator-(const Polinom& other) const;
  /*void addMonome(const Monome& monome) {
    for( List<Monome>::iterator it = monomes.begin(); it != monomes.end(); it++)
  { if (it->degree == monome.degree) { int coeff = it->coeff + monome.coeff; if
  (coeff != 0) { *it = Monome(coeff, it->degree);
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
  Polinom operator*(double num);
  Polinom operator*(const Polinom& other);
  Polinom& operator=(const Polinom& other);
  double evaluate(double x, double y, double z) const;
  friend istream& operator>>(istream& in, Polinom& polinom);
  friend ostream& operator<<(ostream& out, const Polinom& polinom);
};

class Monome {
  double coeff;
  int degree;
  friend class Polinom;
  int degree_sum() const;

 public:
  bool operator>(const Monome& other) const;
  bool operator<(const Monome& other) const;
  Monome();
  Monome(double coeff, int degree);
  Monome operator-() const;
  Monome operator*(double num) const;
  Monome operator*(const Monome& other) const;
  bool operator==(const Monome& other) const;
  friend istream& operator>>(istream& in, Monome& monome);
  friend ostream& operator<<(ostream& out, const Monome& monome);
};
