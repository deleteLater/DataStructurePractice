#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <sstream>
using namespace std;

enum class EXCEPTION { OutOfMaxCapacity, OutOfBoundary };
enum class SORT_PATTERN {Ascending,Descending};
class OutOfAccessException {
public:
	OutOfAccessException() {
		this->error = "EmptyError";
	}
	OutOfAccessException(EXCEPTION exc) {
		if (exc == EXCEPTION::OutOfMaxCapacity) {
			error = "OutOfAccessException:Beyond the MaxCapacity";
		}
		else if (exc == EXCEPTION::OutOfBoundary) {
			error = "OutOfAccessException:Beyond the Array's Boundary";
		}
	}
	void printErrorMessage() {
		cout << "Exception Occured: " << error << endl;
	}
private:
	string error;
};

void MyNewHandler() {
	cerr << "Bad_Allocation Occured!";
	exit(1);
}

																		//���಻�����̰߳�ȫ��,�ռ�������(Ԫ�ض���16ʱ)���ڵ���75%(size/capacity>=75%)
#define MAX_CAPACITY 10000												//��˳�����������
#define DEFAULT_INIT_CAPACITY 16										//Ĭ�ϵĳ�ʼ����ֵ
template <class T>
class SeqList {
public:
	SeqList(int Capacity = -1);											//����һ��Ĭ��SeqList(Ĭ������Ϊ10)
	SeqList(const T arr[],int size,int Capacity = -1);					//������������ʼ��SeqList
	~SeqList();															//�ͷſռ� 
	void insert(T value, const int index);								//��value���뵽�±�Ϊindex�ĵط�
	void append(T value);												//��value׷�ӵ���β
	int search(T &value) const;											//����ֵΪvalue��Ԫ�ز��������±�,����-1����ʧ��
	void deleteE(T value);												//��ֵΪvalue�����ݴӱ����Ƴ�
	T& at(int index);													//�����±�ΪindexԪ�ص�����
	void sort(SORT_PATTERN pattern);									//����������ģʽ����
	string toString() const;											//��˳����е�Ԫ��װ����string
	void reverse();														//Ԫ������
	bool isEmpty() const { return (size == 0); };						//�жϱ��Ƿ�Ϊ��
	int Size() const { return this->size; };							//Ԫ�ظ���
	int Capacity() const { return this->capacity; };					//list����(capacity >= size)
	double utilization() const { return (double)size / (double)capacity; };	//��ǰlist�Ŀռ�ʹ����
	string info();														//��ӡ��ǰ��������Ϣ
private:
	T *datas;															//ָ��T[]
	int size;															//��Ĵ�С(����Ԫ�ظ���)
	int capacity;														//�������
	void reCapacity(int newCapacity);									//�ı�����
};

template<class T>
SeqList<T>::SeqList(int Capacity) {
	set_new_handler(MyNewHandler);
	this->size = 0;
	if (Capacity > MAX_CAPACITY)
		throw OutOfAccessException(EXCEPTION::OutOfMaxCapacity);
	if (Capacity == -1)
		this->capacity = DEFAULT_INIT_CAPACITY;
	else
		this->capacity = Capacity;
	datas = new T[capacity];
}

template<class T>
SeqList<T>::SeqList(const T arr[], int size, int Capacity) {
	set_new_handler(MyNewHandler);
	if (initCapacity > MAX_CAPACITY) {
		throw OutOfAccessException(EXCEPTION::OutOfMaxCapacity);
	}
	if (initCapacity == -1)
		this->capacity = 4 * size / 3 + 1;
	else
		this->capacity = initCapacity;
	datas = new T[this->capacity];
	this->size = size;
	for (int i = 0; i < this->size; i++) {
		datas[i] = arr[i];
	}
}

template <class T>
SeqList<T>::~SeqList() {
	for (int i = 0; i < size; i++) {
		datas[i] = NULL;
	}
	delete[] datas;
	datas = nullptr;
}

template <class T>
void SeqList<T>::reCapacity(int newCapacity) {
	set_new_handler(MyNewHandler);
	if (newCapacity > MAX_CAPACITY)
		throw OutOfAccessException(EXCEPTION::OutOfMaxCapacity);
	T *temp = new T[newCapacity];
	for (int i = 0; i < this->size; i++) {
		temp[i] = datas[i];
	}
	delete[] datas;
	datas = temp;
	temp = nullptr;
	this->capacity = newCapacity;
}

template <class T>
void SeqList<T>::insert(T value, const int index) {
	if (index > this->size) {
		throw OutOfAccessException(EXCEPTION::OutOfBoundary);
	}
	if (size == capacity && size < 7000)
		reCapacity((int)4 * capacity / 3 + 1);
	else if (size == capacity && size > 7000)
		reCapacity(size + 500);
	for (int i = this->size-1; i >= index; i--)
		datas[i + 1] = datas[i];
	datas[index] = value;
	this->size++;
}

template<class T>
void SeqList<T>::append(T value) {
	insert(value, this->size);
}

template <class T>
int SeqList<T>::search(T &value) const {
	for (int i = 0; i < this->size; i++) {
		if (datas[i] == value)
			return i;
	}
	return -1;
}

template <class T>
void SeqList<T>::deleteE(T value) {
	int index = search(value);
	if (index == -1) {
		cout << "delete failed!--NoSuchElement!";
		return;
	}
	else
	{
		for (int i = index; i < this->size-1; i++) {
			datas[i] = datas[i + 1];
		}
	}
	this->size--;
	if (size < 3 * capacity / 4 && size>0) {
		reCapacity((int)3 * capacity / 4 - 1);
	}
}

template <class T>
T& SeqList<T>::at(int index) {
	if (index > this->size - 1) {
		throw OutOfAccessException(EXCEPTION::OutOfBoundary);
	}
	return datas[index];
}

template <class T>
void SeqList<T>::sort(SORT_PATTERN pattern) {
	//Bubble Sort
	for (int i = 0; i < this->size; i++) {
		for (int j = i + 1; j < this->size; j++) {
			if (datas[i] > datas[j] && pattern == SORT_PATTERN::Ascending)
				swap(datas[i], datas[j]);
			else if (datas[i] < datas[j] && pattern == SORT_PATTERN::Descending)
				swap(datas[i], datas[j]);
		}
	}
}

template <class T>
void SeqList<T>::reverse() {
	for (int i = 0; i < this->size / 2; i++) {
		swap(datas[i],datas[this->size-i-1]);
	}
}

template <class T>
string SeqList<T>::toString() const {
	ostringstream os;
	os << '[';
	for (int i = 0; i < size-1; i++) {
		os << datas[i] << ',';
	}
	os << datas[size - 1] << ']';

	return os.str();
}

template <class T>
string SeqList<T>::info() {
	ostringstream oss;
	oss << "��ǰ������:" << Capacity() << ",Ԫ������:" << Size() << ",�ռ�ʹ����: " << utilization();
	return oss.str();
}