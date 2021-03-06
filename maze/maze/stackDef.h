#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;
#define STACK_INIT_SIZE 5//栈的初始长度
#define STACKINCREAMENT 20//每次栈的增加长度
class stack {
private:
	int *base;//栈底指针
	int *top;//栈顶指针
	int stacksize;//保存栈的大小
public:
	stack() {
		base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
		top = base;
		stacksize = STACK_INIT_SIZE;
	}//初始化栈
	void push(int e);//将数据压入栈
	int pop();//将数据弹出栈
	int top1();//返回栈顶元素值
	int printStack(int i);//打印栈中元素
};
