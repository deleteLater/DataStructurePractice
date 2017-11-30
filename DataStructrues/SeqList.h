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

																		//该类不具有线程安全性,空间利用率(元素多于16时)大于等于75%(size/capacity>=75%)
#define MAX_CAPACITY 10000												//该顺序表的最大容量
#define DEFAULT_INIT_CAPACITY 16										//默认的初始容量值
template <class T>
class SeqList {
public:
	SeqList(int Capacity = -1);											//构造一个默认SeqList(默认容量为10)
	SeqList(const T arr[],int size,int Capacity = -1);					//按给定参数初始化SeqList
	~SeqList();															//释放空间 
	void insert(T value, const int index);								//把value插入到下标为index的地方
	void append(T value);												//将value追加到表尾
	int search(T &value) const;											//查找值为value的元素并返回其下标,返回-1查找失败
	void deleteE(T value);												//将值为value的数据从表中移除
	T& at(int index);													//返回下标为index元素的引用
	void sort(SORT_PATTERN pattern);									//按给定排序模式排序
	string toString() const;											//将顺序表中的元素装换成string
	void reverse();														//元素逆置
	bool isEmpty() const { return (size == 0); };						//判断表是否为空
	int Size() const { return this->size; };							//元素个数
	int Capacity() const { return this->capacity; };					//list容量(capacity >= size)
	double utilization() const { return (double)size / (double)capacity; };	//当前list的空间使用率
	string info();														//打印当前表的相关信息
private:
	T *datas;															//指向T[]
	int size;															//表的大小(等于元素个数)
	int capacity;														//表的容量
	void reCapacity(int newCapacity);									//改变容量
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
	oss << "当前表容量:" << Capacity() << ",元素数量:" << Size() << ",空间使用率: " << utilization();
	return oss.str();
}