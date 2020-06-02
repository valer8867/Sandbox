#ifndef HEADER_H_
#define HEADER_H_
#include <iostream>
namespace VECTOR {
	class Vector {
	public:
		enum class Mode{RECT, POL};
	private:
		double x;
		double y;
		double mag;
		double ang;
		Mode mode;
		void set_mag();
		void set_ang();
		void set_x();
		void set_y();

	public:
		
		Vector();
		Vector(double n1, double n2, Mode form = Mode::RECT);
		void reset(double n1, double n2, Mode form = Mode::RECT);
		~Vector();
		double xval() const { return x; }
		double yval() const { return y; }
		double magval() const { return mag; }
		double angval() const { return ang; }

		void polar_mode();
		void rect_mode();
		Vector operator+(const Vector&) const;
		Vector operator-(const Vector&) const;
		Vector operator-() const;
		Vector operator*(double) const;

		friend Vector operator*(double, const Vector&);
		friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
	};
}
#endif // !HEADER_H_