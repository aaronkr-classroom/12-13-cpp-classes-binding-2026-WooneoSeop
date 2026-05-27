// Core.cpp

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Core.h"
#include "Grad.h"
#include "Vec.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

int main() {

	vector<Core*> students; // 객체가 아닌 포인터를 저장
	Core* record; // 일시적 변수는 반드시 포인터 타입
	char ch;
	string::size_type maxlen = 0;

	// 데이터를 읽고 저장하기
	while (cin >> ch) {
		if (cin.eof()) break; // EOF 끝내기
		
		// 'U'나 'G'만 받기
		if (ch != 'U' && ch != 'G') { // U일 때만 또는 G일 때만 받기 나올 수도
			// 학생 아닌 타입이면 건너뛰기
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (ch == 'U')
			record = new Core;
		else if (ch == 'G')
			record = new Grad;
		record->read(cin);

		maxlen = max(maxlen, record->getName().size());
		students.push_back(record);
	}

	// 포인터로 동작하는 compare 함수를 전달
	sort(students.begin(), students.end(), compare_Core_ptrs);
	
	// 이름과 점수 출력
	for (vector<Core*>::size_type i = 0; i != students.size(); ++i) {
		// dynamic_cast를 사용하여 학생의 타입 확인
		if (dynamic_cast<Grad*>(students[i])) {
			cout << "(G ) "; //대학원생입니다.
		}
		//else if(dynamic_cast<Foreign*>(students[i])){
		//	cout << "(F ) "; // 외국인입니다.
		//} //이렇게 만들듯 근데 Foreign이라는 헤더랑 cpp를 만들어야하지 않을까 싶음
		else {
			cout << "(U ) "; // 대학생입니다.
		}

		// 함수를 호출하려고 포인터인 students[i]를 역참조
		cout << students[i]->getName() << string(maxlen + 1 - students[i]->getName().size(), ' ');
		try {
			double final_grade = students[i]->grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl;
		}
		delete students[i]; // 읽어 들인 객체의 할당을 해제
	}
	

	return 0;
}
