#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <limits>

const double EPSILON = 1e-9; // Малое значение для сравнения с нулём.

struct Monom // Структура для представления монома.
{
	double coeff; // Коэффициент coefficient.
	size_t deg; // Степень degree. Трёхзначное число от 0 до 999, где сотни - это степень x, десятки - это степень y, единицы - это степень z.

	Monom(double coefficient = 0.0, size_t degree = 0) : coeff{ coefficient }, deg{ degree } {} // Конструктор по умолчанию и конструктор с параметрами.
};

struct Node // Структура для представления элемента списка.
{
	Monom data; // Данные типа Monom.
	Node* next; // Указатель на следующий элемент списка.

	Node(const Monom& data_, Node* next_ = nullptr) : data{ data_ }, next{ next_ } {} // Конструктор по умолчанию и конструктор с параметрами.
};

class Forward_list_with_f_head // Объявление класса для представления односвязного списка с фиктивной головой.
{
	size_t size; // Размер списка.
	Node* head; // Указатель на голову списка.

	Node* find_middle_elem(Node* node_); // Метод для нахождения среднего элемента списка, который используется в алгоритме сортировки слиянием. Node_ - не фиктивная голова. Разрывает связь списка по среднему элементу.

	Node* merge(Node* left, Node* right); // Метод для слияния двух отсортированных частей списка, который используется в алгоритме сортировки слиянием.

	Node* merge_sort(Node* node_); // Node_ - не фиктивная голова. Рекурсиявная функция для сортировки списка с помощью алгоритма сортировки слиянием. Разделяет список на две части, сортирует каждую часть рекурсивно и затем сливает отсортированные части обратно в один отсортированный список.

	friend class Polynomial; // Объявление класса Polynomial дружественным.

public:
	Forward_list_with_f_head(); // Конструктор по умолчанию.

	Forward_list_with_f_head(const Forward_list_with_f_head& other_list); // Конструктор копирования.

	void clear(); // Очистка списка.

	~Forward_list_with_f_head(); // Деструктор.

	Forward_list_with_f_head& operator=(const Forward_list_with_f_head& other_list); // Перегруженный оператор присваивания.

	bool is_empty() const; // Метод проверки списка на пустоту.

	void sort(); // Метод сортировки списка с помощью алгоритма сортировки слиянием. 

	void push_front(double coeff_, size_t deg_); // Метод добавления нового элемента в начало списка (после фиктивной головы).
};

class Polynomial // Ообъявление класса для представления полинома, который будет дружественным классу Forward_list_with_f_head.
{
	Forward_list_with_f_head polynom; // Односвязный список для хранения мономов полинома.

public:
	Polynomial(); // Конструктор по умолчанию.

	Polynomial(const std::vector<std::pair<double, size_t>>& source); // Конструктор создания полинома с данными из source.

	Polynomial(const Polynomial& other_polynom); // Конструктор копирования.

	~Polynomial(); // Деструктор.

	Polynomial& operator=(const Polynomial& other_polynom); // Перегруженный оператор присваивания.

	Polynomial operator+(const Polynomial& other_polynom) const; // Перегруженный оператор сложения полиномов (алгоритм слияния упорядоченных массивов).

	Polynomial operator*(const double& val) const; // Перегруженный оператор умножения полинома на константу val.

	Polynomial operator-(const Polynomial& other_polynom) const; // Перегруженный оператор вычитания полиномов.

	Polynomial operator*(const Polynomial& other_polynom) const; // Перегруженный оператор умножения полиномов.

	void print_polynom() const;  // Метод для вывода полинома.

	bool is_empty(); // Метод проверки на пустоту полинома.
};

// Realization Forward_list_with_f_head:

Node* Forward_list_with_f_head::find_middle_elem(Node* node_) // Метод для нахождения среднего элемента списка, который используется в алгоритме сортировки слиянием. Node_ - не фиктивная голова.
{
	if (node_ == nullptr || node_->next == nullptr) // Если список пустой (то есть если указатель на следующий элемент после фиктивной головы равен nullptr) или содержит только один элемент (то есть если указатель на следующий элемент после первого элемента указывает на nullptr), то возвращаем nullptr, так как нет среднего элемента.
	{
		return nullptr;
	}

	Node* slow = node_; // Указатель slow - медленный указатель, который будет двигаться по одному элементу за итерацию в цикле обхода.
	Node* fast = node_->next; // Указатель fast - быстрый указатель, который будет двигаться по два элемента за итерацию в цикле обхода.

	while (fast != nullptr && fast->next != nullptr) // Пока указатель fast не достигнет конца списка (то есть пока fast не равен nullptr) и пока указатель fast->next не достигнет конца списка (то есть пока fast->next не равен nullptr), двигаем указатели.
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	Node* middle = slow->next; // Указатель middle - это средний элемент списка. Используется для указания на вторую часть списка после его разделения на две части в алгоритме сортировки слиянием.
	slow->next = nullptr; // Разрываем связь между первой половиной списка (которая начинается с node_) и второй половиной списка (которая начинается с middle), чтобы разделить список на две части для дальнейшей сортировки.

	return middle;
}

Node* Forward_list_with_f_head::merge(Node* left, Node* right) // Метод для слияния двух отсортированных частей списка, который используется в алгоритме сортировки слиянием. left - указатель на левую (первую) часть списка, right - указатель на правую (вторую) часть списка.
{
	if (!left) // Если указатель на левую часть списка равен nullptr, то возвращаем правую часть списка, так как левая часть пройдена и правая уже отсортирована.
	{
		return right;
	}
	if (!right) // Если указатель на правую часть списка равен nullptr, то возвращаем левую часть списка, так как правая часть пройдена и левая уже отсортирована.
	{
		return left;
	}

	if (left->data.deg > right->data.deg) // Сравниваем степени мономов в левой и правой части списка. Если степень монома в левой части больше, то он должен идти первым в результирующем отсортированном списке.
	{
		left->next = merge(left->next, right); // Рекурсивно вызываем merge для следующего элемента в левой части списка и текущего элемента в правой части списка. Позволяет продолжать сравнивать элементы в левой части списка с элементами в правой части списка, пока не достигнем конца одной из частей списка.
		return left; // Возвращаем указатель на элемент с большей степенью, который ожидается предыдущим элементом в результирующем отсортированном списке как next.
	}
	else if (left->data.deg < right->data.deg) // Аналогично. Если степень монома в правой части больше, то он должен идти первым в результирующем отсортированном списке.
	{
		right->next = merge(left, right->next);
		return right;
	}
	else // Если степени мономов в левой и правой части равны, то мы должны сложить их коэффициенты. 
	{
		left->data.coeff = left->data.coeff + right->data.coeff;
		Node* next = merge(left->next, right->next);
		delete right;

		if (std::fabs(left->data.coeff) < EPSILON) // Если абсолютное значение (std::fabs) суммы коэффциентов мономов меньше, чем EPSILON, то считаем сумму коэфциентов равной 0.
		{
			delete left; // Удаляем элемент списка.
			return next; // Возвращаем указатель, для предыдующего элемента как next, на следующий элемент после этих двух равных по степени мономов.
		}
		else // Иначе добавляем новый моном в результирующий отсортированный список.
		{
			left->next = next;
			return left;
		}
	}
}

Node* Forward_list_with_f_head::merge_sort(Node* node_) // Node_ - не фиктивная голова. Рекурсиявная функция для сортировки списка с помощью алгоритма сортировки слиянием. Разделяет список на две части, сортирует каждую часть рекурсивно и затем сливает отсортированные части обратно в один отсортированный список.
{
	if (node_ == nullptr || node_->next == nullptr) // Если список пустой (node_ == nullptr) или содержит только один элемент (node_->next == nullptr), то возвращаем указатель на текущий элемент, так как пустой список (или список из одного элемента) уже отсортирован.
	{
		return node_;
	}

	Node* middle = find_middle_elem(node_); // Находим средний элемент списка, который будет использоваться для разделения списка на две части для дальнейшей сортировки.

	Node* left = merge_sort(node_); // Рекурсивно сортируем первую (левую) половину списка, которая начинается с node_ и заканчивается на элементе перед middle.
	Node* right = merge_sort(middle); // Рекурсивно сортируем вторую (правую) половину списка, которая начинается с middle и заканчивается на последнем элементе списка.

	return merge(left, right); // Сливаем отсортированные части списка (левую и правую) обратно в один отсортированный список и возвращаем указатель на его первый элемент после фиктивной головы функцией merge.
}

Forward_list_with_f_head::Forward_list_with_f_head() // Конструктор по умолчанию.
{
	size = 0; // Инициализация размера списка нулём.
	head = new Node(Monom()); // Фиктивная голова списка, которая не содержит данных и служит для удобства работы со списком. Node(Monom()) - приминяются констуркторы по умолчанию структур Monom и Node.
}

Forward_list_with_f_head::Forward_list_with_f_head(const Forward_list_with_f_head& other_list) // Конструктор копирования.
{
	size = other_list.size; // Копируем размер списка.
	head = new Node(Monom()); // Создаём фиктивную голову.

	Node* current_other = other_list.head->next; // Указатель для обхода списка other_list, начиная с первого элемента после фиктивной головы.
	Node* current_this = head; // Указатель для обхода текущего списка, начиная с фиктивной головы.

	while (current_other) // Пока current_other не равен nullptr, то есть пока не достигнут конец списка other_list.
	{
		current_this->next = new Node(current_other->data); // Создание нового элемента текущего списка. Вызывается конструтор структуры Node для нового элемента, который инициализируется данными из current_other->data.

		current_this = current_this->next; // Переход к следующему элементу текущего списка.
		current_other = current_other->next; // Переход к следующему элементу списка other_list.
	}
}

void Forward_list_with_f_head::clear() // Очистка списка.
{
	while (head->next) // Пока head->next не равен nullptr, то есть пока не достигнут конец текущего списка.
	{
		Node* temp = head->next; // Запоминаем указатель на следующий элемент списка после фиктивной головы.
		head->next = head->next->next; // Обновляем указатель после фиктивной головы, чтобы он указывал на следующий элемент после удаляемого элемента.
		delete temp; // Удаляем элемент после фиктивной головы, который запомнили в temp.
	}
	size = 0; //Сброс размера текущего списка.
}

Forward_list_with_f_head::~Forward_list_with_f_head() // Деструктор.
{
	clear(); // Очищаем список от элементов.
	delete head; // Удаляем фиктивную голову списка.
}

Forward_list_with_f_head& Forward_list_with_f_head::operator=(const Forward_list_with_f_head& other_list) // Перегруженный оператор присваивания.
{
	if (this != &other_list) // Проверка на самоприсваивание.
	{
		Forward_list_with_f_head temp(other_list); // temp - временная копия other_list.

		std::swap(size, temp.size); // Меняем местами размеры списков.
		std::swap(head, temp.head); // Меняем местами указатели на головы списков.
	}

	return *this; // Возвращаем ссылку на текущий список после присваивания.
}

bool Forward_list_with_f_head::is_empty() const // Метод проверки списка на пустоту.
{
	return size == 0; // true - если список пуст, false - если список не пуст.
}

void Forward_list_with_f_head::sort() // Метод сортировки списка с помощью алгоритма сортировки слиянием. 
{
	head->next = merge_sort(head->next); // Сортируем список, начиная с первого элемента после фиктивной головы merge_sort(head->next). После сортировки head->next будет указывать на новый первый элемент отсортированного списка.

	size = 0; // Сбрасываем размер списка, так как он мог измениться после сортировки (из-за слияния мономов).
	for (Node* current = head->next; current != nullptr; current = current->next) // Подсчитываем размер отсортированного списка.
	{
		++size;
	}
}

void Forward_list_with_f_head::push_front(double coeff_, size_t deg_) // Метод добавления нового элемента в начало списка (после фиктивной головы).
{
	if (deg_ > 999) // Проверка на допустимость степени монома. (deg_ < 0) не может быть из-за типа size_t.
	{
		throw std::range_error("The degrees of the variables are greater than 9. The maximum degree of the polynomial is 999.\n");
	}

	if (std::fabs(coeff_) < EPSILON) // Проверка на нулевой коэффициент монома.
	{
		throw std::invalid_argument("The coefficient of the monomial must be different from 0.\n");
	}

	Node* new_node = new Node(Monom(coeff_, deg_), head->next); //Создаём новый элемент списка. Инициализируем его данными coeff_ и deg_ с помощью конструктора структуры Monom. И устанавливаем указатель на следующий элемент списка head->next.
	head->next = new_node; // Обновляем указатель после фиктивной головы, чтобы он указывал на новый элемент списка.
	++size; // Обновляем размер списка.
}

// Realization Polynomial:

Polynomial::Polynomial() {} // Конструктор по умолчанию. Вызывается конструктор по умолчанию для класса Forward_list_with_f_head.

Polynomial::Polynomial(const std::vector<std::pair<double, size_t>>& source) // Конструктор создания полинома с данными из source.
{
	size_t size_source = source.size(); // Запоминаем размер вектора source.

	for (size_t i = 0; i < size_source; ++i) // Записываем в полином данные из вектора source.
	{
		if (std::fabs(source[i].first) < EPSILON) // Проверка на нулевой коэффициент монома.
		{
			continue;
		}

		polynom.push_front(source[i].first, source[i].second); // Добавляем моном в полином.
	}

	polynom.sort(); // Сортируем полином, чтобы мономы были упорядочены по степеням и чтобы полином не имел подобных мономов.
}

Polynomial::Polynomial(const Polynomial& other_polynom) : polynom{ other_polynom.polynom } {} // Конструктор копирования. Вызывается конструктор копирования класса Forward_list_with_f_head.

Polynomial::~Polynomial() {} // Деструктор. Вызывается деструктор класса Forward_list_with_f_head.

Polynomial& Polynomial::operator=(const Polynomial& other_polynom) // Перегруженный оператор присваивания.
{
	if (this != &other_polynom) // Проверка на самоприсваивание.
	{
		this->polynom = other_polynom.polynom; // Вызываем перегруженный оператор присваивания для класса Forward_list_with_f_head.
	}

	return *this; // Возвращаем ссылку на текущий полином после присваивания. 
}

Polynomial Polynomial::operator+(const Polynomial& other_polynom) const // Перегруженный оператор сложения полиномов (алгоритм слияния упорядоченных массивов).
{
	Polynomial res_polynom; // Создаём новый полином - результат сложения полиномов.

	Node* this_current = this->polynom.head->next; // Указатель для обхода мономов первого (this) полинома.
	Node* other_current = other_polynom.polynom.head->next; // Указатель для обхода мономов второго (other_polynom) полинома.

	while (this_current != nullptr && other_current != nullptr) // Пока оба полинома не достигнут конца по мономам.
	{
		if (this_current->data.deg > other_current->data.deg) // Если степень монома первого (this) полинома больше, чем степень монома второго (other_polynom) полинома, то добавляем в результирующий полином моном первого (this) полинома.
		{
			res_polynom.polynom.push_front(this_current->data.coeff, this_current->data.deg);
			this_current = this_current->next; // Переход к следующему моному первого (this) полинома.
		}
		else if (this_current->data.deg < other_current->data.deg) // Если степень монома первого (this) полинома меньше, чем степень монома второго (other_polynom) полинома, то добавляем в результирующий полином моном второго (other_polynom) полинома.
		{
			res_polynom.polynom.push_front(other_current->data.coeff, other_current->data.deg);
			other_current = other_current->next; // Переход к следующему моному второго (other_polynom) полинома.
		}
		else // При равенстве степеней мононом полиномов складываем коэффициенты мономом, проверяем результат на равенство 0.
		{
			double sum_coeff = this_current->data.coeff + other_current->data.coeff; // Суммируем коэффциенты подобных мономов.

			if (!(std::fabs(sum_coeff) < EPSILON)) // Проверка на нулевой коэффициент монома.
			{
				res_polynom.polynom.push_front(sum_coeff, this_current->data.deg); // Добавляем в результирующий полином моном данной степени this_current->data.deg.
			}

			this_current = this_current->next; // Переход к следующему моному первого (this) полинома.
			other_current = other_current->next; // Переход к следующему моному второго (other_polynom) полинома.
		}
	}

	while (this_current != nullptr) // Если первый (this) полином не достиг конца по мономам, когда второй (other_polynom) полином достиг конца по мономам, то добавляем в результирующий полином оставшиеся мономы первого (this) полинома.
	{
		res_polynom.polynom.push_front(this_current->data.coeff, this_current->data.deg);
		this_current = this_current->next; // Переход к следующему моному первого (this) полинома.
	}

	while (other_current != nullptr) // Если второй (other_polynom) полином не достиг конца по мономам, когда первый (this) полином достиг конца по мономам, то добавляем в результирующий полином оставшиеся мономы второго (other_polynom) полинома.
	{
		res_polynom.polynom.push_front(other_current->data.coeff, other_current->data.deg);
		other_current = other_current->next; // Переход к следующему моному второго (other_polynom) полинома.
	}

	res_polynom.polynom.sort(); // Сортируем результирующий полином, так как он не отсортирован.

	return res_polynom; // Возвращаем результирующий полином после сложения.
}

Polynomial Polynomial::operator*(const double& val) const // Перегруженный оператор умножения полинома на константу val.
{
	Polynomial res_polynom; // Создаём новый полином - результат умножения на константу val.

	Node* this_current = this->polynom.head->next; // Указатель для обхода мономов текущего (this) полинома.

	while (this_current != nullptr) // Пока текущий (this) полином не достиг конца по мономам, умножаем коэффициент каждого монома на константу val, проверяем результат на равенство 0. Если он отличен от 0, то добавляем в результирующий полином моном данной степени с новым коэффициентом.
	{
		if (!(std::fabs(this_current->data.coeff * val) < EPSILON)) // Проверка на нулевой коэффициент монома.
		{
			res_polynom.polynom.push_front(this_current->data.coeff * val, this_current->data.deg);
		}

		this_current = this_current->next; // Переход к следующему моному текущего (this) полинома.
	}

	res_polynom.polynom.sort(); // Сортируем результирующий полином, так как он может быть не отсортирован.

	return res_polynom; // Возвращаем результирующий полином после умножения на константу val.
}

Polynomial Polynomial::operator-(const Polynomial& other_polynom) const // Перегруженный оператор вычитания полиномов.
{
	Polynomial res_polynom; // Создаём новый полином - результат вычитания полиномов.

	res_polynom = *this + (other_polynom * (-1)); // Применяем перегруженные операторы сложения полиномов и умножения полинома на константу для вычитания полиномов.

	return res_polynom; // Возвращаем результирующий полином после вычитания.
}

Polynomial Polynomial::operator*(const Polynomial& other_polynom) const // Перегруженный оператор умножения полиномов.
{
	Polynomial res_polynom; // Создаём новый полином - результат сложения полиномов.

	Node* this_current = this->polynom.head->next; // Указатель для обхода мономов первого (this) полинома.
	Node* other_current = other_polynom.polynom.head->next; // Указатель для обхода мономов второго (other_polynom) полинома.
	Node* temp_current = other_current; // Указать для возвращения к началу полинома other_polynom.

	size_t this_units = 0, this_tens = 0, this_hundreds = 0; // Единица, десятки, сотни в степени монома первого (this) полинома.
	size_t other_units = 0, other_tens = 0, other_hundreds = 0; // Единица, десятки, сотни в степени монома второго (other_polynom) полинома.
	size_t res_units = 0, res_tens = 0, res_hundreds = 0; // Единица, десятки, сотни в степени монома результирующего полинома.
	size_t res_deg = 0; // Степень монома результирующего полинома.

	// Обходим все мономы первого (this) полинома, умножая каждый из них на все мономы второго (other_polynom) полинома.
	while (this_current != nullptr)
	{
		while (other_current != nullptr)
		{
			double multi_coeff = this_current->data.coeff * other_current->data.coeff; // Вычисялем коэффциент нового монома - результата умножения двух мономов.

			if (!(std::fabs(multi_coeff) < EPSILON)) // Проверка на нулевой коэффициент монома результирующего полинома после умножения.
			{
				// Разбиваем степени мономов на единицы, десятки и сотни.
				this_units = this_current->data.deg % 10;
				this_tens = (this_current->data.deg / 10) % 10;
				this_hundreds = this_current->data.deg / 100;

				other_units = other_current->data.deg % 10;
				other_tens = (other_current->data.deg / 10) % 10;
				other_hundreds = other_current->data.deg / 100;

				// Единицы, десятки и сотни степени нового монома.
				res_units = this_units + other_units;
				res_tens = this_tens + other_tens;
				res_hundreds = this_hundreds + other_hundreds;

				if (res_units >= 10 || res_tens >= 10 || res_hundreds >= 10) // Если степень монома после умножения превышает 9 для любой из переменных, то выбрасываем исключение, так как максимальная степень полинома - 999 (9 для каждой переменной).
				{
					throw std::range_error("The degrees of the obtained variables are greater than 9. The maximum degree of a polynomial is 999.\n");
				}

				res_deg = res_units + res_tens * 10 + res_hundreds * 100; // Собираем новую степень монома результирующего полинома после умножения.

				res_polynom.polynom.push_front(multi_coeff, res_deg); // Добавляем в результирующй полином новый моном.
			}

			other_current = other_current->next; // Переход к следующему моному второго (other_polynom) полинома.
		}

		this_current = this_current->next; // Переход к следующему моному первого (this) полинома.

		other_current = temp_current; // Возвращаем указатель на начало второго (other_polynom) полинома (на его первый моном после фиктивной головы).
	}

	res_polynom.polynom.sort(); // Сортируем результирующий полином, так как он не отсортирован.

	return res_polynom; // Возвращаем результирующий полином после умножения полиномов.
}

void Polynomial::print_polynom() const  // Метод для вывода полинома в консоль.
{
	if (polynom.size != 0) // Если текущий полином не пуст, то выводим его.
	{
		Node* this_current = this->polynom.head->next; // Указатель для обхода мономов текущего (this) полинома.

		if (this_current->data.coeff < 0) // Если коэффициент первого монома текущего полинома отрицательный, то выводим знак минус перед ним.
		{
			std::cout << "-";
		}

		while (this_current != nullptr) // Пока текущий (this) полином не достиг конца по мономам, то выводим каждый моном данного полинома.
		{
			std::cout << std::fabs(this_current->data.coeff); // Выводим абсолютное значение коэффициента монома.

			// Выводим переменные монома, степень которых отлична от 0.
			if ((this_current->data.deg / 100) != 0)
			{
				std::cout << "x^" << (this_current->data.deg / 100);
			}

			if (((this_current->data.deg / 10) % 10) != 0)
			{
				std::cout << "y^" << ((this_current->data.deg / 10) % 10);
			}

			if ((this_current->data.deg % 10) != 0)
			{
				std::cout << "z^" << (this_current->data.deg % 10);
			}


			if (this_current->next != nullptr) // Если текущий моном не последний, то выводим знак коэффициента следующего после него монома.
			{
				if (this_current->next->data.coeff > 0)
				{
					std::cout << " +";
				}
				else
				{
					std::cout << " -";
				}
			}

			this_current = this_current->next; // Переход к следующему моному текущего (this) полинома.
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "The polynomial is empty.\n";
	}
}

bool Polynomial::is_empty() // Метод проверки текущего (this) полинома на пустоту.
{
	return this->polynom.is_empty(); // Вызываем метод is_empty() класса Forward_list_with_f_head для списка polynom.
}