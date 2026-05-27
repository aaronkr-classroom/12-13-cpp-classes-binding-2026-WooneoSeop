// Student_info.h
#pragma once

#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <iostream>
#include <string>
#include <vector>
#include "Core.h"
#include "Grad.h"

using namespace std;

class Student_info {
private: // 숨기고 싶은 변수
	Core* cp;


public: // 접근할 수 있는 함수
	// ###### 생성자 ######
	Student_info() : cp(0) { } // 빈 객체를 생성
	Student_info(istream& is) : cp(0) { read(is); } // xc스트림을 읽어 객체를 생성
	// 윗 생성자가 read_hw() 함수와 비슷해

	// ###### 멤버 함수 정의 ######
	string getName() const { return cp->getName(); }
	void setName(string n) { cp->setName(n); }

	double getMidterm() const { return cp->getMidterm(); }		// FIX
	double getFinal() const { return cp->getFinal(); }			// FIX
	vector<double> getHw() const { return cp->getHw(); }	// FIX

	// bool valid() const { return !homework.empty(); }

	// 9.2.1/254p에서 정의한 함수들
	istream& read(istream&);
	double grade() const {
		if (cp) return cp->grade();
		else throw runtime_error("Uninitialized student !");

	}

	static bool compare(const Student_info&x, const Student_info&y) {
		return x.getName() < y.getName();
	}

}; // 세미콜론을 잊지 않도록 주의




#endif
