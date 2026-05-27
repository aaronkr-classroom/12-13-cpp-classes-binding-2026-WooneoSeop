// Student_info.cpp
#include <iostream>

#include "grade.h"
#include "Student_info.h"

using namespace std;

// 생성자
Student_info::Student_info(const Student_info& s) : cp(0) {
    if (s.cp) cp = s.cp->clone();
}

// 입력 스트림에서 과제 점수를 읽어서 vector<double>에 넣음.
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        // 이전 내용을 제거
        hw.clear();

        // 입력을 위한 변수
        double x; // cin에서 사용하기 

        // 불변성: 지금까지 count개 점수를 입력받았으며
        // 입력받은 점수의 합은 sum
        while (in >> x) {
            hw.push_back(x);
        }

        // 다음 학생의 점수 입력 작업을 고려해 스트림을 지움
        in.clear();
    }
    return in;
}

istream& Student_info::read(istream& in) {
    delete cp; // 이전 객체 있으면 삭제

    char ch;
    in >> ch; // record 타입 입력

    // record 타입 확인
    if (ch == 'U') // 대학생
        cp = new Core(in);
    else // 대학원생 (G) - "F" 유학생 Thesis // 대신에 TOEIC  있을듯 (6/10에 다시)
        cp = new Grad(in);

    return in;
}

// = 연산자 추가
Student_info& Student_info::operator = (const Student_info& s) {
    if (&s != this) {
        delete cp;
        if (s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}
