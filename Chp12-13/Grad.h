#pragma once
// Grad.h

#ifndef GUARD_GRAD_H
#define GUARD_GRAD_H

#include <iostream>
#include "Core.h"

using namespace std;

class Grad : public Core {
public:
	Grad() : thesis(0) { }
	Grad(istream& is) { read(is); }
	double grade() const;
	istream& read(istream&);

private:
	double thesis;
	Grad* clone() const { return new Grad(*this); }
};


#endif // !GUARD_GRAD_H
