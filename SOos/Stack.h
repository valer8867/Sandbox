#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename T>
class Stack {
private:
	vector<T> elems;
	char a{ 'a' };
	char b[5]{ '1','2','3','4','5' };
public:
	void push(T const& elem);
	void pop();
	T const& top() const;
	bool is_empty() const {
		return elems.empty();
	}
	template<typename T>
	friend ostream& operator<<(ostream& os, Stack<T> const& st);
};


template<typename T>
void Stack<T>::push(T const& elem)
{
	elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop()
{
	static_assert(!elems.empty());
	elems.pop_back();
}

template<typename T>
T const& Stack<T>::top() const
{
	assert(!elems.empty());
	return elems.back();
}

template<typename T>
ostream& operator<<(ostream& os, Stack<T> const& st)
{
	return os << st.b[2];
}
