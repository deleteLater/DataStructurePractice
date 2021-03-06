// LinkedList.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LinkedList.h"
#include <iostream>
#include <time.h>

using namespace std;

void LinkedListTestCodes() {
	srand((unsigned)time(NULL));
	cout << "第一步: 创建一个空单链表(以整形为例,带头节点!),并打印相关信息\n";
	LinkedList<int> list;
	list.printNodesInfo();
	cout << "当前链表是否为空: " << list.isEmpty() << endl ;

	cout << "\n第二步: 向单链表中追加10个随机数,并打印相关信息\n";
	for (int i = 0; i < 10; i++) {
		list.add(rand() % 100);
	}
	cout << "链表元素的数据域: " << list.toString() << endl;
	cout << "当前节点信息:\n";
	list.printNodesInfo();

	cout << "\n第三步: 增删节点测试";
	for (int i = 0; i < 5; i++) {
		list.remove(list.getNode(1).data);
	}
	cout << "\n删除 0~5 节点后:\n";
	list.printNodesInfo();
	cout << "在 2~5 处插入新节点后:\n";
	for (int i = 0; i < 3; i++) {
		list.insert(rand() % 100,2);
	}
	list.printNodesInfo();

	cout << "\n第四步: 将链表中的所有节点写入一个节点数组中并输出节点数组的数据域内容\n";
	vector<Node<int>> nodes;
	list.getAllNodes(nodes);
	for (auto value : nodes) {
		cout << value.data << " ";
	}

	cout << "\n\n第五步: 链表反转 && 清空链表\n";
	cout << "链表反转后:\n";
	list.reverse();
	list.printNodesInfo();
	cout << endl;
	list.clear();
	cout<<"清空链表后:\n";
	list.printNodesInfo();
	cout << "\n\n最后一步: 异常测试\n";
	cout << "尝试在大于链表长度位置插入节点时: \n";
	try {
		list.insert(101010,list.length()+1);
	}
	catch (Exception e) {
		e.printErrorMessage();
	}
	cout << "\n尝试获取链表中不可达的头节): \n";
	try {	
		list.getNode(2);
	}
	catch(Exception e){
		e.printErrorMessage();
	}
}

int main()
{
	LinkedListTestCodes();
	cin.get();
    return 0;
}

