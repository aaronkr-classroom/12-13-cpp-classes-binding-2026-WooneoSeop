#pragma once
// Vec.h
#ifndef GUARD_VEC_H
#define GUARD_VEC_H

#include <cstddef> // ptrdiff_t
#include <memory>
#include <algorithm>

using namespace std;

template <class T> class Vec {
public:
	// 속성
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type; // *i - *j
	typedef T& reference; // &
	typedef const T& const_reference; // const &

	/*
	Vec<int> grades;
	Vec<int> pass;
	pass = grades;
	1. operator 필요
	2. Vec() 사본 만든 생성자 필요

	*/

	// 생성자 (여러가지 필요함)
	// 1. 빈 객체
	Vec() { create(); }

	// 2. 벡터 크기와 선택적 초기값 정의하기
	explicit Vec(size_type n, const T& val = T()) { create(n, val); }

	// 3. 사본 만드는 생성자
	Vec(const Vec& v) { create(v.begin(), v.end()); }

	// 4. template 추가
	template <class In> Vec(In b, In e) {
		create(b, e);
	}

	// 연산자
	// 벡터 크기와 인덱스에 관한 새로운 함수들
	size_type size() const { return avail - data; }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	// 할당
	Vec& operator = (const Vec&);

	// 반복자
	// 반복자를 반환하는 새로운 함수
	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return avail; }
	const_iterator end() const { return avail; }

	// insert & assign 추가 ( 연습문제 12 + 13)
	template<class In> iterator insert(iterator, In, In); // Q12
	void assign(iterator, iterator); // Q13 assign is = 할당/정의

	// 인터페이스 = 미완성...
	void push_back(const T& val) {
		if (avail == limit) // 필요하다면 저장 공간 확보
			grow();

		unchecked_append(val); // 새로운 요소 추가
	}

	// Q9을 위해 추가
	void push_back_grow_once(const T& t) {
		grow_once();
		unchecked_append(t); // 새로운 요소 추가
	}
		

	// 소멸자
	~Vec() { uncreate(); }
	void clear() { uncreate(); }
	bool empty() const { return data == avail; } // 0 == 0 ? True : False
	

private:
	iterator data; // Vec의 첫 번째 요소를 가리키는 포인터
	iterator avail; // Vec의 마지막 요소 다음을 가리키는 포인터
	iterator limit; // 사용할 수 있는 마지막 요소의 다음을 가리키는 포인터
	
	allocator<T> alloc; // 메모리 할당 위해 관리하는 객체

	// 멤버 함수 (push_back 함수를 지원하는 함수)
	// 1. 생성자 : 메모리 할당 및 초기화 함수
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	// 2. 소멸자 : 메모리 해제
	void uncreate();

	// 3. 유틸리티 함수들 (push_back 지원하는 함수)
	void grow();
	void grow_once(); // Q9을 위해 추가
	void unchecked_append(const T&);
};

template <class T> Vec<T>& Vec<T>::operator = (const Vec& rhs) {
	// int i = 0;
	// lhs = left  - hand side (i) = 변수
	// rhs = right - hand side (0) = 값
	// 자가 할당 여부 확인
	if (&rhs != this) {
		// 좌변이 지닌 배열이 점유하는 메모리를 해제
		uncreate();

		// 우변이 지닌 요소를 좌변으로 복사
		create(rhs.begin(), rhs.end());
	}
	return *this;

}

template <class T> void Vec<T>::create() {
	data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val) {
	data = alloc.allocate(n); // #include <memory>
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j) {
	data = alloc.allocate(j - i);
	limit = avail = uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate() {
	if (data) {
		// 역순으로 모든 요소를 소멸하고 메모리 해제
		iterator it = avail; // 마지막 요소 다음을 가리키는 포인터
		while (it != data) // 첫 번째 요소를 가리키는 포인터까지
			alloc.destroy(--it);
		// 할당한 메모리 공간을 해제 (비우기)
		alloc.deallocate(data, limit - data);
	}
	// 모든 포인터를 재정의 (재설정)
	data = limit = avail = 0;
}

template <class T> void Vec<T>::unchecked_append(const T& val) {
	// 'avail' =  할당되지 않은  사용 가능 공간
	alloc.construct(avail++, val);
}

// 사용 가능한 공간은 다 채우면
// 벡터 크기를 2배로 증가하는 함수
template <class T> void Vec<T>::grow() {
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

	// 새로운 공간 할당하고 모든 있는 요소를 복사
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	// 구공간(old space)을 소멸
	uncreate();

	// 모든 포인터를 새로운 공간에서 가리킴
	data = new_data;
	avail = new_avail;
	limit = data + new_size;

}

// Q9을 위한 grow_once 함수 추가
template <class T> void Vec<T>::grow_once() {
	size_type new_size = limit - data + ptrdiff_t(1);

	// 새로운 공간 할당하고 모든 있는 요소를 복사
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	// 구공간(old space)을 소멸
	uncreate();

	// 모든 포인터를 새로운 공간에서 가리킴
	data = new_data;
	avail = new_avail;
	limit = data + new_size;

}

// 12장 - 연습문제 12
template<class T>
template <class In>
typename Vec<T>::iterator Vec<T> ::insert(iterator d, In b, In e) {
	// 끝 부분과 차이 저장
	Vec<T> end(d, avail); // d부터 끝까지 다른 Vec에서 data 저장
	ptrdiff_t diff = d - data;

	// 끝 부분 소멸하기
	if (d) {
		// 역방향으로 모든 요소 제거/삭제하기
		while (avail != d)
			alloc.destroy(--avail);
	}
		
	// b부터 e까지 요소를 추가하기
	while (b != e)
		push_back(*b++);

	// 다시 끝 부분 추가하기 ( 불러오기 )
	for (Vec<T> ::const_iterator it = end.begin(); it != end.end(); ++it)
		push_back(*it);

	return data + diff;
}

// 12장 - 연습문제 13
template <class T>
void Vec<T>::assign(iterator b, iterator e) {
	// Vec 소멸
	uncreate();

	// 모든 반복자의 요소를 추가하기
	while (b != e)
		push_back(*b++);
}
#endif // !GUARD_VEC_H
