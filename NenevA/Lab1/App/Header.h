#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <vector>   
#include <algorithm>
#include <sstream>  
#include <cmath>    
#include <stdexcept>
#include <limits>   
using namespace std;

struct Monomial {
    double Coefficient;
    int Degrees;
    Monomial() : Coefficient(0), Degrees(0) {};
    Monomial(double C, int D) : Coefficient(C), Degrees(D) {};
    bool operator<(const Monomial& other) const { return Degrees > other.Degrees; }
    bool operator==(const Monomial& other) const { return Degrees == other.Degrees && fabs(Coefficient - other.Coefficient) < 0.000001; }
    bool operator!=(const Monomial& other) const { return !(*this == other); }
};

struct Node {
    Monomial Elem;
    Node* next;
    Node(Monomial M) : Elem(M), next(nullptr) {};
    ~Node() = default;
};

class my_list {
private:
    Node* head;
    Node* tail;
    size_t _size;

public:
    class iterator {
    private:
        Node* current_node;
        friend class my_list;
    public:
        explicit iterator(Node* ptr = nullptr);
        Monomial& operator*() const;
        Monomial* operator->() const;
        iterator& operator++();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    class const_iterator {
    private:
        const Node* current_node;
        friend class my_list;
    public:
        explicit const_iterator(const Node* ptr = nullptr);
        const Monomial& operator*() const;
        const Monomial* operator->() const;
        const_iterator& operator++();
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    };


    my_list();
    ~my_list();
    my_list(const my_list& other);
    my_list& operator=(my_list other);
    bool empty() const;
    size_t size() const;
    void clear();
    void emplace_back(Monomial M);
    void emplace_back(double c, int d);
    void sort();


    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
};

class Polinomial {
private:
    my_list Data;
public:
    void simplify();
    Polinomial() {};
    Polinomial(const Polinomial& other);
    Polinomial(const string s);
    bool operator==(const Polinomial& other) const;
    bool operator!=(const Polinomial& other) const;
    Polinomial& operator=(const Polinomial& other);
    Polinomial operator+(const Polinomial& other) const;
    Polinomial operator-(const Polinomial& other) const;
    Polinomial operator*(const Polinomial& other) const;
    Polinomial operator*(const double Mult);

    friend ostream& operator <<(ostream& out, const Polinomial& P) {
        if (P.Data.empty()) return out << "0";
        bool firstTerm = true;

        for (my_list::const_iterator it = P.Data.begin(); it != P.Data.end(); ++it) {
            const Monomial& m = *it;
            if (fabs(m.Coefficient) < 0.000001) {
                continue;
            }
            if (!firstTerm) {
                if (m.Coefficient > 0) {
                    out << " + ";
                }
                else {
                    out << " - ";
                }
            }
            else if (m.Coefficient < 0) {
                out << "-";
            }
            double absCoeff = fabs(m.Coefficient);
            if (m.Degrees == 0 || fabs(absCoeff - 1.0) > 0.000001) {
                out << absCoeff;
            }
            int degX = m.Degrees / 100;
            int degY = (m.Degrees / 10) % 10;
            int degZ = m.Degrees % 10;
            bool hasVariable = false;

            if (degX > 0) {
                out << "x";
                if (degX > 1) out << "^" << degX;
                hasVariable = true;
            }
            if (degY > 0) {
                if (hasVariable) out << " ";
                out << "y";
                if (degY > 1) out << "^" << degY;
                hasVariable = true;
            }
            if (degZ > 0) {
                if (hasVariable) out << " ";
                out << "z";
                if (degZ > 1) out << "^" << degZ;
                hasVariable = true;
            }
            firstTerm = false;
        }
        return out;

    }

    friend istream& operator>>(istream& in, Polinomial& P) {
        string input;
        if (getline(in, input)) P = Polinomial(input);
        return in;
    }
};

