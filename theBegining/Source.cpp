#include <cmath>
#include "Header.h"
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;
namespace VECTOR {
	const double Rad_to_dec = 45.0 / atan(1.0);
	
	void Vector::set_mag() {
		mag = sqrt(x * x + y * y);
	}
	void Vector::set_ang(){
		if (x == 0 && y == 0) ang = 0;
		else ang = atan(y / x);
	}
	void Vector::set_x() {
		x = mag * cos(ang);
	}
	void Vector::set_y() {
		y = mag * sin(ang);
	}
	
	Vector::Vector() {
		x = y = mag = ang = 0;
		mode = Mode::RECT;
	}
	Vector::Vector(double n1, double n2, Mode form) {
		mode = form;
		if (form == Mode::RECT) {
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == Mode::POL) {
			mag = n1;
			ang = n2;
			set_x();
			set_y();
		}
		else {
			cout << "Incorrect MODE, used default instruction\n";
			x = y = mag = ang = 0;
			mode = Mode::RECT;
		}
	}
	void Vector::reset(double n1, double n2, Mode form) {
		mode = form;
		if (form == Mode::RECT) {
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == Mode::POL) {
			mag = n1;
			ang = n2;
			set_x();
			set_y();
		}
		else {
			cout << "Incorrect MODE, used default instruction\n";
			x = y = mag = ang = 0;
			mode = Mode::RECT;
		}

	}
	Vector::~Vector() {}

	void Vector::polar_mode() {
		mode = Mode::POL;
	}
	void Vector::rect_mode() {
		mode = Mode::RECT;
	}

	Vector Vector::operator+(const Vector& a) const {
		return Vector(x + a.x, y + a.y);
	}
	Vector Vector::operator-(const Vector& a) const {
		return Vector(x - a.x, y - a.y);
	}
	Vector Vector::operator*(double a) const {
		return Vector(x *a, y*a);
	}
	Vector Vector::operator-() const {
		return Vector(-x, -y);
	}

	Vector operator*(double a, const Vector& b) {
		return b * a;
	}

	std::ostream& operator<<(std::ostream& os, const Vector& a) {
		if (a.mode == Vector::Mode::RECT) os << a.x << ' ' << a.y;
		else if (a.mode == Vector::Mode::POL) os << a.mag << ' ' << a.ang * Rad_to_dec;
		else os << "Invalide mode";
		return os;
	}

}























































/*#include <iostream>

/*class vector {
	int size;
	int* vec;
public:
	vector(int);
	~vector();
	int& operator[](int index);
};

vector::vector(int size) {
	std::cout << "constructor" << std::endl;
	if (size <= 0) throw("Incorrect size of vector!");
	this->size = size;
	vec = new int[size];
}

vector::~vector() {
	std::cout << "destructor" << std::endl;
	delete[] vec;
}

int& vector::operator[](int i) {

	return vec[i];
}
*/


