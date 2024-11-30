#pragma once
#include <stdexcept>
#include <iostream>

template <class T>
class TQueue {
private:
	int begin;
	int end;
	size_t capacity;
	T* pMem;
	int cnt;

public:
	TQueue() : begin(0), end(0), capacity(1), cnt(0) {
		setlocale(LC_ALL, "Russian");
		pMem = new T[capacity];
	}

	~TQueue() {
		delete[] pMem;
	}

	bool IsEmpty() {
		return cnt == 0;
	}

	void Push(T val) {
		if (cnt == capacity) {
			Resize(capacity * 2);
		}
		pMem[end] = val;
		end = (end + 1) % capacity;
		cnt++;
	}

	T Pop() {
		if (IsEmpty()) {
			throw std::underflow_error("Очередь пуста");
		}
		T tmp = pMem[begin];
		begin = (begin + 1) % capacity;
		cnt--;
		if (cnt > 0 && cnt == capacity / 4) {
			Resize(capacity / 2);
		}
		return tmp;
	}

	T ViewFirst() {
		if (IsEmpty()) {
			throw std::underflow_error("Очередь пуста");
		}
		return pMem[begin];
	}

private:
	void Resize(size_t newCapacity) {
		T* newMem = new T[newCapacity];
		for (size_t i = 0; i < cnt; i++) {
			newMem[i] = pMem[(begin + i) % capacity];
		}
		delete[] pMem;
		pMem = newMem;
		capacity = newCapacity;
		begin = 0;
		end = cnt;
	}
};