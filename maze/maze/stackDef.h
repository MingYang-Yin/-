#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;
#define STACK_INIT_SIZE 5//ջ�ĳ�ʼ����
#define STACKINCREAMENT 20//ÿ��ջ�����ӳ���
class stack {
private:
	int *base;//ջ��ָ��
	int *top;//ջ��ָ��
	int stacksize;//����ջ�Ĵ�С
public:
	stack() {
		base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
		top = base;
		stacksize = STACK_INIT_SIZE;
	}//��ʼ��ջ
	void push(int e);//������ѹ��ջ
	int pop();//�����ݵ���ջ
	int top1();//����ջ��Ԫ��ֵ
	int printStack(int i);//��ӡջ��Ԫ��
};
