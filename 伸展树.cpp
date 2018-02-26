             // 伸展树.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SplayTree.h"

int main()
{
	SplayTree S1;
	for (int i = 11; i < 70; i += 6)
		S1.Insert(i);
	S1.Display();

	S1.Find(35);
	S1.Display();
	cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
	S1.Splay(41);
	S1.Display();
	cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
	S1.Remove(41);
	S1.Display();

    return 0;
}

