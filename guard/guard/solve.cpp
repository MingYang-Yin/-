#include <iostream>
#include<sstream>
using namespace std;
#define MAXNUM 22 //博物馆行数和列数的最大值
int d[6][3] = { {0,0,0},{0,0,0},{0,0,-1},{0,-1,0},{0,0,1},{0,1,0} };
int guard_now[MAXNUM][MAXNUM]; //设置当前警卫
int monitorCondition[MAXNUM][MAXNUM]; //表示监控情况
int bestSolution[MAXNUM][MAXNUM]; //bestSolution返回最终结果
int k = 0; //当前已设置的警卫数为k
int t = 0; //储存受监视的陈列室数量
int t1, t2, more; //判断下界剪枝的条件参数
bool p;
int n;
int m;
int best; //当前最少警卫数为best

//在位置(i, j)处放一个警卫，并改变其周围受监控情况
void changeMonitoring(int i, int j) {
	guard_now[i][j] = 1;
	k++;
	//每个警卫机器人除了监视它所在的陈列室外，还可监视与它所在陈列室相邻的上、下、左、右4个陈列室。
	//设置这些位置的监视情况
	for (int r = 1; r <= 5; r++) {
		int p = i + d[r][1];
		int q = j + d[r][2];
		monitorCondition[p][q]++;
		if (monitorCondition[p][q] == 1) {
			t++;
		}
	}
}

//撤销在位置(i, j)处设置的警卫，更新监控情况
void restore(int i, int j) {
	guard_now[i][j] = 0;
	k--;
	for (int r = 1; r <= 5; r++) {
		int p = i + d[r][1];
		int q = j + d[r][2];
		monitorCondition[p][q]--;
		if (monitorCondition[p][q] == 0)
			t--;
	}
}

//回溯
void search(int i, int j) {
	do { //搜索没被监控的位置，方向从上到下，从左至右
		j++;
		if (j > m) {
			i++;
			j = 1;
		}
	} while (!((monitorCondition[i][j] == 0) || (i > n)));
	if (i > n) {
		if (k < best) { //刷新警卫值
			best = k;
			for (int p = 1; p <= n; p++) {
				for (int q = 1; q <= m; q++) {
					bestSolution[p][q] = guard_now[p][q];
				}
			}
			return;
		}
	}
	if (k + (t1 - t) / 5 >= best) {//设置警卫数下界为还需设置的最少警卫数加上现有的警卫数
		return;
	}
	if ((i < n - 1) && (k + (t2 - t) / 5 >= best)) {//如果比最优警卫数多的话，需要剪枝
		return;
	}
	if (i < n) { //结点p
		changeMonitoring(i + 1, j);
		search(i, j); //递归搜索下一个点
		restore(i + 1, j); //恢复
	}
	if (monitorCondition[i][j + 1] == 0) { //结点q
		changeMonitoring(i, j);
		search(i, j);
		restore(i, j);
	}
	if ((j < m) && ((monitorCondition[i][j + 1] == 0) || (monitorCondition[i][j + 2] == 0))) { //结点r
		changeMonitoring(i, j + 1);
		search(i, j);
		restore(i, j + 1);
	}
}

//计算
void compute() {
	more = m / 4 + 1;
	if (m % 4 == 3)
		more++;
	else if (m % 4 == 2)
		more += 2;
	t2 = m * n + more + 4;
	t1 = m * n + 4;
	best = 65536;
	if (m == 1 && n == 1) {
		cout << 1 << "\n";
		cout << 1 << "\n";
	}
	for (int i = 0; i <= m + 1; i++) { //在整个外面加上一圈，便于处理边界情况
		monitorCondition[0][i] = 1;
		monitorCondition[n + 1][i] = 1;
	}
	for (int i = 0; i <= n + 1; i++) {
		monitorCondition[i][0] = 1;
		monitorCondition[i][m + 1] = 1;
	}
	search(1, 0);
}

//判断用户输入的是否是数字的函数
int examine(string input) {
	int i = 0;
	int num;
	stringstream ss;
	//遍历字符串的每个字符，判断其是否属于数字
	while (input[i] != '\0') {
		if (input[i] > '9' || input[i] < '0')
			return (-1); //如果不是数字，返回-1
		i++;
	}
	ss << input;
	ss >> num;
	return num; //如果是数字，返回数字的值
}

//获取用户的输入
void input() {
	int numberFlag; //判断是否为数字的标志
	string tempL; //以字符串的形式存储用户的输入，以方便进行输入检查

	cout << "**********************获取用户输入**********************\n\n";
	cout << "请设置陈列馆区域：\n";

	//获取用户输入的行数m
	cout << "请输入陈列馆行数m：（注意：1≤m≤20）：";
	cin >> tempL;
	numberFlag = examine(tempL); //判断用户输入的是否是数字
	while (numberFlag <= 0 || numberFlag > 20) { //检查用户的输入是否是数字或是否越界
		cout << "您的输入有误，请重新输入：";
		cin >> tempL;
		numberFlag = examine(tempL); //判断用户输入的是否是数字
	}
	n = numberFlag; //输入正确，将用户输入的行数赋给n
	//获取用户输入的列数n
	cout << "请输入陈列馆列数n：（注意：1≤n≤20）：";
	cin >> tempL;
	numberFlag = examine(tempL); //判断用户输入的是否是数字
	while (numberFlag <= 0 || numberFlag > 20) { //检查用户的输入是否是数字或是否越界
		cout << "您的输入有误，请重新输入：";
		cin >> tempL;
		numberFlag = examine(tempL); //判断用户输入的是否是数字
	}
	m = numberFlag; //输入正确，将用户输入的列数赋给m
	cout << "\n";
}

//打印结果
void output() {
	cout << "最少警卫数是：" << best << "，哨位安排如下所示：" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << bestSolution[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	input(); //获取用户的输入
	compute(); //计算
	cout << "**********************警卫问题结果**********************\n\n";
	output(); //打印结果
	system("pause");
}
