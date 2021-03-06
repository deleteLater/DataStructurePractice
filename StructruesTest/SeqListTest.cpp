// SeqList.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SeqList.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void SeqListExampleCodes() {
	srand((unsigned)time(NULL));
	cout << "第一步: 初始化能容纳 15 个元素(以整数为例)的顺序表并打印表信息\n";
	SeqList<int> list(15);
	cout << list.info() << endl <<endl;
	cout << "第二步: 向顺序表中写入随机整数(0~100)并打印元素 \n";
	for (int i = 0; i < 15; i++) {
		list.append(rand() % 100);
	}
	cout << list.toString()<<endl<<endl;
	cout << "第三步: 修改下标为 5 的元素为 1000:\n";
	cout << "修改前的值: " << list.at(5) << endl;
	list.at(5) = 1000;
	cout << "修改后的值: " << list.at(5) << endl << endl;
	cout << "第四步: 对表进行排序(以升序为例)\n";
	list.sort(SORT_PATTERN::Ascending);
	cout << list.toString() << endl << endl;
	cout << "第五步: 对表元素进行逆置\n";
	list.reverse();
	cout << list.toString() << endl << endl;
	cout << "第六步: 删除下标 2~7 的元素\n";
	for (int i = 0; i < 6; i++) {
	list.deleteE(list.at(2)); //使用该方法连续删除的时候一定要注意！！！ 不是deleteE(list.at(i))
	}
	cout << list.toString() << endl << endl;
	cout << "由于自动变容机制---"<<list.info() << endl << endl;
	cout << "第七步: 在下标为3处插入10个随机数\n";
	for (int i = 3; i < 13; i++) {
		list.insert(rand()% 100, 3);
	}
	cout << list.toString() << endl << endl;
	cout << "由于自动变容机制---" << list.info() << endl << endl;
	cout << "最后一步: 越界访问异常测试,当尝试访问下标为1000的元素\n";
	try {
		cout << list.at(1000);	//越界访问
		SeqList<int> l(10000);	//超过了表最大容量
	}
	catch (OutOfAccessException e) {
		e.printErrorMessage();
		cout << endl;
	}
	try {
		cout << "尝试创建超过最大容量(10000)的表时:\n";
		SeqList<int> l(100000);	//超过了表最大容量
	}
	catch (OutOfAccessException e) {
		e.printErrorMessage();
	}
	cout << "\n测试结束!(注:这里仅测试了一些常用方法, 还有new异常未测试)";
}

int main()
{
	SeqListExampleCodes();
	cin.get();
    return 0;
}