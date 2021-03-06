// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SeqStack.h"
#include <iostream>

using namespace std;

void SeqStackTest(){
	cout << "第一步: 创建一个默认栈(默认大小为5),将 0~10 入栈并打印元素\n";
	SeqStack<int> stack;
	for (int i = 0; i < 11; i++) {
		stack.push(i);
	}
	cout << "打印结果: " << stack.toString() << " 栈顶元素: "<< stack.top() << endl << endl;
	cout << "第二步: 获得栈的相关信息\n";
	cout << "元素个数: " << stack.length() << " 栈容量(自动变容):" << stack.capacity() << " 栈顶元素: " << stack.top() << endl << endl;
	cout << "第三步: 出栈6个元素并打印相关信息\n";
	for (int i = 0; i < 6; i++) {
		stack.pop();
	}
	cout << "打印结果: " << stack.toString() << endl;
	cout << "元素个数: " << stack.length() << " 栈容量(自动变容):" << stack.capacity() << " 栈顶元素: " << stack.top() << endl << endl;
	cout << "第四步: 清空栈并打印相关信息\n";
	stack.clear();
	cout << "元素个数: " << stack.length() << " 栈容量(自动变容):" << stack.capacity() << endl << endl;
	cout << "最后一步: 异常测试\n";
	cout << "尝试对空栈进行pop操作时: ";
	try {
		stack.pop();
	}
	catch (out_of_range e) {
		cout << "Exception:" << e.what() << endl;
	}
	cout << "尝试访问空栈的栈顶时:    ";
	try {
		stack.top();
	}
	catch (out_of_range e) {
		cout << "Exception: " << e.what() << endl;
	}
	cout << "测试结束!";
}

int main()
{
	SeqStackTest();
	cin.get();
    return 0;
}

