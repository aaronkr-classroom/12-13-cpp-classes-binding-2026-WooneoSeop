// median_T.h
#pragma once

#ifndef GUARD_median_T_h
#define GUARD_median_T_h

#include <algorithm>
#include <vector>
#include <stdexcept>

using namespace std;

// vector<double>의 중앙값을 구함 ~~
// 함수를 호출하면 인수로 제공된 백터를 통째로 복사
template<class T>
T median(vector<T> v) {
	// 과제 점수의 입력 유무를 확인
	typedef typename vector<T>::size_type vec_sz;
	vec_sz size = v.size();

	if (size == 0)
		throw domain_error("Median of empty vector!");

	// 점수를 정렬하기
	sort(v.begin(), v.end()); // <algorithm> 필요

	// 과제 점수의 중앙값을 구함
	vec_sz mid = size / 2;

	return size % 2 == 0 ?
		(v[mid] + v[mid - 1]) / 2 :
		v[mid];
}
#endif
