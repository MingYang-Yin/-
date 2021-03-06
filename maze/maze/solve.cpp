/*#include <iostream>
#include <vector>
#include "stackDef.h"
using namespace std;
int maze[100][100];
bool mazeVisit[100][100];
bool mazeVisitY[100][100];
//定义，在一个格子中，只能往右/下方走
vector<int> seqX;//储存路径
vector<int> seqY;//储存路径
int mazeNum;
int allPath[20][100][2];
int index = 0;
int exitX;
int exitY;//出口的x、y坐标
stack *stackX = new stack();
stack *stackY = new stack();*/

/*
//检查是否需要剪枝
bool check(int nodeX,int nodeY, int direction) {
	if (direction == 1) {
		if (maze[nodeX+1][nodeY] == 1) {//碰到墙，需要剪枝
			return true;
		}
	}
	if (direction == 0) {
		if (maze[nodeX][nodeY+1] == 1) {//碰到墙，需要剪枝
			return true;
		}
	}
	return false;
}*/

/*
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
	cout << "请输入迷宫的行和列：";
	cin >> mazeNum;
	init(mazeNum);
	exitX = mazeNum - 2;
	exitY = mazeNum - 2;//出口的x、y坐标
	*/
	/*for (int i = 0; i < mazeNum; i++) {
		for (int j = 0; j < mazeNum; j++) {
			cout << "请输入迷宫的第" << i<<","<<j << "位";
			cin >> maze[i][j];
		}
	}*/
	/*while (k == 1) {
		while (flag1 == false) {
			cout << "请输入无法通行的点的行数";
			cin >> tempL;
			c1 = examine(tempL);
		}
		flag1 = false;
		while (flag1 == false) {
			cout << "请输入无法通行的点的列数";
			cin >> tempL;
			c2 = examine(tempL);
		}
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
			cout << "该点已经输入过！\n";
		}
		else if (c1 > mazeNum-1 || c2 > mazeNum-1) {
			cout << "非法的点编号！请重新输入该点的两个坐标！\n";
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
		cout << "("<<elex << ","<<eley<<")  ";
	}
	cout << "(" << exitX << "," << exitY << ")  ";
	cout << "\n";
}*/
/*
void dfs_search(int nodeX, int nodeY) {
	if (nodeX==exitX&&nodeY==exitY) {
		cout << "找到出口";
		result1();
		result();
	}
	else {
		//向下走
		if (!check(nodeX,nodeY,1)) {
			seqX.push_back(nodeX);
			seqY.push_back(nodeY);
			dfs_search(nodeX + 1, nodeY);
			seqX.erase(seqX.begin() + seqX.size()-1);
			seqY.erase(seqY.begin() + seqY.size()-1);
		}
		//向右走
		if (!check(nodeX, nodeY,0)) {
			seqX.push_back(nodeX);
			seqY.push_back(nodeY);
			dfs_search(nodeX, nodeY+1);
			seqX.erase(seqX.begin() + seqX.size()-1);
			seqY.erase(seqY.begin() + seqY.size()-1);
		}
	}
}*/

/*void dfs_search(int nodeX, int nodeY) {
	stackX->push(nodeX);
	stackY->push(nodeY);
	int x = 0;
	int y = 0;
	while (stackX->top1() != -1) {//若栈不为空
		x = stackX->top1();
		y = stackY->top1();
		if (x <= mazeNum - 2 && y <= mazeNum - 2) {
			if (x == exitX && y == exitY) {//若走到出口
				cout << "找到出口，路径为：";
				int k = 0;
				while (stackX->printStack(k) != -1) {
					cout << "(" << stackX->printStack(k) << "," << stackY->printStack(k) << ")  ";
					k++;
				}
				cout << "\n";
				stackX->pop();
				stackY->pop();
				while (stackX->top1() != -1) {
					if (mazeVisitY[stackX->top1()][stackY->top1()] == 1) {
						mazeVisitY[stackX->top1()][stackY->top1()] == 0;
						stackX->pop();
						stackY->pop();
					}
					else
						break;
				}
				//break;
			}
			else {
				while (stackX->top1() != -1) {
					if (mazeVisitY[stackX->top1()][stackY->top1()] == 1) {
						mazeVisitY[stackX->top1()][stackY->top1()] == 0;
						stackX->pop();
						stackY->pop();
					}
					else
						break;
				}
			}
			x = stackX->top1();
			y = stackY->top1();
			if (x != -1 && y != -1) {
				if (mazeVisit[x][y] == 0) {
					if (maze[x + 1][y] != 1) {//若向下走碰不到墙
						stackX->push(x + 1);
						stackY->push(y);
						mazeVisit[x][y] = 1;
					}
					else
						mazeVisit[x][y] = 1;
				}
				x = stackX->top1();
				y = stackY->top1();
				if (mazeVisit[x][y] == 1) {
					if (maze[x][y + 1] != 1) {//若向右走碰不到墙
						stackX->push(x);
						stackY->push(y + 1);
						mazeVisitY[x][y] = 1;
					}
					else
						mazeVisitY[x][y] = 1;
				}
			}
			else
				break;
		}
	}
}

int main() {
	getUserInput();
	for (int i = 0; i < mazeNum; i++) {
		for (int j = 0; j < mazeNum; j++) {
			cout << maze[i][j] << " ";
		}
		cout << "\n";
	}
	dfs_search(1, 1);
	system("pause");
}*/
