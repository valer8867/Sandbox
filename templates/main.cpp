#include<iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <ctime>
#include <map>
#include <cctype>
#include "Vine13.h"
#include <climits>
#include <array>

const int MIN_PER_HR = 60;

using namespace std;

class Customer {
private:
	int arrive;
	int processtime;
public:
	Customer() { arrive = processtime = 0; }
	void set(int when) {
		arrive = when;
		processtime = rand() % 3 + 1;
	}
	int when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item;

class Queue {
	static const int Q_SIZE = 10;
	struct Node {
		Item item;
		Node* next = nullptr;
	};
	Node* first;
	Node* last;
	const int size;
	int items;
public:
	explicit Queue(int size = Q_SIZE) : size(size) {
		first = last = nullptr;
		items = 0;
	}
	bool isEmpty() const {
		return items == 0;
	}
	bool isFull() const {
		return items == size;
	}
	bool enqueue(const Item&);
	bool dequeu(Item&);
	int count() const {
		return items;
	}
	~Queue() {
		Node* tmp;
		while (first!=nullptr) {
			tmp = first;
			first = first->next;
			delete tmp;
		}
	}
};

bool newcustomer(double x) {
	return (rand() * x / RAND_MAX < 1);
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	cout << "Maximum size of queue: ";
	int quesize;
	cin >> quesize;
	Queue line(quesize);
	cout << "Enter simulation hours: ";
	int hours;
	cin >> hours;
	double cyclelimit = static_cast<double>(hours) * MIN_PER_HR;
	cout << "Enter x clients for hour: ";
	double x;
	cin >> x;
	double xmin = MIN_PER_HR / x;
	Item tmp;
	int turnaways = 0;
	int customers = 0;
	int served = 0;
	int sum_line = 0;
	int wait_time = 0;
	int line_wait = 0;


	for (int cycle = 0; cycle < cyclelimit; ++cycle) {
		if (newcustomer(xmin)) {														//if new custormer
			if (line.isFull()) ++turnaways;
			else {
				customers++;
				tmp.set(cycle);
				line.enqueue(tmp);
			}
		}
		if (wait_time <= 0 && !line.isEmpty()) {
			line.dequeu(tmp);
			wait_time = tmp.ptime();
			line_wait += cycle - tmp.when();
			served++;
		}
		if (wait_time > 0) wait_time--;
		sum_line += line.count();
	}
	if (customers > 0) {
		cout << customers << " " << served << " " << turnaways << endl;
	}
	else cout << "No customers!" << endl;
	cout << "Done!" << endl;
	
}




bool Queue::enqueue(const Item& a) {
	if (isFull()) return false;
	Node* tmp = new Node;
	tmp->item = a;
	tmp->next = nullptr;
	++items;
	if (first == nullptr) first = tmp;
	else last->next = tmp;
	last = tmp;
	return true;
}

bool Queue::dequeu(Item& item) {
	if (first == nullptr) return false;
	item = first->item;
	Node* tmp = first;
	first = first->next;
	delete tmp;
	--items;
	if (first == nullptr) last = first;
	return true;
}
