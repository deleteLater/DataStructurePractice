#pragma once

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//class Node
template <class T>
class Node {
public:
	Node(T value) {
		this->value = value;
		this->next = nullptr;
	}
	T value;
	Node *next;
};

//Exception 
enum class EXCEPTION {EmptyQueueGetFront,EmptyQueueGetTail,EmptyQueueDeQueue};
class OutOfAccessException {
public:
	OutOfAccessException(EXCEPTION e) {
		if (e == EXCEPTION::EmptyQueueDeQueue) {
			this->error = "Try to DeQueue EmptyQueue!";
		}
		else if (e == EXCEPTION::EmptyQueueGetFront) {
			this->error = "Try to GetFront from EmptyQueue!";
		}
		else
			this->error = "Try yo GetTail from EmptyQueue!";
	}
	void printErrorMessage() {
		cout << "Exception: " << error << endl ;
	}
private:
	string error;
};

//API of LinkedQueue
template <class T>
class LinkedQueue {
private:
	Node<T> *front;
	Node<T> *tail;
	int N;
public:
	LinkedQueue();
	~LinkedQueue();
	void EnQueue(T value);
	int DeQueue();
	T getFront();
	T getTail();
	void clear();
	string toString();
	bool isEmpty() { return (N == 0); };
	int size() { return N; };
}; 

template <class T>
LinkedQueue<T>::LinkedQueue() {
	//construct a empty queue
	N = 0;
	front = nullptr;
	tail = nullptr;
}

template <class T>
LinkedQueue<T>::~LinkedQueue() {
	//destruct a queue(delete all nodes && resetting it to be empty)
	Node<T> * temp = front;
	while (temp) {
		front = front->next;
		delete temp;
		temp = front;
	}
	front = nullptr;
	tail = nullptr;
	N = NULL;
}

template <class T>
void LinkedQueue<T>::EnQueue(T value) {
	Node<T> *newNode = new Node<T>(value);
	//the first node should be specially treated
	if (N == 0) {
		front = newNode;
		tail = newNode;
		N++;
	}
	else {
		tail->next = newNode;
		tail = newNode;
		N++;
	}
}

template <class T>
int LinkedQueue<T>::DeQueue() {
	if (N == 0) {
		throw OutOfAccessException(EXCEPTION::EmptyQueueDeQueue);
	}
	//the last node should be specially treated
	else if (N == 1) {
		int value = front->value;
		delete front;
		front = nullptr;
		tail = nullptr;
		N--;
		return value;
	}
	else
	{
		Node<T> *oldFront = front;
		front = front->next;
		N--;
		delete oldFront;
		oldFront = nullptr;
		return oldFront->value;
	}
}

template <class T>
T LinkedQueue<T>::getFront() {
	if (N == 0)
		throw OutOfAccessException(EXCEPTION::EmptyQueueGetFront);
	return front->value;
}

template <class T>
T LinkedQueue<T>::getTail() {
	if (N == 0)
		throw OutOfAccessException(EXCEPTION::EmptyQueueGetTail);
	return tail->value;
}

template <class T>
string LinkedQueue<T>::toString() {
	if (N == 0) {
		return "";
	}
	ostringstream oos;
	oos << "[";
	Node<T> *temp = front;
	for (int i = 0; i < N-1; i++) {
		oos << temp->value << ',';
		temp = temp->next;
	}
	oos << tail->value <<"]";
	return oos.str();
}

template <class T>
void LinkedQueue<T>::clear() {
	while (N != 0) {
		this->DeQueue();
	}
}