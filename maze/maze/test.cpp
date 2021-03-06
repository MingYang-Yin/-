#include <iostream>
#include <vector>
#include "stackDef.h"
using namespace std;
int maze[100][100];
bool mazeVisit[100][100];
bool mazeVisitY[100][100];
bool mazeVisitU[100][100];
bool mazeVisitL[100][100];

vector<int> seqX;//储存路径
vector<int> seqY;//储存路径
int mazeNum;
int allPath[20][100][2];
int index = 0;
int exitX;
int exitY;//出口的x、y坐标
stack *stackX = new stack();
stack *stackY = new stack();
bool flag1 = false;//记录用户输入是否为正整数（false表示不为，true表示为）
bool exam = false;

int examine(char a[]) {//检测用户的输入是否为数字
	flag1 = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "请输入一个正整数！" << endl;
			flag1 = false;
			break;
		}
	}
	if (flag1) {
		for (int j = 0; a[j] != 0; j++) {//将用户输入的数字字符转化为数
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
	char tempL[20];//暂时储存用户输入
	int c1, c2;
	cout << "***************************************************\n";
	while (flag1 == false) {
		cout << "请输入迷宫的行和列（小于100，大于2）：";
		cin >> tempL;
		mazeNum = examine(tempL);
		if (mazeNum >= 100 || mazeNum <= 2) {
			cout << "迷宫的行和列应该小于100，小于2！\n";
			flag1 = false;
		}
	}
	cout << "\n**********************宣读规则**********************\n";
	cout << "迷宫！\n规则：以1代表墙，0代表路\n有一圈墙将迷宫围了起来\n迷宫入口为坐标(1,1)的点，出口为("<< mazeNum - 2 <<","<<mazeNum - 2 <<")\n\n";
	cout << "请您输入迷宫中的墙壁，以点坐标(x,y)标识\n注：输入(0,0)代表输入结束\n";
	cout << "\n**********************输入墙壁**********************\n";
	flag1 = false;
	init(mazeNum);
	exitX = mazeNum - 2;
	exitY = mazeNum - 2;//出口的x、y坐标
	while (k == 1) {
		while (flag1 == false) {
			cout << "请输入无法通行的点的行数x：";
			cin >> tempL;
			c1 = examine(tempL);
		}
		flag1 = false;
		while (flag1 == false) {
			cout << "请输入无法通行的点的列数y：";
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
				cout << "不能输入一个0！\n";
			}
		}
		else if (maze[c1][c2] == 1) {
			cout << "该点已经被设置为墙！\n";
		}
		else if (c1 > mazeNum - 1 || c2 > mazeNum - 1) {
			cout << "非法的点编号！请重新输入该点的两个坐标！\n";
		}
		else if (c1 == exitX && c2 == exitY) {
			cout << "该点为迷宫出口，不能设置为无法通行！\n";
		}
		else if (c1 == 1 && c2 == 1) {
			cout << "该点为迷宫入口，不能设置为无法通行！\n";
		}
		else {
			flag1 = false;
			maze[c1][c2] = 1;
		}
	}
	flag1 = false;
	cout << "\n";
}

//储存结果函数
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
	bool check = 0;//验证迷宫是否有解
	stackX->push(nodeX);//压入迷宫入口坐标
	stackY->push(nodeY);
	int x = 0;
	int y = 0;
	while (stackX->top1() != -1) {//若栈不为空
		x = stackX->top1();//取栈顶元素的值
		y = stackY->top1();
		if (x <= mazeNum - 2 && y <= mazeNum - 2) {
			if (x == exitX && y == exitY) {//若走到出口，打印路径，返回
				cout << "找到出口，路径为：";
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
					if (mazeVisitL[stackX->top1()][stackY->top1()] == 1) {//重置栈顶元素的visit数组
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
			x = stackX->top1();//取栈顶元素的值
			y = stackY->top1();
			if (x != -1 && y != -1) {
				if (mazeVisit[x][y] == 0) {
					if (maze[x + 1][y] != 1) {//若没向下找过且向下走碰不到墙
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
					if (maze[x][y + 1] != 1) {////若没向右找过且向右走碰不到墙
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
					if (maze[x-1][y] != 1) {//若没向上找过且向上走碰不到墙
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
					if (maze[x][y-1] != 1) {//若没向左找过且向左走碰不到墙
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
		cout << "没有合适的路径\n";
	}
}

int main() {
	getUserInput();
	cout << "\n*********************打印迷宫*********************\n";
	for (int i = 0; i < mazeNum; i++) {
		for (int j = 0; j < mazeNum; j++) {
			cout << maze[i][j] << " ";
		}
		cout << "\n";
	}
	Solution(1, 1);
	system("pause");
}
