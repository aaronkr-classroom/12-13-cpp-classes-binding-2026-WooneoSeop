// Core.h
#pragma once

#ifndef GUARD_CORE_H
#define GUARD_CORE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Core {
private: // 숨기고 싶은 변수
	string name;
	friend class Student_info;

protected:
	double midterm, final;
	vector<double> homework;
	istream& read_common(istream&);

	// 사본 만들기
	virtual Core* clone() const { 
		return new Core(*this);
	}

public: // 접근할 수 있는 함수
	// ###### 생성자 ######
	Core() : midterm(0), final(0) { }; // 빈 객체를 생성
	Core(istream& is) { // 스트림을 읽어 객체를 생성
		read(is);
	}	
	// 윗 생성자가 read_hw() 함수와 비슷해

	// ###### 멤버 함수 정의 ######
	string getName() const { return name; }
	void setName(string n) { name = n; }

	double getMidterm() const { return midterm; }		// FIX
	double getFinal() const { return final; }			// FIX
	vector<double> getHw() const { return homework; }	// FIX

	bool valid() const { return !homework.empty(); }

	// 9.2.1/254p에서 정의한 함수들
	virtual istream& read(istream&);
	virtual double grade() const;

	// 소멸자
	virtual ~Core() { }

}; // 세미콜론을 잊지 않도록 주의

// 전역 함수 정의
bool compare(const Core&, const Core&);
bool compare_grades(const Core&, const Core&);
bool compare_Core_ptrs(const Core*, const Core*);

#endif
