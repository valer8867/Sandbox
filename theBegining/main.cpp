#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Header.h"

int main() {
	using namespace std;
	using VECTOR::Vector;
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	int steps = 0;
	double target;
	double dstep;

	cout << "Enter targer distanse (q to quit): ";

	while (cin >> target) {
		cout << "Enter step lenght: ";
		if (!(cin >> dstep)) break;
		while (result.magval() < target) {
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::Mode::POL);
			result = result + step;
			++steps;
		}
		cout << "After " << steps << " steps, the subject"
			"has the following location:\n";
		cout << result << endl;
		result.polar_mode();
		cout << "or\n" << result << endl;
		cout << "Average outward distance per step = "
			<< result.magval() / steps << endl;

		steps = 0;
		result.reset(0.0, 0.0);
		cout << "Enter targer distanse (q to quit): ";
	}
	cout << "Bye\n";
	cin.clear();
	while (cin.get() != '\n') continue;
	
		
}