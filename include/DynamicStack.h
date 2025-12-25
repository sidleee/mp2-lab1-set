#pragma once

#include <iostream>

using namespace std;

template<class T>
class DynamicStack {
	int curr;
	int n;
	T* Mem;

	void addsize() {
		T* newMem = new T[n + 1];
		for (int i = 0; i < n; i++) 
			newMem[i] = Mem[i];
		delete[] Mem;
		Mem = newMem;
		n++;
	}
public:
	DynamicStack(int n = 0) {
		if (n < 0) throw - 1;
		curr = -1;
		this->n = n;
		Mem = new T[n];
	}
	DynamicStack(const DynamicStack& sample) {
		curr = sample.curr;
		n = sample.n;
		Mem = new T[n];
		for (int i = 0; i < n; i++) {
			Mem[i] = sample.Mem[i];
		}
	}
	~DynamicStack() {
		delete[] Mem;
	}
	DynamicStack& operator=(const DynamicStack& sample) {
		if (this == &sample) return *this;
		delete[] Mem;
		curr = sample.curr;
		n = sample.n;
		Mem = new T[n];
		for (int i = 0; i < n; i++) {
			Mem[i] = sample.Mem[i];
		}
	}
	void push(const T& el) {
		if (curr == n - 1) addsize();
		Mem[++curr] = el;
	}

	T pop() {
		if (curr < 0) throw - 1;
		return Mem[curr--];
	}
	T& top() {
		if (curr < 0) throw - 1;
		return Mem[curr];
	}
	bool isEmpty() {
		return curr == -1;
	}
};