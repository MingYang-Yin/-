#include "stackDef.h"
bool flag = true;

void stack::push(int e) {
	if (top - base >= stacksize) {//���ջ���������ӳ���
		base = (int *)realloc(base, (stacksize + STACKINCREAMENT) * sizeof(int));//����ջ������
		top = base + stacksize;//�ı�ջ��ָ��
		stacksize += STACKINCREAMENT;//�ı�ջ�ļ�������
	}
	if (!base)//����ڴ�������򷵻�
		return;
	*top++ = e;
}//������eѹ��ջ


int stack::pop() {
	if (top == base) {//��ջΪ�գ���ӡ������
		
		return -1;
	}
	else
		return *--top;
}//��ջ��Ԫ�ص���ջ

int stack::top1() {
	int *temp = top;
	if (top == base) {//��ջΪ�գ���ӡ������
		return -1;
	}
	else
		return *--temp;
}//��ջ��Ԫ�ص���ջ

int stack::printStack(int i) {
	int *temp = base;
	if ((temp+i) != top) {
		return *(temp + i);
	}
	else
		return -1;
}
