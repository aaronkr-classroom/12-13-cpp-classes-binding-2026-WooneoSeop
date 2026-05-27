// Grad.cpp

#include <algorithm>
#include <vector>
#include "Grad.h"

using namespace std;

istream& read_hw(istream& in, vector<double>& hw);


istream& Grad::read(istream& in) {
	Core::read_common(in); // name, midterm, final 읽기
	in >> thesis;
	read_hw(in, homework);
	return in;
}

double Grad::grade() const {
	return min(Core::grade(), thesis);
}
