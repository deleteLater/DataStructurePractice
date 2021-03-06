// LinkedQueue.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LinkedQueue.h"
#include <iostream>

using namespace std;

void LinkedQueueTest() {
	LinkedQueue<char> queue;
	cout << "第一步: 将HelloWolrd!入队，并打印队中元素:";
	string s = "HelloWorld!";
	for (char ch : s)
		queue.EnQueue(ch);
	cout << queue.toString() << endl << endl;
	cout << "第二步: 出队5个元素，并打印队中元素";
	for (int i = 0; i < 5; i++)
		queue.DeQueue();
	cout << queue.toString() << endl << endl;
	cout << "第三步: 获得当前队头和队尾元素";
	cout << "队头: " << queue.getFront() << "  队尾:" << queue.getTail() << endl << endl;
	cout << "第四步: 清空当前队列\n";
	queue.clear();
	cout << "当前队列是否为空: " << queue.isEmpty() << "  当前队列元素个数: " << queue.size() << endl << endl;

	cout << "最后一步: 异常测试";
	cout << "\n尝试对空队列执行出队的操作时:     ";
	try {
		queue.DeQueue();
	}
	catch (OutOfAccessException e) {
		e.printErrorMessage();
	}
	cout << "尝试对空队列执行获取队头的操作时: ";
	try {
		queue.getFront();
	}
	catch (OutOfAccessException e) {
		e.printErrorMessage();
	}
	cout << "尝试对空队列执行获取队尾的操作时: ";
	try {
		queue.getTail();
	}
	catch (OutOfAccessException e) {
		e.printErrorMessage();
	}
	cout << "测试结束!";
}

int main()
{
	LinkedQueueTest();
	cin.get();

    return 0;
}

