#include <iostream>
#include <vector>
#include "stackDef.h"
using namespace std;
int maze[100][100];
bool mazeVisit[100][100];
bool mazeVisitY[100][100];
bool mazeVisitU[100][100];
bool mazeVisitL[100][100];

vector<int> seqX;//����·��
vector<int> seqY;//����·��
int mazeNum;
int allPath[20][100][2];
int index = 0;
int exitX;
int exitY;//���ڵ�x��y����
stack *stackX = new stack();
stack *stackY = new stack();
bool flag1 = false;//��¼�û������Ƿ�Ϊ��������false��ʾ��Ϊ��true��ʾΪ��
bool exam = false;

int examine(char a[]) {//����û��������Ƿ�Ϊ����
	flag1 = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "������һ����������" << endl;
			flag1 = false;
			break;
		}
	}
	if (flag1) {
		for (int j = 0; a[j] != 0; j++) {//���û�����������ַ�ת��Ϊ��
			result = result + (a[j] - 48) * pow(10, i - j - 1);
		}
		flag1 = true;
	}
	return result;
}

void init(int num) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			mazeVisit[i][j] = 0;
			mazeVisitY[i][j] = 0;
			mazeVisitU[i][j] = 0;
			mazeVisitL[i][j] = 0;
			maze[i][j] = 0;
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (i == 0 || i == num - 1) {
				maze[i][j] = 1;
			}
			if (j == 0 || j == num - 1) {
				maze[i][j] = 1;
			}
		}
	}
}

void getUserInput() {
	int k = 1;
	char tempL[20];//��ʱ�����û�����
	int c1, c2;
	cout << "***************************************************\n";
	while (flag1 == false) {
		cout << "�������Թ����к��У�С��100������2����";
		cin >> tempL;
		mazeNum = examine(tempL);
		if (mazeNum >= 100 || mazeNum <= 2) {
			cout << "�Թ����к���Ӧ��С��100��С��2��\n";
			flag1 = false;
		}
	}
	cout << "\n**********************��������**********************\n";
	cout << "�Թ���\n������1����ǽ��0����·\n��һȦǽ���Թ�Χ������\n�Թ����Ϊ����(1,1)�ĵ㣬����Ϊ("<< mazeNum - 2 <<","<<mazeNum - 2 <<")\n\n";
	cout << "���������Թ��е�ǽ�ڣ��Ե�����(x,y)��ʶ\nע������(0,0)�����������\n";
	cout << "\n**********************����ǽ��**********************\n";
	flag1 = false;
	init(mazeNum);
	exitX = mazeNum - 2;
	exitY = mazeNum - 2;//���ڵ�x��y����
	while (k == 1) {
		while (flag1 == false) {
			cout << "�������޷�ͨ�еĵ������x��";
			cin >> tempL;
			c1 = examine(tempL);
		}
		flag1 = false;
		while (flag1 == false) {
			cout << "�������޷�ͨ�еĵ������y��";
			cin >> tempL;
			c2 = examine(tempL);
		}
		cout << "\n";
		flag1 = false;
		if (c1 == 0 || c2 == 0) {
			if (c1 == 0 && c2 == 0) {
				k = 0;
			}
			else {
				cout << "��������һ��0��\n";
			}
		}
		else if (maze[c1][c2] == 1) {
			cout << "�õ��Ѿ�������Ϊǽ��\n";
		}
		else if (c1 > mazeNum - 1 || c2 > mazeNum - 1) {
			cout << "�Ƿ��ĵ��ţ�����������õ���������꣡\n";
		}
		else if (c1 == exitX && c2 == exitY) {
			cout << "�õ�Ϊ�Թ����ڣ���������Ϊ�޷�ͨ�У�\n";
		}
		else if (c1 == 1 && c2 == 1) {
			cout << "�õ�Ϊ�Թ���ڣ���������Ϊ�޷�ͨ�У�\n";
		}
		else {
			flag1 = false;
			maze[c1][c2] = 1;
		}
	}
	flag1 = false;
	cout << "\n";
}

//����������
void result() {
	int j = 0;
	for (int ele : seqX) {
		allPath[index][j][0] = ele;
		j++;
	}
	j = 0;
	for (int ele : seqY) {
		allPath[index][j][1] = ele;
		j++;
	}
	index++;
}

void result1() {
	int i = 0;
	for (int elex : seqX) {
		int eley = seqY[i];
		i++;
		cout << "(" << elex << "," << eley << ")  ";
	}
	cout << "(" << exitX << "," << exitY << ")  ";
	cout << "\n";
}

void Solution(int nodeX, int nodeY) {
	bool check = 0;//��֤�Թ��Ƿ��н�
	stackX->push(nodeX);//ѹ���Թ��������
	stackY->push(nodeY);
	int x = 0;
	int y = 0;
	while (stackX->top1() != -1) {//��ջ��Ϊ��
		x = stackX->top1();//ȡջ��Ԫ�ص�ֵ
		y = stackY->top1();
		if (x <= mazeNum - 2 && y <= mazeNum - 2) {
			if (x == exitX && y == exitY) {//���ߵ����ڣ���ӡ·��������
				cout << "�ҵ����ڣ�·��Ϊ��";
				int k = 0;
				while (stackX->printStack(k) != -1) {
					cout << "(" << stackX->printStack(k) << "," << stackY->printStack(k) << ")  ";
					k++;
				}
				cout << "\n";
				check = 1;
				break;
			}
			else {
				while (stackX->top1() != -1) {
					if (mazeVisitL[stackX->top1()][stackY->top1()] == 1) {//����ջ��Ԫ�ص�visit����
						mazeVisitL[stackX->top1()][stackY->top1()] == 0;
						mazeVisit[stackX->top1()][stackY->top1()] == 0;
						mazeVisitY[stackX->top1()][stackY->top1()] == 0;
						mazeVisitU[stackX->top1()][stackY->top1()] == 0;
						stackX->pop();
						stackY->pop();
					}
					else
						break;
				}
			}
			x = stackX->top1();//ȡջ��Ԫ�ص�ֵ
			y = stackY->top1();
			if (x != -1 && y != -1) {
				if (mazeVisit[x][y] == 0) {
					if (maze[x + 1][y] != 1) {//��û�����ҹ���������������ǽ
						stackX->push(x + 1);
						stackY->push(y);
						mazeVisit[x][y] = 1;
					}
					else
						mazeVisit[x][y] = 1;
				}
				x = stackX->top1();
				y = stackY->top1();
				if (mazeVisit[x][y] == 1 && mazeVisitY[x][y] == 0) {
					if (maze[x][y + 1] != 1) {////��û�����ҹ���������������ǽ
						stackX->push(x);
						stackY->push(y + 1);
						mazeVisitY[x][y] = 1;
					}
					else
						mazeVisitY[x][y] = 1;
				}
				x = stackX->top1();
				y = stackY->top1();
				if (mazeVisitY[x][y] == 1 && mazeVisitU[x][y] == 0) {
					if (maze[x-1][y] != 1) {//��û�����ҹ���������������ǽ
						stackX->push(x-1);
						stackY->push(y);
						mazeVisitU[x][y] = 1;
					}
					else
						mazeVisitU[x][y] = 1;
				}
				x = stackX->top1();
				y = stackY->top1();
				if (mazeVisitU[x][y] == 1 && mazeVisitL[x][y] == 0) {
					if (maze[x][y-1] != 1) {//��û�����ҹ���������������ǽ
						stackX->push(x);
						stackY->push(y-1);
						mazeVisitL[x][y] = 1;
					}
					else
						mazeVisitL[x][y] = 1;
				}
			}
			else
				break;
		}
	}
	if (check == 0) {
		cout << "û�к��ʵ�·��\n";
	}
}

int main() {
	getUserInput();
	cout << "\n*********************��ӡ�Թ�*********************\n";
	for (int i = 0; i < mazeNum; i++) {
		for (int j = 0; j < mazeNum; j++) {
			cout << maze[i][j] << " ";
		}
		cout << "\n";
	}
	Solution(1, 1);
	system("pause");
}
