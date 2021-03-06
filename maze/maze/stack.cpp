#include "stackDef.h"
bool flag = true;

void stack::push(int e) {
	if (top - base >= stacksize) {//如果栈满，则增加长度
		base = (int *)realloc(base, (stacksize + STACKINCREAMENT) * sizeof(int));//增加栈的容量
		top = base + stacksize;//改变栈顶指针
		stacksize += STACKINCREAMENT;//改变栈的计数变量
	}
	if (!base)//如果内存溢出，则返回
		return;
	*top++ = e;
}//将数据e压入栈


int stack::pop() {
	if (top == base) {//若栈为空，打印输出完毕
		
		return -1;
	}
	else
		return *--top;
}//将栈顶元素弹出栈

int stack::top1() {
	int *temp = top;
	if (top == base) {//若栈为空，打印输出完毕
		return -1;
	}
	else
		return *--temp;
}//将栈顶元素弹出栈

int stack::printStack(int i) {
	int *temp = base;
	if ((temp+i) != top) {
		return *(temp + i);
	}
	else
		return -1;
}
