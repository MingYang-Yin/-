#include <iostream>
using namespace std;
int color[100];
int n = 0;//储存图的顶点数
int m = 0;//储存用户输入的颜色数
int c[101][101];
bool flag = false;//记录用户输入是否为正整数（false表示不为，true表示为）
bool exam = false;

int examine(char a[]) {//检测用户的输入是否为数字
	flag = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "请输入一个正整数！" << endl;
			flag = false;
			break;
		}
	}
	if (flag) {
		for (int j = 0; a[j] != 0; j++) {//将用户输入的数字字符转化为数
			result = result + (a[j] - 48) * pow(10, i - j - 1);
		}
		flag = true;
	}
	return result;
}

void initC() {//初始化储存结点的数组
	for (int j = 0; j < n+1; j++) {
		for (int k = 0; k < n+1; k++) {
			c[j][k] = 0;
		}
	}
}

void getUserInput() {//获取用户输入
	int k = 1;
	char tempL[20];//暂时储存用户输入
	while (flag == false) {
		cout << "请输入图的顶点数（不得超过100）:";
		cin >> tempL;
		n = examine(tempL);
		if (n > 100) {
			cout << "图的顶点数不得超过100，请重新输入！\n";
			flag = false;
		}
	}
	flag = false;
	while (flag == false) {
		cout << "请输入图的颜色数:";
		cin >> tempL;
		m = examine(tempL);
	}
	flag = false;
	cout << "请输入编号"<<1<<"~"<<n<<"来确定图的连接关系（两顶点均输入0，则退出）:\n";
	int c1, c2;
	while (k == 1) {
		while (flag == false) {
			cout << "请输入边的一个顶点：";
			cin >> tempL;
			c1 = examine(tempL);
		}
		flag = false;
		while (flag == false) {
			cout << "请输入边的另一个顶点：";
			cin >> tempL;
			c2 = examine(tempL);
		}
		flag = false;
		if (c1 == 0 || c2 == 0) {
			if (c1 == 0 && c2 == 0) {
				k = 0;
			}
			else {
				cout << "不能输入一个0！\n";
			}
		}
		else if (c[c1][c2] == 1) {
			cout << "该边已经输入过！\n";
		}
		else if (c1>n||c2>n) {
			cout << "非法的结点编号！请重新输入该边的两个结点！\n";
		}
		else {
			flag = false;
			c[c1][c2] = 1;
			c[c2][c1] = 1;
		}
	}
	flag = false;
	cout << "\n";
}

bool Ok(int k) //判断顶点k的着色是否发生冲突
{
	for (int i = 1; i < k; i++)
		if (c[k][i] == 1 && color[i] == color[k])//表示冲突发生
			return false;
	return true;
}

void GraphColor(int n, int c[101][101], int m)
//所有数组下标从1开始
{
	for (int i = 1; i <= n; i++) //将数组color[n]初始化为0
		color[i] = 0;
	int k = 1;
	while (k >= 1) {
		color[k] = color[k] + 1;//尝试用颜色1~m为结点K涂色
		while (color[k] <= m)
			if (Ok(k))//若顶点k的着色不发生冲突，则通过
				break;
			else color[k] = color[k] + 1; //否则，搜索下一个颜色
		if (color[k] <= m && k == n) //求解完毕，输出解
		{
			for (int i = 1; i <= n; i++)
				cout << color[i]<<"  ";
			cout << "\n";
			exam = true;//表示有解
			//接着寻找下一种解
		}
		else if (color[k] <= m && k < n)//未求解完毕
			k = k + 1; //处理下一个顶点
		else {//处理完毕，回溯，处理下一种情况
			color[k] = 0;
			k = k - 1; //回溯
		}
	}
}


int main() {
	initC();//初始化数组
	cout << "*****************获取用户输入*******************\n";
	getUserInput();//获取用户输入
	cout << "\n*****************输出路径矩阵*******************\n";
	cout << "路径矩阵（1代表两节点有边，0代表没边）：\n";
	for (int j = 1; j < n+1; j++) {//打印路径矩阵
		for (int k = 1; k < n+1; k++) {
			cout << c[j][k];
		}
		cout << "\n";
	}
	cout << "\n****************验证颜色数*********************\n";
	cout << "\n当颜色数为"<<m<<"时，结点" << 1 << "~" << n << "着色情况如下：\n";
	GraphColor(n, c, m);
	if (exam == false) {//没有完成着色
		cout << "颜色数不足，无法完成着色\n";
	}
	exam = false;
	cout << "\n***************寻找最少颜色数********************\n";
	for (int i = 1; i <= n; i++) {//因为最多n种颜色可以完成图着色问题，最少颜色数应不大于n
		cout << "当颜色数为" << i << "时，结点" << 1 << "~" << n << "着色情况如下：：\n";
		GraphColor(n, c, i);
		if (exam == true) {
			cout << "满足条件的最少颜色数为：" << i << "\n";
			break;
		}
		else {
			cout << "颜色数不足，无法完成着色\n";
		}
	}
	system("pause");
}