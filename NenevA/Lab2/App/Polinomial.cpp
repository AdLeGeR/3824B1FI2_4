#include "Polinomial.h"
MyList::MyList() : head_(nullptr), tail_(nullptr), size_(0) {}

MyList::~MyList() { clear(); }

MyList::MyList(const MyList& other) : head_(nullptr), tail_(nullptr), size_(0) {
    for (const Monomial& m : other) EmplaceBack(m);
}

MyList& MyList::operator=(MyList other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
    return *this;
}

bool MyList::empty() const { return head_ == nullptr; }

size_t MyList::size() const { return size_; }

void MyList::clear() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

void MyList::EmplaceBack(const Monomial& m) {
    Node* p = new Node(m);
    if (empty()) {
        head_ = p;
        tail_ = p;
    }
    else {
        tail_->next = p;
        tail_ = p;
    }
    size_++;
}

void MyList::EmplaceBack(double c, int d) {
    EmplaceBack(Monomial(c, d));
}

void MyList::Sort() {
    if (empty() || head_ == tail_) return;
    bool swapped;
    Node* end_ptr = nullptr;
    do {
        swapped = false;
        Node* current = head_;
        while (current->next != end_ptr) {
            if (current->next->elem < current->elem) {
                std::swap(current->elem, current->next->elem);
                swapped = true;
            }
            current = current->next;
        }
        end_ptr = current;
    } while (swapped);
}


void Polinomial::Simplify() {
    if (data_.empty()) return;
    data_.Sort();
    MyList new_data;
    auto it = data_.begin();
    while (it != data_.end()) {
        double current_coeff = it->coefficient;
        int current_degree = it->degrees;
        ++it;
        while (it != data_.end() && it->degrees == current_degree) {
            current_coeff += it->coefficient;
            ++it;
        }
        if (std::fabs(current_coeff) > 0.000001) {
            new_data.EmplaceBack(current_coeff, current_degree);
        }
    }
    data_ = new_data;
}

Polinomial::Polinomial(const Polinomial& other) {
    for (auto it = other.data_.begin(); it != other.data_.end(); ++it) {
        data_.EmplaceBack(*it);
    }
}

Polinomial::Polinomial(const std::string& s) {
    std::istringstream iss(s);
    double coeff;
    int degree;
    std::vector<Monomial> temp_monomials;
    while (iss >> coeff >> degree) {
        if (degree > 999 || degree < 0) {
            throw std::runtime_error("Such values of degrees are not supported");
        }
        if (coeff) temp_monomials.emplace_back(coeff, degree);
    }

    if (!temp_monomials.empty()) {
        std::sort(temp_monomials.begin(), temp_monomials.end());
        for (const auto& m : temp_monomials) {
            data_.EmplaceBack(m);
        }
    }
    Simplify();
}

bool Polinomial::operator==(const Polinomial& other) const {
    if (data_.size() != other.data_.size()) return false;
    auto it1 = data_.begin();
    auto it2 = other.data_.begin();
    while (it1 != data_.end()) {
        if (!(*it1 == *it2)) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

bool Polinomial::operator!=(const Polinomial& other) const {
    return !(*this == other);
}

Polinomial& Polinomial::operator=(const Polinomial& other) {
    if (*this == other) return *this;
    Polinomial temp(other);
    std::swap(data_, temp.data_);
    return *this;
}

Polinomial Polinomial::operator+(const Polinomial& other) const {
    Polinomial result;

    auto a = data_.begin();
    auto b = other.data_.begin();

    while (a != data_.end() && b != other.data_.end()) {
        if (a->degrees == b->degrees) {
            double sum = a->coefficient + b->coefficient;
            if (std::fabs(sum) > 0.000001) {
                result.data_.EmplaceBack(sum, a->degrees);
            }
            ++a;
            ++b;
        }
        else if (a->degrees > b->degrees) {
            result.data_.EmplaceBack(*a);
            ++a;
        }
        else {
            result.data_.EmplaceBack(*b);
            ++b;
        }
    }
    while (a != data_.end()) {
        result.data_.EmplaceBack(*a);
        ++a;
    }

    while (b != other.data_.end()) {
        result.data_.EmplaceBack(*b);
        ++b;
    }
    return result;
}

Polinomial Polinomial::operator-(const Polinomial& other) const {
    Polinomial m(other), result = *this;
    result = result + m * -1;
    return result;
}

Polinomial Polinomial::operator*(const Polinomial& other) const {
    Polinomial result;
    std::vector<Monomial> temp1, temp2, res;

    for (auto& elem : this->data_) temp1.emplace_back(elem);
    for (auto& elem : other.data_) temp2.emplace_back(elem);

    for (auto& elem1 : temp1) {
        for (auto& elem2 : temp2) {
            int x = elem1.degrees / 100 + elem2.degrees / 100;
            int z = elem1.degrees % 10 + elem2.degrees % 10;
            int y = (elem1.degrees + elem2.degrees - z - 100 * x) / 10;
            if (x > 9 || y > 9 || z > 9) {
                throw std::runtime_error("Degrees over 9 aren't allowed");
            }
            int new_degree = z + y * 10 + 100 * x;
            double new_coeff = elem1.coefficient * elem2.coefficient;
            res.emplace_back(new_coeff, new_degree);
        }
    }

    for (auto& elem : res) result.data_.EmplaceBack(elem);

    result.Simplify();
    return result;
}

Polinomial Polinomial::operator*(double mult) const {
    Polinomial result(*this);
    for (auto& elem : result.data_) elem.coefficient *= mult;
    return result;
}

std::ostream& operator<<(std::ostream& out, const Polinomial& p) {
    if (p.data_.empty()) return out << "0";
    bool first_term = true;

    for (auto it = p.data_.begin(); it != p.data_.end(); ++it) {
        const Monomial& m = *it;
        if (std::fabs(m.coefficient) < 0.000001) {
            continue;
        }
        if (!first_term) {
            if (m.coefficient > 0) {
                out << " + ";
            }
            else {
                out << " - ";
            }
        }
        else if (m.coefficient < 0) {
            out << "-";
        }
        double abs_coeff = std::fabs(m.coefficient);
        if (m.degrees == 0 || std::fabs(abs_coeff - 1.0) > 0.000001) {
            out << abs_coeff;
        }
        int deg_x = m.degrees / 100;
        int deg_y = (m.degrees / 10) % 10;
        int deg_z = m.degrees % 10;
        bool has_variable = false;

        if (deg_x > 0) {
            out << "x";
            if (deg_x > 1) out << "^" << deg_x;
            has_variable = true;
        }
        if (deg_y > 0) {
            if (has_variable) out << " ";
            out << "y";
            if (deg_y > 1) out << "^" << deg_y;
            has_variable = true;
        }
        if (deg_z > 0) {
            if (has_variable) out << " ";
            out << "z";
            if (deg_z > 1) out << "^" << deg_z;
            has_variable = true;
        }
        first_term = false;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Polinomial& p) {
    std::string input;
    if (std::getline(in, input)) p = Polinomial(input);
    return in;
}