// Hanoi.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void moveDisk(int disk, char src, char des) {
	cout << "Move disk " << disk << " from " << src << " to " << des << endl;
}

void Hanio(int scale, char srcPillar,char auxPillar,char desPillar) {
	if (scale == 1) {
		moveDisk(1, srcPillar, desPillar);
		return ;
	}
	else {
		Hanio(scale - 1, srcPillar, desPillar, auxPillar);
		moveDisk(scale,srcPillar,desPillar);
		Hanio(scale - 1, auxPillar, srcPillar, desPillar);
	}
}

int main()
{
	Hanio(3,'A','B','C');
	cin.get();
    return 0;
}

