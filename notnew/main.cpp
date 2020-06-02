#include <iostream>
#include <string>
using namespace std;

class A {
	
public:
	int x = 0;
};
class B: public A {
public:
	int y = 2;
	void get() {
		cout << x << ' ' << y << ' ';;
	}
	void set(int a) { y = a;  x = a * 2; }
};
int main(){
	B m, n;
	n.set(342);
	m = n;
	m.get();
	n.get();
	m = n;
}