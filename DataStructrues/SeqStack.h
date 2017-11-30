#pragma once

#define DEFAULT_STACK_SIZE 5
#include <sstream>
using namespace std;

template <class T>
class SeqStack {
public:
	SeqStack(int initSize = -1);
	~SeqStack();
	void push(T value);
	T pop();
	T top();
	bool isEmpty() { return (Top == -1); }
	void clear();
	string toString();
	const int capacity() { return size; }
	int length() { return (Top + 1); }
private:
	int Top;
	int size;
	T *datas;
	void resize(int newSize);
};

template <class T>
SeqStack<T>::SeqStack(int initSize) {
	Top = -1;
	if (initSize == -1)
		initSize = DEFAULT_STACK_SIZE;
	datas = new T[initSize];
	size = initSize;
}

template <class T>
SeqStack<T>::~SeqStack() {
	delete[] datas;
}

template <class T>
void SeqStack<T>::push(T value) {
	if ((++Top) == size)
		resize(2 * size);
	datas[Top] = value;
}

template <class T>
T SeqStack<T>::pop() {
	if (this->isEmpty())
		throw out_of_range("EmptyStack_PopError!");
	if (Top>0 && Top == size / 4)
		resize(size / 2);
	return datas[Top--];
}

template <class T>
T SeqStack<T>::top() {
	if (this->isEmpty())
		throw out_of_range("EmptyStack_GetTopError!");
	return datas[Top];
}

template <class T>
void SeqStack<T>::resize(int newSize) {
	T *temp = new T[newSize];
	for (int i = 0; i < newSize; i++) {
		temp[i] = datas[i];
	}
	delete[]datas;
	datas = temp;
	temp = nullptr;
	size = newSize;
}

template <class T>
void SeqStack<T>::clear() {
	while (!this->isEmpty()) {
		this->pop();
	}
}

template <class T>
string SeqStack<T>::toString() {
	ostringstream oos;
	if (!this->isEmpty()) {
		for (int i = 0; i < this->length() - 1; i++) {
			oos << i << " ";
		}
		oos << datas[Top];
	}
	return oos.str();
}