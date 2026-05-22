#ifndef LIB_LIST_LIST_H
#define LIB_LIST_LIST_H

#include <iostream>
#include <utility>

struct Node {
	std::pair<double, int> _val;
	Node* _next;
	Node(const std::pair<double, int>&, Node*);
};


class List
{
	Node* _head, * _tail;
public:
	List();
	List(const List&);
	~List();

	bool is_empty();
	void pop_front();
	void push_front(const std::pair<double, int>&) noexcept;
	void pop_back();
	void push_back(const std::pair<double, int>&) noexcept;
	void insert(Node* A, const std::pair<double, int>&);
	void clear() noexcept;
	List& operator = (const List&);

	class Iterator {
		Node* _current;
	public:
		Iterator();
		Iterator(Node* poc);
		Iterator(const Iterator& A);

		Iterator& operator =(const Iterator& A);
		std::pair<double, int>& operator*();
		bool operator != (const Iterator& A);
		bool operator == (const Iterator& A);
		Iterator operator ++(int);
		Iterator operator ++();
		Node* get_current();
	};
	 
	Iterator begin() const { return Iterator(_head); }
	Iterator end() const { return Iterator(); }
	typedef Iterator iterator;
};

int sum_numb(int);
#endif // !LIB_LIST_LIST_H