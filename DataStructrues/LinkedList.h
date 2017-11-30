#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

enum class EXCEPTION {OutOfBoundaryAccess,EmptyListOperation};
class Exception {
public:
	Exception(EXCEPTION e) {
		if (e == EXCEPTION::EmptyListOperation) {
			error = "TryToOperateEmptyList!";
		}
		else {
			error = "OutOfBoundaryAccess!";
		}
	}
	void printErrorMessage() {
		cout << "Exeption Occured: " << error;
	}
private:
	string error;
};

template <class T>
class Node {
public:
	T data;
	Node* next;
	Node() {
		data = T();
		next = nullptr;
	}
	Node(T value) {
		data = value;
		next = nullptr;
	}
};

template <class T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	void add(T value);
	void remove(T value);
	int search(T value);
	void insert(T value,int pos);
	void clear();
	void reverse();
	string toString();
	void printNodesInfo();
	Node<T>& getNode(int index);
	void getAllNodes(vector<Node<T>> &nodes);
	const int length() { return Length; };
	bool isEmpty() { return (first->next == nullptr); };
private:
	Node<T>* first;
	int Length;
};

template <class T>
LinkedList<T>::LinkedList() {
	Length = 0;
	first = new Node<T>(NULL);
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node<T>* temp = first;
	while (first != nullptr) {
		first = first->next;
		delete temp;
		temp = first;
	}
	Length = 0;
}

template <class T>
void LinkedList<T>::add(T value) {
	Node<T>* newNode = new Node<T>(value);
	Node<T>*temp = first;
	while (temp->next != nullptr)
		temp = temp->next;
	temp->next = newNode;
	Length++;
}

template <class T>
int LinkedList<T>::search(T value) {
	if (this->isEmpty())
		throw Exception(EXCEPTION::EmptyListOperation);
	Node<T>* temp = first->next;
	int index = 0;
	while (temp->next != nullptr) {
		if (temp->data == value)
			return index;
		else
			index++;
	}
	return -1;
}

template <class T>
void LinkedList<T>::insert(T value,int pos) {
	if (pos < 0 || pos > Length)
		throw Exception(EXCEPTION::OutOfBoundaryAccess);
	Node<T> *newNode = new Node<T>(value);
	Node<T> *temp = first;
	for (int i = 0; i < pos; i++) {
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
	Length++;
}

template <class T>
void LinkedList<T>::remove(T value) {
	if (this->isEmpty())
		throw Exception(EXCEPTION::EmptyListOperation);
	Node<T>* temp = first;
	while (temp->next != nullptr && temp->next->data != value) {
		temp = temp->next;
	}
	if (temp->next == nullptr) {
		cout << "remove value failed!NoSuchElement!\n";
		return;
	}else{
		Node<T>* curNode = temp->next;
		temp->next = temp->next->next;
		delete curNode;
		curNode = nullptr;
		Length--;
	}
}

template <class T>
Node<T>& LinkedList<T>::getNode(int index) {
	if (index == 0)
		return *first;
	if (index > Length)
		throw Exception(EXCEPTION::OutOfBoundaryAccess);
	if (this->isEmpty())
		throw Exception(EXCEPTION::EmptyListOperation);
	Node<T>* temp = first->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return *temp;
}

template <class T>
string LinkedList<T>::toString() {
	if (this->isEmpty()) {
		return "EmptyList!\n";
	}
	ostringstream oos;
	oos << '[';
	Node<T>* temp = first->next;
	for (int i = 0; i < Length - 1; i++) {
		oos << temp->data << ',';
		temp = temp->next;
	}
	oos << temp->data << ']';
	return oos.str();
}

template <class T>
void LinkedList<T>::getAllNodes(vector<Node<T>> &nodes) {
	if (this->isEmpty())
		throw Exception(EXCEPTION::EmptyListOperation);
	Node<T> *temp = first->next;
	for (int i = 0; i < Length; i++) {
		nodes.push_back(*temp);
		temp = temp->next;
	}
}

template <class T>
void LinkedList<T>::clear() {
	if (this->isEmpty())
		throw Exception(EXCEPTION::EmptyListOperation);
	Node<T> *temp = first->next;
	Node<T> *temp_2 = temp;
	while(temp_2 != nullptr) {
		temp_2 = temp_2->next;
		delete temp;
		temp = temp_2;
	}
	first->next = nullptr;
	Length = 0;
}

template <class T>
void LinkedList<T>::printNodesInfo() {
	cout << "头节点--地址: " << first << " 数据域:" << first->data << " 指针域:" << first->next << endl;
	Node<T>* temp = first->next;
	for (int i = 0; i < Length; i++) {
		cout << "节点"<< (i+1) <<"--地址: "<<temp<<" 数据域:"<< temp->data << " 指针域:" << temp->next << endl;
		temp = temp->next;
	}
}

template <class T>
void LinkedList<T>::reverse() {
	if (this->isEmpty())
		return;
	Node<T> *p1 = first->next;
	Node<T> *p2 = nullptr;
	Node<T> *p3 = nullptr;
	while (p1->next != nullptr) {
		p2 = p1->next;
		p3 = p2->next;
		p2->next = first->next;
		first->next = p2;
		p1->next = p3;
	}
}